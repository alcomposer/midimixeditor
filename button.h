#pragma once

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSpinBox>

class Button : public QWidget
{
	Q_OBJECT
public:
	explicit Button(QWidget *parent = nullptr);
	QPushButton * button;
private:
	QVBoxLayout * button_layout;
	QSpinBox * chan_number;
	QSpinBox * cc_number;
signals:

public slots:
};
