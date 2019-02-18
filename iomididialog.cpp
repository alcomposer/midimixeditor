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

#include "iomididialog.h"

IOMidiDialog::IOMidiDialog(QWidget * parent) :
	QDialog (parent),
	selectMIDI(new IOMidiSelect(this))
{
}
void IOMidiDialog::setPortLists(int currentInPort, QVector<QString> inPorts, int currentOutPort, QVector<QString> outPorts)
{
	selectMIDI->MIDI_in->clear();
	selectMIDI->MIDI_out->clear();

	foreach(QString port, inPorts){
		selectMIDI->MIDI_in->addItem(port);
	}
	foreach(QString port, outPorts){
		selectMIDI->MIDI_out->addItem(port);
	}
	selectMIDI->MIDI_in->setCurrentIndex(currentInPort);
	selectMIDI->MIDI_out->setCurrentIndex(currentOutPort);
	setFixedSize(selectMIDI->sizeHint());
}
