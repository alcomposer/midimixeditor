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
	int V = static_cast<int>(message->at(0));
	int CC = static_cast<int>(message->at(1));
	int Value = static_cast<int>(message->at(2));

	if (static_cast<int>(message->at(0))==240){
		emit sendSysEx(message);
	} else {
		emit sendMidi(V, CC, Value);
	}
}
