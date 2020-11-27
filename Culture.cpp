#include "Culture.hpp"
#include <QList>
#include <QPair>
#include <QtGlobal>

typedef QPair<QString,int> NamedNumber;

bool isGreater(const NamedNumber& a, const NamedNumber& b) {
	return a.second > b.second;
}

Culture::Culture()
{

}

enum class CultureParseStates {
	DONE,
	EXPECTING_ENTRY, // After a }
	GRAPHICAL_CULTURES_ENTRY, // graphical_cultures
	GRAPHICAL_CULTURES_EQUAL, // =
	GRAPHICAL_CULTURES_START, // {
	COLOR_ENTRY, // color
	COLOR_EQUAL, // =
	COLOR_RGBF, // {
	COLOR_RGBI, // rgb{
	COLOR_HSVF, // hsv{
	COLOR_HSV360, // hsv360{
	COLOR_N_RGBI, // rgb
	COLOR_N_HSVF, // hsv
	COLOR_N_HSV360, // hsv360
	CADET_DYNASTY_ENTRY, // cadet_dynasty_names
	CADET_DYNASTY_EQUAL, // =
	CADET_DYNASTY_START, // {
	CADET_DYNASTY_EXTRA, // {
	DYNASTY_ENTRY, // dynasty_names
	DYNASTY_EQUAL, // =
	DYNASTY_START, // {
	DYNASTY_EXTRA, // {
	MALE_ENTRY, // male_names
	MALE_EQUAL, // =
	MALE_START, // {
	FEMALE_ENTRY, // female_names
	FEMALE_EQUAL, // =
	FEMALE_START, // {
	LOCATION_PREFIX_ENTRY, // dynasty_of_location_prefix
	LOCATION_PREFIX_EQUAL, // =
	MALE_PATRONYM_SUFFIX_ENTRY, // patronym_suffix_male
	MALE_PATRONYM_SUFFIX_EQUAL, // =
	FEMALE_PATRONYM_SUFFIX_ENTRY, // patronym_suffix_female
	FEMALE_PATRONYM_SUFFIX_EQUAL, // =
	MALE_PATRONYM_PREFIX_ENTRY, // patronym_prefix_male
	MALE_PATRONYM_PREFIX_EQUAL, // =
	FEMALE_PATRONYM_PREFIX_ENTRY, // patronym_prefix_female
	FEMALE_PATRONYM_PREFIX_EQUAL, // =
	MALE_PATRONYM_PREFIX_V_ENTRY, // patronym_prefix_male_vowel
	MALE_PATRONYM_PREFIX_V_EQUAL, // =
	FEMALE_PATRONYM_PREFIX_V_ENTRY, // patronym_prefix_female_vowel
	FEMALE_PATRONYM_PREFIX_V_EQUAL, // =
	DYNNAME_FIRST_ENTRY, // dynasty_name_first
	DYNNAME_FIRST_EQUAL, // =
	FOUNDER_NAME_ENTRY, // founder_named_dynasties
	FOUNDER_NAME_EQUAL, // =
	ETHNICITIES_ENTRY, // ethnicities
	ETHNICITIES_EQUAL, // =
	ETHNICITIES_START, // {
	ETHNICITIES_NUMBER, // <int>
	ETHNICITIES_NAME, // <string>
	ETHNICITIES_MAP, // =
	DYNASTY_TITLE_ENTRY, // dynasty_title_names
	DYNASTY_TITLE_EQUAL, // =
	MERCENARY_ENTRY, // mercenary_names
	MERCENARY_EQUAL, // =
	MERCENARY_START, // {
	MERCENARY_ENTRY_START, // {
	MERCENARY_ENTRY_NAME, // name
	MERCENARY_ENTRY_EQUAL, // =
	MERCENARY_ENTRY_STR, // <string>
	PAT_GRF_NAME_CHANCE_ENTRY, // pat_grf_name_chance
	MAT_GRF_NAME_CHANCE_ENTRY, // mat_grf_name_chance
	FATHER_NAME_CHANCE_ENTRY, // father_name_chance
	PAT_GRM_NAME_CHANCE_ENTRY, // pat_grm_name_chance
	MAT_GRM_NAME_CHANCE_ENTRY, // mat_grm_name_chance
	MOTHER_NAME_CHANCE_ENTRY, // mother_name_chance
	PAT_GRF_NAME_CHANCE_EQUAL,
	MAT_GRF_NAME_CHANCE_EQUAL,
	FATHER_NAME_CHANCE_EQUAL,
	PAT_GRM_NAME_CHANCE_EQUAL,
	MAT_GRM_NAME_CHANCE_EQUAL,
	MOTHER_NAME_CHANCE_EQUAL,
	GRAMMAR_TRANSFORM_ENTRY,
	GRAMMAR_TRANSFORM_EQUAL,
	BASTARD_DYNASTY_ENTRY,
	BASTARD_DYNASTY_EQUAL,
	ALWAYS_PATRONYM_ENTRY,
	ALWAYS_PATRONYM_EQUAL,
	CHARMOD_ENTRY, // character_modifier
	CHARMOD_EQUAL, // =
	CHARMOD_START, // {
	CHARMOD_KEY, // <string>
	CHARMOD_MAP, // =
	CHARMOD_VALUE, // <variant>
};

