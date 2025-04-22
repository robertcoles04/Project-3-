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

// To check user input for popularity
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
    // Read through the dataset, create a Song object for each song, and add each one to the vector called songs
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

    // while loop to allow the user to use the program multiple times without it stopping
    while (true) {
        string releaseDate;
        int duration;
        int popularity;

        // Loop to ask user for release year until they give valid input
        while (true) {
            cout << "What release year would you like the songs to be? (2000 - 2020) " << endl;
            cin >> releaseDate;
            if (!all_of(releaseDate.begin(), releaseDate.end(), [](char c) { return isdigit(c); })){
                cout << "Error: please enter digits only." << endl;
                continue;
            }
            int release = stoi(releaseDate);
            if(release > 2020 or release < 2000){
                cout << "Sorry invalid input. Please try again." << endl;
                continue;
            }
            if (all_of(releaseDate.begin(), releaseDate.end(), [](char c) { return isdigit(c); })) {
                break;
            }
        }

        // Ask user for duration preference
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

        // Loop to ask user for popularity preference until they give valid input
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

        // Loop to ask user for which attribute they want to sort the outputted songs by until they give valid input
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

            // Sort songs based on duration using merge sort
            auto startMerge = chrono::high_resolution_clock::now();
            mergeSort(mergeSongs1, 0, mergeSongs1.size() - 1, "duration");
            auto endMerge = chrono::high_resolution_clock::now();
            auto mergeTime = chrono::duration_cast<chrono::milliseconds>(endMerge - startMerge).count();

            // Sort songs based on duration using merge sort
            auto startQuick = chrono::high_resolution_clock::now();
            quickSort(quickSongs1, 0, quickSongs1.size() - 1, "duration");
            auto endQuick = chrono::high_resolution_clock::now();
            auto quickTime = chrono::duration_cast<chrono::milliseconds>(endQuick - startQuick).count();

            // Sort songs based on popularity using merge sort
            startMerge = chrono::high_resolution_clock::now();
            mergeSort(mergeSongs2, 0, mergeSongs2.size() - 1, "popularity");
            endMerge = chrono::high_resolution_clock::now();
            mergeTime += chrono::duration_cast<chrono::milliseconds>(endMerge - startMerge).count();

            // Sort songs based on popularity using quick sort
            startQuick = chrono::high_resolution_clock::now();
            quickSort(quickSongs2, 0, quickSongs2.size() - 1, "popularity");
            endQuick = chrono::high_resolution_clock::now();
            quickTime += chrono::duration_cast<chrono::milliseconds>(endQuick - startQuick).count();

            // Sort songs based on release date using merge sort
            startMerge = chrono::high_resolution_clock::now();
            mergeSort(mergeSongs3, 0, mergeSongs3.size() - 1, "releaseDate");
            endMerge = chrono::high_resolution_clock::now();
            mergeTime += chrono::duration_cast<chrono::milliseconds>(endMerge - startMerge).count();

            // Sort songs based on release date using quick sort
            startQuick = chrono::high_resolution_clock::now();
            quickSort(quickSongs3, 0, quickSongs3.size() - 1, "releaseDate");
            endQuick = chrono::high_resolution_clock::now();
            quickTime += chrono::duration_cast<chrono::milliseconds>(endQuick - startQuick).count();

            // Binary Search to create vectors of songs which are each sorted by one of the three attributes
            // Conduct binary search on the vectors sorted by merge sort
            vector<Song> filteredSongs1 = binarySearch(mergeSongs1, 0, mergeSongs1.size() - 1, "duration", duration);
            vector<Song> filteredSongs2 = binarySearch(mergeSongs2, 0, mergeSongs2.size() - 1, "popularity",
                                                       popularity);
            vector<Song> filteredSongs3 = binarySearch(mergeSongs3, 0, mergeSongs3.size() - 1, "releaseDate",
                                                       releaseDate);

            // Conduct binary search on the vectors sorted by quick sort
            vector<Song> filteredSongs4 = binarySearch(quickSongs1, 0, quickSongs1.size() - 1, "duration", duration);
            vector<Song> filteredSongs5 = binarySearch(quickSongs2, 0, quickSongs2.size() - 1, "popularity",
                                                       popularity);
            vector<Song> filteredSongs6 = binarySearch(quickSongs3, 0, quickSongs3.size() - 1, "releaseDate",
                                                       releaseDate);

            // This unordered map will contain all of the songs in the first three filteredSong vectors.
            // (Those vectors were created by filtering the vectors sorted by merge sort)
            // The songs that are in all three vectors will have a value of 3 in the map.
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

            // Same as above but for the other three filtered song vectors,
            // which were created by  filtering the vectors sorted by quick sort
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
                    if (combined1[filteredSongs6[i].getTitle()] == 1) {
                        combined1[filteredSongs6[i].getTitle()] = 2;
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
        } else { // if sortBy is not "all"
            vector<Song> mergeSongs = songs;
            vector<Song> quickSongs = songs;

            // Sort songs with merge sort based on whatever the user chose to sort by
            auto startMerge = chrono::high_resolution_clock::now();
            mergeSort(mergeSongs, 0, mergeSongs.size() - 1, sortBy);
            auto endMerge = chrono::high_resolution_clock::now();
            auto mergeTime = chrono::duration_cast<chrono::milliseconds>(endMerge - startMerge).count();

            // Sort songs with quick sort based on whatever the user chose to sort by
            auto startQuick = chrono::high_resolution_clock::now();
            quickSort(quickSongs, 0, quickSongs.size() - 1, sortBy);
            auto endQuick = chrono::high_resolution_clock::now();
            auto quickTime = chrono::duration_cast<chrono::milliseconds>(endQuick - startQuick).count();

            if (sortBy == "duration") {
                // Conduct binary search on the vectors sorted by merge sort and quick sort in order to filter them by duration
                int target = duration;
                vector<Song> filteredSongs1 = binarySearch(mergeSongs, 0, songs.size() - 1, sortBy, target);
                vector<Song> filteredSongs2 = binarySearch(quickSongs, 0, songs.size() - 1, sortBy, target);

                // Output
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
                // Conduct binary search on the vectors sorted by merge sort and quick sort in order to filter them by duration
                int target = popularity;
                vector<Song> filteredSongs1 = binarySearch(mergeSongs, 0, songs.size() - 1, sortBy, target);
                vector<Song> filteredSongs2 = binarySearch(quickSongs, 0, songs.size() - 1, sortBy, target);

                // Output
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
                // Conduct binary search on the vectors sorted by merge sort and quick sort in order to filter them by duration
                string target = releaseDate;
                vector<Song> filteredSongs1 = binarySearch(mergeSongs, 0, songs.size() - 1, sortBy, target);
                vector<Song> filteredSongs2 = binarySearch(quickSongs, 0, songs.size() - 1, sortBy, target);

                // Output
                cout << "\nTop 10 songs sorted by " << sortBy << " using Merge Sort:\n";
                int count = 0;
                for (int i = 0; i < 5000; ++i) {
                    const Song &s = filteredSongs2[i];
                    if (s.getReleaseDate() >= releaseDate) {
                        cout << s.getTitle() << " | " << s.getArtist()
                         << " | " << s.getGenre()
                         << " | " << s.getReleaseDate()
                         << " | " << s.getDuration()
                         << "s | " << s.getPopularity() << endl;
                        count++;
                    }
                    if (count == 10) {break;}
                }
                cout << "\nTop 10 songs sorted by " << sortBy << " using Quick Sort:\n";
                count = 0;
                for (int i = 0; i < 5000; ++i) {
                    const Song &s = filteredSongs2[i];
                    if (s.getReleaseDate() >= releaseDate) {
                        cout << s.getTitle() << " | " << s.getArtist()
                         << " | " << s.getGenre()
                         << " | " << s.getReleaseDate()
                         << " | " << s.getDuration()
                         << "s | " << s.getPopularity() << endl;
                        count++;
                    }
                    if (count == 10) {break;}
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
