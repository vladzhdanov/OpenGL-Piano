# OpenGL Piano

### Vladimir Zhdanov
### CSCI 4229: Computer Graphics, Fall 2018

### Dependencies:
1. OpenGL
2. GLUT
3. SDL 1.2 and SDL_mixer

### To run the program: 
Type "make" and run the final executable file (`./final`) once its finished compiling.


### Key bindings
| Key         | Function                        |
| ----------- | -------------------------------:|
| ESC         | Exit                            |
| PgDn/PgUp   | Zoom in and out                 |
| arrows      | Change view angle               |
| 0           | Reset view angle/zoom           |
| b           | Toggle axes                     |
| m           | Toggle light                    |
| ,			      | Toggle light ball visibility    |
| x/X 		    | Decrease/Increase Light x-pos   |
| y/Y 		    | Decrease/Increase Light y-pos   |
| z/Z 	  	  | Decrease/Increase Light z-pos   |
| n  		      |	Toggle key highlighting			    |
| mouse click | Play key mouse is hovered over  |
| -/+         | Decrease/Increase note interval |
| a           | Play 1st key in interval        |
| s           | Play 2nd key in interval        |
| d           | Play 3rd key in interval        |
| f           | Play 4th key in interval        |
| g           | Play 5th key in interval        |  
| h           | Play 6th key in interval        |
| j           | Play 7th key in interval        |
| k           | Play 8th key in interval        |
| l           | Play 9th key in interval        |
| ;           | Play 10th key in interval       |
| '           | Play 11th key in interval       |
| 1			      | Play/Stop song #1 (Little Lamb) |
| 2			      | Play/Stop song #2 (Ode to Joy)	|


### Features:
* Full-fledged grand piano with accurate lighting and textures that can be viewed from any angle.
* The correct note sound plays for each specified key, and the correct key will move.
* Each key is animated, and smoothly moves down and returns to its original position when played.
* Able to play several notes at once (chords) by using multiple audio channels.
* The ability to click on any note with the mouse and the piano will move and play the correct note.
* The piano is able to play several songs on its own including Mary had a Little Lamb and Ode to Joy.

### Other things I did as part of this project:
* Modified the object.c file provided as part of CSCIx229.h to be able to read .obj files with negative/relative texture/vertex indices.
* Figured out how to use the stencil buffer to determine which objects were being clicked in order to know which note on the piano to click.
* Modified an existing .obj grand piano file to remove their key models, and drew my own models of the keys using my own keyboard as a reference for size and position. 


### Outside Files Used:
* [Original Grand Piano .obj file](https://free3d.com/3d-model/piano-8271.html) (This was modified to remove the keys and insert my own key models)
* [Piano Key Sound Samples](https://freesound.org/people/jobro/packs/2489/)
