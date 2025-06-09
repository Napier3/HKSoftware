#include "SttReportViewHtml.h"

#ifndef STT_NOT_TESTCNTRFRAME
#include "../SttTestCntrFrameBase.h"
#else
#include "../../SttTestSysGlobalPara.h"
#include "../../SttTestResourceMngr/SttTestResourceMngr.h"
#endif

#include <QDir>

extern long g_nLogDebugInfor;
//extern bool g_bIsOpenMacroFromMain;

#ifndef STT_NOT_TESTCNTRFRAME
extern QSttTestCntrFrameBase *g_theTestCntrFrame;
#endif

QSttReportViewHtml::QSttReportViewHtml(QWidget* parent)
: QSttWebViewBase(parent)
{
	m_pGlobalDatas = NULL;
	m_bUpdateReportHead = TRUE;
}

void QSttReportViewHtml::OnHtmlLoadFinish(bool b)
{
	//zhouhj 2023.9.26 js中未查找到对应接口函数,暂时去掉
//	QueryReportFillMode();

	if (g_nLogDebugInfor)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, "SttReportViewHtml::OnHtmlLoadFinish");
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("**** begin UpdateReportHead"));
	}

	UpdateReportHead(m_pGlobalDatas);

// 	if (g_bIsOpenMacroFromMain)
// 	{//如果是从Main函数打开的测试功能，必须在加载完报告头后才能插入报告
// 		//此处调用主框架的AddMacroUIReport
// 		g_bIsOpenMacroFromMain = FALSE;
// #ifndef STT_NOT_TESTCNTRFRAME
// 		g_theTestCntrFrame->AddMacroTestReport();
// #endif
// 	}
	m_bCanExecCmd = TRUE;
	ExcuteNextCmd();

	if (g_nLogDebugInfor)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("***** end UpdateReportHead"));
	}
}

void QSttReportViewHtml::SetGlobalDatas( CDataGroup *pSttReport )
{
	m_pGlobalDatas = pSttReport;
}

void QSttReportViewHtml::UpdateReportHead( CDataGroup *pSttReportGroup )
{
	if (pSttReportGroup == NULL)
	{
		return;
	}

	SetValues_ReportHead(pSttReportGroup);

	CSttReports oReports;
	CSttReport *pReport = NULL;
	char *pszReport = NULL,*pszGbkString = NULL;
	long nGbkLenth = 0;
	POS pos = pSttReportGroup->GetHeadPosition();
	CDataGroup *p = NULL;
	CString strItemID;
	int nValue;

	while (pos != NULL)
	{
		p = (CDataGroup*)pSttReportGroup->GetNext(pos);

		if (p->GetClassID() == DTMCLASSID_CDATAGROUP)
		{
			oReports.AddReport(p);
			pReport = (CSttReport*)oReports.GetTail();
			ASSERT(pReport);
			pReport->GetXml_ASCII(CSttCmdDefineXmlRWKeys::g_pXmlKeys, &pszReport, 0, _JSON_TYPE_);

// 			if (p->m_strID == "TestAppInfor")
// 			{
// 				CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s"),pszReport);
// 			}
			
			strItemID = pSttReportGroup->m_strID + "$" + p->m_strID;
			
			nValue = p->m_strValue.toInt() ;
	
			if(nValue == 0)//20240430 suyang 根据m_strValue值来显示对应HTML，如果为0 则删除对应html区域
			{
				if (m_bUpdateReportHead)
				{
					DeleteRptHtml("", strItemID);
				}
				
			}
			else
			{
			FillReportData("Table", strItemID, "NORMAL", pszReport);
			}

			
			delete pszReport;
		}
	}
}

