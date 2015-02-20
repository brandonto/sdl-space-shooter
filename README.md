sdl-space-shooter
=================

A 2D space shooter written in C++ with SDL, using the Object Oriented paradigm.
Done primarily as a learning exercise on software architecture. The code base
tries to use many design patterns common in game development.

Currently supported on Linux and Windows.

Due to copyright issues, the music I used will not be included. If you want
to use your own music, create the directory "data/audio/music" and put your
music in there. The file extention must be ".ogg".

The following audio file names will correspond to the state it will be played in:
Menu State: menu.ogg
Game State: level1.ogg
Victory State: win.ogg
Game Over State: lose.ogg


Screetshots
=================

![Menu Screen](http://i.imgur.com/Ddb9l4b.png)

![Game](http://i.imgur.com/1WmAAGh.png)


Building
=================

Dependancies: lSDL2, lSDL2_image, lSDL2_ttf, and lSDL2_mixer installed


Linux (Debian)
=================

1. Run the following commands on bash:

- sudo apt-get update

- apt-cache search libsdl2

- sudo apt-get install libsdl2-dev

- sudo apt-get install libsdl2-image-dev

- sudo apt-get install libsdl2-ttf-dev

- sudo apt-get install libsdl2-mixer-dev

2. Navigate to the directory where you want the project to be cloned
   and run the following commands:

- git clone https://github.com/brandonto/sdl-space-shooter

- make all

- cd bin

- ./SpaceShooter


Windows
=================

1. Download the latest Windows mingw development libraries for:

- SDL2
- SDL2_image
- SDL2_ttf
- SDL2_mixer

Extract them all to a common directory.

2. Set up a Code::Blocks project

3. In "Project Build Options>Search Directories>Compiler" add:

C:\PATH-TO-EXTRACTED-DIRECTORY\include\SDL2

4. In "Project Build Options>Search Directories>Linker" add:

C:\PATH-TO-EXTRACTED-DIRECTORY\lib

5. In "Project Build Options>Linker Settings>Other Linker Options" add:

-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

6. Build and run

