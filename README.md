sdl-space-shooter
=================

An object-oriented, 2D space shooter written in C++ with SDL. Primarily as
a learning exercise on software architecture. The code base uses many design
patterns common in game development.

Currently only supported on Linux. May or may not be port to Windows in the
future.


Screetshots
=================

![Menu Screen](http://i.imgur.com/hNZOrdP.png)

![Game](http://i.imgur.com/iHSs6fC.png)


Building
=================

Dependancies: lSDL2, lSDL2_image, lSDL2_ttf, and lSDL2_mixer installed


Linux (Debian)
=================

sudo apt-get update

apt-cache search libsdl2

sudo apt-get install libsdl2-dev

sudo apt-get install libsdl2-image-dev

sudo apt-get install libsdl2-ttf-dev

sudo apt-get install libsdl2-mixer-dev

navigate to the directory where you want the project to be cloned

git clone https://github.com/brandonto/sdl-space-shooter

make all

./SpaceShooter


Windows
=================

TBD

