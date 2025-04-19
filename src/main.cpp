#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

struct Song{
    string title;
    string artist;
    string album;
    string genre;
    string releasedate;
    int duration;
    int popularity;

};

std::vector<std::vector<int>> createAdjMatrix( std::vector<Song>& songs) {
    size_t n = songs.size();
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n, 0));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (i != j and abs(songs[i].popularity - songs[j].popularity) < 0.1f) {
                matrix[i][j] = 1;
            }
        }
    }

    return matrix;
}
int main(){
    string title;
    string artist;
    string album;
    string genre;
    string releasedate;
    int duration;
    int popularity;
    ifstream file("music.csv");
    if (!file.is_open()) {
        cerr << "Failed to open music.csv" << endl;
        return 1;
    }
cout << "What type of genre do you like?" << endl;
    cin >> genre;
    cout << genre << endl;
    return 0;
}
