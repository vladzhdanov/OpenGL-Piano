/*
 *  HW 6: Textures
 *
 *  Expands the scene from HW 5 by adding textures
 *
 *  Key bindings:
 *  /          Toggle axes
 *  arrows     Change view angle
 *  0          Reset view angle
 *  +/-        Increase/Decrease FOV
 *  PgDn/PgUp  Zoom in and out 
 *  w/s        Move forward/backwards (First Person Mode)
 *  a/d        Rotate the camera left/right (First Person Mode)
 *  r          Reset First Person position/camera
 *  m          Cycle between projection modes
 *  l/L        Toggle lighting
 *  ;          Toggle light movement
 *  ]/[        Increase/Decrease light elevation
 *  F12        Decrease light rotation distance
 *  \          Reset light elevation/distance
 *  X/x        Increase/Decrease ambient light level
 *  C/c        Increase/Decrease diffuse light level
 *  V/v        Increase/Decrease specular light level
 *  B/b        Increase/Decrease emission light level
 *  N/n        Increase/Decrease shininess level
 *  '          Reset light levels
 *  ESC        Exit
 */

// Parts of this code were adapted from examples 8, 9, 13, 14, and 15 on Moodle,
// along with my code for HW 5.
#include "CSCIx229.h"
int th=0;         //  Azimuth of view angle
int ph=30;        //  Elevation of view angle
int fov=55;       //  Field of view (for perspective)
int axes=1;       //  Display axes
int mode=1;       //  What to display
int wide=600;     //  Initial window width
int high=600;     //  Initial window height
double asp=1;     //  Initial aspect ratio
double dim=5.0;   //  Initial size of the world

// First-person navigation values
double eyeX = 0;    // Initial Eye Position
double eyeY = .75;
double eyeZ = 10;
double cameraX = 0; // Initial Location the Camera is Looking
double cameraY = 0; 
double cameraZ = 0; 
int theta = 0.0;    // Initial Camera Rotation

// Light values
int move      =   1;  // Light movement
int light     =   1;  // Light switch
int one       =   1;  // Unit value
int distance  = 5.5;  // Light distance
int inc       =  10;  // Ball increment
int smooth    =   1;  // Smooth/Flat shading
int local     =   0;  // Local Viewer Model
int emission  =   0;  // Emission intensity (%)
int ambient   =  30;  // Ambient intensity (%)
int diffuse   = 100;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shiny   =   1;  // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  = 4.5;  // Elevation of light

// Textures
unsigned int texture[9];  //  Texture names

void reshape(int width,int height)
{
  //  Ratio of the width to the height of the window
  asp = (height>0) ? (double)width/height : 1;
  //  Set the viewport to the entire window
  glViewport(0,0, width,height);
  //  Set projection
  Project(mode?fov:0, asp, dim);
}

void idle()
{
  //  Elapsed time in seconds
  double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
  zh = fmod(90*t,360.0);
  //  Tell GLUT it is necessary to redisplay the scene
  glutPostRedisplay();
  Project(mode?fov:0, asp, dim);
}

static void Vertex(double th,double ph)
{
  double x = Sin(th)*Cos(ph);
  double y = Cos(th)*Cos(ph);
  double z =         Sin(ph);
  glNormal3d(x,y,z);
  glVertex3d(x,y,z);
}

static void cylinder(double x, double y, double z,double r, double h)
{
  float white[] = {1,1,1,1};
  float black[] = {0,0,0,1};
  glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

  glPushMatrix();
  glTranslated(x, y, z);

  // Draw the circular tube
  glBindTexture(GL_TEXTURE_2D,texture[8]);
  // glColor3f(.4,0,0);
  glColor3f(1,.7,.7);
  glBegin(GL_QUAD_STRIP);
  for(double i = 0; i <= 365; i+=1){
  glNormal3f(Cos(i), 1, Sin(i));
  glTexCoord2f((float)Cos(i) * r,1);
  glVertex3f(r * Cos(i), h, r * Sin(i));
  glTexCoord2f((float)Cos(i) * r,0);
  glVertex3f(r * Cos(i), -h, r * Sin(i));
  }
  glEnd();

  // Draw both ends 
  glColor3f(.1,.1,.1);
  glBegin(GL_TRIANGLE_FAN);
  glNormal3f(0, 1, 0);
  glVertex3f(0, h, 0);
  for(double i = 0; i <= 365*r*4; i += 5){
  glVertex3f(r * Cos(i), h, r*Sin(i));
  }
  glEnd();

  glBegin(GL_TRIANGLE_FAN);
  glNormal3f(0, -1, 0);
  glVertex3f(0, h, 0);
  for(double i = 0; i <= 365*r*4; i += .05){
  glVertex3f(r * Cos(i), -h, r*Sin(i));
  }
  glEnd();

  glPopMatrix();
}

