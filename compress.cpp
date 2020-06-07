#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <fstream>
#include "RW_PGM.hpp"
#include "ENCODING.hpp"
#include "DE_SERIALIZATION.hpp"
#include "DECODING.hpp"

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        int width, height, maxValue;
        std::map<int, std::string> encTable;                                                         //Codes table
        uint8_t *imgData = read_pgm_image(width, height, maxValue, argv[1]);                         //Stroing pixels data after reading the image
        std::vector<std::pair<int, int>> FrequencyTable = constructFrqTable(imgData, width, height); //Constructing frequency table
        std::priority_queue<node> HuffmanTree = preHuff(FrequencyTable);                             //Constructing huffman tree
        constructTree(HuffmanTree);
        node *parent = new node{HuffmanTree.top().pixel, HuffmanTree.top().value, HuffmanTree.top().left, HuffmanTree.top().right};
        encodingTable("", encTable, parent);                                   //Constructing codes table
        serialize(encTable, imgData, width, height, maxValue, FrequencyTable); //Serialization
    }
    else
    {
        std::string encodedFile = argv[1];
        std::string encodedFrqtable = argv[3];
        int width, height, maxValue;
        std::vector<std::pair<int, int>> FrequencyTable(256);
        std::string bits = "";
        std::map<int, std::string> encTable;                                                      //codes table
        std::map<std::string, int> decTable;                                                      //decoding table
        deserialize(encodedFile, encodedFrqtable, FrequencyTable, bits, width, height, maxValue); //Deserialization
        std::priority_queue<node> HuffmanTree = preHuff(FrequencyTable);                          //Reconstructing huffman tree
        constructTree(HuffmanTree);
        node *parent = new node{HuffmanTree.top().pixel, HuffmanTree.top().value, HuffmanTree.top().left, HuffmanTree.top().right};
        encodingTable("", encTable, parent);                                   //Reconstructing codes table
        decodingTable(encTable, decTable);                                     //Constructing decoding table
        uint8_t *imgData = decode(bits, decTable, width, height, encTable[0]); //Retrieving image data
        write_pgm_image(imgData, width, height, maxValue, "Retrieved.pgm");    //Writing image data
    }
}