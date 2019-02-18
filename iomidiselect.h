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
