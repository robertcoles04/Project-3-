#pragma once
#include "Song.h"
#include <vector>

using namespace std;

// For genre
int binaryGenre(std::vector<Song> songs, string target, int low, int high) {
    if (high >= low) {
        int mid = (high - low) / 2 + low;

        if (target == songs[mid].getGenre()) {return mid;}

        if (songs[mid].getGenre() > target) {
            return binaryGenre(songs, target, low, mid - 1);
        }
        if (songs[mid].getGenre() < target) {
            return binaryGenre(songs, target, mid + 1, high);
        }
    }
    return -1;
}

// For RD
int binaryRD(std::vector<Song> songs, string target, int low, int high) {
    if (high >= low) {
        int mid = (high - low) / 2 + low;

        if (target == songs[mid].getReleaseDate()) {return mid;}

        if (songs[mid].getReleaseDate() > target) {
            return binaryRD(songs, target, low, mid - 1);
        }
        if (songs[mid].getReleaseDate() < target) {
            return binaryRD(songs, target, mid + 1, high);
        }
    }
    return -1;
}

// For Duration
int binaryDuration(std::vector<Song> songs, int target, int low, int high) {
    if (high >= low) {
        int mid = (high - low) / 2 + low;

        if (target == songs[mid].getDuration()) {return mid;}

        if (songs[mid].getDuration() > target) {
            return binaryDuration(songs, target, low, mid - 1);
        }
        if (songs[mid].getDuration() < target) {
            return binaryDuration(songs, target, mid + 1, high);
        }
    }
    return -1;
}

// For Popularity
vector<Song> binaryPop(std::vector<Song> songs, int target, int low, int high) {
    vector<Song> result;
    if (high >= low) {
        int mid = (high - low) / 2 + low;

        if (target == songs[mid].getPopularity()) {
            for (int i = 0; i < 10; i++) {
                //Add the 10 songs surrounding mid
                result.push_back(songs[mid - 5 + i]);
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
    //NEED TO RETURN VECTOR

    //Search based on attribute
    if (type == "genre") {
        binaryGenre(songs, target, low, high);
    }

    if (type == "release date") {
        binaryRD(songs, target, low, high);
    }

    if (type == "duration") {
        binaryDuration(songs, target, low, high);
    }

    if (type == "popularity") {
        vector<Song> popularitySongs;
        popularitySongs = binaryPop(songs, target, low, high);
    }

    //Return combined songs
    if (type == "all") {

    }
}
