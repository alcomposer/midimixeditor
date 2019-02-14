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
