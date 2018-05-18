#include "drawing.h"

void drawSquare(GLfloat dimension){
      glBegin(GL_POLYGON);
         glVertex3f(0, 0, 0);
         glVertex3f(dimension, 0, 0);
         glVertex3f(dimension, dimension, 0);
         glVertex3f(0, dimension, 0);
      glEnd();
}

void drawRectVolume(GLfloat width, GLfloat height, GLfloat depth){
   glBegin(GL_QUADS);
      glColor3f(1,0,0);
      glVertex3f(0,0,0);
      glVertex3f(depth,0,0);
      glVertex3f(depth,height,0);
      glVertex3f(0,height,0);

      glColor3f(0,1,0);
      glVertex3f(0,0,0);
      glVertex3f(depth,0,0);
      glVertex3f(depth,0,width);
      glVertex3f(0,0,width);

      glColor3f(0,0,1);
      glVertex3f(0,0,0);
      glVertex3f(0,height,0);
      glVertex3f(0,height,width);
      glVertex3f(0,0,width);

      glColor3f(1,1,1);
      glVertex3f(depth,height,width);
      glVertex3f(0,height,width);
      glVertex3f(0,height,0);
      glVertex3f(depth,height,0);

      glColor3f(1,1,0);
      glVertex3f(depth,height,width);
      glVertex3f(0,height,width);
      glVertex3f(0,0,width);
      glVertex3f(depth,0,width);

      glColor3f(0,1,1);
      glVertex3f(depth,height,width);
      glVertex3f(depth,0,width);
      glVertex3f(depth,0,0);
      glVertex3f(depth,height,0);
   glEnd();
}

void drawPyramid(GLfloat width, GLfloat height, GLfloat depth){
   glBegin(GL_TRIANGLES);
      glColor3f(1,0,0);
      glVertex3f(0,0,0);
      glVertex3f(depth,0,0);
      glVertex3f(depth,height,width/2);

      glColor3f(0,1,0);
      glVertex3f(0,0,0);
      glVertex3f(0,0,width);
      glVertex3f(depth,height,width/2);

      glColor3f(0,0,1);
      glVertex3f(depth,0,width);
      glVertex3f(0,0,width);
      glVertex3f(depth,height,width/2);

      glColor3f(1,0,1);
      glVertex3f(depth,0,width);
      glVertex3f(depth,0,0);
      glVertex3f(depth,height,width/2);
   glEnd();
}

void drawFrame(){
   glColor3f(1.0, 1.0, 1.0); // couleur du dessin
   glBegin(GL_LINES);
   glVertex3f(-500,0,0);
   glColor3f(1.0, 0.0, 0.0); // couleur du dessin
   glVertex3f(500,0,0);
   glColor3f(1.0, 1.0, 1.0); // couleur du dessin
   glVertex3f(0,-500,0);
   glColor3f(0.0, 1.0, 0.0); // couleur du dessin
   glVertex3f(0,500,0);
   glColor3f(1.0, 1.0, 1.0); // couleur du dessin
   glVertex3f(0,0,-500);
   glColor3f(0.0, 0.0, 1.0); // couleur du dessin
   glVertex3f(0,0,500);
   glEnd();
}
void drawFloor(GLfloat dimension){
   glPushMatrix();
   glBegin(GL_QUADS);
      glColor3f(0.30,0.2,0);
      glVertex3f(-dimension,0,-dimension);
      glVertex3f(-dimension,0,dimension);
      glVertex3f(dimension,0,dimension);
      glVertex3f(dimension,0,-dimension);
   glEnd();
   glPopMatrix();
}

void drawCircle(GLfloat centerX, GLfloat centerZ, GLfloat radius, GLfloat nbSegments)
{
   float theta, x, y;
   glBegin(GL_LINE_LOOP);
   for(int ii = 0; ii < nbSegments; ii++)
   {
      theta = 2.0f * M_PI * float(ii) / float(nbSegments);//get the current angle

      x = radius * cosf(theta);//calculate the x component
      y = radius * sinf(theta);//calculate the y component

      glVertex3f(x + centerX,0, y + centerZ);//output vertex
   }
   glEnd();
}
