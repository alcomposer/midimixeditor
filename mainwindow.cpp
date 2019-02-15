#include "mainwindow.h"
#include "mycallback.h"
#include "iomididialog.h"
#include "about.h"

#include "rtmidi/RtMidi.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QGridLayout>
#include <QSizePolicy>
#include <QTextEdit>
#include <iostream>
#include <QMenuBar>
#include <QApplication>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	midiCallback(new myCallback()),
	app_name(new QString(tr("MIDI MIX EDIT"))),
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
	//Draw layout for sliders/rsliders/buttons
	QGridLayout * MIDIMIX_layout = new QGridLayout(mainWindow);

	for (int i =0; i < 9; i++){
		sliders.push_back(new Slider());
		sliders.at(i)->slider->setDisabled(true);
		sliders.at(i)->slider->setMinimum(0);  //[todo] make a setMinimum() member in sliders.h
		sliders.at(i)->slider->setMaximum(127); //[todo]make a setMaximum() member in slider.h
		MIDIMIX_layout->addWidget(sliders.at(i),6,i);
		MIDIMIX_layout->setRowMinimumHeight(6,100);//set sliders row to stretch
		MIDIMIX_layout->setSpacing(10);

		if (i == 8){
			MIDIMIX_layout->addWidget(new QLabel(tr("ROW 1"),this),0,8);
			MIDIMIX_layout->addWidget(new QLabel(tr("ROW 2"),this),1,8);
			MIDIMIX_layout->addWidget(new QLabel(tr("ROW 3"),this),2,8);
			MIDIMIX_layout->addWidget(new QLabel(tr("MUTE"),this),3,8);
			MIDIMIX_layout->addWidget(new QLabel(tr("SOLO"),this),4,8);
			MIDIMIX_layout->addWidget(new QLabel(tr("REC ARM"),this),5,8);
		}

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
			for (int j = 0; j < 3; j++){
				int current = (i*3)+j;
				buttons.push_back(new QPushButton());
				button_state.push_back(0);
				MIDIMIX_layout->addWidget(buttons.at(current),j+3,i);
			}
		}
	}
	connect(midiCallback, SIGNAL(sendMidi(int,int,int)), this, SLOT(setSlider(int,int,int)));
	connect(midiCallback, SIGNAL(sendSysEx(std::vector<unsigned char>*)), this, SLOT(setSysEx(std::vector<unsigned char>*)));

	text_window = new QPlainTextEdit();
	text_window->setFont(QFont("mono"));
	text_window->setReadOnly(true);
	//text_window->setHidden(true);

	QHBoxLayout * mainWindowLayout = new QHBoxLayout();
	mainWindowLayout->addWidget(mainWindow);
	mainWindowLayout->addWidget(text_window);

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
	connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

	saveAsAct = new QAction(tr("Save &As..."), this);
	connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

	loadFromHardwareAct = new QAction(tr("&Load From Hardware"), this);
	connect(loadFromHardwareAct, SIGNAL(triggered()), this, SLOT(loadFromHardware()));

	sendToHardwareAct = new QAction(tr("Send &To Hardware"), this);

	midiSetupAct = new QAction(tr("&MIDI Setup"));
	connect(midiSetupAct, SIGNAL(triggered()), this, SLOT(midiSetup()));

	quitAct = new QAction(tr("&Quit"), this);
	connect(quitAct, SIGNAL(triggered()), this, SLOT(quit()));

	showMidiConsoleAct = new QAction(tr("&MIDI Console"), this);
	showMidiConsoleAct->setCheckable(true);
	showMidiConsoleAct->setChecked(true);
	connect(showMidiConsoleAct, SIGNAL(toggled(bool)), this, SLOT(showMidiConsole(bool)));

	aboutAct = new QAction(tr("&About"), this);
	connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::setSlider(int v, int cc, int value)
{
	//Vertical Sliders
	text_window->appendPlainText("V: " + QString::number(v) + " CC: " + QString::number(cc) + " Value: " + QString::number(value));
	if (v == 176){
	if (cc == 19) sliders.at(0)->slider->setValue(value);
	if (cc == 23) sliders.at(1)->slider->setValue(value);
	if (cc == 27) sliders.at(2)->slider->setValue(value);
	if (cc == 31) sliders.at(3)->slider->setValue(value);
	if (cc == 49) sliders.at(4)->slider->setValue(value);
	if (cc == 53) sliders.at(5)->slider->setValue(value);
	if (cc == 57) sliders.at(6)->slider->setValue(value);
	if (cc == 61) sliders.at(7)->slider->setValue(value);
	if (cc == 62) sliders.at(8)->slider->setValue(value);

	//Radial Sliders
	for (int i = 0; i < rsliders.count(); i++){
	if (cc == rsliders.at(i)->getCCNumber()) rsliders.at(i)->r_slider->setValue(value);
	}
}
	//buttons
	if (cc == 1) buttons.at(0)->setDown(++button_state[0]%2);
	if (cc == 3) buttons.at(1)->setDown(++button_state[1]%2);


}

void MainWindow::newPreset()
{
	QFileDialog * newPresetDialog = new QFileDialog();
	newPresetDialog->setFileMode(QFileDialog::AnyFile);
	workingFile = newPresetDialog->getSaveFileName(this, "Create New Preset");
	QFile newPreset(workingFile);
	newPreset.open(QIODevice::WriteOnly);
	newPreset.close();
	delete newPresetDialog;
	setWindowTitle(*app_name + QString(": ") + workingFile);
}

void MainWindow::openPreset()
{

}

void MainWindow::save()
{
	if(workingFile != ""){
		qInfo() << "We have a data file";
		QFile saveData(workingFile);
		saveData.open(QIODevice::WriteOnly);
		QTextStream stream(&saveData);
		int i, j;
		for (i = 0, j = 8; i < 24; i++, j+=2){
			stream << rsliders.at(i)->getCCNumber() << endl;
			stream << rsliders.at(i)->getChanNumber()-1 << endl;
		}
		saveData.close();
	} else saveAs();
}

void MainWindow::saveAs()
{
	QFileDialog * savePresetAs = new QFileDialog();
	savePresetAs->setFileMode(QFileDialog::AnyFile);
	workingFileNew = savePresetAs->getSaveFileName(this, "Save Preset As");
	delete savePresetAs;
	if (workingFileNew != ""){
		workingFile = workingFileNew;
		save();
		setWindowTitle(*app_name + QString(": ") + workingFile);
	}
}

void MainWindow::loadFromHardware()
{
	qInfo() << "[SysEx] loading from hardware";

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

	viewMenu = menuBar()->addMenu(tr("&View"));
	viewMenu->addAction(showMidiConsoleAct);

	helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(aboutAct);
}
void MainWindow::about(){
	qInfo() << "showing about info";
	About * aboutWindow = new About(this);
	aboutWindow->show();
}

void MainWindow::setSysEx(std::vector<unsigned char> *message)
{

	for (int i = 0; i < message->size(); i++){
	qInfo() << static_cast<int>(message->at(i));
	}
	int i, j;
	for (i = 0, j = 8; i < 24; i++, j+=2){
		rsliders.at(i)->setCCNumber(static_cast<int>(message->at(j)));
		rsliders.at(i)->setChanNumber(static_cast<int>(message->at(j+1)));
	}
	for (i = 0, j = 56; i < 9; i++, j+=2){
		sliders.at(i)->setCCNumber(static_cast<int>(message->at(j)));
		sliders.at(i)->setChanNumber(static_cast<int>(message->at(j+1)));
	}
}

void MainWindow::showMidiConsole(bool show)
{
	text_window->setHidden(!show);
}
