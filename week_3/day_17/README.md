## Day 17

Decided not to put in too much effort today so I brute forced part 2 with good boundaries. Though I think I do understand the most efficient way to do it:

As `x` and `y` and independant, you can work out separately which values land within the target zone. Then its simply a case of forming all pairs of `{x,y}` but removing those which overshoot in `x` before reaching the target in `y` and vice versa. 