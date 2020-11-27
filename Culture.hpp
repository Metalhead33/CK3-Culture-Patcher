#ifndef CULTURE_HPP
#define CULTURE_HPP

#include <QVariantMap>
#include <QStringList>
#include <QColor>
#include <QMap>
#include <QTextStream>

class Culture
{
private:
	QStringList graphical_cultures;
	QColor color;
	QStringList cadet_dynasty_names;
	QStringList dynasty_names;
	QStringList male_names;
	QStringList female_names;
	QString dynasty_of_location_prefix;
	QString patronym_suffix_male;
	QString patronym_suffix_female;
	QString patronym_prefix_male;
	QString patronym_prefix_male_vowel;
	QString patronym_prefix_female;
	QString patronym_prefix_female_vowel;
	QString grammar_transform;
	QString bastard_dynasty_prefix;
	bool dynasty_name_first = false;
	bool founder_named_dynasties = false;
	bool dynasty_title_names = false;
	bool always_use_patronym = false;
	int pat_grf_name_chance = 0;
	int mat_grf_name_chance = 0;
	int father_name_chance = 0;
	int pat_grm_name_chance = 0;
	int mat_grm_name_chance = 0;
	int mother_name_chance = 0;
	QMap<QString,int> ethnicities;
	QStringList mercenary_names;
	QVariantMap character_modifier;
public:
	Culture();
	void load(QTextStream& stream);
	void save(QTextStream& stream) const;
};

QTextStream& operator<<(QTextStream& stream, const Culture& culture);
QTextStream& operator>>(QTextStream& stream, Culture& culture);

#endif // CULTURE_HPP
