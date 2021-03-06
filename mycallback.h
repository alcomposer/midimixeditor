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

class myCallback : public QWidget
{
	Q_OBJECT
public:
	static void staticCallback(double deltatime, std::vector<unsigned char> *message, void *userData);
	void Callback(double deltatime, std::vector<unsigned char> *message, void *userData);
signals:
	void sendMidi(int, int, int, int);
	void sendSysEx(std::vector<unsigned char> *message);
};
