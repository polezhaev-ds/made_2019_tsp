//
// Created by Петр Полежаев ( polezhaev.ds@gmail.com ) on 19.12.2019.
//

#ifndef TASK_15_POINT2D_H
#define TASK_15_POINT2D_H


class Point2D {
public:
    explicit Point2D(double x, double y):
            x(x), y(y)
    {
    }

    [[nodiscard]] double GetX() const {
        return x;
    }

    [[nodiscard]] double GetY() const {
        return y;
    }

    [[nodiscard]] double DistanceTo(const Point2D& point) const;

private:
    double x, y;
};


#endif //TASK_15_POINT2D_H
