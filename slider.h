#pragma once

#include <QObject>
#include <QWidget>
#include <QSlider>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QSlider>

class Slider : public QWidget
{
	Q_OBJECT
public:
	Slider(QWidget * parent = nullptr);
	QSlider * slider;
	int getChanNumber();
	int getCCNumber();
private:
	QVBoxLayout * slider_layout;
	QSpinBox * chan_number;
	QSpinBox * cc_number;

public slots:
	void setChanNumber(int);
	void setCCNumber(int);
};
