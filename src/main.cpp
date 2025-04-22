#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>
#include <unordered_map>
#include <algorithm>
#include "Song.h"
#include "mergeSort.h"
#include "quickSort.h"
#include "binarySearch.h"

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
            if (any_of(releaseDate.begin(), releaseDate.end(), [](unsigned char c){
                return isalpha(c);
            })) {
                cout << "Error: please enter digits only (no letters)." << endl;
                continue;
            }
            int release = stoi(releaseDate);
            if(release > 2020 or release < 2000){
                cout << "Sorry invalid input. Please try again." << endl;
                continue;
            }
            if (all_of(releaseDate.begin(), releaseDate.end(), [](char c) { return isdigit(c); })) {
                break;
            } else {
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
            } else {
                cout << "Sorry invalid input. Please try again." << endl;
            }
        }

        cout << "\nYou chose:\n"
             << "Year: " << releaseDate << "\n"
             << "Max Length: " << duration << " seconds\n"
             << "Popularity: " << popularity << " (0-100)\n";

        string sortBy;
        while (true) {
            cout << "\nSort by which attribute? (duration / popularity / releaseDate / all): ";
            cin >> sortBy;
            if (sortBy == "duration" || sortBy == "popularity" || sortBy == "releaseDate" || sortBy == "all") {
                break;
            } else {
                cout << "Sorry invalid input. Please try again." << endl;
            }
        }

        //Change release date for binary search parsing
        releaseDate += "-01-01";

        if (sortBy == "all") {
            //Create Vectors
            vector<Song> mergeSongs1 = songs;
            vector<Song> quickSongs1 = songs;

            vector<Song> mergeSongs2 = songs;
            vector<Song> quickSongs2 = songs;

            vector<Song> mergeSongs3 = songs;
            vector<Song> quickSongs3 = songs;

            auto startMerge = chrono::high_resolution_clock::now();
            mergeSort(mergeSongs1, 0, mergeSongs1.size() - 1, "duration");
            auto endMerge = chrono::high_resolution_clock::now();
            auto mergeTime = chrono::duration_cast<chrono::milliseconds>(endMerge - startMerge).count();

            auto startQuick = chrono::high_resolution_clock::now();
            quickSort(quickSongs1, 0, quickSongs1.size() - 1, "duration");
            auto endQuick = chrono::high_resolution_clock::now();
            auto quickTime = chrono::duration_cast<chrono::milliseconds>(endQuick - startQuick).count();

            //Popularity
            startMerge = chrono::high_resolution_clock::now();
            mergeSort(mergeSongs2, 0, mergeSongs2.size() - 1, "popularity");
            endMerge = chrono::high_resolution_clock::now();
            mergeTime += chrono::duration_cast<chrono::milliseconds>(endMerge - startMerge).count();

            startQuick = chrono::high_resolution_clock::now();
            quickSort(quickSongs2, 0, quickSongs2.size() - 1, "popularity");
            endQuick = chrono::high_resolution_clock::now();
            quickTime += chrono::duration_cast<chrono::milliseconds>(endQuick - startQuick).count();

            //releaseDate
            startMerge = chrono::high_resolution_clock::now();
            mergeSort(mergeSongs3, 0, mergeSongs3.size() - 1, "releaseDate");
            endMerge = chrono::high_resolution_clock::now();
            mergeTime = chrono::duration_cast<chrono::milliseconds>(endMerge - startMerge).count();

            startQuick = chrono::high_resolution_clock::now();
            quickSort(quickSongs3, 0, quickSongs3.size() - 1, "releaseDate");
            endQuick = chrono::high_resolution_clock::now();
            quickTime += chrono::duration_cast<chrono::milliseconds>(endQuick - startQuick).count();

            //Binary Search to find
            vector<Song> filteredSongs1 = binarySearch(mergeSongs1, 0, mergeSongs1.size() - 1, "duration", duration);
            vector<Song> filteredSongs2 = binarySearch(mergeSongs2, 0, mergeSongs2.size() - 1, "popularity",
                                                       popularity);
            vector<Song> filteredSongs3 = binarySearch(mergeSongs3, 0, mergeSongs3.size() - 1, "releaseDate",
                                                       releaseDate);

            //Binary with quick sort
            vector<Song> filteredSongs4 = binarySearch(quickSongs1, 0, quickSongs1.size() - 1, "duration", duration);
            vector<Song> filteredSongs5 = binarySearch(quickSongs2, 0, quickSongs2.size() - 1, "popularity",
                                                       popularity);
            vector<Song> filteredSongs6 = binarySearch(quickSongs3, 0, quickSongs3.size() - 1, "releaseDate",
                                                       releaseDate);

            //Combine
            std::unordered_map<string, int> combined;

            //Add Songs
            for (int i = 0; i < filteredSongs1.size(); i++) {
                combined[filteredSongs1[i].getTitle()] = 1;
            }
            for (int i = 0; i < filteredSongs2.size(); i++) {
                if (combined.find(filteredSongs2[i].getTitle()) != combined.end()) {
                    if (combined[filteredSongs2[i].getTitle()] == 1) {
                        combined[filteredSongs2[i].getTitle()] = 2;
                    }
                }
            }
            for (int i = 0; i < filteredSongs3.size(); i++) {
                if (combined.find(filteredSongs3[i].getTitle()) != combined.end()) {
                    if (combined[filteredSongs3[i].getTitle()] == 2) {
                        combined[filteredSongs3[i].getTitle()] = 3;
                    }
                    if (combined[filteredSongs3[i].getTitle()] == 1) {
                        combined[filteredSongs3[i].getTitle()] = 2;
                    }
                }
            }

            //Quick
            std::unordered_map<string, int> combined1;
            for (int i = 0; i < filteredSongs4.size(); i++) {
                combined1[filteredSongs4[i].getTitle()] = 1;
            }
            for (int i = 0; i < filteredSongs5.size(); i++) {
                if (combined1.find(filteredSongs5[i].getTitle()) != combined1.end()) {
                    if (combined1[filteredSongs5[i].getTitle()] == 1) {
                        combined1[filteredSongs5[i].getTitle()] = 2;
                    }
                }
            }
            for (int i = 0; i < filteredSongs6.size(); i++) {
                if (combined1.find(filteredSongs6[i].getTitle()) != combined1.end()) {
                    if (combined1[filteredSongs6[i].getTitle()] == 2) {
                        combined1[filteredSongs6[i].getTitle()] = 3;
                    }
                    if (combined[filteredSongs6[i].getTitle()] == 1) {
                        combined[filteredSongs6[i].getTitle()] = 2;
                    }
                }
            }

            //Output
            cout << "\nTop 10 songs sorted by " << sortBy << " using Merge Sort:\n";
            int count = 0;
            for (int i = 0; i < filteredSongs1.size(); ++i) {
                const Song &s = filteredSongs1[i];
                if (combined[s.getTitle()] == 3) {
                    cout << s.getTitle() << " | " << s.getArtist()
                         << " | " << s.getGenre()
                         << " | " << s.getReleaseDate()
                         << " | " << s.getDuration()
                         << "s | " << s.getPopularity() << endl;
                    count++;
                }
                if (count == 10) { break; }
            }

            cout << "\nTop 10 songs sorted by " << sortBy << " using Quick Sort:\n";
            count = 0;
            for (int i = 0; i < filteredSongs4.size(); ++i) {
                const Song &s = filteredSongs4[i];
                if (combined1[s.getTitle()] == 3) {
                    cout << s.getTitle() << " | " << s.getArtist()
                         << " | " << s.getGenre()
                         << " | " << s.getReleaseDate()
                         << " | " << s.getDuration()
                         << "s | " << s.getPopularity() << endl;
                    count++;
                }
                if (count == 10) { break; }
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
        } else {
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


            if (sortBy == "duration") {
                int target = duration;
                vector<Song> filteredSongs1 = binarySearch(mergeSongs, 0, songs.size() - 1, sortBy, target);
                vector<Song> filteredSongs2 = binarySearch(quickSongs, 0, songs.size() - 1, sortBy, target);

                cout << "\nTop 10 songs sorted by " << sortBy << " using Merge Sort:\n";
                for (int i = 2495; i < 2505; ++i) {
                    const Song &s = filteredSongs1[i];
                    cout << s.getTitle() << " | " << s.getArtist()
                         << " | " << s.getGenre()
                         << " | " << s.getReleaseDate()
                         << " | " << s.getDuration()
                         << "s | " << s.getPopularity() << endl;
                }

                cout << "\nTop 10 songs sorted by " << sortBy << " using Quick Sort:\n";
                for (int i = 2495; i < 2505; ++i) {
                    const Song &s = filteredSongs2[i];
                    cout << s.getTitle() << " | " << s.getArtist()
                         << " | " << s.getGenre()
                         << " | " << s.getReleaseDate()
                         << " | " << s.getDuration()
                         << "s | " << s.getPopularity() << endl;
                }
            }

            if (sortBy == "popularity") {
                int target = popularity;
                vector<Song> filteredSongs1 = binarySearch(mergeSongs, 0, songs.size() - 1, sortBy, target);
                vector<Song> filteredSongs2 = binarySearch(quickSongs, 0, songs.size() - 1, sortBy, target);

                cout << "\nTop 10 songs sorted by " << sortBy << " using Merge Sort:\n";
                for (int i = 2495; i < 2505; ++i) {
                    const Song &s = filteredSongs1[i];
                    cout << s.getTitle() << " | " << s.getArtist()
                         << " | " << s.getGenre()
                         << " | " << s.getReleaseDate()
                         << " | " << s.getDuration()
                         << "s | " << s.getPopularity() << endl;
                }

                cout << "\nTop 10 songs sorted by " << sortBy << " using Quick Sort:\n";
                for (int i = 2495; i < 2505; ++i) {
                    const Song &s = filteredSongs2[i];
                    cout << s.getTitle() << " | " << s.getArtist()
                         << " | " << s.getGenre()
                         << " | " << s.getReleaseDate()
                         << " | " << s.getDuration()
                         << "s | " << s.getPopularity() << endl;
                }
            }

            if (sortBy == "releaseDate") {
                string target = releaseDate;
                vector<Song> filteredSongs1 = binarySearch(mergeSongs, 0, songs.size() - 1, sortBy, target);
                vector<Song> filteredSongs2 = binarySearch(quickSongs, 0, songs.size() - 1, sortBy, target);

                cout << "\nTop 10 songs sorted by " << sortBy << " using Merge Sort:\n";
                for (int i = 2495; i < 2505; ++i) {
                    const Song &s = filteredSongs1[i];
                    cout << s.getTitle() << " | " << s.getArtist()
                         << " | " << s.getGenre()
                         << " | " << s.getReleaseDate()
                         << " | " << s.getDuration()
                         << "s | " << s.getPopularity() << endl;
                }

                cout << "\nTop 10 songs sorted by " << sortBy << " using Quick Sort:\n";
                for (int i = 2495; i < 2505; ++i) {
                    const Song &s = filteredSongs2[i];
                    cout << s.getTitle() << " | " << s.getArtist()
                         << " | " << s.getGenre()
                         << " | " << s.getReleaseDate()
                         << " | " << s.getDuration()
                         << "s | " << s.getPopularity() << endl;
                }
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
    }

    return 0;
}
