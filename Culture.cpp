#include "Culture.hpp"
#include <QList>
#include <QPair>
#include <QtGlobal>
#include <QJsonArray>
#include <QCborArray>

typedef QPair<QString,int> NamedNumber;

bool isGreater(const NamedNumber& a, const NamedNumber& b) {
	return a.second > b.second;
}

const QStringList& Culture::getGraphicalCultures() const
{
	return graphicalCultures;
}
QStringList& Culture::getGraphicalCultures()
{
	return graphicalCultures;
}
void Culture::setGraphicalCultures(const QStringList &value)
{
	graphicalCultures = value;
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


QJsonObject Culture::toJson() const
{
	QJsonObject tmp;
	toJson(tmp);
	return tmp;
}

void Culture::toCbor(QCborMap &cbor) const
{
	cbor[QStringLiteral("color")] = QCborValue::fromVariant(color);
	cbor[QStringLiteral("dynastyOfLocationPrefix")] = dynastyOfLocationPrefix;
	cbor[QStringLiteral("patronymSuffixMale")] = patronymSuffixMale;
	cbor[QStringLiteral("patronymSuffixFemale")] = patronymSuffixFemale;
	cbor[QStringLiteral("patronymPrefixMale")] = patronymPrefixMale;
	cbor[QStringLiteral("patronymPrefixMaleVowel")] = patronymPrefixMaleVowel;
	cbor[QStringLiteral("patronymPrefixFemale")] = patronymPrefixFemale;
	cbor[QStringLiteral("patronymPrefixFemaleVowel")] = patronymPrefixFemaleVowel;
	cbor[QStringLiteral("grammarTransform")] = grammarTransform;
	cbor[QStringLiteral("bastardDynastyPrefix")] = bastardDynastyPrefix;
	cbor[QStringLiteral("dynastyNameFirst")] = dynastyNameFirst;
	cbor[QStringLiteral("founderNamedDynasties")] = founderNamedDynasties;
	cbor[QStringLiteral("dynastyTitleNames")] = dynastyTitleNames;
	cbor[QStringLiteral("alwaysUsePatronym")] = alwaysUsePatronym;
	cbor[QStringLiteral("patGrfNameChance")] = patGrfNameChance;
	cbor[QStringLiteral("matGrfNameChance")] = matGrfNameChance;
	cbor[QStringLiteral("fatherNameChance")] = fatherNameChance;
	cbor[QStringLiteral("patGrmNameChance")] = patGrmNameChance;
	cbor[QStringLiteral("matGrmNameChance")] = matGrmNameChance;
	cbor[QStringLiteral("motherNameChance")] = motherNameChance;
	if(!graphicalCultures.isEmpty()) {
		QCborArray tmp;
		for(const auto& it : graphicalCultures) {
			tmp.push_back(it);
		}
		cbor[QStringLiteral("graphicalCultures")] = tmp;
	}
	if(!mercenaryNames.isEmpty()) {
		QCborArray tmp;
		for(const auto& it : mercenaryNames) {
			tmp.push_back(it);
		}
		cbor[QStringLiteral("mercenaryNames")] = tmp;
	}
	if(!cadetDynastyNames.isEmpty()) {
		QCborArray tmp;
		for(const auto& it : cadetDynastyNames) {
			tmp.push_back(it);
		}
		cbor[QStringLiteral("cadetDynastyNames")] = tmp;
	}
	if(!dynastyNames.isEmpty()) {
		QCborArray tmp;
		for(const auto& it : dynastyNames) {
			tmp.push_back(it);
		}
		cbor[QStringLiteral("dynastyNames")] = tmp;
	}
	if(!maleNames.isEmpty()) {
		QCborArray tmp;
		for(const auto& it : maleNames) {
			tmp.push_back(it);
		}
		cbor[QStringLiteral("maleNames")] = tmp;
	}
	if(!femaleNames.isEmpty()) {
		QCborArray tmp;
		for(const auto& it : femaleNames) {
			tmp.push_back(it);
		}
		cbor[QStringLiteral("femaleNames")] = tmp;
	}
	if(!ethnicities.isEmpty()) {
		QCborMap tmp;
		for(auto it = std::begin(ethnicities); it != std::end(ethnicities); ++it) {
			tmp.insert(it.key(),it.value());
		}
		cbor[QStringLiteral("ethnicities")] = tmp;
	}
	if(!characterModifier.isEmpty()) {
		QCborMap tmp;
		for(auto it = std::begin(characterModifier); it != std::end(characterModifier); ++it) {
			tmp.insert(it.key(),QCborValue::fromVariant(it.value()));
		}
		cbor[QStringLiteral("characterModifier")] = tmp;
	}
}

QCborMap Culture::toCbor() const
{
	QCborMap tmp;
	toCbor(tmp);
	return tmp;
}

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
			characterModifier.insert(tmpStr,curStr);
			break;
		case CultureParseStates::ALWAYS_PATRONYM_ENTRY:
			if(!curStr.compare(QStringLiteral("="))) {
				state = CultureParseStates::ALWAYS_PATRONYM_EQUAL;
			} break;
		case CultureParseStates::ALWAYS_PATRONYM_EQUAL:
			if(!curStr.compare(QStringLiteral("yes"))) {
				alwaysUsePatronym = true;
			} else alwaysUsePatronym = false;
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
			patronymPrefixMaleVowel = curStr;
			break;
		case CultureParseStates::FEMALE_PATRONYM_PREFIX_V_EQUAL:
			state = CultureParseStates::EXPECTING_ENTRY;
			curStr.remove(QChar('\"'));
			patronymPrefixFemaleVowel = curStr;
			break;
		case CultureParseStates::BASTARD_DYNASTY_EQUAL:
			state = CultureParseStates::EXPECTING_ENTRY;
			curStr.remove(QChar('\"'));
			bastardDynastyPrefix = curStr;
			break;
		case CultureParseStates::GRAMMAR_TRANSFORM_EQUAL:
			state = CultureParseStates::EXPECTING_ENTRY;
			curStr.remove(QChar('\"'));
			grammarTransform = curStr;
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
				graphicalCultures.append(curStr);
			} break;
		case CultureParseStates::LOCATION_PREFIX_EQUAL:
			state = CultureParseStates::EXPECTING_ENTRY;
			curStr.remove(QChar('\"'));
			dynastyOfLocationPrefix = curStr;
			break;
		case CultureParseStates::MALE_PATRONYM_SUFFIX_EQUAL:
			state = CultureParseStates::EXPECTING_ENTRY;
			curStr.remove(QChar('\"'));
			patronymSuffixMale = curStr;
			break;
		case CultureParseStates::FEMALE_PATRONYM_SUFFIX_EQUAL:
			state = CultureParseStates::EXPECTING_ENTRY;
			curStr.remove(QChar('\"'));
			patronymSuffixFemale = curStr;
			break;
		case CultureParseStates::MALE_PATRONYM_PREFIX_EQUAL:
			state = CultureParseStates::EXPECTING_ENTRY;
			curStr.remove(QChar('\"'));
			patronymPrefixMale = curStr;
			break;
		case CultureParseStates::FEMALE_PATRONYM_PREFIX_EQUAL:
			state = CultureParseStates::EXPECTING_ENTRY;
			curStr.remove(QChar('\"'));
			patronymPrefixFemale = curStr;
			break;
		case CultureParseStates::PAT_GRF_NAME_CHANCE_EQUAL:
			state = CultureParseStates::EXPECTING_ENTRY;
			patGrfNameChance = curStr.toInt();
			break;
		case CultureParseStates::MAT_GRF_NAME_CHANCE_EQUAL:
			state = CultureParseStates::EXPECTING_ENTRY;
			matGrfNameChance = curStr.toInt();
			break;
		case CultureParseStates::FATHER_NAME_CHANCE_EQUAL:
			state = CultureParseStates::EXPECTING_ENTRY;
			fatherNameChance = curStr.toInt();
			break;
		case CultureParseStates::PAT_GRM_NAME_CHANCE_EQUAL:
			state = CultureParseStates::EXPECTING_ENTRY;
			patGrmNameChance = curStr.toInt();
			break;
		case CultureParseStates::MAT_GRM_NAME_CHANCE_EQUAL:
			state = CultureParseStates::EXPECTING_ENTRY;
			matGrmNameChance = curStr.toInt();
			break;
		case CultureParseStates::MOTHER_NAME_CHANCE_EQUAL:
			state = CultureParseStates::EXPECTING_ENTRY;
			motherNameChance = curStr.toInt();
			break;
		case CultureParseStates::DYNASTY_TITLE_EQUAL:
			if(!curStr.compare(QStringLiteral("yes"))) {
				dynastyTitleNames = true;
			} else dynastyTitleNames = false;
			state = CultureParseStates::EXPECTING_ENTRY;
			break;
		case CultureParseStates::DYNNAME_FIRST_EQUAL:
			if(!curStr.compare(QStringLiteral("yes"))) {
				dynastyNameFirst = true;
			} else dynastyNameFirst = false;
			state = CultureParseStates::EXPECTING_ENTRY;
			break;
		case CultureParseStates::FOUNDER_NAME_EQUAL:
			if(!curStr.compare(QStringLiteral("yes"))) {
				founderNamedDynasties = true;
			} else founderNamedDynasties = false;
			state = CultureParseStates::EXPECTING_ENTRY;
			break;
		case CultureParseStates::CADET_DYNASTY_START:
			if(!curStr.compare(QStringLiteral("{"))) {
				state = CultureParseStates::CADET_DYNASTY_EXTRA;
			} else if(!curStr.compare(QStringLiteral("}"))) {
				state = CultureParseStates::EXPECTING_ENTRY;
			} else {
				curStr.remove(QChar('\"'));
				cadetDynastyNames.append(curStr);
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
				dynastyNames.append(curStr);
				state = CultureParseStates::DYNASTY_START;
			}
			break;
		case CultureParseStates::MALE_START:
			if(!curStr.compare(QStringLiteral("}"))) {
				state = CultureParseStates::EXPECTING_ENTRY;
			} else {
				curStr.remove(QChar('\"'));
				maleNames.append(curStr);
				state = CultureParseStates::MALE_START;
			}
			break;
		case CultureParseStates::FEMALE_START:
			if(!curStr.compare(QStringLiteral("}"))) {
				state = CultureParseStates::EXPECTING_ENTRY;
			} else {
				curStr.remove(QChar('\"'));
				femaleNames.append(curStr);
				state = CultureParseStates::FEMALE_START;
			}
			break;
		case CultureParseStates::CADET_DYNASTY_EXTRA:
			if(!curStr.compare(QStringLiteral("}"))) {
				if(tmpList.size() > 1) cadetDynastyNames.append(QStringLiteral("{ %1 %2 }").arg(tmpList[0]).arg(tmpList[1]));
				else cadetDynastyNames.append(QStringLiteral("{ %1 }").arg(tmpList[0]));
				tmpList.clear();
				state = CultureParseStates::CADET_DYNASTY_START;
			} else {
				tmpList.append(curStr);
				state = CultureParseStates::CADET_DYNASTY_EXTRA;
			}
			break;
		case CultureParseStates::DYNASTY_EXTRA:
			if(!curStr.compare(QStringLiteral("}"))) {
				if(tmpList.size() > 1) dynastyNames.append(QStringLiteral("{ %1 %2 }").arg(tmpList[0]).arg(tmpList[1]));
				else dynastyNames.append(QStringLiteral("{ %1 }").arg(tmpList[0]));
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
			curStr.remove(QChar('\"'));
			mercenaryNames.append(curStr);
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
	if(!graphicalCultures.isEmpty()) {
		stream << QStringLiteral("\t\tgraphical_cultures = {\n");
		for(const auto& it : graphicalCultures) {
			stream << QStringLiteral("\t\t\t") << it << '\n';
		}
		stream << QStringLiteral("\t\t}\n");
	}
	// Colour
	stream << QStringLiteral("\t\tcolor = { ") << color.redF() << ' ' << color.greenF() << ' ' << color.blueF() << QStringLiteral(" }\n");
	// Character modifier
	if(!characterModifier.isEmpty()) {
		stream << QStringLiteral("\t\tcharacter_modifier = {\n");
		for(auto it = std::begin(characterModifier); it != std::end(characterModifier); ++it) {
			stream << QStringLiteral("\t\t\t%1 = %2\n").arg(it.key()).arg(it.value().toString());
		}
		stream << QStringLiteral("\t\t}\n");
	}
	// Cadet Dynasty Names
	if(!cadetDynastyNames.isEmpty()) {
		int i = 0;
		stream << QStringLiteral("\t\tcadet_dynasty_names = {\n\t\t\t");
		for(const auto& it : cadetDynastyNames) {
			if(i < 15) {
				if(it.startsWith(QChar('{'))) stream << it << ' ';
				else stream << '\"' << it << '\"' << ' ';
				++i;
			} else {
				if(it.startsWith(QChar('{'))) stream << it << '\n';
				else stream << '\"' << it << '\"' << QStringLiteral("\n\t\t\t");
				i = 0;
			}
		}
		stream << QStringLiteral("\n\t\t}\n");
	}
	// Dynasty Names
	if(!dynastyNames.isEmpty()) {
		int i = 0;
		stream << QStringLiteral("\t\tdynasty_names = {\n\t\t\t");
		for(const auto& it : dynastyNames) {
			if(i < 15) {
				if(it.startsWith(QChar('{'))) stream << it << ' ';
				else stream << '\"' << it << '\"' << ' ';
				++i;
			} else {
				if(it.startsWith(QChar('{'))) stream << it << '\n';
				else stream << '\"' << it << '\"' << QStringLiteral("\n\t\t\t");
				i = 0;
			}
		}
		stream << QStringLiteral("\n\t\t}\n");
	}
	// Male Names
	if(!maleNames.isEmpty()) {
		int i = 0;
		stream << QStringLiteral("\t\tmale_names = {\n\t\t\t");
		for(const auto& it : maleNames) {
			if(i < 15) {
				stream << '\"' << it << '\"' << ' ';
				++i;
			} else {
				stream << '\"' << it << '\"' << QStringLiteral("\n\t\t\t");
				i = 0;
			}
		}
		stream << QStringLiteral("\n\t\t}\n");
	}
	// Female Names
	if(!femaleNames.isEmpty()) {
		int i = 0;
		stream << QStringLiteral("\t\tfemale_names = {\n\t\t\t");
		for(const auto& it : femaleNames) {
			if(i < 15) {
				stream << '\"' << it << '\"' << ' ';
				++i;
			} else {
				stream << '\"' << it << '\"' << QStringLiteral("\n\t\t\t");
				i = 0;
			}
		}
		stream << QStringLiteral("\n\t\t}\n");
	}
	if(!dynastyOfLocationPrefix.isEmpty()) stream << QStringLiteral("\t\tdynasty_of_location_prefix = \"%1\"\n").arg(dynastyOfLocationPrefix);
	if(!patronymSuffixMale.isEmpty()) stream << QStringLiteral("\t\tpatronym_suffix_male = \"%1\"\n").arg(patronymSuffixMale);
	if(!patronymSuffixFemale.isEmpty()) stream << QStringLiteral("\t\tpatronym_suffix_female = \"%1\"\n").arg(patronymSuffixFemale);
	if(!patronymPrefixMale.isEmpty()) stream << QStringLiteral("\t\tpatronym_prefix_male = \"%1\"\n").arg(patronymPrefixMale);
	if(!patronymPrefixMaleVowel.isEmpty()) stream << QStringLiteral("\t\tpatronym_prefix_male_vowel = \"%1\"\n").arg(patronymPrefixMaleVowel);
	if(!patronymPrefixFemale.isEmpty()) stream << QStringLiteral("\t\tpatronym_prefix_female = \"%1\"\n").arg(patronymPrefixFemale);
	if(!patronymPrefixFemaleVowel.isEmpty()) stream << QStringLiteral("\t\tpatronym_prefix_female_vowel = \"%1\"\n").arg(patronymPrefixFemaleVowel);
	if(!grammarTransform.isEmpty()) stream << QStringLiteral("\t\tgrammar_transform = %1\n").arg(grammarTransform);
	if(!bastardDynastyPrefix.isEmpty()) stream << QStringLiteral("\t\tbastard_dynasty_prefix = \"%1\"\n").arg(bastardDynastyPrefix);
	if(dynastyNameFirst) stream << QStringLiteral("\t\tdynasty_name_first = yes\n");
	if(founderNamedDynasties) stream << QStringLiteral("\t\tfounder_named_dynasties = yes\n");
	if(dynastyTitleNames) stream << QStringLiteral("\t\tdynasty_title_names = yes\n");
	if(alwaysUsePatronym) stream << QStringLiteral("\t\talways_use_patronym = yes\n");
	if(patGrfNameChance) stream << QStringLiteral("\t\tpat_grf_name_chance = %1\n").arg(patGrfNameChance);
	if(matGrfNameChance) stream << QStringLiteral("\t\tmat_grf_name_chance = %1\n").arg(matGrfNameChance);
	if(fatherNameChance) stream << QStringLiteral("\t\tfather_name_chance = %1\n").arg(fatherNameChance);
	if(patGrmNameChance) stream << QStringLiteral("\t\t\t\tpat_grm_name_chance = %1\n").arg(patGrmNameChance);
	if(matGrmNameChance) stream << QStringLiteral("mat_grm_name_chance = %1\n").arg(matGrmNameChance);
	if(motherNameChance) stream << QStringLiteral("\t\tmother_name_chance = %1\n").arg(motherNameChance);
	// Ethnicities
	if(!ethnicities.isEmpty()) {
		QList<QPair<QString,int>> tmpList;
		for(auto it = std::begin(ethnicities); it != std::end(ethnicities); ++it ) {
			tmpList.append(QPair<QString,int>(it.key(),it.value()));
		}
		std::sort(std::begin(tmpList), std::end(tmpList),isGreater);
		stream << QStringLiteral("\t\tethnicities = {\n");
		for(const auto& it : tmpList) {
			stream << QStringLiteral("\t\t\t%2 = %1\n").arg(it.first).arg(it.second);
		}
		stream << QStringLiteral("\t\t}\n");
	}
	// Mercenaries
	if(!mercenaryNames.isEmpty()) {
		stream << QStringLiteral("\t\tmercenary_names = {\n");
		for(const auto& it : mercenaryNames) {
			stream << QStringLiteral("\t\t\t{ name = \"%1\" }").arg(it) << '\n';
		}
		stream << QStringLiteral("\t\t}\n");
	}
}

