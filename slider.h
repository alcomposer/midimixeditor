#pragma once

#include <QObject>
#include <QWidget>
#include <QSlider>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QSlider>
#include <QLabel>

class Slider : public QWidget
{
	Q_OBJECT
public:
	Slider(QWidget * parent = nullptr);
	QSlider * slider;
	int getChanNumber();
	int getCCNumber();
	void set_cc_number_visibility(bool);
	void set_channel_number_visibility(bool);
private:
	QVBoxLayout * slider_layout;
	QSpinBox * chan_number;
	QSpinBox * cc_number;
	QLabel * chan_label;
	QLabel * cc_label;
public slots:
	void setChanNumber(int);
	void setCCNumber(int);
};
