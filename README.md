Playlist Manager
A simple C++ Playlist Manager that allows users to manage a collection of songs. This project demonstrates the use of basic data structures, pointers, and functions to create a linked list-based playlist system with various functionalities like adding, removing, playing, and filtering songs.

Features
Add Song: Add a song to the playlist with details such as song name, singer, and movie.
Remove Song by Name: Remove a song from the playlist by specifying its name.
Play Song by Name: Play a specific song from the playlist.
Next Song: Move to the next song in the playlist.
Previous Song: Move to the previous song in the playlist.
Filter Songs: Filter songs by singer or movie name to display only the songs that match the specified criteria.
Display Playlist: Display the complete playlist sorted alphabetically by song name.
Project Structure
This project utilizes a doubly linked list structure where each song is represented by a Node. Each Node stores the song's name, singer, and movie, along with pointers to the next and previous songs. The playlist itself is represented by a Playlist struct that maintains pointers to the head, last, and current nodes in the list.

Technologies Used
C++ Standard Library
Linked List Data Structure
