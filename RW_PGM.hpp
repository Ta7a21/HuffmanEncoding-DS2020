#ifndef RW_PGM_HPP
#define RW_PGM_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

std::uint8_t *read_pgm_image(int &width, int &height, int &maxValue, const std::string filename)
{
    std::string line;
    std::ifstream in(filename); //Reading file
    getline(in, line);          //Format
    if (line.compare("P5") != 0)
    {
        std::cerr << "Please use P5 version only" << std::endl;
        exit(1);
    }
    getline(in, line); //Width and height
    std::stringstream width_height_ss(line);
    width_height_ss >> width >> height;
    getline(in, line); //Max value
    std::stringstream maxValue_ss(line);
    maxValue_ss >> maxValue;
    std::uint8_t *img = new std::uint8_t[width * height]; //Dynamic array to store pixels
    in.read((char *)img, width * height);                 //Data
    in.close();
    return img;
}

void write_pgm_image(const std::uint8_t *img, const int width, const int height, const int maxValue, const std::string filename)
{
    std::ofstream out(filename); //Creating file
    out << "P5" << std::endl
        << width << " " << height << std::endl
        << maxValue << std::endl;                 //Writing headers
    out.write((const char *)img, width * height); //Writing data
    out.close();
}

#endif //RW_PGM_HPP
