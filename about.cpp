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
