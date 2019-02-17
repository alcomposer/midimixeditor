#include "mycallback.h"

#include <QDebug>

void
myCallback::staticCallback(double deltatime,
				std::vector<unsigned char> *message,
				void *userData)
{
static_cast<myCallback *>(userData)->Callback(deltatime, message, userData);
}

void
myCallback::Callback(double deltatime,
						   std::vector<unsigned char> *message,
						  void *userData)
{
	int type = static_cast<int>(message->at(0));
	int type_res = type >> 4;
	int channel = static_cast<int>(message->at(0));
	int chan_res = channel & 0x0f;
	int cc = static_cast<int>(message->at(1));
	int value = static_cast<int>(message->at(2));

	if (static_cast<int>(message->at(0))==240){
		emit sendSysEx(message);
	} else {
		emit sendMidi(type_res, chan_res, cc, value);
	}
}
