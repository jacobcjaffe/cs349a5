#include <iostream>
#include <fstream>
#include <string>

using namespace std;

ofstream outstream;
ifstream instream;

int main(int argc, char * argv[]) {

    unsigned short numcases = 0;
    unsigned short numclasses = 0;
    unsigned short width = 0;
    unsigned short height = 0;
    char shipclass;
    int timeval;
    int classidx[25] = {-1};
    
    if (argc != 3) {
        cout << "ERROR: Input and output files must be specified." << endl;
        return -1;
    }

    instream.open(argv[1]);
    outstream.open(argv[2]);
    string hi;
   /*  for(int i = 0; i < 18; i++) {
        instream >> hi;
        std::cout << hi << std::endl;
    } */

    instream >> numcases;
    cout << "DEBUG: numcases is " << (unsigned short) numcases << endl;
    instream >> numclasses >> width >> height;
    cout << "DEBUG: numclasses is " << (unsigned short) numclasses << ", width is " << width << ", height is " << height << endl;

    while (numclasses > 0) {
        // cout << "DEBUG: iterator numclasses is " << (unsigned short) numclasses << endl;
        instream >> shipclass >> timeval;
        std::cout << shipclass << " " << timeval << std::endl;
        classidx[(shipclass - 0x41)] = timeval;
        numclasses--;
    }

    // unsigned char grid[height][width] = {0};
    unsigned short iterator = 0;
    unsigned short iterator2 = 0;
    string gridline;
    string gridline2;
    for(int i = 0; i < height; i++) {
        instream >> gridline2;
        std::cout << gridline2 << std::endl;
    }
/*     
    instream >> gridline;
    outstream << "testing: " << (int)gridline[0] << std::endl;
    while (iterator2 < height) {
        std::getline(instream, gridline);
        outstream << "DEBUG: Grid input line is " << gridline << endl;
        while (iterator < width) {
            grid[iterator2][iterator] = gridline[iterator];
            iterator++;
        }
        iterator2++;
    }
    outstream << "DEBUG: Grid should be " << endl;
    for( iterator = 0; iterator < height; iterator++) {
        for (iterator2 = 0; iterator2 < width; iterator2++) {
            // cout << (unsigned short) grid[iterator][iterator2];
        }       
        // cout << endl;
    }
    */
    // Garbage collection before ending
    instream.close();
    outstream.close();
    
    return 0;
}