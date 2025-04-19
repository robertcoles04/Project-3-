#ifndef SONG_H
#define SONG_H

#include <string>
using std::string;

class Song
{
    string title;
    string artist;
    string album;
    string genre;
    string releaseDate;

    int numDaysReleasedAfter2000;
    int duration;
    int popularity;

    void setNumDaysReleasedAfter2000();

public:
    Song();
    Song(const string &title, const string &artist, const string &album, const string &genre,
         const string &releaseDate, const string& duration, const string& popularity);

    string getTitle() const;
    string getArtist() const;
    string getAlbum() const;
    string getGenre() const;
    string getReleaseDate() const;
    int getNumDaysReleasedAfter2000() const;
    int getDuration() const;
    int getPopularity() const;

    void setTitle(const string &title);
    void setArtist(const string &artist);
    void setAlbum(const string &album);
    void setGenre(const string &genre);
    void setReleaseDate(const string &releaseDate);
    void setDuration(const string& duration);
    void setPopularity(const string& popularity);
};

#endif //SONG_H
