#ifndef MATHFD_H
#define MATHFD_H
#include <raylib.h>

typedef struct Vertex4D {
  double x, y, z, w;
} Vertex4D;

void MulMatrixVector4D(double matrix[4][4], Vertex4D *vertex);

Vector3 ProjectTo3D(Vertex4D v);

void GetRotationMatrix(double angle, char plane[2], double matrix[4][4]);

#endif
