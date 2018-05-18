#include "crobot.h"

CRobot::CRobot(GLfloat posX, GLfloat posZ, GLfloat direction, GLfloat width, GLfloat height, GLfloat depth)
{
   m_robotState = RobotState::OUTINTERLINE;
   m_posX = posX;
   m_posZ = posZ;
//   m_pos.setX(posX);
//   m_pos.setY(posY);
   m_direction = direction;
   m_width = width;
   m_height = height;
   m_depth = depth;
   m_acceleration = 0.5;
   m_turningSpeed = 0.5;
   m_lidar.setPosX(m_posX+(m_depth+20)/2);
   m_lidar.setPosZ(0);
   m_lidar.setAngleVision(180);
   m_lidar.setDistMax(100);
   updateVecteurDirecteur();
}

CRobot::~CRobot()
{
   foreach (CCorn * pCorn, m_vVisibleCorns) {
      delete(pCorn);
   }
   foreach (CCorn * pCorn, m_vVisibleLeftLine) {
      delete(pCorn);
   }
   foreach (CCorn * pCorn, m_vVisibleRightLine) {
      delete(pCorn);
   }
   foreach (QPointF * pCP, m_vListCheckPoints) {
      delete(pCP);
   }
}

void CRobot::stepForward(){
   m_posX += m_acceleration * cos(m_direction*M_PI/180);
   m_posZ -= m_acceleration * sin(m_direction*M_PI/180);
   updateVecteurDirecteur();
}

void CRobot::stepBackward(){
   m_posX -= m_acceleration * cos(m_direction*M_PI/180);
   m_posZ += m_acceleration * sin(m_direction*M_PI/180);
   updateVecteurDirecteur();
}

void CRobot::stepTurnRight(){
   m_direction -= m_turningSpeed ;
   if(m_direction<0)
      m_direction=359;
   updateVecteurDirecteur();
}

void CRobot::stepTurnLeft(){
   m_direction += m_turningSpeed;
   if( m_direction >=360 )
      m_direction=0;
   updateVecteurDirecteur();
}

void CRobot::turnRight(GLfloat angle)
{
  for(int i = 0 ; i < angle ; i++){
     stepTurnRight();
  }
}

void CRobot::turnLeft(GLfloat angle)
{
  for(int i = 0; i < angle ; i++){
     stepTurnLeft();
  }
}

void CRobot::goForward(GLfloat distance)
{
  for(int i = 0; i < distance ; i++){
     stepForward();
  }
}

void CRobot::goBackward(GLfloat distance)
{
  for(int i = 0; i < distance ; i++){
     stepBackward();
  }
}

bool CRobot::turnToPoint(QPointF * p)
{
   QVector3D vectToCP3D = get3DVectorFromPointsInPlane(m_posX,m_posZ,p->x(), p->y());
   QVector3D crossProduct = QVector3D::crossProduct(m_vecteurDirecteur,vectToCP3D);
   cout << "produit vectoriel y= " << crossProduct.y() << endl;
   if(crossProduct.y() > 500){
      stepTurnLeft();
      return false;
   }else if(crossProduct.y() < -500){
      stepTurnRight();
      return false;
   }else{
      return true;
   }
}

bool CRobot::turnToCorn(CCorn * pCorn)
{
   QVector3D vectToCP3D = get3DVectorFromPointsInPlane(m_posX,m_posZ,pCorn->getPosX(), pCorn->getPosZ());
   QVector3D crossProduct = QVector3D::crossProduct(m_vecteurDirecteur,vectToCP3D);
   cout << "produit vectoriel y= " << crossProduct.y() << endl;
   if(crossProduct.y() > 500){
      stepTurnLeft();
      return false;
   }else if(crossProduct.y() < -500){
      stepTurnRight();
      return false;
   }else{
      return true;
   }
}

