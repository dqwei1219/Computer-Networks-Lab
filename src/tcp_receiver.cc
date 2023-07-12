#include "tcp_receiver.hh"
#include <iostream>

using namespace std;

void TCPReceiver::receive( TCPSenderMessage message, Reassembler& reassembler, Writer& inbound_stream )
{
  if ( !set_syn_ ) {
    if ( !message.SYN ) {
      return;
    }
    set_syn_ = true;
    isn_ = message.seqno;
  }

  uint64_t abs_seqno
    = message.seqno.unwrap( isn_, inbound_stream.bytes_pushed() + 1 ); // total bytes pushed + 1 is the next index;
  uint64_t start_index = abs_seqno + message.SYN - 1; // SYN occupied one seqno, isn_ occupy one index so minus one.
  reassembler.insert( start_index, message.payload.release(), message.FIN, inbound_stream );
}

TCPReceiverMessage TCPReceiver::send( const Writer& inbound_stream ) const
{
  TCPReceiverMessage msg;
  uint16_t window_size
    = inbound_stream.available_capacity() > UINT16_MAX ? UINT16_MAX : inbound_stream.available_capacity();

  if ( !set_syn_ ) {
    return { std::optional<Wrap32> {}, window_size };
  }

  uint64_t abs_ackno_offset = inbound_stream.bytes_pushed() + 1;

  if ( inbound_stream.is_closed() ) {
    abs_ackno_offset++;
  }

  msg.ackno = isn_ + abs_ackno_offset;
  msg.window_size = window_size;
  return msg;
}