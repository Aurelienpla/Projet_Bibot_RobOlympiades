#ifndef CROBOT_H
#define CROBOT_H
/**
 * @brief The CRobot class de gestion d'un robot
 */

#include "drawing.h"
#include "clidar.h"
#include "utils.h"
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <QVector2D>
#include <QVector3D>
#include <QPointF>

enum class RobotState { ININTERLINE, OUTINTERLINE };

using namespace std;

class CRobot
{
public:
   CRobot(GLfloat posX = 0,
          GLfloat posZ = 0,
          GLfloat direction = -45,
          GLfloat width = 60,
          GLfloat height = 48,
          GLfloat depth = 100);
   ~CRobot();

   void stepForward();
   void stepBackward();
   void stepTurnRight();
   void stepTurnLeft();

   void turnRight(GLfloat angle);
   void turnLeft(GLfloat angle);
   void goForward(GLfloat distance);
   void goBackward(GLfloat distance);
   //Oriente la robot vers le point p et renvoie true si bien oriente false sinon
   bool turnToPoint(QPointF * p);
   bool turnToCorn(CCorn * pCorn);
   bool turnColinearTo(QVector3D vect);
   GLfloat distanceTo(QPointF * p);
   GLfloat distanceTo(CCorn * pCorn);
   void autonomousMove();
   void updateVision();
   void printToStringListCorn(QVector<CCorn*> vCorns);
   bool isCornInCircularRange(CCorn * pCorn);
   bool isCornInCircularFrontRange(CCorn * pCorn);
   bool isPointInCircularRange(QPointF * p);
   bool isPointInCircularFrontRange(QPointF * p);
   GLfloat xCornInRobotFrame(CCorn * pCorn);
   GLfloat zCornInRobotFrame(CCorn * pCorn);
   void draw();
   void drawTrajectory();
   void drawCheckPoints();

   //filterCornOut retire les maïs de m_vVisibleCorn qui sorte de la zone
   void filterCornOut();
   //filterCornIn ajoute les mais qui entre dans la zone du radar dans m_vVisibleCorn
   void filterCornIn();
   //ajoute tout les maïs les plus proche a gauche a m_vVisibleLeftLine
   void filterNearestLeftLine();
   //ajoute tout les maïs les plus proche a droite a m_vVisibleDroiteLine
   void filterNearestRightLine();
   //construit la liste des points de passage et retire les points de passage sortant de la zone
   void filterCheckPoints();

   void addCheckPoint(QPointF * checkPoint);
   void removeCheckPoint(QPointF * checkPoint);
   bool isCheckPointExist(QPointF * checkPoint);
   void posToString();
   void updateVecteurDirecteur();

   GLfloat getPosX() const;
   void setPosX(const GLfloat & posX);
   GLfloat getPosZ() const;
   void setPosZ(const GLfloat & posZ);
   GLfloat getDirection() const;
   void setDirection(const GLfloat & direction);
   GLfloat getWidth() const;
   void setWidth(const GLfloat & width);
   GLfloat getHeight() const;
   void setHeight(const GLfloat & height);
   GLfloat getDepth() const;
   void setDepth(const GLfloat & depth);
   CLidar getLidar() const;
   void setLidar(const CLidar & lidar);
   CCornField getCornField() const;
   void setCornField(const CCornField & cornField);
   QVector<CCorn *> getVVisibleCorns() const;
   void setVVisibleCorns(const QVector<CCorn *> & vVisibleCorns);
   QVector<CCorn *> getVVisibleLeftLine() const;
   void setVVisibleLeftLine(const QVector<CCorn *> & vVisibleLeftLine);
   QVector<CCorn *> getVVisibleRightLine() const;
   void setVVisibleRightLine(const QVector<CCorn *> & vVisibleRightLine);
   QVector3D getVecteurDirecteur() const;
   void setVecteurDirecteur(const QVector3D & vecteurDirecteur);
   GLfloat getAcceleration() const;
   void setAcceleration(const GLfloat & acceleration);
   GLfloat getTurningAcceleration() const;
   void setTurningAcceleration(const GLfloat & turningAcceleration);
   RobotState getRobotState() const;
   void setRobotState(const RobotState & robotState);

private:
   RobotState m_robotState;
   GLfloat m_width;
   GLfloat m_height;
   GLfloat m_depth;
   GLfloat m_posX;
   GLfloat m_posZ;
//   QPointF m_pos;
   QVector3D m_vecteurDirecteur;
   GLfloat m_direction;
   GLfloat m_acceleration;
   GLfloat m_turningSpeed;
   CLidar m_lidar;
   CCornField m_cornField;
   QVector<CCorn *> m_vVisibleCorns;
   QVector<CCorn *> m_vVisibleLeftLine;
   QVector<CCorn *> m_vVisibleRightLine;
   QVector<QPointF *> m_vListCheckPoints;
};

#endif // CROBOT_H
