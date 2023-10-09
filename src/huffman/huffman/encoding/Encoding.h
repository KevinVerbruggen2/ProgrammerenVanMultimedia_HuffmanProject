#ifndef ENCODING_H
#define ENCODING_H
#include "EncodingImplementation.h"
#include "util.h"
#include "io/data-endpoints.h"

namespace encoding
{
    template <u64 IN, u64 OUT>
    class Encoding
    {
    private:
        std::shared_ptr<EncodingImplementation> implementation;
    public:
        Encoding(std::shared_ptr<EncodingImplementation> impl) : implementation(std::move(impl))
        {
        }

        void encode(io::InputStream& input, io::OutputStream& output)
        {
            implementation->encode(input, output);
        }

        void decode(io::InputStream& input, io::OutputStream& output)
        {
            implementation->decode(input, output);
        }

        // // Overloaded -> operator (non-const version)
        // EncodingImplementation* operator->() {
        //     return &implementation;
        // }
        //
        // // Overloaded -> operator (const version)
        // const EncodingImplementation* operator->() const {
        //     return &implementation;
        // }

        // Overloaded -> operator (non-const version)
        EncodingImplementation* operator->() {
            return implementation.get();
        }

        // Overloaded -> operator (const version)
        const EncodingImplementation* operator->() const {
            return implementation.get();
        }
        
    };

    template <u64 IN, u64 OUT>
    void encode(io::DataSource<IN> source,  Encoding<IN, OUT> encoding, io::DataDestination<OUT> destination)
    {
        auto input_stream = source->create_input_stream();
        auto output_stream = destination->create_output_stream();
        encoding.encode(input_stream, output_stream);
    }

    template <u64 IN, u64 OUT>
    void decode(io::DataSource<IN> source,  Encoding<IN, OUT> encoding, io::DataDestination<OUT> destination)
    {
        auto input_stream = source->create_input_stream();
        auto output_stream = destination->create_output_stream();
        encoding.decode(input_stream, output_stream);
    }
    
}

#endif

