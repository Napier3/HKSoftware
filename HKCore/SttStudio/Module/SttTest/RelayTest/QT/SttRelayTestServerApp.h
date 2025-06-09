#ifndef _SttRelayTestServerApp_h__
#define _SttRelayTestServerApp_h__

#include <QCoreApplication>
#include"../../SttTestServerBaseApp.h"
#include "../../../../../Module/Log/LogPrint.h"


class CSttRelayTestServerApp : public CSttTestServerBaseApp, public QCoreApplication ,public CLogBase
{
public:
	CSttRelayTestServerApp(int &argc, char **argv);
    virtual ~CSttRelayTestServerApp();

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
