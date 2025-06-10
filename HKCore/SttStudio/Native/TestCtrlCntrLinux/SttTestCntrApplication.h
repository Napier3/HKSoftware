#ifndef _SttTestCntrApplication_h__
#define _SttTestCntrApplication_h__

#include "../Module/SttTestCtrl/SttTestAppBase.h"

#include <QApplication>
#include <QTextCodec>
#include <QSharedMemory>

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
  virtual void InitSttTestApp(CXLanguageResourceBase *pLanguage);
  virtual void ExitSttTestApp();
};

#endif // MAINWINDOW_H
