#ifndef FOOD_H
#define FOOD_H

#include <QPoint>
#include <QList>

class Food
{
public:
    Food(int width, int height, int dotSize);

    QPoint getPosition() const;
    void setPosition(const QPoint &position);
    void generate(const QList<QPoint> &snakeBody, const QList<QPoint> &obstacles = QList<QPoint>());

private:
    QPoint position;
    int gameWidth;
    int gameHeight;
    int dotSize;
};

#endif // FOOD_H
