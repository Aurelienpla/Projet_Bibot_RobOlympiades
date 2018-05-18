#include "ccorn.h"

CCorn::CCorn(GLfloat posX,GLfloat posZ, GLfloat height, GLfloat diametreBot, GLfloat diametreTop)
{
   m_posX = posX;
   m_posZ = posZ;
   m_height = height;
   m_diametreBot = diametreBot;
   m_diametreTop = diametreTop;
}

void CCorn::draw()
{
   GLUquadric * cornDrawing = gluNewQuadric();
   glPushMatrix();
   glTranslatef(m_posX,0,m_posZ);
   glRotatef(-90,1,0,0);
   glColor3f(0,1,0);
   gluCylinder(cornDrawing,m_diametreBot,m_diametreTop,m_height,10,1);
   glPopMatrix();
}

void CCorn::toString()
{
  std::cout << "Corn: (" << m_posX << "," << m_posZ << ")";
}

GLfloat CCorn::getPosX() const
{
   return m_posX;
}

void CCorn::setPosX(GLfloat value)
{
   m_posX = value;
}

GLfloat CCorn::getPosZ() const
{
   return m_posZ;
}

void CCorn::setPosY(GLfloat value)
{
   m_posZ = value;
}

GLfloat CCorn::getHeight() const
{
   return m_height;
}

void CCorn::setHeight(GLfloat value)
{
   m_height = value;
}

GLfloat CCorn::getDiametreTop() const
{
   return m_diametreTop;
}

void CCorn::setDiametreTop(GLfloat value)
{
   m_diametreTop = value;
}

GLfloat CCorn::getDiametreBot() const
{
   return m_diametreBot;
}

void CCorn::setDiametreBot(GLfloat value)
{
   m_diametreBot = value;
}
