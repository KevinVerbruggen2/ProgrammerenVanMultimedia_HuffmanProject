#include "catch.hpp"
#include "data/binary-tree.h"
#include "encoding/huffman/tree-encoding.h"
#include "io/memory-buffer.h"
#include "io/streams.h"

TEST_CASE("Tree Encoding Tests", "[tree-encoding]")
{
    SECTION("Encode and Decode Tree") {
        //ints for tree
        Datum value1 = 2;
        Datum value2 = 2;
        Datum value3 = 3;
        Datum value4 = 4;
        Datum value5 = 5;
        
        std::unique_ptr<data::Node<Datum>> leaf1 = std::make_unique<data::Leaf<Datum>>(value1);
        std::unique_ptr<data::Node<Datum>> leaf2 = std::make_unique<data::Leaf<Datum>>(value2);
        std::unique_ptr<data::Node<Datum>> leaf3 = std::make_unique<data::Leaf<Datum>>(value3);
        std::unique_ptr<data::Node<Datum>> leaf4 = std::make_unique<data::Leaf<Datum>>(value4);
        std::unique_ptr<data::Node<Datum>> leaf5 = std::make_unique<data::Leaf<Datum>>(value5);

        //TEST CASE 1: 1 leave encoding
        //create output stream
        /**/
        auto data_receiver = std::make_shared<std::vector<Datum>>();
        std::unique_ptr<io::OutputStream> output_stream = io::create_memory_output_stream(data_receiver);
        
        //test leaf
        encoding::encode_tree(*leaf1, 5, std::move(output_stream));
        
        //print all bits of the output stream
        std::cout << "t1: Leaf 1: ";
        for (std::size_t i = 0; i < data_receiver->size(); ++i)
        {
            std::cout << data_receiver->at(i) << " ";
        }

        //TEST CASE 2: 1 leave encoding & decoding
        constexpr u64 bits_per_datum_test1 = 5;
        std::unique_ptr<io::MemoryBuffer<bits_per_datum_test1>> buffer = std::make_unique<io::MemoryBuffer<bits_per_datum_test1>>();
        std::unique_ptr<io::OutputStream> buffer_output = io::create_memory_output_stream(buffer->data());
        
        //test leaf
        encoding::encode_tree(*leaf1, 5, std::move(buffer_output));
        
        // create input stream
        std::unique_ptr<io::InputStream> buffer_input = io::create_memory_input_stream(buffer->data());

        //decode tree
        data::Node<Datum> decoded_tree = encoding::decode_tree(bits_per_datum_test1, std::move(buffer_input));

        //cast to brach
        const auto& decoded_branch = dynamic_cast<const data::Branch<Datum>&>(decoded_tree);

        // Check if the decoded tree is a leaf

        
        
        //
        // Check if the decoded tree is the same as the original tree
        // const auto& decodedBranch = dynamic_cast<const data::Branch<int>&>(decodedTree);
        // const auto& decodedLeaf1 = dynamic_cast<const data::Leaf<int>&>(*decodedBranch.getLeftChild());
        // const auto& decodedLeaf2 = dynamic_cast<const data::Leaf<int>&>(*decodedBranch.getRightChild());
        //
        // REQUIRE(*decodedLeaf1.getValue() == 1);
        // REQUIRE(*decodedLeaf2.getValue() == 2);
    }
}

