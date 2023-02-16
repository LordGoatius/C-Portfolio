#include "Playlist.h"

Playlist::Playlist(string name) {
    playlistName = name;
}

void Playlist::AddSong(Song* newSong) {
    playlist.push_back(newSong);
}

void Playlist::PlayPlaylist() {
    for (int i = 0; i < playlist.size(); i++) {
        playlist.at(i)->PlaySong();
    }
}

string Playlist::GetName() {
    return playlistName;
}

void Playlist::RemoveSong(Song* song) {
    for (unsigned i = 0; i < playlist.size(); i++) {
        if (playlist.at(i) == song) {
            playlist.erase(playlist.begin() + i);
        }
    }
}

void Playlist::RemoveSong(int index) {
    playlist.erase(playlist.begin() + index);
}

void Playlist::ListSongs() {
    for (unsigned int i = 0; i < playlist.size(); i++) {
        cout << i << ": " << playlist.at(i)->GetTitle() << endl;
    }
}

bool Playlist::IsInPlaylist(Song* song) {
    for (unsigned i = 0; i < playlist.size(); i++) {
        if (playlist.at(i) == song) {
            return true;
        }
    }
    return false;
}