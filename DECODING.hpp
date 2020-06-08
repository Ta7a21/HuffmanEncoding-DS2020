#ifndef DECODING_HPP
#define DECODING_HPP

#include <iostream>
#include <map>
#include <vector>
#include "HEAP.hpp"

void decodingTable(const std::map<int, std::string> enctable, std::map<std::string, int> &dectable)
{
    //Constructing an inverse table for the coded table
    for (auto it = enctable.begin(); it != enctable.end(); it++)
        dectable[it->second] = it->first;
}

uint8_t *decode(const std::string bits, std::map<std::string, int> &dectable, const int width, const int height, const std::string zero)
{
    int j = 0;
    std::string temp = "";
    uint8_t *imgData = new uint8_t[width * height];

    //Retrieving the original form of the data
    for (int i = 0; i < bits.size(); i++)
    {
        temp += bits[i];

        if (dectable[temp] != 0 || temp == zero)
        {
            imgData[j] = dectable[temp];

            j++;

            temp = "";
        }
    }
    
    return imgData;
}

#endif //DECODING_HPP