void Culture::load(QTextStream &stream)
{
	CultureParseStates state = CultureParseStates::EXPECTING_ENTRY;
	QString tmpStr;
	QStringList tmpList;
	int tmpInt = 0;
	while(state != CultureParseStates::DONE) {
		QString curStr;
		stream >> curStr;
		if(curStr.isEmpty()) return;
		if(curStr.startsWith(QChar('#'))) {
			stream.readLine();
			stream >> curStr;
		}
		switch (state) {
		case CultureParseStates::EXPECTING_ENTRY:
			if(!curStr.compare(QStringLiteral("}"))) {
				state = CultureParseStates::DONE;
			} else if(!curStr.compare(QStringLiteral("graphical_cultures"))) {
				state = CultureParseStates::GRAPHICAL_CULTURES_ENTRY;
			} else if(!curStr.compare(QStringLiteral("color"))) {
				state = CultureParseStates::COLOR_ENTRY;
			} else if(!curStr.compare(QStringLiteral("cadet_dynasty_names"))) {
				state = CultureParseStates::CADET_DYNASTY_ENTRY;
			} else if(!curStr.compare(QStringLiteral("dynasty_names"))) {
				state = CultureParseStates::DYNASTY_ENTRY;
			} else if(!curStr.compare(QStringLiteral("male_names"))) {
				state = CultureParseStates::MALE_ENTRY;
			} else if(!curStr.compare(QStringLiteral("female_names"))) {
				state = CultureParseStates::FEMALE_ENTRY;
			} else if(!curStr.compare(QStringLiteral("dynasty_of_location_prefix"))) {
				state = CultureParseStates::LOCATION_PREFIX_ENTRY;
			} else if(!curStr.compare(QStringLiteral("patronym_suffix_male"))) {
				state = CultureParseStates::MALE_PATRONYM_SUFFIX_ENTRY;
			} else if(!curStr.compare(QStringLiteral("patronym_suffix_female"))) {
				state = CultureParseStates::FEMALE_PATRONYM_SUFFIX_ENTRY;
			} else if(!curStr.compare(QStringLiteral("patronym_prefix_male"))) {
				state = CultureParseStates::MALE_PATRONYM_PREFIX_ENTRY;
			} else if(!curStr.compare(QStringLiteral("patronym_prefix_female"))) {
				state = CultureParseStates::FEMALE_PATRONYM_PREFIX_ENTRY;
			} else if(!curStr.compare(QStringLiteral("patronym_prefix_male_vowel"))) {
				state = CultureParseStates::MALE_PATRONYM_PREFIX_V_ENTRY;
			} else if(!curStr.compare(QStringLiteral("patronym_prefix_female_vowel"))) {
				state = CultureParseStates::FEMALE_PATRONYM_PREFIX_V_ENTRY;
			} else if(!curStr.compare(QStringLiteral("dynasty_name_first"))) {
				state = CultureParseStates::DYNNAME_FIRST_ENTRY;
			} else if(!curStr.compare(QStringLiteral("founder_named_dynasties"))) {
				state = CultureParseStates::FOUNDER_NAME_ENTRY;
			} else if(!curStr.compare(QStringLiteral("ethnicities"))) {
				state = CultureParseStates::ETHNICITIES_ENTRY;
			} else if(!curStr.compare(QStringLiteral("dynasty_title_names"))) {
				state = CultureParseStates::DYNASTY_TITLE_ENTRY;
			} else if(!curStr.compare(QStringLiteral("mercenary_names"))) {
				state = CultureParseStates::MERCENARY_ENTRY;
			} else if(!curStr.compare(QStringLiteral("pat_grf_name_chance"))) {
				state = CultureParseStates::PAT_GRF_NAME_CHANCE_ENTRY;
			} else if(!curStr.compare(QStringLiteral("mat_grf_name_chance"))) {
				state = CultureParseStates::MAT_GRF_NAME_CHANCE_ENTRY;
			} else if(!curStr.compare(QStringLiteral("father_name_chance"))) {
				state = CultureParseStates::FATHER_NAME_CHANCE_ENTRY;
			} else if(!curStr.compare(QStringLiteral("pat_grm_name_chance"))) {
				state = CultureParseStates::PAT_GRM_NAME_CHANCE_ENTRY;
			} else if(!curStr.compare(QStringLiteral("mat_grm_name_chance"))) {
				state = CultureParseStates::MAT_GRM_NAME_CHANCE_ENTRY;
			} else if(!curStr.compare(QStringLiteral("mother_name_chance"))) {
				state = CultureParseStates::MOTHER_NAME_CHANCE_ENTRY;
			} else if(!curStr.compare(QStringLiteral("grammar_transform"))) {
				state = CultureParseStates::GRAMMAR_TRANSFORM_ENTRY;
			} else if(!curStr.compare(QStringLiteral("bastard_dynasty_prefix"))) {
				state = CultureParseStates::BASTARD_DYNASTY_ENTRY;
			} else if(!curStr.compare(QStringLiteral("always_use_patronym"))) {
				state = CultureParseStates::ALWAYS_PATRONYM_ENTRY;
			} else if(!curStr.compare(QStringLiteral("character_modifier"))) {
				state = CultureParseStates::CHARMOD_ENTRY;
			} else {
				qWarning("Unknown token encountered!");
				if(!curStr.isEmpty()) {
					auto setrdi = curStr.toStdString();
					qWarning("%s", setrdi.c_str());
				}
				if(tmpInt > 3) state = CultureParseStates::DONE;
				else ++tmpInt;
			} break;
		case CultureParseStates::CHARMOD_ENTRY:
			if(!curStr.compare(QStringLiteral("="))) {
				state = CultureParseStates::CHARMOD_EQUAL;
			} break;
		case CultureParseStates::CHARMOD_EQUAL:
			if(!curStr.compare(QStringLiteral("{"))) {
				state = CultureParseStates::CHARMOD_START;
			} break;
		case CultureParseStates::CHARMOD_START:
			if(!curStr.compare(QStringLiteral("}"))) {
				state = CultureParseStates::EXPECTING_ENTRY;
			} else {
				tmpStr = curStr;
				state = CultureParseStates::CHARMOD_KEY;
			} break;
		case CultureParseStates::CHARMOD_KEY:
			if(!curStr.compare(QStringLiteral("="))) {
				state = CultureParseStates::CHARMOD_MAP;
			} break;
		case CultureParseStates::CHARMOD_MAP:
			state = CultureParseStates::CHARMOD_START;
			character_modifier.insert(tmpStr,curStr);
			break;
		case CultureParseStates::ALWAYS_PATRONYM_ENTRY:
			if(!curStr.compare(QStringLiteral("="))) {
				state = CultureParseStates::ALWAYS_PATRONYM_EQUAL;
			} break;
		case CultureParseStates::ALWAYS_PATRONYM_EQUAL:
			if(!curStr.compare(QStringLiteral("yes"))) {
				always_use_patronym = true;
			} else always_use_patronym = false;
			state = CultureParseStates::EXPECTING_ENTRY;
			break;
		case CultureParseStates::MALE_PATRONYM_PREFIX_V_ENTRY:
			if(!curStr.compare(QStringLiteral("="))) {
				state = CultureParseStates::MALE_PATRONYM_PREFIX_V_EQUAL;
			} break;
		case CultureParseStates::FEMALE_PATRONYM_PREFIX_V_ENTRY:
			if(!curStr.compare(QStringLiteral("="))) {
				state = CultureParseStates::FEMALE_PATRONYM_PREFIX_V_EQUAL;
			} break;
		case CultureParseStates::BASTARD_DYNASTY_ENTRY:
			if(!curStr.compare(QStringLiteral("="))) {
				state = CultureParseStates::BASTARD_DYNASTY_EQUAL;
			} break;
		case CultureParseStates::GRAMMAR_TRANSFORM_ENTRY:
			if(!curStr.compare(QStringLiteral("="))) {
				state = CultureParseStates::GRAMMAR_TRANSFORM_EQUAL;
			} break;
		case CultureParseStates::PAT_GRF_NAME_CHANCE_ENTRY:
			if(!curStr.compare(QStringLiteral("="))) {
				state = CultureParseStates::PAT_GRF_NAME_CHANCE_EQUAL;
			} break;
		case CultureParseStates::MAT_GRF_NAME_CHANCE_ENTRY:
			if(!curStr.compare(QStringLiteral("="))) {
				state = CultureParseStates::MAT_GRF_NAME_CHANCE_EQUAL;
			} break;
		case CultureParseStates::FATHER_NAME_CHANCE_ENTRY:
			if(!curStr.compare(QStringLiteral("="))) {
				state = CultureParseStates::FATHER_NAME_CHANCE_EQUAL;
			} break;
		case CultureParseStates::PAT_GRM_NAME_CHANCE_ENTRY:
			if(!curStr.compare(QStringLiteral("="))) {
				state = CultureParseStates::PAT_GRM_NAME_CHANCE_EQUAL;
			} break;
		case CultureParseStates::MAT_GRM_NAME_CHANCE_ENTRY:
			if(!curStr.compare(QStringLiteral("="))) {
				state = CultureParseStates::MAT_GRM_NAME_CHANCE_EQUAL;
			} break;
		case CultureParseStates::MOTHER_NAME_CHANCE_ENTRY:
			if(!curStr.compare(QStringLiteral("="))) {
				state = CultureParseStates::MOTHER_NAME_CHANCE_EQUAL;
			} break;
		case CultureParseStates::DYNASTY_TITLE_ENTRY:
			if(!curStr.compare(QStringLiteral("="))) {
				state = CultureParseStates::DYNASTY_TITLE_EQUAL;
			} break;
		case CultureParseStates::MERCENARY_ENTRY:
			if(!curStr.compare(QStringLiteral("="))) {
				state = CultureParseStates::MERCENARY_EQUAL;
			} break;
		case CultureParseStates::GRAPHICAL_CULTURES_ENTRY:
			if(!curStr.compare(QStringLiteral("="))) {
				state = CultureParseStates::GRAPHICAL_CULTURES_EQUAL;
			} break;
		case CultureParseStates::COLOR_ENTRY:
			if(!curStr.compare(QStringLiteral("="))) {
				state = CultureParseStates::COLOR_EQUAL;
			} break;
		case CultureParseStates::CADET_DYNASTY_ENTRY:
			if(!curStr.compare(QStringLiteral("="))) {
				state = CultureParseStates::CADET_DYNASTY_EQUAL;
			} break;
		case CultureParseStates::DYNASTY_ENTRY:
			if(!curStr.compare(QStringLiteral("="))) {
				state = CultureParseStates::DYNASTY_EQUAL;
			} break;
		case CultureParseStates::MALE_ENTRY:
			if(!curStr.compare(QStringLiteral("="))) {
				state = CultureParseStates::MALE_EQUAL;
			} break;
		case CultureParseStates::FEMALE_ENTRY:
			if(!curStr.compare(QStringLiteral("="))) {
				state = CultureParseStates::FEMALE_EQUAL;
			} break;
		case CultureParseStates::LOCATION_PREFIX_ENTRY:
			if(!curStr.compare(QStringLiteral("="))) {
				state = CultureParseStates::LOCATION_PREFIX_EQUAL;
			} break;
		case CultureParseStates::MALE_PATRONYM_SUFFIX_ENTRY:
			if(!curStr.compare(QStringLiteral("="))) {
				state = CultureParseStates::MALE_PATRONYM_SUFFIX_EQUAL;
			} break;
		case CultureParseStates::FEMALE_PATRONYM_SUFFIX_ENTRY:
			if(!curStr.compare(QStringLiteral("="))) {
				state = CultureParseStates::FEMALE_PATRONYM_SUFFIX_EQUAL;
			} break;
		case CultureParseStates::MALE_PATRONYM_PREFIX_ENTRY:
			if(!curStr.compare(QStringLiteral("="))) {
				state = CultureParseStates::MALE_PATRONYM_PREFIX_EQUAL;
			} break;
		case CultureParseStates::FEMALE_PATRONYM_PREFIX_ENTRY:
			if(!curStr.compare(QStringLiteral("="))) {
				state = CultureParseStates::FEMALE_PATRONYM_PREFIX_EQUAL;
			} break;
		case CultureParseStates::DYNNAME_FIRST_ENTRY:
			if(!curStr.compare(QStringLiteral("="))) {
				state = CultureParseStates::DYNNAME_FIRST_EQUAL;
			} break;
		case CultureParseStates::FOUNDER_NAME_ENTRY:
			if(!curStr.compare(QStringLiteral("="))) {
				state = CultureParseStates::FOUNDER_NAME_EQUAL;
			} break;
		case CultureParseStates::ETHNICITIES_ENTRY:
			if(!curStr.compare(QStringLiteral("="))) {
				state = CultureParseStates::ETHNICITIES_EQUAL;
			} break;
		case CultureParseStates::MALE_PATRONYM_PREFIX_V_EQUAL:
			state = CultureParseStates::EXPECTING_ENTRY;
			curStr.remove(QChar('\"'));
			patronym_prefix_male_vowel = curStr;
			break;
		case CultureParseStates::FEMALE_PATRONYM_PREFIX_V_EQUAL:
			state = CultureParseStates::EXPECTING_ENTRY;
			curStr.remove(QChar('\"'));
			patronym_prefix_female_vowel = curStr;
			break;
		case CultureParseStates::BASTARD_DYNASTY_EQUAL:
			state = CultureParseStates::EXPECTING_ENTRY;
			curStr.remove(QChar('\"'));
			bastard_dynasty_prefix = curStr;
			break;
		case CultureParseStates::GRAMMAR_TRANSFORM_EQUAL:
			state = CultureParseStates::EXPECTING_ENTRY;
			curStr.remove(QChar('\"'));
			grammar_transform = curStr;
			break;
		case CultureParseStates::GRAPHICAL_CULTURES_EQUAL:
			if(!curStr.compare(QStringLiteral("{"))) {
				state = CultureParseStates::GRAPHICAL_CULTURES_START;
			} break;
		case CultureParseStates::CADET_DYNASTY_EQUAL:
			if(!curStr.compare(QStringLiteral("{"))) {
				state = CultureParseStates::CADET_DYNASTY_START;
			} break;
		case CultureParseStates::DYNASTY_EQUAL:
			if(!curStr.compare(QStringLiteral("{"))) {
				state = CultureParseStates::DYNASTY_START;
			} break;
		case CultureParseStates::MALE_EQUAL:
			if(!curStr.compare(QStringLiteral("{"))) {
				state = CultureParseStates::MALE_START;
			} break;
		case CultureParseStates::FEMALE_EQUAL:
			if(!curStr.compare(QStringLiteral("{"))) {
				state = CultureParseStates::FEMALE_START;
			} break;
		case CultureParseStates::ETHNICITIES_EQUAL:
			if(!curStr.compare(QStringLiteral("{"))) {
				state = CultureParseStates::ETHNICITIES_START;
			} break;
		case CultureParseStates::GRAPHICAL_CULTURES_START:
			if(!curStr.compare(QStringLiteral("}"))) {
				state = CultureParseStates::EXPECTING_ENTRY;
			} else {
				graphical_cultures.append(curStr);
			} break;
		case CultureParseStates::LOCATION_PREFIX_EQUAL:
			state = CultureParseStates::EXPECTING_ENTRY;
			curStr.remove(QChar('\"'));
			dynasty_of_location_prefix = curStr;
			break;
		case CultureParseStates::MALE_PATRONYM_SUFFIX_EQUAL:
			state = CultureParseStates::EXPECTING_ENTRY;
			curStr.remove(QChar('\"'));
			patronym_suffix_male = curStr;
			break;
		case CultureParseStates::FEMALE_PATRONYM_SUFFIX_EQUAL:
			state = CultureParseStates::EXPECTING_ENTRY;
			curStr.remove(QChar('\"'));
			patronym_suffix_female = curStr;
			break;
		case CultureParseStates::MALE_PATRONYM_PREFIX_EQUAL:
			state = CultureParseStates::EXPECTING_ENTRY;
			curStr.remove(QChar('\"'));
			patronym_prefix_male = curStr;
			break;
		case CultureParseStates::FEMALE_PATRONYM_PREFIX_EQUAL:
			state = CultureParseStates::EXPECTING_ENTRY;
			curStr.remove(QChar('\"'));
			patronym_prefix_female = curStr;
			break;
		case CultureParseStates::PAT_GRF_NAME_CHANCE_EQUAL:
			state = CultureParseStates::EXPECTING_ENTRY;
			pat_grf_name_chance = curStr.toInt();
			break;
		case CultureParseStates::MAT_GRF_NAME_CHANCE_EQUAL:
			state = CultureParseStates::EXPECTING_ENTRY;
			mat_grf_name_chance = curStr.toInt();
			break;
		case CultureParseStates::FATHER_NAME_CHANCE_EQUAL:
			state = CultureParseStates::EXPECTING_ENTRY;
			father_name_chance = curStr.toInt();
			break;
		case CultureParseStates::PAT_GRM_NAME_CHANCE_EQUAL:
			state = CultureParseStates::EXPECTING_ENTRY;
			pat_grm_name_chance = curStr.toInt();
			break;
		case CultureParseStates::MAT_GRM_NAME_CHANCE_EQUAL:
			state = CultureParseStates::EXPECTING_ENTRY;
			mat_grm_name_chance = curStr.toInt();
			break;
		case CultureParseStates::MOTHER_NAME_CHANCE_EQUAL:
			state = CultureParseStates::EXPECTING_ENTRY;
			mother_name_chance = curStr.toInt();
			break;
		case CultureParseStates::DYNASTY_TITLE_EQUAL:
			if(!curStr.compare(QStringLiteral("yes"))) {
				dynasty_title_names = true;
			} else dynasty_title_names = false;
			state = CultureParseStates::EXPECTING_ENTRY;
			break;
		case CultureParseStates::DYNNAME_FIRST_EQUAL:
			if(!curStr.compare(QStringLiteral("yes"))) {
				dynasty_name_first = true;
			} else dynasty_name_first = false;
			state = CultureParseStates::EXPECTING_ENTRY;
			break;
		case CultureParseStates::FOUNDER_NAME_EQUAL:
			if(!curStr.compare(QStringLiteral("yes"))) {
				founder_named_dynasties = true;
			} else founder_named_dynasties = false;
			state = CultureParseStates::EXPECTING_ENTRY;
			break;
		case CultureParseStates::CADET_DYNASTY_START:
			if(!curStr.compare(QStringLiteral("{"))) {
				state = CultureParseStates::CADET_DYNASTY_EXTRA;
			} else if(!curStr.compare(QStringLiteral("}"))) {
				state = CultureParseStates::EXPECTING_ENTRY;
			} else {
				curStr.remove(QChar('\"'));
				cadet_dynasty_names.append(curStr);
				state = CultureParseStates::CADET_DYNASTY_START;
			}
			break;
		case CultureParseStates::DYNASTY_START:
			if(!curStr.compare(QStringLiteral("{"))) {
				state = CultureParseStates::DYNASTY_EXTRA;
			} else if(!curStr.compare(QStringLiteral("}"))) {
				state = CultureParseStates::EXPECTING_ENTRY;
			} else {
				curStr.remove(QChar('\"'));
				dynasty_names.append(curStr);
				state = CultureParseStates::DYNASTY_START;
			}
			break;
		case CultureParseStates::MALE_START:
			if(!curStr.compare(QStringLiteral("}"))) {
				state = CultureParseStates::EXPECTING_ENTRY;
			} else {
				curStr.remove(QChar('\"'));
				male_names.append(curStr);
				state = CultureParseStates::MALE_START;
			}
			break;
		case CultureParseStates::FEMALE_START:
			if(!curStr.compare(QStringLiteral("}"))) {
				state = CultureParseStates::EXPECTING_ENTRY;
			} else {
				curStr.remove(QChar('\"'));
				female_names.append(curStr);
				state = CultureParseStates::FEMALE_START;
			}
			break;
		case CultureParseStates::CADET_DYNASTY_EXTRA:
			if(!curStr.compare(QStringLiteral("}"))) {
				cadet_dynasty_names.append(QStringLiteral("{ %1 %2 }").arg(tmpList[0],tmpList[1]));
				tmpList.clear();
				state = CultureParseStates::CADET_DYNASTY_START;
			} else {
				tmpList.append(curStr);
				state = CultureParseStates::CADET_DYNASTY_EXTRA;
			}
			break;
		case CultureParseStates::DYNASTY_EXTRA:
			if(!curStr.compare(QStringLiteral("}"))) {
				dynasty_names.append(QStringLiteral("{ %1 %2 }").arg(tmpList[0],tmpList[1]));
				tmpList.clear();
				state = CultureParseStates::DYNASTY_START;
			} else {
				tmpList.append(curStr);
				state = CultureParseStates::DYNASTY_EXTRA;
			}
			break;
		case CultureParseStates::ETHNICITIES_START:
			if(!curStr.compare(QStringLiteral("}"))) {
				state = CultureParseStates::EXPECTING_ENTRY;
			} else {
				tmpInt = curStr.toInt();
				state = CultureParseStates::ETHNICITIES_NUMBER;
			}
			break;
		case CultureParseStates::ETHNICITIES_NUMBER:
			if(!curStr.compare(QStringLiteral("="))) {
				state = CultureParseStates::ETHNICITIES_MAP;
			} break;
		case CultureParseStates::ETHNICITIES_MAP:
			ethnicities.insert(curStr,tmpInt);
			state = CultureParseStates::ETHNICITIES_START;
			break;
		case CultureParseStates::MERCENARY_EQUAL:
			state = CultureParseStates::MERCENARY_START;
			break;
		case CultureParseStates::MERCENARY_START:
			if(!curStr.compare(QStringLiteral("}"))) {
				state = CultureParseStates::EXPECTING_ENTRY;
			} else {
				state = CultureParseStates::MERCENARY_ENTRY_START;
			}
			break;
		case CultureParseStates::MERCENARY_ENTRY_START:
			state = CultureParseStates::MERCENARY_ENTRY_NAME;
			break;
		case CultureParseStates::MERCENARY_ENTRY_NAME:
			if(!curStr.compare(QStringLiteral("="))) {
				state = CultureParseStates::MERCENARY_ENTRY_EQUAL;
			}
			break;
		case CultureParseStates::MERCENARY_ENTRY_EQUAL:
			mercenary_names.append(curStr);
			state = CultureParseStates::MERCENARY_ENTRY_STR;
			break;
		case CultureParseStates::MERCENARY_ENTRY_STR:
			state = CultureParseStates::MERCENARY_START;
			break;
		case CultureParseStates::COLOR_EQUAL:
			if(!curStr.compare(QStringLiteral("{"))) {
				state = CultureParseStates::COLOR_RGBF;
			} else if(!curStr.compare(QStringLiteral("rgb{"))) {
				state = CultureParseStates::COLOR_RGBI;
			} else if(!curStr.compare(QStringLiteral("hsv{"))) {
				state = CultureParseStates::COLOR_HSVF;
			} else if(!curStr.compare(QStringLiteral("hsv360{"))) {
				state = CultureParseStates::COLOR_HSV360;
			} else if(!curStr.compare(QStringLiteral("rgb"))) {
				state = CultureParseStates::COLOR_N_RGBI;
			} else if(!curStr.compare(QStringLiteral("hsv"))) {
				state = CultureParseStates::COLOR_N_HSVF;
			} else if(!curStr.compare(QStringLiteral("hsv360"))) {
				state = CultureParseStates::COLOR_N_HSV360;
			}
			tmpInt = 0;
			tmpList.clear();
			break;
		case CultureParseStates::COLOR_N_RGBI:
			state = CultureParseStates::COLOR_RGBI;
			break;
		case CultureParseStates::COLOR_N_HSVF:
			state = CultureParseStates::COLOR_HSVF;
			break;
		case CultureParseStates::COLOR_N_HSV360:
			state = CultureParseStates::COLOR_HSV360;
			break;
		case CultureParseStates::COLOR_RGBF:
			if(!curStr.compare(QStringLiteral("}"))) {
				color.setRgbF(tmpList[0].toDouble(),tmpList[1].toDouble(),tmpList[2].toDouble());
				tmpList.clear();
				state = CultureParseStates::EXPECTING_ENTRY;
			} else {
				tmpList.append(curStr);
			}
			break;
		case CultureParseStates::COLOR_RGBI:
			if(!curStr.compare(QStringLiteral("}"))) {
				color.setRgb(tmpList[0].toInt(),tmpList[1].toInt(),tmpList[2].toInt());
				tmpList.clear();
				state = CultureParseStates::EXPECTING_ENTRY;
			} else {
				tmpList.append(curStr);
			}
			break;
		case CultureParseStates::COLOR_HSVF:
			if(!curStr.compare(QStringLiteral("}"))) {
				color.setHsvF(tmpList[0].toDouble(),tmpList[1].toDouble(),tmpList[2].toDouble());
				tmpList.clear();
				state = CultureParseStates::EXPECTING_ENTRY;
			} else {
				tmpList.append(curStr);
			}
			break;
		case CultureParseStates::COLOR_HSV360:
			if(!curStr.compare(QStringLiteral("}"))) {
				color.setHsv(tmpList[0].toInt(),tmpList[1].toInt(),tmpList[2].toInt());
				tmpList.clear();
				state = CultureParseStates::EXPECTING_ENTRY;
			} else {
				tmpList.append(curStr);
			}
			break;
		default:
			break;
		}
	}
}

