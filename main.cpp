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
    return 0;
}
