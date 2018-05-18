#ifndef CDRAWING_H
#define CDRAWING_H

/**
*  Contient toutes les méthodes d'affichages d'objets
**/
#include "ccorn.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <QVector>

#define RATIO_PIXEL_CM 10

void drawSquare(GLfloat dimension);
void drawRectVolume(GLfloat width, GLfloat height, GLfloat depth);
void drawPyramid(GLfloat width, GLfloat height, GLfloat depth);
void drawFrame();
void drawFloor(GLfloat dimension);
void drawCircle(GLfloat centerX, GLfloat centerZ, GLfloat radius, GLfloat nbSegments);

#endif // CDRAWING_H
