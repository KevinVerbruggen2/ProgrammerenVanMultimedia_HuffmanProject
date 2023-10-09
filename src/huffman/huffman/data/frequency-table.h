
#ifndef FREQUENCY_TABLE_H
#define FREQUENCY_TABLE_H

#include <map>
#include <vector>

namespace data {

    template <typename T>
    class FrequencyTable {
    private:
        std::map<T, int> frequencyData;

    public:
        void increment(const T x) {
            frequencyData[x]++;
        }

        int operator[](const T& x) const {
            auto it = frequencyData.find(x);
            if (it != frequencyData.end()) {
                return it->second;
            }
            return 0;
        }

        std::vector<T> values() const {
            std::vector<T> valueList;
            for (const auto& pair : frequencyData) {
                valueList.push_back(pair.first);
            }
            return valueList;
        }
    };

    template <typename T>
    FrequencyTable<T> count_frequencies(const std::vector<T>& values) {
        FrequencyTable<T> freqTable;
        for (const T& value : values) {
            freqTable.increment(value);
        }
        return freqTable;
    }

} // namespace data

#endif // FREQUENCY_TABLE_H
