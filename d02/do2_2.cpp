#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

int main()
{
    int sumpower = 0;
  string line;
  ifstream dataFile("data.txt");
  int gameNumber = 1;
  int sumIDs = 0;

  int r_max = 12;
  int g_max = 13;
  int b_max = 14;

  while (getline (dataFile, line)) {
    cout << "GAME" << endl;

    int biggest_red = 0;
    int biggest_green = 0;
    int biggest_blue = 0;

    int smallest_red = 0;
    int smallest_green = 0;
    int smallest_blue = 0;

    vector<string> tries;
    int pos = 0;
    pos = line.find(":");
    line.erase(0,pos+2);

    stringstream s1(line);
    string word;
    while (!s1.eof()) {
        getline(s1, word, ';');
        tries.push_back(word);
    }

    for (int i = 0; i<tries.size(); i++) {
        int red = 0;
        int green = 0;
        int blue = 0;
        // cout << "HAND" << endl;
        vector<string> color_count;
        stringstream s2(tries[i]);
        string hand;
        while(!s2.eof()) {
            getline(s2, hand, ',');
            color_count.push_back(hand);
        }

        //count up each color
        for (int j = 0; j<color_count.size(); j++) {
            string num;
            string color;
            stringstream reading(color_count[j]);
            reading >> num;
            reading >> color;

            if (color.compare("red") == 0) {
                red = stoi(num);
            }

            if (color.compare("green") == 0) {
                green = stoi(num);
            }

            if (color.compare("blue") == 0) {
                blue = stoi(num);
            }
            
            if (red > biggest_red) {
                biggest_red = red;
            }
            if (green > biggest_green) {
                biggest_green = green;
            }
            if (blue > biggest_blue) {
                biggest_blue = blue;
            }

        }
        
    }
    
    // cout << biggest_red << " " << biggest_green << " " << biggest_blue << endl;

    int power = biggest_red*biggest_green*biggest_blue;
    sumpower += power;

    if (biggest_red <= r_max) {
        if (biggest_green <= g_max) {
            if (biggest_blue <= b_max) {
                sumIDs += gameNumber;
            }
        }
    }
    // sumIDs += Search(line);

    gameNumber++;
  }

  dataFile.close();

  cout << sumpower << endl;

}