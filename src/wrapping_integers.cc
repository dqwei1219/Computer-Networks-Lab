#include "wrapping_integers.hh"

using namespace std;

Wrap32 Wrap32::wrap( uint64_t n, Wrap32 zero_point ) // given an abs seqno, return its relative seqno
{
  return zero_point + static_cast<uint32_t>(n); // abs seqno + the zero_point will get the relative seqno
}

uint64_t Wrap32::unwrap(Wrap32 zero_point, uint64_t checkpoint) const // given a seqno, return its abs seqno near its check point
{
  uint32_t offset = this->raw_value_ - wrap(checkpoint, zero_point).raw_value_; // get the offset
  uint64_t ret = checkpoint + offset;

  if (offset >= (1u << 31) && ret >= (1ul << 32)) {
    ret -= (1ul << 32);
  }

  return ret;
}
