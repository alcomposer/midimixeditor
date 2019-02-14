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
	emit sendMidi(V, CC, Value);
	for (int i = 0; i < message->size(); i++){
	qInfo() << message->at(i);
	}
	qInfo() << "--------";
}
