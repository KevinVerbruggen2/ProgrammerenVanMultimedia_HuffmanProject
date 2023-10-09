#include "tree-encoding.h"

namespace encoding
{
    void encode_tree(const data::Node<Datum>& root, unsigned bits_per_datum, std::unique_ptr<io::OutputStream> output)
    {
        // check if root is a leaf
        data::Node<Datum> current_node = root;

        if (const data::Leaf<Datum>* leaf = dynamic_cast<const data::Leaf<Datum>*>(&root))
        {
            // Root is a leaf
            io::write_bits(0, 1, *output);
            io::write_bits(*leaf->getValue(), bits_per_datum, *output);
        }
        else if (const data::Branch<Datum>* branch = dynamic_cast<const data::Branch<Datum>*>(&root))
        {
            // Root is a branch
            io::write_bits(1, 1, *output);

            if (branch->getLeftChild() != NULL)
            {
                encode_tree(*branch->getLeftChild(), bits_per_datum, std::move(output));
            }

            if (branch->getRightChild() != NULL)
            {
                encode_tree(*branch->getRightChild(), bits_per_datum, std::move(output));
            }
        }
    }

    std::unique_ptr<data::Node<Datum>> getNode(unsigned bits_per_datum, std::unique_ptr<io::InputStream>& input)
    {
        if (input->end_reached())
        {
            return nullptr;
        }

        Datum datum = io::read_bits(1 , *input);
        
        if (datum == 1)
        {
            return std::make_unique<data::Branch<Datum>>(getNode(bits_per_datum, input), getNode(bits_per_datum, input));
        }
        else if (datum == 0)
        {
            Datum value = io::read_bits(bits_per_datum, *input);
            return std::make_unique<data::Leaf<Datum>>(value);
        }
    }
    
    data::Node<Datum> decode_tree(unsigned bits_per_datum, std::unique_ptr<io::InputStream> input)
    {
        return *getNode(bits_per_datum, input);
    }
}
