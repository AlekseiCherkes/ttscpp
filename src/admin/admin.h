#ifndef ADMIN_H
#define ADMIN_H

#include <QtGui/QMainWindow>
#include "ui_admin.h"

class Admin : public QMainWindow
{
	Q_OBJECT

public:
	Admin(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Admin();

private:
	Ui::AdminClass ui;
};

#endif // ADMIN_H
