#include "button.h"

#include <QLabel>
#include <QDebug>

Button::Button(QWidget *parent) :
	QWidget(parent),
	button(new QPushButton(this)),
	button_text(new QLabel()),
	button_layout(new QVBoxLayout(this)),
	note_number(new QSpinBox(this)),
	chan_number(new QSpinBox(this)),
	cc_number(new QSpinBox(this)),
	cc_midi_visability(true)
{
	button_mode = BMode::NOTE;  //[TODO] hard coded for now, needs to read default setup

	button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	button->setText(tr("NOTE"));

	connect(button, SIGNAL(clicked()), this, SLOT(set_button_text()));

	QHBoxLayout * note_number_layout = new QHBoxLayout();
	QHBoxLayout * chan_number_layout = new QHBoxLayout();
	QHBoxLayout * cc_number_layout   = new QHBoxLayout();

	note_label = new QLabel(tr("NT:"));
	chan_label = new QLabel(tr("CH:"));
	cc_label   = new QLabel(tr("CC:"));

	note_number_wid = new QWidget();
	chan_number_wid = new QWidget();
	cc_number_wid   = new QWidget();

	note_number_layout->addWidget(note_label);
	note_number_layout->addWidget(note_number);
	note_number_layout->setMargin(1);
	note_number_layout->setSpacing(0);
	note_number_wid->setMaximumWidth(80);

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

	note_number_wid->setLayout(note_number_layout);
	chan_number_wid->setLayout(chan_number_layout);
	cc_number_wid->setLayout(cc_number_layout);

	note_number->setRange(0,127);
	chan_number->setRange(1,16);
	cc_number->setRange(0,127);

	//add the widgets in the order we want them displaied
	button_layout->addWidget(button);
	button_layout->addWidget(note_number_wid);
	button_layout->addWidget(cc_number_wid);
	button_layout->addWidget(chan_number_wid);

	button_layout->setAlignment(Qt::AlignCenter);
	button_layout->setMargin(0);
	button_layout->setSpacing(0);
	setLayout(button_layout);

	update_display();
}

void Button::set_button_text()
{
	if(button_mode==BMode::NOTE){
		button->setText(tr("CC"));
		button_mode=BMode::CC;
	}else {
		button->setText(tr("NOTE"));
		button_mode=BMode::NOTE;
	}
	update_display();
}

void Button::update_display()
{
	if(button_mode==BMode::NOTE){
		cc_number_wid->setHidden(true);
		note_number_wid->setHidden(false);
		button->setText(tr("NOTE"));
	}else {
		cc_number_wid->setHidden(false);
		note_number_wid->setHidden(true);
		button->setText(tr("CC"));
	}
}

void Button::setButtonMode(BMode::buttonMode mode)
{
	button_mode = mode;
	update_display();
}

void Button::setChanNumber(int value)
{
	chan_number->setValue(value+1);
}

void Button::setCCNumber(int value)
{
	cc_number->setValue(value);
}

void Button::setNoteNumber(int value)
{
	note_number->setValue(value);
}
void Button::set_cc_number_visibility(bool show)
{
	cc_number->setHidden(show);
	cc_label->setHidden(show);
	note_number->setHidden(show);
	note_label->setHidden(show);
	cc_midi_visability = !show;
}

int Button::getChanNumber()
{
	return chan_number->value()-1; //we have to minus 1 as we are displaying the value as 1 indexed
}

int Button::getButtonState()
{
	return !button_mode;
}

int Button::getNoteCCNumber()
{
	if (button_mode==BMode::CC){
		return cc_number->value();
	}else {
		return note_number->value();
	}
}

void Button::set_channel_number_visibility(bool show)
{
	chan_number->setHidden(show);
	chan_label->setHidden(show);
}

