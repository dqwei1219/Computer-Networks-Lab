#include "network_interface.hh"

#include "arp_message.hh"
#include "ethernet_frame.hh"

using namespace std;

// ethernet_address: Ethernet (what ARP calls "hardware") address of the interface
// ip_address: IP (what ARP calls "protocol") address of the interface
NetworkInterface::NetworkInterface( const EthernetAddress& ethernet_address, const Address& ip_address )
  : ethernet_address_( ethernet_address ), ip_address_( ip_address )
{
  cerr << "DEBUG: Network interface has Ethernet address " << to_string( ethernet_address_ ) << " and IP address "
       << ip_address.ip() << "\n";
}

// dgram: the IPv4 datagram to be sent
// next_hop: the IP address of the interface to send it to (typically a router or default gateway, but
// may also be another host if directly connected to the same network as the destination)

// Note: the Address type can be converted to a uint32_t (raw 32-bit IP address) by using the
// Address::ipv4_numeric() method.
void NetworkInterface::send_datagram( const InternetDatagram& dgram, const Address& next_hop )
{
  const uint32_t next_hop_ip = next_hop.ipv4_numeric();
  if ( arp_table_.contains( next_hop_ip ) ) { // contains the ethernet address
    EthernetFrame frame;
    frame.payload = serialize( dgram );
    frame.header.dst = arp_table_[next_hop_ip].eth_addr;
    frame.header.src = this->ethernet_address_;
    frame.header.type = EthernetHeader::TYPE_IPv4;
    outbound_frames_.push( frame );
  } else { // broadcast ARP request
    // if we didnt send the request
    if ( arp_requests_lifetime_.find( next_hop_ip ) == arp_requests_lifetime_.end() ) {
      ARPMessage arp_msg;
      arp_msg.opcode = ARPMessage::OPCODE_REQUEST;
      arp_msg.sender_ip_address = ip_address_.ipv4_numeric();
      arp_msg.sender_ethernet_address = ethernet_address_;
      arp_msg.target_ip_address = next_hop_ip;
      arp_msg.target_ethernet_address = { /* empty */ };

      EthernetFrame arp_eth_frame;
      arp_eth_frame.header.src = ethernet_address_;
      arp_eth_frame.header.dst = ETHERNET_BROADCAST;
      arp_eth_frame.header.type = EthernetHeader::TYPE_ARP;
      arp_eth_frame.payload = serialize( arp_msg );
      outbound_frames_.push( arp_eth_frame );

      arp_requests_lifetime_.insert( std::make_pair( next_hop_ip, ARP_REQUEST_DEFAULT_TTL ) );
    }

    // if we already send that request
    arp_datagrams_waiting_list_.push_back( std::pair { next_hop, dgram } );
  }
}

