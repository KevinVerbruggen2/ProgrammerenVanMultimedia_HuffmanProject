#include "catch.hpp"
#include "io/memory-buffer.h"
#include "io/binary-io.h"   


void check(uint64_t n, unsigned nbits)
{
    io::MemoryBuffer<2> buffer;
    auto input = buffer.source()->create_input_stream();
    auto output = buffer.destination()->create_output_stream();
    io::write_bits(n, nbits, *output);
    auto result = io::read_bits(nbits, *input);

    REQUIRE(n == result);
}


TEST_CASE("Binary IO - read_bits and write_bits", "[BinaryIO]")
{
    SECTION("Read and write 8 bits")
    {
        check(0x5A, 8);
        check(0x00, 8);
        check(0xFF, 8);
    }

    SECTION("Read and write 16 bits")
    {
        check(0x1234, 16);
        check(0x0000, 16);
        check(0xFFFF, 16);
    }

    SECTION("Read and write 32 bits")
    {
        check(0x12345678, 32);
        check(0x00000000, 32);
        check(0xFFFFFFFF, 32);
    }

    SECTION("Read and write 64 bits")
    {
        check(0x123456789ABCDEF0ULL, 64);
        check(0x0000000000000000ULL, 64);
        check(0xFFFFFFFFFFFFFFFFULL, 64);
    }    
}





