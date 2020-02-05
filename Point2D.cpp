//
// Created by Петр Полежаев ( polezhaev.ds@gmail.com ) on 19.12.2019.
//

#include <cmath>
#include "Point2D.h"

double Point2D::DistanceTo(const Point2D& point) const {
    return std::hypot(x - point.x, y - point.y);
}