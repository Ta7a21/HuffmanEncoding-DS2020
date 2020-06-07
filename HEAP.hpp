#ifndef HEAP_HPP
#define HEAP_HPP

#include <vector>

template <typename T>

class Heap
{
public:
    size_t size()
    {
        return data.size();
    }

    T top()
    {
        return data.front();
    }

    void insert(T node)
    {
        data.push_back(node);
        auto child = data.size() - 1;
        siftUp(child);
    }

    void pop()
    {
        std::swap(data[data.size() - 1], data[0]);
        data.pop_back();
        siftDown(0);
    }

private:
    void siftDown(size_t node)
    {
        size_t left = leftChild(node);
        size_t right = rightChild(node);
        size_t length = size();
        size_t minimum = node;

        if (left < length && data[left] < data[minimum])
            minimum = left;

        if (right < length && data[right] < data[minimum])
            minimum = right;

        if (minimum != node)
        {
            std::swap(data[minimum], data[node]);
            siftDown(minimum);
        }
    }

    void siftUp(size_t node)
    {
        auto parentNode = parent(node);
        if (data[parentNode] > data[node])
        {
            std::swap(data[parentNode], data[node]);
            siftUp(parentNode);
        }
    }

    size_t leftChild(size_t parent)
    {
        return parent * 2 + 1;
    }

    size_t rightChild(size_t parent)
    {
        return parent * 2 + 2;
    }

    size_t parent(size_t child)
    {
        return child / 2;
    }

private:
    std::vector<T> data;
};

#endif //HEAP_HPP
