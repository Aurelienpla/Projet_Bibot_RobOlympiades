#ifndef CCORN_H
#define CCORN_H

/**
 * @brief The CCorn class gérant un plant de maïs
 */


#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

class CCorn
{
public:
   CCorn(GLfloat posX = 0,
         GLfloat posZ = 0,
         GLfloat height = 20,
         GLfloat diametreBot = 3,
         GLfloat diametreTop = 3);
   void draw();
   void toString();

   //Accesseurs
   GLfloat getPosX() const;
   void setPosX(GLfloat value);
   GLfloat getPosZ() const;
   void setPosY(GLfloat value);
   GLfloat getHeight() const;
   void setHeight(GLfloat value);
   GLfloat getDiametreTop() const;
   void setDiametreTop(GLfloat value);
   GLfloat getDiametreBot() const;
   void setDiametreBot(GLfloat value);

private:
   GLfloat m_posX;
   GLfloat m_posZ;
   GLfloat m_height;
   GLfloat m_diametreTop;
   GLfloat m_diametreBot;
};

#endif // CCORN_H
