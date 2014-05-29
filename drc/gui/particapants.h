#ifndef PARTICAPANTS_H
#define PARTICAPANTS_H

#include <QWidget>

namespace Ui {
class Particapants;
}

class Particapants : public QWidget
{
    Q_OBJECT

public:
    explicit Particapants(QWidget *parent = 0);
    ~Particapants();

private:
    Ui::Particapants *ui;
};

#endif // PARTICAPANTS_H
