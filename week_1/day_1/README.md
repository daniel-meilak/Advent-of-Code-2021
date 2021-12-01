## Day 1 

Start of AoC 2021!! 

Loop through input to check for increments. Used vector indices to find and sum depths. Later realised that part 2 can be siplified to compar depths which are 2 steps apart. 

After looking at Reddit, found out about a very convenient function, `std::inner_product`, which can reduce the code length considerably. An alternate form of the solution is provided in the function `void using_inner_product()`. 