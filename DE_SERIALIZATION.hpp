#ifndef DE_SERIALIZATION_HPP
#define DE_SERIALIZATION_HPP

#include <iostream>
#include <map>
#include <vector>
#include "HEAP.hpp"
#include <bitset>
#include <sstream>
#include <fstream>

void serialize(std::map<int, std::string> &encTable, const uint8_t *img, const int width, const int height, const int maxValue, const std::vector<std::pair<int, int>> frqtable)
{
    std::string bits = ""; //For storing image codes in one string
    std::string code = ""; //For dividing the bits string when writing the encoded file

    //writing our coded pixels in the string
    for (int i = 0; i < width * height; i++)
        bits += encTable[int(img[i])];

    //calculating the padding bits to store every 8-bits in a single char
    int paddingBits = 8 - (bits.size() % 8);

    std::ofstream outenc("image.enc"); //Creating file

    //Serializing the encoded image
    std::bitset<32> w(width);
    std::string codeW = w.to_string();
    for (int i = 0; i < codeW.size(); i++)
    {
        code += codeW[i];
        if (code.size() % 8 == 0)
        {
            int codeSer = stoi(code, 0, 2);
            char temp = (char)codeSer;
            outenc << temp;
            code = "";
        }
    }
    code = "";
    std::bitset<32> h(height);
    std::string codeH = h.to_string();
    for (int i = 0; i < codeH.size(); i++)
    {
        code += codeH[i];
        if (code.size() % 8 == 0)
        {
            int codeSer = stoi(code, 0, 2);
            char temp = (char)codeSer;
            outenc << temp;
            code = "";
        }
    }

    outenc << char(maxValue) << char(paddingBits);
    code = "";
    for (int i = 0; i < bits.size(); i++)
    {
        code += bits[i];
        if (code.size() % 8 == 0)
        {
            int codeSer = stoi(code, 0, 2);
            char temp = (char)codeSer;
            outenc << temp;
            code = "";
        }
    }
    //Adding the padding bits
    for (int i = 0; i < paddingBits; i++)
        code += '0';
    int codeSer = stoi(code, 0, 2);
    char temp = (char)codeSer;
    outenc << temp;
    outenc.close();

    //Serializing the frequency table
    std::ofstream outfrq("image.frq");
    code = "";
    for (int i = 0; i < 256; i++)
    {
        std::bitset<32> f(frqtable[i].second);
        std::string codeF = f.to_string();
        for (int i = 0; i < codeF.size(); i++)
        {
            code += codeF[i];
            if (code.size() % 8 == 0)
            {
                int codeSer = stoi(code, 0, 2);
                char temp = (char)codeSer;
                outfrq << temp;
                code = "";
            }
        }
    }
    outfrq.close();
}

void deserialize(const std::string encfile, const std::string encfrq, std::vector<std::pair<int, int>> &frqtable, std::string &bits, int &width, int &height, int &maxValue)
{
    //Deserializing frequency table
    std::ifstream infrq(encfrq);
    int frqncy,charDes;
    std::string code = "";
    char c;
    for (int i = 0; i < 256; i++)
    {
        frqtable[i].first=i;
        for (int i = 0; i < 4; i++)
        {
            infrq.get(c);
            charDes = int(c);
            std::bitset<8> x(charDes);
            code += x.to_string();
        }
        frqtable[i].second = stoi(code, 0, 2);
        code="";
    }

    infrq.close();

    //Deserializing encoded image
    std::string line = "";
    code="";
    std::ifstream inenc(encfile);
    for (int i = 0; i < 4; i++)
    {
        inenc.get(c);
        charDes = int(c);
        std::bitset<8> x(charDes);
        code += x.to_string();
    }
    width = stoi(code, 0, 2);
    code = "";
    for (int i = 0; i < 4; i++)
    {
        inenc.get(c);
        charDes = int(c);
        std::bitset<8> x(charDes);
        code += x.to_string();
    }
    height = stoi(code, 0, 2);

    inenc.get(c); //Max Value
    unsigned char temp = c;
    maxValue = int(temp);

    //Getting the padding bits number to remove them later
    inenc.get(c);
    int paddingBits = int(c);

    while (inenc.get(c))
    {
        charDes = int(c);
        std::bitset<8> x(charDes);
        bits += x.to_string();
    }

    //Removing padding bits
    for (int i = 0; i < paddingBits; i++)
        bits.pop_back();
    inenc.close();
}

#endif //DE_SERIALIZATION_HPP