void QSttReportViewHtml::UpdateReportHead_StartEndTestTime(BOOL bUpdateStartTime,BOOL bUpdateEndTime)
{
	CString strCurrTestTime;
	//是否使用自定义的时间对象
#ifdef USE_Custom_CDateTime
	CDateTime::GetDateTime_YYYYMMDD_HHMMSS(strCurrTestTime);
#else
	QDateTime current_date_time =QDateTime::currentDateTime();
	strCurrTestTime = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
#endif

	CDataGroup oRootHeadRptDatas;
	oRootHeadRptDatas.m_strID = _T("TestGlobalDatas");
	CDataGroup *pTestAppInfor = new CDataGroup;
	pTestAppInfor->m_strID = _T("TestAppInfor");
	pTestAppInfor->m_strValue = _T("2");//20240514 如果Value值为空的在UpdateReportHead()函数中走删除的函数，如在m_bUpdateReportHead判断，会有分险，所以直接赋值
	CDataGroup *pNomSettings = new CDataGroup;
	pNomSettings->m_strID = _T("NomSettings");
	pNomSettings->m_strValue = _T("2");
	oRootHeadRptDatas.AddNewChild(pTestAppInfor);
	oRootHeadRptDatas.AddNewChild(pNomSettings);
	CDvmData *pCurrData = NULL;
	CString strTemp;


	if (bUpdateStartTime)
	{
		pCurrData = new CDvmData;
		pCurrData->m_strID = STT_REPORTHEAD_TestStartTime;
		pCurrData->m_strValue = strCurrTestTime;
		pTestAppInfor->AddNewChild(pCurrData);
	}

	if (bUpdateEndTime)
	{
		pCurrData = new CDvmData;
		pCurrData->m_strID = STT_REPORTHEAD_TestEndTime;
		pCurrData->m_strValue = strCurrTestTime;
		pTestAppInfor->AddNewChild(pCurrData);
	}

	pCurrData = new CDvmData;
	pCurrData->m_strID = STT_REPORTHEAD_Vnom;
	strTemp.Format("%f", g_oSystemParas.m_fVNom);
	pCurrData->m_strValue = strTemp;
	pNomSettings->AddNewChild(pCurrData);

	pCurrData = new CDvmData;
	pCurrData->m_strID = STT_REPORTHEAD_Inom;
	strTemp.Format("%f", g_oSystemParas.m_fINom);
	pCurrData->m_strValue = strTemp;
	pNomSettings->AddNewChild(pCurrData);

	pCurrData = new CDvmData;
	pCurrData->m_strID = STT_REPORTHEAD_Fnom;
	strTemp.Format("%f", g_oSystemParas.m_fFNom);
	pCurrData->m_strValue = strTemp;
	pNomSettings->AddNewChild(pCurrData);

	pCurrData = new CDvmData;
	pCurrData->m_strID = STT_REPORTHEAD_SureTime;
	strTemp.Format("%f", g_oSystemParas.m_fStabTime);
	pCurrData->m_strValue = strTemp;
	pNomSettings->AddNewChild(pCurrData);

	CString strValue;
	strValue = g_oSttTestResourceMngr.GetCurrModel();
	pTestAppInfor->AddNewData(STT_REPORTHEAD_AppModel,strValue);
	strValue = g_oSttTestResourceMngr.GetCurrSelSN();
	pTestAppInfor->AddNewData(STT_REPORTHEAD_AppSN,strValue);

	m_bUpdateReportHead = FALSE;
	UpdateReportHead(&oRootHeadRptDatas);
	m_bUpdateReportHead = TRUE;
}

void QSttReportViewHtml::SetValues_ReportHead(CDataGroup *pReportHead)
{
	if (pReportHead == NULL)
	{
		return;
	}

	CDataGroup *pNomSettings = (CDataGroup*)pReportHead->FindByID(STT_REPORTHEAD_NomSettings);
	CDataGroup *pTestAppInfor = (CDataGroup*)pReportHead->FindByID(STT_REPORTHEAD_TestAppInfor);
	double dValue = 0.0f;

	if (pNomSettings != NULL)
	{
		dValue = g_oSystemParas.m_fVNom;
		pNomSettings->SetDataValue(STT_REPORTHEAD_Vnom,dValue);
		dValue = g_oSystemParas.m_fINom;
		pNomSettings->SetDataValue(STT_REPORTHEAD_Inom,dValue);
		dValue = g_oSystemParas.m_fFNom;
		pNomSettings->SetDataValue(STT_REPORTHEAD_Fnom,dValue);
		dValue = g_oSystemParas.m_fStabTime;
		pNomSettings->SetDataValue(STT_REPORTHEAD_SureTime,dValue);
	}

	if (pTestAppInfor != NULL)
	{
		dValue = g_oLocalSysPara.m_fAC_CurMax;
		pTestAppInfor->SetDataValue(STT_REPORTHEAD_Imax,dValue);
		dValue = g_oLocalSysPara.m_fAC_VolMax;
		pTestAppInfor->SetDataValue(STT_REPORTHEAD_Vmax,dValue);
		CString strValue;
		strValue = g_oSttTestResourceMngr.GetCurrModel();
		pTestAppInfor->SetDataValue(STT_REPORTHEAD_AppModel,strValue);
		strValue = g_oSttTestResourceMngr.GetCurrSelSN();
		pTestAppInfor->SetDataValue(STT_REPORTHEAD_AppSN,strValue);
	}
}

