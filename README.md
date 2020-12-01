#### CardGame (26%)

- [x] Cards (4%)
```
Card will be an abstract base class and the eight different bean cards will <br>
be derived from it (inheritance). All containers will hold cards through the base type. However, <br>
standard containers do not work well with polymorphic types because they hold copies (slicing will occur).
```
- [x] Deck (2%)
```
Deck will initially hold all the cards which will have to be shuffled <br> 
to produce a randomized order, then players' hands are dealt and during game play players draw cards <br>
from the Deck. There is no insertion into the Deck. Deck can therefore usefully extend a std::vector.
```
- [x] DiscardPile (2%)
```
DiscardPile must support insertion and removal but not at random locations but all at the end. <br> 
Again a std::vector will work fine but here we can use simple aggregation.
```
- [] Chain (2%)
```
Chain is also a container and will have to grow and shrink as the game progresses. <br> 
Again insertion is only to one end of the chain and a std::vector is fine (see below). <br>
A template class will have to created for Chain being parametric in the type of card. <br> 
In this project, we will instantiate Chain for the corresponding bean card.
```
- [] Table (2%)
```
Table will manage all the game components. It will hold two objects of type Player, the Deck and <br> 
the DiscardPile, as well as the TradeArea.
```
- [] TradeArea (3%)
```
TradeArea class will have to hold cards openly and support random access insertion and removal.
```
- [] Coins
- [] Hand (2%)
```
Hand is well mapped by a queue since players have to keep their hand in order and the first card drawn is the first card played. <br> 
The only derivation form this pattern is if players discard a card from the middle in Step 4 <br> 
in the above description of a player's turn. Therefore, we can use a std::list to remove at an arbitrary location <br>
efficiently with a std::queue adapter.
```
- [] Players (3%)
- [x] CardFactory (2%)
```
CardFactory will generate all cards, and so, we will explore the factory pattern. <br>
A factory ensures that there is only a single unit in the program that is responsible to create and delete cards.<br> 
Other parts of the program will only use pointers to access the cards.<br> 
Note that means, we will delete the copy constructor and assignment operator in Card.
```
- [] Main Loop (4%)
