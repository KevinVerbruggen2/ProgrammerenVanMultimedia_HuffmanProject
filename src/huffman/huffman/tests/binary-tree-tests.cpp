#include <iostream>

#include "data/binary-tree.h"
#ifdef TEST_BUILD

#include "catch.hpp"


TEST_CASE("Binary Tree Tests", "[binary-tree]") {
    SECTION("Leaf Test") {
        int value = 42;
        data::Leaf<int> leaf(value);

        REQUIRE(*leaf.getValue() == value);
    }

    SECTION("Branch Test") {
        int leftValue = 10;
        int rightValue = 20;
        data::Leaf<int> leftLeaf(leftValue);
        data::Leaf<int> rightLeaf(rightValue);

        std::unique_ptr<data::Node<int>> leftNode = std::make_unique<data::Leaf<int>>(leftLeaf);
        std::unique_ptr<data::Node<int>> rightNode = std::make_unique<data::Leaf<int>>(rightLeaf);

        data::Branch<int> branch(std::move(leftNode), std::move(rightNode));
        
        // cast the left child to a Leaf
        const auto& leftLeafChild = dynamic_cast<const data::Leaf<int>&>(*branch.getLeftChild());
        const auto& rightLeafChild = dynamic_cast<const data::Leaf<int>&>(*branch.getRightChild());

        // print the data of the left child
        REQUIRE(*leftLeafChild.getValue() == leftValue);
        REQUIRE(*rightLeafChild.getValue() == rightValue);
    }

    SECTION("Map Test") {
        int value = 5;
        data::Leaf<int> leaf(value);

        // std::cout << "Value leaf: " << leaf.getValue() << std::endl;

        std::function<std::string(const int&)> function = [](const int& val) {
            return "Value: " + std::to_string(val);
        };

        std::string strValue = function(value);
        //
        // std::cout << "Value function: " << strValue << std::endl;
        //
        // std::cout << "map test1" << std::endl;

        // TODO: Fix this

        /*
        std::unique_ptr<data::Node<std::string>> mapped = map(std::move(leaf), function);
        // std::unique_ptr<data::Node<std::string>> mappedTree = map(leaf, function);
        // mappedTree = std::move(mapped);

        std::cout << "map test2" << std::endl;

        // cast mappedTree to a Leaf
        const auto& mappedLeaf = dynamic_cast<const data::Leaf<std::string>&>(*mapped);

        // std::cout << "map test3" << std::endl;

        // std::cout << mappedLeaf.getValue() << std::endl;

        // REQUIRE(mappedTree->getData() == "Value: 5");
        */
    }
}

#endif