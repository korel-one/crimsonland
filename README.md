# Crimsonland

## Environment:
- Microsoft Visual C++ 2017

## Dependencies:
- SDL2_image-2.0.3
- SDL2-2.0.8

## **Launch**
  - Game.exe -> by default num_enemies=20, num_ammo=3, window=1024x680
  - Game.exe -window [width]x[height] -map [width]x[height] -num_enemies [val] -num_ammo [val]
    
## Not completed functionality:
  - Player should always be in the center of a screen (i.e. if it moves map is recentered).
  
## Drawbacks and limitations:
  - Framework global functions are not completelly used
  - Number of enemies to be generated is limited (otherwise packing problem should be solved)
  - SDL_RenderClear() on every Tick() provokes vexing flickering
  - To randomly spawn enemies on every game start change srand(1) to srand(time(NULL)) in EnemyManager::GenerateEnemies() {}
