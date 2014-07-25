#ifndef SLIDESHOWFORM_H
#define SLIDESHOWFORM_H

#include <QWidget>

namespace Ui {
class SlideShowForm;
}

typedef std::vector<QWidget*> WidgetVector;

/*!
 * \brief The SlideShowForm class
 */
class SlideShowForm : public QWidget
{
    Q_OBJECT

public:
    explicit SlideShowForm(QWidget *parent = 0);
//  SlideShowForm(WidgetVector slides);
    ~SlideShowForm();

    // Set the set of widgets to flip through.
    /*!
     * \brief SetSlideWidgets
     * \param slides
     */
    void SetSlideWidgets(WidgetVector slides);
    /*!
     * \brief AddSlide
     * \param widget
     */
    void AddSlide(QWidget* widget);
    /*!
     * \brief Reset
     */
    void Reset();
    /*!
     * \brief SetCurrentSlideIndex
     * \param index
     */
    void SetCurrentSlideIndex(quint32 index);

private slots:
    /*!
     * \brief on_rightButton_clicked
     */
    void on_rightButton_clicked();
    /*!
     * \brief on_leftButton_clicked
     */
    void on_leftButton_clicked();

private:
    Ui::SlideShowForm *ui;

    // Slides - (a widget collection)
    WidgetVector _slides;
    int _currentIndex;  // which slide in the vector is shown.
    /*!
     * \brief RemoveCurrentWidget
     */
    void RemoveCurrentWidget();

};

#endif // SLIDESHOWFORM_H
