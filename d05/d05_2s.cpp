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
    long min_loc = 662197086000000;
    long maps[8];
    long counter = 0;

    int maprange[7] = {48, 23, 35, 24, 15, 11, 28};

    vector<long> starts;
    vector<long> ranges;
    double pct = 0;

    vector<long> seeds;

    vector<string> map;
    vector<vector<string>> mapmap;

    // create arrays to store maps
    for (int j = 1; j<8; j++) {

        ifstream mapFile(prefix+"/"+names[j-1]+".txt");
        
        while (getline (mapFile, line)) {

            stringstream s1(line);
            string dest_buf;
            string source_buf;
            string range_buf;

            s1 >> dest_buf;
            s1 >> source_buf;
            s1 >> range_buf;

            map.push_back(dest_buf + " " + source_buf + " " + range_buf);
        }
        mapFile.close();
        mapmap.push_back(map);
    }


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

    // make vectors of starts and ranges
    for (int i = 0; i<20; i++) {
        if (i%2 == 1) {
            ranges.push_back(seeds[i]);
        }
        else {
            starts.push_back(seeds[i]);
        }
    }

    // cout << "Starting at " << starts[0] << " with a range of " << ranges[0] << endl;

    // iterate through 10 ranges of seeds
    for (int i= 0; i< 10; i++) {
        // cout << "RANGE " << i << endl;
        // loop through a range
        for (long x = starts[i]; x<(starts[i]+ranges[i]); x++){
            if (x%20000 == 0){
                pct = 100.0*counter/2136279819.0;
                cout << "minimum loc: " << min_loc << " - (" << pct << ") " << endl;
            }

            counter++;
            maps[0] = x;
            // iterate through maps
            for (int j = 1; j<8; j++) {

                // initialize column with previous column
                maps[j] = maps[j-1];

                for (int y=0; y<maprange[j-1]; y++) {

                    stringstream s1(mapmap[j-1][y]);
                    string dest_buf;
                    string source_buf;
                    string range_buf;

                    s1 >> dest_buf;
                    s1 >> source_buf;
                    s1 >> range_buf;

                    long dst = stol(dest_buf);
                    long src = stol(source_buf);
                    long rng = stol(range_buf);

                    // compare, and if within range, save dest number
                    if (maps[j-1] >= src && maps[j-1] < (src+rng)) {
                        maps[j] = maps[j-1] - src + dst;
                        break;
                    }                
                }
                
            }

            // record the minimum location
            if (maps[7] < min_loc) {
                min_loc = maps[7];
            }
        }
        
    }
    cout << "MINIMUM LOCATION: " << min_loc << endl;
}