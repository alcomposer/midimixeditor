#include "mainwindow.h"
#include "midi.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSlider>
#include "rtmidi/RtMidi.h"
#include <QDebug>
#include "mycallback.h"
#include <QGridLayout>
#include <QSizePolicy>
#include <QTextEdit>
#include <iostream>
#include <QMenuBar>
#include <QApplication>
#include <QFileDialog>
#include "iomididialog.h"

#define appname "MIDImix Editor"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent),
	midiCallback(new myCallback()),
	app_name(new QString(tr("MIDImix Editor"))),
	midi_io_dialog(new IOMidiDialog(this)),
	currentInPort(0),
	currentOutPort(0)
{
	setWindowTitle(*app_name);

	midiOut = new RtMidiOut();
	midiIn = new RtMidiIn();
	midiIn->ignoreTypes( false, true, true );
	// Check available ports.
	unsigned int nPorts = midiIn->getPortCount();
	if ( nPorts == 0 ) {
	  qInfo() << "No ports available!\n";
	  return;
	} else qInfo() << "We have: " << nPorts << " port";
	//hardcoded port 1
	if (nPorts ==2 ){
		midiIn->openPort( 1 );
		midiOut->openPort( 1 );
	}

	midiIn->setCallback(&midiCallback->staticCallback, midiCallback);
	QWidget * window = new QWidget(this);
	QWidget * mainWindow = new QWidget();
	//QHBoxLayout * slider_layout = new QHBoxLayout(window);
	QGridLayout * MIDIMIX_layout = new QGridLayout(mainWindow);
	for (int i =0; i < 9; i++){
		sliders.push_back(new QSlider());
		sliders.at(i)->setMinimum(0);
		sliders.at(i)->setMaximum(127);
		MIDIMIX_layout->addWidget(sliders.at(i),5,i);
		MIDIMIX_layout->setRowMinimumHeight(5,100);//set sliders row to stretch
		MIDIMIX_layout->setSpacing(10);
		//MIDIMIX_layout->setSizeConstraint(QLayout::Set);
		//MIDIMIX_layout->setAlignment(sliders.at(i),Qt::AlignCenter);

		if (i < 8){
			for (int j = 0; j < 3; j++){
				int current = (i*3)+j;
				rsliders.push_back(new RSlider(this));
				rsliders.at(current)->r_slider->setMinimum(0);
				rsliders.at(current)->r_slider->setMaximum(127);
				MIDIMIX_layout->setSpacing(0);
				MIDIMIX_layout->setMargin(0);
				MIDIMIX_layout->setRowStretch(j,0);
				MIDIMIX_layout->setColumnStretch(i,0);
				MIDIMIX_layout->addWidget(rsliders.at(current),j,i);
			}
			for (int j = 0; j < 2; j++){
				int current = (i*2)+j;
				buttons.push_back(new QPushButton());
				button_state.push_back(0);
				MIDIMIX_layout->addWidget(buttons.at(current),j+3,i);
			}
		}
	}
	connect(midiCallback, SIGNAL(sendMidi(int,int,int)), this, SLOT(setSlider(int,int,int)));

	text_window = new QPlainTextEdit();
	text_window->setFont(QFont("mono"));
	text_window->setReadOnly(true);

	QTextEdit * midiDeviceSelect = new QTextEdit();  //temp text, use qdropdown

	QVBoxLayout * mainWindowLayout = new QVBoxLayout();
	mainWindowLayout->addWidget(mainWindow);

	QHBoxLayout * bottomWindowLayout = new QHBoxLayout();
	QWidget * bottomWindow = new QWidget();
	bottomWindowLayout->addWidget(text_window);
	bottomWindowLayout->addWidget(midiDeviceSelect);

	bottomWindow->setLayout(bottomWindowLayout);
	mainWindowLayout->addWidget(bottomWindow);
	window->setLayout(mainWindowLayout);

	setCentralWidget(window);

	createActions();
	createMenues();

}

MainWindow::~MainWindow()
{

}

void MainWindow::createActions()
{
	newAct = new QAction(tr("&New Preset..."), this);
	connect(newAct, SIGNAL(triggered()), this, SLOT(newPreset()));

	openPresetAct = new QAction(tr("&Open Preset..."), this);

	saveAct = new QAction(tr("&Save"), this);

	saveAsAct = new QAction(tr("&Save As..."), this);

	loadFromHardwareAct = new QAction(tr("&Load From Hardware"), this);
	connect(loadFromHardwareAct, SIGNAL(triggered()), this, SLOT(loadFromHardware()));

	sendToHardwareAct = new QAction(tr("&Send To Hardware"), this);

	midiSetupAct = new QAction(tr("&MIDI Setup"));
	connect(midiSetupAct, SIGNAL(triggered()), this, SLOT(midiSetup()));

	quitAct = new QAction(tr("&Quit"), this);
	connect(quitAct, SIGNAL(triggered()), this, SLOT(quit()));
}

