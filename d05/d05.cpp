#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

int main()
{
    string line;
    string prefix = "data"; //data
    ifstream seedFile(prefix+"/seeds.txt");
    string names[7] = {"seedtosoil","soiltofertilizer", "fertilizertowater", "watertolight", "lighttotemp", "temptohumidity", "humiditytolocation"};

    vector<long long> seeds;    

    // grab seeds
    while (getline (seedFile, line)) {

        stringstream s1(line);

        while (!s1.eof()) {
            string buffer;
            s1 >> buffer;
            seeds.push_back(stol(buffer));
        }
    }
    seedFile.close();

    

    // map[i][0] is seed, map[i][1] is soil...
    int seed_number = 20; //20
    long long maps[seed_number][8];

    for (int i= 0; i< seed_number; i++) {
        maps[i][0] = seeds[i];
    }

    // iterate through seeds to map to location
    for (int i= 0; i< seed_number; i++) {
        
        // cout << seed << endl;

        // iterate through maps
        for (int j = 1; j<8; j++) {

            // initialize column with previous column
            maps[i][j] = maps[i][j-1];


            ifstream mapFile(prefix+"/"+names[j-1]+".txt");

            while (getline (mapFile, line)) {

                stringstream s1(line);
                string dest_buf;
                string source_buf;
                string range_buf;

                s1 >> dest_buf;
                s1 >> source_buf;
                s1 >> range_buf;

                long long dst = stoll(dest_buf);
                long long src = stoll(source_buf);
                long long rng = stoll(range_buf);

                // compare, and if within range, save dest number
                if (maps[i][j-1] >= src && maps[i][j-1] < (src+rng)) {
                    maps[i][j] = maps[i][j-1] - src + dst;
                    break;
                }                
            }
            mapFile.close();
        }
    }
    

    for (int i= 0; i< seed_number; i++) {
        for (int j = 0; j<8; j++) {
            cout << maps[i][j] << "\t";
        }
        cout << endl;
    }

    // find minimum of last column
    long long min;
    min = maps[0][7];
    for (int i= 0; i< seed_number; i++) {
        if (maps[i][7] < min) {
            min = maps[i][7];
        }
    }

    cout << "minimum loc: " << min << endl;
}