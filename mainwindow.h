#pragma once

#include <QMainWindow>
#include <QDial>
#include <QPushButton>
#include <QDebug>
#include <QPlainTextEdit>
#include <QMenu>

#include "rtmidi/RtMidi.h"
#include "mycallback.h"
#include "iomididialog.h"
#include "rslider.h"
#include "slider.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
	QPlainTextEdit * text_window;

	QString * app_name;

	QMenu *fileMenu;
	QAction* newAct;
	QAction* openPresetAct;
	QAction* saveAct;
	QAction* saveAsAct;
	QAction* loadFromHardwareAct;
	QAction* sendToHardwareAct;
	QAction* midiSetupAct;
	QAction* quitAct;

	QMenu* viewMenu;
	QAction* showMidiConsoleAct;

	QMenu* helpMenu;
	QAction* aboutAct;

	RtMidiIn * midiIn;
	RtMidiOut * midiOut;
private:
	void createActions();
	void createMenues();

	QVector<Slider*> sliders;
	QVector<RSlider*> rsliders;
	QVector<QPushButton*> buttons;
	void setMidiValue();
	myCallback * midiCallback;
	QVector<unsigned int> button_state;
	IOMidiDialog * midi_io_dialog;
	unsigned int currentInPort;
	unsigned int currentOutPort;

	QString workingFile = "";
	QString workingFileNew = "";


private slots:
	void setSlider(int, int, int);

	void newPreset();
	void openPreset();
	void save();
	void saveAs();
	void loadFromHardware();
	void sendToHardware();
	void midiSetup();
	void quit();
	void about();

	void setSysEx(std::vector<unsigned char>*);
public slots:
	void setMidiInPort(const int);
	void setMidiOutPort(const int);
	void showMidiConsole(bool);
};
