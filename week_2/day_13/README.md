## Day 13

I spent some time thinking about this puzzle after solving it the straight forward way. I assumed that there must be a way to know which points in the grid collapse onto all others without doing any "folding". So I took out some paper and worked out the patters (with help from Wolfram Alpha). In the end, I found this relation between points on a folding grid:

In 1D, if you have a line of length `S`, the box `line[x]` is collapsed onto by all boxes: `line[ 0.5(2S*n + (S-2x-2)(-1)^n - (S+2)) ]` where `n` is the index for each repeating segment. `n=1` for the final collapsed line and `n=2,3,4...` for repeated lines.

This method is implemented in [day_13_alt_part_2.cpp](day_13_alt_part_2.cpp), though it actaully runs slower than the straight forward solution. I assume this is because by folding you actually reduce the number of checked grid positions in half every time you fold the grid, making the total number of checked boxes not much higher, and also using the above function so many times has its own cost.