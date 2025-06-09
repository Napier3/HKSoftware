#include "SttTestCntrApplication.h"
#include "../../Module/UI/SttTestCntrFrameAPI.h"

#ifdef SttXcmdCh_SttClientSocket
CGbSmartGenWzd *g_theGbSmartGenWzd;

extern long g_nXSttRcdInitChDvmData_Harm;// = 31;

CSttTestCntrApplication::CSttTestCntrApplication(int argc, char *argv[]):QApplication(argc,argv)
{
	m_pGbSmartGenWzd = NULL;
	g_nXSttRcdInitChDvmData_Harm = 25; //2022-5-8  lijunqing  //20220511 zhouhj 目前只计算到25次谐波,暂时只显示25次
}

CSttTestCntrApplication::~CSttTestCntrApplication()
{

}


void CSttTestCntrApplication::InitSttTestApp(CXLanguageResourceBase *pLanguage)
{
#ifdef USE_IN_Astra_LINUX//zhouhj 2024.4.27 国际部多语言采用此方式
	QTextCodec *pCodecGBK = QTextCodec::codecForName("utf-8");
#else
	QTextCodec *pCodecGBK = QTextCodec::codecForName("GBK");
#endif

	QTextCodec::setCodecForLocale(pCodecGBK);  
#ifndef _USE_IN_IED_QT5
    QTextCodec::setCodecForCStrings(pCodecGBK);
	QTextCodec::setCodecForTr(pCodecGBK);
#endif
// 	QTextCodec *pCodec_Curr = QTextCodec::codecForLocale();
// 	QTextCodec::setCodecForLocale(pCodecUFT8); 
// 	pCodec_Curr = QTextCodec::codecForLocale();
// 	QTextCodec::setCodecForLocale(pCodecGBK); 
// 	pCodec_Curr = QTextCodec::codecForLocale();

	CSttTestAppBase::InitSttTestApp(pLanguage);

	//2022-09-09  lijunqing
	m_pGbSmartGenWzd = new CGbSmartGenWzd();
	g_theGbSmartGenWzd = m_pGbSmartGenWzd;
	m_pGbSmartGenWzd->InitGbSmartGenWzd();
}

void CSttTestCntrApplication::ExitSttTestApp()
{
	if (stt_Frame_GbTreeCtrl() != NULL)
	{
		disconnect(stt_Frame_GbTreeCtrl(),SIGNAL(itemChanged(QTreeWidgetItem *, int))
			,stt_Frame_GbTreeCtrl(),SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));
	}

	CSttTestAppBase::ExitSttTestApp();

	delete m_pGbSmartGenWzd;
	m_pGbSmartGenWzd = NULL;
	g_theGbSmartGenWzd = NULL;
	CLogPrint::CloseLogFile();
}

#endif