bool CRobot::turnColinearTo(QVector3D vect)
{
   QVector3D crossProduct = QVector3D::crossProduct(m_vecteurDirecteur,vect);
   cout << "produit vectoriel y= " << crossProduct.y() << endl;
   if(crossProduct.y() > 500){
      stepTurnLeft();
      return false;
   }else if(crossProduct.y() < -500){
      stepTurnRight();
      return false;
   }else{
      return true;
   }
}

GLfloat CRobot::distanceTo(QPointF * p)
{
   return sqrt(pow(p->x() - m_posX,2) + pow(p->y() - m_posZ,2));
}

GLfloat CRobot::distanceTo(CCorn * pCorn)
{
   return sqrt(pow(pCorn->getPosX() - m_posX,2) + pow(pCorn->getPosZ() - m_posZ,2));
}

void CRobot::autonomousMove()
{
   QPointF * checkPoint;
   CCorn * pCorn;
   QVector3D vectToCP;
   QVector3D vectToCornLeft,vectToCornRight;
   QVector3D vectCornLeftToCornRight;
   float margin;
//      if(m_robotState == RobotState::OUTINTERLINE){
//         if(m_vListCheckPoints.isEmpty() == true){
//            stepForward();
//         }else if(m_vVisibleLeftLine.size() >= 1 && m_vVisibleRightLine.size() >= 1){
//            vectToCornLeft = get3DVectorFromPointsInPlane(m_posX,m_posZ,m_vVisibleLeftLine[0]->getPosX(),m_vVisibleLeftLine[0]->getPosZ());
//            vectCornLeftToCornRight = get3DVectorFromPointsInPlane(m_vVisibleLeftLine[0]->getPosX(),m_vVisibleLeftLine[0]->getPosZ(),
//                  m_vVisibleRightLine[0]->getPosX(), m_vVisibleRightLine[0]->getPosZ());
////            if(turnColinearTo(vectCornLeftToCornRight) == true){
////               stepForward();
////            }
//            QVector3D crossProductVD_VCL = QVector3D::crossProduct(m_vecteurDirecteur,vectToCornLeft);
//            float productNorme = m_vecteurDirecteur.length() * vectToCornLeft.length();
//            margin = productNorme * 2/100;
//            if(crossProductVD_VCL.length() > productNorme + margin){
//               stepTurnLeft();
//            }else if(crossProductVD_VCL.length() < productNorme - margin){
//               stepTurnRight();
//            }else{
//               stepForward();
//            }
//         }
//      }else{
//         stepBackward();
//      }
   if(m_vListCheckPoints.isEmpty() == true){
      stepForward();
   }else if(m_vListCheckPoints.size() >= 1){
      vectToCP = get3DVectorFromPointsInPlane(m_posX,m_posZ,m_vListCheckPoints.back()->x(),m_vListCheckPoints.back()->y());
      QVector3D crossProduct = QVector3D::crossProduct(m_vecteurDirecteur,vectToCP);
      if(crossProduct.y() > 0){
         stepTurnLeft();
      }else if(crossProduct.y() < 0){
         stepTurnRight();
      }
      stepForward();
   }
//   }
}

