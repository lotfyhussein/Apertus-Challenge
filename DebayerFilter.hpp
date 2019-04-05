#ifndef DEBAYERFILTER_H
#define DEBAYERFILTER_H

#include <iostream>
#include <fstream>
#include <string>

const uint16_t WIDTH = 4096;
const uint16_t HEIGHT = 3072;

class DebayerFilter
{
    std::string fileName;
  
    //Allocating space for all the channels

    unsigned char * ImageBuffer = new unsigned char[4096 * 3072 * 3 / 2];
    unsigned char * ImageBufferP = ImageBuffer;

    unsigned char * EightBitsBUffer = new unsigned char[4096 * 3072 ];
    unsigned char * EightBitsBUfferP = EightBitsBUffer;

    unsigned char * redChannel = new unsigned char[(4096 * 3072) /4 ];
    unsigned char * redChannelP = redChannel;

    unsigned char * green0Channel = new unsigned char[(4096 * 3072) /4 ];
    unsigned char * green0ChannelP = green0Channel;

    unsigned char * green1Channel = new unsigned char[(4096 * 3072) /4 ];
    unsigned char * green1ChannelP = green1Channel;

    unsigned char * blueChannel = new unsigned char[(4096 * 3072) /4 ];
    unsigned char * blueChannelP = blueChannel;

    unsigned char * coloredImage = new unsigned char[(4096 * 3072) * 3];
    unsigned char * coloredImageP = coloredImage;



public:

    DebayerFilter(std::string fileName);
    void SeparateChannels();
    void RedChannelToPPM();
    void Green0ChannelToPPM();
    void Green1ChannelToPPM();
    void BlueChannelToPPM();
    void CFA();
    void ColoredToPPM();

};

#endif