#ifndef ENCODING_HPP
#define ENCODING_HPP

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include "HEAP.hpp"

struct node
{
    int pixel;
    long long value;
    node *left;
    node *right;
    bool operator<(const node &rhs) const
    {
        return value < rhs.value;
    };
    bool operator>(const node &rhs) const
    {
        return value > rhs.value;
    };
};

void constructFrqTable(const uint8_t *img, const int width, const int height,std::vector<std::pair<int, int>> &FreqTable)
{
    std::map<int, int> mapHuff;

    for (int i = 0; i < width * height; i++)
        mapHuff[int(img[i])]++;
    for (int i = 0; i < 256; i++)
    {
        if (!mapHuff[i])
        {
            FreqTable[i].first = i;
            FreqTable[i].second = 0;
        }
        else
        {
            FreqTable[i].first = i;
            FreqTable[i].second = mapHuff[i];
        }
    }
    sort(FreqTable.begin(), FreqTable.end());
}

Heap<node> preHuff(const std::vector<std::pair<int, int>> freqtable)
{
    Heap<node> preTree;
    for (int i = 0; i < freqtable.size(); i++)
        preTree.insert({freqtable[i].first, freqtable[i].second, nullptr, nullptr});
    return preTree;
}

void constructTree(Heap<node> &frqtable)
{
    while (frqtable.size() > 1)
    {
        node *frst = new node{frqtable.top().pixel, frqtable.top().value, frqtable.top().left, frqtable.top().right};
        frqtable.pop();
        node *scnd = new node{frqtable.top().pixel, frqtable.top().value, frqtable.top().left, frqtable.top().right};
        frqtable.pop();
        node *newNode = new node{-1, frst->value + scnd->value, frst, scnd};
        frqtable.insert({newNode->pixel, newNode->value, newNode->left, newNode->right});
    }
}

void encodingTable(std::string code, std::map<int, std::string> &encTable, const node *parent)
{
    if (parent->left != nullptr)
        encodingTable(code + '0', encTable, parent->left);
    if (parent->right != nullptr)
        encodingTable(code + '1', encTable, parent->right);
    if (parent->pixel != -1)
        encTable[parent->pixel] = code;
}

void constructEncodingTable(std::vector<std::pair<int, int>> &FreqTable, std::map<int, std::string> &encTable)
{
    Heap<node> HuffmanTree = preHuff(FreqTable);
    constructTree(HuffmanTree);
    node *parent = new node{HuffmanTree.top().pixel, HuffmanTree.top().value, HuffmanTree.top().left, HuffmanTree.top().right};
    encodingTable("", encTable, parent); //Constructing codes table
}

#endif //ENCODING_HPP