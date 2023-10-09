#ifndef HUFFMAN_ENCODING_IMPLEMENTATION_H
#define HUFFMAN_ENCODING_IMPLEMENTATION_H
#include "io/streams.h"

class EncodingImplementation
{
public:
    virtual ~EncodingImplementation() {} // Empty virtual destructor

    virtual void encode(io::InputStream& input, io::OutputStream& output) = 0;
    virtual void decode(io::InputStream& input, io::OutputStream& output) = 0;
};

#endif
