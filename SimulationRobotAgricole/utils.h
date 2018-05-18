#ifndef UTILS_H
#define UTILS_H
#include <QVector2D>
#include <QVector3D>
#include <iostream>

using namespace std;

/**
 * @brief Compute the scalar product of two one dimensional vectors
 * @param v1
 * @param v2
 * @return
 */
float scalarProduct2D(QVector2D v1, QVector2D v2);
/**
 * @brief get the vecteur corresponding to the given points
 * @param p1
 * @param p2
 * @param p3
 * @param p4
 * @return a QVectord2D
 */
QVector2D get2DVectorFromPoints(float xP1, float zP1, float xP2, float zP2);
QVector2D get2DVectorFromPoints(QPointF * p1, QPointF * p2);
QVector3D get3DVectorFromPointsInPlane(float xP1, float zP1, float xP2, float zP2);
QVector3D get3DVectorFromPointsInPlane(QPointF * p1, QPointF * p2);
bool isPerpendicular(QVector3D & v1, QVector3D & v2);


#endif // UTILS_H
