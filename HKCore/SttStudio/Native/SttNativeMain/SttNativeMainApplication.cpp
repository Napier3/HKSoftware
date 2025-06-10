#include "SttNativeMainApplication.h"

#ifdef _PSX_OS_CENTOS_
CSttNativeMainApplication::CSttNativeMainApplication(Display *pDisplay):QApplication(pDisplay)
#else
CSttNativeMainApplication::CSttNativeMainApplication(int argc, char *argv[]):QApplication(argc,argv)
#endif
 {

 }

 CSttNativeMainApplication::~CSttNativeMainApplication()
 {

 }


void CSttNativeMainApplication::InitSttMainApp(CXLanguageResourceBase *pLanguage)
 {
 #ifdef _USE_IN_IED_QT5
    QTextCodec *codec = QTextCodec::codecForName("GBK");
    QTextCodec::setCodecForLocale(codec);
 #else
    QTextCodec *codec = QTextCodec::codecForName("GBK");
    QTextCodec::setCodecForLocale(codec);  //zhouhj 20221210
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
 #endif

    CSttXMainAppBase::InitSttXMainApp(pLanguage);
 }

 void CSttNativeMainApplication::ExitSttMainApp()
 {
     CSttXMainAppBase::ExitSttXMainApp();
 }
