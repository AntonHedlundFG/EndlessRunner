# Endless Runner - C++ Assignment for FutureGames
This is an assignment for a 10-week C++ course for Unreal Engine at FutureGames. The assignment was handed out at the end of week 5. The handing in was handled in 2 parts, one at the end of week 8, and one at the end of week 10. For part 1 the requirement was an executable build, and for part 2 a feature-full build. The assignment was C++-focused and there was no visual or aesthetic requirements.

![](https://github.com/AntonHedlundFG/EndlessRunner/blob/main/Gifs/GameplayGIF.gif)

## Part 1
For the first hand-in of the game I focused on making a functioning game loop; the level generation was still only a prototype for testing game loop functionality.

### Features:
- Loop: Start->(Pause)->Game End->(Record High Score)->Restart
- Moving game board, spawning new tiles when required, deleting old tiles when out of view
  - Managed by the TileSpawner Actor, spawning and deleting tiles using the Y-axis position of the previous tile and tile itself, respectively.
- Input (1 Player)
  - Uses the EnhancedInputSystem.
- Score system w/ .json saving between sessions
  - Uses the JsonSerializer and FileHelper to save and load high scores to a .json file. 
- Rudimentary UI elements
  - Not very interesting for this course as they are mostly Blueprint-based and quite hacky. There are a few Delegates in the GameState that were required to notify the UI to update.

## Part 2
In this part I implemented the actual obstacle generation, beyond the basic prototype version included in part 1. We also received 2 surprise tasks in the last 2 weeks of this project, their implementation described below.

### Features:
- Random obstacle generation on tile spawn
  - When the TileSpawner spawns a new Tile it also generates a number of obstacles based on the current difficulty. These obstacles are positioned randomly across the surface of the Tile, and given random modifiers to customize their shape&position (Tall; Wide; Deep; Flying). 
- Gradual difficulty increase
  - There is now a DifficultyManager that handles the gradually increasing difficulty level, storing information in a FDifficulty struct. Every time a new tile is spawned, the DifficultyManager is notified, and on regular intervals it updates the difficulty. 
  - The ScorePerSecond() value is equal to GameSpeed, with a % bonus for each obstacle spawned per tile, and each customizing modifier per obstacle.
  - Whenever the number of obstacles or modifiers is increased, the speed of the game is reduced; so that there is not a drastic jump in ScorePerSecond() when this happens, also keeping the game speed from skyrocketing too quickly.

### Surprise tasks
- Input (2 Players)
  - The input management was tricky to solve; It appears two PlayerController components struggle to use the same InputDevice. The solution is somewhat hacky; PC1 handles all input and calls the respective functions in PC2 if available. Note that PC1 and PC2 both use the same class, but PC2 simply doesn't ever receive input. Given more time; I might implement a separate PlayerController for PC2 that doesn't have input mappings etc. 
  - For the actual game logic, no problems. Life management is not handled by the characters themselves, but the GameState, so there were no major changes required.
- % chance for random obstacle to disappear when overcoming an obstacle
  - This was mostly trivial to implement, as I hadn't really tackled the obstacle generation before we received the task. The TileSpawner Actor that keeps track of tile generation, speed, and removal, was simply extended to do the same for obstacles. When an obstacle is removed due to passing the players there is a chance that one of the active obstacles in the scene is destroyed. The obstacles themselves have no awareness of this feature, it's all handled in the TileSpawner.
