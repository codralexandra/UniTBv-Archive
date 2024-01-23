#pragma once

#include <QDialog>
#include "ui_costbox.h"
#include "qlineedit.h"
#include "qpushbutton.h"
#include <QVBoxLayout>

class costBox : public QDialog
{
	Q_OBJECT

public:
	costBox(QWidget *parent = nullptr);
	~costBox();

public slots:
	uint32_t getCost();

private:
	Ui::costBoxClass ui;
	QLineEdit* m_lineEdit;
};
