#include "food.h"
#include <QRandomGenerator>

Food::Food(int width, int height, int dotSize)
    : gameWidth(width), gameHeight(height), dotSize(dotSize)
{
}

QPoint Food::getPosition() const
{
    return position;
}

void Food::setPosition(const QPoint &position)
{
    this->position = position;
}

void Food::generate(const QList<QPoint> &snakeBody, const QList<QPoint> &obstacles)
{
    int maxX = (gameWidth / dotSize) - 1;
    int maxY = (gameHeight / dotSize) - 1;

    while (true) {
        int x = QRandomGenerator::global()->bounded(0, maxX) * dotSize;
        int y = QRandomGenerator::global()->bounded(0, maxY) * dotSize;
        position = QPoint(x, y);

        if (!snakeBody.contains(position) && !obstacles.contains(position)) {
            break;
        }
    }
}
