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

    Particapants(QWidget *parent = 0);
    Particapants(QWidget *parent,std::string input);
    ~Particapants();
    QString getName();
    void setName(std::string str);
private slots:


private:
    Ui::Particapants *ui;

};

#endif // PARTICAPANTS_H
