#include "about.h"
#include <QLabel>
#include <QVBoxLayout>

About::About(QWidget * parent) :
	QDialog(parent)
{
	setWindowTitle(tr("About MIDImix Editor"));
	QLabel * aboutInfo = new QLabel(this);
	aboutInfo->setText("Copyright 2019 Alexander Waite Mitchell.\n\
						All rights reserved.\n\n\
						Using RtMidi & Qt\n\n\
						This software is free / libre software, GPL3\n\
						The program is provided AS IS with\n\
						NO WARRANTY OF ANY KIND,\n\
						INCLUDING THE WARRANTY OF DESIGN,\n\
						MERCHANTABILITY AND FITNESS FOR\n\
						A PARTICULAR PURPOSE.");
	aboutInfo->setAlignment(Qt::AlignCenter);
	QVBoxLayout * aboutLayout = new QVBoxLayout(this);
	//aboutLayout->setAlignment(Qt::AlignCenter);
	aboutLayout->addWidget(aboutInfo);
	setLayout(aboutLayout);
}
