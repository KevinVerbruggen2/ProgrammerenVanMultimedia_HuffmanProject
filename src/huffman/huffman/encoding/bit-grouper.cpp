#include "bit-grouper.h"

#include "EncodingImplementation.h"
#include "io/binary-io.h"


namespace
{
    class BitGrouperImplementation : public EncodingImplementation
    {
    private:
        const unsigned group_size;
    public:
        BitGrouperImplementation(unsigned group_size) : group_size(group_size)
        {
        }
        
        void encode(io::InputStream& input, io::OutputStream& output) override
        {
            while (!input.end_reached())
            {
                const uint64_t value = read_bits(group_size, input);
                output.write(value);
            }
        }

        void decode (io::InputStream& input, io::OutputStream& output) override
        {
            while (!input.end_reached())
            {
                const uint64_t value = input.read();
                write_bits(value, group_size, output);
            }
        }
        
    };
}


/*
* std::shared_ptr<EncodingImplementation> create_eof_implementation(u64 domain_size)
{
    return std::make_shared<EofEncodingImplementation>(domain_size);
}

 */


std::shared_ptr<EncodingImplementation> create_bit_grouper_implementation(u64 group_size)
{
    return std::make_shared<BitGrouperImplementation>(group_size);
}
