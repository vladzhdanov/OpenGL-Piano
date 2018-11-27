/*
 *  CSCI 4229 Project: Piano.
 *
 *  Key bindings:
 *
 */
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "CSCIx229.h"
int axes=1;       //  Display axes
int mode=1;       //  Projection mode
int side=0;       //  Two sided mode
int ntex=1;       //  Texture mode
int th=0,ph=0;    //  View angles
int Th=0,Ph=30;   //  Light angles
float sco=180;    //  Spot cutoff angle
float Exp=0;      //  Spot exponent
int at0=100;      //  Constant  attenuation %
int at1=0;        //  Linear    attenuation %
int at2=0;        //  Quadratic attenuation %
int fov=53;       //  Field of view (for perspective)
int light=0;      //  Lighting
double asp=1;     //  Aspect ratio
double dim=4;     //  Size of world
// Light values
int num       =   1;  // Number of quads
int inf       =   0;  // Infinite distance light
int smooth    =   1;  // Smooth/Flat shading
int local     =   0;  // Local Viewer Model
int emission  =   0;  // Emission intensity (%)
int ambient   =   0;  // Ambient intensity (%)
int diffuse   = 100;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shiny   =   1; // Shininess (value)
float X       = 0;    // Light X position
float Y       = 0;    // Light Y position
float Z       = 1;    // Light Z position
// Piano values
int delay = 5;
int interval = 1;
int playing[89];
Mix_Chunk* notes[89];
int downTime[89];

static void Vertex(double th,double ph)
{
   glVertex3d(Sin(th)*Cos(ph),Cos(th)*Cos(ph),Sin(ph));
}

