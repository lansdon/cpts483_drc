#ifndef DRC_H
#define DRC_H

#include <QtWidgets/QMainWindow>
#include "ui_drc.h"

class drc : public QMainWindow
{
	Q_OBJECT

public:
	drc(QWidget *parent = 0);
	~drc();

private:
	Ui::drcClass ui;
};

#endif // DRC_H
