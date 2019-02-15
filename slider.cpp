#include "slider.h"
#include <QLabel>

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
	QLabel * chan_label = new QLabel(tr("CH:"));
	QLabel * cc_label = new QLabel(tr("CC:"));
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

	slider_layout->addWidget(slider);
	chan_number->setRange(1,16);
	cc_number->setRange(0,127);
	slider_layout->addWidget(chan_number_wid);
	slider_layout->addWidget(cc_number_wid);
	slider_layout->setAlignment(Qt::AlignCenter);
	slider_layout->setMargin(0);
	slider_layout->setSpacing(0);
	setLayout(slider_layout);
}

int Slider::getChanNumber()
{

}

int Slider::getCCNumber()
{

}

void Slider::setChanNumber(int)
{

}

void Slider::setCCNumber(int)
{

}
