#ifndef SKINMANAGER_H
#define SKINMANAGER_H

#include <QObject>
#include <QColor>

class SkinManager : public QObject
{
    Q_OBJECT
public:
    enum SkinType { Classic, Dark, Neon, Nature };

    explicit SkinManager(QObject *parent = nullptr);

    void setSkin(SkinType type);
    QColor getSnakeColor() const;
    QColor getSnakeHeadColor() const;
    QColor getFoodColor() const;
    QColor getBackgroundColor() const;
    QColor getGridColor() const;

private:
    SkinType currentSkin;
    QColor snakeColor;
    QColor snakeHeadColor;
    QColor foodColor;
    QColor backgroundColor;
    QColor gridColor;
};

#endif // SKINMANAGER_H
