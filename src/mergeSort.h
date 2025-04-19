#pragma once
#include "Song.h"
#include <vector>
using std::vector;

//Algorithm Credit: Module 8 Merge Sort Slideshow

void merge(vector<Song>& songs, int left, int mid, int right, const string& comparison)
{
    // Create X ← arr[left..mid] & Y ← arr[mid+1..right]
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Song> X(n1);
    vector<Song> Y(n2);

    for (int i = 0; i < n1; i++)
        X[i] = songs[left + i];
    for (int j = 0; j < n2; j++)
        Y[j] = songs[mid + 1 + j];

    // Merge the arrays X and Y into arr
    int i, j, k;
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2)
    {
        if (comparison == "duration") {
            if (X[i].getDuration() <= Y[j].getDuration())
            {
                songs[k] = X[i];
                i++;
            }
            else
            {
                songs[k] = Y[j];
                j++;
            }
        }
        else if (comparison == "release date") {
            if (X[i].getReleaseDate() <= Y[j].getReleaseDate())
            {
                songs[k] = X[i];
                i++;
            }
            else
            {
                songs[k] = Y[j];
                j++;
            }
        }
        else if (comparison == "popularity") {
            if (X[i].getPopularity() <= Y[j].getPopularity())
            {
                songs[k] = X[i];
                i++;
            }
            else
            {
                songs[k] = Y[j];
                j++;
            }
        }
        k++;
    }
    // When we run out of elements in either X or Y append the remaining elements
    while (i < n1)
    {
        songs[k] = X[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        songs[k] = Y[j];
        j++;
        k++;
    }
}

void mergeSort(vector<Song>& songs, int left, int right, const string& comparison)
{
    if (left < right)
    {
        // m is the point where the array is divided into two subarrays
        int mid = left + (right - left) / 2;

        mergeSort(songs, left, mid, comparison);
        mergeSort(songs, mid + 1, right, comparison);

        // Merge the sorted subarrays
        merge(songs, left, mid, right, comparison);
    }
}