# 2048
C++ Impl of 2048 for playing around with AIs for the game

I did this project to play around with C++ and see what heuristics worked well for 2048. I also was hoping to make a neural net for the game (given the games random nature it seemed like an obvious application), but had issues getting it to learn. I think there's a small bug in the impl.

The current players are (with max, median score over 100 random trials)

- Zed - Plays randomly (2700, 1032)
- Bertha - Always tries left, then down, then up, then right (6872, 1964)
- Rod - Single level search, ordering states by score (8780, 2796)
- Friedrich - Single level search, order by number of largest tiles, then second largest, etc (9608, 2156)
- Rodney - Single level search including random placement after move, order by score (13028, 3054)
- Silvia - Multi (4) level search including random placement after move, order by weighted combination of score, number of empty cells, and discomfort for cells to be surrounded by incompatible cells (50412, 17158)
- Oliver - Neural net, but doesn't learn currently so is basically Zed (3256, 846)
