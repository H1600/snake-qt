#include "scoremanager.h"
#include <QDebug>

ScoreManager::ScoreManager(QObject *parent) : QObject(parent), settings("MyCompany", "SnakeGame")
{
}

void ScoreManager::saveScore(int score)
{
    int highScore = getHighScore();
    if (score > highScore) {
        settings.setValue("highScore", score);
    }
}

int ScoreManager::getHighScore()
{
    return settings.value("highScore", 0).toInt();
}

void ScoreManager::saveGame(const QList<QPoint> &snakeBody, const QPoint &foodPos, int direction)
{
    settings.beginWriteArray("snakeBody");
    for (int i = 0; i < snakeBody.size(); ++i) {
        settings.setArrayIndex(i);
        settings.setValue("position", snakeBody.at(i));
    }
    settings.endArray();

    settings.setValue("foodPos", foodPos);
    settings.setValue("direction", direction);
}

bool ScoreManager::loadGame(QList<QPoint> &snakeBody, QPoint &foodPos, int &direction)
{
    if (!settings.contains("snakeBody/size")) {
        return false;
    }

    snakeBody.clear();
    int size = settings.beginReadArray("snakeBody");
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        snakeBody.append(settings.value("position").toPoint());
    }
    settings.endArray();

    foodPos = settings.value("foodPos").toPoint();
    direction = settings.value("direction").toInt();

    return true;
}
