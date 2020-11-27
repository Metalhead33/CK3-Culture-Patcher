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
	QStringList graphicalCultures;
	QColor color;
	QStringList cadetDynastyNames;
	QStringList dynastyNames;
	QStringList maleNames;
	QStringList femaleNames;
	QString dynastyOfLocationPrefix;
	QString patronymSuffixMale;
	QString patronymSuffixFemale;
	QString patronymPrefixMale;
	QString patronymPrefixMaleVowel;
	QString patronymPrefixFemale;
	QString patronymPrefixFemaleVowel;
	QString grammarTransform;
	QString bastardDynastyPrefix;
	bool dynastyNameFirst = false;
	bool founderNamedDynasties = false;
	bool dynastyTitleNames = false;
	bool alwaysUsePatronym = false;
	int patGrfNameChance = 0;
	int matGrfNameChance = 0;
	int fatherNameChance = 0;
	int patGrmNameChance = 0;
	int matGrmNameChance = 0;
	int motherNameChance = 0;
	QMap<QString,int> ethnicities;
	QStringList mercenaryNames;
	QVariantMap characterModifier;
public:
	Culture();
	void load(QTextStream& stream);
	void save(QTextStream& stream) const;
	// Getters and setters
	const QStringList& getGraphicalCultures() const;
	QStringList& getGraphicalCultures();
	void setGraphicalCultures(const QStringList &value);
	const QStringList& getCadetDynastyNames() const;
	QStringList& getCadetDynastyNames();
	void setCadetDynastyNames(const QStringList &value);
	const QStringList& getDynastyNames() const;
	QStringList& getDynastyNames();
	void setDynastyNames(const QStringList &value);
	const QStringList& getMaleNames() const;
	QStringList& getMaleNames();
	void setMaleNames(const QStringList &value);
	const QStringList& getFemaleNames() const;
	QStringList& getFemaleNames();
	void setFemaleNames(const QStringList &value);
	const QString& getDynastyOfLocationPrefix() const;
	QString& getDynastyOfLocationPrefix();
	void setDynastyOfLocationPrefix(const QString &value);
	const QString& getPatronymSuffixMale() const;
	QString& getPatronymSuffixMale();
	void setPatronymSuffixMale(const QString &value);
	const QString& getPatronymSuffixFemale() const;
	QString& getPatronymSuffixFemale();
	void setPatronymSuffixFemale(const QString &value);
	const QString& getPatronymPrefixMale() const;
	QString& getPatronymPrefixMale();
	void setPatronymPrefixMale(const QString &value);
	const QString& getPatronymPrefixMaleVowel() const;
	QString& getPatronymPrefixMaleVowel();
	void setPatronymPrefixMaleVowel(const QString &value);
	const QString& getPatronymPrefixFemale() const;
	QString& getPatronymPrefixFemale();
	void setPatronymPrefixFemale(const QString &value);
	const QString& getPatronymPrefixFemaleVowel() const;
	QString& getPatronymPrefixFemaleVowel();
	void setPatronymPrefixFemaleVowel(const QString &value);
	const QString& getGrammarTransform() const;
	QString& getGrammarTransform();
	void setGrammarTransform(const QString &value);
	const QString& getBastardDynastyPrefix() const;
	QString& getBastardDynastyPrefix();
	void setBastardDynastyPrefix(const QString &value);
	const QMap<QString,int>& getEthnicities() const;
	QMap<QString,int>& getEthnicities();
	void setEthnicities(const QMap<QString,int> &value);
	const QStringList& getMercenaryNames() const;
	QStringList& getMercenaryNames();
	void setMercenaryNames(const QStringList &value);
	const QVariantMap& getCharacterModifier() const;
	QVariantMap& getCharacterModifier();
	void setCharacterModifier(const QVariantMap &value);
};

QTextStream& operator<<(QTextStream& stream, const Culture& culture);
QTextStream& operator>>(QTextStream& stream, Culture& culture);

#endif // CULTURE_HPP
