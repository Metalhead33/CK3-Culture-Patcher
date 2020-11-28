#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "CultureGroup.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:

	void on_loadRegular_clicked();

	void on_saveRegular_clicked();

	void on_loadJson_clicked();

	void on_saveJson_clicked();

private:
	Ui::MainWindow *ui;
	CultureGroup group;
};
#endif // MAINWINDOW_HPP
