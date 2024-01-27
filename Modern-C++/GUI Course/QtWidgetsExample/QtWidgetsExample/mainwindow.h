#pragma once

#include <QtWidgets/QMainWindow>

#include "ui_mainwindow.h" // this include can give an error in the IDE; you can ignore it
#include <QStringListModel>

//class VisitorModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT // necessary in order to use signals and slots in a class
            // also the class needs to be a direct/indirect child of QObject

public:
    MainWindow(QWidget *parent = Q_NULLPTR); // parent is specified in order to create a tree of widgets
                                             // and to free memory properly
private:
    Ui::MainWindowClass ui; // generated ui after parsing the .ui file;
                            // as you can see, it can be a simple object; doesn't have to be a pointer

private slots:
    void onSliderValueChanged();
    void onAddButtonClicked();
    void onDeleteSelectedButtonClicked();
};