void CRobot::updateVision()
{
   //retrait des mais qui sorte de la zone
   filterCornOut();

   //ajout des maïs qui entre dans la zone
   filterCornIn();

   std::cout << "Liste des maïs visibles:" << std::endl;
   printToStringListCorn(m_vVisibleCorns);

   //recupération de la première ligne de gauche
   filterNearestLeftLine();
   std::cout << "Liste des maïs visibles à gauche:" << std::endl;
   printToStringListCorn(m_vVisibleLeftLine);

   //recupération de la première ligne de droite
   filterNearestRightLine();
   std::cout << "Liste des maïs visibles à droite:" << std::endl;
   printToStringListCorn(m_vVisibleRightLine);

   //construction des points de passages
   filterCheckPoints();
   cout << "Liste des points de passages" << endl;
   foreach (QPointF * checkPoint, m_vListCheckPoints) {
      cout << "(" << checkPoint->x() << "," << checkPoint->y() << ") | ";
   }
   cout << endl;

   QPointF * checkPoint;
   if(m_vListCheckPoints.size() >= 2){
      checkPoint = m_vListCheckPoints[0];
      QVector3D vectToCP = get3DVectorFromPointsInPlane(m_posX,m_posZ,checkPoint->x(), checkPoint->y());
      float scalarProduct = QVector3D::dotProduct(m_vecteurDirecteur,vectToCP);
      cout << "Produit scalaire: (" << m_vecteurDirecteur.x() << "," << m_vecteurDirecteur.z() << ")."
           << "(" << checkPoint->x() << "," << checkPoint->y() << ")"
           << "= " << scalarProduct << endl;

      if(isPerpendicular(m_vecteurDirecteur,vectToCP) == false){
         cout<<"isPerpendicular"<<endl;
      }else{
         cout<<"is not perpendicular"<<endl;
      }
      QVector3D vectToCP1 = get3DVectorFromPointsInPlane(m_posX,m_posZ,m_vListCheckPoints[0]->x(),m_vListCheckPoints[0]->y());
      QVector3D vectToCP2 = get3DVectorFromPointsInPlane(m_posX,m_posZ,m_vListCheckPoints[1]->x(),m_vListCheckPoints[1]->y());
      QVector3D crossProductCP1_CP2 = QVector3D::crossProduct(vectToCP1,vectToCP2);
      float margin = (vectToCP1.length() * vectToCP2.length()) * 5/100;
      cout << "Comparaison vectToCP1: (" <<  vectToCP1.x() << "," << vectToCP1.z() << ") "
           << "et vectToCP3: (" << vectToCP2.x() << "," << vectToCP2.z() << ": " << endl;
      cout << "produit vectoriel.y= " << crossProductCP1_CP2.y() << endl;
      cout << "marge= " << margin << endl;
      cout << "produit des normes= " << vectToCP1.length()*vectToCP2.length() << endl;

   }
   if(m_vVisibleCorns.isEmpty() == false){
      CCorn * pCorn = m_vVisibleCorns[0];
      QVector3D vectToCorn = get3DVectorFromPointsInPlane(m_posX,m_posZ,pCorn->getPosX(),pCorn->getPosZ());
      float scalarProduct = QVector3D::dotProduct(m_vecteurDirecteur,vectToCorn);
      cout << "Produit scalaire: (" << m_vecteurDirecteur.x() << "," << m_vecteurDirecteur.z() << ")."
           << "(" << pCorn->getPosX() << "," << pCorn->getPosZ() << ")"
           << "= " << scalarProduct << endl;

      if(isPerpendicular(m_vecteurDirecteur,vectToCorn) == false){
         cout<<"isPerpendicular"<<endl;
      }else{
         cout<<"is not perpendicular"<<endl;
      }
   }
}

void CRobot::printToStringListCorn(QVector<CCorn*> vCorns)
{
   CCorn * pCorn;
   for(int i = 0 ; i < vCorns.size() ; i++){
      pCorn = vCorns[i];
      std::cout << "id: " << i << " : ";
      pCorn->toString();
      cout << " | ";
   }
   std::cout << std::endl;
}

bool CRobot::isCornInCircularRange(CCorn * pCorn)
{
   float d2 = (pCorn->getPosX() - m_posX) * (pCorn->getPosX() - m_posX)
              + (pCorn->getPosZ() - m_posZ) * (pCorn->getPosZ() - m_posZ);
   if(d2 > m_lidar.getDistMax() * m_lidar.getDistMax()){
      return false;
   }else{
      return true;
   }
}

