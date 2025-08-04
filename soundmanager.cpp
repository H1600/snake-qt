#include "soundmanager.h"
#include <QDebug>

SoundManager::SoundManager(QObject *parent) : QObject(parent), soundEnabled(true)
{
    eatSound.setSource(QUrl("qrc:/sounds/eat.wav"));
    crashSound.setSource(QUrl("qrc:/sounds/crash.wav"));

    eatSound.setVolume(0.5f);
    crashSound.setVolume(0.5f);
}

void SoundManager::playEatSound()
{
    if (soundEnabled) {
        eatSound.play();
    }
}

void SoundManager::playCrashSound()
{
    if (soundEnabled) {
        crashSound.play();
    }
}

void SoundManager::setSoundEnabled(bool enabled)
{
    soundEnabled = enabled;
}

bool SoundManager::isSoundEnabled() const
{
    return soundEnabled;
}
