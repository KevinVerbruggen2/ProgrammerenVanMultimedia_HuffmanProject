#ifndef ENCODING_COMBINER_H
#define ENCODING_COMBINER_H
#include "EncodingImplementation.h"
#include "encoding/eof-encoding.h"
#include "encoding/bit-grouper.h"
#include "io/memory-buffer.h"


namespace encoding
{
    template <u64 N1, u64 N2, u64 N3>
    class EncodingCombinerImplementation : public EncodingImplementation
    {
    private:
        // N1 input_domain_size_e1;
        // N2 output_domain_size_e1;
        // N3 output_domain_size_e2;
        std::shared_ptr<EncodingImplementation> e1_;
        std::shared_ptr<EncodingImplementation> e2_;

    public:
        EncodingCombinerImplementation(std::shared_ptr<EncodingImplementation> e1, std::shared_ptr<EncodingImplementation> e2) : e1_(e1), e2_(e2) {}

        void encode(io::InputStream &input, io::OutputStream &output) override {
            // Create a temporary buffer for e1's output
            std::shared_ptr<io::MemoryBuffer<N2>> buffer = std::make_shared<io::MemoryBuffer<N2>>();

            std::shared_ptr<io::OutputStream> buffer_output = io::create_memory_output_stream(buffer->data());

            // Encode input with e1 and write the result to the buffer
            e1_->encode(input, *buffer_output);

            std::shared_ptr<io::InputStream> buffer_input = io::create_memory_input_stream(buffer->data());

            // Pass the buffer's output to e2 for further encoding
            e2_->encode(*buffer_input, output);
        }
        

        void decode(io::InputStream& input, io::OutputStream& output) override
        {
            //do the reverse of encode
            std::shared_ptr<io::MemoryBuffer<N2>> buffer = std::make_shared<io::MemoryBuffer<N2>>();

            std::shared_ptr<io::OutputStream> buffer_output = io::create_memory_output_stream(buffer->data());

            e2_->decode(input, *buffer_output);

            std::shared_ptr<io::InputStream> buffer_input = io::create_memory_input_stream(buffer->data());

            e1_->decode(*buffer_input, output);
        }
    };
}


template <u64 N1, u64 N2, u64 N3>
std::shared_ptr<EncodingImplementation>
operator|(std::shared_ptr<EncodingImplementation> e1,
          std::shared_ptr<EncodingImplementation> e2) {
    return std::make_shared<encoding::EncodingCombinerImplementation<N1, N2, N3>>(e1, e2);
}



#endif





/*
 * #ifndef ENCODING_COMBINER_H
#define ENCODING_COMBINER_H
#include "EncodingImplementation.h"
#include "encoding/eof-encoding.h"
#include "encoding/bit-grouper.h"
#include "io/memory-buffer.h"


namespace encoding
{
    template <typename N1, typename  N2, typename  N3>
    class EncodingCombinerImplementation : public EncodingImplementation
    {
    private:
        N1 input_domain_size_e1;
        N2 output_domain_size_e1;
        N3 output_domain_size_e2;
        // const u64 input_domain_size_e1;
        // const u64 output_domain_size_e1;
        // const u64 output_domain_size_e2;

    public:
        EncodingCombinerImplementation()
        : input_domain_size_e1(input_domain_size_e1), output_domain_size_e1(output_domain_size_e1), output_domain_size_e2(output_domain_size_e2)
        {
        }

        void encode(io::InputStream& input, io::OutputStream& output) override
        {
            std::shared_ptr<EncodingImplementation> eof_implementation = create_eof_implementation(input_domain_size_e1);
            std::shared_ptr<EncodingImplementation> bit_grouper_implementation = create_bit_grouper_implementation(output_domain_size_e1);

            // buffer to store the output of e1
            std::shared_ptr<io::MemoryBuffer<>> tmp_output_buffer = std::make_shared<io::MemoryBuffer<>>();
            
            eof_implementation->encode(input, io::create_memory_output_stream(tmp_output_buffer));
            bit_grouper_implementation->encode(io::create_memory_input_stream(tmp_output_buffer), output);
        }

        void decode(io::InputStream& input, io::OutputStream& output) override
        {
            
        }
        
        
    };
}


std::shared_ptr<EncodingImplementation> create_combiner_implementation(const u64 input_domain_size_e1, const u64 output_domain_size_e1, const u64 output_domain_size_e2)
{
    return std::make_shared<encoding::EncodingCombinerImplementation<u64, u64, u64>>(input_domain_size_e1, output_domain_size_e1, output_domain_size_e2);
}



#endif
 */