bool CRobot::isCornInCircularFrontRange(CCorn * pCorn)
{
   float d2 = (pCorn->getPosX() - m_posX) * (pCorn->getPosX() - m_posX)
              + (pCorn->getPosZ() - m_posZ) * (pCorn->getPosZ() - m_posZ);
   QVector3D vectToCorn = get3DVectorFromPointsInPlane(m_posX,m_posZ,pCorn->getPosX(),pCorn->getPosZ());
   float scalarProduct = QVector3D::dotProduct(m_vecteurDirecteur,vectToCorn);
   if(d2 < m_lidar.getDistMax() * m_lidar.getDistMax()
         && scalarProduct > 0){
      return true;
   }else{
      return false;
   }
}

bool CRobot::isPointInCircularFrontRange(QPointF * p)
{
   float d2 = (p->x() - m_posX) * (p->x() - m_posX)
              + (p->y() - m_posZ) * (p->y() - m_posZ);
   QVector3D vectToPoint = get3DVectorFromPointsInPlane(m_posX,m_posZ,p->x(),p->y());
   float scalarProduct = QVector3D::dotProduct(m_vecteurDirecteur,vectToPoint);
   if(d2 < m_lidar.getDistMax() * m_lidar.getDistMax()
         && scalarProduct > 0){
      return true;
   }else{
      return false;
   }
}

void CRobot::draw()
{
   glPushMatrix();
   //position du robot selon ses coordonnées
   glTranslatef(m_posX,0,m_posZ);
   glRotatef(m_direction,0,1,0);
   drawFrame();

   //dessin du robot
   glPushMatrix();
   glTranslatef(-(m_depth-20)/2,0,-m_width/2);
   drawRectVolume(m_width,m_height,m_depth - 20);
   glTranslatef(m_depth - 20,m_height,0);
   glRotatef(-90,0,0,1);
   drawPyramid(m_width,20,m_height);
   glPopMatrix();

   //dessin du champs de vision du lidar
//   glTranslatef(m_lidar.getPosX(),0,m_lidar.getPosZ());
   m_lidar.draw();

   //dessin du vecteur de direction du robot
   glBegin(GL_LINES);
      glColor3f(0,1,1);
      glVertex3f(0,0,0);
      glVertex3f(m_lidar.getDistMax(),1,0);
   glEnd();
   glPopMatrix();
   cout << "Vecteur Directeur: (" << m_vecteurDirecteur.x() << "," << m_vecteurDirecteur.z() << ")" << endl;

   //dessin des points de passage
   drawCheckPoints();

   posToString();
   std::cout << std::endl;
}

void CRobot::drawTrajectory()
{

}

void CRobot::drawCheckPoints()
{
   glPushMatrix();
   glColor3f(1,0,0);
   glBegin(GL_LINES);
   foreach (QPointF * checkPoint, m_vListCheckPoints) {
      glVertex3f(checkPoint->x(),2,checkPoint->y() - 3);
      glVertex3f(checkPoint->x(),2,checkPoint->y() + 3);
      glVertex3f(checkPoint->x() - 3,2,checkPoint->y());
      glVertex3f(checkPoint->x() + 3,2,checkPoint->y());
   }
   glEnd();
   glPopMatrix();
}

void CRobot::filterCornOut()
{
   CCorn * pCorn;
   int i;
   for(i = 0 ; i < m_vVisibleCorns.size() ; i++){
      pCorn = m_vVisibleCorns[i];
      if(isCornInCircularFrontRange(pCorn) == false){
         std::cout << "Maïs[" << i << "] : ";
         pCorn->toString();
         std::cout <<" sort de la zone" << std::endl;
         m_vVisibleCorns.takeAt(i);                      //retrait de la zone de vision
         if(m_vVisibleLeftLine.contains(pCorn)){         //retrait de la ligne de gauche si présent
            m_vVisibleLeftLine.takeAt(m_vVisibleLeftLine.indexOf(pCorn));
         }
         if(m_vVisibleRightLine.contains(pCorn)){        //retrait de la ligne de droite si présent
            m_vVisibleRightLine.takeAt(m_vVisibleRightLine.indexOf(pCorn));
         }
      }
   }
}

