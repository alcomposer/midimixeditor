#include "rslider.h"
#include <QDial>
#include <QIntValidator>
#include <QHBoxLayout>
#include <QLabel>

RSlider::RSlider(QWidget *parent) :
	QWidget(parent),
	r_slider(new QDial(this)),
	chan_number(new QSpinBox(this)),
	cc_number(new QSpinBox(this)),
	r_slider_layout(new QVBoxLayout(this))
{
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

	r_slider_layout->addWidget(r_slider);
	chan_number->setRange(1,16);
	cc_number->setRange(0,127);
	r_slider_layout->addWidget(chan_number_wid);
	r_slider_layout->addWidget(cc_number_wid);
	r_slider_layout->setAlignment(Qt::AlignCenter);
	r_slider_layout->setMargin(0);
	r_slider_layout->setSpacing(0);
	setLayout(r_slider_layout);
}
