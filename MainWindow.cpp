#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QJsonValue>
#include <QJsonDocument>
#include <QCborValue>

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

void MainWindow::on_loadRegular_clicked()
{
	group = CultureGroup();
	QString path = QFileDialog::getOpenFileName(this,tr("Open CK3 culture group file"),QString(),tr("Text files (*.txt)"));
	if(path.isEmpty()) return;
	QFile file(path);
	if(!file.open(QFile::ReadOnly | QFile::Text)) {
		QMessageBox::critical(this,tr("Error!"),tr("Failed to open the file \"%1\" for reading!").arg(path));
		return;
	}
	QTextStream stream(&file);
	stream.setCodec("UTF-8");
	stream >> group;
	file.close();
}

void MainWindow::on_saveRegular_clicked()
{
	QString path = QFileDialog::getSaveFileName(this,tr("Save CK3 culture group file"),QString(),tr("Text files (*.txt)"));
	if(path.isEmpty()) return;
	QFile file(path);
	if(!file.open(QFile::WriteOnly | QFile::Text)) {
		QMessageBox::critical(this,tr("Error!"),tr("Failed to open the file \"%1\" for writing!").arg(path));
		return;
	}
	QTextStream stream(&file);
	stream.setCodec("UTF-8");
	stream.setGenerateByteOrderMark(true);
	stream << group;
	file.close();
}

void MainWindow::on_loadJson_clicked()
{
	group = CultureGroup();
	QString path = QFileDialog::getOpenFileName(this,tr("Open JSON / CBOR"),QString(),tr("JSON and CBOR files (*.json *cbor)"));
	if(path.isEmpty()) return;
	QFile file(path);
	if(!file.open(QFile::ReadOnly)) {
		QMessageBox::critical(this,tr("Error!"),tr("Failed to open the file \"%1\" for reading!").arg(path));
		return;
	}
	if(path.endsWith(QStringLiteral("json")) || path.endsWith(QStringLiteral("JSON"))) {
		group.fromJson(QJsonDocument::fromJson(file.readAll()).object());
	} else if(path.endsWith(QStringLiteral("cbor")) || path.endsWith(QStringLiteral("CBOR"))) {
		group.fromCbor(QCborValue::fromCbor(file.readAll()).toMap());
	}
	file.close();
}

void MainWindow::on_saveJson_clicked()
{
	QString path = QFileDialog::getSaveFileName(this,tr("Save JSON / CBOR"),QString(),tr("JSON and CBOR files (*.json *cbor)"));
	if(path.isEmpty()) return;
	QFile file(path);
	if(!file.open(QFile::WriteOnly)) {
		QMessageBox::critical(this,tr("Error!"),tr("Failed to open the file \"%1\" for writing!").arg(path));
		return;
	}
	if(path.endsWith(QStringLiteral("json")) || path.endsWith(QStringLiteral("JSON"))) {
		QJsonDocument doc(group.toJson());
		file.write(doc.toJson());
	} else if(path.endsWith(QStringLiteral("cbor")) || path.endsWith(QStringLiteral("CBOR"))) {
		file.write(QCborValue(group.toCbor()).toCbor());
	}
	file.close();
}
