#include "slotsgame.h"
#include "ui_slotsgame.h"
#include "Mediator.h"
#include "MediatorKeys.h"
#include <QMessageBox>
#include <QMediaContent>
#include <QDebug>
#include <QString>
#include <QFuture>
#include <QtConcurrent>


#include <windows.h>

std::map<int,QString> imageMap;


SlotsGame::SlotsGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SlotsGame),
    _cash(500)
{
    ui->setupUi(this);
    ui->groupBox->setStyleSheet("QGroupBox {\
                                border: 2px solid gray;\
                                border-radius: 5px;\
                                margin-top: 8px;\
                               }");
    imageMap[0] = ":images/7.jpg";
    imageMap[1] = ":images/cherries.png";
    imageMap[2] = ":images/coin.jpg";
    imageMap[3] = ":images/dollarSign.jpg";
    _imageSlot1 = qrand() % 4;
    _imageSlot2 = qrand() % 4;
    _imageSlot3 = qrand() % 4;
    _imageSlot4 = qrand() % 4;
    display();
}

SlotsGame::~SlotsGame()
{
    delete ui;
}

void SlotsGame::on_addMoneyPushButton_clicked()
{
    if(_cash < 200)
        _cash += 500;
    ui->cashDisplayLabel->setText("$" + QString::number(_cash));
}

void SlotsGame::on_spinPushButton_clicked()
{

    PlaySpin();
    ui->spinPushButton->setEnabled(false);
    ui->addMoneyPushButton->setEnabled(false);

    _cash -= 25;
    ui->cashDisplayLabel->setText("$" + QString::number(_cash));
    _imageSlot1 = qrand() % 4;
    _imageSlot2 = qrand() % 4;
    _imageSlot3 = qrand() % 4;
    _imageSlot4 = qrand() % 4;
    spinDisplay();

    if((_imageSlot1 == _imageSlot2) && (_imageSlot2 == _imageSlot3) && (_imageSlot3 == _imageSlot4))
        win();

    display();
    ui->spinPushButton->setEnabled(true);
    ui->addMoneyPushButton->setEnabled(true);
}
void SlotsGame::PlaySpin()
{
    QThread *thread = new QThread;
    playSoundWorker* worker = new playSoundWorker;
    worker->moveToThread(thread);
    connect(thread, SIGNAL(started()), worker, SLOT(playSound()));
    thread->start(QThread::HighPriority);
}
void SlotsGame::PlayWin()
{
    QThread *thread = new QThread;
    playSoundWorker* worker = new playSoundWorker;
    worker->moveToThread(thread);
    connect(thread, SIGNAL(started()), worker, SLOT(playWinnerSound()));
    thread->start(QThread::HighPriority);

}

void SlotsGame::display()
{


    ui->Slot1label->setPixmap(QPixmap(imageMap[_imageSlot1]));



    ui->Slot2label->setPixmap(QPixmap(imageMap[_imageSlot2]));



    ui->Slot3label->setPixmap(QPixmap(imageMap[_imageSlot3]));


    ui->Slot4label->setPixmap(QPixmap(imageMap[_imageSlot4]));
    ui->cashDisplayLabel->setText("$" + QString::number(_cash));
    if(_cash <= 0)
        lose();
}

void SlotsGame::spinDisplay()
{
    int num;
    for(int i = 0; i < 21; i++)
    {
        if(i < 10)
        {
            num = (qrand() % 4);
            ui->Slot1label->setPixmap(QPixmap(imageMap[num]));
            ui->Slot1label->repaint();
        }
        else
        {
            ui->Slot1label->setPixmap(QPixmap(imageMap[_imageSlot1]));
            ui->Slot1label->repaint();
        }
        if(i < 15)
        {
            num = (qrand() % 4);
            ui->Slot2label->setPixmap(QPixmap(imageMap[num]));
            ui->Slot2label->repaint();
        }
        else
        {
            ui->Slot2label->setPixmap(QPixmap(imageMap[_imageSlot2]));
            ui->Slot2label->repaint();
        }
        if(i < 18)
        {
            num = (qrand() % 4);
            ui->Slot3label->setPixmap(QPixmap(imageMap[num]));
            ui->Slot3label->repaint();
        }
        else
        {
            ui->Slot3label->setPixmap(QPixmap(imageMap[_imageSlot3]));
            ui->Slot3label->repaint();
        }
        if(i < 21)
        {
            num = (qrand() % 4);
            ui->Slot4label->setPixmap(QPixmap(imageMap[num]));
            ui->Slot4label->repaint();
        }
        else
        {
            ui->Slot4label->setPixmap(QPixmap(imageMap[_imageSlot4]));
            ui->Slot4label->repaint();
        }
        Sleep(250);
    }
}

void SlotsGame::win()
{
    PlayWin();
    _cash += 500;
}

void SlotsGame::lose()
{
    QMessageBox msgBox;
    msgBox.addButton(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setText("You lose, Play again?");

    int selection = msgBox.exec();

    if(selection == QMessageBox::Yes)
        on_addMoneyPushButton_clicked();
    else
        on_quitPushButton_clicked();
}

void SlotsGame::on_quitPushButton_clicked()
{
    Mediator::Call(MKEY_GUI_ENABLE_MENUS);
}
