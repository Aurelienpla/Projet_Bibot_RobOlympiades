#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <QVector>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "drawing.h"
#include "ccorn.h"
#include "ccornfield.h"
#include "crobot.h"

#define WIDTH  640
#define HEIGHT 700

#define RED   0
#define GREEN 0
#define BLUE  0
#define ALPHA 1
#define My_Square 1
#define My_Cube 2

#define TRUE 1
#define FALSE 0

#define KEY_ESC 27

using namespace std;

GLfloat eyex,eyey,eyez,cx,cy,cz,upx,upy,upz;
GLfloat world_rotate_angle_x;
GLfloat world_rotate_angle_y;
GLfloat world_rotate_angle_z;
GLfloat world_translate_x, world_translate_y, world_translate_z;
GLfloat bot_pos_x, bot_pos_y, bot_pos_z;
GLfloat bot_acceleration, bot_rotation;
GLfloat robot_matrix[16],matrix_tmp[16];
int avancer,reculer, tournerGauche, tournerDroite;
CRobot bot;
QVector<CCorn*> vCorn;
CCornField cornField(0,-160);
bool simulationRun;

int compteur_image = 0;

void init_scene();

GLvoid initGL();
GLvoid init_light();
GLvoid mon_window_display();
GLvoid mon_window_reshape(GLsizei width, GLsizei height);
GLvoid key_push_event(unsigned char key, int x, int y);
GLvoid key_release_event(unsigned char key, int x, int y);
void showMatrix(GLfloat * matrix);
void moveRobotManual();

int main(int argc, char **argv)
{
   // initialisation  des paramètres de glut en fonction
   // des arguments sur la ligne de commande
   glutInit(&argc, argv);
   // initialisation du contexte grapique
   glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);

   // définition et création de la fenêtre graphique
   glutInitWindowSize(WIDTH, HEIGHT);
   glutInitWindowPosition(0, 0);
   glutCreateWindow("Simulation Robot Agricole");

   // initialisation de opengl et de la scène
   initGL();
   init_light();
   init_scene();

   // choix des procédures de callback pour
   // le tracé graphique
   glutDisplayFunc(&mon_window_display);
   glutIdleFunc(&mon_window_display);
   // le redimensionnement de la fenêtre
   glutReshapeFunc(&mon_window_reshape);
   // la gestion des événements clavier
   glutKeyboardFunc(&key_push_event);
   glutKeyboardUpFunc(&key_release_event);

   // la boucle prinicipale de gestion des événements utilisateur
   glutMainLoop();

   return 1;
}

// initialisation du fond de la fenêtre graphique : noir opaque

GLvoid initGL()
{
   glClearColor(RED, GREEN, BLUE, ALPHA);  //alpha
   glEnable(GL_DEPTH_TEST);
   glShadeModel(GL_SMOOTH);
   glLoadIdentity();
//   glEnable(GL_LIGHTING) ;
//   glEnable(GL_LIGHT0);
}

// fonction de call-back pour lžaffichage dans la fenêtre
GLvoid mon_window_display()
{
   printf("image number : %d\n",compteur_image++);

   bot.updateVision();
   if(simulationRun){
      bot.autonomousMove();
   }
   moveRobotManual();

   glClear(GL_COLOR_BUFFER_BIT); // initialise le buffer à la couleur du fond.
   glClear(GL_DEPTH_BUFFER_BIT);

   glLoadIdentity();		//initialisation de la matrice courant gl_modelview

   //définition de l'orientation de la camera
   gluLookAt(eyex,eyey,eyez,cx,cy,cz,upx,upy,upz);

   //Mise a jour des action de déplacement de la caméra
   glRotatef(world_rotate_angle_x, 1, 0, 0);
   glRotatef(world_rotate_angle_y, 0, 1, 0);
   glRotatef(world_rotate_angle_z, 0, 0, 1);
   glTranslatef(world_translate_x, world_translate_y, world_translate_z);

   drawFrame();
   drawFloor(1000);

   //Dessin du robot
   glPushMatrix();
   bot.draw();
   glPopMatrix();

   //dessin du champs de mais
   cornField.draw();

   cout <<"-----------------------------------------------------------" << endl;

   glutSwapBuffers();
}

// fonction de call-back pour le redimensionnement de la fenêtre si on modifie sa taile.
GLvoid mon_window_reshape(GLsizei width, GLsizei height)
{
   glViewport(0, 0, WIDTH, HEIGHT);

   glMatrixMode(GL_PROJECTION); //indique le type  de transformation et charge la matrice correspondante
   glLoadIdentity();		//initialise la matrice courante à la matrice identité.
   //  gluortho2d(-2.0, 2.0, -2.0, 2.0);//définit le type de projection : orthogonal 2d,
   //et ses paramètres à partir desquels opengl construit la matrice de projection correspondante.
//         glOrtho( -500, 500, -500, 500, 100, 1000);
   gluPerspective(100,(GLfloat)width / (GLfloat)height,2,10000);
   // toutes les transformations suivantes sžappliquent au modèle de vue
   glMatrixMode(GL_MODELVIEW);
}

