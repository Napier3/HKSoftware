#ifndef QSCLCOMPARELOG
#define QSCLCOMPARELOG
#include <QWidget>
#include <QTextEdit>
#include <QStringList>
#include "..\..\Log\LogPrint.h"


class QSCLCompareLog :public QTextEdit,public CLogBase
{
public:
	QSCLCompareLog(QWidget *parent = 0, Qt::WFlags flags = 0);
	virtual~QSCLCompareLog();

	QStringList  m_strListInfo;
	virtual void LogString(long nLevel, const CString &strMsg);
	virtual void LogString(long nLevel, const char *strMsg);



protected:

private:
};

#endif
