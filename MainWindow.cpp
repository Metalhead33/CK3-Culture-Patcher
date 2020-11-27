#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "CultureGroup.hpp"

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


void MainWindow::on_pushButton_clicked()
{
	QString str1 = ui->plainTextEdit->toPlainText();
	if(str1.isEmpty()) return;
	if(!str1.contains(QChar('}'))) return;
	QString str2;
	QTextStream streamIn(&str1,QIODevice::ReadOnly);
	QTextStream streamOut(&str2,QIODevice::WriteOnly);
	CultureGroup cult;
	streamIn >> cult;
	streamOut << cult;
	ui->plainTextEdit->setPlainText(str2);
}
