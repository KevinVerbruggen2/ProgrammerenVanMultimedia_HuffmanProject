#ifndef EOF_ENCODING_CPP_H
#define EOF_ENCODING_CPP_H
#include "Encoding.h"
#include "EncodingImplementation.h"

std::shared_ptr<EncodingImplementation> create_eof_implementation(u64 domain_size);


namespace encoding
{
    template<u64 N>
    Encoding<N, N + 1> eof_encoding()
    {
        //make a new Encoding with the create_eof_implementation
        return Encoding<N, N + 1>(create_eof_implementation(N));
    }    
}



#endif
