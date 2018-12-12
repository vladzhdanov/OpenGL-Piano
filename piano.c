/*
 *  CSCI 4229 Final Project: Piano.
 *
 *  Key bindings: See README.md
 *
 */
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "CSCIx229.h"

int width = 750;  // Intial screen width
int height = 750; // Initial screen height
int delay = 5;    // Screen Time delay
int axes=0;       //  Display axes
int ntex=1;       //  Texture mode
int th=-35,ph=40; //  View angles
int Th=0,Ph=30;   //  Light angles
int at0=100;      //  Constant  attenuation %
int at1=5;        //  Linear    attenuation %
int at2=0;        //  Quadratic attenuation %
int fov=55;       //  Field of view (for perspective)
int light=1;      //  Lighting
double asp=1;     //  Aspect ratio
double dim= 11.5; //  Size of world

// Light values
int inf       =   0; // Infinite distance light
int smooth    =   1; // Smooth/Flat shading
int local     =   1; // Local Viewer Model
int emission  =   0; // Emission intensity (%)
int ambient   =  20; // Ambient intensity (%)
int diffuse   = 100; // Diffuse intensity (%)
int specular  =   0; // Specular intensity (%)
int shininess =   0; // Shininess (power of two)
float shiny   =   1; // Shininess (value)
float X       =   0; // Light X position
float Y       = 9.8; // Light Y position
float Z       = -.5; // Light Z position
int showlight =   1; // Toggle light visibility

// Textures
int tex[5]; // Texture array


// Piano related values
int obj;              // Piano model obj file
int highlight = 1;    // Highlight keys when played
int interval = 4;     // Current keyboard key interval
int playing[89];      // Key being played or not
int play_pos[89];     // Key playing animations
Mix_Chunk* notes[89]; // Note sounds
int downTime[89];     // Counts how long since key pressed
int down_len = 100;   // Length of time key is pressed down
int song = 0;         // Song 1 toggle
int song2 = 0;        // Song 2 toggle
int songlength = 26;  // Song 1 length
int songlength2 = 62; // Song 2 length

// Song 1 (Mary had a Little Lamb) notes and pauses
int songnotes[26] = {44, 42, 40, 42, 44, 44, 44, 42, 42, 42,
                     44, 47, 47, 44, 42, 40, 42, 44, 44, 44, 
                     44, 42, 42, 44, 42, 40};
int pauses[26] = {20, 20, 20, 20, 20, 20, 20, 40, 20, 20,
                  40, 20, 20, 40, 20, 20, 20, 20, 20, 20,
                  20, 20, 20, 20, 20, 20};

// Song 2 (Ode to Joy) notes and pauses
int songnotes2[62] = {44, 44, 45, 47, 47, 45, 44, 42, 40, 40,
                      42, 44, 44, 42, 42, 44, 44, 45, 47, 47,
                      45, 44, 42, 40, 40, 42, 44, 42, 40, 40,
                      42, 42, 44, 40, 42, 44, 45, 44, 40, 42,
                      44, 45, 44, 42, 40, 42, 35, 44, 44, 45,
                      47, 47, 45, 44, 42, 40, 40, 42, 44, 42,
                      40, 40};

int songleft2[62] =  {28, 28, 30, 32, 32, 30, 28, 33, 32, 32,
                      33, 35, 35,  0, 35, 28, 28, 30, 32, 32,
                      30, 28, 33, 32, 32, 33, 35, 33, 32, 32,
                      35,  0,  0,  0, 35,  0,  0,  0,  0, 35,
                       0,  0, 36,  0, 37, 34, 35, 28, 28, 30, 
                      32, 32, 30, 28, 33, 32, 32, 33, 35, 33,
                      32, 32};
int pauses2[62] = {25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
                   25, 25, 25, 35, 20, 50, 25, 25, 25, 25,
                   25, 25, 25, 25, 25, 25, 25, 25, 35, 20,
                   50, 25, 25, 25, 25, 25, 15, 15, 25, 25,
                   25, 15, 15, 25, 25, 25, 25, 50, 25, 25,
                   25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
                   35, 20};
int current = 0;  // Current note being played (song 1)
int current2 = 0; // Current note being played (song 2)

static void Vertex(double th,double ph)
{
  glVertex3d(Sin(th)*Cos(ph),Cos(th)*Cos(ph),Sin(ph));
}

