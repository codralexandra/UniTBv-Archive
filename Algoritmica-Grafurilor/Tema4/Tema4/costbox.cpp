#include "costbox.h"

costBox::costBox(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("Input Cost");

    m_lineEdit = new QLineEdit(this);
    m_lineEdit->setPlaceholderText("Insert arch cost...");

    QPushButton* okButton = new QPushButton("OK", this);
    connect(okButton, &QPushButton::clicked, this, &costBox::accept);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(m_lineEdit);
    layout->addWidget(okButton);

    setLayout(layout);
}

costBox::~costBox()
{
    /* EMPTY */
}

uint32_t costBox::getCost()
{
    return m_lineEdit->text().toUInt();
}
