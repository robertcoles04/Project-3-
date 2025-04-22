#pragma once
#include "Song.h"
#include <vector>
#include <type_traits>

using namespace std;

// For RD
vector<Song> binaryRD(std::vector<Song> songs, string target, int low, int high) {
    vector<Song> result;
    if (high >= low) {
        int mid = (high - low) / 2 + low;

        if (target == songs[mid].getReleaseDate()) {
            if (target > "2018-1-1") {
                for (int i = 0; i < 5000; i++) {
                    //Add the 10 songs surrounding mid
                    result.push_back(songs[mid - i]);
                }
            }
            else if (target < "2002-1-1") {
                for (int i = 0; i < 5000; i++) {
                    //Add the 10 songs surrounding mid
                    result.push_back(songs[mid + i]);
                }
            }
            else {
                for (int i = 0; i < 5000; i++) {
                    //Add the 10 songs surrounding mid
                    result.push_back(songs[mid - 2500 + i]);
                }
            }
            return result;
        }

        if (songs[mid].getReleaseDate() > target) {
            return binaryRD(songs, target, low, mid - 1);
        }
        if (songs[mid].getReleaseDate() < target) {
            return binaryRD(songs, target, mid + 1, high);
        }
    }
    return result;
}

// For Duration
vector<Song> binaryDuration(std::vector<Song> songs, int target, int low, int high) {
    vector<Song> result;
    if (high >= low) {
        int mid = (high - low) / 2 + low;

        if (target == songs[mid].getDuration()) {
            if (target > 250) {
                for (int i = 0; i < 5000; i++) {
                    //Add the 10 songs surrounding mid
                    result.push_back(songs[mid - i]);
                }
            }
            else if (target < 180) {
                for (int i = 0; i < 5000; i++) {
                    //Add the 10 songs surrounding mid
                    result.push_back(songs[mid + i]);
                }
            }
            else {
                for (int i = 0; i < 5000; i++) {
                    //Add the 10 songs surrounding mid
                    result.push_back(songs[mid - 2500 + i]);
                }
            }
            return result;
        }

        if (songs[mid].getDuration() > target) {
            return binaryDuration(songs, target, low, mid - 1);
        }
        if (songs[mid].getDuration() < target) {
            return binaryDuration(songs, target, mid + 1, high);
        }
    }
    return result;
}

// For Popularity
vector<Song> binaryPop(std::vector<Song> songs, int target, int low, int high) {
    vector<Song> result;
    if (high >= low) {
        int mid = (high - low) / 2 + low;

        if (target == songs[mid].getPopularity()) {
            if (target > 80) {
                for (int i = 0; i < 5000; i++) {
                    //Add the 10 songs surrounding mid
                    result.push_back(songs[mid - i]);
                }
            }
            else if (target < 20) {
                for (int i = 0; i < 5000; i++) {
                    //Add the 10 songs surrounding mid
                    result.push_back(songs[mid + i]);
                }
            }
            else {
                for (int i = 0; i < 5000; i++) {
                    //Add the 10 songs surrounding mid
                    result.push_back(songs[mid - 2500 + i]);
                }
            }
            return result;
        }

        if (songs[mid].getPopularity() > target) {
            return binaryPop(songs, target, low, mid - 1);
        }
        if (songs[mid].getPopularity() < target) {
            return binaryPop(songs, target, mid + 1, high);
        }
    }
    return result;
}

//Conversion helpers
std::string convertToString(const std::string& val) {
    return val;
}

template <typename T>
std::string convertToString(const T& val) {
    return std::to_string(val);
}

int convertToInt(int val) {
    return val;
}

int convertToInt(const std::string& val) {
    return std::stoi(val);
}

// CALL THIS. Input vector of song objects, 0 for low index, songs.size() - 1, attribute of song, and search item
template <typename T>
std::vector<Song> binarySearch(std::vector<Song>& songs, int low, int high, const std::string& type, T target) {
    if (type == "releaseDate") {
        std::string target1 = convertToString(target);
        return binaryRD(songs, target1, low, high);
    }

    if (type == "duration") {
        int target1 = convertToInt(target);
        return binaryDuration(songs, target1, low, high);
    }

    if (type == "popularity") {
        int target1 = convertToInt(target);
        return binaryPop(songs, target1, low, high);
    }
}
