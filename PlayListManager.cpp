#include <bits/stdc++.h>
using namespace std;

struct Node
{
    char name[100];
    char singer[100];
    char movie[100];
    Node *next;
    Node *prev;
};

struct Playlist
{
    Node *head;
    Node *last;
    Node *current;
};

bool equalsIgnoreCase(const char *a, const char *b)
{
    return strcasecmp(a, b) == 0;
}

Node* createSong(char *name, char *singer, char *movie)
{
    Node *newSong = new Node();
    strcpy(newSong->name, name);
    strcpy(newSong->singer, singer);
    strcpy(newSong->movie, movie);
    newSong->next = NULL;
    newSong->prev = NULL;
    return newSong;
}

void initializePlaylist(Playlist &playlist)
{
    playlist.head = NULL;
    playlist.last = NULL;
    playlist.current = NULL;
}

void addSong(Playlist &playlist, char *name, char *singer, char *movie)
{
    Node *newSong = createSong(name, singer, movie);
    if (playlist.head == NULL)
    {
        playlist.head = newSong;
        playlist.last = newSong;
        playlist.current = newSong;
    }
    else
    {
        playlist.last->next = newSong;
        newSong->prev = playlist.last;
        playlist.last = newSong;
    }
    cout << "Song added: " << name << endl;
}

void playSong(Playlist &playlist, char *name)
{
    Node *temp = playlist.head;
    while (temp != NULL)
    {
        if (equalsIgnoreCase(temp->name, name))
        {
            playlist.current = temp;
            cout << "Now playing: " << temp->name << " from " << temp->movie << " by " << temp->singer << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Song with name '" << name << "' not found." << endl;
}

void removeSong(Playlist &playlist, char *title)
{
    Node *temp = playlist.head;
    while (temp != NULL)
    {
        if (equalsIgnoreCase(temp->name, title))
        {
            if (temp->prev) temp->prev->next = temp->next;
            if (temp->next) temp->next->prev = temp->prev;
            if (temp == playlist.head) playlist.head = temp->next;
            if (temp == playlist.last) playlist.last = temp->prev;
            if (temp == playlist.current) playlist.current = temp->next ? temp->next : temp->prev;
            cout << "Removed song: " << temp->name << endl;
            free(temp);
            return;
        }
        temp = temp->next;
    }
    cout << "Song with name '" << title << "' not found." << endl;
}

void nextSong(Playlist &playlist)
{
    if (playlist.current != NULL && playlist.current->next != NULL)
    {
        playlist.current = playlist.current->next;
        cout << "Now playing: " << playlist.current->name << " from " << playlist.current->movie << " by " << playlist.current->singer << endl;
    }
    else
    {
        cout << "No next song." << endl;
    }
}

void previousSong(Playlist &playlist)
{
    if (playlist.current != NULL && playlist.current->prev != NULL)
    {
        playlist.current = playlist.current->prev;
        cout << "Now playing: " << playlist.current->name << " from " << playlist.current->movie << " by " << playlist.current->singer << endl;
    }
    else
    {
        cout << "No previous song." << endl;
    }
}

void displayPlaylist(Playlist &playlist)
{
    if (playlist.head == NULL)
    {
        cout << "Playlist is empty." << endl;
        return;
    }

    for (Node *i = playlist.head; i != NULL; i = i->next)
    {
        for (Node *j = i->next; j != NULL; j = j->next)
        {
            if (strcasecmp(i->name, j->name) > 0)
            {
                swap(i->name, j->name);
                swap(i->singer, j->singer);
                swap(i->movie, j->movie);
            }
        }
    }

    cout << "\nComplete Playlist:\n";
    cout << "-------------------------------------------------------------------------------------\n";
    cout << "| " << left << setw(25) << "Name" << "| " << setw(25) << "Movie" << "| " << setw(25) << "Singer" << "|\n";
    cout << "-------------------------------------------------------------------------------------\n";

    for (Node *temp = playlist.head; temp != NULL; temp = temp->next)
    {
        cout << "| " << left << setw(25) << temp->name << "| " << setw(25) << temp->movie << "| " << setw(25) << temp->singer << "|\n";
    }

    cout << "-------------------------------------------------------------------------------------\n";
}

void filterSongs(Playlist &playlist)
{
    pair<string, string> ch;

    cout << "Filter by (singer/movie): ";
    getline(cin, ch.first);

    cout << "Enter name of " << ch.first << ": ";
    getline(cin, ch.second);

    Node *temp = playlist.head;
    bool found = false;

    cout << "\nFiltered songs by " << ch.first << " (" << ch.second << "):\n";
    cout << "-------------------------------------------------------------------------------------\n";
    cout << "| " << left << setw(25) << "Name" << "| " << setw(25) << "Movie" << "| " << setw(25) << "Singer" << "|\n";
    cout << "-------------------------------------------------------------------------------------\n";

    while (temp!=NULL)
    {
        if ((equalsIgnoreCase(ch.first.c_str(), "singer") && equalsIgnoreCase(temp->singer, ch.second.c_str())) ||
            (equalsIgnoreCase(ch.first.c_str(), "movie") && equalsIgnoreCase(temp->movie, ch.second.c_str())))
        {
            cout << "| " << left << setw(25) << temp->name << "| " << setw(25) << temp->movie << "| " << setw(25) << temp->singer << "|\n";
            found = true;
        }
        temp = temp->next;
    }

    if (found==NULL)
    {
        cout << "| " << left << setw(76) << "No songs found for the given filter." << "|\n";
    }

    cout << "-----------------------------------------------------------------------------------------\n";
}

int main()
{
    Playlist playlist;
    initializePlaylist(playlist);

    int ch;
    char name[100], singer[100], movie[100];

    while (true)
    {
        cout << "\n------------ Playlist Manager ------------\n";
        cout << "1. Add Song\n";
        cout << "2. Remove Song by Name\n";
        cout << "3. Play Song by Name\n";
        cout << "4. Next Song\n";
        cout << "5. Previous Song\n";
        cout << "6. Filter Songs\n";
        cout << "7. Display Playlist\n";
        cout << "8. Exit\n";
        cout << "Enter choice: ";
        cin >> ch;
        cin.ignore();

        switch (ch)
        {
            case 1:
                cout << "Enter song name: ";
                cin.getline(name, 100);

                cout << "Enter singer: ";
                cin.getline(singer, 100);

                cout << "Enter movie: ";
                cin.getline(movie, 100);

                addSong(playlist, name, singer, movie);
                break;
            case 2:
                cout << "Enter the name of the song to remove: ";
                cin.getline(name, 100);
                removeSong(playlist, name);
                break;
            case 3:
                cout << "Enter the name of the song to play: ";
                cin.getline(name, 100);
                playSong(playlist, name);
                break;
            case 4:
                nextSong(playlist);
                break;
            case 5:
                previousSong(playlist);
                break;
            case 6:
                filterSongs(playlist);
                break;
            case 7:
                displayPlaylist(playlist);
                break;
            case 8:
                exit(0);
            default:
                cout << "Invalid choice! Try again." << endl;
        }
    }

    return 0;
}
