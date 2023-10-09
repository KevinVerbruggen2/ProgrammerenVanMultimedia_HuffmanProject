#include "catch.hpp"
#include "util.h"
#include "encoding/bit-grouper.h"
#include "io/memory-buffer.h"
#ifdef TEST_BUILD


namespace io
{
    struct InputStream;
}

TEST_CASE("Bit Grouper encoding test")
{

    auto original_data = std::make_shared<std::vector<Datum>>();
    original_data->push_back(0);
    original_data->push_back(1);
    original_data->push_back(2);
    original_data->push_back(3);

    
    std::shared_ptr<io::InputStream> input_stream = io::create_memory_input_stream(original_data);
    
    auto data_receiver = std::make_shared<std::vector<Datum>>();
    std::shared_ptr<io::OutputStream> output_stream = io::create_memory_output_stream(data_receiver);
    
    // Create the bit grouper implementation
    std::shared_ptr<EncodingImplementation> bit_grouper_implementation = create_bit_grouper_implementation(8);
    
    // Create encoding using the bit grouper implementation
    encoding::Encoding<2, 3> encoding(bit_grouper_implementation);
    
    // Encode the input stream
    encoding.encode(*input_stream, *output_stream);
    

    std::cout << std::endl;
    std::cout << std::endl;

    // print the original data and data receiver
    // std::cout << "Original data: ";
    // for (std::size_t i = 0; i < original_data->size(); ++i)
    // {
    //     std::cout << original_data->at(i) << " ";
    // }
    //
    // //print next line
    // std::cout << std::endl;
    // std::cout << std::endl;
    //
    //
    // std::cout << "data receiver: ";
    // for (std::size_t i = 0; i < data_receiver->size(); ++i)
    // {
    //     std::cout << data_receiver->at(i) << " ";
    // }
    //
    // std::cout << std::endl;
    // std::cout << std::endl;

    
}


#endif