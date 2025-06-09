#ifndef _SttTestServerApp_h__
#define _SttTestServerApp_h__

#include <QCoreApplication>
#include"../SttTestServerBaseApp.h"
#include "../../../../Module/Log/LogPrint.h"


class CSttTestServerApp : public CSttTestServerBaseApp, public QCoreApplication ,public CLogBase
{
public:
	CSttTestServerApp(int &argc, char **argv);
	virtual ~CSttTestServerApp();

public:
	virtual void InitSttTestServerBaseApp();
	virtual void ExitSttTestServerBaseApp();

public:
	virtual void LogString(long nLevel, const CString &strMsg);
	virtual void LogString(long nLevel, const char *strMsg);

signals:

public slots:

};

#endif // _SttTestServerApp_h__
