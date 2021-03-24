#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <QList>

struct CultureData {
	QString miscStr;
	QList<QPair<QString,int>> phenotypes;
};

enum State {
	EXPECTING_GROUP_NAME,
	EXPECTING_CULTURE_NAME,
	EXPECTING_CULTURE_DATA,
	EXPECTING_PHENOTYPE_DATA
};

int countBrackets(const QString& str) {
	int brackets=0;
	for(const auto& it : str) {
		if( it == QChar('{')) ++brackets;
		else if( it == QChar('}')) --brackets;
	}
	return brackets;
}

int main(int argc, char *argv[])
{
	QString lastLine;
	State state = EXPECTING_GROUP_NAME;
	QString cultureGrpName;
	QString groupMisc;
	QString lastCulture;
	QHash<QString,CultureData> cultures;
	int innerBrackets = 1;

	int bracketsOpen = 0;
	bool keepGoing = true;

	QFile file("/home/metalhead33/NewFolder/CK3-Human-Phenotype-Project/common/culture/cultures/00_balto_finnic.txt");
	file.open(QFile::ReadOnly);
	QTextStream stream(&file);
	while(stream.readLineInto(&lastLine)) {
		switch (state) {
		case EXPECTING_GROUP_NAME:
		{
			QTextStream(&lastLine,QFile::ReadOnly) >> cultureGrpName;
			state = EXPECTING_CULTURE_NAME;
			break;
		}
		case EXPECTING_CULTURE_NAME:
		{
			if(lastLine.endsWith(QStringLiteral("= {"))) {
				QString firstSample;
				QTextStream(&lastLine,QFile::ReadOnly) >> firstSample;
			if(!firstSample.contains(QStringLiteral("graphical_cultures")) && !firstSample.contains(QStringLiteral("mercenary_names"))) {
				state = EXPECTING_CULTURE_DATA;
				cultures[firstSample] = CultureData();
				lastCulture = firstSample;
				innerBrackets = 1;
			} else {
				lastLine.append(QChar('\n'));
				groupMisc.append(lastLine);
			}
			} else {
				lastLine.append(QChar('\n'));
				groupMisc.append(lastLine);
			}
			break;
		}
		case EXPECTING_CULTURE_DATA: {
			innerBrackets += countBrackets(lastLine);
			if(innerBrackets <= 0) state = EXPECTING_CULTURE_NAME;
			else if( lastLine.contains(QStringLiteral("ethnicities"))) state = EXPECTING_PHENOTYPE_DATA;
			else {
			lastLine.append(QChar('\n'));
			cultures[lastCulture].miscStr.append(lastLine);
			}
			break;
		}
		case EXPECTING_PHENOTYPE_DATA: {
			lastLine = lastLine.trimmed();
			lastLine = lastLine.replace(QStringLiteral(" = "),QStringLiteral("\t"));
			if(lastLine.contains(QChar('}')) ) { state = EXPECTING_CULTURE_DATA; --innerBrackets; }
			else {
				QStringList splitstr = lastLine.split(QChar('\t'));
				if(splitstr.size() == 2) {
					cultures[lastCulture].phenotypes.append(QPair<QString,int>(splitstr[1],splitstr[0].toInt()));
				}
			}
			break;
		}
		default:
			break;
		}
	}
	std::cout << "Culture group name: " << cultureGrpName.toStdString() << std::endl;
	for (auto it = std::begin(cultures); it != std::end(cultures); ++it) {
		std::cout << "Culture name: " << it.key().toStdString() << std::endl;
		std::cout << "Phenotypes: " << std::endl;
		for (auto zit = std::begin(it->phenotypes); zit != std::end(it->phenotypes) ; ++zit) {
			std::cout << "\t" << zit->first.toStdString() << " - " << zit->second << std::endl;
		}
	}
	return 0;
}