void Culture::fromJson(const QJsonObject &json)
{
	QJsonArray tmpGC = json[QStringLiteral("graphicalCultures")].toArray();
	if(!tmpGC.isEmpty()) {
		for(const auto it : tmpGC) {
			graphicalCultures.push_back(it.toString());
		}
	}
	QJsonArray tmpMN = json[QStringLiteral("mercenaryNames")].toArray();
	if(!tmpMN.isEmpty()) {
		for(const auto it : tmpMN) {
			mercenaryNames.push_back(it.toString());
		}
	}
	color = json[QStringLiteral("color")].toVariant().value<QColor>();
	tmpMN = json[QStringLiteral("cadetDynastyNames")].toArray();
	if(!tmpMN.isEmpty()) {
		for(const auto it : tmpMN) {
			mercenaryNames.push_back(it.toString());
		}
	}
	tmpMN = json[QStringLiteral("dynastyNames")].toArray();
	if(!tmpMN.isEmpty()) {
		for(const auto it : tmpMN) {
			mercenaryNames.push_back(it.toString());
		}
	}
	tmpMN = json[QStringLiteral("maleNames")].toArray();
	if(!tmpMN.isEmpty()) {
		for(const auto it : tmpMN) {
			mercenaryNames.push_back(it.toString());
		}
	}
	tmpMN = json[QStringLiteral("femaleNames")].toArray();
	if(!tmpMN.isEmpty()) {
		for(const auto it : tmpMN) {
			mercenaryNames.push_back(it.toString());
		}
	}
	dynastyOfLocationPrefix = json[QStringLiteral("dynastyOfLocationPrefix")].toString();
	patronymSuffixMale = json[QStringLiteral("patronymSuffixMale")].toString();
	patronymSuffixFemale = json[QStringLiteral("patronymSuffixFemale")].toString();
	patronymPrefixMale = json[QStringLiteral("patronymPrefixMale")].toString();
	patronymPrefixMaleVowel = json[QStringLiteral("patronymPrefixMaleVowel")].toString();
	patronymPrefixFemale = json[QStringLiteral("patronymPrefixFemale")].toString();
	patronymPrefixFemaleVowel = json[QStringLiteral("patronymPrefixFemaleVowel")].toString();
	grammarTransform = json[QStringLiteral("grammarTransform")].toString();
	bastardDynastyPrefix = json[QStringLiteral("bastardDynastyPrefix")].toString();
	dynastyNameFirst = json[QStringLiteral("dynastyNameFirst")].toBool();
	founderNamedDynasties = json[QStringLiteral("founderNamedDynasties")].toBool();
	dynastyTitleNames = json[QStringLiteral("dynastyTitleNames")].toBool();
	alwaysUsePatronym = json[QStringLiteral("alwaysUsePatronym")].toBool();
	patGrfNameChance = json[QStringLiteral("patGrfNameChance")].toInt();
	matGrfNameChance = json[QStringLiteral("matGrfNameChance")].toInt();
	fatherNameChance = json[QStringLiteral("fatherNameChance")].toInt();
	patGrmNameChance = json[QStringLiteral("patGrmNameChance")].toInt();
	matGrmNameChance = json[QStringLiteral("matGrmNameChance")].toInt();
	motherNameChance = json[QStringLiteral("motherNameChance")].toInt();
	QJsonObject tmpCL = json[QStringLiteral("ethnicities")].toObject();
	if(!tmpMN.isEmpty()) {
		for(auto it = std::begin(tmpCL); it != std::end(tmpCL); ++it) {
			ethnicities.insert(it.key(),it.value().toInt());
		}
	}
	tmpCL = json[QStringLiteral("characterModifier")].toObject();
	if(!tmpMN.isEmpty()) {
		for(auto it = std::begin(tmpCL); it != std::end(tmpCL); ++it) {
			characterModifier.insert(it.key(),it.value().toVariant());
		}
	}
}

