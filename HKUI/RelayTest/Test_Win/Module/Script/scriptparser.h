#ifndef SCRIPTPARSER_H
#define SCRIPTPARSER_H

#include <QMap>
#include "ScriptEngine.h"
#include <QString>

class ScriptParser
{

public:
	ScriptParser();
	~ScriptParser();

public:
	void CreateEngine();
	void DestroyEngine();
	void ResetEngine();
	void SetScript();
	void ExecuteScript();
	void SetSettingMap(QMap<QString, QString> settintMap);
	double Caculating(QString str, bool *bOK);

private:
	void* m_pScriptEngine;
	QMap<QString, QString> m_SettingMap;
	QString m_strScript;
	
};

#endif // SCRIPTPARSER_H
