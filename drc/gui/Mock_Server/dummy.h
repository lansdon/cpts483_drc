#ifndef DUMMY_H
#define DUMMY_H

#include <QObject>

class dummy : public QObject
{
    Q_OBJECT
public:
    explicit dummy(QObject *parent = 0);

signals:

public slots:

};

#endif // DUMMY_H
