#ifndef CONSTRUCTHUFF_HPP
#define CONSTRUCTHUFF_HPP

#include <iostream>
#include <map>
#include <vector>
#include <queue>

struct node
{
    int pixel;
    long long value;
    node *left;
    node *right;
    bool operator<(const node &x) const
    {
        return value > x.value;
    }
};

std::vector<std::pair<int, int>> constructFrqTable(uint8_t *img, const int width, const int height)
{
    std::map<int, int> mapHuff;
    for (int i = 0; i < width * height; i++)
        mapHuff[int(img[i])]++;
    std::vector<std::pair<int, int>> imgHuff(256);
    int i = 0;
    for (int i = 0; i < 256; i++)
    {
        if (!mapHuff[i])
        {
            imgHuff[i].first = i;
            imgHuff[i].second = 0;
        }
        else
        {
            imgHuff[i].first = i;
            imgHuff[i].second = mapHuff[i];
        }
    }
    sort(imgHuff.begin(), imgHuff.end());
    return imgHuff;
}

std::priority_queue<node> preHuff(const std::vector<std::pair<int, int>> freqtable)
{
    std::priority_queue<node> preTree;
    for (int i = 0; i < freqtable.size(); i++)
    {
        preTree.push({freqtable[i].first, freqtable[i].second, nullptr, nullptr});
    }
    return preTree;
}

void constructTree(std::priority_queue<node> &frqtable)
{
    while (frqtable.size() > 1)
    {
        node *frst = new node{frqtable.top().pixel, frqtable.top().value, frqtable.top().left, frqtable.top().right};
        frqtable.pop();
        node *scnd = new node{frqtable.top().pixel, frqtable.top().value, frqtable.top().left, frqtable.top().right};
        frqtable.pop();
        node *newNode = new node{-1, frst->value + scnd->value, frst, scnd};
        frqtable.push({newNode->pixel, newNode->value, newNode->left, newNode->right});
    }
}

void encodingTable(std::string code, std::map<int, std::string> &encTable, const node *parent)
{
    if (parent->left != nullptr)
    {
        encodingTable(code + '0', encTable, parent->left);
    }
    if (parent->right != nullptr)
    {
        encodingTable(code + '1', encTable, parent->right);
    }
    if (parent->pixel != -1)
    {
        encTable[parent->pixel] = code;
    }
}
#endif //CONSTRUCTHUFF_HPP