#include "tcp_sender.hh"
#include "buffer.hh"
#include "tcp_config.hh"
#include "tcp_sender_message.hh"
#include "wrapping_integers.hh"

#include <bits/ranges_base.h>
#include <cstddef>
#include <cstdint>
#include <random>

using namespace std;

/* TCPSender constructor (uses a random ISN if none given) */
TCPSender::TCPSender(uint64_t initial_RTO_ms, optional<Wrap32> fixed_isn)
    : isn_(fixed_isn.value_or(Wrap32{random_device()()})),
      initial_RTO_ms_(initial_RTO_ms) {}

uint64_t TCPSender::sequence_numbers_in_flight() const {
    return bytes_in_flight_;
}

uint64_t TCPSender::consecutive_retransmissions() const {
    return consecutive_retransmissions_;
}

optional<TCPSenderMessage> TCPSender::maybe_send() {
    if (_messages.empty()) { // if no mesage we return
        return {};
    }

    TCPSenderMessage msg = _messages.front(); // we need to send a data segment
    _messages.pop();

    return msg;
}

void TCPSender::push(Reader &outbound_stream) {
    if (fin_sent_) { // if there is a FIN, we shoudn't push any data
        return;
    }

    uint64_t space = rcvno + (window_size_ ? window_size_ : 1) - nxt_seqno_; // total size (rcvno + window_size) - next seqno, is the amount of space still available in the window size
    while (space > 0 && !fin_sent_) { // while we have more space and we are not finished
        TCPSenderMessage msg;
        if (!nxt_seqno_) {  // if this is the first msg we want to send, it is SYN
            msg.SYN = true; 
            syn_sent_ = true;
            --space; // SYN occupies one byte
        }

        msg.seqno = Wrap32::wrap(nxt_seqno_, isn_);
        Buffer &buffer = msg.payload;
        read(outbound_stream, min(space, TCPConfig::MAX_PAYLOAD_SIZE), buffer);
        space -= buffer.size();
        if (outbound_stream.is_finished() && space > 0) { // if it is finished
            msg.FIN = true;
            fin_sent_ = true;
            --space; // FIN occupies one byte
        }

        uint64_t len = msg.sequence_length();
        if (!len) { // if no length, then there is no data need to be sent
            return;
        }
        _messages.push(msg); // else there are some remaning data
        if (!timer_.in_run()) { // start timer if timer not start
            timer_.start();
        }
        _outstanding_messages.push(msg); // push remaining data
        nxt_seqno_ += len; // reset for next sequence number
        bytes_in_flight_ += len; // we send more data has not been acknolwedge
    }
}

TCPSenderMessage TCPSender::send_empty_message() const {
    /**
     * Send empty message for acknoledge something
    */
    TCPSenderMessage msg;
    msg.seqno = Wrap32::wrap(nxt_seqno_, isn_); // wrap the next sequence number closest to the isn_
    return msg;
}

void TCPSender::receive(const TCPReceiverMessage &msg) {

    // if there is an acknolowdge flag means a new message
    if (msg.ackno) {
        rcvno = msg.ackno->unwrap(isn_, nxt_seqno_); // unwrap to be the new receive
    }

    if (rcvno > nxt_seqno_) { // impossible to receive a future data.
        return;
    }
    window_size_ = msg.window_size; // update window size

    bool new_check_ = false; // flag for "do we need to reset the timer ?"
    while (!_outstanding_messages.empty()) { // after receiving data, check if we need to update our oustanding queue.
        TCPSenderMessage s_msg = _outstanding_messages.front(); 
        uint64_t len = s_msg.sequence_length();
        uint64_t seqno = s_msg.seqno.unwrap(isn_, nxt_seqno_); // unwrap it provide zero point and closest to the next_seqno_;
        if (seqno + len > rcvno) { // if we haven't acknowledge this data, break; 
            break; 
        }
        _outstanding_messages.pop(); // then this is an outstanding data we now received
        bytes_in_flight_ -= len; // received len bit minus it
        new_check_ = true;
    }
    if (new_check_) { // reset timer
        retransmission_timeout_ = initial_RTO_ms_; // back to intiial zero
        if (!_outstanding_messages.empty()) { // if it is not empty, start the timer
            timer_.start();
        } else {
            timer_.stop(); // stop the timer since no dat is outstanding
        }
        consecutive_retransmissions_ = 0; // we received an outstanding data segment so it is not hopeless connection, reset zero.
    }
}

void TCPSender::tick(const size_t ms_since_last_tick) {
    /**
     * We want to resend if the timer goes off and there are outstanding segments.
     * 
     * After timer expired
     * 1. push the earliest segment to the message queue
     * 2. double timout and increment consecutive retrransmission if window size is nonzero
     * 3. reset the timer
    */
    if(_outstanding_messages.empty() || !timer_.expired(ms_since_last_tick, retransmission_timeout_) ) {
        return;
    }

    _messages.push(_outstanding_messages.front());

    if(window_size_ > 0) { 
        retransmission_timeout_ <<= 1;
    }
    consecutive_retransmissions_++;
    timer_.start();
}