static void pianoKey(int num,
      double x, double y, double z,
      double dx, double dy, double dz, 
      double playing, double temp){

  glPushMatrix();
  glTranslated(x,y,z);
  glScaled(dx,dy,dz);

  // First key has a unique shape 
  if(num == 1){
    num = -1;
  }
  // Except for the very first and last key,
  // the piano repeats the same pattern of notes
  // every octave (12 steps)
  if(num != 88 && num != -1 && num >= 12){
    num %= 12;
  }
  
  if(playing == 1){
      glTranslated(0,0,-6);
      if(num == 0 || num == 2 || num == 5 || num == 7 || num == 10) 
          glRotatef(3, 1,0,0);
      else 
          glRotatef(6 , 1,0,0);
      glTranslated(0,0,6);
  }
    //   case 0:
    // case 2:
    // case 5:
    // case 7:
    // case 10:

  switch(num){
    // White key with hole on right
    case 4:
    case 9:
      glColor3f(1, 1, 1);
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
      glColor3f(.2, .2, .2);
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
      glColor3f(1, 1, 1);
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
      glColor3f(1, 1, 1);
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
      glColor3f(1, 1, 1);
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
      glColor3f(1, 1, 1);
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
    glColor3f(1, 1, 1);
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
      glColor3f(1, 1, 1);
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
                  double dx, double dy, double dz){
  glPushMatrix(); 
  glTranslated(x,y,z);
  glScaled(dx,dy,dz);

  // White key distance
  float wkd  = 15./16.;
  // Various black key offsets from white keys
  float bkd  = 1/8.;
  float bkd2 = 3/8.;
  float bkd3 = 2/8.;

  pianoKey(1,  0*wkd,0,0,       1,1,1, playing[1 ],ph);
  pianoKey(2,  1*wkd-bkd,0,0,   1,1,1, playing[2 ],ph);
  pianoKey(3,  1*wkd,0,0,       1,1,1, playing[3 ],ph);
  pianoKey(4,  2*wkd,0,0,       1,1,1, playing[4 ],ph);
  pianoKey(5,  3*wkd-bkd2,0,0,  1,1,1, playing[5 ],ph);
  pianoKey(6,  3*wkd,0,0,       1,1,1, playing[6 ],ph);
  pianoKey(7,  4*wkd-bkd,0,0,   1,1,1, playing[7 ],ph);
  pianoKey(8,  4*wkd,0,0,       1,1,1, playing[8 ],ph);
  pianoKey(9,  5*wkd,0,0,       1,1,1, playing[9 ],ph);
  pianoKey(10, 6*wkd-bkd2,0,0,  1,1,1, playing[10],ph);
  pianoKey(11, 6*wkd,0,0,       1,1,1, playing[11],ph);
  
  pianoKey(12, 7*wkd-bkd3,0,0,  1,1,1, playing[12],ph);
  pianoKey(13, 7*wkd,0,0,       1,1,1, playing[13],ph);
  pianoKey(14, 8*wkd-bkd,0,0,   1,1,1, playing[14],ph);
  pianoKey(15, 8*wkd,0,0,       1,1,1, playing[15],ph);
  pianoKey(16, 9*wkd,0,0,       1,1,1, playing[16],ph);
  pianoKey(17, 10*wkd-bkd2,0,0, 1,1,1, playing[17],ph);
  pianoKey(18, 10*wkd,0,0,      1,1,1, playing[18],ph);
  pianoKey(19, 11*wkd-bkd,0,0,  1,1,1, playing[19],ph);
  pianoKey(20, 11*wkd,0,0,      1,1,1, playing[20],ph);
  pianoKey(21, 12*wkd,0,0,      1,1,1, playing[21],ph);
  pianoKey(22, 13*wkd-bkd2,0,0, 1,1,1, playing[22],ph);
  pianoKey(23, 13*wkd,0,0,      1,1,1, playing[23],ph);

  pianoKey(24, 14*wkd-bkd3,0,0, 1,1,1, playing[24],ph);
  pianoKey(25, 14*wkd,0,0,      1,1,1, playing[25],ph);
  pianoKey(26, 15*wkd-bkd,0,0,  1,1,1, playing[26],ph);
  pianoKey(27, 15*wkd,0,0,      1,1,1, playing[27],ph);
  pianoKey(28, 16*wkd,0,0,      1,1,1, playing[28],ph);
  pianoKey(29, 17*wkd-bkd2,0,0, 1,1,1, playing[29],ph);
  pianoKey(30, 17*wkd,0,0,      1,1,1, playing[30],ph);
  pianoKey(31, 18*wkd-bkd,0,0,  1,1,1, playing[31],ph);
  pianoKey(32, 18*wkd,0,0,      1,1,1, playing[32],ph);
  pianoKey(33, 19*wkd,0,0,      1,1,1, playing[33],ph);
  pianoKey(34, 20*wkd-bkd2,0,0, 1,1,1, playing[34],ph);
  pianoKey(35, 20*wkd,0,0,      1,1,1, playing[35],ph);

  pianoKey(36, 21*wkd-bkd3,0,0, 1,1,1, playing[36],ph);
  pianoKey(37, 21*wkd,0,0,      1,1,1, playing[37],ph);
  pianoKey(38, 22*wkd-bkd,0,0,  1,1,1, playing[38],ph);
  pianoKey(39, 22*wkd,0,0,      1,1,1, playing[39],ph);
  pianoKey(40, 23*wkd,0,0,      1,1,1, playing[40],ph);
  pianoKey(41, 24*wkd-bkd2,0,0, 1,1,1, playing[41],ph);
  pianoKey(42, 24*wkd,0,0,      1,1,1, playing[42],ph);
  pianoKey(43, 25*wkd-bkd,0,0,  1,1,1, playing[43],ph);
  pianoKey(44, 25*wkd,0,0,      1,1,1, playing[44],ph);
  pianoKey(45, 26*wkd,0,0,      1,1,1, playing[45],ph);
  pianoKey(46, 27*wkd-bkd2,0,0, 1,1,1, playing[46],ph);
  pianoKey(47, 27*wkd,0,0,      1,1,1, playing[47],ph);

  pianoKey(48, 28*wkd-bkd3,0,0, 1,1,1, playing[48],ph);
  pianoKey(49, 28*wkd,0,0,      1,1,1, playing[49],ph);
  pianoKey(50, 29*wkd-bkd,0,0,  1,1,1, playing[50],ph);
  pianoKey(51, 29*wkd,0,0,      1,1,1, playing[51],ph);
  pianoKey(52, 30*wkd,0,0,      1,1,1, playing[52],ph);
  pianoKey(53, 31*wkd-bkd2,0,0, 1,1,1, playing[53],ph);
  pianoKey(54, 31*wkd,0,0,      1,1,1, playing[54],ph);
  pianoKey(55, 32*wkd-bkd,0,0,  1,1,1, playing[55],ph);
  pianoKey(56, 32*wkd,0,0,      1,1,1, playing[56],ph);
  pianoKey(57, 33*wkd,0,0,      1,1,1, playing[57],ph);
  pianoKey(58, 34*wkd-bkd2,0,0, 1,1,1, playing[58],ph);
  pianoKey(59, 34*wkd,0,0,      1,1,1, playing[59],ph);

  pianoKey(60, 35*wkd-bkd3,0,0, 1,1,1, playing[60],ph);
  pianoKey(61, 35*wkd,0,0,      1,1,1, playing[61],ph);
  pianoKey(62, 36*wkd-bkd,0,0,  1,1,1, playing[62],ph);
  pianoKey(63, 36*wkd,0,0,      1,1,1, playing[63],ph);
  pianoKey(64, 37*wkd,0,0,      1,1,1, playing[64],ph);
  pianoKey(65, 38*wkd-bkd2,0,0, 1,1,1, playing[65],ph);
  pianoKey(66, 38*wkd,0,0,      1,1,1, playing[66],ph);
  pianoKey(67, 39*wkd-bkd,0,0,  1,1,1, playing[67],ph);
  pianoKey(68, 39*wkd,0,0,      1,1,1, playing[68],ph);
  pianoKey(69, 40*wkd,0,0,      1,1,1, playing[69],ph);
  pianoKey(70, 41*wkd-bkd2,0,0, 1,1,1, playing[70],ph);
  pianoKey(71, 41*wkd,0,0,      1,1,1, playing[71],ph);

  pianoKey(72, 42*wkd-bkd3,0,0, 1,1,1, playing[72],ph);
  pianoKey(73, 42*wkd,0,0,      1,1,1, playing[73],ph);
  pianoKey(74, 43*wkd-bkd,0,0,  1,1,1, playing[74],ph);
  pianoKey(75, 43*wkd,0,0,      1,1,1, playing[75],ph);
  pianoKey(76, 44*wkd,0,0,      1,1,1, playing[76],ph);
  pianoKey(77, 45*wkd-bkd2,0,0, 1,1,1, playing[77],ph);
  pianoKey(78, 45*wkd,0,0,      1,1,1, playing[78],ph);
  pianoKey(79, 46*wkd-bkd,0,0,  1,1,1, playing[79],ph);
  pianoKey(80, 46*wkd,0,0,      1,1,1, playing[80],ph);
  pianoKey(81, 47*wkd,0,0,      1,1,1, playing[81],ph);
  pianoKey(82, 48*wkd-bkd2,0,0, 1,1,1, playing[82],ph);
  pianoKey(83, 48*wkd,0,0,      1,1,1, playing[83],ph); 

  pianoKey(84, 49*wkd-bkd3,0,0, 1,1,1, playing[84],ph);
  pianoKey(85, 49*wkd,0,0,      1,1,1, playing[85],ph);
  pianoKey(86, 50*wkd-bkd,0,0,  1,1,1, playing[86],ph);
  pianoKey(87, 50*wkd,0,0,      1,1,1, playing[87],ph);
  pianoKey(88, 51*wkd,0,0,      1,1,1, playing[88],ph);  

  glPopMatrix();
}


static void ball(double x,double y,double z,double r)
{
   int th,ph;
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  Bands of latitude
   glColor3f(1,1,0);
   for (ph=-90;ph<90;ph+=10)
   {
      glBegin(GL_QUAD_STRIP);
      for (th=0;th<=360;th+=20)
      {
         Vertex(th,ph);
         Vertex(th,ph+10);
      }
      glEnd();
   }
   //  Undo transofrmations
   glPopMatrix();
}


void display()
{
   // int i,j;
   const double len=2.0;  //  Length of axes
   // double mul = 2.0/num;
   float Position[] = {X+Cos(Th),Y+Sin(Th),Z,1-inf};
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective - set eye position
   if (mode)
   {
      double Ex = -2*dim*Sin(th)*Cos(ph);
      double Ey = +2*dim        *Sin(ph);
      double Ez = +2*dim*Cos(th)*Cos(ph);
      gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   }
   //  Orthogonal - set world orientation
   else
   {
      glRotatef(ph,1,0,0);
      glRotatef(th,0,1,0);
   }
   glShadeModel(smooth?GL_SMOOTH:GL_FLAT);
   //  Light switch
   if (light)
   {
      //  Translate intensity to color vectors
      float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
      float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
      float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
      //  Spotlight color and direction
      float yellow[] = {1.0,1.0,0.0,1.0};
      float Direction[] = {Cos(Th)*Sin(Ph),Sin(Th)*Sin(Ph),-Cos(Ph),0};
      //  Draw light position as ball (still no lighting here)
      ball(Position[0],Position[1],Position[2] , 0.1);
      //  OpenGL should normalize normal vectors
      glEnable(GL_NORMALIZE);
      //  Enable lighting
      glEnable(GL_LIGHTING);
      //  Location of viewer for specular calculations
      glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
      //  Two sided mode
      glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,side);
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
      //  Set spotlight parameters
      glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,Direction);
      glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,sco);
      glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,Exp);
      //  Set attenuation
      glLightf(GL_LIGHT0,GL_CONSTANT_ATTENUATION ,at0/100.0);
      glLightf(GL_LIGHT0,GL_LINEAR_ATTENUATION   ,at1/100.0);
      glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION,at2/100.0);
   }
   else
      glDisable(GL_LIGHTING);

   piano(-6.25,0,0, .25,.25,.25);
   // pianoKey(6, 0,0,0, 1,1,1, th, ph);
   //  Enable textures
   // if (ntex)
   //    glEnable(GL_TEXTURE_2D);
   // else
      // glDisable(GL_TEXTURE_2D);
   // glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   // //  Draw the wall
   // glColor3f(1.0,1.0,1.0);
   // glNormal3f(0,0,1); 
   // glBegin(GL_QUADS);
   // for (i=0;i<num;i++)
   //    for (j=0;j<num;j++)
   //    {
   //       glTexCoord2d(mul*(i+0),mul*(j+0)); glVertex2d(5*mul*(i+0)-5,5*mul*(j+0)-5);
   //       glTexCoord2d(mul*(i+1),mul*(j+0)); glVertex2d(5*mul*(i+1)-5,5*mul*(j+0)-5);
   //       glTexCoord2d(mul*(i+1),mul*(j+1)); glVertex2d(5*mul*(i+1)-5,5*mul*(j+1)-5);
   //       glTexCoord2d(mul*(i+0),mul*(j+1)); glVertex2d(5*mul*(i+0)-5,5*mul*(j+1)-5);
   //    }
   // glEnd();
   // glDisable(GL_TEXTURE_2D);
   //  Draw axes - no lighting from here on

   glDisable(GL_LIGHTING);
   glColor3f(1,1,1);
   if (axes)
   {
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
     th,ph,dim,mode?"Perpective":"Orthogonal",light?"On":"Off", interval);
   if (light)
   {
      glWindowPos2i(5,65);
      Print("Cutoff=%.0f Exponent=%.1f Direction=%d,%d Attenuation=%.2f,%.2f,%.2f",sco,Exp,Th,Ph,at0/100.0,at1/100.0,at2/100.0);
      glWindowPos2i(5,45);
      Print("Model=%s LocalViewer=%s TwoSided=%s Position=%.1f,%.1f,%.1f,%.1f Num=%d",smooth?"Smooth":"Flat",local?"On":"Off",side?"On":"Off",Position[0],Position[1],Position[2],Position[3],num);
      glWindowPos2i(5,25);
      Print("Ambient=%d  Diffuse=%d Specular=%d Emission=%d Shininess=%.0f",ambient,diffuse,specular,emission,shiny);
   }
   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   SDL_GL_SwapBuffers();
}


