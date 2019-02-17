#include "mainwindow.h"
#include "mycallback.h"
#include "iomididialog.h"
#include "about.h"
#include "button.h"

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
	currentOutPort(0),
	ROW_1(new   QLabel(tr("ROW 1"),this)),
	ROW_2(new   QLabel(tr("ROW 2"),this)),
	ROW_3(new   QLabel(tr("ROW 3"),this)),
	_MUTE(new   QLabel(tr("MUTE"),this)),
	_SOLO(new   QLabel(tr("SOLO"),this)),
	REC_ARM(new QLabel(tr("REC ARM"),this))
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

	ROW_1->setAlignment(Qt::AlignTop);
	ROW_2->setAlignment(Qt::AlignTop);
	ROW_3->setAlignment(Qt::AlignTop);
	_MUTE->setAlignment(Qt::AlignTop);
	_SOLO->setAlignment(Qt::AlignTop);
	REC_ARM->setAlignment(Qt::AlignTop);

	for (int i =0; i < 9; i++){
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
		}
		sliders.push_back(new Slider());
		sliders.at(i)->slider->setDisabled(true);
		sliders.at(i)->slider->setMinimum(0);  //[todo] make a setMinimum() member in sliders.h
		sliders.at(i)->slider->setMaximum(127); //[todo]make a setMaximum() member in slider.h
		MIDIMIX_layout->addWidget(sliders.at(i),6,i);
		MIDIMIX_layout->setRowMinimumHeight(6,100);//set sliders row to stretch
		MIDIMIX_layout->setSpacing(10);

		if (i == 8){
			MIDIMIX_layout->addWidget(ROW_1,0,8);
			MIDIMIX_layout->addWidget(ROW_2,1,8);
			MIDIMIX_layout->addWidget(ROW_3,2,8);
			MIDIMIX_layout->addWidget(_MUTE,3,8);
			MIDIMIX_layout->addWidget(_SOLO,4,8);
			MIDIMIX_layout->addWidget(REC_ARM,5,8);
		}
	}
	/*
	 * Add buttons, need to do this per row, not per column
	 * becuase the second row of buttons represents the hidden state of the first row.
	 * This means that the numbering of the buttons is:
	 *
	 *   0 |  1 |  2 |  3 |  4 |  5 |  6 |  7
	 *  -------------------------------------
	 *  16 | 17 | 18 | 19 | 20 | 21 | 22 | 23
	 *  -------------------------------------
	 *   8 |  9 | 10 | 11 | 12 | 13 | 14 | 15
	 */
	for (int x = 0; x < 8; x++){
		int current = x;
		buttons.push_back(new Button());
		MIDIMIX_layout->addWidget(buttons.at(current),3,x);
	}
	for (int x = 0; x < 8; x++){
		int current = x + 8;
		buttons.push_back(new Button());
		MIDIMIX_layout->addWidget(buttons.at(current),5,x);
	}
	for (int x = 0; x < 8; x++){
		int current = x + 16;
		buttons.push_back(new Button());
		MIDIMIX_layout->addWidget(buttons.at(current),4,x);
	}

	connect(midiCallback, SIGNAL(sendMidi(int,int,int,int)), this, SLOT(setSlider(int,int,int,int)));
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
	connect(sendToHardwareAct, SIGNAL(triggered()), this, SLOT(sendToHardware()));

	midiSetupAct = new QAction(tr("&MIDI Setup"));
	connect(midiSetupAct, SIGNAL(triggered()), this, SLOT(midiSetup()));

	quitAct = new QAction(tr("&Quit"), this);
	connect(quitAct, SIGNAL(triggered()), this, SLOT(quit()));

	showMidiConsoleAct = new QAction(tr("&MIDI Console"), this);
	showMidiConsoleAct->setCheckable(true);
	showMidiConsoleAct->setChecked(true);
	connect(showMidiConsoleAct, SIGNAL(toggled(bool)), this, SLOT(showMidiConsole(bool)));

	showMidiChannelAct = new QAction(tr("Display C&hannel"), this);
	showMidiChannelAct->setCheckable(true);
	showMidiChannelAct->setChecked(true);
	connect(showMidiChannelAct, SIGNAL(toggled(bool)), this, SLOT(showMidiChannel(bool)));

	showMidiCCAct = new QAction(tr("Display &CC/Note"), this);
	showMidiCCAct->setCheckable(true);
	showMidiCCAct->setChecked(true);
	connect(showMidiCCAct, SIGNAL(toggled(bool)), this, SLOT(showMidiCC(bool)));

	aboutAct = new QAction(tr("&About"), this);
	connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::setSlider(int type, int channel, int cc, int value)
{
	//Vertical Sliders
	QString channelVal = QString("%1").arg(channel+1,2,10,QChar(' '));
	QString ccVal = QString("%1").arg(cc,3,10,QChar(' '));
	QString valueVal = QString("%1").arg(value,3,10,QChar(' '));

	switch(type){
		case 11: //midi cc
			text_window->appendPlainText("CH: " + channelVal + " CC:   " + ccVal + "    Value: " + valueVal);
		break;
		case 9: //note-on
			text_window->appendPlainText("CH: " + channelVal + " Note: " + ccVal + " ON  Value: " + valueVal);
		break;
		case 8: //note-off
			text_window->appendPlainText("CH: " + channelVal + " Note: " + ccVal + " OFF Value: " + valueVal);
	}
	if (type == 11){
		for (int i = 0; i < sliders.count(); i++){
			if (cc == sliders.at(i)->getCCNumber()) sliders.at(i)->slider->setValue(value);
		}
		//Radial Sliders
		for (int i = 0; i < rsliders.count(); i++){
		if (cc == rsliders.at(i)->getCCNumber()) rsliders.at(i)->r_slider->setValue(value);
		}
	}
	//buttons
	//[TODO] don't worry about implementing this right now


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

	//this is the SysEx message we send to the MIDIMIX in order to receive the current state of the device
	std::vector<unsigned char> message;
	message ={240, //sysex start
			  71,  //akai
			  0x00, //device id, [TODO] will need to change this if multiple devices preset
			  49,
			  0x66, //hex code to ask for hardware state
			  247   //sysex end
			 };

	midiOut->sendMessage(&message);

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
	viewMenu->addAction(showMidiChannelAct);
	viewMenu->addAction(showMidiCCAct);

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
	for (i = 0, j = 7; i < 24; i++, j+=2){
		rsliders.at(i)->setChanNumber(static_cast<int>(message->at(j)));
		rsliders.at(i)->setCCNumber(static_cast<int>(message->at(j+1)));
	}
	for (i = 0, j = 55; i < 9; i++, j+=2){
		sliders.at(i)->setChanNumber(static_cast<int>(message->at(j)));
		sliders.at(i)->setCCNumber(static_cast<int>(message->at(j+1)));
	}
	for (i = 0, j = 73; i < 24; i++, j+=3){
		buttons.at(i)->setChanNumber(static_cast<int>(message->at(j)));
		if (message->at(j+1) == 0){
			buttons.at(i)->setNoteNumber(static_cast<int>(message->at(j+2)));
			buttons.at(i)->setButtonMode(BMode::NOTE);
		} else {
			buttons.at(i)->setCCNumber(static_cast<int>(message->at(j+2)));
			buttons.at(i)->setButtonMode(BMode::CC);
	};
	}
}
void MainWindow::sendToHardware()
{
	qInfo() << "sending to hardware";
	std::vector<unsigned char> messageSetHardware, dialConfig, buttonConfig, sliderConfig, endMessage;
	for (int i = 0; i < 24; i++){
		dialConfig.push_back(static_cast<unsigned char>(rsliders.at(i)->getChanNumber()));
		dialConfig.push_back(static_cast<unsigned char>(rsliders.at(i)->getCCNumber()));
	}

	for (int i = 0; i < 24; i++){
		buttonConfig.push_back(static_cast<unsigned char>(buttons.at(i)->getChanNumber()));
		buttonConfig.push_back(static_cast<unsigned char>(buttons.at(i)->getButtonState()));
		buttonConfig.push_back(static_cast<unsigned char>(buttons.at(i)->getNoteCCNumber()));
	}

	for (int i = 0; i < 9; i++){
		sliderConfig.push_back(static_cast<unsigned char>(sliders.at(i)->getChanNumber()));
		sliderConfig.push_back(static_cast<unsigned char>(sliders.at(i)->getCCNumber()));
	}


	messageSetHardware = {240,
						 71,
						 0x00, //device id [TODO] see above
						 49,
						 100,
						 1,
						 10
						 };
	endMessage = {247};

	messageSetHardware.insert(messageSetHardware.end(), dialConfig.begin(),dialConfig.end());
	messageSetHardware.insert(messageSetHardware.end(), sliderConfig.begin(),sliderConfig.end());
	messageSetHardware.insert(messageSetHardware.end(), buttonConfig.begin(),buttonConfig.end());
	messageSetHardware.insert(messageSetHardware.end(), endMessage.begin(),endMessage.end());

	//for (int i = 0; i < messageSetHardware.size(); i++){
	//	qInfo() << "[OUT MESSAGE]" <<messageSetHardware.at(i);
	//}
	midiOut->sendMessage(&messageSetHardware);
}

void MainWindow::showMidiConsole(bool show)
{
	text_window->setHidden(!show);
}

void MainWindow::showMidiCC(bool show)
{
	for(int i = 0; i < sliders.size(); i++) sliders.at(i)->set_cc_number_visibility(!show);
	for(int i = 0; i < buttons.size(); i++) buttons.at(i)->set_cc_number_visibility(!show);
	for(int i = 0; i < rsliders.size(); i++) rsliders.at(i)->set_cc_number_visibility(!show);
}

void MainWindow::showMidiChannel(bool show)
{
	for(int i = 0; i < sliders.size(); i++) sliders.at(i)->set_channel_number_visibility(!show);
	for(int i = 0; i < buttons.size(); i++) buttons.at(i)->set_channel_number_visibility(!show);
	for(int i = 0; i < rsliders.size(); i++) rsliders.at(i)->set_channel_number_visibility(!show);
}
