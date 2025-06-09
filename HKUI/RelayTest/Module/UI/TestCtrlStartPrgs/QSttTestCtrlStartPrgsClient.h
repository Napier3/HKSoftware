#ifndef QSttTestCtrlStartPrgsClient_H
#define QSttTestCtrlStartPrgsClient_H

#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusError>

class QSttTestCtrlStartPrgsClient
{
private:
	explicit QSttTestCtrlStartPrgsClient();
	~QSttTestCtrlStartPrgsClient();


	static long g_nSttTestCtrlStartPrgsClient;
	static QSttTestCtrlStartPrgsClient *g_pQSttTestCtrlStartPrgsClient;
	
public:
	static void Create();
	static void Release();
	
	static void ShowInfor(const QString &strInfor);
	static void Step(long nCurrStep);
	static void SetSteps(long nSteps);
};

#endif // QSttTestCtrlStartPrgsClient_H
