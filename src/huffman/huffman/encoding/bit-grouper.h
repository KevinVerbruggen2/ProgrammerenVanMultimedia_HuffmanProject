#ifndef BIT_GROUPER_H
#define BIT_GROUPER_H 
#include <memory>

#include "Encoding.h"
#include "EncodingImplementation.h"

std::shared_ptr<EncodingImplementation> create_bit_grouper_implementation(u64 group_size);

namespace encoding
{
    template<unsigned GROUP_SIZE>
    Encoding<2, 1 << GROUP_SIZE>bit_grouper()
    {
        //make a new Encoding with the create_eof_implementation
        return Encoding<2, 1 << GROUP_SIZE>(create_bit_grouper_implementation(GROUP_SIZE));
    }
}

#endif
