#ifndef BINARY_IO_H
#define BINARY_IO_H

#include "streams.h"

namespace io
{
    void write_bits(uint64_t value, unsigned nbits, io::OutputStream& output);
    uint64_t read_bits(unsigned nbits, io::InputStream& input);
}

#endif  // BINARY_IO_H
