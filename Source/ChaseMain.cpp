/*
 *   Basic NPC AI project main entry point.
 *   Created by Jeff Colgan, January 7, 2022,
 *   Personal portfolio project.  
 */
#include "NPCAI.h"
#include "Ground.h"
#include "Player.h"


Camera* cam;
Ground* map;
Player* player;

// Initialize game objects and load textures from files.
void initialize()
{
   int mapInit;

   map = new Ground(0.0, 0.0, 0.0, 5.0, 0.0, 10.0, 0.0, 0.0, 0.0);
   mapInit = map->Initialize("../Assets/Concrete.bmp");

   if (mapInit != 0)
   {
      printf("Failed to load ground texture!\n");
      exit(0);
   }

   cam = new Camera();
   
   player = new Player(-4.5, 0.1, -9.5, 0.5, 1.0, 0.5, 0.0, 0.0, 0.0);
   player->Initialize("../Assets/Metal.bmp");
}

// Display function, called by GLUT to redraw the window.
void display()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);

   glShadeModel(GL_SMOOTH);
   glEnable(GL_NORMALIZE);
   glEnable(GL_LIGHTING);
   glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
   glEnable(GL_COLOR_MATERIAL);

   glLoadIdentity();

   gluLookAt(0.0, 5.0, 0.0, 0.0, 0.0, 0.0, -1, 0, 0);
   map->Render();
   player->Render();

   glFlush();
   glutSwapBuffers();
}

// Special function, called by GLUT when the user presses a special key.
void special(int key, int x, int y)
{
   if (key == GLUT_KEY_RIGHT)
   {
      int theta = cam->getTheta() + 5;
      theta %= 360;
      cam->setTheta(theta);
   }
   else if (key == GLUT_KEY_LEFT)
   {
      int theta = cam->getTheta() - 5;
      theta %= 360;
      cam->setTheta(theta);
   }
   cam->Project(0.0);
   glutPostRedisplay();
}

// Key function, called by GLUT when the player presses a key.
void key(unsigned char key, int x, int y)
{
   if (key == 27)
      exit(0);
}

// Reshape function, called by GLUT when the application window is resized.
void reshape(int width, int height)
{
   double asp;

   glViewport(0, 0, RES*width, RES*height);
   asp = (height > 0) ? (double)width / height : 1;
   cam->setAsp(asp);
   cam->Project(0.0);
}

// Main entry point.
int main(int argc, char* argv[])
{
   glutInit(&argc, argv);

   //glutInitWindowSize(500, 500);
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutCreateWindow("Basic NPC AI");
   glutFullScreen();

#ifdef USEGLEW
   if (glewInit() != GLEW_OK) return 0;
#endif

   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);

   initialize();

   //ErrCheck("init");
   glutMainLoop();

   return 0;
}