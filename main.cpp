#include "DebayerFilter.hpp"
using namespace std;

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
      cout <<"Error!" <<endl;
      cout << "Usage: ./out RawImagefilename\n";
      return -1;
    }
    string fileName = argv[1];
    DebayerFilter RawImage(fileName);
    RawImage.SeparateChannels();
    RawImage.RedChannelToPPM();
    RawImage.Green0ChannelToPPM();
    RawImage.Green1ChannelToPPM();
    RawImage.BlueChannelToPPM();
    RawImage.CFA();
    RawImage.ColoredToPPM();
    cout << "Done" <<endl;

    return 0;
}
