#include "DebayerFilter.hpp"

using namespace std;

DebayerFilter::DebayerFilter(string fileName)
{
    this->fileName = fileName;
}


void DebayerFilter::SeparateChannels()

{
    ifstream rawFile(fileName, ifstream::binary);
    rawFile.read(reinterpret_cast<char*>(ImageBuffer), 4096 * 3072 * 3 / 2);
    rawFile.close();

    int c = 0; 
    for (long i = 0; i < 4096 * 3072 * 3 / 2; i += 3)
    {
        EightBitsBUfferP[c]   = ImageBuffer[i];
        EightBitsBUfferP[c+1] = ((ImageBuffer[i+1] & 0x0F) << 4) | (ImageBuffer[i+2] >> 4);
        c+=2;
    }

    delete[] ImageBuffer;


    int OddRow = 0, EvenRow = 0;
    for (long i = 0; i < 4096 * 3072; i += 2) 
    {
        int row = i / WIDTH;
        if ((row % 2) == 0) 
        {
            redChannel[EvenRow]      = EightBitsBUffer[i];
            green0Channel[EvenRow]   = EightBitsBUffer[i + 1];
            EvenRow++;
        } 
        else 
        {
            green1Channel[OddRow]    = EightBitsBUffer[i];
            blueChannel[OddRow]      = EightBitsBUffer[i + 1];
            OddRow++;
        }
    }

    cout << "Red Channel 5x5 Pixels: " << endl;
     for (int i = 0; i < 5; i++)
    {
        cout << hex << unsigned(redChannel[WIDTH * i + 0]) << ",";
        cout << hex << unsigned(redChannel[WIDTH * i + 1])<< ",";
        cout << hex << unsigned(redChannel[WIDTH * i + 2])<< ",";
        cout << hex << unsigned(redChannel[WIDTH * i + 3])<< ",";
        cout << hex << unsigned(redChannel[WIDTH * i + 4]);
        cout << endl;

    }
    cout << "==========================="<<endl;
    cout << "Green 0 Channel 5x5 Pixels: " << endl;
     for (int i = 0; i < 5; i++)
    {
        cout << hex << unsigned(green0Channel[WIDTH * i + 0]) << ",";
        cout << hex << unsigned(green0Channel[WIDTH * i + 1])<< ",";
        cout << hex << unsigned(green0Channel[WIDTH * i + 2])<< ",";
        cout << hex << unsigned(green0Channel[WIDTH * i + 3])<< ",";
        cout << hex << unsigned(green0Channel[WIDTH * i + 4]);
        cout << endl;

    }
    cout << "==========================="<<endl;
    cout << "Green 1 Channel 5x5 Pixels: " << endl;
     for (int i = 0; i < 5; i++)
    {
        cout << hex << unsigned(green1Channel[WIDTH * i + 0]) << ",";
        cout << hex << unsigned(green1Channel[WIDTH * i + 1])<< ",";
        cout << hex << unsigned(green1Channel[WIDTH * i + 2])<< ",";
        cout << hex << unsigned(green1Channel[WIDTH * i + 3])<< ",";
        cout << hex << unsigned(green1Channel[WIDTH * i + 4]);
        cout << endl;

    }
    cout << "==========================="<<endl;
    cout << "Blue Channel 5x5 Pixels: " << endl;
     for (int i = 0; i < 5; i++)
    {
        cout << hex << unsigned(blueChannel[WIDTH * i + 0]) << ",";
        cout << hex << unsigned(blueChannel[WIDTH * i + 1])<< ",";
        cout << hex << unsigned(blueChannel[WIDTH * i + 2])<< ",";
        cout << hex << unsigned(blueChannel[WIDTH * i + 3])<< ",";
        cout << hex << unsigned(blueChannel[WIDTH * i + 4]);
        cout << endl;
    }
     
    cout << endl;



  //Outputing the channels as separate ppm files

    RedChannelToPPM();
    Green0ChannelToPPM();
    Green1ChannelToPPM();
    BlueChannelToPPM();
   

}



void DebayerFilter::RedChannelToPPM()
{

    ofstream outfile("red.ppm");
    outfile << "P3\n2048 1536\n255\n";
    for (long i = 0; i < (4096 * 3072) /4; ++i)
    {
        if (i % WIDTH / 2 == 0 && i > 0)
        {
            outfile << "\n";
        }
            outfile << (int)redChannel[i] << " " << 0 << " " << 0 << " ";
    }
}




void DebayerFilter::Green0ChannelToPPM()
{
    ofstream outfile("green0.ppm");
    outfile << "P3\n2048 1536\n255\n";
    for (long i = 0; i < (4096 * 3072) /4; ++i)
    {
        if (i % WIDTH / 2 == 0 && i > 0)
        {
            outfile << "\n";
        }
            outfile << 0 << " " << (int)green0Channel[i] << " " << 0 << " ";
    }

}

void DebayerFilter::Green1ChannelToPPM()
{
    ofstream outfile("green1.ppm");
    outfile << "P3\n2048 1536\n255\n";
    for (long i = 0; i < (4096 * 3072) /4; ++i)
    {
        if (i % WIDTH / 2 == 0 && i > 0)
        {
            outfile << "\n";
        }
            outfile << 0 << " " << (int)green1Channel[i] << " " << 0 << " ";
    }

}

void DebayerFilter::BlueChannelToPPM()
{

    ofstream outfile("blue.ppm");
    outfile << "P3\n2048 1536\n255\n";
    for (long i = 0; i < (4096 * 3072) /4; ++i)
    {
        if (i % WIDTH / 2 == 0 && i > 0)
        {
            outfile << "\n";
        }
            outfile << 0 << " " << 0 << " " << (int)blueChannel[i] << " ";
    }

}

void DebayerFilter::CFA()
{
    int j;
    for (long  i = 0; i < (4096 * 3072); i += 2)
    {
        j = i * 3;
        int row = i / WIDTH;
      if ((i % (WIDTH *2)) < WIDTH) 
        {
            coloredImageP[j] = EightBitsBUfferP[i];
            coloredImageP[j + 1] = EightBitsBUfferP[i + 1];
            coloredImageP[j + 2] = EightBitsBUfferP[i + WIDTH + 1];
            coloredImageP[j + 3] = EightBitsBUfferP[i];
            coloredImageP[j + 4] = EightBitsBUfferP[i + 1];
            coloredImageP[j + 5] = EightBitsBUfferP[i + WIDTH + 1];
        } 

        else 
        {
            coloredImageP[j] = EightBitsBUfferP[i - WIDTH];
            coloredImageP[j + 1] = EightBitsBUfferP[i];
            coloredImageP[j + 2] = EightBitsBUfferP[i + 1];
            coloredImageP[j + 3] = EightBitsBUfferP[i - WIDTH];
            coloredImageP[j + 4] = EightBitsBUfferP[i];
            coloredImageP[j + 5] = EightBitsBUfferP[i + 1];
        }
    }


}

void DebayerFilter::ColoredToPPM()
{
    std::ofstream outfile("colored.ppm");

        outfile << "P3\n4096 3072\n255\n";
        for(long i = 0; i < 3 * (4096 * 3072); i += 3)
        {
            if(i % WIDTH == 0 && i > 0)
            {
                outfile << "\n";
            }

            outfile << (int)coloredImageP[i] << " " << (int)coloredImageP[i+1] << " " << (int)coloredImageP[i+2] << " ";
        }    
    
}


