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
#include <QDialog>
#include "iomidiselect.h"

class IOMidiDialog : public QDialog
{
	Q_OBJECT
public:
	IOMidiDialog(QWidget* parent = nullptr);
	void setPortLists(int currentInPort, QVector<QString> inPorts, int currentOutPort, QVector<QString> outPorts);
private:
	IOMidiSelect * selectMIDI;
};
