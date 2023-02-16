#include <iostream>
#include <string>
#include <vector>

#include "Playlist.h"
using namespace std;

string GetUserString(const string& prompt);
int GetUserInt(const string& prompt);

int main() {
    cout << "Welcome to the Firstline Player!  Enter options to see menu options." << endl << endl;

    vector<Song*> library;
    vector<Playlist> playlistLibrary;

    string userMenuChoice = "none";
    bool continueMenuLoop = true;

    while (continueMenuLoop) {
        userMenuChoice = GetUserString("Enter your selection now: ");

        //Add a song
        if (userMenuChoice == "add") {
            const string DONE_KEYWORD = "DONE";
            cout << "Enter songs' names and first lines"
                << " (type \"" << DONE_KEYWORD << "\" when done):" << endl;

            string songName = "none";
            string firstLine = "none";

            songName = GetUserString("Song Name: ");
            while (songName != DONE_KEYWORD) {
                firstLine = GetUserString("Song's first line: ");

                Song* newSong = new Song(songName, firstLine);
                library.push_back(newSong);

                songName = GetUserString("Song Name: ");
            }
        }
        //List all songs
        else if (userMenuChoice == "list") {
            for (unsigned int i = 0; i < library.size(); i++) {
                cout << library.at(i)->GetTitle() << ": \"" << library.at(i)->GetFirstLine()
                    << "\", " << library.at(i)->GetPlayed() << " play(s)." << endl;
            }
        }
        else if (userMenuChoice == "addp") {
            string name = GetUserString("Playlist name: ");
            Playlist newPlaylist(name);
            playlistLibrary.push_back(newPlaylist);
        }
        else if (userMenuChoice == "addsp") {
            for (unsigned int i = 0; i < playlistLibrary.size(); i++) {
                cout << i << ": " << playlistLibrary.at(i).GetName() << endl;
            }
            int playlistIndex = GetUserInt("Pick a playlist index number: ");

            for (unsigned int i = 0; i < library.size(); i++) {
                cout << i << ": " << library.at(i)->GetTitle() << endl;
            }
            int songIndex = GetUserInt("Pick a song index number: ");

            playlistLibrary.at(playlistIndex).AddSong(library.at(songIndex));
        }
        else if (userMenuChoice == "listp") {
            for (unsigned i = 0; i < playlistLibrary.size(); i++) {
                cout << i << ": " << playlistLibrary.at(i).GetName() << endl;
            }
        }
        else if (userMenuChoice == "play") {
            for (unsigned int i = 0; i < playlistLibrary.size(); i++) {
                cout << i << ": " << playlistLibrary.at(i).GetName() << endl;
            }
            int playlistIndex = GetUserInt("Pick a playlist index number: ");

            cout << "Playing songs from playlist: " << playlistLibrary.at(playlistIndex).GetName() << endl;
            playlistLibrary.at(playlistIndex).PlayPlaylist();
        }
        else if (userMenuChoice == "remp") {
            for (unsigned int i = 0; i < playlistLibrary.size(); i++) {
                cout << i << ": " << playlistLibrary.at(i).GetName() << endl;
            }
            int playlistIndex = GetUserInt("Pick a playlist index number to remove: ");

            playlistLibrary.erase(playlistLibrary.begin() + playlistIndex);
        }
        else if (userMenuChoice == "remsp") {
            for (unsigned int i = 0; i < playlistLibrary.size(); i++) {
                cout << i << ": " << playlistLibrary.at(i).GetName() << endl;
            }
            int playlistIndex = GetUserInt("Pick a playlist index number: ");

            playlistLibrary.at(playlistIndex).ListSongs();
            
            int songIndex = GetUserInt("Pick a song index number to remove: ");

            playlistLibrary.at(playlistIndex).RemoveSong(songIndex);
        }
        else if (userMenuChoice == "remsl") {
            for (unsigned int i = 0; i < library.size(); i++) {
                cout << i << ": " << library.at(i)->GetTitle() << endl;
            }
            int songIndex = GetUserInt("Pick a song index number to remove: ");

            for (unsigned i = 0; i < playlistLibrary.size(); i++) {
                if (playlistLibrary.at(i).IsInPlaylist(library.at(songIndex))) {
                    playlistLibrary.at(i).RemoveSong(library.at(songIndex));
                }
            }

            delete library.at(songIndex); //free memory
            library.erase(library.begin() + songIndex);
        }
        else if (userMenuChoice == "options") {
            cout << "add      Adds a list of songs to the library" << endl
                << "list     Lists all the songs in the library" << endl
                << "addp     Adds a new playlist" << endl
                << "addsp    Adds a song to a playlist" << endl
                << "listp    Lists all the playlists" << endl
                << "play     Plays a playlist" << endl
                << "remp     Removes a playlist" << endl
                << "remsp    Removes a song from a playlist" << endl
                << "remsl    Removes a song from the library (and all playlists)" << endl
                << "options  Prints this options menu" << endl
                << "quit     Quits the program" << endl << endl;
        }
        else if (userMenuChoice == "quit") {
            cout << "Goodbye!" << endl;
            for (int i = 0; i < library.size(); i++) {
                delete library.at(0); //free memory
                library.erase(library.begin());
            }
            continueMenuLoop = false;
        }
        else {
            cout << "add      Adds a list of songs to the library" << endl
                << "list     Lists all the songs in the library" << endl
                << "addp     Adds a new playlist" << endl
                << "addsp    Adds a song to a playlist" << endl
                << "listp    Lists all the playlists" << endl
                << "play     Plays a playlist" << endl
                << "remp     Removes a playlist" << endl
                << "remsp    Removes a song from a playlist" << endl
                << "remsl    Removes a song from the library (and all playlists)" << endl
                << "options  Prints this options menu" << endl
                << "quit     Quits the program" << endl << endl;
        }
    }

    return 0;
}


string GetUserString(const string& prompt) {
    string userAnswer = "none";

    cout << prompt;
    getline(cin, userAnswer);
    cout << endl;
    return userAnswer;
}
int GetUserInt(const string& prompt) {
    int userAnswer = 0;

    cout << prompt;
    cin >> userAnswer;
    cin.ignore();
    cout << endl;
    return userAnswer;
}
