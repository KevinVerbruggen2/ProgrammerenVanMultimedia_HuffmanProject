#include "eof-encoding.h"
#include <memory>


#include "Encoding.h"
#include "io/binary-io.h"
#include "io/data-endpoints.h"


namespace
{
    class EofEncodingImplementation : public EncodingImplementation
    {
    private:
        const u64 domain_size;
    public:
        EofEncodingImplementation(u64 domain_size) : domain_size(domain_size)
        {
        }
        
        //virtual void encode(io::InputStream& input, io::OutputStream& output);
        void encode(io::InputStream& input, io::OutputStream& output) override
        {
            while (!input.end_reached())
            {
                output.write(input.read());
            }
            output.write(char(domain_size));
        }

        void decode(io::InputStream& input, io::OutputStream& output) override
        {
            while (!input.end_reached())
            {
                char c = input.read();
                if (c == char(domain_size))
                {
                    break;
                }
                output.write(c);
            }
        }
    };    
}

std::shared_ptr<EncodingImplementation> create_eof_implementation(u64 domain_size)
{
    return std::make_shared<EofEncodingImplementation>(domain_size);
}
