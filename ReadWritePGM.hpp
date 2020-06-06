#ifndef READWRITE_HPP
#define READWRITE_HPP

#include <iostream>
#include <fstream>
#include <sstream>


std::uint8_t *Readpgm(int &numbercolumns, int &numberrow, std::string imagename)
{
  std::ifstream readfile(imagename); // Operate on the image.pgm (input file)
  std::string Line = "";

  getline(readfile, Line); // read the format type (version)
  if (Line.compare("P5") != 0)
  {
    std::cerr << "Error, not the true format" << std::endl;
    exit(1);
  }

  getline(readfile, Line); // read dimensions of image (the number of columns and rows)
  std::stringstream readptr(Line);
  readptr >> numbercolumns >> numberrow;

  getline(readfile, Line); // read the pixels data (max intensity)

  std::uint8_t *pgm = new std::uint8_t[numbercolumns * numberrow];

  readfile.read((char *)pgm, numbercolumns * numberrow);
  readfile.close();
  return pgm;
}

// output file
void Writepgm(const std::uint8_t *pgm, int &numbercolumns, int &numberrow, std::string imagename)
{
  std::ofstream outdata(imagename);  // output image.pgm after decoding
  outdata << "P5" << std::endl
          << numbercolumns << " " << numberrow << std::endl
          << "255" << std::endl;
  for (int i = 0; i < numbercolumns * numberrow; i++)
  {

    outdata << (pgm[i]) << "";
  }
  outdata.close();
}

#endif //READWRITE_HPP