void MainWindow::setSlider(int v, int cc, int value)
{
	//Vertical Sliders
	text_window->appendPlainText("V: " + QString::number(v,16) + " CC: " + QString::number(cc,16) + " Value: " + QString::number(value));
	if (v == 176){
	if (cc == 19) sliders.at(0)->setValue(value);
	if (cc == 23) sliders.at(1)->setValue(value);
	if (cc == 27) sliders.at(2)->setValue(value);
	if (cc == 31) sliders.at(3)->setValue(value);
	if (cc == 49) sliders.at(4)->setValue(value);
	if (cc == 53) sliders.at(5)->setValue(value);
	if (cc == 57) sliders.at(6)->setValue(value);
	if (cc == 61) sliders.at(7)->setValue(value);
	if (cc == 62) sliders.at(8)->setValue(value);

	//Radial Sliders
	if (cc == 16) rsliders.at(0)->r_slider->setValue(value);
	if (cc == 17) rsliders.at(1)->r_slider->setValue(value);
	if (cc == 18) rsliders.at(2)->r_slider->setValue(value);

	if (cc == 20) rsliders.at(3)->r_slider->setValue(value);
	if (cc == 21) rsliders.at(4)->r_slider->setValue(value);
	if (cc == 22) rsliders.at(5)->r_slider->setValue(value);

	if (cc == 24) rsliders.at(6)->r_slider->setValue(value);
	if (cc == 25) rsliders.at(7)->r_slider->setValue(value);
	if (cc == 26) rsliders.at(8)->r_slider->setValue(value);

	if (cc == 28) rsliders.at(9)->r_slider->setValue(value);
	if (cc == 29) rsliders.at(10)->r_slider->setValue(value);
	if (cc == 30) rsliders.at(11)->r_slider->setValue(value);

	if (cc == 46) rsliders.at(12)->r_slider->setValue(value);
	if (cc == 47) rsliders.at(13)->r_slider->setValue(value);
	if (cc == 48) rsliders.at(14)->r_slider->setValue(value);

	if (cc == 50) rsliders.at(15)->r_slider->setValue(value);
	if (cc == 51) rsliders.at(16)->r_slider->setValue(value);
	if (cc == 52) rsliders.at(17)->r_slider->setValue(value);

	if (cc == 54) rsliders.at(18)->r_slider->setValue(value);
	if (cc == 55) rsliders.at(19)->r_slider->setValue(value);
	if (cc == 56) rsliders.at(20)->r_slider->setValue(value);

	if (cc == 58) rsliders.at(21)->r_slider->setValue(value);
	if (cc == 59) rsliders.at(22)->r_slider->setValue(value);
	if (cc == 60) rsliders.at(23)->r_slider->setValue(value);
	}

	//buttons
	if (cc == 1) buttons.at(0)->setDown(++button_state[0]%2);
	if (cc == 3) buttons.at(1)->setDown(++button_state[1]%2);


}

void MainWindow::newPreset()
{
	QFileDialog * newPresetDialog = new QFileDialog();
	newPresetDialog->setFileMode(QFileDialog::AnyFile);
	QString strFile = newPresetDialog->getSaveFileName(this, "Create New Preset");
	QFile newPreset(strFile);
	newPreset.open(QIODevice::WriteOnly);
	newPreset.close();
	delete newPresetDialog;
	setWindowTitle(*app_name + QString(": ") + strFile);
}

void MainWindow::openPreset()
{

}

void MainWindow::save()
{

}

void MainWindow::saveAs()
{

}

void MainWindow::loadFromHardware()
{
	qInfo() << "sysex from hardware:\n-------";

	std::vector<unsigned char> message;
	message ={240, //sysex start
			  71,  //akai
			  0x00,
			  49,
			  0x66, //hex code to ask for hardware state
			  247   //sysex end
			 };

	midiOut->sendMessage(&message);

}

void MainWindow::sendToHardware()
{

}

void MainWindow::midiSetup()
{
	QVector<QString> inPorts, outPorts;
	for (int i = 0; i < midiIn->getPortCount(); i++){
		inPorts.push_back(QString::fromStdString(midiIn->getPortName(i)));
	}
	for (int i = 0; i < midiOut->getPortCount(); i++){
		outPorts.push_back(QString::fromStdString(midiOut->getPortName(i)));
	}
	midi_io_dialog->setPortLists(currentInPort, inPorts, currentOutPort, outPorts);
	midi_io_dialog->show();
}

void MainWindow::quit()
{
	QApplication::closeAllWindows();
}

void MainWindow::setMidiInPort(const int port)
{
	midiIn->closePort();
	midiIn->openPort(port);
	currentInPort = port;
}

void MainWindow::setMidiOutPort(const int port)
{
	midiOut->closePort();
	midiOut->openPort(port);
	currentOutPort = port;

}
void MainWindow::createMenues(){
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(newAct);
	fileMenu->addAction(openPresetAct);
	fileMenu->addSeparator();
	fileMenu->addAction(saveAct);
	fileMenu->addAction(saveAsAct);
	fileMenu->addSeparator();
	fileMenu->addAction(loadFromHardwareAct);
	fileMenu->addAction(sendToHardwareAct);
	fileMenu->addSeparator();
	fileMenu->addAction(midiSetupAct);
	fileMenu->addSeparator();
	fileMenu->addAction(quitAct);
}
