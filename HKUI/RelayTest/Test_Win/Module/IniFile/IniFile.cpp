#include "IniFile.h"
#include <QSettings>
#include <QVector>

bool IniFile::writeInit(QString path, QString type_key, QString user_key, QString user_value)
{
	if(path.isEmpty() || user_key.isEmpty() || type_key.isEmpty())
	{
		return false;
	}
	else
	{
		//创建配置文件操作对象
		QSettings *config = new QSettings(path, QSettings::IniFormat);
		config->setIniCodec("GBK");
		//将信息写入配置文件
		config->beginGroup(type_key);
		config->setValue(user_key, user_value);
		config->endGroup();

		return true;
	} 
}

bool IniFile::writeInit( QString path,QString type_key,QMap<QString, QString> map )
{
	if(path.isEmpty() || map.isEmpty())
	{
		return false;
	}
	else
	{
		//创建配置文件操作对象
		QSettings *config = new QSettings(path, QSettings::IniFormat);
		config->setIniCodec("GBK");
		//将信息写入配置文件
		config->beginGroup(type_key);
		QMapIterator<QString, QString> i(map);
		while (i.hasNext()) 
		{
			i.next();
			config->setValue(i.key(), i.value());

		}
		config->endGroup();

		return true;
	} 
}

bool IniFile::readInit( QString path,QString type_key, QVector<QString> paraVector,QMap<QString, QString> &map )
{
	map.clear();
	if(path.isEmpty() )
	{
		return false;
	}
	else
	{
		//创建配置文件操作对象
		QSettings *config = new QSettings(path, QSettings::IniFormat);
		config->setIniCodec("GBK");

		QString user_value;
		for (int i=0;i<paraVector.size();i++)
		{
			user_value = config->value(type_key+ QString("/") + paraVector.at(i)).toString();
			map.insert(paraVector.at(i),user_value);
		}

		return true;
	}  
}

bool IniFile::readInit( QString path,QString type_key, QString user_key, QString &user_value )
{
	user_value = QString("");
	if(path.isEmpty() || user_key.isEmpty() || type_key.isEmpty())
	{
		return false;
	}
	else
	{
		//创建配置文件操作对象
		QSettings *config = new QSettings(path, QSettings::IniFormat);
		config->setIniCodec("GBK");
		//读取用户配置信息
		
		user_value = config->value(type_key +  QString("/") + user_key).toString();
		return true;
	}  
}

void IniFile::setValue( QString path,QString type_key,QString user_key,QString &user_value,int &the_Value )
{
	user_value.clear();
	bool is_read= false;
	is_read = IniFile::readInit(path,type_key, user_key, user_value);
	if(is_read)
	{
		if(user_value.isEmpty())
		{
			the_Value=0;
		}
		else
		{
			the_Value = user_value.toInt();
		}
	}
	else
	{
		the_Value=0;
	}
}

void IniFile::setValue( QString path,QString type_key,QString user_key,QString &user_value,float &the_Value )
{
	user_value.clear();
	bool is_read= false;
	is_read = IniFile::readInit(path,type_key, user_key, user_value);
	if(is_read)
	{
		if(user_value.isEmpty())
		{
			the_Value=0;
		}
		else
		{
			the_Value = user_value.toFloat();
		}
	}
	else
	{
		the_Value=0;
	}
}

