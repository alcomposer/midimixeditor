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

#include "about.h"
#include <QLabel>
#include <QVBoxLayout>

About::About(QWidget * parent) :
	QDialog(parent)
{
	setWindowTitle(tr("About MIDImix Editor"));
	QVBoxLayout * aboutLayout = new QVBoxLayout(this);

	QLabel * midimixImage = new QLabel();
	QPixmap midimixIcon(":icons/midimixedit.png");
	midimixIcon = midimixIcon.scaledToWidth(128,Qt::SmoothTransformation);
	midimixImage->setPixmap(midimixIcon);
	midimixImage->setAlignment(Qt::AlignCenter);
	aboutLayout->addWidget(midimixImage);


	QLabel * aboutInfo = new QLabel();
	aboutInfo->setText(QString("Copyright 2019 Alexander Waite Mitchell.\n") +
						QString("All rights reserved.\n\n") +
						QString("Using RtMidi & Qt\n\n")+
						QString("This software is free / libre software, GPL3\n")+
						QString("The program is provided AS IS with\n")+
						QString("NO WARRANTY OF ANY KIND,\n") +
						QString("INCLUDING THE WARRANTY OF DESIGN,\n") +
						QString("MERCHANTABILITY AND FITNESS FOR\n") +
						QString("A PARTICULAR PURPOSE."));
	aboutInfo->setAlignment(Qt::AlignCenter);

	aboutLayout->addWidget(aboutInfo);
	//setFixedSize(aboutInfo->sizeHint());
	setLayout(aboutLayout);
}
