#ifndef IOMIDIDIALOG_H
#define IOMIDIDIALOG_H

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

#endif // IOMIDIDIALOG_H
