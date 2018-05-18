#include "clidar.h"

CLidar::CLidar(GLfloat posX, GLfloat posZ, GLfloat angleVision, GLfloat distMaxVision)
{
   m_posX = posX;
   m_posZ = posZ;
   m_angleVision = angleVision;
   m_distMax = distMaxVision;
}

void CLidar::draw()
{
   glPushMatrix();
   GLUquadric * lidarDrawingQuadricParam = gluNewQuadric();
   glTranslatef(0,1,0);
   drawCircle(0,0,m_distMax,20);
   glRotatef(-90,1,0,0);
   gluPartialDisk(lidarDrawingQuadricParam,0,m_distMax,20,1,0,m_angleVision);
   glPopMatrix();
}

void CLidar::update()
{

}

GLfloat CLidar::getAngleVision() const
{
   return m_angleVision;
}

void CLidar::setAngleVision(const GLfloat & angleVision)
{
   m_angleVision = angleVision;
}

GLfloat CLidar::getDistMax() const
{
   return m_distMax;
}

void CLidar::setDistMax(const GLfloat & distMax)
{
   m_distMax = distMax;
}

GLfloat CLidar::getPosX() const
{
   return m_posX;
}

void CLidar::setPosX(const GLfloat & posX)
{
   m_posX = posX;
}

GLfloat CLidar::getPosZ() const
{
   return m_posZ;
}

void CLidar::setPosZ(const GLfloat & posZ)
{
   m_posZ = posZ;
}