void CRobot::filterCornIn()
{
   CCorn * pCorn;
   int i;
   for (i = 0 ; i < m_cornField.getVCornField().size() ; i++){
      pCorn = m_cornField.getVCornField()[i];
      if(isCornInCircularFrontRange(pCorn)){
         std::cout << "Maïs[" << i << "] : ";
         pCorn->toString();
         std::cout <<" entre dans la zone" << std::endl;
         if((m_vVisibleCorns.contains(pCorn)) == false){
            m_vVisibleCorns.push_back(pCorn);
         }else{
            std::cout << "Déjà dans la zone" << std::endl;
         }
      }
   }
}

void CRobot::filterNearestLeftLine()
{
   int i;
   QVector<CCorn *> leftCorns;
   GLfloat maxLeftZ = -1000000;
   //on retire tous les maïs qui ne sont plus a gauche
   foreach (CCorn * pCorn, m_vVisibleLeftLine) {
      if(pCorn->getPosZ() > m_posZ){
         m_vVisibleLeftLine.takeAt(m_vVisibleLeftLine.indexOf(pCorn));
      }
   }

   //récupération des mais a gauche du robot
   for (i = 0 ; i < m_vVisibleCorns.size() ; i++){
      if(m_vVisibleCorns[i]->getPosZ() <= m_posZ){
         leftCorns.push_back(m_vVisibleCorns[i]);
         if(m_vVisibleCorns[i]->getPosZ() > maxLeftZ){      // on en profite pour récuperer le max des plants de gauche
            maxLeftZ = m_vVisibleCorns[i]->getPosZ();
         }
      }
   }

   //on récuper dans les mais a gauches les mais les plus a droites
   for (i = 0; i < leftCorns.size() ; i++){
      if(m_vVisibleLeftLine.contains(leftCorns[i]) == false
            && leftCorns[i]->getPosZ() == maxLeftZ){
         m_vVisibleLeftLine.push_back(leftCorns[i]);
      }
   }
}

void CRobot::filterNearestRightLine()
{
   int i;
   QVector<CCorn *> rightCorns;
   GLfloat minRightZ = 1000000;
   //on retire tous les maïs qui ne sont plus a droite
   foreach (CCorn * pCorn, m_vVisibleRightLine) {
      if(pCorn->getPosZ() < m_posZ){
         m_vVisibleRightLine.takeAt(m_vVisibleRightLine.indexOf(pCorn));
      }
   }

   //récupération des mais visible a droite du robot
   for (i = 0 ; i < m_vVisibleCorns.size() ; i++){
      if(m_vVisibleCorns[i]->getPosZ() > m_posZ){
         rightCorns.push_back(m_vVisibleCorns[i]);
         if(m_vVisibleCorns[i]->getPosZ() < minRightZ){      // on en profite pour récuperer le max des plants de gauche
            minRightZ = m_vVisibleCorns[i]->getPosZ();
         }
      }
   }

   //on récuper dans les mais a droite les mais les plus a gauche
   for (i = 0; i < rightCorns.size() ; i++){
      if(m_vVisibleRightLine.contains(rightCorns[i]) == false
            && rightCorns[i]->getPosZ() == minRightZ){
         m_vVisibleRightLine.push_back(rightCorns[i]);
      }
   }
}

void CRobot::filterCheckPoints()
{
   for (int i = 0 ; i < m_vListCheckPoints.size() ; i++){
      if(isPointInCircularFrontRange(m_vListCheckPoints[i]) == false){
         m_vListCheckPoints.takeAt(i);
      }
   }
   int iLeft,iRight;
   QPointF * pNewCheckPoint;
   if(m_vVisibleLeftLine.isEmpty() == false
         && m_vVisibleRightLine.isEmpty() == false){
      for(iLeft = 0 ; iLeft < m_vVisibleLeftLine.size() ; iLeft++){
         for(iRight = 0 ; iRight < m_vVisibleRightLine.size() ; iRight++){
            if(m_vVisibleLeftLine[iLeft]->getPosX() == m_vVisibleRightLine[iRight]->getPosX()){
               pNewCheckPoint = new QPointF(m_vVisibleLeftLine[iLeft]->getPosX(),
                                            (m_vVisibleLeftLine[iLeft]->getPosZ() + m_vVisibleRightLine[iRight]->getPosZ())/2);
               if(isCheckPointExist(pNewCheckPoint) == false){
                  m_vListCheckPoints.push_back(pNewCheckPoint);
               }
            }
         }
      }
   }
}

