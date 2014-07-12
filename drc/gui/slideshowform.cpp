#include "slideshowform.h"
#include "ui_slideshowform.h"
#include <QDebug>
#include <QPropertyAnimation>
#include <QTime>

//SlideShowForm::SlideShowForm(WidgetVector slides)
//    : _slides(slides)
//    , self(parent)
//{

//}

SlideShowForm::SlideShowForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SlideShowForm)
{
    ui->setupUi(this);
    SetCurrentSlideIndex(0);    // attempt to load the first slide
}

SlideShowForm::~SlideShowForm()
{
    delete ui;
}

void SlideShowForm::on_rightButton_clicked()
{
    if(_slides.size() > 1)
    {
        // animation:
        int duration = 250;
        QPropertyAnimation *animation = new QPropertyAnimation(ui->container, "pos");
        animation->setDuration(duration);
        QPoint origin = ui->container->pos();
        animation->setStartValue(origin);
        animation->setEndValue(QPoint(2280,origin.y()));
        animation->start();

        // Pause
        QTime dieTime= QTime::currentTime().addMSecs(duration);
        while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

        // Showing last one, cycle to the first
        if(_currentIndex == ((int)_slides.size()-1) )
            SetCurrentSlideIndex(0);
        else
            SetCurrentSlideIndex(_currentIndex+1);

        // animation with new view back to center
        QPropertyAnimation *animationNewWidget = new QPropertyAnimation(ui->container, "pos");
        animationNewWidget->setDuration(duration);
        animationNewWidget->setStartValue(QPoint(-2280,origin.y()));
        animationNewWidget->setEndValue(origin);
        animationNewWidget->start();
    }
}

void SlideShowForm::on_leftButton_clicked()
{
    if(_slides.size() > 1)
    {
        // animation:
        int duration = 250;
        QPropertyAnimation *animation = new QPropertyAnimation(ui->container, "pos");
        animation->setDuration(duration);
        QPoint origin = ui->container->pos();
        animation->setStartValue(origin);
        animation->setEndValue(QPoint(-2280,origin.y()));
        animation->start();

        // Pause
        QTime dieTime= QTime::currentTime().addMSecs(duration);
        while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

        // Showing first one, cycle to the last
        if( _currentIndex == 0 )
            SetCurrentSlideIndex(_slides.size()-1);
        else
            SetCurrentSlideIndex(_currentIndex-1);

        // animation with new view back to center
        QPropertyAnimation *animationNewWidget = new QPropertyAnimation(ui->container, "pos");
        animationNewWidget->setDuration(duration);
        animationNewWidget->setStartValue(QPoint(2280,origin.y()));
        animationNewWidget->setEndValue(origin);
        animationNewWidget->start();

    }
}

//void delay()
//{
//    QTime dieTime= QTime::currentTime().addSecs(1);
//    while( QTime::currentTime() < dieTime )
//    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
//}

// Set the set of widgets to flip through.
void SlideShowForm::SetSlideWidgets(WidgetVector slides)
{
    Reset();

    _slides = slides;
    SetCurrentSlideIndex(0);
}

void SlideShowForm::AddSlide(QWidget* widget)
{
    _slides.push_back(widget);

    if(_slides.size() == 1)
    {
        SetCurrentSlideIndex(0);
    }
}

void SlideShowForm::RemoveCurrentWidget()
{

    if(_currentIndex >= 0 && _currentIndex < (int)_slides.size())
    {
        try {
            QWidget* w = _slides[_currentIndex];
            w->setHidden(true);
            w->setParent(0);
            ui->container->setLayout(nullptr);
        } catch (std::exception &e)
        {
        }
    }
    if(ui->container->layout())
        ui->container->layout()->deleteLater();
    _currentIndex = -1;
}

void SlideShowForm::Reset()
{
    RemoveCurrentWidget();
    _slides.clear();
}

void SlideShowForm::SetCurrentSlideIndex(quint32 index)
{
    if( index < _slides.size() && _slides[index])
    {
        RemoveCurrentWidget();
        QWidget* w = _slides[index];
        w->setHidden(false);
        if(!ui->container->layout())
        {
            QGridLayout* layout = new QGridLayout;
            layout->addWidget(_slides[index]);
            ui->container->setLayout(layout);
        }
        else
        {
            ui->container->layout()->addWidget(_slides[index]);
        }
        _currentIndex = index;
    }
    else
    {
//        QDebug() << "Failed to set slide index!";
    }
}
