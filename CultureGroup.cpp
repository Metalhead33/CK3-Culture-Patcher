#include "CultureGroup.hpp"

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

void CultureGroup::fromStream(QTextStream &stream)
{
	QString lastLine;
	State state = EXPECTING_GROUP_NAME;
	QString lastCulture;
	int innerBrackets = 1;

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
			if(lastLine.contains(QStringLiteral("= {"))) {
				if(!lastLine.contains(QStringLiteral("graphical_cultures")) && !lastLine.contains(QStringLiteral("mercenary_names"))) {
					QString firstSample;
					QTextStream(&lastLine,QFile::ReadOnly) >> firstSample;
					state = EXPECTING_CULTURE_DATA;
					cultures[firstSample] = Culture();
					lastCulture = firstSample;
					innerBrackets = 1;
				} else {
					lastLine.append(QChar('\n'));
					groupMisc.append(lastLine);
				}
			} else {
				if(lastLine.length() > 1) {
				lastLine.append(QChar('\n'));
				groupMisc.append(lastLine);
				}
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
}

void CultureGroup::toStream(QTextStream &stream)
{
	stream << cultureGrpName << " = {\n";
	stream << groupMisc << "\n";
	for (auto it = std::begin(cultures); it != std::end(cultures); ++it) {
		stream << "\t" << it.key() << "= {\n";
		it.value().toStream(stream);
		stream << "\t}\n";
	}
	stream << "}\n";
}

void CultureGroup::replacePhenotypes(const QDir &phenoDir)
{
	for (auto it = std::begin(cultures); it != std::end(cultures); ++it) {
		QFile file(QStringLiteral("%1.txt").arg(it.key()));
		file.open(QFile::ReadOnly | QFile::Text);
		QTextStream stream(&file);
		it->replacePhenotypes(stream);
		file.close();
	}
}

void Culture::toStream(QTextStream &stream)
{
	stream << miscStr << '\n';
	stream << "\t\tethnicities = {\n";
	for (auto it = std::begin(phenotypes); it != std::end(phenotypes) ; ++it) {
		stream << "\t\t\t" << it->second << " = " << it->first << "\n";
	}
	stream << "\t\t}\n";
}

void Culture::replacePhenotypes(QTextStream &stream)
{
	phenotypes.clear();
	QString lastLine;
	while(stream.readLineInto(&lastLine)) {
		lastLine = lastLine.trimmed();
		lastLine = lastLine.replace(QStringLiteral(" = "),QStringLiteral("\t"));
		QStringList splitstr = lastLine.split(QChar('\t'));
		if(splitstr.size() == 2) {
			phenotypes.append(QPair<QString,int>(splitstr[1],splitstr[0].toInt()));
		}
	}
}
