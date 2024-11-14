#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Song
{
    char title[100];
    char singer[100];
    char movie[100];
    struct Song* next;
    struct Song* prev;
} Song;

typedef struct Playlist {
    Song* head;
    Song* tail;
    Song* current;
} Playlist;

Song* createSong(char* title, char* singer, char* movie)
{
    Song* newSong = (Song*)malloc(sizeof(Song));
    strcpy(newSong->title, title);
    strcpy(newSong->singer, singer);
    strcpy(newSong->movie, movie);
    newSong->next = NULL;
    newSong->prev = NULL;
    return newSong;
}

void initPlaylist(Playlist* playlist)
{
    playlist->head = NULL;
    playlist->tail = NULL;
    playlist->current = NULL;
}

void addSong(Playlist* playlist, char* title, char* singer, char* movie) {
    Song* newSong = createSong(title, singer, movie);
    if (playlist->head == NULL)
    {
        playlist->head = playlist->tail = playlist->current = newSong;
    }
    else
    {
        playlist->tail->next = newSong;
        newSong->prev = playlist->tail;
        playlist->tail = newSong;
    }
    printf("Song added: %s\n", title);
}
1
// Function to remove a song by title
void removeSong(Playlist* playlist, char* title)
{
    Song* temp = playlist->head;
    while (temp != NULL)
    {
        if (strcmp(temp->title, title) == 0)
        {
            if (temp == playlist->head)
            {
                playlist->head = temp->next;
                if (playlist->head) playlist->head->prev = NULL;
            }
            else if (temp == playlist->tail)
            {
                playlist->tail = temp->prev;
                if (playlist->tail) playlist->tail->next = NULL;
            }
            else
            {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
            if (playlist->current == temp) playlist->current = playlist->head; // Reset current if removed
            free(temp);
            printf("Song removed: %s\n", title);
            return;
        }
        temp = temp->next;
    }
    printf("Song not found: %s\n", title);
}

void playCurrentSong(Playlist* playlist)
{
    if (playlist->current != NULL)
    {
        printf("Playing: %s by %s from %s\n", playlist->current->title, playlist->current->singer, playlist->current->movie);
    }
    else
    {
        printf("No song in the playlist.\n");
    }
}

// Function to skip to the next song
void skipForward(Playlist* playlist) {
    if (playlist->current != NULL && playlist->current->next != NULL) {
        playlist->current = playlist->current->next;
        playCurrentSong(playlist);
    } else {
        printf("Reached the end of the playlist.\n");
    }
}

// Function to skip to the previous song
void skipBackward(Playlist* playlist) {
    if (playlist->current != NULL && playlist->current->prev != NULL) {
        playlist->current = playlist->current->prev;
        playCurrentSong(playlist);
    } else {
        printf("At the beginning of the playlist.\n");
    }
}

// Function to filter songs by singer or movie
void filterSongs(Playlist* playlist, char* filter, int bySinger) {
    Song* temp = playlist->head;
    printf("Filtered songs by %s: %s\n", (bySinger ? "singer" : "movie"), filter);
    while (temp != NULL) {
        if ((bySinger && strcmp(temp->singer, filter) == 0) || (!bySinger && strcmp(temp->movie, filter) == 0)) {
            printf("%s by %s from %s\n", temp->title, temp->singer, temp->movie);
        }
        temp = temp->next;
    }
}
int main() {
    Playlist playlist;
    initPlaylist(&playlist);

    int ch;
    char title[100], singer[100], movie[100], filter[100];

    do {
        printf("\n--- Playlist Manager ---\n");
        printf("1. Add Song\n2. Remove Song\n3. Play Current Song\n4. Skip Forward\n5. Skip Backward\n6. Filter Songs by Singer\n7. Filter Songs by Movie\n8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        getchar();

        switch (ch) {
            case 1:
                printf("Enter song title: ");
                fgets(title, 100, stdin);
                title[strlen(title) - 1] = '\0'; // Remove trailing newline
                printf("Enter singer name: ");
                fgets(singer, 100, stdin);
                singer[strlen(singer) - 1] = '\0';
                printf("Enter movie name: ");
                fgets(movie, 100, stdin);
                movie[strlen(movie) - 1] = '\0';
                addSong(&playlist, title, singer, movie);
                break;
            case 2:
                printf("Enter song title to remove: ");
                fgets(title, 100, stdin);
                title[strlen(title) - 1] = '\0';
                removeSong(&playlist, title);
                break;
            case 3:
                playCurrentSong(&playlist);
                break;
            case 4:
                skipForward(&playlist);
                break;
            case 5:
                skipBackward(&playlist);
                break;
            case 6:
                printf("Enter singer name to filter: ");
                fgets(filter, 100, stdin);
                filter[strlen(filter) - 1] = '\0';
                filterSongs(&playlist, filter, 1);
                break;
            case 7:
                printf("Enter movie name to filter: ");
                fgets(filter, 100, stdin);
                filter[strlen(filter) - 1] = '\0';
                filterSongs(&playlist, filter, 0);
                break;
            case 8:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (ch!= 8);

    return 0;
}
