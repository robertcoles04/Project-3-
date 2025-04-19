#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>
using std::string;

class Song
{
    string title;
    string artist;
    string album;
    string genre;
    string releaseDate;

    int numDaysReleasedAfter2000{};
    int duration{};
    int popularity{};

    void setNumDaysReleasedAfter2000(){
        std::tm t1 = {};
        std::tm t2 = {};

        // Parse input date (yyyy-mm-dd)
        std::istringstream ss(releaseDate);
        ss >> std::get_time(&t1, "%Y-%m-%d");

        // Set reference date to January 1st, 2000
        t2.tm_year = 100; // year since 1900
        t2.tm_mon = 0;            // January
        t2.tm_mday = 1;           // 1st

        std::time_t time1 = std::mktime(&t1);
        std::time_t time2 = std::mktime(&t2);

        // Calculate the difference in seconds then convert to days
        double difference = std::difftime(time1, time2) / (60 * 60 * 24);

        numDaysReleasedAfter2000 = static_cast<int>(difference);
    }

public:
    Song()= default;
    Song(const string &title, const string &artist, const string &album, const string &genre,
         const string &releaseDate, const string& duration, const string& popularity){
        this->title = title;
        this->artist = artist;
        this->album = album;
        this->genre = genre;
        this->releaseDate = releaseDate;
        setNumDaysReleasedAfter2000();
        this->duration = stoi(duration);
        this->popularity = stoi(popularity);
    }

    string getTitle() const{return title;}
    string getArtist() const{return artist;}
    string getAlbum() const{return album;}
    string getGenre() const{return genre;}
    string getReleaseDate() const{return releaseDate;}
    int getNumDaysReleasedAfter2000() const{return numDaysReleasedAfter2000;}
    int getDuration() const{return duration;}
    int getPopularity() const{return popularity;}

    void setTitle(const string &title){this->title = title;}
    void setArtist(const string &artist){this->artist = artist;}
    void setAlbum(const string &album){this->album = album;}
    void setGenre(const string &genre){this->genre = genre;}
    void setReleaseDate(const string &releaseDate){
      this->releaseDate = releaseDate;
      setNumDaysReleasedAfter2000();
    }
    void setDuration(const string& duration){this->duration = stoi(duration);}
    void setPopularity(const string& popularity){this->popularity = stoi(popularity);}
};