// fonction de call-back pour la gestion des événements clavier
GLvoid key_release_event(unsigned char key, int x, int y){
   switch (key) {
   case 'i':
      avancer = FALSE;
      break;
   case 'k':
      reculer = FALSE;
      break;
   case 'j':
      tournerGauche = FALSE;
      break;
   case 'l':
      tournerDroite = FALSE;
      break;
   }
}

GLvoid key_push_event(unsigned char key, int x, int y)
{
   switch (key) {
   case KEY_ESC:
      exit(1);
      break;
   case '+':
      if(eyex>100)
         eyex-=5;
      if(eyey>100)
         eyey-=5;
      if(eyez>100)
         eyez-=5;
      break;
   case '-':
      if(eyex<500)
         eyex+=5;
      if(eyey<500)
         eyey+=5;
      if(eyez<500)
         eyez+=5;
      break;

   case 'd':
      world_translate_x += 5.0;
      break;
   case 'q':
      world_translate_x -= 5.0;
      break;
   case 'z':
      world_translate_y += 5.0;
      break;
   case 's':
      world_translate_y -= 5.0;
      break;
   case 'a':
      world_translate_z -= 5.0;
      break;
   case 'e':
      world_translate_z += 5.0;
      break;
   case '8':
      world_rotate_angle_x += 4.0;
      if(world_rotate_angle_x>=360)
         world_rotate_angle_x=0;
      break;
   case '4':
      world_rotate_angle_y += 4.0;
      if(world_rotate_angle_y>=360)
         world_rotate_angle_y=0;
      break;
   case '7':
      world_rotate_angle_z += 4.0;
      if(world_rotate_angle_z>=360)
         world_rotate_angle_z=0;
      break;
   case '2':
      world_rotate_angle_x -= 4.0;
      if(world_rotate_angle_x<=0)
         world_rotate_angle_x=360;
      break;
   case '6':
      world_rotate_angle_y -= 4.0;
      if(world_rotate_angle_y<=0)
         world_rotate_angle_y=360;
      break;
   case '9':
      world_rotate_angle_z -= 4.0;
      if(world_rotate_angle_z<=0)
         world_rotate_angle_z=360;
      break;
   case 'j':
      tournerGauche = TRUE;
      break;
   case 'k':
      reculer = TRUE;
      break;
   case 'l':
      tournerDroite = TRUE;
      break;
   case 'i':
      avancer = TRUE;
      break;
   case 'g':
      simulationRun = !simulationRun;
      break;

   default:
      printf ("la touche %d nžest pas active.\n", key);
      break;
   }
}

void init_light()
{
   //différents paramètres
   GLfloat ambient[] = {1.5f,1.5f,1.5f,1.0f};
   GLfloat diffuse[] = {0.5f,0.5f,0.5f,1.0f};
   GLfloat light0_position [] = {0.0f, 0.0f, 0.0f, 0.0f};
   GLfloat specular_reflexion[] = {0.8f,0.8f,0.8f,1.0f};
   GLubyte shiny_obj = 25;
   //positionnement de la lumière avec les différents paramètres
   glEnable(GL_LIGHTING);
   glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
   glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
   glLightfv(GL_LIGHT0,GL_POSITION,light0_position);
   glEnable(GL_LIGHT0);
   //spécification de la réflexion sur les matériaux
   glEnable(GL_COLOR_MATERIAL);
   glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
   glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ambient);
   glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diffuse);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular_reflexion);
   glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,shiny_obj);
}

void init_scene(){
   eyex = -1;
   eyey = 300;
   eyez = 0;
   cx = 0;
   cy = 0;
   cz = 0;
   upx = 0;
   upy = 1;
   upz = 0;

   world_rotate_angle_x = world_rotate_angle_y = world_rotate_angle_z = 0;
   world_translate_x = 0;
   world_translate_y = world_translate_z = 0;
   avancer = reculer = tournerDroite = tournerGauche = FALSE;
   bot.setPosX(-100);
//   bot.setPosX(200);
//   bot.setPosX(200);
   bot.setCornField(cornField);
   simulationRun = false;
}

void showMatrix(GLfloat * matrix){
   for (int index = 0; index < 16; index++) {
      printf("%f ",matrix[index]);
      if(((index+1) % 4 )== 0)
         printf("\n");
   }
   printf("\n");
}

void moveRobotManual(){
    if( avancer == TRUE ){
      bot.stepForward();
    }
    if( tournerGauche ==TRUE ){
      bot.stepTurnLeft();
    }
    if( tournerDroite == TRUE ){
       bot.stepTurnRight();
    }
    if( reculer == TRUE){
       bot.stepBackward();
    }
}

