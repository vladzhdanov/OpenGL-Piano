# CSCI 4229 Final Project: OpenGL Piano

### Vladimir Zhdanov
### CSCI4229 Computer Graphics, Fall 2018

### Dependencies:
1. OpenGL
2. GLUT
3. SDL 1.0 and SDL_mixer

### To run the program: 
Type "make" and run the piano executable file once its finished compiling.


### Key bindings
| Key         | Function                        |
| ----------- | -------------------------------:|
| ESC         | Exit                            |
| PgDn/PgUp   | Zoom in and out                 |
| arrows      | Change view angle               |
| 0           | Reset view angle                |
| b           | Toggle axes                     |
| m           | Toggle light                    |
| n  		      |	Toggle key highlighting			    |
| left click  | Play key mouse is hovered over  |
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


### Features:
* Full-fledged and accurate grand piano with accurate lighting and textures.
* The correct note sound plays for each specified key, and the correct key will move.
* Able to play several notes at once (chords) by using multiple audio channels.
* The ability to click on any note with the mouse and it will animate and play the correct note.


### Outside Files Used:
* [Original Grand Piano .obj file](https://free3d.com/3d-model/piano-8271.html) (This was modified to remove the keys and insert my own key models)
* [Piano Key Sound Samples](https://freesound.org/people/jobro/packs/2489/)
