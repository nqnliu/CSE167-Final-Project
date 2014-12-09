#include "Viewport.h"

Viewport::Viewport(int x, int y, int width, int height)
{
   matrix = Matrix4();
   set(x, y, width, height);
}

void Viewport::set(int x, int y, int width, int height)
{
   matrix.set(0, 0, (width) / 2.0);
   matrix.set(0, 3, (x + width) / 2.0);
   matrix.set(1, 1, (height) / 2.0);
   matrix.set(1, 3, (y + height) / 2.0);
   matrix.set(2, 2, 1 / 2.0);
   matrix.set(2, 3, 1 / 2.0);
   matrix.set(3, 3, 1.0);
   matrix.print("Viewport:\n");
}

Matrix4* Viewport::getMatrix()
{
   return &matrix;
}