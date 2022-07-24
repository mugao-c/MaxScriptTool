#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Configer.h"
#include "App3dsMaxMgr.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QStandardPaths>
#include "LogMacro.h"

DECLARE_LOG_CATEGORY(LogMain)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::appNotInstalled()
{

}