/*
对于嵌套的value对象，在转为JSON格式的时候，需要做处理，如下：
"data": {
	"name": "通道2",    "id": "SV1_I1_Ia1",    "data-type": "Curr",
	"value": "1.000000",    "unit": "A",    "format": "0.000000",  [value属性改为val]
	"index": "0",    "time": "0",    "change": "1",
	"value": [
	{
		"name": "幅值",   "id": "SV1_I1_Ia1$mag",        "data-type": "FLOAT",
		"value": "0.00"  [value属性改为val]
	},
	{
		"name": "比差",   "id": "SV1_I1_Ia1$RatError",     "data-type": "FLOAT",
		"value": "0.00",  [value属性改为val]
		"value": [
		{
			"name": "标准值",  "id": "SV1_I1_Ia1$RatError$StdValue",
			"data-type": "FLOAT",            "value": "100.1234"  [value属性改为val]
}, 
*/
void QSttReportViewHtml::FillReportDataset(const CString &strParentItemsPath, const CString &strItemID, CDvmDataset *pDataset)
{
	char *pszReport = NULL;

	dvm_get_json_ascii(CDataMngrXmlRWKeys::g_pXmlKeys, pDataset, &pszReport, 0, FALSE);
	FillReportDataset(strParentItemsPath, strItemID, pszReport);

	delete pszReport;
}

void QSttReportViewHtml::FillRptMapDatas(CSttRptMapDatas *pRptMapDatas, const CString &strState)
{
	char *pszReport = NULL;

	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nXmlOnlyWrite_Id_Value++;
	pRptMapDatas->GetXml_ASCII(CSttCmdDefineXmlRWKeys::g_pXmlKeys, &pszReport, 0, _JSON_TYPE_);
	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nXmlOnlyWrite_Id_Value--;

	FillRptMapDatas(pszReport, strState);
	delete pszReport;
}

extern long g_nLogDebugInfor;

void QSttReportViewHtml::InsertRptHtml(const CString &strParentItemsPath, const CString &strItemsID, const char *strGbDatas, const CString &strRptFileData)
{
	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> begin InsertRptHtml >>");	}

	if (strRptFileData.IsEmpty())
	{
		slot_InsertRptHtml(strParentItemsPath, strItemsID, m_strCurrHtmlRptFileData, strGbDatas);  //20230217 zhangyq
	}
	else
	{
		slot_InsertRptHtml(strParentItemsPath, strItemsID, strRptFileData, strGbDatas);  //20230217 zhangyq
	}

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end InsertRptHtml >>");	}
}

void QSttReportViewHtml::UpdateRptHtml(const CString &strParentItemsPath, const CString &strItemsID
									   , const CString &strGbDatas, const CString &strRptFileData)
{
	slot_UpdateRptHtml(strParentItemsPath, strItemsID, strRptFileData, strGbDatas);   //20230217 zhangyq
}

void QSttReportViewHtml::UpdateRptHtml(const CString &strParentItemsPath, const CString &strItemsID
									   , const char *strGbDatas, const CString &strRptFileData)
{
	slot_UpdateRptHtml2(strParentItemsPath, strItemsID, strRptFileData, strGbDatas);  //20230217 zhangyq
}

void QSttReportViewHtml::DeleteRptHtml(const CString &strParentItemsPath, const CString &strItemsID)
{
	slot_DeleteRptHtml(strParentItemsPath, strItemsID);
}

void QSttReportViewHtml::ItemStateChanged(const CString &strParentItemsPath, const CString &strItemID, const CString &strState)
{
	slot_ItemStateChanged(strParentItemsPath, strItemID, strState);
}

void QSttReportViewHtml::FillReportData(const CString &strParentItemsPath, const CString &strItemID, const CString &strState,  char *pszReport)
{
	slot_FillReportData(strParentItemsPath, strItemID, strState, pszReport);
}

