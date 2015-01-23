# Simple opengl GLUT application

- player can move in the 64x64x64 grid
- move with **W** **A** **S** **D**
- can turn right-left the camera by pushing **Left-mouse-click** and draging the mouse
- create a new cube by pressing **M**
- delete a cube by pressing **N**
- delete all cubes in front of you by pressing **B**
- after **90** moves lights are out
- by pressing **L** and create an additional light for **30** moves
- by pressing **Spacebar** you can see **Score** and make the block under the player **blue** and absorb it's stock

Compile with : g++ myMineCraft.cpp -lglut -lGL -lGLU