static void pianoKey(int num,
      double x, double y, double z,
      double dx, double dy, double dz, 
      double playing, double position)
{

  glPushMatrix();
  glTranslated(x,y,z);
  glScaled(dx,dy,dz);

  glStencilFunc(GL_ALWAYS, num, -1);

  // First key has a unique shape 
  if(num == 1){
    num = -1;
  }
  // Except for the very first and last key,
  // the piano repeats the same pattern of notes
  // every octave (12 half steps)
  if(num != 88 && num != -1 && num >= 12){
    num %= 12;
  }
  
  if(playing || position > 0){
    glTranslated(0,0,-6);
    if(num == 0 || num == 2 || num == 5 || num == 7 || num == 10){
      glRotatef(3*(float)(position/down_len), 1,0,0);
      } 
    else{
      glRotatef(6*(float)(position/down_len), 1,0,0);      
    } 
    glTranslated(0,0,6);
  }

  switch(num){
    // White key with hole on right
    case 4:
    case 9:
      (playing && highlight) ? glColor3f(1,.4,.4) : glColor3f(1, 1, 1);
      glBegin(GL_QUADS);
      // Bottom
      glNormal3f(0, -1, 0);
      glVertex3d(0,    0,  0);
      glVertex3d(.5,   0,  0);
      glVertex3d(.5,   0, -6);
      glVertex3d(0,    0, -6);

      glNormal3f(0, -1, 0);
      glVertex3d(.5,   0,  0);
      glVertex3d(.875, 0,  0);
      glVertex3d(.875, 0, -2);
      glVertex3d(.5,   0, -2);

      // Sides
      glNormal3f(0, 0, 1);
      glVertex3d(0,       0,  0);
      glVertex3d(.875,    0,  0);
      glVertex3d(.875, .875,  0);
      glVertex3d(0,    .875,  0);

      glNormal3f(-1, 0, 0);
      glVertex3d(0,    0,  0);
      glVertex3d(0,    0, -6);
      glVertex3d(0, .875, -6);
      glVertex3d(0, .875,  0);

      glNormal3f(0, 0, -1);
      glVertex3d(0,     0, -6);
      glVertex3d(0,  .875, -6);
      glVertex3d(.5, .875, -6);
      glVertex3d(.5,    0, -6);

      glNormal3f(1, 0, 0);
      glVertex3d(.5,    0, -6);
      glVertex3d(.5, .875, -6);
      glVertex3d(.5, .875, -2);
      glVertex3d(.5,    0, -2);

      glNormal3f(0, 0, -1);
      glVertex3d(.5,      0, -2);
      glVertex3d(.5,   .875, -2);
      glVertex3d(.875, .875, -2);
      glVertex3d(.875,    0, -2);

      glNormal3f(1, 0, 0);
      glVertex3d(.875,    0, -2);
      glVertex3d(.875, .875, -2);
      glVertex3d(.875, .875,  0);
      glVertex3d(.875,    0,  0);

      // Top
      glNormal3f(0, 1, 0);
      glVertex3d(0,  .875,  0);
      glVertex3d(.5, .875,  0);
      glVertex3d(.5, .875, -6);
      glVertex3d(0,  .875, -6);

      glNormal3f(0, 1, 0);
      glVertex3d(.5,   .875,  0);
      glVertex3d(.875, .875,  0);
      glVertex3d(.875, .875, -2);
      glVertex3d(.5,   .875, -2);
      glEnd();
      break;

    // Black key
    case 0:
    case 2:
    case 5:
    case 7:
    case 10:
      (playing && highlight) ? glColor3f(.6,.2,.2) : glColor3f(.2, .2, .2);
      glBegin(GL_QUADS);

      // Bottom
      glNormal3f(0, -1, 0);
      glVertex3d(0,     0, -2.0625);      
      glVertex3d(.4375, 0, -2.0625);
      glVertex3d(.4375, 0, -6);
      glVertex3d(0,     0, -6);

      // Sides
      glNormal3f(0, 0, 1);
      glVertex3d(0,        0, -2.0625);
      glVertex3d(.4375,    0, -2.0625);
      glVertex3d(.4375, .875, -2.0625);
      glVertex3d(0,     .875, -2.0625);

      glNormal3f(0, 0, -1);
      glVertex3d(0,        0, -6);
      glVertex3d(.4375,    0, -6);
      glVertex3d(.4375, .875, -6);
      glVertex3d(0,     .875, -6);

      glNormal3f(-1, 0, 0);
      glVertex3d(0,    0, -2.0625);
      glVertex3d(0,    0, -6);
      glVertex3d(0, .875, -6);
      glVertex3d(0, .875, -2.0625);      

      glNormal3f(1, 0, 0);
      glVertex3d(.4375,    0, -2.0625);
      glVertex3d(.4375,    0, -6);
      glVertex3d(.4375, .875, -6);
      glVertex3d(.4375, .875, -2.0625);  
      
      // Slanted Sides
      glNormal3f(0, 1, 8);
      glVertex3d(     0,  .875, -2.0625);
      glVertex3d(.03125, 1.125, -2.09375);
      glVertex3d(.40625, 1.125, -2.09375);
      glVertex3d( .4375,  .875, -2.0625);

      glNormal3f(-8, 1, 0);
      glVertex3d(     0,  .875, -2.0625);
      glVertex3d(.03125, 1.125, -2.09375);
      glVertex3d(.03125, 1.125, -5.96875);
      glVertex3d(     0,  .875, -6);

      glNormal3f(8, 1, 0);
      glVertex3d( .4375,  .875, -2.0625);
      glVertex3d(.40625, 1.125, -2.09375);
      glVertex3d(.40625, 1.125, -5.96875);
      glVertex3d( .4375,  .875, -6);

      glNormal3f(0, 1, -8);
      glVertex3d(     0,  .875, -6);
      glVertex3d(.03125, 1.125, -5.96875);
      glVertex3d(.40625, 1.125, -5.96875);
      glVertex3d( .4375,  .875, -6);

      // Top
      glNormal3f(0, 1, 0);
      glVertex3d(.03125,   1.125, -2.09375);
      glVertex3d(.40625,   1.125, -2.09375);
      glVertex3d(.40625,   1.125, -5.96875);
      glVertex3d(.03125,   1.125, -5.96875);

      glEnd();
      break;

    // White key with hole on left
    case 3:
    case 8:
      (playing && highlight) ? glColor3f(1,.4,.4) : glColor3f(1, 1, 1);
      glBegin(GL_QUADS);
      // Bottom
      glNormal3f(0, -1, 0);
      glVertex3d(.375,    0,  0);
      glVertex3d(.875,    0,  0);
      glVertex3d(.875,    0, -6);
      glVertex3d(.375,    0, -6);

      glNormal3f(0, -1, 0);
      glVertex3d(0,    0,  0);
      glVertex3d(.375, 0,  0);
      glVertex3d(.375, 0, -2);
      glVertex3d(0,    0, -2);

      // Sides
      glNormal3f(0, 0, 1);
      glVertex3d(0,       0,  0);
      glVertex3d(.875,    0,  0);
      glVertex3d(.875, .875,  0);
      glVertex3d(0,    .875,  0);

      glNormal3f(0, 0, -1);
      glVertex3d(.375,     0, -6);
      glVertex3d(.375,  .875, -6);
      glVertex3d(.875, .875, -6);
      glVertex3d(.875,    0, -6);

      glNormal3f(0, 0, -1);
      glVertex3d(0,      0, -2);
      glVertex3d(0,   .875, -2);
      glVertex3d(.375, .875, -2);
      glVertex3d(.375,    0, -2);

      glNormal3f(1, 0, 0);
      glVertex3d(.875,    0,  0);
      glVertex3d(.875,    0, -6);
      glVertex3d(.875, .875, -6);
      glVertex3d(.875, .875,  0);

      glNormal3f(-1, 0, 0);
      glVertex3d(.375,    0, -6);
      glVertex3d(.375, .875, -6);
      glVertex3d(.375, .875, -2);
      glVertex3d(.375,    0, -2);

      glNormal3f(-1, 0, 0);
      glVertex3d(0,    0, -2);
      glVertex3d(0, .875, -2);
      glVertex3d(0, .875,  0);
      glVertex3d(0,    0,  0);

      // Top
      glNormal3f(0, 1, 0);
      glVertex3d(.375,  .875,  0);
      glVertex3d(.875,  .875,  0);
      glVertex3d(.875,  .875, -6);
      glVertex3d(.375,  .875, -6);

      glNormal3f(0, 1, 0);
      glVertex3d(0,     .875,  0);
      glVertex3d(.375,  .875,  0);
      glVertex3d(.375,  .875, -2);
      glVertex3d(0,     .875, -2);
      glEnd();
      break;

    // White key with holes on both sides
    // Hole on left is larger
    case 1:
      (playing && highlight) ? glColor3f(1,.4,.4) : glColor3f(1, 1, 1);
      glBegin(GL_QUADS);
      // Bottom
      glNormal3f(0, -1, 0);
      glVertex3d(.25,  0,  0);
      glVertex3d(.75,    0,  0);
      glVertex3d(.75,    0, -6);
      glVertex3d(.25,  0, -6);

      glNormal3f(0, -1, 0);
      glVertex3d(0,    0,  0);
      glVertex3d(.25, 0,  0);
      glVertex3d(.25, 0, -2);
      glVertex3d(0,    0, -2);

      glNormal3f(0, -1, 0);
      glVertex3d(.75,    0,  0);
      glVertex3d(.875,  0,  0);
      glVertex3d(.875,  0, -2);
      glVertex3d(.75,    0, -2);

      // Top
      glNormal3f(0, 1, 0);
      glVertex3d(.25, .875,  0);
      glVertex3d(.75,  .875,  0);
      glVertex3d(.75,  .875, -6);
      glVertex3d(.25, .875, -6);

      glNormal3f(0, 1, 0);
      glVertex3d(0,    .875,  0);
      glVertex3d(.25, .875,  0);
      glVertex3d(.25, .875, -2);
      glVertex3d(0,    .875, -2);

      glNormal3f(0, 1, 0);
      glVertex3d(.75,  .875,  0);
      glVertex3d(.875, .875,  0);
      glVertex3d(.875, .875, -2);
      glVertex3d(.75,  .875, -2);

      // Sides
      glNormal3f(0, 0, 1);
      glVertex3d(0,       0, 0);
      glVertex3d(.875,    0, 0);
      glVertex3d(.875, .875, 0);
      glVertex3d(0,    .875, 0);

      glNormal3f(0, 0, -1);
      glVertex3d(.25,    0, -6);
      glVertex3d(.75,     0, -6);
      glVertex3d(.75,  .875, -6);
      glVertex3d(.25, .875, -6);

      glNormal3f(0, 0, -1);
      glVertex3d( 0,      0, -2);
      glVertex3d(.25,    0, -2);
      glVertex3d(.25, .875, -2);
      glVertex3d( 0,   .875, -2);

      glNormal3f(0, 0, -1);
      glVertex3d(.75,      0, -2);
      glVertex3d(.875,    0, -2);
      glVertex3d(.875, .875, -2);
      glVertex3d(.75,   .875, -2);

      glNormal3f(-1, 0, 0);
      glVertex3d(0,    0,  0);
      glVertex3d(0,    0, -2);
      glVertex3d(0, .875, -2);
      glVertex3d(0, .875,  0);

      glNormal3f(-1, 0, 0);
      glVertex3d(.25,    0, -2);
      glVertex3d(.25,    0, -6);
      glVertex3d(.25, .875, -6);
      glVertex3d(.25, .875, -2);

      glNormal3f(1, 0, 0);
      glVertex3d(.875,    0,  0);
      glVertex3d(.875,    0, -2);
      glVertex3d(.875, .875, -2);
      glVertex3d(.875, .875,  0);

      glNormal3f(1, 0, 0);
      glVertex3d(.75,    0, -2);
      glVertex3d(.75,    0, -6);
      glVertex3d(.75, .875, -6);
      glVertex3d(.75, .875, -2);

      glEnd(); 
      break;

    // White key with holes on both sides
    // Both holes same size
    case 6:
      (playing && highlight) ? glColor3f(1,.4,.4) : glColor3f(1, 1, 1);
      glBegin(GL_QUADS);
      // Bottom
      glNormal3f(0, -1, 0);
      glVertex3d(.125,  0,  0);
      glVertex3d(.75,    0,  0);
      glVertex3d(.75,    0, -6);
      glVertex3d(.125,  0, -6);

      glNormal3f(0, -1, 0);
      glVertex3d(0,    0,  0);
      glVertex3d(.125, 0,  0);
      glVertex3d(.125, 0, -2);
      glVertex3d(0,    0, -2);

      glNormal3f(0, -1, 0);
      glVertex3d(.75,    0,  0);
      glVertex3d(.875,  0,  0);
      glVertex3d(.875,  0, -2);
      glVertex3d(.75,    0, -2);

      // Top
      glNormal3f(0, 1, 0);
      glVertex3d(.125, .875,  0);
      glVertex3d(.75,  .875,  0);
      glVertex3d(.75,  .875, -6);
      glVertex3d(.125, .875, -6);

      glNormal3f(0, 1, 0);
      glVertex3d(0,    .875,  0);
      glVertex3d(.125, .875,  0);
      glVertex3d(.125, .875, -2);
      glVertex3d(0,    .875, -2);

      glNormal3f(0, 1, 0);
      glVertex3d(.75,  .875,  0);
      glVertex3d(.875, .875,  0);
      glVertex3d(.875, .875, -2);
      glVertex3d(.75,  .875, -2);

      // Sides
      glNormal3f(0, 0, 1);
      glVertex3d(0,       0, 0);
      glVertex3d(.875,    0, 0);
      glVertex3d(.875, .875, 0);
      glVertex3d(0,    .875, 0);

      glNormal3f(0, 0, -1);
      glVertex3d(.125,    0, -6);
      glVertex3d(.75,     0, -6);
      glVertex3d(.75,  .875, -6);
      glVertex3d(.125, .875, -6);

      glNormal3f(0, 0, -1);
      glVertex3d( 0,      0, -2);
      glVertex3d(.125,    0, -2);
      glVertex3d(.125, .875, -2);
      glVertex3d( 0,   .875, -2);

      glNormal3f(0, 0, -1);
      glVertex3d(.75,      0, -2);
      glVertex3d(.875,    0, -2);
      glVertex3d(.875, .875, -2);
      glVertex3d(.75,   .875, -2);

      glNormal3f(-1, 0, 0);
      glVertex3d(0,    0,  0);
      glVertex3d(0,    0, -2);
      glVertex3d(0, .875, -2);
      glVertex3d(0, .875,  0);

      glNormal3f(-1, 0, 0);
      glVertex3d(.125,    0, -2);
      glVertex3d(.125,    0, -6);
      glVertex3d(.125, .875, -6);
      glVertex3d(.125, .875, -2);

      glNormal3f(1, 0, 0);
      glVertex3d(.875,    0,  0);
      glVertex3d(.875,    0, -2);
      glVertex3d(.875, .875, -2);
      glVertex3d(.875, .875,  0);

      glNormal3f(1, 0, 0);
      glVertex3d(.75,    0, -2);
      glVertex3d(.75,    0, -6);
      glVertex3d(.75, .875, -6);
      glVertex3d(.75, .875, -2);

      glEnd(); 
      break;

    // White key with holes on both sides
    // Hole on right is larger
    case 11: 
      (playing && highlight) ? glColor3f(1,.4,.4) : glColor3f(1, 1, 1);
      glBegin(GL_QUADS);
      // Bottom
      glNormal3f(0, -1, 0);
      glVertex3d(.125,  0,  0);
      glVertex3d(.625,    0,  0);
      glVertex3d(.625,    0, -6);
      glVertex3d(.125,  0, -6);

      glNormal3f(0, -1, 0);
      glVertex3d(0,    0,  0);
      glVertex3d(.125, 0,  0);
      glVertex3d(.125, 0, -2);
      glVertex3d(0,    0, -2);

      glNormal3f(0, -1, 0);
      glVertex3d(.625,    0,  0);
      glVertex3d(.875,  0,  0);
      glVertex3d(.875,  0, -2);
      glVertex3d(.625,    0, -2);

      // Top
      glNormal3f(0, 1, 0);
      glVertex3d(.125, .875,  0);
      glVertex3d(.625,  .875,  0);
      glVertex3d(.625,  .875, -6);
      glVertex3d(.125, .875, -6);

      glNormal3f(0, 1, 0);
      glVertex3d(0,    .875,  0);
      glVertex3d(.125, .875,  0);
      glVertex3d(.125, .875, -2);
      glVertex3d(0,    .875, -2);

      glNormal3f(0, 1, 0);
      glVertex3d(.625,  .875,  0);
      glVertex3d(.875, .875,  0);
      glVertex3d(.875, .875, -2);
      glVertex3d(.625,  .875, -2);

      // Sides
      glNormal3f(0, 0, 1);
      glVertex3d(0,       0, 0);
      glVertex3d(.875,    0, 0);
      glVertex3d(.875, .875, 0);
      glVertex3d(0,    .875, 0);

      glNormal3f(0, 0, -1);
      glVertex3d(.125,    0, -6);
      glVertex3d(.625,     0, -6);
      glVertex3d(.625,  .875, -6);
      glVertex3d(.125, .875, -6);

      glNormal3f(0, 0, -1);
      glVertex3d( 0,      0, -2);
      glVertex3d(.125,    0, -2);
      glVertex3d(.125, .875, -2);
      glVertex3d( 0,   .875, -2);

      glNormal3f(0, 0, -1);
      glVertex3d(.625,      0, -2);
      glVertex3d(.875,    0, -2);
      glVertex3d(.875, .875, -2);
      glVertex3d(.625,   .875, -2);

      glNormal3f(-1, 0, 0);
      glVertex3d(0,    0,  0);
      glVertex3d(0,    0, -2);
      glVertex3d(0, .875, -2);
      glVertex3d(0, .875,  0);

      glNormal3f(-1, 0, 0);
      glVertex3d(.125,    0, -2);
      glVertex3d(.125,    0, -6);
      glVertex3d(.125, .875, -6);
      glVertex3d(.125, .875, -2);

      glNormal3f(1, 0, 0);
      glVertex3d(.875,    0,  0);
      glVertex3d(.875,    0, -2);
      glVertex3d(.875, .875, -2);
      glVertex3d(.875, .875,  0);

      glNormal3f(1, 0, 0);
      glVertex3d(.625,    0, -2);
      glVertex3d(.625,    0, -6);
      glVertex3d(.625, .875, -6);
      glVertex3d(.625, .875, -2);

      glEnd(); 
      break;

    // Special Keys
    // Key 1: Smaller hole on right side
    case -1:
      (playing && highlight) ? glColor3f(1,.4,.4) : glColor3f(1, 1, 1);
      glBegin(GL_QUADS);
      // Bottom
      glNormal3f(0, -1, 0);
      glVertex3d(0,     0,  0);
      glVertex3d(.75,    0,  0);
      glVertex3d(.75,    0, -6);
      glVertex3d(0,     0, -6);

      glNormal3f(0, -1, 0);
      glVertex3d(.75,    0,  0);
      glVertex3d(.875,  0,  0);
      glVertex3d(.875,  0, -2);
      glVertex3d(.75,    0, -2);

      // Top
      glNormal3f(0, 1, 0);
      glVertex3d(0,    .875,  0);
      glVertex3d(.75,  .875,  0);
      glVertex3d(.75,  .875, -6);
      glVertex3d(0,    .875, -6);

      glNormal3f(0, 1, 0);
      glVertex3d(.75,  .875,  0);
      glVertex3d(.875, .875,  0);
      glVertex3d(.875, .875, -2);
      glVertex3d(.75,  .875, -2);

      // Sides
      glNormal3f(0, 0, 1);
      glVertex3d(0,       0, 0);
      glVertex3d(.875,    0, 0);
      glVertex3d(.875, .875, 0);
      glVertex3d(0,    .875, 0);

      glNormal3f(0, 0, -1);
      glVertex3d(0,       0, -6);
      glVertex3d(.75,     0, -6);
      glVertex3d(.75,  .875, -6);
      glVertex3d(0,    .875, -6);

      glNormal3f(0, 0, -1);
      glVertex3d(.75,      0, -2);
      glVertex3d(.875,    0, -2);
      glVertex3d(.875, .875, -2);
      glVertex3d(.75,   .875, -2);

      glNormal3f(-1, 0, 0);
      glVertex3d(0,    0,  0);
      glVertex3d(0,    0, -6);
      glVertex3d(0, .875, -6);
      glVertex3d(0, .875,  0);

      glNormal3f(1, 0, 0);
      glVertex3d(.875,    0,  0);
      glVertex3d(.875,    0, -2);
      glVertex3d(.875, .875, -2);
      glVertex3d(.875, .875,  0);

      glNormal3f(1, 0, 0);
      glVertex3d(.75,    0, -2);
      glVertex3d(.75,    0, -6);
      glVertex3d(.75, .875, -6);
      glVertex3d(.75, .875, -2);

      glEnd(); 
      break;

    // Key 88: White key block
    case 88:
      (playing && highlight) ? glColor3f(1,.4,.4) : glColor3f(1, 1, 1);
      glBegin(GL_QUADS);
      // Bottom
      glNormal3f(0, -1, 0);
      glVertex3d(0,    0,  0);
      glVertex3d(.875, 0,  0);
      glVertex3d(.875, 0, -6);
      glVertex3d(0,    0, -6);

      // Top
      glNormal3f(0, 1, 0);
      glVertex3d(0,    .875,  0);
      glVertex3d(.875, .875,  0);
      glVertex3d(.875, .875, -6);
      glVertex3d(0,    .875, -6);

      // Sides
      glNormal3f(0, 0, 1);
      glVertex3d(0,       0,  0);
      glVertex3d(.875,    0,  0);
      glVertex3d(.875, .875,  0);
      glVertex3d(0,    .875,  0);

      glNormal3f(0, 0, -1);
      glVertex3d(0,       0,  -6);
      glVertex3d(.875,    0,  -6);
      glVertex3d(.875, .875,  -6);
      glVertex3d(0,    .875,  -6);

      glNormal3f(-1, 0, 0);
      glVertex3d(0,    0,  0);
      glVertex3d(0,    0, -6);
      glVertex3d(0, .875, -6);
      glVertex3d(0, .875,  0);

      glNormal3f(1, 0, 0);
      glVertex3d(.875,    0,  0);
      glVertex3d(.875,    0, -6);
      glVertex3d(.875, .875, -6);
      glVertex3d(.875, .875,  0);

      glEnd();
      break;

    default:
      break;
  }

  glPopMatrix();
}

