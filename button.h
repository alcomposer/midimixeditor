#pragma once

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QLabel>

namespace BMode{
	enum buttonMode{CC,NOTE};
}

class Button : public QWidget
{
	Q_OBJECT
public:
	explicit Button(QWidget *parent = nullptr);
	QPushButton * button;
	void update_display();
	void setButtonMode(BMode::buttonMode mode);
	void setChanNumber(int);
	void setCCNumber(int);
	void setNoteNumber(int);
	void set_channel_number_visibility(bool show);
	void set_cc_number_visibility(bool show);

	int getChanNumber();
	int getButtonState();
	int getNoteCCNumber();

private:
	bool button_mode;
	bool cc_midi_visability;
	QLabel * button_text;

	QVBoxLayout * button_layout;
	QSpinBox * note_number;
	QSpinBox * chan_number;
	QSpinBox * cc_number;
	QLabel * cc_label;
	QLabel * note_label;
	QLabel * chan_label;

	QWidget * note_number_wid;
	QWidget * chan_number_wid;
	QWidget * cc_number_wid;

signals:

public slots:
	void set_button_text();
};
