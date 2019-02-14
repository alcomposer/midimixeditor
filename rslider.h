#ifndef RSLIDER_H
#define RSLIDER_H

#include <QObject>
#include <QWidget>
#include <QDial>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QSpinBox>

class RSlider : public QWidget
{
	Q_OBJECT
public:
	explicit RSlider(QWidget *parent = nullptr);
	QDial * r_slider;
private:
	QVBoxLayout * r_slider_layout;
	QSpinBox * chan_number;
	QSpinBox * cc_number;
signals:

public slots:
};

#endif // RSLIDER_H
