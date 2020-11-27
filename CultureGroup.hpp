#ifndef CULTUREGROUP_HPP
#define CULTUREGROUP_HPP

#include <QStringList>
#include "Culture.hpp"

class CultureGroup
{
private:
	QString name;
	QStringList graphicalCultures;
	QStringList mercenaryNames;
	QMap<QString,Culture> cultures;
public:
	CultureGroup();
	void load(QTextStream& stream);
	void save(QTextStream& stream) const;
	// Getters and setters
	QString& getName();
	const QString& getName() const;
	void setName(const QString &value);
	QStringList &getGraphicalCultures();
	const QStringList &getGraphicalCultures() const;
	void setGraphicalCultures(const QStringList &value);
	QStringList &getMercenaryNames();
	const QStringList &getMercenaryNames() const;
	void setMercenaryNames(const QStringList &value);
	QMap<QString, Culture>& getCultures();
	const QMap<QString, Culture>& getCultures() const;
	void setCultures(const QMap<QString, Culture> &value);
};

QTextStream& operator<<(QTextStream& stream, const CultureGroup& culture);
QTextStream& operator>>(QTextStream& stream, CultureGroup& culture);

#endif // CULTUREGROUP_HPP
