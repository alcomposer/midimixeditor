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
#include <QDial>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>

class RSlider : public QWidget
{
	Q_OBJECT
public:
	explicit RSlider(QWidget *parent = nullptr);
	QDial * r_slider;
	int getChanNumber();
	int getCCNumber();
	void set_cc_number_visibility(bool show);
	void set_channel_number_visibility(bool show);
private:
	QVBoxLayout * r_slider_layout;
	QSpinBox * chan_number;
	QSpinBox * cc_number;
	QLabel * cc_label;
	QLabel * chan_label;
signals:

public slots:
	void setChanNumber(int);
	void setCCNumber(int);
};
