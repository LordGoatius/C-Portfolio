#ifndef MAINLAB_PLAYLIST_H
#define MAINLAB_PLAYLIST_H

#include "Song.h"

class Playlist {
public:
    Playlist(string name = "");
    void AddSong(Song* newSong);
    void PlayPlaylist();
    string GetName();
    void RemoveSong(Song* song);
    void RemoveSong(int index);
    void ListSongs();
    bool IsInPlaylist(Song* song);
private:
    string playlistName;
    vector<Song*> playlist;
};


#endif //UNTITLED6_PLAYLIST_H