static void piano(double x, double y, double z,
                  double dx, double dy, double dz)
{
  glPushMatrix(); 
  glTranslated(x,y,z);
  glScaled(dx,dy,dz);
  
  float px = .65;       // Piano-key x position
  float py = -.66;      // Piano-key y position
  float pz = -.94;      // Piano-key z position  
  float scale = 36.7;   // Piano-key scale

  float pianoAmbient[4] =  {0, 0, 0, 1};
  float pianoDiffuse[4] =  {0.5880, 0.5880, 0.5880, 1};
  float pianoSpecular[4] = {0.5040, 0.5040, 0.5040, 1};
  float pianoShininess[1] = {10};
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, pianoAmbient);
  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, pianoDiffuse);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, pianoSpecular);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS, pianoShininess);

  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
  glBindTexture(GL_TEXTURE_2D,tex[0]);
  glStencilFunc(GL_ALWAYS, 0, -1);

  glPushMatrix();
  glScaled(scale, scale, scale);
  glTranslated(px, py, pz);
  glRotatef(90, 0, 1, 0);
  glCallList(obj);
  glPopMatrix();

  glDisable(GL_TEXTURE_2D);
  // White key distance
  float wkd  = 15./16.;
  // Various black key offsets from white keys
  float bkd  = 1/8.;
  float bkd2 = 2/8.;
  float bkd3 = 3/8.;
  float distanceCounter = 0;
  float distance;

  // Draw all the piano keys
  for(int i = 1; i <= 88; i++){
    switch(i%12){
      case 0:
        distance = distanceCounter*wkd-bkd2;
        break;
      case 2:
      case 7:
        distance = distanceCounter*wkd-bkd;
        break;
      case 5:
      case 10:
        distance = distanceCounter*wkd-bkd3;
        break;
      default:
        distance = distanceCounter*wkd;
        distanceCounter++;
        break;
    }
    pianoKey(i, distance,0,0,   1,1,1,
             playing[i], play_pos[i]);
  }

  glPopMatrix();
}


