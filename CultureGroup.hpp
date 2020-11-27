#ifndef CULTUREGROUP_HPP
#define CULTUREGROUP_HPP

#include <QStringList>
#include "Culture.hpp"

class CultureGroup
{
private:
	QStringList graphical_cultures;
	QStringList mercenary_names;
	QMap<QString,Culture> cultures;
public:
	CultureGroup();
	void load(QTextStream& stream);
	void save(QTextStream& stream) const;
};

QTextStream& operator<<(QTextStream& stream, const CultureGroup& culture);
QTextStream& operator>>(QTextStream& stream, CultureGroup& culture);

#endif // CULTUREGROUP_HPP
