#ifndef MAINLAB_SONG_H
#define MAINLAB_SONG_H

#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Song {
public:
    Song(string inputTitle = "", string inputFirstLine = "");
    string GetTitle();
    string GetFirstLine();
    int GetPlayed();
    void PlaySong();
private:
    string title;
    string firstLine;
    int played;
};

#endif 
