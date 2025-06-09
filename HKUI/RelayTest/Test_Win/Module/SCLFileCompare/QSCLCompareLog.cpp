#include "QSCLCompareLog.h"

QSCLCompareLog::QSCLCompareLog(QWidget *parent /* = 0 */, Qt::WFlags flags /* = 0 */)
{

};

QSCLCompareLog::~QSCLCompareLog()
{

};

void QSCLCompareLog::LogString(long nLevel, const char *strMsg)
{
	LogString(nLevel, CString(strMsg));
}

void QSCLCompareLog::LogString(long nLevel, const CString &strMsg)
{
	if (strMsg.IsEmpty())
	{
		return;
	}

	QString strInfo;
	if(nLevel == XLOGLEVEL_EXCEPTION || nLevel == XLOGLEVEL_ERROR)
	{
		strInfo = QString("%1").arg(strMsg);
	}
	else
	{
		strInfo = QString("%1").arg(strMsg);
	}

	m_strListInfo.append(strInfo);

	
}