#ifndef CSTTDRIVEROPER_H
#define CSTTDRIVEROPER_H

#include <QObject>
#include <unistd.h>
#include "drv_define.h"

class CSttDriverOper : public QObject
{
	Q_OBJECT

public:
	static void Create(int nfd);
	static void Release();

private:
	explicit CSttDriverOper(QObject *parent = 0);

	static CSttDriverOper *g_pSttDriverOper;
	static long g_nSttDriverOperRef;

//	static int m_nAnalogSync;
//	static unsigned long m_nModuleSet;

public:
	//2019-102  lijq 鍏ㄥ眬鍞