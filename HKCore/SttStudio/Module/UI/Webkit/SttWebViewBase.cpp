#include "SttWebViewBase.h"
#include "../../../../Module/API/FileApi.h"

#include"../../Module/XLangResource_Native.h"

extern long g_nLogDebugInfor;

#ifndef _PSX_QT_LINUX_
QSttWebViewBase::QSttWebViewBase(QWidget* parent)
: QWebView(parent)
#else
QSttWebViewBase::QSttWebViewBase(QWidget* parent)
: QScrollWebView(parent)
#endif
{
	m_pWebPage = new QSttWebPageBase(this); 
	setPage(m_pWebPage); 
    QWebSettings::setMaximumPagesInCache(1);

	connect(page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(populateJavaScriptWindowObject()));
    connect(page()->mainFrame(),SIGNAL(loadFinished(bool)),this,SLOT(slot_loadFinished(bool)));
}

QSttWebViewBase::~QSttWebViewBase()
{
	delete m_pWebPage;
}


void QSttWebViewBase::populateJavaScriptWindowObject()
{
	page()->mainFrame()->addToJavaScriptWindowObject("mainWindow", this);
}

unsigned int QSttWebView_OnHtmlLoadFinish(void *pPara)
{
	QSttWebViewBase *pView = (QSttWebViewBase *)pPara;
	pView->OnHtmlLoadFinish(true);
	return 0;
}

#ifndef STT_NOT_TESTCNTRFRAME
#ifndef _NOT_USE_SttTestCntrThread_
#include "../SttTestCntrThread.h"
#endif
#endif

void QSttWebViewBase::slot_loadFinished(bool b)
{
#ifndef SttTestCntrThread_H
	//QtConcurrent::run(QSttWebView_OnHtmlLoadFinish, this);
	OnHtmlLoadFinish(b);
#else
	g_theSttTestCntrThread->PostThreadMessage(1, (unsigned long)this, (unsigned long)this);
#endif
}

void QSttWebViewBase::OnHtmlLoadFinish(bool b)
{

}

bool QSttWebViewBase::OpenHtmlFile(const CString &strHtmlFile)
{
	m_strHtmlFile = strHtmlFile;//zhouhj 20220322 系统参数等菜单类用于根据该文件名称判别为系统参数、功率档位、直流输出等

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, ">> begin OpenHtmlFile [%s] >>", strHtmlFile.GetString());	}

	CString strPath = stt_ui_GetHtmlFile(strHtmlFile);

	if (!IsFileExist(strPath))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("网页文件(%s)不存在.")*/g_sLangTxt_Native_WebPageNotExst.GetString(),strPath.GetString());
	}

	QUrl url = QUrl::fromLocalFile(strPath);

//  // 设置页面编码
// 	QWebSettings *pSettings = settings(); //设置不起作用,暂时去掉
//  pSettings->setDefaultTextEncoding("utf-8");	
//   setUrl(url);// ??????????????????????????????????????在打开网页时,需增加对之前网页的处理zhouhj 20220220

	load(url);

   if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end OpenHtmlFile >>");	}

   return true;
}

void QSttWebViewBase::ToDvmDataset(QVariant &strParas, CDvmDataset &oDvmDataset)
{
	QByteArray oByteArray = strParas.toByteArray();
	char *pszParasData = oByteArray.data();
	long nLen = oByteArray.size();

	oDvmDataset.SetXml_ASCII(pszParasData, nLen, CDataMngrXmlRWKeys::g_pXmlKeys, _JSON_TYPE_);//zhouhj 20220126 实际网页传出的编码是gbk
}

