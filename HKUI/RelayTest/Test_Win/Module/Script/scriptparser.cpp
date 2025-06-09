#include "scriptparser.h"
#include <QMapIterator>

ScriptParser::ScriptParser()
{
	m_pScriptEngine = 0;
}

ScriptParser::~ScriptParser()
{

}

void ScriptParser::CreateEngine()
{
	if ( m_pScriptEngine != 0)
	{
		DestroyScriptEngine(  m_pScriptEngine );
		m_pScriptEngine = 0;
	}
	m_pScriptEngine = CreateScriptEngine(LT_JSCRIPT);
}

void ScriptParser::DestroyEngine()
{
	if ( m_pScriptEngine != 0)
	{
		DestroyScriptEngine(  m_pScriptEngine );
		m_pScriptEngine = 0;
	}
}
void ScriptParser::ResetEngine()
{
	if ( m_pScriptEngine != 0)
	{
		ResetScriptEngine(m_pScriptEngine);
	}
}
void ScriptParser::SetScript()
{
	ResetScriptEngine(m_pScriptEngine);
	//LPCTSTR str;
	m_strScript = "var valueA=3;\r\nvar valueB=5;\r\nfunction Caculate(){ return valueA+valueB;}";
	bool ret = LoadScript(m_pScriptEngine, m_strScript.toStdWString().c_str());
}
void ScriptParser::ExecuteScript()
{
	double paramList[1024] = {0};
	int paramCnt = 0;
	bool IsOK = false;
	QString strFuncName = "Caculate";
	double retVal = ExecuteScriptFunction(m_pScriptEngine, strFuncName.toStdWString().c_str(), &paramList[0],  paramCnt, &IsOK );
}
void ScriptParser::SetSettingMap(QMap<QString, QString> settintMap)
{
	m_strScript.clear();
	QMapIterator<QString, QString> i(settintMap);
	while(i.hasNext())
	{
		i.next();
		m_strScript += "var " + i.key() + "=" + i.value() + ";\r\n";
	}
}


double ScriptParser::Caculating(QString str, bool *bOK)
{
	m_strScript += "function Caculate(){ return " + str + ";}";
	ResetScriptEngine(m_pScriptEngine);
	LoadScript(m_pScriptEngine, m_strScript.toStdWString().c_str());
	double paramList[1024] = {0};
	int paramCnt = 0;
	QString strFuncName = "Caculate";
	double retVal = ExecuteScriptFunction(m_pScriptEngine, strFuncName.toStdWString().c_str(), &paramList[0],  paramCnt, bOK );

	return retVal;

}



