# Go-Board-Game

This code implements the board game Go. Originally written in C as a personal project, I am currently in the process of porting it to C++.

For a set of rules, go to https://www.wikihow.com/Play-Go

In summary:

Black and white take turns to place stones on the board in order to capture territory (space on the board completely enclosed by your own stones).

Stones are only removed from the board once they are surrounded (all orthogonal spaces adjacent to them are full of the opponent's stones).

Stones of the same colour that are orthogonally next to each other form a stone group, and can be taken as one, but are also harder to take as they require more stones to surround. When stones are taken, the taking player recevies points equal to stones taken.

The game ends when both players pass.

Because black always starts, white recevies an extra 6.5 points, known as komi.





The game uses a Board class that consists of (for a 9x9 board) 81 instances of a Stones class. Stones know where they are, what group they belong to, and which spaces need to be filled in order for them to be taken.



Future plans include:

Implementing a scoring system using a depth-first search utilising a hashset.

Converting the implementation of the stone groups functionality to just evaluate the board each turn, in order to improve space complexity.
