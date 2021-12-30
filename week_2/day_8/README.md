## Day 8

Couldnt think of a clever way to solve todays puzzle, so I manually found the differences between numbers, which segments are common/missinge between digits and coded out a [method](day_8_old.cpp) which works out the line bit by bit.

After looking at reddit, particularly [this solution](https://www.reddit.com/r/adventofcode/comments/rbj87a/2021_day_8_solutions/hnoxpwk/), I realised how it is possible to solve the problem efficiently, and implemented it in [day_8.cpp](day_8.cpp). 

Each digit is made up of a different combination of segments. The segments in turn occur n times in the digits 0-9. Adding together the number of occurences of each segment in a digit, multiplied by the n occurences of each segment in 0-9, gives a unique ID which can be tied to a digit.

Hence, it is possible to count the occurences of the mixed segment labels and automatically derive which digits are represents by finding this ID.

Below the unique IDs for each digit are given:
| Digit |  ID   |
| :---: | :---: |
|   0   |  42   |
|   1   |  17   |
|   2   |  34   |
|   3   |  39   |
|   4   |  30   |
|   5   |  37   |
|   6   |  41   |
|   7   |  25   |
|   8   |  49   |
|   9   |  45   |
