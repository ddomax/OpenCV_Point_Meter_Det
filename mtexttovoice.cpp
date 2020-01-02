#include "mtexttovoice.h"

MTextToVoice::MTextToVoice(QObject *parent) : QObject(parent)
{
    m_speech = new QTextToSpeech(0);
    m_speech->setVolume(100);
    m_speech->setRate(0.3); //-1 to +1
    m_speech->setPitch(1);
}

MTextToVoice::~MTextToVoice()
{
    m_speech->deleteLater();
}

void MTextToVoice::operator<<(const QString& textIn)
{
    this->m_speech->say(textIn);
}

void MTextToVoice::stopLast()
{
    this->m_speech->stop();
}

QTextToSpeech::State MTextToVoice::getState()
{
    return m_speech->state();
}
