#pragma once
#include "Song.h"
#include <vector>

using namespace std;

// For genre
void quickGenre(std::vector<Song>& songs, int low, int high) {
    if (low < high) {
        int pivot = low;
        string val = songs[pivot].getGenre();

        for (int i = low + 1; i <= high; i++) {
            if (songs[i].getGenre() < val) {
                pivot++;
                std::swap(songs[i], songs[pivot]);
            }
        }
        std::swap(songs[low], songs[pivot]);

        quickGenre(songs, low, pivot - 1);
        quickGenre(songs, pivot + 1, high);
    }
}

// For RD
void quickRD(std::vector<Song>& songs, int low, int high) {
    if (low < high) {
        int pivot = low;
        string val = songs[pivot].getReleaseDate();

        for (int i = low + 1; i <= high; i++) {
            if (songs[i].getReleaseDate() < val) {
                pivot++;
                std::swap(songs[i], songs[pivot]);
            }
        }
        std::swap(songs[low], songs[pivot]);

        quickRD(songs, low, pivot - 1);
        quickRD(songs, pivot + 1, high);
    }
}

// For Duration
void quickDuration(std::vector<Song>& songs, int low, int high) {
    if (low < high) {
        int pivot = low;
        int val = songs[pivot].getDuration();

        for (int i = low + 1; i <= high; i++) {
            if (songs[i].getDuration() < val) {
                pivot++;
                std::swap(songs[i], songs[pivot]);
            }
        }
        std::swap(songs[low], songs[pivot]);

        quickDuration(songs, low, pivot - 1);
        quickDuration(songs, pivot + 1, high);
    }
}

// For Popularity
void quickPop(std::vector<Song>& songs, int low, int high) {
    if (low < high) {
        int pivot = low;
        int val = songs[pivot].getPopularity();

        for (int i = low + 1; i <= high; i++) {
            if (songs[i].getPopularity() < val) {
                pivot++;
                std::swap(songs[i], songs[pivot]);
            }
        }
        std::swap(songs[low], songs[pivot]);

        quickPop(songs, low, pivot - 1);
        quickPop(songs, pivot + 1, high);
    }
}

// CALL THIS. Input vector of song objects, 0 for low index, songs.size() - 1, and attribute of song
void quickSort(std::vector<Song>& songs, int low, int high, const string& type) {
    // Will sort the song objects based on whatever attribute
    if (type == "genre") {
        quickGenre(songs, low, high);
    }

    if (type == "release date") {
        quickRD(songs, low, high);
    }

    if (type == "duration") {
        quickDuration(songs, low, high);
    }

    if (type == "popularity") {
        quickPop(songs, low, high);
    }
}
