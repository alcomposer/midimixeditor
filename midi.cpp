#include "midi.h"
#include "rtmidi/RtMidi.h"

#include <QDebug>

midi::midi()
{
	midiIn = new RtMidiIn();
	// Check available ports.
	unsigned int nPorts = midiIn->getPortCount();
	if ( nPorts == 0 ) {
	  qInfo() << "No ports available!\n";
	  return;
	} else qInfo() << "We have: " << nPorts << " port";
	if (nPorts ==2) midiIn->openPort( 1 );

}

void midi::myCallBack(double deltatime, std::vector<unsigned char> *message, void *userData)
{
	midi * midiIn = (midi*)userData;
	qInfo() << "number: " <<(int)message->at(1) << " value: " << (int)message->at(2);
	//emit reinterpret_cast<midi*>(userData)->midiValue(message->at(2));
	emit midiValue(message->at(2));
}
