#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

char t1;
char t2;

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
        t2 = t1;
      } else {
        t2 = line[i];
      }
    }
  }
  num.append(1, t1);
  num.append(1, t2);
  
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