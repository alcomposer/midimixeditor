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
#include <QSlider>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QSlider>
#include <QLabel>

class Slider : public QWidget
{
	Q_OBJECT
public:
	Slider(QWidget * parent = nullptr);
	QSlider * slider;
	int getChanNumber();
	int getCCNumber();
	void set_cc_number_visibility(bool);
	void set_channel_number_visibility(bool);
private:
	QVBoxLayout * slider_layout;
	QSpinBox * chan_number;
	QSpinBox * cc_number;
	QLabel * chan_label;
	QLabel * cc_label;
public slots:
	void setChanNumber(int);
	void setCCNumber(int);
};