static void sphere2(double x,double y,double z,double r)
{
  const int d=5;
  int th,ph; 
  float yellow[] = {1.0,1.0,0.0,1.0};
  float Emission[]  = {0.0,0.0,0.01*emission,1.0};

  //  Save transformation
  glPushMatrix();
  //  Offset and scale
  glTranslated(x,y,z);
  glScaled(r,r,r);

  glMaterialf(GL_FRONT,GL_SHININESS,shiny);
  glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
  glMaterialfv(GL_FRONT,GL_EMISSION,Emission);

  //  Latitude bands
  glBindTexture(GL_TEXTURE_2D,texture[7]);  
  for (ph=-90;ph<90;ph+=d)
  {
    glBegin(GL_QUAD_STRIP);
    for (th=0;th<=360;th+=d)
    {
       glTexCoord2f((float)th/360.,(float)ph/360.);
       Vertex(th,ph);
       Vertex(th,ph+d);
    }
    glEnd();
  }

  //  Undo transformations
  glPopMatrix();
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
  const double len=1.5;  //  Length of axes
  //  Erase the window and the depth buffer
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  //  Enable Z-buffering in OpenGL
  glEnable(GL_DEPTH_TEST);
  //  Undo previous transformations
  glLoadIdentity();

  // First Person
  if (mode == 2) {
    cameraX = dim * Sin(theta);
    cameraZ = -dim * Cos(theta);

    gluLookAt(eyeX, eyeY, eyeZ, 
              cameraX + eyeX, cameraY + eyeY, cameraZ + eyeZ, 
              0, 1, 0);
  }
  // Perspective
  else if (mode == 1) {
       // Return to the position of the normal perspective camera
       gluLookAt(-2*dim*Sin(th)*Cos(ph), 2*dim*Sin(ph), 2*dim*Cos(th)*Cos(ph),
                 0, 0, 0,
                 0, Cos(ph), 0); // Up vector of top-view perspective camera depends on the elevation
  }
  //  Orthogonal
  else{
       //  Set view angle
       glRotatef(ph,1,0,0);
       glRotatef(th,0,1,0);
  }
  //  Flat or smooth shading
  glShadeModel(smooth ? GL_SMOOTH : GL_FLAT);
  //  Light switch
  if (light)
  {
    //  Translate intensity to color vectors
    float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
    float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
    float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
    //  Light position
    float Position[]  = {distance*Cos(zh),ylight,distance*Sin(zh),1.0};
    //  Draw light position as ball (still no lighting here)
    glColor3f(1,1,1);
    sphere2(Position[0],Position[1],Position[2] , 0.2);
    //  OpenGL should normalize normal vectors
    glEnable(GL_NORMALIZE);
    //  Enable lighting
    glEnable(GL_LIGHTING);
    //  Location of viewer for specular calculations
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
    //  glColor sets ambient and diffuse color materials
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    //  Enable light 0
    glEnable(GL_LIGHT0);
    //  Set ambient, diffuse, specular components and position of light 0
    glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
    glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
    glLightfv(GL_LIGHT0,GL_POSITION,Position);
  }else
    glDisable(GL_LIGHTING);

  // Enable Textures
  // glEnable(GL_TEXTURE_2D);
  // glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
  // // Generates 5 houses
  // house(5,1,0,         1,1,1,         270);
  // house(3.5,1,-3.5,    1.1,1,1.1,     315);
  // house(0,1.25,-5,       1,1.25,1,      0);
  // house(-3.5,1,-3.5,   1.1,1,1.1,     45);
  // house(-5,1,0,        1,1,1,         90);

  // // Grass  
  // glBindTexture(GL_TEXTURE_2D,texture[0]);
  // // glColor3f(0,.5,0);
  // glColor3f(1,1,1);
  // glBegin(GL_QUADS);
  // glNormal3f(0, 1, 0);
  // glTexCoord2f(0,0); glVertex3f(-20 ,0   ,-20);
  // glTexCoord2f(20,0); glVertex3f( 20 ,0   ,-20);
  // glTexCoord2f(20,20); glVertex3f( 20 ,0   ,20);
  // glTexCoord2f(0,20); glVertex3f(-20 ,0   ,20);
  // glEnd();


  // // Sidewalk
  // glBindTexture(GL_TEXTURE_2D,texture[2]);
  // glColor3f(1,1,1);
  // // glColor3f(.6,.6,.6);
  // glBegin(GL_TRIANGLE_FAN);
  // glNormal3f(0, 1, 0);
  // glVertex3f(0, .001, 0);
  // for(double i = 0; i <= 361; i += .05){
  //   glTexCoord2f(4*Cos(i), 4*Sin(i));
  //   glVertex3f(4 * Cos(i), .001, 4 * Sin(i));
  // }
  // glEnd();


  // glBegin(GL_QUADS);
  // glNormal3f(0, 1, 0);
  // glTexCoord2f(0,0); glVertex3f(1,.001,3);
  // glTexCoord2f(1,0); glVertex3f(1.5,.001,3);
  // glTexCoord2f(1,17); glVertex3f(1.5,.001,20);
  // glTexCoord2f(0,17); glVertex3f(1,.001,20);

  // glNormal3f(0, 1, 0);
  // glTexCoord2f(1,0); glVertex3f(-1,.001,3);
  // glTexCoord2f(0,0); glVertex3f(-1.5,.001,3);
  // glTexCoord2f(0,17); glVertex3f(-1.5,.001,20);
  // glTexCoord2f(1,17); glVertex3f(-1,.001,20);
  // glEnd();



  // // Road part of cul de sac
  // glColor3f(1,1,1);
  // // glColor3f(.2,.2,.2);
  // glBindTexture(GL_TEXTURE_2D,texture[1]);
  // glBegin(GL_TRIANGLE_FAN);
  // glNormal3f(0, 1, 0);
  // glVertex3f(0, .002, 0);
  // for(double i = 0; i <= 361; i += .05){
  //   glTexCoord2f(Cos(i),Sin(i));
  //   glVertex3f(3.5 * Cos(i), .002, 3.5*Sin(i));
  // }
  // glEnd();

  // // Generate the road
  // glBegin(GL_QUADS);
  // glNormal3f(0, 1, 0);
  // glTexCoord2f(0,0); glVertex3f(-1,.002,3);
  // glTexCoord2f(1,0); glVertex3f(1,.002,3);
  // glTexCoord2f(1,17); glVertex3f(1,.002,20);
  // glTexCoord2f(0,17); glVertex3f(-1,.002,20);
  // glEnd();

  // glDisable(GL_TEXTURE_2D);
  glDisable(GL_LIGHTING);
  //  Draw axes
  glColor3f(1,1,1);
  if (axes)
  {
    glBegin(GL_LINES);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(len,0.0,0.0);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,len,0.0);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,0.0,len);
    glEnd();
    //  Label axes
    glRasterPos3d(len,0.0,0.0);
    Print("X");
    glRasterPos3d(0.0,len,0.0);
    Print("Y");
    glRasterPos3d(0.0,0.0,len);
    Print("Z");
  }

  //  Five pixels from the lower left corner of the window
  glWindowPos2i(5,45);
  // Print the correct mode name depending on the mode.
  if(mode == 2){
    Print("Angle=%d,%d   dim:%.1f   FOV:%d   Projection:%s",th,ph,dim,fov,"First Person");
  }else{
    Print("Angle=%d,%d   dim:%.1f   FOV:%d   Projection:%s",th,ph,dim,fov,mode?"Perpective":"Orthogonal");
  }
  glWindowPos2i(5,25);
  Print("Ambient=%d   Diffuse=%d   Specular=%d   Emission=%d   Shininess=%.0f",ambient,diffuse,specular,emission,shiny);
  //  Render the scene
  glFlush();
  //  Make the rendered scene visible
  glutSwapBuffers();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
  //  Right arrow key - increase angle by 5 degrees
  if (key == GLUT_KEY_RIGHT)
    th += 5;
  //  Left arrow key - decrease angle by 5 degrees
  else if (key == GLUT_KEY_LEFT)
    th -= 5;
  //  Up arrow key - increase elevation by 5 degrees
  else if (key == GLUT_KEY_UP && ph < 90)
    ph += 5;
  //  Down arrow key - decrease elevation by 5 degrees
  else if (key == GLUT_KEY_DOWN && ph > 0)
    ph -= 5;
  else if (key == GLUT_KEY_PAGE_UP)
    dim += 0.1;
  //  PageDown key - decrease dim
  else if (key == GLUT_KEY_PAGE_DOWN && dim>1)
    dim -= 0.1;
  // Decrease Light Ball Distance
  else if (key == GLUT_KEY_F12 && distance >= 2)
    distance -= .1;
  //  Keep angles to +/-360 degrees
  th %= 360;
  ph %= 360;

  Project(mode?fov:0, asp, dim);
  //  Tell GLUT it is necessary to redisplay the scene
  glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27){
      exit(0);
   }
   //  Reset view angle
   else if (ch == '0' || ch == ')'){
      th    = 0;
      ph    = 30;
      dim   = 7.0;
      fov   = 55;
      mode  = 0;
   }
   // Reset 1st person location/camera position
   else if(ch == 'r' || ch == 'R'){
      eyeX = 0;
      eyeY = 1;
      eyeZ = 10;
      cameraX = 0; 
      cameraZ = 0; 
      theta = 0.0;
   }
   // First person navigation
   else if(ch == 'w' || ch == 'W'){
      eyeX += cameraX * .025;
      eyeZ += cameraZ * .025;
   }
   else if(ch == 's' || ch == 'S'){
      eyeX -= cameraX * .025;
      eyeZ -= cameraZ * .025;
   }
   else if(ch =='a' || ch == 'A'){
      theta -= 2;
   }
   else if(ch == 'd' || ch == 'D'){
      theta += 2;
   }
   else if(ch == 'm' || ch == 'M'){
      mode = (mode + 1)%3;
   }
   // Change FOV (for Perspective/First Person Modes)
   else if (ch == '-' || ch == '_'){
      fov--;
   }
   else if (ch == '+' || ch == '='){
      fov++;
   }
   //  Toggle axes
   else if (ch == '/' || ch == '?'){
      axes = 1-axes;
   }

   /* Lighting Controls */
   // Light switch
   else if (ch == 'l' || ch == 'L'){
      light = 1-light;
   }
   //  Toggle light movement
   else if (ch == ';' || ch == ':')
      move = 1-move;
   //  Move light
   else if (ch == '<' || ch == ',')
      zh += 1;
   else if (ch == '>' || ch == '.')
      zh -= 1;
   //  Light elevation
   else if (ch=='[' || ch == '{')
      ylight -= 0.1;
   else if (ch==']' || ch == '}')
      ylight += 0.1;
   else if (ch =='\\' || ch == '|'){
      distance = 5;    
      ylight = 4.5;
   }
   //  Ambient level
   else if (ch=='x' && ambient>0)
      ambient -= 5;
   else if (ch=='X' && ambient<100)
      ambient += 5;
   //  Diffuse level
   else if (ch=='c' && diffuse>0)
      diffuse -= 5;
   else if (ch=='C' && diffuse<100)
      diffuse += 5;
   //  Specular level
   else if (ch=='v' && specular>0)
      specular -= 5;
   else if (ch=='V' && specular<100)
      specular += 5;
   //  Emission level
   else if (ch=='b' && emission>0)
      emission -= 5;
   else if (ch=='B' && emission<100)
      emission += 5;
   //  Shininess level
   else if (ch=='n' && shininess>-1)
      shininess -= 1;
   else if (ch=='N' && shininess<7)
      shininess += 1;
   else if (ch=='\'' || ch=='"'){
      emission = 0;
      ambient = 30;
      diffuse = 100;
      specular = 0;
      shininess = 0;
   }
   //  Translate shininess power to value (-1 => 0)
   shiny = shininess<0 ? 0 : pow(2.0,shininess);
   // Keep theta between 0-360 to avoid overflow
   theta %= 360;
    
   Project(mode?fov:0,asp,dim);
   //  Animate if requested  
   glutIdleFunc(move?idle:NULL);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

