#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include "RW_PGM.hpp"
#include "ENCODING.hpp"
#include "DE_SERIALIZATION.hpp"
#include "DECODING.hpp"
#include "HEAP.hpp"

void compress(const uint8_t *imgData, const int width, const int height, const int maxValue, std::vector<std::pair<int, int>> &FreqTable, std::map<int, std::string> &encTable)
{
    constructFrqTable(imgData, width, height, FreqTable); //Constructing frequency table

    constructEncodingTable(FreqTable, encTable);

    serialize(encTable, imgData, width, height, maxValue, FreqTable); //Serialization

    std::cout << "Image compressed successfully" << std::endl;
}

void decompress(const std::string encfile, const std::string encfrq, std::string &bits, int &width, int &height, int &maxValue,std::vector<std::pair<int, int>> &Freqtable, std::map<int, std::string> &enctable, std::map<std::string, int> &dectable)
{
    deserialize(encfile, encfrq, Freqtable, bits, width, height, maxValue); //Deserialization

    constructEncodingTable(Freqtable, enctable);

    decodingTable(enctable, dectable); //Constructing decoding table
}

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        int width, height, maxValue;
        std::map<int, std::string> encTable; //Codes table
        std::vector<std::pair<int, int>> FrequencyTable(256);

        uint8_t *imgData = read_pgm_image(width, height, maxValue, argv[1]); //Stroing pixels data after reading the image

        compress(imgData, width, height, maxValue, FrequencyTable, encTable);
    }
    else
    {
        int width, height, maxValue;
        std::string encodedFile = argv[1], encodedFrqtable = argv[3], bits = "";
        std::vector<std::pair<int, int>> FrequencyTable(256);
        std::map<int, std::string> encTable; //codes table
        std::map<std::string, int> decTable; //decoding table

        decompress(encodedFile,encodedFrqtable,bits,width,height,maxValue,FrequencyTable,encTable,decTable);

        uint8_t *imgData = decode(bits, decTable, width, height, encTable[0]); //Retrieving image data

        write_pgm_image(imgData, width, height, maxValue, "Retrieved.pgm"); //Writing image data

        std::cout<<"Files decompressed successfully"<<std::endl;
    }
}