// frame: the incoming Ethernet frame
optional<InternetDatagram> NetworkInterface::recv_frame( const EthernetFrame& frame )
{
  // if this frame is not for us, drop it
  if ( frame.header.dst != this->ethernet_address_ && frame.header.dst != ETHERNET_BROADCAST ) {
    return nullopt;
  }

  // if it is an IP datagrams
  if ( frame.header.type == EthernetHeader::TYPE_IPv4 ) {
    InternetDatagram dgram;
    if ( !parse( dgram, frame.payload ) ) {
      return nullopt;
    } else {
      return dgram;
    }
  }

  // if it is an ARP datagrams
  if ( frame.header.type == EthernetHeader::TYPE_ARP ) {
    ARPMessage arp_msg;
    if ( not parse( arp_msg, frame.payload ) ) {
      printf( "[NetworkInterface ERROR]: 'recv_frame' ARP parse error\n" );
      return nullopt;
    }

    const bool is_arp_request
      = arp_msg.opcode == ARPMessage::OPCODE_REQUEST && arp_msg.target_ip_address == ip_address_.ipv4_numeric();
    if ( is_arp_request ) {
      ARPMessage arp_reply_msg;
      arp_reply_msg.opcode = ARPMessage::OPCODE_REPLY;
      arp_reply_msg.sender_ip_address = ip_address_.ipv4_numeric();
      arp_reply_msg.sender_ethernet_address = ethernet_address_;
      arp_reply_msg.target_ip_address = arp_msg.sender_ip_address;
      arp_reply_msg.target_ethernet_address = arp_msg.sender_ethernet_address;

      EthernetFrame arp_reply_eth_frame;
      arp_reply_eth_frame.header.src = ethernet_address_;
      arp_reply_eth_frame.header.dst = arp_msg.sender_ethernet_address;
      arp_reply_eth_frame.header.type = EthernetHeader::TYPE_ARP;
      arp_reply_eth_frame.payload = serialize( arp_reply_msg );
      outbound_frames_.push( arp_reply_eth_frame );
    }

    const bool is_arp_response
      = arp_msg.opcode == ARPMessage::OPCODE_REPLY && arp_msg.target_ethernet_address == ethernet_address_;

    // we can get arp info from either ARP request or ARP reply
    if ( is_arp_request || is_arp_response ) {
      arp_table_.emplace(
        std::make_pair( arp_msg.sender_ip_address, arp_t { arp_msg.sender_ethernet_address, ARP_DEFAULT_TTL } ) );
      // delete arp datagrams waiting list
      for ( auto iter = arp_datagrams_waiting_list_.begin(); iter != arp_datagrams_waiting_list_.end(); ) {
        const auto& [ipv4_addr, datagram] = *iter;
        if ( ipv4_addr.ipv4_numeric() == arp_msg.sender_ip_address ) {
          send_datagram( datagram, ipv4_addr );
          iter = arp_datagrams_waiting_list_.erase( iter );
        } else {
          iter++;
        }
      }
      arp_requests_lifetime_.erase( arp_msg.sender_ip_address );
    }
  }
  return nullopt;
}

// ms_since_last_tick: the number of milliseconds since the last call to this method
void NetworkInterface::tick( const size_t ms_since_last_tick )
{
  /* delete expired ARP items in ARP Table */
  // FIXME: Don't use 'iter++' if we have erase current iter's data!
  for ( auto iter = arp_table_.begin(); iter != arp_table_.end(); /* nop */ ) {
    auto& [ipv4_addr_numeric, arp] = *iter;
    if ( arp.ttl <= ms_since_last_tick ) {
      iter = arp_table_.erase( iter );
    } else {
      arp.ttl -= ms_since_last_tick;
      iter++;
    }
  }

  /* delete expired ARP requests */
  for ( auto& [ipv4_addr, arp_ttl] : arp_requests_lifetime_ ) {
    /* resent ARP request if this request has expired */
    if ( arp_ttl <= ms_since_last_tick ) {
      ARPMessage arp_msg;
      arp_msg.opcode = ARPMessage::OPCODE_REQUEST;
      arp_msg.sender_ip_address = ip_address_.ipv4_numeric();
      arp_msg.sender_ethernet_address = ethernet_address_;
      arp_msg.target_ip_address = ipv4_addr;
      arp_msg.target_ethernet_address = { /* empty */ };

      EthernetFrame arp_eth_frame;
      arp_eth_frame.header.src = ethernet_address_;
      arp_eth_frame.header.dst = ETHERNET_BROADCAST;
      arp_eth_frame.header.type = EthernetHeader::TYPE_ARP;
      arp_eth_frame.payload = serialize( arp_msg );
      outbound_frames_.push( arp_eth_frame );

      /* reset ARP ttl for this component */
      arp_ttl = ARP_REQUEST_DEFAULT_TTL;
    } else {
      arp_ttl -= ms_since_last_tick;
    }
  }
}

optional<EthernetFrame> NetworkInterface::maybe_send()
{
  if ( outbound_frames_.empty() ) {
    return nullopt;
  }

  EthernetFrame send = std::move( this->outbound_frames_.front() );
  this->outbound_frames_.pop();
  return send;
}