void QSttWebViewBase::ToDataGroup(QVariant &strParas, CDataGroup &oDataGroup)
{
	QByteArray oByteArray = strParas.toByteArray();
	char *pszParasData = oByteArray.data();
	long nLen = oByteArray.size();

	if (nLen < 10)
	{
		return;
	}

	//oDataGroup.DeleteAll();  //2022-3-16  lijunqing 不删除，只进行赋值
	dvm_IncGroupUseDvmData(CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataGroup oCurr;

	if (*pszParasData == '<')
	{
		oCurr.SetXml_ASCII(pszParasData, nLen, CDataMngrXmlRWKeys::g_pXmlKeys, _PUGI_XML_TYPE_);
	}
	else
	{
		oCurr.SetXml_ASCII(pszParasData, nLen, CDataMngrXmlRWKeys::g_pXmlKeys, _JSON_TYPE_);
	}

//	char *pszDataset = NULL;
//	CDataMngrXmlRWKeys::IncXmlOnlyWrite_Id_Value();
//	oCurr.GetXml_ASCII(CDataMngrXmlRWKeys::g_pXmlKeys, &pszDataset, 0, _JSON_TYPE_);
//	CDataMngrXmlRWKeys::DecXmlOnlyWrite_Id_Value();
//
	oDataGroup.InitDataValues(&oCurr, FALSE);

	dvm_DecGroupUseDvmData(CDataMngrXmlRWKeys::g_pXmlKeys);
}

//APP ==>> HTML

//HTML ==>> APP
void QSttWebViewBase::ShowMsg(QVariant strParas)
{
	QString strMsg = strParas.toString();
	CLogPrint::LogString(XLOGLEVEL_TRACE, strMsg);
//	qDebug() << strMsg;
}

void QSttWebViewBase::ShowMsgEx(QVariant strLevel,QVariant strParas)
{
	long nLevel = strLevel.toInt();
	QString strMsg = strParas.toString();
	
	CLogPrint::LogString(nLevel, strMsg);
//	qDebug() << strMsg;
}
// 
// #ifndef _PSX_QT_LINUX_
// 
// QString QSttWebViewBase::GetCurrentText()
// {
// 	QWebPage* pPage = page();
// 	QWebFrame* pFrame = pPage->mainFrame();
// 	QVariant var = pFrame->evaluateJavaScript("document.activeElement.value");
// 	return var.toString();
// }
// 
// void QSttWebViewBase::CalInputValid()
// {
// 	QWebPage* pPage = page();
// 	QWebFrame* pFrame = pPage->mainFrame();
// 
// 	QVariant var = pFrame->evaluateJavaScript("document.activeElement.attributes.type.value");
// 	QString strlocalName = var.toString();
// 	if(strlocalName == "input" || strlocalName == "text")
// 	{	
// 		var = pFrame->evaluateJavaScript("document.activeElement.id");
// 		QString strID = var.toString();
// 
// 		QString strJS = QString("document.getElementById(\"%1\").getAttribute(\"size\")").arg(strID);
// 		var = pFrame->evaluateJavaScript(strJS);
// 		QString strSize = var.toString();
// 		long nSize = CString_To_long(strSize);
// 
// 		strJS = QString("document.getElementById(\"%1\").getAttribute(\"max\")").arg(strID);
// 		var = pFrame->evaluateJavaScript(strJS);
// 		QString strMax = var.toString();
// 		float fMax = CString_To_double(strMax);
// 
// 		strJS = QString("document.getElementById(\"%1\").getAttribute(\"min\")").arg(strID);
// 		var = pFrame->evaluateJavaScript(strJS);
// 		QString strMin = var.toString();
// 		float fMin = CString_To_double(strMin);
// 
// 		var = pFrame->evaluateJavaScript("document.activeElement.value");
// 		QString strVal = var.toString();
// 		float fVal = CString_To_double(strVal);
// 		if(fVal > fMax)
// 		{
// 			strJS = QString("document.getElementById(\"%1\").value = %2").arg(strID).arg(fMax);
// 			pFrame->evaluateJavaScript(strJS);
// 			strVal = strMax;
// 		}
// 
// 		if(fVal < fMin)
// 		{
// 			strJS = QString("document.getElementById(\"%1\").value = %2").arg(strID).arg(fMin);
// 			pFrame->evaluateJavaScript(strJS);
// 			strVal = strMin;
// 		}
// 
// 		long nIndex = strVal.indexOf('.');
// 		if(nIndex != -1 && strVal.mid(nIndex + 1).length() > nSize)
// 		{
// 			strVal = strVal.mid(0, nIndex + nSize + 1);
// 			strJS = QString("document.getElementById(\"%1\").value = %2").arg(strID).arg(strVal);
// 			pFrame->evaluateJavaScript(strJS);
// 		}
// 	}
// }
// 
// void QSttWebViewBase::keyPressEvent(QKeyEvent* e)
// {
// 	//16777219 回退 
// 	if(e->key() != 16777219 
// 		&& e->key() != '.'
// 		&& e->key() != '-'
// 		&& (e->key() < '0' || e->key() > '9'))
//  	{
//  		return;
//  	}
//  
//  	if(e->key() == '.' && GetCurrentText().indexOf('.') != -1)
//  	{
//  		return;
//  	}
// 
// 	QWebView::keyPressEvent(e);
// 	CalInputValid();
// }
// 
// #endif