static void playNote(int num){
  if(!playing[num]){
    playing[num] = 1;
    Mix_PlayChannel(-1, notes[num], 0);
    downTime[num] = 100;
  }
}

/*
 *  Call this routine when a key is pressed
 *     Returns 1 to continue, 0 to exit
 */
int key()
{
   Uint8* keys = SDL_GetKeyState(NULL);
   int shift = SDL_GetModState()&KMOD_SHIFT;
   //  Exit on ESC
   if (keys[SDLK_ESCAPE])
      return 0;
   //  Reset view angle
   else if (keys[SDLK_0])
      X = Y = th = ph = 0;
   //  Toggle axes
   else if (keys[SDLK_b])
      axes = 1-axes;
   // //  Toggle textures
   // else if (keys[SDLK_t])
   //    ntex = 1-ntex;
   //  Toggle lighting
   else if (keys[SDLK_m])
      light = 1-light;
   //  Toggle infinity
   else if (keys[SDLK_i])
      inf = 1-inf;

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

   //  Light position
   else if (keys[SDLK_x] && !shift)
      X -= 0.1;
   else if (keys[SDLK_x] && shift)
      X += 0.1;
   else if (keys[SDLK_y] && !shift)
      Y -= 0.1;
   else if (keys[SDLK_y] && shift)
      Y += 0.1;
   else if (keys[SDLK_z] && !shift)
      Z -= 0.1;
   else if (keys[SDLK_z] && shift)
      Z += 0.1;
   //  Increase/decrease asimuth
   else if (keys[SDLK_RIGHT])
      th += 5;
   else if (keys[SDLK_LEFT])
      th -= 5;
   //  Increase/decrease elevation
   else if (keys[SDLK_UP])
      ph += 5;
   else if (keys[SDLK_DOWN])
      ph -= 5;
   //  PageUp key - increase dim
   else if (keys[SDLK_PAGEDOWN])
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (keys[SDLK_PAGEUP] && dim>1)
      dim -= 0.1;
   //  Smooth color model
   else if (keys[SDLK_F1])
      smooth = 1-smooth;
   //  Local Viewer
   else if (keys[SDLK_F2])
      local = 1-local;
   //  Two sided mode
   else if (keys[SDLK_F3])
      side = 1-side;
   //  Translate shininess power to value (-1 => 0)
   shiny = shininess<0 ? 0 : pow(2.0,shininess);
   //  Wrap angles
   Th %= 360;
   Ph %= 360;
   th %= 360;
   ph %= 360;
   //  Update projection
   Project(mode?fov:0,asp,dim);
   //  Tell GLUT it is necessary to redisplay the scene
   return 1;
}

