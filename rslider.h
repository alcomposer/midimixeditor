#pragma once

#include <QObject>
#include <QWidget>
#include <QDial>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>

class RSlider : public QWidget
{
	Q_OBJECT
public:
	explicit RSlider(QWidget *parent = nullptr);
	QDial * r_slider;
	int getChanNumber();
	int getCCNumber();
	void set_cc_number_visibility(bool show);
	void set_channel_number_visibility(bool show);
private:
	QVBoxLayout * r_slider_layout;
	QSpinBox * chan_number;
	QSpinBox * cc_number;
	QLabel * cc_label;
	QLabel * chan_label;
signals:

public slots:
	void setChanNumber(int);
	void setCCNumber(int);
};