bool CRobot::isCheckPointExist(QPointF * checkPoint)
{
   foreach (QPointF * cp, m_vListCheckPoints) {
      if(cp->x() == checkPoint->x() && cp->y() == checkPoint->y()){
         return true;
      }
   }
   return false;
}

GLfloat CRobot::xCornInRobotFrame(CCorn * pCorn)
{
   return pCorn->getPosX() - m_posX;
}

GLfloat CRobot::zCornInRobotFrame(CCorn * pCorn)
{
   return pCorn->getPosZ() - m_posZ;
}

void CRobot::posToString()
{
   std::cout << "Robot: (" << m_posX << "," << m_posZ << ")";
}

void CRobot::updateVecteurDirecteur()
{
   m_vecteurDirecteur.setX(m_lidar.getDistMax() * cos(m_direction*M_PI/180));
   m_vecteurDirecteur.setZ(m_lidar.getDistMax() * -sin(m_direction*M_PI/180));
}

GLfloat CRobot::getPosX() const
{
   return m_posX;
}

void CRobot::setPosX(const GLfloat & posX)
{
   m_posX = posX;
}

GLfloat CRobot::getPosZ() const
{
   return m_posZ;
}

void CRobot::setPosZ(const GLfloat & posZ)
{
   m_posZ = posZ;
}

GLfloat CRobot::getDirection() const
{
   return m_direction;
}

void CRobot::setDirection(const GLfloat & direction)
{
   m_direction = direction;
}

GLfloat CRobot::getWidth() const
{
   return m_width;
}

void CRobot::setWidth(const GLfloat & width)
{
   m_width = width;
}

GLfloat CRobot::getHeight() const
{
   return m_height;
}

void CRobot::setHeight(const GLfloat & height)
{
   m_height = height;
}

GLfloat CRobot::getDepth() const
{
   return m_depth;
}

void CRobot::setDepth(const GLfloat & depth)
{
   m_depth = depth;
}

CLidar CRobot::getLidar() const
{
   return m_lidar;
}

void CRobot::setLidar(const CLidar & lidar)
{
   m_lidar = lidar;
}

CCornField CRobot::getCornField() const
{
   return m_cornField;
}

void CRobot::setCornField(const CCornField & cornField)
{
   m_cornField = cornField;
}

QVector<CCorn *> CRobot::getVVisibleCorns() const
{
   return m_vVisibleCorns;
}

void CRobot::setVVisibleCorns(const QVector<CCorn *> & vVisibleCorns)
{
   m_vVisibleCorns = vVisibleCorns;
}

QVector3D CRobot::getVecteurDirecteur() const
{
   return m_vecteurDirecteur;
}

void CRobot::setVecteurDirecteur(const QVector3D & vecteurDirecteur)
{
   m_vecteurDirecteur = vecteurDirecteur;
}

GLfloat CRobot::getAcceleration() const
{
   return m_acceleration;
}

void CRobot::setAcceleration(const GLfloat & acceleration)
{
   m_acceleration = acceleration;
}

GLfloat CRobot::getTurningAcceleration() const
{
   return m_turningSpeed;
}

void CRobot::setTurningAcceleration(const GLfloat & turningAcceleration)
{
   m_turningSpeed = turningAcceleration;
}

RobotState CRobot::getRobotState() const
{
   return m_robotState;
}

void CRobot::setRobotState(const RobotState & robotState)
{
   m_robotState = robotState;
}
