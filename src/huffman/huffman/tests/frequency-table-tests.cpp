#include "data/frequency-table.h"
#ifdef TEST_BUILD

#include "catch.hpp"
#include "data/frequency-table.h"

TEST_CASE("FrequencyTable - Increment and Access", "[FrequencyTable]") {
    data::FrequencyTable<int> freqTable;

    SECTION("Increment values") {
        freqTable.increment(1);
        freqTable.increment(2);
        freqTable.increment(1);
        freqTable.increment(3);
        freqTable.increment(2);
        freqTable.increment(2);

        REQUIRE(freqTable[1] == 2);
        REQUIRE(freqTable[2] == 3);
        REQUIRE(freqTable[3] == 1);
        REQUIRE(freqTable[4] == 0);
    }

    SECTION("Access non-existing values") {
        REQUIRE(freqTable[1] == 0);
        REQUIRE(freqTable[2] == 0);
        REQUIRE(freqTable[3] == 0);
        REQUIRE(freqTable[4] == 0);
    }
}

// testing the size function
TEST_CASE("FrequencyTable - Values", "[FrequencyTable]") {
    data::FrequencyTable<char> freqTable;

    SECTION("Empty frequency table") {
        std::vector<char> values = freqTable.values();
        REQUIRE(values.empty());
    }

    SECTION("Non-empty frequency table") {
        freqTable.increment('a');
        freqTable.increment('b');
        freqTable.increment('a');
        freqTable.increment('c');

        std::vector<char> values = freqTable.values();
        REQUIRE(values.size() == 3);
        REQUIRE(std::count(values.begin(), values.end(), 'a') == 1);
        REQUIRE(std::count(values.begin(), values.end(), 'b') == 1);
        REQUIRE(std::count(values.begin(), values.end(), 'c') == 1);
    }
}

// testing the count_frequencies function
TEST_CASE("count_frequencies", "[FrequencyTable]") {
    SECTION("Count frequencies of integers") {
        std::vector<int> values = {1, 2, 1, 3, 2, 2, 4, 1};
        data::FrequencyTable<int> freqTable = data::count_frequencies(values);

        REQUIRE(freqTable[1] == 3);
        REQUIRE(freqTable[2] == 3);
        REQUIRE(freqTable[3] == 1);
        REQUIRE(freqTable[4] == 1);
        REQUIRE(freqTable[5] == 0);
    }

    SECTION("Count frequencies of characters") {
        std::vector<char> values = {'a', 'b', 'a', 'c', 'b', 'b'};
        data::FrequencyTable<char> freqTable = data::count_frequencies(values);

        REQUIRE(freqTable['a'] == 2);
        REQUIRE(freqTable['b'] == 3);
        REQUIRE(freqTable['c'] == 1);
        REQUIRE(freqTable['d'] == 0);
    }
}

#endif
