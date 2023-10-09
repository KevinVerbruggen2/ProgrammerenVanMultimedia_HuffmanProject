#ifndef TREE_ENCODING_H
#define TREE_ENCODING_H
#include "util.h"
#include "data/binary-tree.h"
#include "io/binary-io.h"
#include "io/streams.h"

namespace encoding
{
    void encode_tree(const data::Node<Datum>& root, unsigned bits_per_datum, std::unique_ptr<io::OutputStream> output);
    
    std::unique_ptr<data::Node<Datum>> getNode(unsigned bits_per_datum, std::unique_ptr<io::InputStream>& input);
    
    data::Node<Datum> decode_tree(unsigned bits_per_datum, std::unique_ptr<io::InputStream> input);
}

#endif
