#ifndef MIDI_H
#define MIDI_H

#include <QObject>
#include <QWidget>
#include "rtmidi/RtMidi.h"
#include <QDebug>
#include <QByteArray>

class midi : public QObject
{
	Q_OBJECT
public:
	midi();

	RtMidiIn * midiIn;
	void myCallBack(double deltatime,
							std::vector<unsigned char> *message,
							void *userData);

signals:
	void midiValue(int);
};

#endif // MIDI_H
