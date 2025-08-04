#ifndef SNAKE_H
#define SNAKE_H

#include <QList>
#include <QPoint>

class Snake
{
public:
    enum class Direction { Left, Right, Up, Down };

    Snake(int width, int height, int dotSize,
          const QList<QPoint>& body = QList<QPoint>(),
          Direction direction = Direction::Right);

    void setDirection(Direction newDirection);
    Direction getDirection() const;
    QList<QPoint> getBody() const;
    QPoint getHead() const;
    int getLength() const;

    void move();
    void grow();
    bool checkWallCollision() const;
    bool checkSelfCollision() const;

private:
    QList<QPoint> body;
    Direction direction;
    int gameWidth;
    int gameHeight;
    int dotSize;
    bool growing;
};

#endif // SNAKE_H
