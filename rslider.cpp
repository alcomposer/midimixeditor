#include "rslider.h"
#include <QDial>
#include <QIntValidator>
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>

RSlider::RSlider(QWidget *parent) :
	QWidget(parent),
	r_slider(new QDial(this)),
	r_slider_layout(new QVBoxLayout(this)),
	chan_number(new QSpinBox(this)),
	cc_number(new QSpinBox(this))
{
	r_slider_layout->setSizeConstraint(QLayout::SetMinimumSize);
	r_slider->setDisabled(true);
	r_slider->setMaximumSize(QSize(50,50));
	//r_slider->setSizePolicy(QSizePolicy::MinimumExpanding);
	QHBoxLayout * chan_number_layout = new QHBoxLayout();
	QHBoxLayout * cc_number_layout = new QHBoxLayout();
	chan_label = new QLabel(tr("CH:"));
	cc_label = new QLabel(tr("CC:"));
	QWidget * chan_number_wid = new QWidget();
	QWidget * cc_number_wid = new QWidget();

	chan_number_layout->addWidget(chan_label);
	chan_number_layout->addWidget(chan_number);
	chan_number_layout->setMargin(0);
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
	r_slider_layout->addWidget(r_slider);
	r_slider_layout->addWidget(cc_number_wid);
	r_slider_layout->addWidget(chan_number_wid);

	r_slider_layout->setAlignment(Qt::AlignCenter);
	r_slider_layout->setMargin(0);
	r_slider_layout->setSpacing(0);
	setLayout(r_slider_layout);
}

void RSlider::setChanNumber(int value)
{
	chan_number->setValue(value+1);
}

void RSlider::setCCNumber(int value)
{
	cc_number->setValue(value);
}
int RSlider::getChanNumber()
{
	return chan_number->value()-1;
}
int RSlider::getCCNumber()
{
	return cc_number->value();
}
void RSlider::set_cc_number_visibility(bool show)
{
	cc_number->setHidden(show);
	cc_label->setHidden(show);

}

void RSlider::set_channel_number_visibility(bool show)
{
	chan_number->setHidden(show);
	chan_label->setHidden(show);
}

