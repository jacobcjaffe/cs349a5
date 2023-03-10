#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <tuple>
#include <climits>

using namespace std;

ofstream outstream;
ifstream instream;

// tuple for x value, y value, weight for djikstra's algorithm
typedef tuple<int, int, int> p;

int main(int argc, char * argv[]) {

    unsigned short numcases = 0;
    unsigned short numclasses = 0;
    unsigned short width = 0;
    unsigned short height = 0;
    char shipclass;
    int timeval;
    int classidx[25] = {-1};
    priority_queue<p, vector<p>, greater<p>> priority;
    p first; 
    
    if (argc != 3) {
        cout << "ERROR: Input and output files must be specified." << endl;
        return -1;
    }

    instream.open(argv[1]);
    outstream.open(argv[2]);
    string hi;

    instream >> numcases;
    // cout << "DEBUG: numcases is " << (unsigned short) numcases << endl;
    while (numcases > 0) {
        instream >> numclasses >> width >> height;
        // cout << "DEBUG: numclasses is " << (unsigned short) numclasses << ", width is " << width << ", height is " << height << endl;

        while (numclasses > 0) {
            // cout << "DEBUG: iterator numclasses is " << (unsigned short) numclasses << endl;
            instream >> shipclass >> timeval;
            // std::cout << shipclass << " " << timeval << std::endl;
            classidx[(shipclass - 0x41)] = timeval;
            numclasses--;
        }

        // dynamically allocate 2d array
        char** grid = new char*[height];
        // tuple contains <x value, y value, weight>
        int** weight = new int*[height];
        // 2d bool array to check if x, y pair has been visited in Djikstra's
        bool** visited = new bool*[height];

        for (int i = 0; i < height; i++) {
            grid[i] = new char[width];
            weight[i] = new int[width];
            visited[i] = new bool[width] {0};
        }

        string gridline;
        int x = -1;
        int y = -1;
        for(int i = 0; i < height; i++) {
            instream >> gridline;
            for(int j = 0; j < width; j++) {
                grid[i][j] = gridline[j];

                // save values when enterprise is found
                if(gridline[j] == 'E') {
                    weight[i][j] = 0;
                    visited[i][j] = true;
                    y = i;
                    x = j;
                }
                else {
                    weight[i][j] = INT_MAX;
                }
            }
        }

        // add location of enterprise to priority queue
        priority.push(make_tuple(0, x, y));

        bool found = false;
        int currDistance;
        while (1) {
            p first = priority.top();
            x = get<1>(first);
            y = get<2>(first);
            currDistance = get<0>(first);
            priority.pop();
            // if the top of priority queue is at the edges of the grid, found exit
            if ((x == 0) || (x == width - 1) || (y == 0) || (y == height - 1)){
                // std::cout << "what " << std::endl;
                break;
            } 

            // update surrounding weights from current position
            if (x < width - 1 && visited[y][x+1] == false && weight[y][x+1] > weight[y][x] + classidx[grid[y][x+1] - 0x41]){
                weight[y][x+1] = weight[y][x] + classidx[grid[y][x+1] - 0x41];
                priority.push(make_tuple(weight[y][x+1], x + 1, y));
            }
            if (x > 0 && visited[y][x-1] == false && weight[y][x-1] > weight[y][x] + classidx[grid[y][x-1] - 0x41]) {
                weight[y][x-1] = weight[y][x] + classidx[grid[y][x-1] - 0x41];
                priority.push(make_tuple(weight[y][x-1], x - 1, y));
            }
            if (y < height - 1 && visited[y + 1][x] == false && weight[y+1][x] > weight[y][x] + classidx[grid[y+1][x] - 0x41]) {
                weight[y+1][x] = weight[y][x] + classidx[grid[y+1][x] - 0x41];
                priority.push(make_tuple(weight[y+1][x], x, y + 1));
            }
            if (y > 0 && visited[y-1][x] == false && weight[y-1][x] > weight[y][x] + classidx[grid[y-1][x] - 0x41]) {
                weight[y-1][x] = weight[y][x] + classidx[grid[y-1][x] - 0x41];
                priority.push(make_tuple(weight[y-1][x], x, y - 1));
            }
            visited[y][x] = true;
        }
        outstream << currDistance << std::endl;

        // free allocated memory
        for(int i = 0; i < height; i++) {
            delete [] grid[i];
            delete [] weight[i];
            delete [] visited[i];
        }
        delete[] grid;
        delete[] weight;
        delete[] visited;
        
        //clear priority queue
        priority = priority_queue<p, vector<p>, greater<p>>();
        numcases--;
    }

    instream.close();
    outstream.close();
    return 0;
}
