#ifndef INIFLE_H
#define INIFLE_H

#include <QString>
#include <QMap>


class IniFile
{
public:
	static bool writeInit(QString path,QString type_key,QMap<QString, QString> map);
	static bool writeInit(QString path,QString type_key, QString user_key, QString user_value);
	static bool readInit(QString path,QString type_key, QVector<QString> paraVector, QMap<QString,QString	> &map);
	static bool readInit(QString path,QString type_key, QString user_key, QString &user_value);
	static void setValue(QString path,QString type_key,QString user_key,QString &user_value,int &the_Value);
	static void setValue(QString path,QString type_key,QString user_key,QString &user_value,float &the_Value);
};

#endif