void Culture::fromCbor(const QCborMap &cbor)
{
	QCborArray tmpGC = cbor[QStringLiteral("graphicalCultures")].toArray();
	if(!tmpGC.isEmpty()) {
		for(const auto it : tmpGC) {
			graphicalCultures.push_back(it.toString());
		}
	}
	QCborArray tmpMN = cbor[QStringLiteral("mercenaryNames")].toArray();
	if(!tmpMN.isEmpty()) {
		for(const auto it : tmpMN) {
			mercenaryNames.push_back(it.toString());
		}
	}
	color = cbor[QStringLiteral("color")].toVariant().value<QColor>();
	tmpMN = cbor[QStringLiteral("cadetDynastyNames")].toArray();
	if(!tmpMN.isEmpty()) {
		for(const auto it : tmpMN) {
			mercenaryNames.push_back(it.toString());
		}
	}
	tmpMN = cbor[QStringLiteral("dynastyNames")].toArray();
	if(!tmpMN.isEmpty()) {
		for(const auto it : tmpMN) {
			mercenaryNames.push_back(it.toString());
		}
	}
	tmpMN = cbor[QStringLiteral("maleNames")].toArray();
	if(!tmpMN.isEmpty()) {
		for(const auto it : tmpMN) {
			mercenaryNames.push_back(it.toString());
		}
	}
	tmpMN = cbor[QStringLiteral("femaleNames")].toArray();
	if(!tmpMN.isEmpty()) {
		for(const auto it : tmpMN) {
			mercenaryNames.push_back(it.toString());
		}
	}
	dynastyOfLocationPrefix = cbor[QStringLiteral("dynastyOfLocationPrefix")].toString();
	patronymSuffixMale = cbor[QStringLiteral("patronymSuffixMale")].toString();
	patronymSuffixFemale = cbor[QStringLiteral("patronymSuffixFemale")].toString();
	patronymPrefixMale = cbor[QStringLiteral("patronymPrefixMale")].toString();
	patronymPrefixMaleVowel = cbor[QStringLiteral("patronymPrefixMaleVowel")].toString();
	patronymPrefixFemale = cbor[QStringLiteral("patronymPrefixFemale")].toString();
	patronymPrefixFemaleVowel = cbor[QStringLiteral("patronymPrefixFemaleVowel")].toString();
	grammarTransform = cbor[QStringLiteral("grammarTransform")].toString();
	bastardDynastyPrefix = cbor[QStringLiteral("bastardDynastyPrefix")].toString();
	dynastyNameFirst = cbor[QStringLiteral("dynastyNameFirst")].toBool();
	founderNamedDynasties = cbor[QStringLiteral("founderNamedDynasties")].toBool();
	dynastyTitleNames = cbor[QStringLiteral("dynastyTitleNames")].toBool();
	alwaysUsePatronym = cbor[QStringLiteral("alwaysUsePatronym")].toBool();
	patGrfNameChance = cbor[QStringLiteral("patGrfNameChance")].toInteger();
	matGrfNameChance = cbor[QStringLiteral("matGrfNameChance")].toInteger();
	fatherNameChance = cbor[QStringLiteral("fatherNameChance")].toInteger();
	patGrmNameChance = cbor[QStringLiteral("patGrmNameChance")].toInteger();
	matGrmNameChance = cbor[QStringLiteral("matGrmNameChance")].toInteger();
	motherNameChance = cbor[QStringLiteral("motherNameChance")].toInteger();
	QCborMap tmpCL = cbor[QStringLiteral("ethnicities")].toMap();
	if(!tmpMN.isEmpty()) {
		for(auto it = std::begin(tmpCL); it != std::end(tmpCL); ++it) {
			ethnicities.insert(it.key().toString(),it.value().toInteger());
		}
	}
	tmpCL = cbor[QStringLiteral("characterModifier")].toMap();
	if(!tmpMN.isEmpty()) {
		for(auto it = std::begin(tmpCL); it != std::end(tmpCL); ++it) {
			characterModifier.insert(it.key().toString(),it.value().toVariant());
		}
	}
}

