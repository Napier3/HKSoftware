#ifndef _SttTestCntrApplicationAx_h__
#define _SttTestCntrApplicationAx_h__

#ifdef SttXcmdCh_AxAtsLib

#include "../../Module/SttTestCtrl/SttTestAppBase.h"

#include <QApplication>
#include <QTextCodec>
#include <QSharedMemory>

//2022-09-09  lijunqing
#include "../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"


class CSttTestCntrApplicationAx : public QApplication, public CSttTestAppBase
{
    Q_OBJECT

public:
  CSttTestCntrApplicationAx(int argc, char *argv[]);
  virtual ~CSttTestCntrApplicationAx();
  
  CGbSmartGenWzd *m_pGbSmartGenWzd;

public:

  virtual void InitSttTestApp(CXLanguageResourceBase *pLanguage);
  virtual void ExitSttTestApp();

public:
  virtual BOOL StartSmartTest(const CString& strMacroID);//zhouhj 2023.7.24 返回值为是否执行启动SmartTest操作,如果SmartTest已启动则返回false
  virtual void ExitSmartTest();
  virtual void StartIotProtoServer();
  virtual void ExitIotProtoServer();

};

#endif //SttXcmdCh_AxAtsLib

#endif // MAINWINDOW_H