void QSttReportViewHtml::FillReportImg(const CString &strParentItemsPath, const CString &strItemID, const CString &strImgBase64)
{
	slot_FillReportImg(strParentItemsPath, strItemID, strImgBase64);
}

 void QSttReportViewHtml::FillReportDataset(const CString &strParentItemsPath, const CString &strItemID, const char *pszDataset)
 {
	slot_FillReportDataset(strParentItemsPath, strItemID, pszDataset);
 }

 void QSttReportViewHtml::FillRptMapDatas(const char *pszRptMapDatas, const CString &strState)
 {
	slot_FillRptMapDatas(pszRptMapDatas, strState);
 }

 void QSttReportViewHtml::QueryReportFillMode()
 {
	slot_QueryReportFillMode();
 }

 void QSttReportViewHtml::ClearRptResults(const CString &strItemsID)
 {
	 slot_ClearRptResults(strItemsID);
 }

 void QSttReportViewHtml::FillReportTitle(const CString &strItemsID,const CString &strGroupData)
 {
	 stt_FillReportTitle(strItemsID,strGroupData);
 }

 void QSttReportViewHtml::FillReportTitle(const CString &strItemsID,const char *pszGroupData)
 {
	 stt_FillReportTitle(strItemsID,pszGroupData);
 }

 void QSttReportViewHtml::FillReportTitle(const CString &strItemsID,CDataGroup *pDataGroup)
 {
	 char *pszReport = NULL;
	 pDataGroup->GetXml_ASCII(CSttCmdDefineXmlRWKeys::g_pXmlKeys, &pszReport, 0, _JSON_TYPE_);
	 FillReportTitle(strItemsID,pszReport);
	 delete pszReport;
 }

void QSttReportViewHtml::OpenReportFile(const CString &strReportFile)
{
	OpenHtmlFile(strReportFile);
}

void QSttReportViewHtml::SaveHtmlReportFile(const CString &strHtmlFile)
{
#ifdef QT_USE_WEBKIT
    QWebPage *pg = page();
	QString strHtml = pg->mainFrame()->toHtml();

#ifdef _PSX_QT_LINUX_
	QTextCodec *pOldTextCodec = NULL;
	InitLocalCodec_BeforeReadWrite(strHtmlFile, &pOldTextCodec);

	char* pFilePath = (char*)strHtmlFile.GetString();
	FILE* pFile = fopen(pFilePath, "w");
	fwrite(strHtml.toUtf8(), 1, strHtml.length(), pFile);
	fclose(pFile);

	ResetLocalCodec(pOldTextCodec);
#else
	QFile file(strHtmlFile);
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	file.write(strHtml.toUtf8());
	file.close();
#endif

#ifdef _PSX_QT_LINUX_  //20220509 zhouhj  linux下写文件后,需要进行同步操作
	system("sync");
#endif

#endif
}

#ifndef _PSX_QT_LINUX_
//#include <QAxObject>
////20230524 在window下将html文件转换为其它格式文件,通过转换后文件扩展名识别转换后文件格式(*.doc *.docx *.pdf)
//BOOL HtmlFileTransToOtherFile(const CString &strHtmlFilePath,const CString &strNewFilePath)
//{
//	QAxObject oWordApp("Word.Application", 0);
//	oWordApp.setProperty("Visible", false);
//	QAxObject *pWordDocuments = oWordApp.querySubObject("Documents");

//	if(!pWordDocuments)
//	{
//		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("Quering Documents failed."));
//		return FALSE;
//	}

//	//create a new document using the html file as a template
//	pWordDocuments->dynamicCall("Add(QString)",strHtmlFilePath);
//	QAxObject *pWordDocument=oWordApp.querySubObject("ActiveDocument");

//	if(!pWordDocument)
//	{
//		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("Quering ActiveDocument failed."));
//		return FALSE;
//	}

//	QString strNativeSepNewPath;
//	strNativeSepNewPath = QDir::toNativeSeparators(strNewFilePath);
//	QVariant oNewFileNamePath(strNativeSepNewPath/*strNewFilePath*/); //存放位置和名称
//	QVariant oFileFormat(1); //文件格式  1——doc;16——docx   WdSaveFormat 枚举 (Word)
//	QVariant oLockComments(false);//如果为True，则锁定文档以获取注释。默认值为False。
//	QVariant oPassword("");     //设置打开密码
//	QVariant oRecent(true);//如果为True，则将文档添加到“文件”菜单上最近使用的文件列表中。默认值为True。
//	QVariant oWritePassword("");//用于保存文档更改的密码字符串
//	QVariant oReadOnlyRecommended(false);//如果为True，则无论何时打开文档，Word都将处于只读状态。默认值为False。

