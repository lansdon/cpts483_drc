#ifndef SLOTSGAME_H
#define SLOTSGAME_H

#include <QWidget>
#include <QSoundEffect>
#include <QThread>

namespace Ui {
class SlotsGame;
}
class playSoundWorker : public QObject
{
    Q_OBJECT
private:
    QSoundEffect *spin, *winner;
public slots:
    void playSound()
    {
        spin = new QSoundEffect(this);
        spin->setSource(QUrl::fromLocalFile(":images/slot_machine_run.wav"));
        spin->play();
    }
    void playWinnerSound()
    {
        winner = new QSoundEffect(this);
        winner->setSource(QUrl::fromLocalFile(":images/slot_machine_winner.wav"));
        winner->play();
    }
};
class SlotsGame : public QWidget
{
    Q_OBJECT

public:
    explicit SlotsGame(QWidget *parent = 0);
    ~SlotsGame();

private slots:
    void on_addMoneyPushButton_clicked();

    void on_spinPushButton_clicked();

    void on_quitPushButton_clicked();

    void PlaySpin();

    void PlayWin();

private:
    Ui::SlotsGame *ui;
    int _cash;
    int _imageSlot1, _imageSlot2, _imageSlot3, _imageSlot4;
    void display();
    void spinDisplay();
    void win();
    void lose();

};

#endif // SLOTSGAME_H
