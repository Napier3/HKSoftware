#include "SttReportViewHtml.h"

#ifndef STT_NOT_TESTCNTRFRAME
#include "../SttTestCntrFrameBase.h"
#else
#include "../../SttTestSysGlobalPara.h"
#include "../../SttTestResourceMngr/SttTestResourceMngr.h"
#endif

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

#ifndef STT_NOT_TESTCNTRFRAME
	m_bHasInitFinished = false;
	m_pXAddRpt_TestMacroUI = 0;
	m_pXAddRpt_pParent = 0;
	m_bUpdateRptHtml = true;
#endif
}

#ifndef STT_NOT_TESTCNTRFRAME
#ifdef _PSX_QT_LINUX_
void QSttReportViewHtml::showEvent(QShowEvent *event)
{
	InitReportView();
	QWidget::showEvent(event);
}

void QSttReportViewHtml::InitReportView()
{
	if (m_bHasInitFinished)
	{
		return;
	}
	m_nCurrIndex = 0;
	m_bCanExecCmd = FALSE;//dingxy 20250117 �˱���������ΪFALSE����ֹ��Դδ�ܼ��سɹ��ͼ��ر���
	OpenHtmlFile(STT_REPORT_HEAD_HTML_FILE);   //�򿪱���ͷ�ļ�
	//��䱨��
#ifndef STT_NOT_TESTCNTRFRAME
	/*g_theTestCntrFrame->AddMacroTestReport(m_pXAddRpt_TestMacroUI, m_pXAddRpt_pParent
		, m_strXAddRpt_strItemsName, m_strXAddRpt_strItemsID);*/
	//g_theTestCntrFrame->UpdateRptHtml();//dingxy 20240923 showӦ�ø��ݵ�ǰ��Դ���¸��±�������
 	g_theTestCntrFrame->AddMacroTestReport();
	QTimer::singleShot(0, this, SLOT(slot_UpdateRptData()));
#endif
}

void QSttReportViewHtml::slot_UpdateRptData()
{
	if (m_nCurrIndex < 200)
	{
		 m_nCurrIndex++;
		 QTimer::singleShot(10, this, SLOT(slot_UpdateRptData()));
	}
	else
	{
	UpdateReportHead_StartEndTestTime(TRUE, TRUE);//���µ�һ�ε������ǰ�Ĳ��Կ�ʼ����ʱ��
		emit msg_FillReport_HtmlRptData();
	m_bHasInitFinished = true;
	}
}
#endif
void QSttReportViewHtml::XAddMacroTestReport(CSttMacroTestUI_TestMacroUI *pTestMacroUI, CExBaseObject *pParent, const CString &strItemsName, const CString &strItemsID)
{
	m_pXAddRpt_TestMacroUI = pTestMacroUI;
	m_pXAddRpt_pParent = pParent;
	m_strXAddRpt_strItemsName = strItemsName;
	m_strXAddRpt_strItemsID = strItemsID;
}

#endif
void QSttReportViewHtml::OnHtmlLoadFinish(bool b)
{
	//zhouhj 2023.9.26 js��δ���ҵ���Ӧ�ӿں���,��ʱȥ��
//	QueryReportFillMode();

	if (g_nLogDebugInfor)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, "SttReportViewHtml::OnHtmlLoadFinish");
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("**** begin UpdateReportHead"));
	}

	UpdateReportHead(m_pGlobalDatas);

// 	if (g_bIsOpenMacroFromMain)
// 	{//����Ǵ�Main�����򿪵Ĳ��Թ��ܣ������ڼ����걨��ͷ����ܲ��뱨��
// 		//�˴���������ܵ�AddMacroUIReport
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
	
			if(nValue == 0)//20240430 suyang ����m_strValueֵ����ʾ��ӦHTML�����Ϊ0 ��ɾ����Ӧhtml����
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

			if (pszReport != NULL)
			{
				delete[] pszReport;
				pszReport = NULL;
			}
		}
	}
}

