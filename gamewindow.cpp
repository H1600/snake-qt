#include "gamewindow.h"
#include <QPainter>
#include <QLinearGradient>
#include <QRadialGradient>
#include <QMenu>
#include <QAction>
#include <QRandomGenerator>

GameWindow::GameWindow(QWidget *parent) : QWidget(parent)
{
    setFixedSize(WIDTH, HEIGHT);
    setWindowTitle("QT贪吃蛇游戏");
    // 设置窗口大小，考虑分数区域
    setFixedSize(WIDTH, HEIGHT + 60); // 原高度+60像素的分数区域
    scoreManager = new ScoreManager(this);
    soundManager = new SoundManager(this);
    skinManager = new SkinManager(this);

    currentDelay = DEFAULT_DELAY;
    isPaused = false;
    obstacleMode = false;

    createMenu();
    initGame();
    updateAreas();
}

GameWindow::~GameWindow()
{
    delete snake;
    delete food;
    delete scoreManager;
    delete soundManager;
    delete skinManager;
}

void GameWindow::initGame()
{
    snake = new Snake(WIDTH, HEIGHT, DOT_SIZE);
    food = new Food(WIDTH, HEIGHT, DOT_SIZE);

    if (obstacleMode) {
        generateObstacles();
    } else {
        obstacles.clear();
    }

    food->generate(snake->getBody(), obstacles);
    timerId = startTimer(currentDelay);
}

void GameWindow::restartGame()
{
    killTimer(timerId);
    delete snake;
    delete food;
    initGame();
}

void GameWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    // 1. 绘制背景
    painter.fillRect(rect(), skinManager->getBackgroundColor());

    // 2. 绘制分数区域
    painter.fillRect(scoreAreaRect, skinManager->getBackgroundColor());
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 14, QFont::Bold));
    painter.drawText(scoreAreaRect.adjusted(200, 30, -10, -10),
                     Qt::AlignLeft | Qt::AlignTop,
                     QString("分数: %1").arg(snake->getLength() - 3));
    painter.drawText(scoreAreaRect.adjusted(10, 30, -10, -10),
                     Qt::AlignLeft | Qt::AlignTop,
                     QString("最高分: %1").arg(scoreManager->getHighScore()));

    // 3. 游戏区域
    painter.setClipRect(gameAreaRect);

    // 绘制网格
    painter.setPen(skinManager->getGridColor());
    for (int x = gameAreaRect.left(); x < gameAreaRect.right(); x += DOT_SIZE) {
        painter.drawLine(x, gameAreaRect.top(), x, gameAreaRect.bottom());
    }
    for (int y = gameAreaRect.top(); y < gameAreaRect.bottom(); y += DOT_SIZE) {
        painter.drawLine(gameAreaRect.left(), y, gameAreaRect.right(), y);
    }

    // 绘制障碍物
    if (obstacleMode) {
        painter.setBrush(Qt::darkGray); // 可扩展为皮肤色
        painter.setPen(Qt::darkGray);
        for (const QPoint &obstacle : obstacles) {
            painter.drawRect(obstacle.x(), obstacle.y() + gameAreaRect.top(), DOT_SIZE, DOT_SIZE);
        }
    }

    // 绘制蛇身
    painter.setBrush(skinManager->getSnakeColor());
    painter.setPen(skinManager->getSnakeColor().darker());
    for (const QPoint &point : snake->getBody()) {
        painter.drawEllipse(point.x(), point.y() + gameAreaRect.top(), DOT_SIZE, DOT_SIZE);
    }

    // 绘制蛇头
    QPoint head = snake->getHead();
    painter.setBrush(skinManager->getSnakeHeadColor());
    painter.setPen(skinManager->getSnakeHeadColor().darker());
    painter.drawEllipse(head.x(), head.y() + gameAreaRect.top(), DOT_SIZE, DOT_SIZE);

    // 绘制食物
    painter.setBrush(skinManager->getFoodColor());
    painter.setPen(skinManager->getFoodColor().darker());
    painter.drawEllipse(food->getPosition().x(),
                        food->getPosition().y() + gameAreaRect.top(),
                        DOT_SIZE, DOT_SIZE);

    if (isPaused) {
        painter.setClipping(false);
        painter.setPen(Qt::red);
        painter.setFont(QFont("Arial", 36, QFont::Bold));
        painter.drawText(gameAreaRect, Qt::AlignCenter, "游戏暂停");
    }
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        if (snake->getDirection() != Snake::Direction::Right || snake->getLength() == 1)
            snake->setDirection(Snake::Direction::Left);
        break;
    case Qt::Key_Right:
        if (snake->getDirection() != Snake::Direction::Left || snake->getLength() == 1)
            snake->setDirection(Snake::Direction::Right);
        break;
    case Qt::Key_Up:
        if (snake->getDirection() != Snake::Direction::Down || snake->getLength() == 1)
            snake->setDirection(Snake::Direction::Up);
        break;
    case Qt::Key_Down:
        if (snake->getDirection() != Snake::Direction::Up || snake->getLength() == 1)
            snake->setDirection(Snake::Direction::Down);
        break;
    case Qt::Key_Space:
        pauseGame();
        break;
    case Qt::Key_R:
        if (isPaused) {
            restartGame();
        }
        break;
    }
}

