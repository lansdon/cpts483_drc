#ifndef SEARCHWIZARD_H
#define SEARCHWIZARD_H

#include <QObject>
#include <QWizard>


const QString FIELD_SEARCH_TYPE = "FIELD_SEARCH_TYPE";



class SearchWizard : public QWizard
{
    Q_OBJECT
public:
    SearchWizard(QWidget *parent = 0);

    void accept();

signals:

public slots:

};

#endif // SEARCHWIZARD_H
