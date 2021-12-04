## Day 4

I tried to make todays problem quite efficient:

The bingo card struct `card_t` uses an unorderd map to quickly check if a value exists on the card. This way we don't need to loop through all values to check. The map also returns the x,y position of the value if it exists, hence again no need to spend extra time looking for the value to mark it off.

Once the raffle begins, cards are removed from the list once they have won, removing the need to cross out numbers on finished cards. This uses a `<list>` as efficient removal of cards is preferred. Also as we are accessing cards one by one in any order, random access is not required. 