void GameWindow::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    if (!isPaused) {
        snake->move();
        checkCollision();
    }
    repaint();
}

void GameWindow::checkCollision()
{
    // 检查是否吃到食物
    if (snake->getHead() == food->getPosition()) {
        soundManager->playEatSound();
        snake->grow();
        food->generate(snake->getBody(), obstacles);
    }

    // 检查碰撞 - 注意游戏区域偏移
    QPoint head = snake->getHead();
    if (head.x() < 0 ||
        head.y() < 0 ||
        head.x() >= gameAreaRect.width() ||
        head.y() >= gameAreaRect.height() ||
        snake->checkSelfCollision() ||
        (obstacleMode && obstacles.contains(head))) {
        soundManager->playCrashSound();
        gameOver();
    }
}

void GameWindow::gameOver()
{
    killTimer(timerId);
    int score = snake->getLength() - 3;
    scoreManager->saveScore(score);

    QMessageBox msgBox;
    msgBox.setWindowTitle("游戏结束");
    msgBox.setText(QString("游戏结束!\n你的分数: %1\n最高分: %2").arg(score).arg(scoreManager->getHighScore()));
    msgBox.addButton("再来一局", QMessageBox::AcceptRole);
    msgBox.addButton("退出", QMessageBox::RejectRole);

    if (msgBox.exec() == QMessageBox::AcceptRole) {
        initGame();
    } else {
        close();
    }
}

void GameWindow::pauseGame()
{
    isPaused = !isPaused;
    if (isPaused) {
        setWindowTitle("QT贪吃蛇游戏 - 已暂停");
    } else {
        setWindowTitle("QT贪吃蛇游戏");
    }
}

