#include "catch.hpp"
#include "encoding/EncodingImplementation.h"
#include "encoding/eof-encoding.h"
#include "encoding/encoding-combiner.h"
#include "io/memory-buffer.h"
#ifdef TEST_BUILD


TEST_CASE("Encoding Combiner Tests", "[Encoding Combiner]")
{
    auto original_data = std::make_shared<std::vector<Datum>>();
    original_data->push_back(0);
    original_data->push_back(1);
    original_data->push_back(2);
    original_data->push_back(3);
    original_data->push_back(4);
    original_data->push_back(5);
    original_data->push_back(6);
    original_data->push_back(7);
    original_data->push_back(8);

    std::shared_ptr<io::InputStream> input_stream = io::create_memory_input_stream(original_data);

    auto data_receiver = std::make_shared<std::vector<Datum>>();
    std::shared_ptr<io::OutputStream> output_stream = io::create_memory_output_stream(data_receiver);
    
    // Create the encodings
    std::shared_ptr<EncodingImplementation> eof_implementation1 = create_eof_implementation(9);
    std::shared_ptr<EncodingImplementation> eof_implementation2 = create_eof_implementation(10);
    std::shared_ptr<EncodingImplementation> eof_implementation3 = create_eof_implementation(10);
    std::shared_ptr<EncodingImplementation> eof_implementation4 = create_eof_implementation(10);
    

    // create the encoding combiner
    // std::shared_ptr<EncodingImplementation> encoding_combiner = eof_implementation1 | eof_implementation2;
    std::shared_ptr<EncodingImplementation> encoding_combiner = operator|<9, 9, 10>(eof_implementation1, eof_implementation2);
    encoding_combiner = operator|<9, 9, 10>(encoding_combiner, eof_implementation3);
    encoding_combiner = operator|<9, 9, 10>(encoding_combiner, eof_implementation4);
    

    // Create encoding using the EOF implementation
    encoding::Encoding<2, 2> encoding(encoding_combiner);
    
    // Encode the input stream
    encoding.encode(*input_stream, *output_stream);
    
    // Check the size of the encoded data
    assert(data_receiver->size() == original_data->size() + 4);
    
    // Access the internal buffer of the data receiver
    Datum* encoded_data = data_receiver->data();
    
    // Verify the encoded data
    for (std::size_t i = 0; i < original_data->size(); ++i)
    {
        assert(encoded_data[i] == original_data->at(i));
    }

    //print size of original data
    // std::cout << "Size of original data: " << original_data->size() << std::endl;
    
    //print the size of the encoded data
    // std::cout << "Size of encoded data: " << data_receiver->size() << std::endl;
    
    // Check the last element of the encoded data
    REQUIRE(original_data->size() + 4 == data_receiver->size());

    
}

//decoder test
TEST_CASE("decoder tests")
{
    auto original_data = std::make_shared<std::vector<Datum>>();
    original_data->push_back(0);
    original_data->push_back(1);
    original_data->push_back(2);
    original_data->push_back(3);
    original_data->push_back(4);
    original_data->push_back(5);
    original_data->push_back(char(6));
    original_data->push_back(char(7));

    std::shared_ptr<io::InputStream> input_stream = io::create_memory_input_stream(original_data);

    auto data_receiver = std::make_shared<std::vector<Datum>>();
    std::shared_ptr<io::OutputStream> output_stream = io::create_memory_output_stream(data_receiver);
    
    // Create the EOF implementation
    std::shared_ptr<EncodingImplementation> eof_implementation1 = create_eof_implementation(7);
    std::shared_ptr<EncodingImplementation> eof_implementation2 = create_eof_implementation(6);

    // create the encoding combiner
    std::shared_ptr<EncodingImplementation> encoding_combiner =operator|<9, 9, 10>(eof_implementation1, eof_implementation2);
    
    // Create encoding using the EOF implementation
    encoding::Encoding<4, 4> encoding(encoding_combiner);
    
    // Decode the input stream
    encoding.decode(*input_stream, *output_stream);
    
    // Access the internal buffer of the data receiver
    Datum* encoded_data = data_receiver->data();
    
    //print size of original data
    // std::cout << "Size of original data: " << original_data->size() << std::endl;
    
    //print the size of the encoded data
    // std::cout << "Size of decoded data: " << data_receiver->size() << std::endl;
    
    REQUIRE(original_data->size() == data_receiver->size() + 2);
}



#endif // TEST_BUILD
