#include "slider.h"
#include <QLabel>
#include <QDebug>

Slider::Slider(QWidget * parent) :
	QWidget(parent),
	slider(new QSlider(this)),
	slider_layout(new QVBoxLayout(this)),
	chan_number(new QSpinBox(this)),
	cc_number(new QSpinBox(this))
{
	slider->setDisabled(true);
	slider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QHBoxLayout * chan_number_layout = new QHBoxLayout();
	QHBoxLayout * cc_number_layout = new QHBoxLayout();
	chan_label = new QLabel(tr("CH:"));
	cc_label = new QLabel(tr("CC:"));
	QWidget * chan_number_wid = new QWidget();
	QWidget * cc_number_wid = new QWidget();

	chan_number_layout->addWidget(chan_label);
	chan_number_layout->addWidget(chan_number);
	chan_number_layout->setMargin(1);
	chan_number_layout->setSpacing(0);
	chan_number_wid->setMaximumWidth(80);

	cc_number_layout->addWidget(cc_label);
	cc_number_layout->addWidget(cc_number);
	cc_number_wid->setMaximumWidth(80);
	cc_number_layout->setMargin(1);
	cc_number_layout->setSpacing(0);

	chan_number_wid->setLayout(chan_number_layout);
	cc_number_wid->setLayout(cc_number_layout);


	chan_number->setRange(1,16);
	cc_number->setRange(0,127);
	//add the widgets in the order we want them displaied
	slider_layout->addWidget(slider);
	slider_layout->addWidget(cc_number_wid);
	slider_layout->addWidget(chan_number_wid);

	slider_layout->setAlignment(Qt::AlignCenter);
	slider_layout->setMargin(0);
	slider_layout->setSpacing(0);
	setLayout(slider_layout);
}

void Slider::setChanNumber(int value)
{
	chan_number->setValue(value+1);
}

void Slider::setCCNumber(int value)
{
	cc_number->setValue(value);
}
int Slider::getChanNumber()
{
	return chan_number->value()-1;
}
int Slider::getCCNumber()
{
	return cc_number->value();
}

void Slider::set_cc_number_visibility(bool show)
{
	cc_number->setHidden(show);
	cc_label->setHidden(show);

}

void Slider::set_channel_number_visibility(bool show)
{
	chan_number->setHidden(show);
	chan_label->setHidden(show);
}
