#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

char t1;
char t2;

char s1;
char s2;

int t1_pos;
int t2_pos;

int s1_pos;
int s2_pos;

std::vector<std::string> numberstring{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

bool isNumber(char a){
  if (a>47 && a <58) {
    return true;
  } else {
    return false;
  }
}

int Search(string &line)
{
    string num;
    bool t1_found = false;
    int length = line.length();
    for (int i = 0; i<length; i++) {
        if (isNumber(line[i])) {
        if (t1_found == false) {
            t1 = line[i];
            t1_found = true;
            t1_pos = i;
            t2 = t1;
            t2_pos = i;
        } else {
            t2 = line[i];
            t2_pos = i;
        }
        }
    }
    
    bool s1_found = false;
    for (int j = 0; j < numberstring.size(); j++) {
        int m = line.find(numberstring[j]);
        while (m != -1) {
            if (s1_found == false) {
                s1 = j + '1';
                s1_found = true;
                s1_pos = m;
                s2 = s1;
                s2_pos = m;
            } else {
                if (m < s1_pos) {
                    s1 = j + '1';
                    s1_pos = m;
                } else if (m > s2_pos) {
                    s2 = j + '1';
                    s2_pos = m;
                }
            }
            m = line.find(numberstring[j],m+1);
        }
    }

    if (s1_found) {
        // cout << s1 << " " << s1_pos << endl;
        // cout << t1 << " " << t1_pos << endl;
        // cout << s2 << " " << s2_pos << endl;
        // cout << t2 << " " << t2_pos << endl;
        if (s1_pos < t1_pos) {
            t1 = s1;
        }

        if (s2_pos > t2_pos) {
            t2 = s2;
        }
    }
    

    // cout << t1 << " at " << t1_pos << "\t\t" << t2 << " at " << t2_pos << endl;
    num.append(1, t1);
    num.append(1, t2);
    // cout << num << endl;
    
    return stoi(num);
}

int main()
{
  string line;
  ifstream dataFile("data.txt");
  int sumCalibration = 0;

  while (getline (dataFile, line)) {
    sumCalibration += Search(line);
  }

  dataFile.close();

  cout << sumCalibration << endl;

}