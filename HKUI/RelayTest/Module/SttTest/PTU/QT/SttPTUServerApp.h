#ifndef _SttRelayTestServerApp_h__
#define _SttRelayTestServerApp_h__

#include"../../SttTestServerBaseApp.h"
#include <QCoreApplication>


class CSttPTUServerApp : public CSttTestServerBaseApp, public QCoreApplication ,public CLogBase
{
public:
	CSttPTUServerApp(int &argc, char **argv);
	virtual ~CSttPTUServerApp();

public:
	virtual void InitSttTestServerBaseApp();
	virtual void ExitSttTestServerBaseApp();

public:
	virtual void LogString(long nLevel, const CString &strMsg);
	virtual void LogString(long nLevel, const char *strMsg);

signals:

public slots:

};

#endif // _SttRelayTestServerApp_h__
