## Day 18

I made the terrible choice of using `std::list<char>` as I thought it would be more performant with many character insertions and deletions, however this deprived me of convenient `std::string` functions as well as the use of `<regex>` which I think would have made everything a lot easier.