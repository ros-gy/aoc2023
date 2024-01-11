#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

// The first match makes the card worth one point and 
// each match after the first doubles the point value 
// of that card.
int points(int matches) {
    int score = 0;
    if (matches == 0) {
        return score;
    } else {
        score = 1;
        if (matches > 1) {
            for (int i = 0; i<matches-1; i++) {
                score = 2*score;
            }
        }
    }
    
    return score;
}

int main()
{
    string line;
    ifstream dataFile("data.txt");

    int num_wins = 10;
    int num_nums = 25;
    int card_num = 1;
    int total_points = 0;

    while (getline (dataFile, line)) {
        
        vector<string> tries;
        int pos = 0;
        pos = line.find(":");
        line.erase(0,pos+2);

        int players [num_nums];
        int winners [num_wins];

        stringstream s1(line);
        string buffer;

        // fill in the winners
        for (int i = 0; i<num_wins; i++) {
            string a;
            s1 >> a;
            winners[i] = stoi(a);
        }

        // grab and throw away pipe
        string garbage;
        s1 >> garbage;

        // fill in the players
        for (int j = 0; j<num_nums; j++) {
            string b;
            s1 >> b;
            players[j] = stoi(b);
        }

        // compare players to winners
        int matched = 0;
        for (int i = 0; i<num_nums; i++) {
            int temp1 = players[i];
            for (int j = 0; j<num_wins; j++) {
                if (players[i] == winners[j]) {
                    matched++;
                }
            }
        }

        total_points += points(matched);

        // cout << "Card " << card_num << " has " << matched << " matches. Score: " << points(matched) <<endl;

        // cout << players[0] << endl;
        // cout << players[num_nums-1] << endl;
        card_num++;
    }

    dataFile.close();

    cout << "Total points: " << total_points << endl;

}
