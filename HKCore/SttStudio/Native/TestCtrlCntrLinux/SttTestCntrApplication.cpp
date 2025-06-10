#include "SttTestCntrApplication.h"

extern long g_nXSttRcdInitChDvmData_Harm;// = 31;

#ifdef _PSX_OS_CENTOS_
CSttTestCntrApplication::CSttTestCntrApplication(Display *pDisplay):QApplication(pDisplay)
#else
CSttTestCntrApplication::CSttTestCntrApplication(int argc, char *argv[]):QApplication(argc,argv)
#endif
{
	g_nXSttRcdInitChDvmData_Harm = 25; //2022-5-8  lijunqing  //20220511 zhouhj Ŀǰֻ���㵽25��г��,��ʱֻ��ʾ25��
}

CSttTestCntrApplication::~CSttTestCntrApplication()
{

}


void CSttTestCntrApplication::InitSttTestApp(CXLanguageResourceBase *pLanguage)
{
#ifdef USE_IN_Astra_LINUX//zhouhj 2024.4.27 ���ʲ������Բ��ô˷�ʽ
	QTextCodec *pCodecGBK = QTextCodec::codecForName("utf-8");
#else
	QTextCodec *pCodecGBK = QTextCodec::codecForName("GBK");
#endif
	QTextCodec::setCodecForLocale(pCodecGBK);  
    //sun QTextCodec::setCodecForCStrings(pCodecGBK);
    //sun QTextCodec::setCodecForTr(pCodecGBK);
// 	QTextCodec *pCodec_Curr = QTextCodec::codecForLocale();
// 	QTextCodec::setCodecForLocale(pCodecUFT8); 
// 	pCodec_Curr = QTextCodec::codecForLocale();
// 	QTextCodec::setCodecForLocale(pCodecGBK); 
// 	pCodec_Curr = QTextCodec::codecForLocale();

	CSttTestAppBase::InitSttTestApp(pLanguage);
}

void CSttTestCntrApplication::ExitSttTestApp()
{
	CSttTestAppBase::ExitSttTestApp();
}
