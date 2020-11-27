#include "CultureGroup.hpp"

CultureGroup::CultureGroup()
{

}

enum class CultureGroupParseStates {
	DONE,
	EXPECTING_ENTRY, // After a }
	GRAPHICAL_CULTURES_ENTRY, // graphical_cultures
	GRAPHICAL_CULTURES_EQUAL, // =
	GRAPHICAL_CULTURES_START, // {
	MERCENARY_ENTRY, // mercenary_names
	MERCENARY_EQUAL, // =
	MERCENARY_START, // {
	MERCENARY_ENTRY_START, // {
	MERCENARY_ENTRY_NAME, // name
	MERCENARY_ENTRY_EQUAL, // =
	MERCENARY_ENTRY_STR, // <string>
	CULTURE_ENTRY, // <string>
	CULTURE_EQUAL, // =
	CULTURE_START, // {
};

void CultureGroup::load(QTextStream &stream)
{
	CultureGroupParseStates state = CultureGroupParseStates::EXPECTING_ENTRY;
	QString tmpStr;
	QStringList tmpList;
	stream >> name;
	stream >> tmpStr;
	stream >> tmpStr;
	tmpStr.clear();
	while(state != CultureGroupParseStates::DONE) {
		QString curStr;
		stream >> curStr;
		if(curStr.isEmpty()) return;
		if(curStr.startsWith(QChar('#'))) {
			stream.readLine();
			stream >> curStr;
		}
		switch (state) {
		case CultureGroupParseStates::EXPECTING_ENTRY:
			if(!curStr.compare(QStringLiteral("}"))) {
				state = CultureGroupParseStates::DONE;
			} else if(!curStr.compare(QStringLiteral("graphical_cultures"))) {
				state = CultureGroupParseStates::GRAPHICAL_CULTURES_ENTRY;
			} else if(!curStr.compare(QStringLiteral("mercenary_names"))) {
				state = CultureGroupParseStates::MERCENARY_ENTRY;
			} else if(!curStr.compare(QStringLiteral("}"))) {
				state = CultureGroupParseStates::DONE;
			} else {
				tmpStr = curStr;
				state = CultureGroupParseStates::CULTURE_ENTRY;
			} break;
		case CultureGroupParseStates::CULTURE_ENTRY:
			if(!curStr.compare(QStringLiteral("="))) {
				state = CultureGroupParseStates::CULTURE_EQUAL;
			} break;
		case CultureGroupParseStates::CULTURE_EQUAL:
			if(!curStr.compare(QStringLiteral("{"))) {
				state = CultureGroupParseStates::CULTURE_START;
				Culture tmpCul;
				stream >> tmpCul;
				cultures.insert(tmpStr,tmpCul);
				tmpStr.clear();
				state = CultureGroupParseStates::EXPECTING_ENTRY;
			} break;
		case CultureGroupParseStates::MERCENARY_ENTRY:
			if(!curStr.compare(QStringLiteral("="))) {
				state = CultureGroupParseStates::MERCENARY_EQUAL;
			} break;
		case CultureGroupParseStates::MERCENARY_EQUAL:
			if(!curStr.compare(QStringLiteral("{"))) {
				state = CultureGroupParseStates::MERCENARY_START;
			} break;
		case CultureGroupParseStates::GRAPHICAL_CULTURES_ENTRY:
			if(!curStr.compare(QStringLiteral("="))) {
				state = CultureGroupParseStates::GRAPHICAL_CULTURES_EQUAL;
			} break;
		case CultureGroupParseStates::GRAPHICAL_CULTURES_EQUAL:
			if(!curStr.compare(QStringLiteral("{"))) {
				state = CultureGroupParseStates::GRAPHICAL_CULTURES_START;
			} break;
		case CultureGroupParseStates::GRAPHICAL_CULTURES_START:
			if(!curStr.compare(QStringLiteral("}"))) {
				state = CultureGroupParseStates::EXPECTING_ENTRY;
			} else {
				graphical_cultures.append(curStr);
			} break;
		case CultureGroupParseStates::MERCENARY_START:
			if(!curStr.compare(QStringLiteral("}"))) {
				state = CultureGroupParseStates::EXPECTING_ENTRY;
			} else {
				state = CultureGroupParseStates::MERCENARY_ENTRY_START;
			}
			break;
		case CultureGroupParseStates::MERCENARY_ENTRY_START:
			state = CultureGroupParseStates::MERCENARY_ENTRY_NAME;
			break;
		case CultureGroupParseStates::MERCENARY_ENTRY_NAME:
			if(!curStr.compare(QStringLiteral("="))) {
				state = CultureGroupParseStates::MERCENARY_ENTRY_EQUAL;
			}
			break;
		case CultureGroupParseStates::MERCENARY_ENTRY_EQUAL:
			curStr.remove(QChar('\"'));
			mercenary_names.append(curStr);
			state = CultureGroupParseStates::MERCENARY_ENTRY_STR;
			break;
		case CultureGroupParseStates::MERCENARY_ENTRY_STR:
			state = CultureGroupParseStates::MERCENARY_START;
			break;
		default:
			break;
		}
	}
}

void CultureGroup::save(QTextStream &stream) const
{
	if(!name.isEmpty()) stream << name << QStringLiteral(" = {\n");
	if(!graphical_cultures.isEmpty()) {
		stream << QStringLiteral("\tgraphical_cultures = {\n");
		for(const auto& it : graphical_cultures) {
			stream << QStringLiteral("\t\t") << it << '\n';
		}
		stream << QStringLiteral("\t}\n");
	}
	// Mercenaries
	if(!mercenary_names.isEmpty()) {
		stream << QStringLiteral("\tmercenary_names = {\n");
		for(const auto& it : mercenary_names) {
			stream << QStringLiteral("\t\t{ name = \"%1\" }").arg(it) << '\n';
		}
		stream << QStringLiteral("\t}\n");
	}
	// Cultures
	if(!cultures.isEmpty()) {
		for(auto it = std::begin(cultures); it != std::end(cultures); ++it) {
			stream << QChar('\t') << it.key() << QStringLiteral(" = {\n") << it.value() << QStringLiteral("\n\t}\n");
		}
	}
	if(!name.isEmpty()) stream << QChar('}');
}

QTextStream &operator<<(QTextStream &stream, const CultureGroup &culture)
{
	culture.save(stream);
	return stream;
}

QTextStream &operator>>(QTextStream &stream, CultureGroup &culture)
{
	culture.load(stream);
	return stream;
}