//	CString strPostfix;
//	strPostfix = ParseFilePostfix(strNewFilePath);

//	if (strPostfix == _T("docx"))
//	{
//		QVariant oNewFileFormat(16);
//		oFileFormat = oNewFileFormat;
//	}
//	else if (strPostfix == _T("pdf"))
//	{
//		QVariant oNewFileFormat(17);
//		oFileFormat = oNewFileFormat;
//	}

//	QAxObject* pResult = pWordDocument->querySubObject("SaveAs(const QVariant&, const QVariant&,const QVariant&, const QVariant&, const QVariant&, const QVariant&,const QVariant&)"
//		,oNewFileNamePath, oFileFormat, oLockComments,oPassword, oRecent, oWritePassword, oReadOnlyRecommended);

//	//4. exit the word App
//	pWordDocument->dynamicCall("Close (boolean)", false);
//	pWordDocuments->dynamicCall("Close()");
//	oWordApp.dynamicCall("Quit()");
//	return TRUE;
//}
#endif

BOOL QSttReportViewHtml::SavePdfReportFile(const CString &strPdfFile)
{
#ifdef QT_USE_WEBKIT
    QWebPage *pg = page();
	QString strHtml = pg->mainFrame()->toHtml();

#ifdef _PSX_QT_LINUX_ //在linux下,不支持转换
	return FALSE;
#else//window下,先存储为html,再转换为pdf
	CString strHtmlFilePath;
	strHtmlFilePath = _P_GetBinPath()/*ChangeFilePostfix(strPdfFile,_T("html"))*/;
	strHtmlFilePath += _T("temporary.html");
	QFile file(strHtmlFilePath);
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	file.write(strHtml.toUtf8());
	file.close();
	BOOL bRet = HtmlFileTransToOtherFile(strHtmlFilePath,strPdfFile);
	X_DeleteFile(strHtmlFilePath);
	return bRet;

// 	QPrinter printer(QPrinter::HighResolution);;
// 	printer.setOutputFormat(QPrinter::PdfFormat);
// 	printer.setPageSize(QPrinter::NPaperSize);
// 	printer.setFullPage(true);
// 	printer.setOutputFileName(strPdfFile);
// 	QTextDocument document;
// 	document.setHtml(strHtml);		//注：html是QTextEdit控件中获取的html格式内容
// 	document.print(&printer);
// 	document.end();
// 	return TRUE;
#endif

#else
    return 0;
#endif
}

BOOL QSttReportViewHtml::SaveWordReportFile(const CString &strWordFile)
{
#ifdef QT_USE_WEBKIT
    QWebPage *pg = page();
	QString strHtml = pg->mainFrame()->toHtml();

#ifdef _PSX_QT_LINUX_ //在linux下,只是将扩展名改为"*.doc"
	QFile file(strWordFile);
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	file.write(strHtml.toUtf8());
	file.close();
	system("sync");
	return TRUE;
#else//window下,先存储为html,再转换为word,
	CString strHtmlFilePath;
	strHtmlFilePath = _P_GetBinPath()/*ChangeFilePostfix(strWordFile,_T("html"))*/;
	strHtmlFilePath += _T("temporary.html");
	QFile file(strHtmlFilePath);
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	file.write(strHtml.toUtf8());
	file.close();

	BOOL bRet = HtmlFileTransToOtherFile(strHtmlFilePath,strWordFile);
	X_DeleteFile(strHtmlFilePath);
	return bRet;
#endif

#else
    return 0;
#endif
}

