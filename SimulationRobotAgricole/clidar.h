#ifndef CLIDAR_H
#define CLIDAR_H


#include "ccorn.h"
#include "ccornfield.h"
#include "drawing.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <QVector>

using namespace std;

class CLidar
{
public:
   CLidar(GLfloat posX = 0,
          GLfloat posZ = 0,
          GLfloat angleVision = 270,
          GLfloat distMaxVision = 1000);

   void draw();
   void update();
   void addVisibleCorn(CCorn * pCorn);
   CCorn * removeVisibleCorn(CCorn * pCorn);

   GLfloat getAngleVision() const;
   void setAngleVision(const GLfloat & angleVision);
   GLfloat getDistMax() const;
   void setDistMax(const GLfloat & distMax);
   GLfloat getPosX() const;
   void setPosX(const GLfloat & posX);
   GLfloat getPosZ() const;
   void setPosZ(const GLfloat & posZ);

private:
   GLfloat m_angleVision;
   GLfloat m_distMax;
   GLfloat m_posX;
   GLfloat m_posZ;
};

#endif // CLIDAR_H
