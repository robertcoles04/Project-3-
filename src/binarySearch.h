#pragma once
#include "Song.h"
#include <vector>
#include <type_traits>

using namespace std;

// For genre
vector<Song> binaryGenre(std::vector<Song> songs, string target, int low, int high) {
    vector<Song> result;
    if (high >= low) {
        int mid = (high - low) / 2 + low;

        if (target == songs[mid].getGenre()) {
            for (int i = 0; i < 100; i++) {
                //Add the 10 songs surrounding mid
                result.push_back(songs[mid - 50 + i]);
            }
            return result;
        }

        if (songs[mid].getGenre() > target) {
            return binaryGenre(songs, target, low, mid - 1);
        }
        if (songs[mid].getGenre() < target) {
            return binaryGenre(songs, target, mid + 1, high);
        }
    }
    return result;
}

// For RD
vector<Song> binaryRD(std::vector<Song> songs, string target, int low, int high) {
    vector<Song> result;
    if (high >= low) {
        int mid = (high - low) / 2 + low;

        if (target == songs[mid].getReleaseDate()) {
            for (int i = 0; i < 5000; i++) {
                //Add the 10 songs surrounding mid
                result.push_back(songs[mid - 2500 + i]);
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
            for (int i = 0; i < 5000; i++) {
                //Add the 10 songs surrounding mid
                result.push_back(songs[mid - 2500 + i]);
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
            for (int i = 0; i < 5000; i++) {
                //Add the 10 songs surrounding mid
                result.push_back(songs[mid - 2500 + i]);
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

// CALL THIS. Input vector of song objects, 0 for low index, songs.size() - 1, attribute of song, and search item
vector<Song> binarySearch(std::vector<Song>& songs, int low, int high, const string& type, auto target) {
    //Search based on attribute
    if (type == "genre") {
        string target1;
        if constexpr (std::is_same<decltype(target), std::string>::value) {
            target1 = target;
        }
        else {
            target1 = std::to_string(target);
        }
        vector<Song> genreSongs;
        genreSongs = binaryGenre(songs, target1, low, high);
        return genreSongs;
    }

    if (type == "releaseDate") {
        string target1;
        if constexpr (std::is_same<decltype(target), std::string>::value) {
            target1 = target;
        }
        else {
            target1 = std::to_string(target);
        }
        vector<Song> releaseSongs;
        releaseSongs = binaryRD(songs, target1, low, high);
        return releaseSongs;
    }

    if (type == "duration") {
        int target1;
        if constexpr (std::is_same<decltype(target), int>::value) {
            target1 = target;
        }
        else {
            target1 = stoi(target);
        }
        vector<Song> durationSongs;
        durationSongs = binaryDuration(songs, target1, low, high);
        return durationSongs;
    }

    if (type == "popularity") {
        int target1;
        if constexpr (std::is_same<decltype(target), int>::value) {
            target1 = target;
        }
        else {
            target1 = stoi(target);
        }
        vector<Song> popularitySongs;
        popularitySongs = binaryPop(songs, target1, low, high);
        return popularitySongs;
    }
}
