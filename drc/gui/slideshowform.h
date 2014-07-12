#ifndef SLIDESHOWFORM_H
#define SLIDESHOWFORM_H

#include <QWidget>

namespace Ui {
class SlideShowForm;
}

typedef std::vector<QWidget*> WidgetVector;

class SlideShowForm : public QWidget
{
    Q_OBJECT

public:
    explicit SlideShowForm(QWidget *parent = 0);
//    SlideShowForm(WidgetVector slides);
    ~SlideShowForm();

    // Set the set of widgets to flip through.
    void SetSlideWidgets(WidgetVector slides);
    void AddSlide(QWidget* widget);
    void Reset();
    void SetCurrentSlideIndex(quint32 index);

private slots:
    void on_rightButton_clicked();

    void on_leftButton_clicked();

private:
    Ui::SlideShowForm *ui;

    // Slides - (a widget collection)
    WidgetVector _slides;
    int _currentIndex;  // which slide in the vector is shown.

    void RemoveCurrentWidget();

};

#endif // SLIDESHOWFORM_H
