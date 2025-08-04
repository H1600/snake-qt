#include "skinmanager.h"

SkinManager::SkinManager(QObject *parent) : QObject(parent), currentSkin(Classic)
{
    setSkin(Classic);
}

void SkinManager::setSkin(SkinType type)
{
    currentSkin = type;

    switch (type) {
    case Classic:
        snakeColor = Qt::green;
        snakeHeadColor = Qt::darkGreen;
        foodColor = Qt::red;
        backgroundColor = Qt::white;
        gridColor = Qt::lightGray;
        break;
    case Dark:
        snakeColor = QColor(70, 130, 180);  // 钢蓝色
        snakeHeadColor = QColor(65, 105, 225); // 皇家蓝
        foodColor = QColor(220, 20, 60);    // 猩红色
        backgroundColor = QColor(30, 30, 30);
        gridColor = QColor(60, 60, 60);
        break;
    case Neon:
        snakeColor = QColor(0, 255, 0);     // 霓虹绿
        snakeHeadColor = QColor(0, 200, 0);
        foodColor = QColor(255, 0, 255);   // 霓虹粉
        backgroundColor = QColor(0, 0, 0);
        gridColor = QColor(50, 50, 50);
        break;
    case Nature:
        snakeColor = QColor(34, 139, 34);   // 森林绿
        snakeHeadColor = QColor(0, 100, 0);
        foodColor = QColor(255, 69, 0);     // 橙红色
        backgroundColor = QColor(245, 245, 220); // 米色
        gridColor = QColor(210, 180, 140);  // 棕褐色
        break;
    }
}

QColor SkinManager::getSnakeColor() const { return snakeColor; }
QColor SkinManager::getSnakeHeadColor() const { return snakeHeadColor; }
QColor SkinManager::getFoodColor() const { return foodColor; }
QColor SkinManager::getBackgroundColor() const { return backgroundColor; }
QColor SkinManager::getGridColor() const { return gridColor; }
