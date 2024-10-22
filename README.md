## SDL Texture Demo
Demonstration of advanced rendering features using libSDL2, image, ttf and mixer libraries

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
The current UML design document:

![The design sheet](/misc/design.png)
