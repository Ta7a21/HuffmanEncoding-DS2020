#ifndef SER_DER_HPP
#define SER_DER_HPP

#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <bitset>
#include <sstream>
#include <fstream>

void serialize(std::map<int, std::string> &encTable, const std::uint8_t *img, const int width, const int height, const std::vector<std::pair<int, int>> frqtable)
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
    outenc << width << " " << height << " " << std::endl
           << 255 << std::endl
           << char(paddingBits);

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
    for (int i = 0; i < 256; i++)
    {
        outfrq << frqtable[i].second << " ";
    }
    outfrq.close();
}

void deserialize(std::string encfile, std::string encfrq, std::vector<std::pair<int, int>> &frqtable, std::string &bits, int &width, int &height)
{
    //Deserializing frequency table
    std::ifstream infrq(encfrq);
    int frqncy;
    for (int i = 0; i < 256; i++)
    {
        infrq >> frqncy;
        frqtable[i].first = i;
        frqtable[i].second = frqncy;
    }
    infrq.close();

    //Deserializing encoded image
    std::string line = "";
    std::ifstream inenc(encfile);
    getline(inenc, line); //Width and height
    std::stringstream width_height_ss(line);
    width_height_ss >> width >> height;
    getline(inenc, line); //Max value
    char c;

    //Getting the padding bits number to remove them later
    inenc.get(c);
    int charDes = int(c);
    int paddingBits = charDes;

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

#endif //SER_DER_HPP
