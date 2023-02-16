#include "Song.h"

Song::Song(string inputTitle, string inputFirstLine) {
    title = inputTitle;
    firstLine = inputFirstLine;
    played = 0;
}

string Song::GetTitle() {
    return title;
}
void Song::PlaySong() {
    played++;
    cout << firstLine << endl;
}

string Song::GetFirstLine() {
    return firstLine;
}

int Song::GetPlayed() {
    return played;
}


