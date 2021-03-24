#include <QApplication>
#include <QFile>
#include <QDir>
#include <QDirIterator>
#include <QFileDialog>
#include <QFileInfo>
#include <iostream>
#include <QTextCodec>
#include "CultureGroup.hpp"

void processCultures(const QDir& dirOut, QDirIterator& dirIn, const QString& replacementDir = QString());

int main(int argc, char *argv[])
{
	if(argc >= 4) {
		QDirIterator dirIn(QString::fromUtf8(argv[1]) ,{"*.txt"},QDir::Files);
		QDir dirOut(QString::fromUtf8(argv[2]));
		QDir replacementDir(QString::fromUtf8(argv[3]));
		processCultures(dirOut,dirIn);
		return 0;
	}
	if(argc == 3) {
		QDirIterator dirIn(QString::fromUtf8(argv[1]) ,{"*.txt"},QDir::Files);
		QDir dirOut(QString::fromUtf8(argv[2]));
		processCultures(dirOut,dirIn);
		return 0;
	} else {
		QApplication a(argc,argv);
		QString dir1 = QFileDialog::getExistingDirectory(nullptr,QStringLiteral("Open culture directory!"));
		if(dir1.isEmpty()) a.exit();
		QString dir2 = QFileDialog::getExistingDirectory(nullptr,QStringLiteral("Open output directory!"));
		if(dir2.isEmpty()) a.exit();
		QString dir3 = QFileDialog::getExistingDirectory(nullptr,QStringLiteral("Open directory for phenotype replacements!"));
		QDirIterator dirIn(dir1,{"*.txt"},QDir::Files);
		QDir dirOut(dir2);
		processCultures(dirOut,dirIn);
		return a.exec();
	}
}
void processCultures(const QDir& dirOut, QDirIterator& dirIn, const QString& replacementDir) {
	while(dirIn.hasNext()) {
		QString path = dirIn.next();
		QFileInfo info(path);
		QFile file(path);
		file.open(QFile::ReadOnly | QFile::Text);
		QTextStream stream1(&file);
		CultureGroup group;
		group.fromStream(stream1);
		file.close();;
		if(!replacementDir.isEmpty()) {
			group.replacePhenotypes(QDir(replacementDir));
		}
		QFile file2(dirOut.absoluteFilePath(info.fileName() )  );
		file2.open(QFile::WriteOnly | QFile::Text);
		QTextStream stream2(&file2);
		stream2.setCodec(QTextCodec::codecForName("UTF-8"));
		stream2.setGenerateByteOrderMark(true);
		group.toStream(stream2);
		file2.close();;
	}
}
