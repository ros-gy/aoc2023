#include <iostream>
#include <fstream>
#include <vector>
#include <string>
// #include <sstream>
#include <algorithm>

using namespace std;

bool isSymbol(char x) {
    
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
                                foundsymbol += isSymbol(grid[startnrow-1][current-1]);
                            }
                            foundsymbol += isSymbol(grid[startnrow-1][current]);
                            if (current < sizedata-1) {
                                foundsymbol += isSymbol(grid[startnrow-1][current+1]);
                            }
                        }
                        if (startnrow < sizedata-1) {
                            if (current !=0) {
                                foundsymbol += isSymbol(grid[startnrow+1][current-1]);
                            }
                            foundsymbol += isSymbol(grid[startnrow+1][current]);
                            if (current < sizedata-1) {
                                foundsymbol += isSymbol(grid[startnrow+1][current+1]);
                            }
                        }
                        if (current !=0) {
                            foundsymbol += isSymbol(grid[startnrow][current-1]);
                        }
                        if (current < sizedata-1) {
                            foundsymbol += isSymbol(grid[startnrow][current+1]);
                        }
                    }

                    // if found symbol, add to sum
                    if (foundsymbol != 0) {
                        cout << buffer << endl;
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

  cout << sumpn << endl;

}