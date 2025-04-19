#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <string>
#include "Song.cpp"
using namespace std;

int main() {
    string title;
    string artist;
    string album;
    string genre;
    string releaseDate;
    int duration;
    int popularity;

    ifstream file("music.csv");
    if (!file.is_open()) {
        cerr << "Failed to open music.csv" << endl;
        return 1;
    }

    cout << "What release year would you like the song to be? " << endl;
    cin >> releaseDate;

    cout << "Would you like a short or long duration? (short/long) " << endl;
    string durPref;
    cin >> durPref;
    if (durPref == "short" || durPref == "Short") {
        duration = 180;
    } else if (durPref == "long" || durPref == "Long") {
        duration = 300;
    } else {
        duration = 240;
    }

    cout << "How popular do you want the song to be? (0 - 100) " << endl;
    cin >> popularity;

    cout << "\nYou chose:\n"
         << "Year:       " << releaseDate << "\n"
         << "Max Length: " << duration << " seconds\n"
         << "Popularity: " << popularity << " (0–100)\n";

    return 0;
}
