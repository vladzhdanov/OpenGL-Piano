# CSCI 4229 Final Project: OpenGL Piano

###### Vladimir Zhdanov

###### CSCI4229 Fall 2018

#### Dependencies:
1. OpenGL
2. GLUT
3. SDL 1.0 and SDL_mixer

#### To run the program: 
Type "make" and run the piano executable file once its finished compiling


#### Key bindings

| Key         | Function                        |
| ----------- | -------------------------------:|
|  arrows     | Change view angle               |
|  PgDn/PgUp  | Zoom in and out                 |
|  0          | Reset view angle                |
|  ESC        | Exit                            |
| b           | Toggle axes                     |
| m           | Toggle light                    |
| n  		  |	Toggle key highlighting			|
|  -/+        | Decrease/Increase note interval |
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
| left click  | Play key mouse is hovered over  |

#### Progress Made so far:
* Created an accurate representation of piano keys
* Added lighting to piano keys
* The correct note sound plays for each specified key, and the correct key will move
* Able to play several notes at once (chords) by using multiple audio channels
* Added the ability to click on any note with the mouse and it will animate and play the correct note

#### Things Left to do:
* Finish the model of the piano (case around the keys)
* Add textures to piano model
