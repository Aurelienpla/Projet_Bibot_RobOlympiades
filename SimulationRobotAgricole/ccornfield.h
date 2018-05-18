#ifndef CCORNFIELD_H
#define CCORNFIELD_H

/**
 * @brief The CCornField class gérant un champs de plusieurs rangées de plants de maïs
 */

#include "ccorn.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <QVector>
#include <iostream>

using namespace std;

class CCornField
{
public:
   CCornField(GLfloat posX = 0,
              GLfloat posZ = 0,
              int nbCornPerLine = 10,
              int nbLine = 5,
              GLfloat sizeGapPlant = 16,
              GLfloat sizeGapLine = 80);
   ~CCornField();

   void addCornToLine(CCorn * pCorn, int idLine);
   void draw();

   QVector<CCorn *> getVCornField() const;
   GLfloat getPosX() const;
   void setPosX(const GLfloat & posX);
   GLfloat getPosZ() const;
   void setPosZ(const GLfloat & posZ);

private:
   QVector<CCorn*> m_vCornField;
   GLfloat m_posX;
   GLfloat m_posZ;
};

#endif // CCORNFIELD_H
