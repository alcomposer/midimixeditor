#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSlider>
#include <QDial>
#include <QPushButton>
#include "rtmidi/RtMidi.h"
#include <QDebug>
#include "mycallback.h"
#include <QPlainTextEdit>
#include <QMenu>
#include "iomididialog.h"

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

	RtMidiIn * midiIn;
	RtMidiOut * midiOut;
private:
	void createActions();
	void createMenues();

	QVector<QSlider*> sliders;
	QVector<QDial*> rsliders;
	QVector<QPushButton*> buttons;
	void setMidiValue();
	myCallback * midiCallback;
	QVector<unsigned int> button_state;
	IOMidiDialog * midi_io_dialog;
	unsigned int currentInPort;
	unsigned int currentOutPort;

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
public slots:
	void setMidiInPort(const int);
	void setMidiOutPort(const int);
};


#endif // MAINWINDOW_H
