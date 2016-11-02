# ofShooter

This is a simple top-down shooter game made with [openFrameworks (0.9.3)](http://openframeworks.cc/), [Box2D](https://github.com/erincatto/Box2D) and tinyXML2. Make sure you've installed OF and Box2d. 

 Basically it's not a real game, it's just study project. So don't be serious about it. 

 For some reasone openFrameworks makefiles doesn't set c++14 standard if gcc<=4.8, so check your gcc version (or edit OF linux Makefile). Run programm by type "make run" (or it will mess root directory).

WARNING:
    I've just try to run this project on another computer. And it did not work =) I'll make a patch this evening.

 TODO:
 * propper building
 * data resource handling
 * main menu, pause, etc.
 * shadows
 * some brains to mobs (now they just go to the player)
 * more guns (with good animation)
 * propper UI