void Culture::save(QTextStream &stream) const
{
	// Graphical Cultures
	if(!graphical_cultures.isEmpty()) {
		stream << QStringLiteral("graphical_cultures = {\n");
		for(const auto& it : graphical_cultures) {
			stream << it << '\n';
		}
		stream << '}' << '\n';
	}
	// Colour
	stream << QStringLiteral("color = { ") << color.redF() << ' ' << color.greenF() << ' ' << color.blueF() << QStringLiteral(" }\n");
	// Character modifier
	if(!character_modifier.isEmpty()) {
		stream << QStringLiteral("character_modifier = {\n");
		for(auto it = std::begin(character_modifier); it != std::end(character_modifier); ++it) {
			stream << QStringLiteral("%1 = %2\n").arg(it.key()).arg(it.value().toString());
		}
		stream << QStringLiteral("}\n");
	}
	// Cadet Dynasty Names
	if(!cadet_dynasty_names.isEmpty()) {
		int i = 0;
		stream << QStringLiteral("cadet_dynasty_names = {\n");
		for(const auto& it : cadet_dynasty_names) {
			if(i < 15) {
				if(it.startsWith(QChar('{'))) stream << it << ' ';
				else stream << '\"' << it << '\"' << ' ';
				++i;
			} else {
				if(it.startsWith(QChar('{'))) stream << it << '\n';
				else stream << '\"' << it << '\"' << '\n';
				i = 0;
			}
		}
		stream << '\n' << '}' << '\n';
	}
	// Dynasty Names
	if(!dynasty_names.isEmpty()) {
		int i = 0;
		stream << QStringLiteral("dynasty_names = {\n");
		for(const auto& it : dynasty_names) {
			if(i < 15) {
				if(it.startsWith(QChar('{'))) stream << it << ' ';
				else stream << '\"' << it << '\"' << ' ';
				++i;
			} else {
				if(it.startsWith(QChar('{'))) stream << it << '\n';
				else stream << '\"' << it << '\"' << '\n';
				i = 0;
			}
		}
		stream << '\n' << '}' << '\n';
	}
	// Male Names
	if(!male_names.isEmpty()) {
		int i = 0;
		stream << QStringLiteral("male_names = {\n");
		for(const auto& it : male_names) {
			if(i < 15) {
				stream << '\"' << it << '\"' << ' ';
				++i;
			} else {
				stream << '\"' << it << '\"' << '\n';
				i = 0;
			}
		}
		stream << '\n' << '}' << '\n';
	}
	// Female Names
	if(!female_names.isEmpty()) {
		int i = 0;
		stream << QStringLiteral("female_names = {\n");
		for(const auto& it : female_names) {
			if(i < 15) {
				stream << '\"' << it << '\"' << ' ';
				++i;
			} else {
				stream << '\"' << it << '\"' << '\n';
				i = 0;
			}
		}
		stream << '\n' << '}' << '\n';
	}
	if(!dynasty_of_location_prefix.isEmpty()) stream << QStringLiteral("dynasty_of_location_prefix = \"%1\"\n").arg(dynasty_of_location_prefix);
	if(!patronym_suffix_male.isEmpty()) stream << QStringLiteral("patronym_suffix_male = \"%1\"\n").arg(patronym_suffix_male);
	if(!patronym_suffix_female.isEmpty()) stream << QStringLiteral("patronym_suffix_female = \"%1\"\n").arg(patronym_suffix_female);
	if(!patronym_prefix_male.isEmpty()) stream << QStringLiteral("patronym_prefix_male = \"%1\"\n").arg(patronym_prefix_male);
	if(!patronym_prefix_male_vowel.isEmpty()) stream << QStringLiteral("patronym_prefix_male_vowel = \"%1\"\n").arg(patronym_prefix_male_vowel);
	if(!patronym_prefix_female.isEmpty()) stream << QStringLiteral("patronym_prefix_female = \"%1\"\n").arg(patronym_prefix_female);
	if(!patronym_prefix_female_vowel.isEmpty()) stream << QStringLiteral("patronym_prefix_female_vowel = \"%1\"\n").arg(patronym_prefix_female_vowel);
	if(!grammar_transform.isEmpty()) stream << QStringLiteral("grammar_transform = %1\n").arg(grammar_transform);
	if(!bastard_dynasty_prefix.isEmpty()) stream << QStringLiteral("bastard_dynasty_prefix = \"%1\"\n").arg(bastard_dynasty_prefix);
	if(dynasty_name_first) stream << QStringLiteral("dynasty_name_first = yes\n");
	if(founder_named_dynasties) stream << QStringLiteral("founder_named_dynasties = yes\n");
	if(dynasty_title_names) stream << QStringLiteral("dynasty_title_names = yes\n");
	if(always_use_patronym) stream << QStringLiteral("always_use_patronym = yes\n");
	if(pat_grf_name_chance) stream << QStringLiteral("pat_grf_name_chance = %1\n").arg(pat_grf_name_chance);
	if(mat_grf_name_chance) stream << QStringLiteral("mat_grf_name_chance = %1\n").arg(mat_grf_name_chance);
	if(father_name_chance) stream << QStringLiteral("father_name_chance = %1\n").arg(father_name_chance);
	if(pat_grm_name_chance) stream << QStringLiteral("pat_grm_name_chance = %1\n").arg(pat_grm_name_chance);
	if(mat_grm_name_chance) stream << QStringLiteral("mat_grm_name_chance = %1\n").arg(mat_grm_name_chance);
	if(mother_name_chance) stream << QStringLiteral("mother_name_chance = %1\n").arg(mother_name_chance);
	// Ethnicities
	if(!ethnicities.isEmpty()) {
		QList<QPair<QString,int>> tmpList;
		for(auto it = std::begin(ethnicities); it != std::end(ethnicities); ++it ) {
			tmpList.append(QPair<QString,int>(it.key(),it.value()));
		}
		std::sort(std::begin(tmpList), std::end(tmpList),isGreater);
		stream << QStringLiteral("ethnicities = {\n");
		for(const auto& it : tmpList) {
			stream << QStringLiteral("%2 = %1\n").arg(it.first).arg(it.second);
		}
		stream << '}' << '\n';
	}
	// Graphical Cultures
	if(!mercenary_names.isEmpty()) {
		stream << QStringLiteral("mercenary_names = {\n");
		for(const auto& it : mercenary_names) {
			stream << QStringLiteral("{ name = \"%1\" }").arg(it) << '\n';
		}
		stream << '}' << '\n';
	}
}

QTextStream &operator<<(QTextStream &stream, const Culture &culture)
{
	culture.save(stream);
	return stream;
}

QTextStream &operator>>(QTextStream &stream, Culture &culture)
{
	culture.load(stream);
	return stream;
}
