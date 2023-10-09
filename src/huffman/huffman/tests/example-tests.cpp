
#include "io/memory-buffer.h"
#ifdef TEST_BUILD

#include "catch.hpp"


TEST_CASE("Passing test")
{
    // auto original_data = std::make_shared<std::vector<Datum>>();
    // original_data->push_back(0);
    // original_data->push_back(1);
    // original_data->push_back(2);
    // original_data->push_back(3);
    //
    // auto input_stream = io::create_memory_input_stream(original_data);
    //
    // auto data_receiver = std::make_shared<std::vector<Datum>>();
    // auto output_stream = io::create_memory_output_stream(data_receiver);
    //
    // encoding::Encoding<10, 20> encoding;
    // encoding.encode(input_stream, output_stream);
    // encoding->encode(input_stream, output_stream);

}


//TEST_CASE("Failing test")
//{
//    REQUIRE(1 == 2);
//}


#endif
