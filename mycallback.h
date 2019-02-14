#ifndef MYCALLBACK_H
#define MYCALLBACK_H

#include <QObject>
#include <QWidget>

class myCallback : public QWidget
{
	Q_OBJECT
public:
	static void staticCallback(double deltatime, std::vector<unsigned char> *message, void *userData);
	void Callback(double deltatime, std::vector<unsigned char> *message, void *userData);
signals:
	void sendMidi(int, int, int);
};

#endif // MYCALLBACK_H
