#pragma once

#include <QObject>
#include <QWidget>

class myCallback : public QWidget
{
	Q_OBJECT
public:
	static void staticCallback(double deltatime, std::vector<unsigned char> *message, void *userData);
	void Callback(double deltatime, std::vector<unsigned char> *message, void *userData);
signals:
	void sendMidi(int, int, int, int);
	void sendSysEx(std::vector<unsigned char> *message);
};