void QSttReportViewHtml::UpdateReportHead_StartEndTestTime(BOOL bUpdateStartTime,BOOL bUpdateEndTime)
{
	CString strCurrTestTime;
	//�Ƿ�ʹ���Զ����ʱ�����
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
	pTestAppInfor->m_strValue = _T("2");//20240514 ���ValueֵΪ�յ���UpdateReportHead()��������ɾ���ĺ���������m_bUpdateReportHead�жϣ����з��գ�����ֱ�Ӹ�ֵ
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
#ifdef _PSX_QT_LINUX_
#ifndef STT_NOT_TESTCNTRFRAME
		if (!m_bHasInitFinished)
		{
			pCurrData->m_strValue = m_strStartTestTime;
		}

		m_strStartTestTime = strCurrTestTime;//dingxy 20240924 ��¼����ʱ��
#endif
#endif
		pTestAppInfor->AddNewChild(pCurrData);
	}

	if (bUpdateEndTime)
	{
		pCurrData = new CDvmData;
		pCurrData->m_strID = STT_REPORTHEAD_TestEndTime;
		pCurrData->m_strValue = strCurrTestTime;
#ifdef _PSX_QT_LINUX_
#ifndef STT_NOT_TESTCNTRFRAME
		if (!m_bHasInitFinished)
		{
			pCurrData->m_strValue = m_strEndTestTime;
		}

		m_strEndTestTime = strCurrTestTime;
#endif
#endif
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



	if (pTestAppInfor)
	{
		pTestAppInfor->DeleteAll();
		pTestAppInfor = NULL;
	}
	if (pCurrData)
	{
		pCurrData->DeleteAll();
		pCurrData = NULL;
	}

	if (pNomSettings)
	{
		pNomSettings->DeleteAll();
		pNomSettings = NULL;
	}
	
	oRootHeadRptDatas.DeleteAll();
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
����Ƕ�׵�value������תΪJSON��ʽ��ʱ����Ҫ���������£�
"data": {
	"name": "ͨ��2",    "id": "SV1_I1_Ia1",    "data-type": "Curr",
	"value": "1.000000",    "unit": "A",    "format": "0.000000",  [value���Ը�Ϊval]
	"index": "0",    "time": "0",    "change": "1",
	"value": [
	{
		"name": "��ֵ",   "id": "SV1_I1_Ia1$mag",        "data-type": "FLOAT",
		"value": "0.00"  [value���Ը�Ϊval]
	},
	{
		"name": "�Ȳ�",   "id": "SV1_I1_Ia1$RatError",     "data-type": "FLOAT",
		"value": "0.00",  [value���Ը�Ϊval]
		"value": [
		{
			"name": "��׼ֵ",  "id": "SV1_I1_Ia1$RatError$StdValue",
			"data-type": "FLOAT",            "value": "100.1234"  [value���Ը�Ϊval]
}, 
*/
void QSttReportViewHtml::FillReportDataset(const CString &strParentItemsPath, const CString &strItemID, CDvmDataset *pDataset)
{
	char *pszReport = NULL;

	dvm_get_json_ascii(CDataMngrXmlRWKeys::g_pXmlKeys, pDataset, &pszReport, 0, FALSE);
	FillReportDataset(strParentItemsPath, strItemID, pszReport);

	if (pszReport != NULL)
	{
		delete[] pszReport;
		pszReport = NULL;
	}
}

void QSttReportViewHtml::FillRptMapDatas(CSttRptMapDatas *pRptMapDatas, const CString &strState)
{
	char *pszReport = NULL;

	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nXmlOnlyWrite_Id_Value++;
	pRptMapDatas->GetXml_ASCII(CSttCmdDefineXmlRWKeys::g_pXmlKeys, &pszReport, 0, _JSON_TYPE_);
	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nXmlOnlyWrite_Id_Value--;

	FillRptMapDatas(pszReport, strState);
	
	if (pszReport != NULL)
	{
		delete[] pszReport;
		pszReport = NULL;
	}
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

 void QSttReportViewHtml::MoveRptPos( const CString &strParentItemsPath, const CString &strItemID, const CString &strPos )
 {
	 slot_MoveRptPos(strParentItemsPath,strItemID, strPos);
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
	 
	 if (pszReport != NULL)
	 {
		 delete[] pszReport;
		 pszReport = NULL;
	 }
 }

void QSttReportViewHtml::OpenReportFile(const CString &strReportFile)
{
	OpenHtmlFile(strReportFile);
}

void QSttReportViewHtml::SaveHtmlReportFile(const CString &strHtmlFile)
{
	QWebPage *pg = page();
	QString strHtml = pg->mainFrame()->toHtml();

#ifdef _PSX_QT_LINUX_
	QTextCodec *pOldTextCodec = NULL;
	InitLocalCodec_BeforeReadWrite(strHtmlFile, &pOldTextCodec);

	char* pFilePath = (char*)strHtmlFile.GetString();
	FILE* pFile = fopen(pFilePath, "w");
	
	//2024-6-24 wuxinyi �޸ı������Ϊʱ�����ܻ�ȱʧ���һ��������Ĳ���
	//ԭ������ΪstrHtml���ַ����ȣ����޸�ΪתΪUtf8���ֽڳ��ȣ�
 	QByteArray byteArray = strHtml.toUtf8();
 	fwrite(byteArray, 1, /*strHtml.length()*/byteArray.length(), pFile);

	//fwrite(strHtml.toUtf8(), 1, strHtml.length(), pFile);

	fclose(pFile);

	ResetLocalCodec(pOldTextCodec);
#else
	QFile file(strHtmlFile);
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	file.write(strHtml.toUtf8());
	file.close();
#endif

#ifdef _PSX_QT_LINUX_  //20220509 zhouhj  linux��д�ļ���,��Ҫ����ͬ������
	system("sync");
#endif
}

#ifndef _PSX_QT_LINUX_
#include <QAxObject>
//20230524 ��window�½�html�ļ�ת��Ϊ������ʽ�ļ�,ͨ��ת�����ļ���չ��ʶ��ת�����ļ���ʽ(*.doc *.docx *.pdf)
BOOL HtmlFileTransToOtherFile(const CString &strHtmlFilePath,const CString &strNewFilePath)
{
	QAxObject oWordApp("Word.Application", 0);
	oWordApp.setProperty("Visible", false);
	QAxObject *pWordDocuments = oWordApp.querySubObject("Documents");

	if(!pWordDocuments) 
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("Quering Documents failed."));
		return FALSE;
	}

	//create a new document using the html file as a template
	pWordDocuments->dynamicCall("Add(QString)",strHtmlFilePath);
	QAxObject *pWordDocument=oWordApp.querySubObject("ActiveDocument");

	if(!pWordDocument) 
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("Quering ActiveDocument failed."));
		return FALSE;
	}

	QString strNativeSepNewPath;
	strNativeSepNewPath = QDir::toNativeSeparators(strNewFilePath);
	QVariant oNewFileNamePath(strNativeSepNewPath/*strNewFilePath*/); //���λ�ú�����
	QVariant oFileFormat(1); //�ļ���ʽ  1����doc;16����docx   WdSaveFormat ö�� (Word)
	QVariant oLockComments(false);//���ΪTrue���������ĵ��Ի�ȡע�͡�Ĭ��ֵΪFalse��
	QVariant oPassword("");     //���ô�����
	QVariant oRecent(true);//���ΪTrue�����ĵ���ӵ����ļ����˵������ʹ�õ��ļ��б��С�Ĭ��ֵΪTrue��
	QVariant oWritePassword("");//���ڱ����ĵ����ĵ������ַ���
	QVariant oReadOnlyRecommended(false);//���ΪTrue�������ۺ�ʱ���ĵ���Word��������ֻ��״̬��Ĭ��ֵΪFalse��

	CString strPostfix;
	strPostfix = ParseFilePostfix(strNewFilePath);

	if (strPostfix == _T("docx"))
	{
		QVariant oNewFileFormat(16);
		oFileFormat = oNewFileFormat;
	}
	else if (strPostfix == _T("pdf"))
	{
		QVariant oNewFileFormat(17);
		oFileFormat = oNewFileFormat;
	}

	QAxObject* pResult = pWordDocument->querySubObject("SaveAs(const QVariant&, const QVariant&,const QVariant&, const QVariant&, const QVariant&, const QVariant&,const QVariant&)"
		,oNewFileNamePath, oFileFormat, oLockComments,oPassword, oRecent, oWritePassword, oReadOnlyRecommended);

	//4. exit the word App
	pWordDocument->dynamicCall("Close (boolean)", false);
	pWordDocuments->dynamicCall("Close()");
	oWordApp.dynamicCall("Quit()");
	return TRUE;
}
#endif

BOOL QSttReportViewHtml::SavePdfReportFile(const CString &strPdfFile)
{
	QWebPage *pg = page();
	QString strHtml = pg->mainFrame()->toHtml();

#ifdef _PSX_QT_LINUX_ //��linux��,��֧��ת��
	return FALSE;
#else//window��,�ȴ洢Ϊhtml,��ת��Ϊpdf
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
// 	document.setHtml(strHtml);		//ע��html��QTextEdit�ؼ��л�ȡ��html��ʽ����
// 	document.print(&printer);
// 	document.end();
// 	return TRUE;
#endif
}

BOOL QSttReportViewHtml::SaveWordReportFile(const CString &strWordFile)
{
	QWebPage *pg = page();
	QString strHtml = pg->mainFrame()->toHtml();

#ifdef _PSX_QT_LINUX_ //��linux��,ֻ�ǽ���չ����Ϊ"*.doc"
	QFile file(strWordFile);
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	file.write(strHtml.toUtf8());
	file.close();
	system("sync");
	return TRUE;
#else//window��,�ȴ洢Ϊhtml,��ת��Ϊword,
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

// 	//�滻
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
void QSttReportViewHtml::slot_MoveRptPos( const CString &strParentItemsPath, const CString &strItemID, const CString &strPos )
{
	emit msg_MoveRptPos(QVariant(strParentItemsPath), QVariant(strItemID), QVariant(strPos));
}

