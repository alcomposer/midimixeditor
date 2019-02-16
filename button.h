#pragma once

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSpinBox>

namespace BMode{
	enum buttonMode{CC,NOTE};
}

class Button : public QWidget
{
	Q_OBJECT
public:
	explicit Button(QWidget *parent = nullptr);
	QPushButton * button;
private:
	bool * button_mode;

	QVBoxLayout * button_layout;
	QSpinBox * note_number;
	QSpinBox * chan_number;
	QSpinBox * cc_number;

signals:

public slots:
};
