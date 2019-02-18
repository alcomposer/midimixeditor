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

#include "mycallback.h"

#include <QDebug>

void
myCallback::staticCallback(double deltatime,
				std::vector<unsigned char> *message,
				void *userData)
{
static_cast<myCallback *>(userData)->Callback(deltatime, message, userData);
}

void
myCallback::Callback(double deltatime,
						   std::vector<unsigned char> *message,
						  void *userData)
{
	int type = static_cast<int>(message->at(0));
	int type_res = type >> 4;
	int channel = static_cast<int>(message->at(0));
	int chan_res = channel & 0x0f;
	int cc = static_cast<int>(message->at(1));
	int value = static_cast<int>(message->at(2));

	if (static_cast<int>(message->at(0))==240){
		emit sendSysEx(message);
	} else {
		emit sendMidi(type_res, chan_res, cc, value);
	}
}
