#ifndef DECODE_HPP
#define DECODE_HPP

#include <iostream>
#include <map>
#include <vector>
#include <queue>

void decodingTable(const std::map<int,std::string> enctable,std::map<std::string,int> &dectable)
{
    //Constructing an inverse table for the coded table
    for(auto it=enctable.begin();it!=enctable.end();it++)
        dectable[it->second]=it->first;
}

std::uint8_t *decode(const std::string bits,std::map<std::string,int> &dectable,const int width,const int height,const std::string zero)
{
    std::string temp="";
    int j=0;
    std::uint8_t *imgData=new std::uint8_t[width*height];
    //Retrieving the original form of the data
    for(int i=0;i<bits.size();i++)
    {
        temp+=bits[i];
        if(dectable[temp]!=0 || temp==zero)
        {
            imgData[j]=dectable[temp];
            j++;
            temp="";
        }
    }
    return imgData;
}
















#endif //DECODE_HPP