static void ball(double x,double y,double z,double r)
{
  int th,ph;
  glPushMatrix();
  glTranslated(x,y,z);
  glScaled(r,r,r);
  glColor3f(1,1,1);
  for (ph=-90;ph<90;ph+=10){
    glBegin(GL_QUAD_STRIP);
    for (th=0;th<=360;th+=20){
      Vertex(th,ph);
      Vertex(th,ph+10);
    }
  glEnd();
  }
  glPopMatrix();
}


void display()
{
  const double len=2.0;  //  Length of axes
  float Position[] = {X+6*Cos(Th),Y,Z+Sin(Th),1-inf};
  //  Erase the window and the depth buffer
  glClearStencil(0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
  //  Enable Z-buffering in OpenGL
  glEnable(GL_DEPTH_TEST);
  //  Undo previous transformations
  glLoadIdentity();
  //  Perspective - set eye position
  double Ex = -2*dim*Sin(th)*Cos(ph);
  double Ey = +2*dim        *Sin(ph);
  double Ez = +2*dim*Cos(th)*Cos(ph);
  gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
  glShadeModel(GL_SMOOTH);
  //  Light switch
  if (light)
  {
    //  Translate intensity to color vectors
    float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
    float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
    float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
    //  Spotlight color and direction
    float yellow[] = {1.0,1.0,1.0,1.0};

    //  Draw light position as ball (still no lighting here)
    if(showlight){
      ball(Position[0],Position[1],Position[2] , 0.1);      
    }
    //  OpenGL should normalize normal vectors
    glEnable(GL_NORMALIZE);
    //  Enable lighting
    glEnable(GL_LIGHTING);
    //  Location of viewer for specular calculations
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
    //  glColor sets ambient and diffuse color materials
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    //  Set specular colors
    glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
    glMaterialf(GL_FRONT,GL_SHININESS,shiny);
    //  Enable light 0
    glEnable(GL_LIGHT0);
    //  Set ambient, diffuse, specular components and position of light 0
    glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
    glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
    glLightfv(GL_LIGHT0,GL_POSITION,Position);
  }
  else
    glDisable(GL_LIGHTING);

  glEnable(GL_STENCIL_TEST);
  glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
 
  glPushMatrix();
  glTranslated(0, 0, 0);
  piano(-6.25,6.06,0, .25,.25,.25);
  glStencilFunc(GL_ALWAYS, 0, -1);

  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
  glBindTexture(GL_TEXTURE_2D,tex[1]);
  glBegin(GL_QUADS);
  // Floor
  glColor3f(1, 1, 1);
  glNormal3f(0, 1, 0);
  for(int i = -50; i <= 50; i++){
    for(int j = -50; j <= 50; j++){
      glTexCoord2f(i/10., j/10.); glVertex3d(i, 0, j); 
      glTexCoord2f(i/10., (j+1)/10.); glVertex3d(i, 0, j+1); 
      glTexCoord2f((i+1)/10., (j+1)/10.); glVertex3d(i+1, 0, j+1); 
      glTexCoord2f((i+1)/10., j/10.); glVertex3d(i+1, 0, j); 
    }
  }
  glEnd();

  // Walls
  glBindTexture(GL_TEXTURE_2D,tex[2]);
  glBegin(GL_QUADS);
  glNormal3f(0, 0, 1);
  glTexCoord2f(0,  0); glVertex3d(-50,  0, -50);
  glTexCoord2f(3.5, 0); glVertex3d( 50,  0, -50);
  glTexCoord2f(3.5, 5); glVertex3d( 50, 35, -50);
  glTexCoord2f(0,   5); glVertex3d(-50, 35, -50);
  glNormal3f(0, 0, -1);
  glTexCoord2f(0,  0); glVertex3d(-50,  0, 50);
  glTexCoord2f(0, 10); glVertex3d( 50,  0, 50);
  glTexCoord2f(7, 10); glVertex3d( 50, 35, 50);
  glTexCoord2f(7,  0); glVertex3d(-50, 35, 50);

  glNormal3f(1, 0, 0);
  glTexCoord2f(0,  0); glVertex3d(-50,  0,  50);
  glTexCoord2f(0, 10); glVertex3d(-50,  0, -50);
  glTexCoord2f(7, 10); glVertex3d(-50, 35, -50);
  glTexCoord2f(7,  0); glVertex3d(-50, 35,  50);

  glNormal3f(-1, 0, 0);
  glTexCoord2f(0,  0); glVertex3d(50,  0,  50);
  glTexCoord2f(0, 10); glVertex3d(50,  0, -50);
  glTexCoord2f(7, 10); glVertex3d(50, 35, -50);
  glTexCoord2f(7,  0); glVertex3d(50, 35,  50);

  glNormal3f(0, -1, 0);
  glTexCoord2f(0,   0); glVertex3d(-50, 35, -50);
  glTexCoord2f(0,  10); glVertex3d( 50, 35, -50);
  glTexCoord2f(10, 10); glVertex3d( 50, 35,  50);
  glTexCoord2f(10,  0); glVertex3d(-50, 35,  50);

  glEnd();
  glPopMatrix();

  glDisable(GL_TEXTURE_2D);
  glDisable(GL_LIGHTING);
  glColor3f(1,1,1);
  if (axes){
    glBegin(GL_LINES);
    glVertex3d(0.0,0.0,0.0);
    glVertex3d(len,0.0,0.0);
    glVertex3d(0.0,0.0,0.0);
    glVertex3d(0.0,len,0.0);
    glVertex3d(0.0,0.0,0.0);
    glVertex3d(0.0,0.0,len);
    glEnd();
    //  Label axes
    glRasterPos3d(len,0.0,0.0);
    Print("X");
    glRasterPos3d(0.0,len,0.0);
    Print("Y");
    glRasterPos3d(0.0,0.0,len);
    Print("Z");
  }
  //  Display parameters
  glWindowPos2i(5,5);
  Print("Angle=%d,%d  Dim=%.1f Projection=%s Light=%s Interval=%d",
    th,ph,dim,"Perpective",light?"On":"Off", interval);
  if (light){
    glWindowPos2i(5,65);
    Print("Direction=%d,%d", Th,Ph);
    glWindowPos2i(5,45);
    Print("LocalViewer=%s Position=%.1f,%.1f,%.1f,%.1f", local?"On":"Off", Position[0],Position[1],Position[2],Position[3]);
    glWindowPos2i(5,25);
    Print("Ambient=%d  Diffuse=%d Specular=%d Emission=%d Shininess=%.0f",ambient,diffuse,specular,emission,shiny);
 }
  //  Render the scene and make it visible
  ErrCheck("display");
  glFlush();
  SDL_GL_SwapBuffers();
}


// Play a note on the piano
static void playNote(int num){
  if(!playing[num] && num > 0 && num < 89){
    playing[num] = 1;
    play_pos[num] = 0;
    Mix_PlayChannel(-1, notes[num], 0);
    downTime[num] = down_len;
  }
}


int key()
{
  Uint8* keys = SDL_GetKeyState(NULL);
  int shift = SDL_GetModState()&KMOD_SHIFT;
  //  Exit on ESC
  if (keys[SDLK_ESCAPE])
    return 0;
  //  Reset view angle
  else if (keys[SDLK_0]){
    th = -35;
    ph = 40;
    dim = 11.5;
  }
  //  Toggle axes
  else if (keys[SDLK_b])
    axes = 1-axes;
  else if (keys[SDLK_m])
    light = 1-light;
  //  Toggle infinity
  else if (keys[SDLK_i])
    inf = 1-inf;
   
  // Piano playing functions
  if ((keys[SDLK_KP_MINUS] || keys[SDLK_MINUS]) && interval>1)
    interval--;
  if ((keys[SDLK_KP_PLUS] || keys[SDLK_EQUALS]) && interval<8)
    interval++;
  if(keys[SDLK_a])
    playNote((interval - 1)*11 + 1);
  if(keys[SDLK_s])
    playNote((interval - 1)*11 + 2);
  if(keys[SDLK_d])
    playNote((interval - 1)*11 + 3);
  if(keys[SDLK_f])
    playNote((interval - 1)*11 + 4);
  if(keys[SDLK_g])
    playNote((interval - 1)*11 + 5);
  if(keys[SDLK_h])
    playNote((interval - 1)*11 + 6);
  if(keys[SDLK_j])
    playNote((interval - 1)*11 + 7);
  if(keys[SDLK_k])
    playNote((interval - 1)*11 + 8);
  if(keys[SDLK_l])
    playNote((interval - 1)*11 + 9);
  if(keys[SDLK_SEMICOLON] || keys[SDLK_COLON])
    playNote((interval - 1)*11 + 10);
  if(keys[SDLK_QUOTE])
    playNote((interval - 1)*11 + 11);

  // Key highlighting
  else if (keys[SDLK_n])
    highlight = 1 - highlight;

  //  Change Light position
  else if (keys[SDLK_x] && !shift)
    X -= 0.01;
  else if (keys[SDLK_x] && shift)
    X += 0.01;
  else if (keys[SDLK_y] && !shift)
    Y -= 0.01;
  else if (keys[SDLK_y] && shift)
    Y += 0.01;
  else if (keys[SDLK_z] && !shift)
    Z -= 0.01;
  else if (keys[SDLK_z] && shift)
    Z += 0.01;
  
  // Show/Hide Light
  else if (keys[SDLK_COMMA])
    showlight = 1 - showlight;

  // Play songs
  else if (keys[SDLK_1]){
    song = 1 - song;
    song2 = 0;      
  }
  else if (keys[SDLK_2]){
    song = 0;      
    song2 = 1 - song2;
  }

  //  Increase/decrease asimuth
  else if (keys[SDLK_RIGHT])
    th += 5;
  else if (keys[SDLK_LEFT])
    th -= 5;
  //  Increase/decrease elevation
  else if (keys[SDLK_UP] && ph < 90)
    ph += 5;
  else if (keys[SDLK_DOWN] && ph > 5)
    ph -= 5;
  //  PageUp key - increase dim
  else if (keys[SDLK_PAGEDOWN] && dim < 18)
    dim += 0.1;
  //  PageDown key - decrease dim
  else if (keys[SDLK_PAGEUP] && dim>1)
    dim -= 0.1;

  shiny = shininess<0 ? 0 : pow(2.0,shininess);
  //  Wrap angles
  Th %= 360;
  Ph %= 360;
  th %= 360;
  ph %= 360;
  //  Update projection
  Project(fov,asp,dim);
  //  Tell GLUT it is necessary to redisplay the scene
  return 1;
}

void reshape(int width,int height)
{
  //  Ratio of the width to the height of the window
  asp = (height>0) ? (double)width/height : 1;
  //  Set the viewport to the entire window
  glViewport(0,0, width,height);
  //  Set projection
  Project(fov,asp,dim);
}

// Specify what happens when object is clicked.
void click(){
  int mouseX, mouseY;
  // Get mouse position
  SDL_GetMouseState(&mouseX, &mouseY);
 
  GLbyte color[4];
  GLfloat depth;
  GLuint index;

  // Read RGB, Depth, and Stencil buffers
  glReadPixels(mouseX, height - mouseY - 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
  glReadPixels(mouseX, height - mouseY - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
  glReadPixels(mouseX, height - mouseY - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

  // Error checking
  // printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u\n",
  //        mouseX, mouseY, color[0], color[1], color[2], color[3], depth, index);
  
  // Play note based on the object's stencil buffer value
  // if it is betweeen 1-88 (piano keys)
  if(index > 0 && index < 89){
    playNote(index);
  }
}


int main(int argc,char* argv[])
{
  int run=1;
  double t0=0;
  int counter = 0;
  SDL_Surface* screen;

  //  Initialize SDL
  SDL_Init(SDL_INIT_VIDEO);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 1);
  //  Set size, resizable and double buffering
  screen = SDL_SetVideoMode(width,height,0,SDL_OPENGL|SDL_RESIZABLE|SDL_DOUBLEBUF);
  if (!screen ) Fatal("Cannot set SDL video mode\n");
  //  Set window and icon labels
  SDL_WM_SetCaption("Piano Project- Vladimir Zhdanov- CSCI 4229","sdl20");
  //  Set screen size
  reshape(screen->w,screen->h);

  //  Load textures
  tex[0] = LoadTexBMP("obj/piano_texture_fixed.bmp");
  tex[1] = LoadTexBMP("obj/wood.bmp");
  tex[2] = LoadTexBMP("obj/wall.bmp");

  // Load obj file
  obj = LoadOBJ("obj/piano.obj");

  //  Initialize audio
  if (Mix_OpenAudio(44100,AUDIO_S16SYS,2,4096)) Fatal("Cannot initialize audio\n");
  
  //  Load note sounds from wav files
  char filepath[14];
  for(int i = 1; i < 89; i++){
    if(i < 10) sprintf(filepath, "notes/0%d.wav", i);
    else sprintf(filepath, "notes/%d.wav", i);          
    notes[i] = Mix_LoadWAV(filepath);
    if (!notes[i]) Fatal("Cannot load note %d\n", i);
  }

  //  SDL event loop
  ErrCheck("init");
  while (run)
  {
    //  Elapsed time in seconds
    double t = SDL_GetTicks()/1000.0;
    //  Process all pending events
    SDL_Event event;
    while (SDL_PollEvent(&event))
      switch (event.type){
        case SDL_VIDEORESIZE:
          screen = SDL_SetVideoMode(event.resize.w,event.resize.h,0,SDL_OPENGL|SDL_RESIZABLE|SDL_DOUBLEBUF);
          reshape(screen->w,screen->h);
          break;
        case SDL_QUIT:
          run = 0;
          break;
        case SDL_KEYDOWN:
          run = key();
          t0 = t+0.5;  // Wait 1/2 s before repeating
          break;
        case SDL_MOUSEBUTTONDOWN:
          click();
          break;
        default:
          break;
    }
    //  Repeat key every 50 ms
    if (t-t0>0.05){
      run = key();
      t0 = t;
    }
    //  Display
    Th = fmod(90*t,360.0);
    display();

    // Counts how long the key has been pressed down
    for(int i = 1; i < 89; i++){
      // Key moving down animation
      if(playing[i] && play_pos[i] < down_len){
        play_pos[i] += 4 * delay;
      }
      // Key moving back up
      else if(!playing[i] && play_pos[i] > 0){
        play_pos[i] -= 5 * delay;
      }
      if(downTime[i]){
        downTime[i] -= delay;
        if(downTime[i] <= 0){
          playing[i] = 0;
        } 
      } 
    }
    
    // Play/Stop song 1
    if(song && current < songlength && counter >= pauses[current]){
      playNote(songnotes[current]);
      current++;
      counter = 0;
    }
    else if(!song){
      current = 0;
    }
    else if(song && current >= songlength){
      song = 0;
      current = 0;
     }
    // Play/Stop song 2
    if(song2 && current2 < songlength2 && counter >= pauses2[current2]){
      playNote(songnotes2[current2]);
      playNote(songleft2[current2]);
      current2++;
      counter = 0;
    }
    else if(!song2){
      current2 = 0;
    }
    else if(song2 && current2 >= songlength2){
      song2 = 0;
      current2 = 0;
    }
    //  Slow down display rate to about 100 fps by sleeping 5ms
    SDL_Delay(delay);

    // Counter used to time pauses when songs are playing
    counter++;
    counter %= 10000;
  }
  //  Shut down SDL
  Mix_CloseAudio();
  SDL_Quit();
  return 0;
}
