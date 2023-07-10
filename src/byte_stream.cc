#include <stdexcept>

#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ) {}

void Writer::push( const string& data )
{
  if ( is_closed() || error_ || data.empty() ) {
    return;
  }

  if ( data.length() > available_capacity() ) {
    queue_.append( data.substr( 0, available_capacity() ) );
    tot_len_ += available_capacity();
  } else {
    queue_.append( data );
    tot_len_ += data.length();
  }
}

void Writer::close()
{
  this->closed_ = true;
}

void Writer::set_error()
{
  this->error_ = true;
}

bool Writer::is_closed() const
{
  return this->closed_;
}

uint64_t Writer::available_capacity() const
{
  return capacity_ - tot_len_ + out_len_;
}

uint64_t Writer::bytes_pushed() const
{
  return tot_len_;
}

string_view Reader::peek() const
{
  return std::string_view( queue_ );
}

bool Reader::is_finished() const
{
  // Your code here.
  return { closed_ && queue_.empty() };
}

bool Reader::has_error() const
{
  // Your code here.
  return error_;
}

void Reader::pop( uint64_t len )
{
  // Your code here.
  if ( error_ || queue_.empty() ) {
    return;
  }

  queue_ = queue_.substr( len, queue_.length() );
  out_len_ += len;
}

uint64_t Reader::bytes_buffered() const
{
  // Your code here.
  return tot_len_ - out_len_;
}

uint64_t Reader::bytes_popped() const
{
  // Your code here.
  return out_len_;
}