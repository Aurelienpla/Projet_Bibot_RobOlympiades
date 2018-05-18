#include "utils.h"

float scalarProduct2D(QVector2D v1, QVector2D v2)
{
   return v1.x() * v2.x() + v1.y() * v2.y();
}

QVector2D get2DVectorFromPoints(float xP1, float zP1, float xP2, float zP2)
{
  return QVector2D(xP2 - xP1,zP2 - zP1);
}

QVector2D get2DVectorFromPoints(QPointF * p1, QPointF * p2)
{
  return QVector2D(p2->x() - p1->x(), p2->y() - p1->y());
}

QVector3D get3DVectorFromPointsInPlane(float xP1, float zP1, float xP2, float zP2)
{
  return QVector3D(xP2 - xP1,0,zP2 - zP1);
}

QVector3D get3DVectorFromPointsInPlane(QPointF * p1, QPointF * p2)
{
  return QVector3D(p2->x() - p1->x(), 0 ,p2->y() - p1->y());
}

bool isPerpendicular(QVector3D & v1, QVector3D & v2)
{
   float lengthCrossProduct = QVector3D::crossProduct(v1,v2).length();
   float lengthProduct = v1.length() * v2.length();
   float margin = lengthProduct * 0.1 / 100;
   cout << "v1:(" << v1.x() << "," << v1.z() << "), v2:(" << v2.x() << "," << v2.z() << ")" << endl;
   cout << "lengthCrossProduct= " << lengthCrossProduct << ", lengthProduct= " << lengthProduct <<endl;
   if( lengthCrossProduct >= lengthProduct - margin ){
      return true;
   }else{
      return false;
   }
}
