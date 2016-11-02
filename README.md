# ofShooter

This is a simple top-down shooter game made with [openFrameworks (0.9.3)](http://openframeworks.cc/), [Box2D](https://github.com/erincatto/Box2D) and tinyXML2.

 Basically it's not a real game, it's just study project. So don't be serious about it. 

 For some reasone openFrameworks makefiles doesn't set c++14 standard if gcc<=4.8, so check your gcc version (or edit OF linux Makefile). Run programm by type "make run" (or it will mess root directory).

# Install and run
I do not use any IDE, so this game tested only by running app in ubuntu console. If you want to use IDE (or windows), read propper OF instruction.

1. Install OF [by this instruction](http://openframeworks.cc/setup/linux-install/). Make sure you install projectGenerator.
2. Set environment variable $OF_ROOT (should point to openFrameworks root directory)
3. Install Box2d by running sudo apt-get install libbox2d-dev
4. Clone this rep
5. Run projectGenerator on rep folder.
6. Run "make" and "make run"


If game cannot load the images run
> mkdir bin/data

from rep directory. It is OF default data folder, but for some reasone it don't create one if it does not exist. 

    Warning. It seems that projectGenerator crash if it compiled with g++<=4.8

 # Expected features
 * main menu, pause, etc.
 * shadows
 * some brains to mobs (now they just go to the player)
 * more guns (with good animation)
 * propper UI