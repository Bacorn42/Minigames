# Minigames

This is a project from September 2016. Its main purpose was for me to learn about C++11 and the SFML library, incorporating most of the knowledge I've obtained. The project contains 2 minigames.

### Dodge

Use the arrow keys to move the player around. Spinning boxes appear around the map and travel across it. Do not let any of them touch you. As time progresses, the game becomes harder. Occasionally items spawn that may help you or simply give you points.

### Piano Hero

It doesn't really have anything to do with a piano. It's supposed to resemble a rhythm game of sorts... without music. The objective is to press the appropriate key at the right time when a fret passes over the rectangle. Every 50 frets you may get an additional life. As time progresses, so does speed and number of frets at once.

# Compilation

The project was made with SFML 2.3.1, and requires the following files to be in the same directory as the executable:

* sfml-graphics-2.dll
* sfml-system-2.dll
* sfml-window-2.dll

In case of problems (at least which I encountered), the following files may be required, but missing from the system:

* openal32.dll
* libgcc\_s\_sjlj-1.dll
* libstdc++-6.dll