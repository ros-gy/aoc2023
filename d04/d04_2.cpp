#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

int main()
{
    string line;
    ifstream dataFile("data.txt");

    int num_wins = 10;
    int num_nums = 25;
    int card_num = 0;
    int starting_num_cards = 202;
    int total_cards = 0;

    int number_cards[starting_num_cards];

    for (int i = 0; i< starting_num_cards; i++) {
        number_cards[i] = 1;
    }

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

        for (int i = 0; i<matched; i++) {
            number_cards[card_num + 1 + i] += number_cards[card_num];
        }

        // cout << "Card " << card_num << " has " << matched << " matches." <<endl;

        card_num++;
    }

    dataFile.close();

    for (int i = 0; i < starting_num_cards; i++) {
        total_cards += number_cards[i];
    }

    cout << "Total scratchcards: " << total_cards << endl;

}