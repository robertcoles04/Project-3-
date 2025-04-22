#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>
#include "Song.h"
#include "mergeSort.h"
#include "quickSort.h"

using namespace std;

bool isPopularityGood(const string& popularity) {
    if (popularity.length() > 3) {
        return false;
    }
    if (!all_of(popularity.begin(), popularity.end(), [](char c){return isdigit(c);})){
        return false;
    }
    if (stoi(popularity) > 100) {
        return false;
    }
    return true;
}

int main() {
    ifstream file("music.csv");
    if (!file.is_open()) {
        cerr << "Failed to open music.csv" << endl;
        return 1;
    }
    vector<Song> songs;
    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string t, a, al, g, rd, dur, pop;

        getline(ss, t, ',');
        getline(ss, a, ',');
        getline(ss, al, ',');
        getline(ss, g, ',');
        getline(ss, rd, ',');
        getline(ss, dur, ',');
        getline(ss, pop, ',');

        Song song(t, a, al, g, rd, dur, pop);
        songs.push_back(song);
    }
    file.close();

    cout << "___________________________________________________________________________________________\n"
            "Hello! Welcome to the Song Finder. We're going to find songs that meet your specifications.\n"
            "___________________________________________________________________________________________" << endl;

    while (true) {
        string releaseDate;
        int duration;
        int popularity;

        while (true) {
            cout << "What release year would you like the songs to be? (2000 - 2020) " << endl;
            cin >> releaseDate;
            if (all_of(releaseDate.begin(), releaseDate.end(), [](char c){return isdigit(c);})){
                break;
            }
            else {
                cout << "bad input" << endl;
            }
        }

        cout << "Would you like a short or long duration? (short/long; type anything else for medium)" << endl;
        string durPref;
        cin >> durPref;
        if (durPref == "short" || durPref == "Short") {
            duration = 180;
        } else if (durPref == "long" || durPref == "Long") {
            duration = 300;
        } else {
            duration = 240;
        }

        string popPref;
        while (true) {
            cout << "How popular do you want the songs to be? (0 - 100) " << endl;
            cin >> popPref;
            if (isPopularityGood(popPref)) {
                popularity = stoi(popPref);
                break;
            }
            else {
                cout << "bad input" << endl;
            }
        }

        cout << "\nYou chose:\n"
             << "Year: " << releaseDate << "\n"
             << "Max Length: " << duration << " seconds\n"
             << "Popularity: " << popularity << " (0-100)\n";

        string sortBy;
        while (true) {
            cout << "\nSort by which attribute? (duration / popularity / releaseDate): ";
            cin >> sortBy;
            if (sortBy == "duration" || sortBy == "popularity" || sortBy == "releaseDate") {
                break;
            }
            else {
                cout << "bad input" << endl;
            }
        }

        vector<Song> mergeSongs = songs;
        vector<Song> quickSongs = songs;

        auto startMerge = chrono::high_resolution_clock::now();
        mergeSort(mergeSongs, 0, mergeSongs.size() - 1, sortBy);
        auto endMerge = chrono::high_resolution_clock::now();
        auto mergeTime = chrono::duration_cast<chrono::milliseconds>(endMerge - startMerge).count();

        auto startQuick = chrono::high_resolution_clock::now();
        quickSort(quickSongs, 0, quickSongs.size() - 1, sortBy);
        auto endQuick = chrono::high_resolution_clock::now();
        auto quickTime = chrono::duration_cast<chrono::milliseconds>(endQuick - startQuick).count();

        /* uncomment once binarySearch is done
        vector<Song> filteredSongs = binarySearch(songs, 0, songs.size()-1, "duration", 50);
        if (filteredSongs.empty()) {
            cout << "No songs matched your filter criteria.\n";
            return 0;
        }*/

        cout << "\nTop 10 songs sorted by " << sortBy << " using Merge Sort:\n";
        for (int i = 0; i < min(10, (int)mergeSongs.size()); ++i) {
            const Song& s = mergeSongs[i];
            cout << s.getTitle() << " | " << s.getArtist()
                 << " | " << s.getGenre()
                 << " | " << s.getReleaseDate()
                 << " | " << s.getDuration()
                 << "s | " << s.getPopularity() << endl;
        }

        cout << "\nTop 10 songs sorted by " << sortBy << " using Quick Sort:\n";
        for (int i = 0; i < min(10, (int)quickSongs.size()); ++i) {
            const Song& s = quickSongs[i];
            cout << s.getTitle() << " | " << s.getArtist()
                 << " | " << s.getGenre()
                 << " | " << s.getReleaseDate()
                 << " | " << s.getDuration()
                 << "s | " << s.getPopularity() << endl;
        }

        cout << "\nSorting Time Comparison:\n";
        cout << "Merge Sort: " << mergeTime << " ms\n";
        cout << "Quick Sort: " << quickTime << " ms\n";
        string goAgain;
        cout << "Would like to go again? Y or y for yes, any other key for no" << endl;
        cin >> goAgain;
        if (goAgain != "Y" && goAgain != "y") {
            cout << "Goodbye!" << endl;
            break;
        }
    }

    return 0;
}
