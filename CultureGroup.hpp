#ifndef CULTUREGROUP_HPP
#define CULTUREGROUP_HPP
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QList>
#include <QDir>

struct Culture {
	QString miscStr;
	QList<QPair<QString,int>> phenotypes;

	void toStream(QTextStream& stream);
	void replacePhenotypes(QTextStream& stream);
};

struct CultureGroup {
	QString cultureGrpName;
	QString groupMisc;
	QHash<QString,Culture> cultures;

	void fromStream(QTextStream& stream);
	void toStream(QTextStream& stream);
	void replacePhenotypes(const QDir& phenoDir);
};

#endif // CULTUREGROUP_HPP
