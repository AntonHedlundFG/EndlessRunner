# Endless Runner

## Part 1
For this release of the game I have focused on making a functioning game loop; the level generation is still only a prototype for testing game loop functionality.

### Features:
- Loop: Start->(Pause)->Game End->(Record High Score)->Restart
- Moving game board, spawning new tiles when required, deleting old tiles when out of view
- Input
- Score system w/ .json saving between sessions
- Rudimentary UI elements

## Part 2
In this part I will implement the actual level generation, beyond the basic prototype version included in part 1.

### TO-DO:
- Random obstacle generation on tile spawn
- Gradual difficulty increase (higher movement speed and/or obstacle frequency) [How will obstacle frequency affect score?]
- (optional) Object pooling for obstacles & tiles
