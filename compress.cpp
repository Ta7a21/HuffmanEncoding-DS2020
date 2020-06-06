#include <bits/stdc++.h>
#include <fstream>
#include "ReadWritePGM.hpp"
#include "constructHuff.hpp"
#include "Serialization_Deserialization.hpp"
#include "decode.hpp"


int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        int width, height;
        std::map<int, std::string> encTable; //Codes table
        std::uint8_t *imgData = Readpgm(width, height, argv[1]); //Stroing pixels data after reading the image
        std::vector<std::pair<int, int>> FrequencyTable = constructFrqTable(imgData, width, height); //Constructing frequency table
        std::priority_queue<node> HuffmanTree = preHuff(FrequencyTable); //Constructing huffman tree
        constructTree(HuffmanTree);
        node *parent = new node{HuffmanTree.top().pixel, HuffmanTree.top().value, HuffmanTree.top().left, HuffmanTree.top().right};
        encodingTable("", encTable, parent); //Constructing codes table
        serialize(encTable, imgData, width, height, FrequencyTable); //Serialization
    }
    else
    {
        std::string encodedFile = argv[1];
        std::string encodedFrqtable = argv[3];
        int width, height;
        std::vector<std::pair<int, int>> FrequencyTable(256);
        std::string bits = "";
        std::map<int, std::string> encTable; //codes table
        std::map<std::string, int> decTable; //decoding table
        deserialize(encodedFile, encodedFrqtable, FrequencyTable, bits, width, height); //Deserialization
        std::priority_queue<node> HuffmanTree = preHuff(FrequencyTable); //Reconstructing huffman tree
        constructTree(HuffmanTree);
        node *parent = new node{HuffmanTree.top().pixel, HuffmanTree.top().value, HuffmanTree.top().left, HuffmanTree.top().right};
        encodingTable("", encTable, parent); //Reconstructing codes table
        decodingTable(encTable, decTable); //Constructing decoding table
        std::uint8_t *imgData = decode(bits, decTable, width, height, encTable[0]); //Retrieving image data
        Writepgm(imgData, width, height, "Retrieved.pgm"); //Writing image data
    }
}