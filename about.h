#pragma once

#include <QObject>
#include <QWidget>
#include <QDialog>

class About : public QDialog
{
	Q_OBJECT
public:
	About(QWidget * parent);
};
