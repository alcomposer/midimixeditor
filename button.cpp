#include "button.h"

#include <QLabel>

Button::Button(QWidget *parent) :
	QWidget(parent),
	button(new QPushButton(this)),
	button_layout(new QVBoxLayout(this)),
	chan_number(new QSpinBox(this)),
	cc_number(new QSpinBox(this))
{
	button->setDisabled(true);
	button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
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
	cc_number_layout->setMargin(0);
	cc_number_layout->setSpacing(0);

	chan_number_wid->setLayout(chan_number_layout);
	cc_number_wid->setLayout(cc_number_layout);

	button_layout->addWidget(button);
	chan_number->setRange(1,16);
	cc_number->setRange(0,127);
	button_layout->addWidget(chan_number_wid);
	button_layout->addWidget(cc_number_wid);
	button_layout->setAlignment(Qt::AlignCenter);
	button_layout->setMargin(0);
	button_layout->setSpacing(0);
	setLayout(button_layout);
}
