#include "math.h"

// inline int min(int a, int b)
// {
//     if (a <= b)
//         return a;
//     return b;
// }

// inline int max(int a, int b)
// {
//     if (a >= b)
//         return a;
//     return b;
// }

MPoint::MPoint(int x, int y)
{
    this->x = x;
    this->y = y;
}

MPoint::MPoint()
{
    this->x = 0;
    this->y = 0;
}