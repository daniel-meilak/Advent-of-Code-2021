## Day 6

Ended up writing a another version for today when I realised the vector of stages does not need to be rotated. Instead we just need to keep track of which day is "day 0" i.e. which group of fish become newborns and also reset to stage 6.

The code in [day_6.cpp](day_6.cpp) is slightly longer due to the `if` statements however timed with `<chrono>` the program runs ~ 3 times faster, with [day_6_old.cpp](day_6_old.cpp) running for `2.2` microseconds and [day_6.cpp](day_6.cpp) for `0.8`.