#include "mainwindow.h"

#include "Visitor.h"

#include <QMessageBox>
#include <QSlider>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this); // don't forget to call this;
                     // otherwise your windows will be empty

    ui.ageSlider->setMinimum(Visitor::MinimumAge);
    ui.ageSlider->setMaximum(Visitor::MaximumAge);

    // connects are usually written in the constructor (but depends on use-case)
    connect(ui.ageSlider, SIGNAL(valueChanged(int)), SLOT(onSliderValueChanged())); // old syntax, but clear function selection

    ui.selectedAgeLabel->setText(QString::number(Visitor::MinimumAge));

    connect(ui.addButton, SIGNAL(clicked()), SLOT(onAddButtonClicked()));
    connect(ui.deleteButton, SIGNAL(clicked()), SLOT(onDeleteSelectedButtonClicked()));
}

void MainWindow::onSliderValueChanged()
{
    ui.selectedAgeLabel->setText(QString::number(ui.ageSlider->value()));
}

void MainWindow::onAddButtonClicked()
{
    if (ui.nameLineEdit->text().isEmpty())
    {
        QMessageBox::critical(this, "Can't save", "The visitor name is not filled in.", QMessageBox::Button::Ok); // modal window
        return;
    }
    
    Visitor visitor(ui.nameLineEdit->text().toStdString(), ui.hasPetsCheckbox->isChecked(), ui.ageSlider->value());
    ui.visitorsListWidget->addItem(QString::fromStdString(visitor.toString()));
}

void MainWindow::onDeleteSelectedButtonClicked()
{
    const auto selectedIndexes = ui.visitorsListWidget->selectionModel()->selectedIndexes();
    if (selectedIndexes.isEmpty())
    {
        QMessageBox::critical(this, "Can't delete", "You haven't selected any item in the list.", QMessageBox::Button::Ok);
        return;
    }
    
    ui.visitorsListWidget->model()->removeRow(selectedIndexes.first().row());
}

