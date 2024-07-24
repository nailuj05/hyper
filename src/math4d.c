#include "math4d.h"
#include <math.h>
#include <raylib.h>

void MulMatrixVector4D(double (*matrix)[4], Vertex4D *vertex) {
  Vertex4D result;
  result.x = matrix[0][0] * vertex->x + matrix[0][1] * vertex->y +
             matrix[0][2] * vertex->z + matrix[0][3] * vertex->w;
  result.y = matrix[1][0] * vertex->x + matrix[1][1] * vertex->y +
             matrix[1][2] * vertex->z + matrix[1][3] * vertex->w;
  result.z = matrix[2][0] * vertex->x + matrix[2][1] * vertex->y +
             matrix[2][2] * vertex->z + matrix[2][3] * vertex->w;
  result.w = matrix[3][0] * vertex->x + matrix[3][1] * vertex->y +
             matrix[3][2] * vertex->z + matrix[3][3] * vertex->w;
  *vertex = result;
}

Vector3 ProjectTo3D(Vertex4D v) {
  double d = 2;
  Vector3 result;
  result.x = v.x / (v.w + d);
  result.y = v.y / (v.w + d);
  result.z = v.z / (v.w + d);
  return result;
}

void GetRotationMatrix(double angle, char plane[2], double matrix[4][4]) {
  double c = cos(angle);
  double s = sin(angle);

  // Initialize as identity matrix
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      matrix[i][j] = (i == j) ? 1 : 0;

  if (plane[0] == 'x' && plane[1] == 'y') {
    matrix[0][0] = c;
    matrix[0][1] = -s;
    matrix[1][0] = s;
    matrix[1][1] = c;
  } else if (plane[0] == 'x' && plane[1] == 'z') {
    matrix[0][0] = c;
    matrix[0][2] = -s;
    matrix[2][0] = s;
    matrix[2][2] = c;
  } else if (plane[0] == 'x' && plane[1] == 'w') {
    matrix[0][0] = c;
    matrix[0][3] = -s;
    matrix[3][0] = s;
    matrix[3][3] = c;
  } else if (plane[0] == 'y' && plane[1] == 'z') {
    matrix[1][1] = c;
    matrix[1][2] = -s;
    matrix[2][1] = s;
    matrix[2][2] = c;
  } else if (plane[0] == 'y' && plane[1] == 'w') {
    matrix[1][1] = c;
    matrix[1][3] = -s;
    matrix[3][1] = s;
    matrix[3][3] = c;
  } else if (plane[0] == 'z' && plane[1] == 'w') {
    matrix[2][2] = c;
    matrix[2][3] = -s;
    matrix[3][2] = s;
    matrix[3][3] = c;
  }
}
