#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSlider>
#include "rtmidi/RtMidi.h"
#include <QDebug>
#include "mycallback.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
private:
	QVector<QSlider*> sliders;
	void setMidiValue();
	RtMidiIn * midiIn;
	myCallback * midiCallback;
private slots:
	void setSlider(int,int);
};

#endif // MAINWINDOW_H
