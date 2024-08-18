## SDL Texture Demo
Demonstration of advanced rendering features using libSDL2 and SDL_image

### Build
  - Tested on g++ ver. 11.4.0 with SDL2 and SDL_image ver. 2.0.20 
  - `git clone` the repository
  - A makefile is provided for convenience. Use `make` to compile the program
  - The compiled binary is located at `output/game.out`


#### Design
The program consists of a main Game class which contatins public executable functiosn and an LTexture wrapper class for the SDL_Texture structure.

Here's the current design document:
<img src=https://raw.githubusercontent.com/nick-testing/SDL_texturedemo/master/misc/design.png>
