#ifndef _SttTestCntrApplication_h__
#define _SttTestCntrApplication_h__

#include "../../Module/SttTestCtrl/SttTestAppBase.h"

#include <QApplication>
#include <QTextCodec>
#include <QSharedMemory>

//2022-09-09  lijunqing
#include "../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"

class CSttTestCntrApplication : public QApplication, public CSttTestAppBase
{
    Q_OBJECT

public:
#ifdef _PSX_OS_CENTOS_
    CSttTestCntrApplication(Display *pDisplay);
#else
    CSttTestCntrApplication(int argc, char *argv[]);
#endif
  virtual ~CSttTestCntrApplication();
  
public:

	CGbSmartGenWzd *m_pGbSmartGenWzd;

  virtual void InitSttTestApp(CXLanguageResourceBase *pLanguage);
  virtual void ExitSttTestApp();
};

#endif // MAINWINDOW_H
