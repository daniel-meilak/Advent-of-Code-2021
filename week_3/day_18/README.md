## Day 18

I made the terrible choice of using `std::list<char>` as I thought it would be more performant with many character insertions and deletions, however this deprived me of convenient `std::string` functions as well as the use of `<regex>` which I think would have made everything a lot easier.

To add to this there is also a bunch of impenetrable iterator manipulation, including using `reverse_iterators`, which makes understanding the code even harder. I think I will return to this code later and redo everything with strings, and find other ways to improve performance.