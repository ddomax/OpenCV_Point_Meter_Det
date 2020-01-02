#ifndef MTEXTTOVOICE_H
#define MTEXTTOVOICE_H

#include <QObject>
#include <QTextToSpeech>

class MTextToVoice : public QObject
{
    Q_OBJECT

private:
    QTextToSpeech *m_speech;

public:
    explicit MTextToVoice(QObject *parent = nullptr);
   ~MTextToVoice();

    void operator<<(const QString& textIn);
    void stopLast();
    QTextToSpeech::State getState();

signals:

public slots:
};

#endif // MTEXTTOVOICE_H
