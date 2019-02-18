/*
This file is part of MIDI MIX EDIT.

MIDI MIX EDIT is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

MIDI MIX EDIT is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar.  If not, see <https://www.gnu.org/licenses/>.
*/

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
