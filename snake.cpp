#include "snake.h"

Snake::Snake(int width, int height, int dotSize, const QList<QPoint> &body, Direction direction)
    : gameWidth(width), gameHeight(height), dotSize(dotSize), direction(direction)
{
    if (body.isEmpty()) {
        // 初始化默认蛇身
        for (int i = 0; i < 3; ++i) {
            this->body.append(QPoint((3 - i) * dotSize, 0));
        }
    } else {
        this->body = body;
    }
    growing = false;
}

void Snake::setDirection(Direction newDirection)
{
    direction = newDirection;
}

Snake::Direction Snake::getDirection() const
{
    return direction;
}

QList<QPoint> Snake::getBody() const
{
    return body;
}

QPoint Snake::getHead() const
{
    return body.first();
}

int Snake::getLength() const
{
    return body.size();
}

void Snake::move()
{
    QPoint newHead = body.first();

    switch (direction) {
    case Direction::Left:
        newHead.rx() -= dotSize;
        break;
    case Direction::Right:
        newHead.rx() += dotSize;
        break;
    case Direction::Up:
        newHead.ry() -= dotSize;
        break;
    case Direction::Down:
        newHead.ry() += dotSize;
        break;
    }

    body.prepend(newHead);

    if (!growing) {
        body.removeLast();
    } else {
        growing = false;
    }
}

void Snake::grow()
{
    growing = true;
}

bool Snake::checkWallCollision() const
{
    QPoint head = body.first();
    return head.x() < 0 || head.y() < 0 ||
           head.x() >= gameWidth || head.y() >= gameHeight;
}

bool Snake::checkSelfCollision() const
{
    QPoint head = body.first();
    for (int i = 1; i < body.size(); ++i) {
        if (head == body.at(i)) {
            return true;
        }
    }
    return false;
}
