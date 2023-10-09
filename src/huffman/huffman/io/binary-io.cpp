#include "streams.h"
#include "util.h"

namespace io
{
    uint64_t read_bits(unsigned nbits, io::InputStream& input)
    {
        uint64_t result = 0;
        
        for (unsigned i = 0; i < nbits; ++i)
        {
            if (input.end_reached())
            {
                result <<= (nbits - i); // Shift the result to the left to make room for remaining bits
                break;
            }
            
            Datum bit = input.read();
            result = (result << 1) | bit; // Shift the result to the left and add the new bit
        }
        
        return result;
    }
    
    void write_bits(uint64_t value, unsigned nbits, io::OutputStream& output)
    {
        for (unsigned i = 0; i < nbits; ++i)
        {
            Datum bit = value >> (nbits - i - 1) & 1; // Extract the i-th bit from the value
            output.write(bit); // Write the bit to the output stream
        }
    }
}
