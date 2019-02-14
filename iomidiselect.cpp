#include "iomidiselect.h"


#include <mainwindow.h>
#include <QHBoxLayout>

IOMidiSelect::IOMidiSelect(QWidget *parent) :
	QWidget(parent),
	IO_MIDI_layout(new QHBoxLayout(parent)),
	MIDI_in(new QComboBox()),
	MIDI_out(new QComboBox()),
	MIDI_in_label(new QLabel(tr("MIDI in:"))),
	MIDI_out_label(new QLabel(tr("MIDI out:")))
{
	IO_MIDI_layout->addWidget(MIDI_in_label);
	IO_MIDI_layout->addWidget(MIDI_in);
	connect(MIDI_in, SIGNAL(activated(int)), parentWidget()->parentWidget(), SLOT(setMidiInPort(int)));

	IO_MIDI_layout->addWidget(MIDI_out_label);
	IO_MIDI_layout->addWidget(MIDI_out);
	connect(MIDI_out, SIGNAL(activated(int)), parentWidget()->parentWidget(), SLOT(setMidiOutPort(int)));
	setLayout(IO_MIDI_layout);
}