void Culture::toJson(QJsonObject &json) const
{
	json[QStringLiteral("color")] = QJsonValue::fromVariant(color);
	json[QStringLiteral("dynastyOfLocationPrefix")] = dynastyOfLocationPrefix;
	json[QStringLiteral("patronymSuffixMale")] = patronymSuffixMale;
	json[QStringLiteral("patronymSuffixFemale")] = patronymSuffixFemale;
	json[QStringLiteral("patronymPrefixMale")] = patronymPrefixMale;
	json[QStringLiteral("patronymPrefixMaleVowel")] = patronymPrefixMaleVowel;
	json[QStringLiteral("patronymPrefixFemale")] = patronymPrefixFemale;
	json[QStringLiteral("patronymPrefixFemaleVowel")] = patronymPrefixFemaleVowel;
	json[QStringLiteral("grammarTransform")] = grammarTransform;
	json[QStringLiteral("bastardDynastyPrefix")] = bastardDynastyPrefix;
	json[QStringLiteral("dynastyNameFirst")] = dynastyNameFirst;
	json[QStringLiteral("founderNamedDynasties")] = founderNamedDynasties;
	json[QStringLiteral("dynastyTitleNames")] = dynastyTitleNames;
	json[QStringLiteral("alwaysUsePatronym")] = alwaysUsePatronym;
	json[QStringLiteral("patGrfNameChance")] = patGrfNameChance;
	json[QStringLiteral("matGrfNameChance")] = matGrfNameChance;
	json[QStringLiteral("fatherNameChance")] = fatherNameChance;
	json[QStringLiteral("patGrmNameChance")] = patGrmNameChance;
	json[QStringLiteral("matGrmNameChance")] = matGrmNameChance;
	json[QStringLiteral("motherNameChance")] = motherNameChance;
	if(!graphicalCultures.isEmpty()) {
		QJsonArray tmp;
		for(const auto& it : graphicalCultures) {
			tmp.push_back(it);
		}
		json[QStringLiteral("graphicalCultures")] = tmp;
	}
	if(!mercenaryNames.isEmpty()) {
		QJsonArray tmp;
		for(const auto& it : mercenaryNames) {
			tmp.push_back(it);
		}
		json[QStringLiteral("mercenaryNames")] = tmp;
	}
	if(!cadetDynastyNames.isEmpty()) {
		QJsonArray tmp;
		for(const auto& it : cadetDynastyNames) {
			tmp.push_back(it);
		}
		json[QStringLiteral("cadetDynastyNames")] = tmp;
	}
	if(!dynastyNames.isEmpty()) {
		QJsonArray tmp;
		for(const auto& it : dynastyNames) {
			tmp.push_back(it);
		}
		json[QStringLiteral("dynastyNames")] = tmp;
	}
	if(!maleNames.isEmpty()) {
		QJsonArray tmp;
		for(const auto& it : maleNames) {
			tmp.push_back(it);
		}
		json[QStringLiteral("maleNames")] = tmp;
	}
	if(!femaleNames.isEmpty()) {
		QJsonArray tmp;
		for(const auto& it : femaleNames) {
			tmp.push_back(it);
		}
		json[QStringLiteral("femaleNames")] = tmp;
	}
	if(!ethnicities.isEmpty()) {
		QJsonObject tmp;
		for(auto it = std::begin(ethnicities); it != std::end(ethnicities); ++it) {
			tmp.insert(it.key(),it.value());
		}
		json[QStringLiteral("ethnicities")] = tmp;
	}
	if(!characterModifier.isEmpty()) {
		QJsonObject tmp;
		for(auto it = std::begin(characterModifier); it != std::end(characterModifier); ++it) {
			tmp.insert(it.key(),QJsonValue::fromVariant(it.value()));
		}
		json[QStringLiteral("characterModifier")] = tmp;
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
const QStringList& Culture::getCadetDynastyNames() const
{
	return cadetDynastyNames;
}
QStringList& Culture::getCadetDynastyNames()
{
	return cadetDynastyNames;
}
void Culture::setCadetDynastyNames(const QStringList &value)
{
	cadetDynastyNames = value;
}
const QStringList& Culture::getDynastyNames() const
{
	return dynastyNames;
}
QStringList& Culture::getDynastyNames()
{
	return dynastyNames;
}
void Culture::setDynastyNames(const QStringList &value)
{
	dynastyNames = value;
}
const QStringList& Culture::getMaleNames() const
{
	return maleNames;
}
QStringList& Culture::getMaleNames()
{
	return maleNames;
}
void Culture::setMaleNames(const QStringList &value)
{
	maleNames = value;
}
const QStringList& Culture::getFemaleNames() const
{
	return femaleNames;
}
QStringList& Culture::getFemaleNames()
{
	return femaleNames;
}
void Culture::setFemaleNames(const QStringList &value)
{
	femaleNames = value;
}
const QString& Culture::getDynastyOfLocationPrefix() const
{
	return dynastyOfLocationPrefix;
}
QString& Culture::getDynastyOfLocationPrefix()
{
	return dynastyOfLocationPrefix;
}
void Culture::setDynastyOfLocationPrefix(const QString &value)
{
	dynastyOfLocationPrefix = value;
}
const QString& Culture::getPatronymSuffixMale() const
{
	return patronymSuffixMale;
}
QString& Culture::getPatronymSuffixMale()
{
	return patronymSuffixMale;
}
void Culture::setPatronymSuffixMale(const QString &value)
{
	patronymSuffixMale = value;
}
const QString& Culture::getPatronymSuffixFemale() const
{
	return patronymSuffixFemale;
}
QString& Culture::getPatronymSuffixFemale()
{
	return patronymSuffixFemale;
}
void Culture::setPatronymSuffixFemale(const QString &value)
{
	patronymSuffixFemale = value;
}
const QString& Culture::getPatronymPrefixMale() const
{
	return patronymPrefixMale;
}
QString& Culture::getPatronymPrefixMale()
{
	return patronymPrefixMale;
}
void Culture::setPatronymPrefixMale(const QString &value)
{
	patronymPrefixMale = value;
}
const QString& Culture::getPatronymPrefixMaleVowel() const
{
	return patronymPrefixMaleVowel;
}
QString& Culture::getPatronymPrefixMaleVowel()
{
	return patronymPrefixMaleVowel;
}
void Culture::setPatronymPrefixMaleVowel(const QString &value)
{
	patronymPrefixMaleVowel = value;
}
const QString& Culture::getPatronymPrefixFemale() const
{
	return patronymPrefixFemale;
}
QString& Culture::getPatronymPrefixFemale()
{
	return patronymPrefixFemale;
}
void Culture::setPatronymPrefixFemale(const QString &value)
{
	patronymPrefixFemale = value;
}
const QString& Culture::getPatronymPrefixFemaleVowel() const
{
	return patronymPrefixFemaleVowel;
}
QString& Culture::getPatronymPrefixFemaleVowel()
{
	return patronymPrefixFemaleVowel;
}
void Culture::setPatronymPrefixFemaleVowel(const QString &value)
{
	patronymPrefixFemaleVowel = value;
}
const QString& Culture::getGrammarTransform() const
{
	return grammarTransform;
}
QString& Culture::getGrammarTransform()
{
	return grammarTransform;
}
void Culture::setGrammarTransform(const QString &value)
{
	grammarTransform = value;
}
const QString& Culture::getBastardDynastyPrefix() const
{
	return bastardDynastyPrefix;
}
QString& Culture::getBastardDynastyPrefix()
{
	return bastardDynastyPrefix;
}
void Culture::setBastardDynastyPrefix(const QString &value)
{
	bastardDynastyPrefix = value;
}
const QMap<QString,int>& Culture::getEthnicities() const
{
	return ethnicities;
}
QMap<QString,int>& Culture::getEthnicities()
{
	return ethnicities;
}
void Culture::setEthnicities(const QMap<QString,int> &value)
{
	ethnicities = value;
}
const QStringList& Culture::getMercenaryNames() const
{
	return mercenaryNames;
}
QStringList& Culture::getMercenaryNames()
{
	return mercenaryNames;
}
void Culture::setMercenaryNames(const QStringList &value)
{
	mercenaryNames = value;
}
const QVariantMap& Culture::getCharacterModifier() const
{
	return characterModifier;
}
QVariantMap& Culture::getCharacterModifier()
{
	return characterModifier;
}
void Culture::setCharacterModifier(const QVariantMap &value)
{
	characterModifier = value;
}