/*
 *  Call this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Set projection
   Project(mode?fov:0,asp,dim);
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   int run=1;
   double t0=0;
   SDL_Surface* screen;

   //  Initialize SDL
   SDL_Init(SDL_INIT_VIDEO);
   //  Set size, resizable and double buffering
   screen = SDL_SetVideoMode(750,750,0,SDL_OPENGL|SDL_RESIZABLE|SDL_DOUBLEBUF);
   if (!screen ) Fatal("Cannot set SDL video mode\n");
   //  Set window and icon labels
   SDL_WM_SetCaption("Piano Project- Vladimir Zhdanov","sdl20");
   //  Set screen size
   reshape(screen->w,screen->h);

   //  Load textures
   // LoadTexBMP("brick.bmp");

   //  Initialize audio
   if (Mix_OpenAudio(44100,AUDIO_S16SYS,2,4096)) Fatal("Cannot initialize audio\n");
  
   //  Load note sounds from wav files
   char filepath[14];
   for(int i = 1; i < 89; i++){
      if(i < 10) sprintf(filepath, "notes/0%d.wav", i);
      else sprintf(filepath, "notes/%d.wav", i);          
      notes[i] = Mix_LoadWAV(filepath);
      if (!notes[i]) Fatal("Cannot load note %d\n", i);
      // printf("%s\n", filepath);
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
         switch (event.type)
         {
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
               break;
            default:
               //  Do nothing
               break;
         }
      //  Repeat key every 50 ms
      if (t-t0>0.05)
      {
         run = key();
         t0 = t;
      }
      //  Display
      Th = fmod(90*t,360.0);
      display();

      // Counts how long the key has been pressed down
      for(int i = 1; i < 89; i++){
         if(downTime[i]){
           downTime[i] -= delay;
           if(!downTime[i]) playing[i] = 0; 
         } 
      }
      //  Slow down display rate to about 100 fps by sleeping 5ms
      SDL_Delay(delay);
   }
   //  Shut down SDL
   Mix_CloseAudio();
   SDL_Quit();
   return 0;
}
