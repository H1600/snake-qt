#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QKeyEvent>
#include <QTimer>
#include <QMenuBar>
#include <QMessageBox>
#include "snake.h"
#include "food.h"
#include "scoremanager.h"
#include "soundmanager.h"
#include "skinmanager.h"

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    Snake *snake;
    Food *food;
    ScoreManager *scoreManager;
    SoundManager *soundManager;
    SkinManager *skinManager;
    // 添加游戏区域和分数区域
    QRect gameAreaRect;
    QRect scoreAreaRect;

    int timerId;
    int currentDelay;
    bool isPaused;
    bool obstacleMode;
    QList<QPoint> obstacles;

    static const int DEFAULT_DELAY = 100;
    static const int WIDTH = 500;
    static const int HEIGHT = 500;
    static const int DOT_SIZE = 20;

    void initGame();
    void restartGame();
    void draw();
    void checkCollision();
    void gameOver();
    void pauseGame();
    void createMenu();
    void generateObstacles();
    void updateAreas();  // 添加这行

private slots:
    void setEasyMode();
    void setMediumMode();
    void setHardMode();
    void saveGame();
    void loadGame();
    void toggleSound();
    void setClassicSkin();
    void setDarkSkin();
    void setNeonSkin();
    void setNatureSkin();
    void toggleObstacleMode();
};

#endif // GAMEWINDOW_H
