#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include <functional>
#include <memory>

namespace data {

    // Declaration of Node class
    template<typename T>
    class Node {
    public:
        // Virtual destructor with an empty body
        virtual ~Node() {}

        // TODO: Add Node member functions here
    };

    // Declaration of Branch class
    template<typename T>
    class Branch : public Node<T> {
    private:
        std::unique_ptr<Node<T>> left_child;  // Pointer to the left child
        std::unique_ptr<Node<T>> right_child; // Pointer to the right child
        public:
        // Constructor to initialize the left and right child
        Branch(std::unique_ptr<Node<T>> left, std::unique_ptr<Node<T>> right)
            : left_child(std::move(left)), right_child(std::move(right)) {}

        // Accessor method to get the left child
        const std::unique_ptr<Node<T>>& getLeftChild() const {
            return left_child;
        }

        // Accessor method to get the right child
        const std::unique_ptr<Node<T>>& getRightChild() const {
            return right_child;
        }

        // TODO: Add Branch member functions here
    };
    


    // Declaration of Leaf class
    template<typename T>
    class Leaf : public Node<T> {
    private:
        const T value;  // Value associated with the leaf

    public:
        // Constructor to initialize the data field
        Leaf(const T value)
            : value(value) {}

        // Accessor method to retrieve the data associated with the leaf
        
        const T * getValue() const{
            return &value;
        }

        // TODO: Add Leaf member functions here
    };

    template<typename IN, typename OUT>
    std::unique_ptr<Node<OUT>> map(const Node<IN>& tree, std::function<OUT(const IN&)> function)
    {
        if (const Leaf<IN>* leaf = dynamic_cast<const Leaf<IN>*>(&tree))
        {
            // Tree is a leaf
            OUT new_data = function(leaf->getValue());
            return std::make_unique<Leaf<OUT>>(new_data);
        }
        else if (const Branch<IN>* branch = dynamic_cast<const Branch<IN>*>(&tree))
        {
            // Tree is a branch
            std::unique_ptr<Node<OUT>> new_left_child = map(*(branch->getLeftChild()), function);
            std::unique_ptr<Node<OUT>> new_right_child = map(*(branch->getRightChild()), function);
            return std::make_unique<Branch<OUT>>(std::move(new_left_child), std::move(new_right_child));
        }
        else
        {
            // Unknown tree type
            // throw std::runtime_error("Unknown tree type");
        }
    }

    
} // namespace data

#endif // BINARY_TREE_H
