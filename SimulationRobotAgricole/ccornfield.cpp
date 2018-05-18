#include "ccornfield.h"

CCornField::CCornField(GLfloat posX, GLfloat posZ, int nbCornPerLine, int nbLine, GLfloat sizeGapPlant, GLfloat sizeGapLine)
{
   int idLine, idCornPerLine, i = 0;
   CCorn * pCorn;
   m_posX = posX;
   m_posZ = posZ;
   std::cout << "Création du cornField" << std::endl;
   for (idLine = 0 ; idLine < nbLine; idLine++){
      for (idCornPerLine = 0 ; idCornPerLine < nbCornPerLine ; idCornPerLine++){
         pCorn = new CCorn(posX + (idCornPerLine * sizeGapPlant),posZ + (idLine * sizeGapLine));
         m_vCornField.push_back(pCorn);
      }
   }
}

CCornField::~CCornField()
{
   foreach (CCorn * pCorn, m_vCornField) {
      delete(pCorn);
   }
}

void CCornField::draw()
{
   glPushMatrix();
   foreach (CCorn * pCorn, m_vCornField) {
      glPushMatrix();
      pCorn->draw();
      glPopMatrix();
   }
   glPopMatrix();
}

QVector<CCorn *> CCornField::getVCornField() const
{
   return m_vCornField;
}

GLfloat CCornField::getPosX() const
{
    return m_posX;
}

void CCornField::setPosX(const GLfloat & posX)
{
    m_posX = posX;
}

GLfloat CCornField::getPosZ() const
{
    return m_posZ;
}

void CCornField::setPosZ(const GLfloat & posZ)
{
    m_posZ = posZ;
}
