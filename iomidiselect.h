#pragma once

#include <QObject>
#include <QWidget>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>

class MainWindow;

class IOMidiSelect : public QWidget
{
	Q_OBJECT
public:
	explicit IOMidiSelect(QWidget *parent = nullptr);
	QComboBox * MIDI_in;
	QComboBox * MIDI_out;
private:
	QLabel * MIDI_in_label;
	QLabel * MIDI_out_label;
	QHBoxLayout * IO_MIDI_layout;

signals:

public slots:
};
