#ifndef CULTUREGROUP_HPP
#define CULTUREGROUP_HPP

#include <QStringList>
#include "Culture.hpp"

class CultureGroup
{
private:
	QString name;
	QStringList graphicalCultures;
	QDoubleStringList mercenaryNames;
	QMap<QString,Culture> cultures;
public:
	CultureGroup();
	void load(QTextStream& stream);
	void save(QTextStream& stream) const;
	// JSON and CBOR
	void fromJson(const QJsonObject& json);
	void fromCbor(const QCborMap& cbor);
	void toJson(QJsonObject& json) const;
	QJsonObject toJson() const;
	void toCbor(QCborMap& cbor) const;
	QCborMap toCbor() const;
	// Getters and setters
	QString& getName();
	const QString& getName() const;
	void setName(const QString &value);
	QStringList &getGraphicalCultures();
	const QStringList &getGraphicalCultures() const;
	void setGraphicalCultures(const QStringList &value);
	QDoubleStringList &getMercenaryNames();
	const QDoubleStringList &getMercenaryNames() const;
	void setMercenaryNames(const QDoubleStringList &value);
	QMap<QString, Culture>& getCultures();
	const QMap<QString, Culture>& getCultures() const;
	void setCultures(const QMap<QString, Culture> &value);
};

QTextStream& operator<<(QTextStream& stream, const CultureGroup& culture);
QTextStream& operator>>(QTextStream& stream, CultureGroup& culture);

#endif // CULTUREGROUP_HPP