BOOL QSttReportViewHtml::OpenRptFileData(const CString &strFile, const CString &strParentPath, const CString &strItemsID)
{
	//20230217zhangyq

	char *pChar = stt_ui_OpenHtmlFile_GetChar(strFile/*, m_pCurrHtmlRptCmd->m_strCurrRptFileData*/);

	if (pChar != NULL)
	{
		delete pChar;
		return TRUE;
	} 
	else
	{
		return FALSE;
	}

//	BOOL bRet = stt_ui_OpenHtmlFile(strFile, m_pCurrHtmlRptCmd->m_strCurrRptFileData);

// 	if (!bRet)
// 	{
// 		return bRet;
// 	}

// 	//替换
// 	CString strXid;
// 
// 	if (strParentPath.GetLength() > 0)
// 	{
// 		strXid = strParentPath + "$";
// 	}
// 
// 	strXid = strXid + strItemsID;
// 	m_pCurrHtmlRptCmd->m_strCurrRptFileData.Replace("$XID$", strXid);
//
//	return bRet;
}

//HTML ==>> APP
void QSttReportViewHtml::SetReportFillMode(QVariant strRptFillMode)
{
	QString strMsg = strRptFillMode.toString();
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("SetReportFillMode: ") + strMsg);
	SetRptFillModeByID(strMsg);
}

//APP ==>> HTML
void QSttReportViewHtml::slot_InsertRptHtml(const CString &strParentItemsPath, const CString &strItemsID, const CString &strRptHtml, const char *strGbDatas)
{
	emit msg_InsertRptHtml(QVariant(strParentItemsPath), QVariant(strItemsID), QVariant(strRptHtml), QVariant(strGbDatas));
}

void QSttReportViewHtml::slot_UpdateRptHtml(const CString &strParentItemsPath, const CString &strItemsID, const CString &strRptHtml, const CString &strGbDatas)
{
	emit msg_UpdateRptHtml(QVariant(strParentItemsPath), QVariant(strItemsID), QVariant(strRptHtml), QVariant(strGbDatas));
}

void QSttReportViewHtml::slot_UpdateRptHtml2(const CString &strParentItemsPath, const CString &strItemsID, const CString &strRptHtml, const char *strGbDatas)
{
	emit msg_UpdateRptHtml(QVariant(strParentItemsPath), QVariant(strItemsID), QVariant(strRptHtml), QVariant(strGbDatas));
}

void QSttReportViewHtml::slot_DeleteRptHtml(const CString &strParentItemsPath, const CString &strItemsID)
{
	emit msg_DeleteRptHtml(QVariant(strParentItemsPath), QVariant(strItemsID));
}

void QSttReportViewHtml::slot_ItemStateChanged(const CString &strParentItemsPath, const CString &strItemID, const CString &strState)
{
	emit msg_ItemStateChanged(QVariant(strParentItemsPath), QVariant(strItemID), QVariant(strState));
}

void QSttReportViewHtml::slot_FillReportData(const CString &strParentItemsPath, const CString &strItemID, const CString &strState,  char *pszReport)
{
	emit msg_FillReportData(QVariant(strParentItemsPath), QVariant(strItemID), QVariant(strState), QVariant(pszReport));
}

void QSttReportViewHtml::slot_FillReportImg(const CString &strParentItemsPath, const CString &strItemID, const CString &strImgBase64)
{
	emit msg_FillReportImg(QVariant(strParentItemsPath), QVariant(strItemID), QVariant(strImgBase64));
}

void QSttReportViewHtml::slot_FillReportDataset(const CString &strParentItemsPath, const CString &strItemID, const char *pszDataset)
{
	emit msg_FillReportDataset(QVariant(strParentItemsPath), QVariant(strItemID), QVariant(pszDataset));
}

void QSttReportViewHtml::slot_FillRptMapDatas(const char *pszRptMapDatas, const CString &strState)
{
	emit msg_FillRptMapDatas(QVariant(pszRptMapDatas), QVariant(strState));
}

void QSttReportViewHtml::slot_QueryReportFillMode()
{
	emit msg_QueryReportFillMode();
}

void QSttReportViewHtml::slot_ClearRptResults(const CString &strItemsID)
{
	emit msg_ClearRptResults(QVariant(strItemsID));
}

void QSttReportViewHtml::stt_FillReportTitle(const CString &strItemsID,const char *pszGroupData)
{
	emit msg_FillReportTitle(QVariant(strItemsID),QVariant(pszGroupData));
}

void QSttReportViewHtml::stt_FillReportTitle(const CString &strItemsID,const CString &strGroupData)
{
	emit msg_FillReportTitle(QVariant(strItemsID),QVariant(strGroupData));
}
