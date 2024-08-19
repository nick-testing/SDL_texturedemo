## SDL Texture Demo
Demonstration of advanced rendering features using libSDL2 and SDL_image

### Prerequisites
- Requries libSDL2, libSDL2-image, libSDL2-ttf, g++ compiler and git in order to run. Installation instructions are provided below:
- Debian/Ubuntu:

    `# apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev g++ git`

- Arch Linux:
  
    `# pacman -Syu sdl2 sdl2_image sdl2_ttf git base-devel`

### Build
<ol>
  <li><code>git clone https://github.com/nick-testing/SDL_texturedemo.git</code></li>
  <li><code>cd</code> to the created directory</li>
  <li>Run <code>make</code> to compile the program</li>
  <li>The compiled binary is located in SDL_texturedemo/output/</li>
</ol>

Run <code>make clean</code> to remove the compiled files


#### Design
The program consists of a parent SDLProgram class which contains a general SDL initialization and display clearing function.
The child class SDLRenderDemo inherits SDLProgram and implements all of the pure virtual functions to create a functioning program.
SDLRender is a wrapper class for the SDL_Renderer struct and offers various rendering functions.

The current UML design document:

<img src=https://github.com/user-attachments/assets/90b37374-b12b-4ff8-8860-3e6a68d896b1>
