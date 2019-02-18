/*
This file is part of MIDI MIX EDIT.

MIDI MIX EDIT is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

MIDI MIX EDIT is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar.  If not, see <https://www.gnu.org/licenses/>.
*/

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
