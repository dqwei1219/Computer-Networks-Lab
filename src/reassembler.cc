#include "reassembler.hh"

using namespace std;

bool Reassembler::is_closed() const
{
  return closed_ && bytes_pending() == 0;
}

void Reassembler::insert( uint64_t first_index, string data, bool is_last_substring, Writer& output )
{
  if ( is_last_substring ) {
    closed_ = true;
  }

  /* handle edge cases
   * 1. data is empty
   * 2. available capacity is 0
   * 3. when it is already been buffered in bytestream and no need to assemble
   * 4. When it is an unacceptable bytes
   */
  if ( data.empty() || output.available_capacity() == 0 || first_index + data.length() - 1 < unassembled_index_
       || unassembled_index_ + output.available_capacity() <= first_index ) {

    if ( is_closed() ) {
      output.close();
    }
    return;
  }

  /*
   * Make the data fit into the capacity
   */
  const uint64_t capacity = output.available_capacity(); // easier to type.
  uint64_t new_index = first_index;                      // where the current data start.

  if ( unassembled_index_ >= first_index ) { // when it has part in bytestream
    new_index = unassembled_index_;          // we ignore the part already in byte stream
    const uint64_t overlapped_length
      = unassembled_index_ - first_index; // calculate the part already in Bytestream.
    data
      = data.substr( overlapped_length,
                     min( data.size() - overlapped_length,
                          capacity ) ); // then only get the data that is in capacity, or all the data if it fits.
  } else {
    // then the data is either all in Reassembler's or part in reassembler and part is unacceptable.
    data = data.substr( 0, min( capacity, data.size() ) ); // data is all in reassembler
    if ( first_index + data.size() - 1
         > unassembled_index_ + capacity - 1 ) { // data is partially in, then only get the part in capacity
      data = data.substr( 0, unassembled_index_ + capacity - first_index );
    }
  }

  /*
   *  when the current data overlapped with the rear data
   */
  auto rear_iter
    = unassembled_substrings_.lower_bound( new_index );  // find the first substring that is after the new_index
  while ( rear_iter != unassembled_substrings_.end() ) { // iterate through the end
    auto& [rear_index, rear_data] = *rear_iter;          // get the start index and its substrings
    if ( new_index + data.size() - 1 < rear_index ) {    // if it has no overlapp with the later substring
      break;
    }
    uint64_t rear_overlapped_length = 0;
    if ( new_index + data.size() - 1
         < rear_index + rear_data.size() - 1 ) { // partially overlapped, rear index is further behind
      rear_overlapped_length = new_index + data.size() - rear_index;
    } else {
      rear_overlapped_length = rear_data.size(); // all overlapped
    }

    // prepare for the next iteration
    const uint64_t next_rear = rear_index + rear_data.size() - 1;
    if ( rear_overlapped_length
         == rear_data.size() ) { // when the rear_data is fully overlapped we delete the length and erase it;
      unassembled_bytes_ -= rear_data.size();
      unassembled_substrings_.erase( rear_index );
    } else {
      // only partially overalapped, we only delete the overlapped part.
      data.erase( data.end() - static_cast<int64_t>( rear_overlapped_length ), data.end() );
    }

    // searh for the next closest substring
    rear_iter = unassembled_substrings_.lower_bound( next_rear );
  }

  /*
   * when the current data overlapped with the front data
   */
  if ( first_index > unassembled_index_ ) {
    auto front_iter = unassembled_substrings_.upper_bound( new_index );
    if ( front_iter != unassembled_substrings_.begin() ) {
      front_iter--;
      const auto& [front_index, front_data] = *front_iter;
      if ( front_index + front_data.size() - 1 >= first_index ) { // check if there is an overlapped
        uint64_t overlapped_length = 0;
        if ( front_index + front_data.size()
             <= first_index + data.size() ) { // if there is an partially overalapped
          overlapped_length = front_index + front_data.size() - first_index;
        } else {
          overlapped_length = data.size(); // else the data is all overalapped in the front part;
        }
        if ( overlapped_length == front_data.size() ) { // if all overlapped then nothing is stored
          unassembled_bytes_ -= front_data.size();
          unassembled_substrings_.erase( front_index );
        } else {
          data.erase( data.begin(),
                      data.begin()
                        + static_cast<int64_t>( overlapped_length ) ); // else only erase the overlapped part
          new_index = first_index + overlapped_length;
        }
      }
    }
  }

  /**
   * push data to the output byte stream, and update our unassembled_substring since we pushed some bytes to the
   * bytestream
   *
   */
  if ( data.size() > 0 ) {
    unassembled_bytes_ += data.size();
    unassembled_substrings_.insert( make_pair( new_index, std::move( data ) ) );
  }

  for ( auto iter = unassembled_substrings_.begin(); iter != unassembled_substrings_.end(); ) {
    auto& [sub_index, sub_data] = *iter;
    if ( sub_index == unassembled_index_ ) {
      const uint64_t prev_bytes_pushed = output.bytes_pushed();
      output.push( sub_data );
      const uint64_t bytes_pushed = output.bytes_pushed();
      if ( prev_bytes_pushed + sub_data.size()
           != bytes_pushed ) { // we cannot push all the data since it reach capacity
        const uint64_t pushed_length = bytes_pushed - prev_bytes_pushed;
        unassembled_bytes_ -= pushed_length; // we already assembled the pushed length
        unassembled_index_ += pushed_length; // update the sliding window;
        unassembled_substrings_.insert( make_pair(
          unassembled_index_,
          sub_data.substr( pushed_length ) ) ); // create a new unassembled substring part minus the pushed_bytes
        unassembled_substrings_.erase( sub_index ); // erase the old one
        break;
      }
      // then we can push all the sub_data size
      unassembled_bytes_ -= sub_data.size();
      unassembled_index_ += sub_data.size();
      unassembled_substrings_.erase( sub_index );
      iter = unassembled_substrings_.find( unassembled_index_ );

    } else {
      break;
    }
  }

  if ( is_closed() ) {
    output.close();
  }
}

uint64_t Reassembler::bytes_pending() const
{
  return unassembled_bytes_;
}