void GameWindow::createMenu()
{
    QMenuBar *menuBar = new QMenuBar(this);

    // 游戏菜单
    QMenu *gameMenu = menuBar->addMenu("游戏");

    QAction *saveAction = gameMenu->addAction("保存游戏");
    QAction *loadAction = gameMenu->addAction("加载游戏");
    QAction *soundAction = gameMenu->addAction("音效开关");
    QAction *obstacleAction = gameMenu->addAction("障碍物模式");

    soundAction->setCheckable(true);
    soundAction->setChecked(true);
    obstacleAction->setCheckable(true);
    obstacleAction->setChecked(false);

    connect(saveAction, &QAction::triggered, this, &GameWindow::saveGame);
    connect(loadAction, &QAction::triggered, this, &GameWindow::loadGame);
    connect(soundAction, &QAction::triggered, this, &GameWindow::toggleSound);
    connect(obstacleAction, &QAction::triggered, this, &GameWindow::toggleObstacleMode);

    // 难度菜单
    QMenu *difficultyMenu = menuBar->addMenu("难度");

    QAction *easyAction = difficultyMenu->addAction("简单");
    QAction *mediumAction = difficultyMenu->addAction("中等");
    QAction *hardAction = difficultyMenu->addAction("困难");

    connect(easyAction, &QAction::triggered, this, &GameWindow::setEasyMode);
    connect(mediumAction, &QAction::triggered, this, &GameWindow::setMediumMode);
    connect(hardAction, &QAction::triggered, this, &GameWindow::setHardMode);

    // 皮肤菜单
    QMenu *skinMenu = menuBar->addMenu("皮肤");

    QAction *classicAction = skinMenu->addAction("经典");
    QAction *darkAction = skinMenu->addAction("暗黑");
    QAction *neonAction = skinMenu->addAction("霓虹");
    QAction *natureAction = skinMenu->addAction("自然");

    connect(classicAction, &QAction::triggered, this, &GameWindow::setClassicSkin);
    connect(darkAction, &QAction::triggered, this, &GameWindow::setDarkSkin);
    connect(neonAction, &QAction::triggered, this, &GameWindow::setNeonSkin);
    connect(natureAction, &QAction::triggered, this, &GameWindow::setNatureSkin);
}

void GameWindow::generateObstacles()
{
    obstacles.clear();
    int maxX = (WIDTH / DOT_SIZE) - 1;
    int maxY = (HEIGHT / DOT_SIZE) - 1;
    int obstacleCount = (maxX * maxY) / 10; // 约10%的障碍物

    for (int i = 0; i < obstacleCount; ++i) {
        int x = QRandomGenerator::global()->bounded(0, maxX) * DOT_SIZE;
        int y = QRandomGenerator::global()->bounded(0, maxY) * DOT_SIZE;
        QPoint obstacle(x, y);

        if (!snake->getBody().contains(obstacle) && obstacle != food->getPosition()) {
            obstacles.append(obstacle);
        }
    }
}

void GameWindow::setEasyMode() { currentDelay = 150; restartGame(); }
void GameWindow::setMediumMode() { currentDelay = 100; restartGame(); }
void GameWindow::setHardMode() { currentDelay = 50; restartGame(); }

void GameWindow::saveGame()
{
    pauseGame();
    scoreManager->saveGame(snake->getBody(), food->getPosition(), static_cast<int>(snake->getDirection()));
    QMessageBox::information(this, "保存", "游戏已保存!");
}

void GameWindow::loadGame()
{
    pauseGame();
    QList<QPoint> body;
    QPoint foodPos;
    int direction;

    if (scoreManager->loadGame(body, foodPos, direction)) {
        killTimer(timerId);
        delete snake;
        delete food;

        snake = new Snake(WIDTH, HEIGHT, DOT_SIZE, body, static_cast<Snake::Direction>(direction));
        food = new Food(WIDTH, HEIGHT, DOT_SIZE);
        food->setPosition(foodPos);

        timerId = startTimer(currentDelay);
        repaint();
        QMessageBox::information(this, "加载", "游戏已加载!");
    } else {
        QMessageBox::warning(this, "加载", "没有找到保存的游戏!");
    }
}

void GameWindow::toggleSound()
{
    soundManager->setSoundEnabled(!soundManager->isSoundEnabled());
}

void GameWindow::setClassicSkin() { skinManager->setSkin(SkinManager::Classic); repaint(); }
void GameWindow::setDarkSkin() { skinManager->setSkin(SkinManager::Dark); repaint(); }
void GameWindow::setNeonSkin() { skinManager->setSkin(SkinManager::Neon); repaint(); }
void GameWindow::setNatureSkin() { skinManager->setSkin(SkinManager::Nature); repaint(); }

void GameWindow::toggleObstacleMode()
{
    obstacleMode = !obstacleMode;
    restartGame();
}
void GameWindow::updateAreas()
{
    int scoreHeight = 60; // 分数区域高度
    scoreAreaRect = QRect(0, 0, width(), scoreHeight);
    gameAreaRect = QRect(0, scoreHeight, width(), height() - scoreHeight);
}

void GameWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    updateAreas();
}
