## Day 4

I tried to make todays problem quite efficient: 

The bingo card struct `card_t` uses an unorderd map to quickly check if a value exists on the card. This way we don't need to loop through all values to check. The map also returns the x,y position of the value if it exists, hence again no need to spend extra time looking for the value to mark it off. 

Once the raffle begins, cards are removed from the list once they have won, removing the need to cross out numbers on finished cards. This uses a `<list>` as efficient removal of cards is preferred. Also as we are accessing cards one by one in any order, random access is not required. 

Update: changed the card_t class to work with a 2D vector of ints, for numbers, and separate 2D vector of bool, for crossing out. Combining them in a box_t class seemed intuitive but ended up annoying me more than anything. In terms of speed I doublt it's any slower/faster. 

One other possibility is forgoing the 2D vector bool, and using `100` as a special crossed out value in the bingo cards. No need to remember a value when it is crossed out. This removes the need to store an extra vector bool in memory. I think it is probably slower however as multiplying integers to check the sum (a completed row/col becomes 1e10) is likely slower than logical anding bools. 