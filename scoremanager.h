#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <QObject>
#include <QSettings>
#include <QPoint>
class ScoreManager : public QObject
{
    Q_OBJECT
public:
    explicit ScoreManager(QObject *parent = nullptr);

    void saveScore(int score);
    int getHighScore();
    void saveGame(const QList<QPoint>& snakeBody, const QPoint& foodPos, int direction);
    bool loadGame(QList<QPoint>& snakeBody, QPoint& foodPos, int& direction);

private:
    QSettings settings;
};

#endif // SCOREMANAGER_H
