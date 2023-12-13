#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>

using namespace std;

vector<string> gear_finds;

bool isSymbol(char x, int prow, int pcol, string nbuffer, int row, int col) {
    
    if (x == 42) {
        // found gear
        // make a list of gear position and numbers found near
        // cout << "row " << prow << " col " << pcol << " " << stoi(nbuffer) << endl;
        string gearpos = to_string(prow) + " " + to_string(pcol) + " " + nbuffer + " " + to_string(row) + " " + to_string(col);
        
        if (find(gear_finds.begin(), gear_finds.end(), gearpos) == gear_finds.end()) {
            gear_finds.push_back(gearpos);
        }
    }

    if (x > 57) { //not a period or number
        // cout << x << endl;
        return true;
    } else if (x < 48 && x!=46) {
        // cout << x << endl;
        return true;
    } else {
        return false;
    }
}

int main()
{
    int sizedata = 140;
    int sumpn = 0;
    int sumgr = 0;
    string line;
    ifstream dataFile("data.txt");
    int row = 0;
    char grid[sizedata][sizedata];

    while (getline (dataFile, line)) {
        for (int i = 0; i < sizedata; i++) {
            // cout << row << " " << i << endl;
            grid[row][i] = line[i];
        }
        row++;
    }

    // iterate through
    // find each number
    // record start and stop position of number
    // look around number positions for symbols

    bool foundNum = false;
    int startnrow;
    int startncol;
    int endncol;
    string buffer;

    for (int row = 0; row < sizedata; row++) {
        for (int col = 0; col < sizedata; col++) {
            
            if (grid[row][col] > 47 && grid[row][col] < 58) {
                // found a number
                if (foundNum == false) {
                    foundNum = true;
                    startnrow = row;
                    startncol = col;
                }
                buffer += grid[row][col];
                endncol = col;
            } else {
                if (foundNum == true) {
                    // at this point, we know the start and stop position
                    // of a number. we can check for symbols
                    int foundsymbol = 0;
                    int length = endncol-startncol+1;
                    for (int k = 0; k<length; k++) {
                        int current = startncol+k;

                        if (startnrow != 0) {
                            if (current !=0) {
                                foundsymbol += isSymbol(grid[startnrow-1][current-1],startnrow-1, current-1, buffer, startnrow, startncol);
                            }
                            foundsymbol += isSymbol(grid[startnrow-1][current],startnrow-1, current, buffer, startnrow, startncol);
                            if (current < sizedata-1) {
                                foundsymbol += isSymbol(grid[startnrow-1][current+1],startnrow-1, current+1, buffer, startnrow, startncol);
                            }
                        }
                        if (startnrow < sizedata-1) {
                            if (current !=0) {
                                foundsymbol += isSymbol(grid[startnrow+1][current-1],startnrow+1, current-1, buffer, startnrow, startncol);
                            }
                            foundsymbol += isSymbol(grid[startnrow+1][current],startnrow+1, current, buffer, startnrow, startncol);
                            if (current < sizedata-1) {
                                foundsymbol += isSymbol(grid[startnrow+1][current+1],startnrow+1, current+1, buffer, startnrow, startncol);
                            }
                        }
                        if (current !=0) {
                            foundsymbol += isSymbol(grid[startnrow][current-1],startnrow, current-1, buffer, startnrow, startncol);
                        }
                        if (current < sizedata-1) {
                            foundsymbol += isSymbol(grid[startnrow][current+1],startnrow, current+1, buffer, startnrow, startncol);
                        }
                    }

                    // if found symbol, add to sum
                    if (foundsymbol != 0) {
                        // cout << buffer << endl;
                        sumpn += stoi(buffer);
                    }
                    
                    foundNum = false;
                    // cout << buffer << " x " << length << endl;
                    buffer.clear();
                }
            }
        }
    }

    dataFile.close();

    string gx;
    string gy;
    string v1;
    string v2;
    string gx2;
    string gy2;
    int dup = 0;

    for (int y = 0; y<gear_finds.size(); y++) {
        // cout << gear_finds[y] << endl;
    }

    for (int y = 0; y<gear_finds.size(); y++) {
        dup = 0;
        stringstream ss;
        ss << gear_finds[y];
        ss >> gx;
        ss >> gy;
        ss >> v1;

        for (int z = 0; z<gear_finds.size(); z++) {
            if (z != y) {
                stringstream st;
                st << gear_finds[z];
                st >> gx2;
                st >> gy2;
                
                if (gx.compare(gx2) == 0 && gy.compare(gy2) == 0) {
                    // cout << gx << " " << gx2 << " " << endl;
                    // sumgr += (stoi(v1)*stoi(v2))/2;
                    st >> v2;
                    dup++;
                    // cout << gx << " = " << gx2 << "  " << gy << " = " << gy2 << endl;
                    cout << v1 << " " << v2 << "  " << endl;
                }
            }
        }

        // cout << "Duplicates: " << dup << endl;
        if (dup == 1) {
            int m = stoi(v1)*stoi(v2)/2;
            // cout << m << endl;
            sumgr += m;
        }
    }

    // cout << sumgr << endl;
    // used excel magic to add up 

}