int main(int argc,char* argv[])
{
  //  Initialize GLUT and process user parameters
  glutInit(&argc,argv);
  //  Request double buffered, true color window with Z buffering at 600x600
  glutInitWindowSize(wide,high);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  //  Create the window
  glutCreateWindow("Vladimir Zhdanov- Piano Project");
  //  Tell GLUT to call "idle" when there is nothing else to do
  glutIdleFunc(idle);
  //  Tell GLUT to call "display" when the scene should be drawn
  glutDisplayFunc(display);
  //  Tell GLUT to call "reshape" when the window is resized
  glutReshapeFunc(reshape);
  //  Tell GLUT to call "special" when an arrow key is pressed
  glutSpecialFunc(special);
  //  Tell GLUT to call "key" when a key is pressed
  glutKeyboardFunc(key);

  // Load Textures
  // texture[0] = LoadTexBMP("Grass.bmp");
  // texture[1] = LoadTexBMP("Road.bmp");
  // texture[2] = LoadTexBMP("Sidewalk.bmp");
  // texture[3] = LoadTexBMP("Window.bmp");
  // texture[4] = LoadTexBMP("Wall2.bmp");
  // texture[5] = LoadTexBMP("Roof.bmp");
  // texture[6] = LoadTexBMP("Door.bmp");
  // texture[7] = LoadTexBMP("Brass.bmp");
  // texture[8] = LoadTexBMP("brick.bmp");


  //  Pass control to GLUT so it can interact with the user
  ErrCheck("init");
  glutMainLoop();
  return 0;
}
