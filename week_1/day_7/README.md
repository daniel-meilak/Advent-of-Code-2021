## Day 7

[Rosetta Code](http://www.rosettacode.org/wiki/Averages/Median#C.2B.2B) provided a nice way of finding the median for part 1. Part 2 required some headscratching however I had already tried using the mean in part one and remember that it was close to the example answer. Turns out the `std::ceil` or `std::floor` of the mean should be the correct choice.