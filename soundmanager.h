#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QObject>
#include <QtMultimedia\QSoundEffect>
#include <QUrl>

class SoundManager : public QObject
{
    Q_OBJECT
public:
    explicit SoundManager(QObject *parent = nullptr);

    void playEatSound();
    void playCrashSound();
    void setSoundEnabled(bool enabled);
    bool isSoundEnabled() const;

private:
    QSoundEffect eatSound;
    QSoundEffect crashSound;
    bool soundEnabled;
};

#endif // SOUNDMANAGER_H
