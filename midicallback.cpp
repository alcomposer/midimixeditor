#include "midicallback.h"

#include <QDebug>
#include <QWidget>
class MainWindow;

midiCallback::midiCallback(QWidget * parent)
{
	connect(this, SIGNAL(sendMidiValue(int)), parent, SLOT(setValue(int)));

}

void midiCallback::myCallBack(double deltatime,
				std::vector<unsigned char> *message,
				void *userData)
{
unsigned int nBytes = message->size();
for (unsigned int i=0; i<nBytes; i++){
	//qInfo() << "Byte " << i << " = " << (int)message->at(i) << ", ";
	if (i == 2) {
		//qInfo() << (int)message->at(2);
		writeValue((int)message->at(2));
	}
}
//if (nBytes > 0)
// qInfo() << "stamp = " << deltatime;


};

void midiCallback::writeValue(int value){
	qInfo() << value;
	extern int midi_value;
	midi_value = value;
}

