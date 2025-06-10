#ifndef _SttNativeMainApplication_h__
#define _SttNativeMainApplication_h__

#include <QApplication>
 #include <QTextCodec>
 #include <QSharedMemory>
#include "../../Module/Main/SttXMainAppBase.h"

 class CSttNativeMainApplication : public QApplication, public CSttXMainAppBase
 {
     Q_OBJECT

 public:
#ifdef _PSX_OS_CENTOS_
   CSttNativeMainApplication(Display *pDisplay);
#else
   CSttNativeMainApplication(int argc, char *argv[]);
#endif
   virtual ~CSttNativeMainApplication();

  public:
    virtual void InitSttMainApp(CXLanguageResourceBase *pLanguage);
    virtual void ExitSttMainApp();
 };

#endif // MAINWINDOW_H
