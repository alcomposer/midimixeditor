#include "mainwindow.h"
#include "midi.h"
#include <QHBoxLayout>
#include <QSlider>
#include "rtmidi/RtMidi.h"
#include <QDebug>
#include "mycallback.h"
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent),
	midiCallback(new myCallback())
{
	midiIn = new RtMidiIn();
	// Check available ports.
	unsigned int nPorts = midiIn->getPortCount();
	if ( nPorts == 0 ) {
	  qInfo() << "No ports available!\n";
	  return;
	} else qInfo() << "We have: " << nPorts << " port";
	//hardcoded port 1
	if (nPorts ==2 )midiIn->openPort( 1 );

	midiIn->setCallback(&midiCallback->staticCallback, midiCallback);

	QWidget * window = new QWidget(this);
	QHBoxLayout * slider_layout = new QHBoxLayout(window);
	for(int i = 0; i < 9; i++)sliders.push_back(new QSlider());
	foreach (QSlider * slider, sliders){
		slider->setMinimum(0);
		slider->setMaximum(127);
		slider_layout->addWidget(slider);
	}
	connect(midiCallback, SIGNAL(sendMidi(int,int)), this, SLOT(setSlider(int,int)));

	setCentralWidget(window);
}

MainWindow::~MainWindow()
{

}

void MainWindow::setSlider(int cc, int value)
{
	qInfo() << "cc: " << cc << " value: " << value;
	if (cc == 19) sliders.at(0)->setValue(value);
	if (cc == 23) sliders.at(1)->setValue(value);
	if (cc == 27) sliders.at(2)->setValue(value);
	if (cc == 31) sliders.at(3)->setValue(value);
	if (cc == 49) sliders.at(4)->setValue(value);
	if (cc == 53) sliders.at(5)->setValue(value);
	if (cc == 57) sliders.at(6)->setValue(value);
	if (cc == 61) sliders.at(7)->setValue(value);
	if (cc == 62) sliders.at(8)->setValue(value);
}
