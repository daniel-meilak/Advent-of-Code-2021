## Day 1 

Start of AoC 2021!! 

Loop through input to check for increments. Used vector indices to find and sum depths. Later realised that part 2 can be siplified to compare depths which are 2 steps apart. 

After looking at Reddit, found out about a very convenient function, `std::inner_product`, which can reduce the code length considerably. An alternate form of the solution is provided in the function `void using_inner_product()`. Technically I think it is slightly slower due to having to loop over the input twice, however the algorithm is much more efficient, so it is a very minor percentage time loss.

Finally, I implemented one more solution to day 1 by looking at the them implementation of `std::inner_product` on [cppreference.com](https://en.cppreference.com/w/cpp/algorithm/inner_product). This way, we only need to loop through the input vector once to do part 1&2 at the same time. This was roughly 40% faster using basic console timing (`time`).