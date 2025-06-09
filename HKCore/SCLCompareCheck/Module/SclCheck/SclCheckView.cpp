// SclFileFormView.cpp : 实现文件
//

#include "stdafx.h"
#include "SclCheckView.h"
//#include "..\SCLCompareCheckDev.h"
#include "WaitingTimeDlg.h"
#include "..\..\Module\SclCheckDataMngr\TinySCLRead.h"


IMPLEMENT_DYNCREATE(CSclCheckView, CFormView)

bool CSclCheckView::UTF8ToMultiByte(CString &srcStr)
{
	signed int iTextLen = 0;
	unsigned short wszGBK[256] = {0};

	memset(wszGBK, 0, 256);

	iTextLen = MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)srcStr, -1, NULL,0); 
	memset(wszGBK, 0, iTextLen * 2 + 2); 
	MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)srcStr, -1, (LPWSTR)wszGBK, iTextLen); 

	iTextLen = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, NULL, 0, NULL, NULL); 
	WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, (LPSTR)(LPCSTR)srcStr, iTextLen, NULL, NULL); 

	return true;
}

CSclCheckView::CSclCheckView()
	: CFormView(CSclCheckView::IDD)
{
	m_pSclSchemaView = NULL;
	m_pDLT860TempsView = NULL;
	pProjAppModelView = NULL;
	m_pSclVirLoopView = NULL;
	m_pSclCheckObject = NULL;
	m_pTemplateFile1396 = NULL;
	m_pSCLTestObjectFile = NULL;
	m_pSCLDataTypeTemplates = NULL;
	m_pSclChStation = NULL;
	m_pStrSclPath = NULL;
// 	theApp.m_pMyMainFrame->InitCheckOperatRibbon();
// 	theApp.m_pMyMainFrame->InitAddTemplatesRibbon();

	m_pTemplateFile1396 = new CTemplateFile1396();
	CString strTmpPath = _P_GetBinPath();
	strTmpPath += "国网1396标准模板文件\\TemplatesSGCC.xml";
	m_pTemplateFile1396->OpenTemplateFile1396(strTmpPath);
}

CSclCheckView::~CSclCheckView()
{
	m_mapCheck.clear();
	if (m_pSclCheckObject != NULL)
	{
		delete m_pSclCheckObject;
	}

	if (m_pTemplateFile1396 != NULL)
	{
		delete m_pTemplateFile1396;
	}

	if (m_pSCLTestObjectFile!=NULL)
	{
		delete m_pSCLTestObjectFile;
	}

	if (m_pSCLDataTypeTemplates!=NULL)
	{
		delete m_pSCLDataTypeTemplates;
	}
}

void CSclCheckView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSclCheckView, CFormView)
	ON_WM_SIZE()
	ON_WM_CREATE()

	ON_MESSAGE(WM_XMLCHECKCLASSID_OBJECT, &CSclCheckView::OnFinishSchemaCheck)
END_MESSAGE_MAP()


#ifdef _DEBUG
void CSclCheckView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSclCheckView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);

}
#endif

CSclCheckDoc* CSclCheckView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSclCheckDoc)));
	return (CSclCheckDoc*)m_pDocument;
}
#endif //_DEBUG

void CSclCheckView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	if (!::IsWindow(m_tabPara.m_hWnd))
	{
		return;
	}

	CRect rcClient;
	GetClientRect(&rcClient);
	m_tabPara.MoveWindow(0, 0, rcClient.Width(), rcClient.Height());

}

void CSclCheckView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
}


BOOL CSclCheckView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CFormView::PreCreateWindow(cs);
}

int CSclCheckView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CCreateContext *pContext = (CCreateContext*) lpCreateStruct->lpCreateParams;

	m_tabPara.Create(CMFCTabCtrl::STYLE_3D_ROUNDED ,CRect(0, 0, 0, 0), this, 1000, CMFCTabCtrl::LOCATION_TOP);

	m_pSclSchemaView = new CSclCheckCtrlView();
	if (m_pSclSchemaView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, 
		CRect(0, 0, 0, 0), &m_tabPara, AFX_IDW_PANE_FIRST, pContext))
	{
		m_tabPara.AddTab(m_pSclSchemaView, _T("Schema语法检查结果"));
	}

	m_pDLT860TempsView = new CSclCheckCtrlView();
	if (m_pDLT860TempsView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, 
		CRect(0, 0, 0, 0), &m_tabPara, AFX_IDW_PANE_FIRST+1, pContext))
	{
		m_tabPara.AddTab(m_pDLT860TempsView, _T("DL/T860数据类型模板库检查结果"));
	}

	pProjAppModelView = new CSclCheckCtrlView();
	if (pProjAppModelView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, 
		CRect(0, 0, 0, 0), &m_tabPara, AFX_IDW_PANE_FIRST+2, pContext))
	{
		m_tabPara.AddTab(pProjAppModelView, _T("工程应用模型规范性检查结果"));
	}

		m_pSclVirLoopView = new CSclCheckCtrlView();
	if (m_pSclVirLoopView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, 
		CRect(0, 0, 0, 0), &m_tabPara, AFX_IDW_PANE_FIRST+3, pContext))
	{
		m_tabPara.AddTab(m_pSclVirLoopView, _T("虚回路规范性检查结果"));
	}

	m_tabPara.EnableTabSwap(TRUE);//可以拖拽

	CArray<COLORREF,COLORREF> arColors;

	arColors.Add(RGB (121, 210, 231));
	arColors.Add(RGB (190, 218, 153));
	arColors.Add(RGB (255, 170, 100));
	arColors.Add(RGB (255, 255, 0));

	m_tabPara.EnableAutoColor(TRUE);
	m_tabPara.SetAutoColors(arColors);

	return 0;
}

void CSclCheckView::ShowAllGridDatas()
{
	m_pSclSchemaView->ShowGridDatas(&m_oSchemaResultsRec);
	m_pDLT860TempsView->ShowGridDatas(&m_oDLT860TmpsResultsRec);
	pProjAppModelView->ShowGridDatas(&m_oProjAppModelResultsRec);
	m_pSclVirLoopView->ShowGridDatas(&m_oVirLoopResultsRec);
}

////////////////////////////////////////////////Schema语法检查 部分函数//////////////////////////////////////////////////////////////
void CSclCheckView::StartSchemaCheck(CSchemaChecks *pSchemaChecks)
{
	CSchemaCheckObject *pSchemaCheckObject = (CSchemaCheckObject*)pSchemaChecks->FindByID("schema-check");

	if (pSchemaCheckObject == NULL)
	{
		return;
	}

	if (!pSchemaCheckObject->m_nChoose)
	{
		return;
	}

	m_strSchemaPath = _P_GetBinPath();
	m_strSchemaPath += pSchemaCheckObject->m_strVertionType;
	m_strSchemaPath += "\\SCL.xsd";

	if (m_pSclCheckObject == NULL)
	{
		m_pSclCheckObject = new CXmlCheckObject;
	}

	m_pSclCheckObject->m_bDomType = (pSchemaCheckObject->m_strCheckType == "DOM");
	
	m_pSclCheckObject->m_pResultsRec = &m_oSchemaResultsRec;
	m_pSclCheckObject->SchemaCheckMap(m_strSchemaPath,m_strSclFilePath);
	CWaitingTimeDlg dlg;
	dlg.m_strMsgDesc = "正在检查Schema语法错误 , 需要等待一段时间";
	dlg.DoModal();
	m_pSclSchemaView->ShowGridDatas(&m_oSchemaResultsRec);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////DL/T860数据类型模板一致性检查 部分函数及成员变量///////////////////////////////////////////////////////////////
BOOL CSclCheckView::BeCheckThisObject(CCheckObject *pCheckObject ,CString &strObjectID)
{
	strObjectID = "";
	if (pCheckObject == NULL)
	{
		return TRUE;
	} 
	else
	{
		strObjectID = pCheckObject->m_strErrorType;
		return pCheckObject->m_nChoose;
	}
}

void CSclCheckView::AddCheckResultDLT860Tmps(CString strErrorType ,CString strText ,CString strErrorPos)
{
	CResultRec *pResultRec = new CResultRec();
	m_oDLT860TmpsResultsRec.AddNewChild(pResultRec);
	pResultRec->m_strErrorText = strText;
	pResultRec->m_strErrorPos = strErrorPos;
	if (strErrorType == "tips")
	{
		m_oDLT860TmpsResultsRec.m_nAllTipIndex++;
		pResultRec->m_strErrorType.Format("提示 %d" , m_oDLT860TmpsResultsRec.m_nAllTipIndex);
		pResultRec->m_nTipIndex = 1;	
	}
	else if (strErrorType == "warning")
	{
		m_oDLT860TmpsResultsRec.m_nAllWarningIndex++;
		pResultRec->m_strErrorType.Format("告警%d" , m_oDLT860TmpsResultsRec.m_nAllWarningIndex);
		pResultRec->m_nWarningIndex = 1;	
	}
	else if (strErrorType == "error")
	{
		m_oDLT860TmpsResultsRec.m_nAllErrorIndex++;
		pResultRec->m_strErrorType.Format("错误%d" , m_oDLT860TmpsResultsRec.m_nAllErrorIndex);
		pResultRec->m_nErrorIndex = 1;
	}
	else if (strErrorType == "fatalerror")
	{
		m_oDLT860TmpsResultsRec.m_nAllFatalErrorIndex++;
		pResultRec->m_strErrorType.Format("严重%d" , m_oDLT860TmpsResultsRec.m_nAllFatalErrorIndex);
		pResultRec->m_nFatalErrorIndex = 1;	
	}
}

void CSclCheckView::CheckLNodeTypeOfGDW1396(CLNodeType *pObjDataType ,CExBaseList *pTemplates1396 ,CDLT860ModelChecks *pDLT860ModelChecks)
{
	CString strObjectID;
	CCheckObject *pCheckObject = NULL;
	////////////////第一步：准备好模板和SCD文件的DataTypeTemplates对象//////////////////////////////////////////////////
	CExBaseList *pTestObjectTemplates = (CExBaseList*)m_pSCLTestObjectFile->FindByID("DataTypeTemplates");
	CLNodeTypeT *pTemplate = NULL;
	pTemplate = (CLNodeTypeT*)pTemplates1396->FindByID(pObjDataType->m_strLnClass);
	CString strErrorText;
	CString strDOValueName;//记录DO 中name属性的名称，以便去掉末尾数组部分
	bool bSmb = false;//记录函数转换后名称末尾中是否包含数字
	///////////////第二步：在模板库中查找本次测试LNodeType的lnClass//////////////////////////////////////////////////////////
	if (pTemplate == NULL)
	{
		pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("lnClass-illegal");

		if (BeCheckThisObject(pCheckObject ,strObjectID))
		{
			strErrorText.Format("LNodeType: id=%s,lnClass=%s 采用了未经标准定义的逻辑节点类 , 此类不得私自扩充;",pObjDataType->m_strID ,pObjDataType->m_strLnClass);
			AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjDataType->m_strErrorPos);
		}
		return;
	}
	///////////////第三步：找到SCD文件本LNodeType的DO对象///////////////////////////////////////////////////////////////////	
	POS objPos = pObjDataType->GetHeadPosition();
	POS tmpPos = pTemplate->GetHeadPosition();
	POS SymbolPos = NULL;
	if (objPos == NULL)
	{
		strErrorText.Format("LNodeType: id=%s,lnClass=%s 逻辑节点下未定义任何DO;",pObjDataType->m_strID ,pObjDataType->m_strLnClass);
		AddCheckResultDLT860Tmps("error" , strErrorText ,pObjDataType->m_strErrorPos);
		return;
	}
	CDOValue *pObjDOValue = NULL;
	CDOValueT *pTmpDOValue = NULL;
	CExBaseList *pDOType = NULL;
	//////////////第四步：以模板库中所有预定义DO顺序为基准，循环遍历，保证M项在SCD文件中必须被定义;////////////////////////////////////////////////
	while(tmpPos!=NULL)
	{
		pTmpDOValue = (CDOValueT*)pTemplate->GetNext(tmpPos);
		if (objPos == NULL)
		{
			if (pTmpDOValue->m_strMop == "M")
			{
				pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DO-M");

				if (BeCheckThisObject(pCheckObject  ,strObjectID))
				{
					pObjDOValue = (CDOValue*)pObjDataType->FindByID(pTmpDOValue->m_strID);

					if (pObjDOValue == NULL)
					{
						strErrorText.Format("LNodeType: id=%s,lnClass=%s 中缺少必备DO: name=%s ;",pObjDataType->m_strID ,pObjDataType->m_strLnClass ,pTmpDOValue->m_strID);
						AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjDataType->m_strErrorPos);
					}
				}
			} 
			continue;
		}

		SymbolPos = objPos;
		pObjDOValue = (CDOValue*)pObjDataType->GetNext(objPos);
		strDOValueName = pObjDOValue->m_strID;
		bSmb = CheckTailDigital(pTmpDOValue->m_strID);
		if (!bSmb)
		{
			DelTailDigtal(&strDOValueName);
		}
		///////////////////////////////////根据DO 的type查找对应cdc,保证使用的cdc与标准一致///////////////////////////////////////////////////////////////////////////
		if (pTmpDOValue->m_strID == strDOValueName)
		{
			pDOType = (CExBaseList*)pTestObjectTemplates->FindByID(pObjDOValue->m_strType);
			if (pDOType == NULL)
			{
// 				pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DO-type-valid");
// 
// 				if (BeCheckThisObject(pCheckObject ,strObjectID))
// 				{
// 					strErrorText.Format("LNodeType: id=%s,lnClass=%s 中DO: name=%s 对应type=%s 未在DOType中定义;",pObjDataType->m_strID ,pObjDataType->m_strLnClass ,pTmpDOValue->m_strID ,
// 						pObjDOValue->m_strType);
// 					AddCheckResultDLT860Tmps(strObjectID , strErrorText  ,pObjDOValue->m_strErrorPos);
// 				}
			}
			else if (pDOType->m_strName != pTmpDOValue->m_strName)
			{
				pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DO-cdc-illegal");

				if (BeCheckThisObject(pCheckObject ,strObjectID))
				{
					strErrorText.Format("LNodeType: id=%s,lnClass=%s 中DO: name=%s 对应cdc=%s定义错误 ,标准定义为%s;",pObjDataType->m_strID ,pObjDataType->m_strLnClass ,pTmpDOValue->m_strID,
						pDOType->m_strName,pTmpDOValue->m_strName);
					AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjDOValue->m_strErrorPos);
				}
			}
			objPos = checkDO_withRepeat(pObjDataType  ,SymbolPos ,bSmb ,pDLT860ModelChecks);
		}
		else if (pTmpDOValue->m_strMop == "M")
		{	
			pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DO-M");

			if (BeCheckThisObject(pCheckObject ,strObjectID))
			{
				pObjDOValue = (CDOValue*)pObjDataType->FindByID(pTmpDOValue->m_strID);

				if (pObjDOValue == NULL)
				{
					strErrorText.Format("LNodeType: id=%s,lnClass=%s 中缺少必备DO: name=%s ;",pObjDataType->m_strID ,pObjDataType->m_strLnClass ,pTmpDOValue->m_strID);
					AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjDataType->m_strErrorPos);
				}
			}
			
			objPos = SymbolPos;
		}
		else
		{
			objPos = SymbolPos;
		}
	}
	///////////////////////第五步：将未经比对的SCD文件中的DO与本模板中的所有DO进行比对，保证标准预定义的DO顺序的正确性///////////////////////////////////////////////////////////
	while(objPos!=NULL)
	{
		pObjDOValue = (CDOValue*)pObjDataType->GetNext(objPos);
		tmpPos = pTemplate->GetHeadPosition();
		while(tmpPos!=NULL)
		{
			pTmpDOValue = (CDOValueT*)pTemplate->GetNext(tmpPos);
			if (pObjDOValue->m_strID == pTmpDOValue->m_strID)
			{
				pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("lnClass-DO-order");

				if (BeCheckThisObject(pCheckObject ,strObjectID))
				{
					strErrorText.Format("LNodeType: id=%s,lnClass=%s 中DO: name=%s 顺序与标准定义不一致;",pObjDataType->m_strID ,pObjDataType->m_strLnClass ,pTmpDOValue->m_strID);
					AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjDOValue->m_strErrorPos);
				}
			}
		}
	}
	/////////////////////////////////////20180108单独增加对LNodeType下的DO使用的type是否定义的检查////////////////////////////////////////////////////////////////////////////////////////////////////////
	objPos = pObjDataType->GetHeadPosition();

	while(objPos!=NULL)
	{
		pObjDOValue = (CDOValue*)pObjDataType->GetNext(objPos);

		pDOType = (CExBaseList*)pTestObjectTemplates->FindByID(pObjDOValue->m_strType);
		if (pDOType == NULL)
		{
			pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DO-type-valid");

			if (BeCheckThisObject(pCheckObject ,strObjectID))
			{
				strErrorText.Format("LNodeType: id=%s,lnClass=%s 中DO: name=%s 对应type=%s 未在DOType中定义;",pObjDataType->m_strID ,pObjDataType->m_strLnClass ,pObjDOValue->m_strID ,
					pObjDOValue->m_strType);
				AddCheckResultDLT860Tmps(strObjectID , strErrorText  ,pObjDOValue->m_strErrorPos);
			}
		}
	}
}

void CSclCheckView::CheckDOTypeOfGDW1396(CDOType *pObjDOType ,CExBaseList *pTemplates1396 ,CDLT860ModelChecks *pDLT860ModelChecks)
{
	CString  strObjectID;
	CCheckObject *pCheckObject = NULL;
	CExBaseList *pTestObjectTemplates = (CExBaseList*)m_pSCLTestObjectFile->FindByID("DataTypeTemplates");
	CExBaseObject *pChildType = NULL;
	CDOType *pTemplate = NULL;
	pTemplate = (CDOType*)pTemplates1396->FindByID(pObjDOType->m_strID);
	CString strErrorText;

	if (pTemplate == NULL)
	{
		pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DOType-illegal");

		if (BeCheckThisObject(pCheckObject ,strObjectID))
		{
			strErrorText.Format("DOType: id=%s,cdc=%s 采用了未经标准定义的DOType , 此类不得私自扩充;",pObjDOType->m_strID ,pObjDOType->m_strName);
			AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjDOType->m_strErrorPos);
		}
		return;
	}

	POS objPos = pObjDOType->GetHeadPosition();
	POS tmpPos = pTemplate->GetHeadPosition();
	POS SymbolPos = NULL;
	if (objPos == NULL)
	{
		strErrorText.Format("DOType: id=%s,cdc=%s DOType下未定义任何DA;",pObjDOType->m_strID ,pObjDOType->m_strName);
		AddCheckResultDLT860Tmps("error" , strErrorText  ,pObjDOType->m_strErrorPos);
		return;
	}
	else if (pObjDOType->m_strName != pTemplate->m_strName)
	{
		pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DOType-cdc-illegal");

		if (BeCheckThisObject(pCheckObject ,strObjectID))
		{
			strErrorText.Format("DOType: id=%s,cdc=%s 中cdc定义与标准不一致 , 标准定义为 cdc=%s;",pObjDOType->m_strID ,pObjDOType->m_strName ,pTemplate->m_strName);
			AddCheckResultDLT860Tmps(strObjectID , strErrorText  ,pObjDOType->m_strErrorPos);
		}
	}
	CExBaseObject *pObjValue = NULL;
	CExBaseObject *pTmpValue = NULL;
	CDAValue *pObjDAValue = NULL;
	CDAValue *pTmpDAValue = NULL;
	CSDOValue *pObjSDOValue = NULL;
	CSDOValue *pTmpSDOValue = NULL;

	while(tmpPos!=NULL)
	{
		pTmpValue = pTemplate->GetNext(tmpPos);

		if (pTmpValue->GetClassID() == SCLCLASSID_CSCLFILE_DADETAIL)
		{
			if (objPos==NULL)
			{
				pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DOType-DA-illegal");

				if (BeCheckThisObject(pCheckObject ,strObjectID))
				{
					strErrorText.Format("DOType: id=%s 中缺少 DA: name=%s ;",pObjDOType->m_strID ,pTmpValue->m_strID);
					AddCheckResultDLT860Tmps(strObjectID , strErrorText  ,pObjDOType->m_strErrorPos);
				}
			} 
			else
			{
				SymbolPos = objPos;
				pObjDAValue = (CDAValue*)pObjDOType->GetNext(objPos);
				pTmpDAValue = (CDAValue*)pTmpValue;
				if (pObjDAValue->m_strID!=pTmpDAValue->m_strID)
				{
					pObjValue = pObjDOType->FindByID(pTmpDAValue->m_strID);
					if (pObjValue==NULL)
					{
						pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DOType-DA-illegal");

						if (BeCheckThisObject(pCheckObject ,strObjectID))
						{
							strErrorText.Format("DOType: id=%s 中缺少 DA: name=%s ;",pObjDOType->m_strID ,pTmpValue->m_strID);
							AddCheckResultDLT860Tmps(strObjectID , strErrorText  ,pObjDOType->m_strErrorPos);
						}
					} 
					else
					{
						pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DOType-DA-order");

						if (BeCheckThisObject(pCheckObject ,strObjectID))
						{
							strErrorText.Format("DOType: id=%s 中 DA: name=%s 顺序与标准不一致;",pObjDOType->m_strID ,pTmpValue->m_strID);
							AddCheckResultDLT860Tmps(strObjectID , strErrorText  ,pObjDAValue->m_strErrorPos);
						}
					}
					objPos = SymbolPos;
				}
				else 
				{
					if (pObjDAValue->m_strBType!=pTmpDAValue->m_strBType)
					{
						pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DOType-DA-attr");

						if (BeCheckThisObject(pCheckObject ,strObjectID))
						{
							strErrorText.Format("DOType: id=%s 中 DA: name=%s 的 bType=%s 与标准 bType=%s 不一致;",pObjDOType->m_strID ,pTmpValue->m_strID ,pObjDAValue->m_strBType ,pTmpDAValue->m_strBType);
							AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjDAValue->m_strErrorPos);
						}
					}
					if (pObjDAValue->m_strFC!=pTmpDAValue->m_strFC)
					{
						pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DOType-DA-attr");

						if (BeCheckThisObject(pCheckObject ,strObjectID))
						{
							strErrorText.Format("DOType: id=%s 中 DA: name=%s 的 fc=%s 与标准 fc=%s 不一致;",pObjDOType->m_strID ,pTmpValue->m_strID ,pObjDAValue->m_strFC ,pTmpDAValue->m_strFC);
							AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjDAValue->m_strErrorPos);
						}
					}
					if (pObjDAValue->m_strName!=pTmpDAValue->m_strName)
					{
						pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DOType-DA-attr");

						if (BeCheckThisObject(pCheckObject ,strObjectID))
						{
							strErrorText.Format("DOType: id=%s 中 DA: name=%s 的 type=%s 与标准 type=%s 不一致;",pObjDOType->m_strID ,pTmpValue->m_strID ,pObjDAValue->m_strName ,pTmpDAValue->m_strName);
							AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjDAValue->m_strErrorPos);
						}
					}
					else if (!pObjDAValue->m_strName.IsEmpty())
					{
						pChildType = pTestObjectTemplates->FindByID(pObjDAValue->m_strName);
						if (pChildType== NULL)
						{
							pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DA-type-valid");

							if (BeCheckThisObject(pCheckObject ,strObjectID))
							{
								strErrorText.Format("DOType: id=%s 中 DA: name=%s 的 type=%s 未定义;",pObjDOType->m_strID ,pTmpValue->m_strID ,pObjDAValue->m_strName);
								AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjDAValue->m_strErrorPos);
							}
						}
					}
					if (pObjDAValue->m_strDchg!=pTmpDAValue->m_strDchg)
					{
						pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DOType-DA-attr");

						if (BeCheckThisObject(pCheckObject ,strObjectID))
						{
							strErrorText.Format("DOType: id=%s 中 DA: name=%s 的 dchg=%s 与标准 dchg=%s 不一致;",pObjDOType->m_strID ,pTmpValue->m_strID ,pObjDAValue->m_strDchg ,pTmpDAValue->m_strDchg);
							AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjDAValue->m_strErrorPos);
						}
					}
					if (pObjDAValue->m_strQchg!=pTmpDAValue->m_strQchg)
					{
						pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DOType-DA-attr");

						if (BeCheckThisObject(pCheckObject ,strObjectID))
						{
							strErrorText.Format("DOType: id=%s 中 DA: name=%s 的 qchg=%s 与标准 qchg=%s 不一致;",pObjDOType->m_strID ,pTmpValue->m_strID ,pObjDAValue->m_strQchg ,pTmpDAValue->m_strQchg);
							AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjDAValue->m_strErrorPos);
						}
					}
					if (pObjDAValue->m_strValue!=pTmpDAValue->m_strValue)
					{
						pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DOType-DA-attr");

						if (BeCheckThisObject(pCheckObject ,strObjectID))
						{
							strErrorText.Format("DOType: id=%s 中 DA: name=%s 的 Val=%s 与标准 Val=%s 不一致;",pObjDOType->m_strID ,pTmpValue->m_strID ,pObjDAValue->m_strValue ,pTmpDAValue->m_strValue);
							AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjDAValue->m_strErrorPos);
						}
					}
				}
			}
		} 
		else if (pTmpValue->GetClassID() == SCLCLASSID_CSCLFILE_SDODETAIL)
		{
			if (objPos==NULL)
			{
				pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DOType-DA-illegal");

				if (BeCheckThisObject(pCheckObject ,strObjectID))
				{
					strErrorText.Format("DOType: id=%s 中缺少 SDO: name=%s ;",pObjDOType->m_strID ,pTmpValue->m_strID);
					AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjDOType->m_strErrorPos);
				}
			} 
			else
			{
				SymbolPos = objPos;
				pObjSDOValue = (CSDOValue*)pObjDOType->GetNext(objPos);
				pTmpSDOValue = (CSDOValue*)pTmpValue;
				if (pObjSDOValue->m_strID!=pTmpSDOValue->m_strID)
				{
					pObjValue = pObjDOType->FindByID(pTmpSDOValue->m_strID);
					if (pObjValue==NULL)
					{
						pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DOType-DA-illegal");

						if (BeCheckThisObject(pCheckObject ,strObjectID))
						{
							strErrorText.Format("DOType: id=%s 中缺少 SDO: name=%s ;",pObjDOType->m_strID ,pTmpValue->m_strID);
							AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjDOType->m_strErrorPos);
						}
					} 
					else
					{
						pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DOType-DA-order");

						if (BeCheckThisObject(pCheckObject ,strObjectID))
						{
							strErrorText.Format("DOType: id=%s 中 SDO: name=%s 顺序与标准不一致;",pObjDOType->m_strID ,pTmpValue->m_strID);
							AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjSDOValue->m_strErrorPos);
						}
					}
					objPos = SymbolPos;
				}
				else 
				{
					if (pObjSDOValue->m_strName!=pTmpSDOValue->m_strName)
					{
						pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DOType-DA-attr");

						if (BeCheckThisObject(pCheckObject ,strObjectID))
						{
							strErrorText.Format("DOType: id=%s 中 SDO: name=%s 的 type=%s 与标准 type=%s 不一致;",pObjDOType->m_strID ,pTmpValue->m_strID ,pObjSDOValue->m_strName ,pTmpSDOValue->m_strName);
							AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjSDOValue->m_strErrorPos);
						}
					}
					else if (!pObjSDOValue->m_strName.IsEmpty())
					{
						pChildType = pTestObjectTemplates->FindByID(pObjSDOValue->m_strName);
						if (pChildType== NULL)
						{
							pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DA-type-valid");

							if (BeCheckThisObject(pCheckObject ,strObjectID))
							{
								strErrorText.Format("DOType: id=%s 中 SDO: name=%s 的 type=%s 未定义;",pObjDOType->m_strID ,pTmpValue->m_strID ,pObjSDOValue->m_strName);
								AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjSDOValue->m_strErrorPos);
							}
						}
					}
				}
			}
		}
	}

}

void CSclCheckView::CheckDATypeOfGDW1396(CDAType *pObjDAType ,CExBaseList *pTemplates1396 ,CDLT860ModelChecks *pDLT860ModelChecks)
{
	CString  strObjectID;
	CCheckObject *pCheckObject = NULL;
	CExBaseList *pTestObjectTemplates = (CExBaseList*)m_pSCLTestObjectFile->FindByID("DataTypeTemplates");
	CExBaseObject *pChildType = NULL;
	CDAType *pTemplate = NULL;
	pTemplate = (CDAType*)pTemplates1396->FindByID(pObjDAType->m_strID);
	CString strErrorText;

	if (pTemplate == NULL)
	{
		pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DAType-illegal");

		if (BeCheckThisObject(pCheckObject ,strObjectID))
		{
			strErrorText.Format("DAType: id=%s 采用了未经标准定义的DAType ;",pObjDAType->m_strID );
			AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjDAType->m_strErrorPos);
		}
		return;
	}

	POS objPos = pObjDAType->GetHeadPosition();
	POS tmpPos = pTemplate->GetHeadPosition();
	POS SymbolPos = NULL;
	if (objPos == NULL)
	{
		strErrorText.Format("DAType: id=%s DAType下未定义任何BDA;",pObjDAType->m_strID );
		AddCheckResultDLT860Tmps("error" , strErrorText ,pObjDAType->m_strErrorPos);
		return;
	}

	CExBaseObject *pObjValue = NULL;

	CBDAValue *pObjBDAValue = NULL;
	CBDAValue *pTmpBDAValue = NULL;

	while(tmpPos!=NULL)
	{
		pTmpBDAValue = (CBDAValue*)pTemplate->GetNext(tmpPos);

		if (objPos==NULL)
		{
			pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DAType-BDA-illegal");

			if (BeCheckThisObject(pCheckObject ,strObjectID))
			{
				strErrorText.Format("DAType: id=%s 中缺少 BDA: name=%s ;",pObjDAType->m_strID ,pTmpBDAValue->m_strID);
				AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjDAType->m_strErrorPos);
			}
		} 
		else
		{
			SymbolPos = objPos;
			pObjBDAValue = (CBDAValue*)pObjDAType->GetNext(objPos);

			if (pObjBDAValue->m_strID!=pTmpBDAValue->m_strID)
			{
				pObjValue = pObjDAType->FindByID(pTmpBDAValue->m_strID);
				if (pObjValue==NULL)
				{
					pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DAType-BDA-illegal");

					if (BeCheckThisObject(pCheckObject ,strObjectID))
					{
						strErrorText.Format("DAType: id=%s 中缺少 BDA: name=%s ;",pObjDAType->m_strID ,pTmpBDAValue->m_strID);
						AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjDAType->m_strErrorPos);
					}
				} 
				else
				{
					pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DAType-BDA-order");

					if (BeCheckThisObject(pCheckObject ,strObjectID))
					{
						strErrorText.Format("DAType: id=%s 中 BDA: name=%s 顺序与标准不一致;",pObjDAType->m_strID ,pTmpBDAValue->m_strID);
						AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjBDAValue->m_strErrorPos);
					}
				}
				objPos = SymbolPos;
			}
			else 
			{
				if (pObjBDAValue->m_strBType!=pTmpBDAValue->m_strBType)
				{
					pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DAType-BDA-attr");

					if (BeCheckThisObject(pCheckObject ,strObjectID))
					{
						strErrorText.Format("DAType: id=%s 中 BDA: name=%s 的 bType=%s 与标准 bType=%s 不一致;",pObjDAType->m_strID ,pTmpBDAValue->m_strID ,pObjBDAValue->m_strBType ,pTmpBDAValue->m_strBType);
						AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjBDAValue->m_strErrorPos);
					}
				}
				if (pObjBDAValue->m_strName!=pTmpBDAValue->m_strName)
				{
					pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DAType-BDA-attr");

					if (BeCheckThisObject(pCheckObject ,strObjectID))
					{
						strErrorText.Format("DAType: id=%s 中 BDA: name=%s 的 type=%s 与标准 type=%s 不一致;",pObjDAType->m_strID ,pTmpBDAValue->m_strID ,pObjBDAValue->m_strName ,pTmpBDAValue->m_strName);
						AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjBDAValue->m_strErrorPos);
					}
				}
				else if (!pObjBDAValue->m_strName.IsEmpty())
				{
					pChildType = pTestObjectTemplates->FindByID(pObjBDAValue->m_strName);
					if (pChildType == NULL)
					{
						pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("BDA-type-valid");

						if (BeCheckThisObject(pCheckObject ,strObjectID))
						{
							strErrorText.Format("DAType: id=%s 中 BDA: name=%s 的 type=%s 未定义;",pObjDAType->m_strID ,pTmpBDAValue->m_strID ,pObjBDAValue->m_strName);
							AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjBDAValue->m_strErrorPos);
						}
					}
				}
			}
		}
	} 
}

void CSclCheckView::CheckEnumTypeOfGDW1396(CEnumType *pObjEnumType ,CExBaseList *pTemplates1396 ,CDLT860ModelChecks *pDLT860ModelChecks)
{
	CString  strObjectID;
	CCheckObject *pCheckObject = NULL;
	CEnumType*pTemplate = NULL;
	pTemplate = (CEnumType*)pTemplates1396->FindByID(pObjEnumType->m_strID);
	CString strErrorText;

	if (pTemplate == NULL)
	{
		pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("EnumType-illegal");

		if (BeCheckThisObject(pCheckObject ,strObjectID))
		{
			strErrorText.Format("EnumType: id=%s 采用了未经标准定义的EnumType ;",pObjEnumType->m_strID );
			AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjEnumType->m_strErrorPos);
		}
		return;
	}

	POS objPos = pObjEnumType->GetHeadPosition();
	POS tmpPos = pTemplate->GetHeadPosition();
	POS SymbolPos = NULL;
	if (objPos == NULL)
	{
		strErrorText.Format("EnumType: id=%s DAType下未定义任何EnumVal;",pObjEnumType->m_strID );
		AddCheckResultDLT860Tmps("error" , strErrorText  ,pObjEnumType->m_strErrorPos);
		return;
	}

	CExBaseObject *pObjValue = NULL;

	CEnumValue *pObjEnumVal = NULL;
	CEnumValue *pTmpEnumVal = NULL;

	while(tmpPos!=NULL)
	{
		pTmpEnumVal = (CEnumValue*)pTemplate->GetNext(tmpPos);

		if (objPos==NULL)
		{
			pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("EnumType-EnumVal-illegal");

			if (BeCheckThisObject(pCheckObject ,strObjectID))
			{
				strErrorText.Format("EnumType: id=%s 中缺少 EnumVal: ord=%s 值为%s;",pObjEnumType->m_strID ,pTmpEnumVal->m_strID ,pTmpEnumVal->m_strName);
				AddCheckResultDLT860Tmps(strObjectID , strErrorText  ,pObjEnumType->m_strErrorPos);
			}
		} 
		else
		{
			SymbolPos = objPos;
			pObjEnumVal = (CEnumValue*)pObjEnumType->GetNext(objPos);

			if (pObjEnumVal->m_strID!=pTmpEnumVal->m_strID)
			{
				if (pObjEnumVal->m_strName == pTmpEnumVal->m_strName)
				{
					pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("EnumType-EnumVal-attr");

					if (BeCheckThisObject(pCheckObject ,strObjectID))
					{
						strErrorText.Format("EnumType: id=%s 中 EnumVal值为%s :ord=%s 与标准定义 ord=%s 不一致;",pObjEnumType->m_strID ,pObjEnumVal->m_strName ,pObjEnumVal->m_strID ,pTmpEnumVal->m_strID);
						AddCheckResultDLT860Tmps(strObjectID , strErrorText  ,pObjEnumVal->m_strErrorPos);
					}
					continue;
				}
				else if(!pTmpEnumVal->m_strName.IsEmpty())
				{
					pObjValue = pObjEnumType->FindByName(pTmpEnumVal->m_strName);
					if (pObjValue==NULL)
					{
						pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("EnumType-EnumVal-illegal");

						if (BeCheckThisObject(pCheckObject ,strObjectID))
						{
							strErrorText.Format("EnumType: id=%s 中缺少 EnumVal:ord=%s 值为%s ;",pObjEnumType->m_strID ,pTmpEnumVal->m_strID ,pTmpEnumVal->m_strName);
							AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjEnumType->m_strErrorPos);
						}
					} 
					else
					{
						pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("EnumType-EnumVal-order");

						if (BeCheckThisObject(pCheckObject ,strObjectID))
						{
							strErrorText.Format("EnumType: id=%s 中 EnumVal值为%s 顺序与标准不一致;",pObjEnumType->m_strID ,pTmpEnumVal->m_strName);
							AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjEnumVal->m_strErrorPos);
						}
					}
				}
				objPos = SymbolPos;
			}
			else if(pObjEnumVal->m_strName!=pTmpEnumVal->m_strName)
			{
				if (!pTmpEnumVal->m_strName.IsEmpty())
				{
					pObjValue = pObjEnumType->FindByName(pTmpEnumVal->m_strName);
					if (pObjValue==NULL)
					{
						pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("EnumType-EnumVal-illegal");

						if (BeCheckThisObject(pCheckObject ,strObjectID))
						{
							strErrorText.Format("EnumType: id=%s 中缺少 EnumVal:ord=%s 值为%s ;",pObjEnumType->m_strID ,pTmpEnumVal->m_strID ,pTmpEnumVal->m_strName);
							AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjEnumType->m_strErrorPos);
						}
					} 
					else
					{
						pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("EnumType-EnumVal-order");

						if (BeCheckThisObject(pCheckObject ,strObjectID))
						{
							strErrorText.Format("EnumType: id=%s 中 EnumVal值为%s 顺序与标准不一致;",pObjEnumType->m_strID ,pTmpEnumVal->m_strName);
							AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjEnumVal->m_strErrorPos);
						}
					}
				} 
			}
		}
	}
}

bool CSclCheckView::CheckTailDigital(CString strName)
{
	unsigned char zfTmp = strName.GetAt(strName.GetLength()-1);
	return (('0'<=zfTmp)&&(zfTmp<='9'));
}

long CSclCheckView::DelTailDigtal(CString *strName )
{
	long nIndex = 0;
	char szDigtal[20] = {""};
	char szNew[20] = {""};
	szDigtal[0] = strName->GetAt(strName->GetLength()-1);
	char *pzfTmp = szDigtal;
	bool bSmb = ('0'<=*pzfTmp)&&(*pzfTmp<='9');

	while(bSmb)
	{
		pzfTmp++;
		*strName = strName->Left(strName->GetLength()-1);
		*pzfTmp = strName->GetAt(strName->GetLength()-1);
		bSmb = ('0'<=*pzfTmp)&&(*pzfTmp<='9');
	}
	*pzfTmp = '\0';

	nIndex = strlen(szDigtal);
	for (int i=0; i<nIndex;i++)
	{
		szNew[i] = szDigtal[nIndex-i-1];
	}

	nIndex = atoi(szNew);
	return nIndex;
}

POS CSclCheckView::checkDO_withRepeat(CLNodeType *pObjDataType , POS pos ,bool bDigtalTail ,CDLT860ModelChecks *pDLT860ModelChecks)
{
	CString  strObjectID;
	CCheckObject *pCheckObject = NULL;
	CDOValue *pObjDOValue = NULL;
	CDOValue *pObjDOValueNext = NULL;
	POS posNew = pos;

	bool bSmb = false;
	pObjDOValue = (CDOValue*)pObjDataType->GetNext(posNew);
	POS posSgn = posNew;
	CString strDOName = pObjDOValue->m_strID;
	CString strDONameNext;
	CString strErrorText;
	bSmb = CheckTailDigital(strDOName);
	long nFind = -1;
	long nIndex = 0;
	long nIndexNext = 0;
	if (bSmb)
	{
		nIndex = DelTailDigtal( &strDOName );
		while(posNew!=NULL)
		{
			posSgn = posNew;
			pObjDOValueNext = (CDOValue*)pObjDataType->GetNext(posNew);
			nFind = FindRepeat(pObjDOValueNext->m_strID ,strDOName);
			if (nFind == -1)
			{
				return posSgn;
			}
			else
			{
				strDONameNext = pObjDOValueNext->m_strID;
				nIndexNext = DelTailDigtal( &strDONameNext );
				if(nIndexNext != (nIndex+1))
				{
					if ((pObjDOValueNext->m_strID=="Z0")&&(pObjDOValue->m_strID=="Z1"))
					{/////////////////排除此特例////////////////////////////////////////////////////////////////////////////////////////
					} 
					else
					{
						pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("lnClass-DO-order");

						if (BeCheckThisObject(pCheckObject ,strObjectID))
						{
							strErrorText.Format("LNodeType: id=%s,lnClass=%s 中DO: name=%s 末尾数字标号不连续;",pObjDataType->m_strID ,pObjDataType->m_strLnClass ,pObjDOValueNext->m_strID);
							AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjDOValue->m_strErrorPos);
						}
					}	
				}
				else if (pObjDOValueNext->m_strType != pObjDOValue->m_strType)
				{
					strErrorText.Format("LNodeType: id=%s,lnClass=%s 中DO: name=%s 对应type前后不一致;",pObjDataType->m_strID ,pObjDataType->m_strLnClass ,pObjDOValueNext->m_strID);
					AddCheckResultDLT860Tmps("error" , strErrorText ,pObjDOValue->m_strErrorPos);
				}
				nIndex = nIndexNext;
			}
		}
		return posNew;
	}
	else
	{
		return posNew;
	}
}

long CSclCheckView::FindRepeat(CString strParant ,CString strChild)
{

	long nChild = strChild.GetLength();
	long nParent = strParant.GetLength();
	long nTmp = 0;
	for (;nTmp<nChild;nTmp++)
	{
		if (strParant[nTmp]!=strChild[nTmp])
		{
			return -1;
		}
	}
	for (;nTmp<nParent;nTmp++)
	{
		if ((strParant[nTmp]<'0')||(strParant[nTmp]>'9'))
		{
			return -1;
		}
	}

	return 0;
}

bool CSclCheckView::DataTypeCompareWithTemplates(CExBaseList *pTmpDataType , CExBaseList *pObjDataType )
{
	CDOValue *pTmpDOValue = NULL;
	CDOValue *pObjDOValue = NULL;
	CDAValue *pTmpDAValue = NULL;
	CDAValue *pObjDAValue = NULL;
	CSDOValue *pTmpSDOValue = NULL;
	CSDOValue *pObjSDOValue = NULL;
	CBDAValue *pTmpBDAValue = NULL;
	CBDAValue *pObjBDAValue = NULL;
	CEnumValue *pTmpEnumValue = NULL;
	CEnumValue *pObjEnumValue = NULL;

	CExBaseObject *pTmpValue = NULL;

	POS tmpPos = pTmpDataType->GetHeadPosition();
	POS objPos = pObjDataType->GetHeadPosition();

	if (pTmpDataType->GetClassID() == SCLCLASSID_CSCLFILELNODETYPE)
	{
		if (((CLNodeType*)pTmpDataType)->m_strLnClass != ((CLNodeType*)pObjDataType)->m_strLnClass)
		{
			return true;
		}
	}

	if (pTmpDataType->m_strName != pObjDataType->m_strName)
	{
		return true;
	}
	else
	{
		if (pTmpDataType->GetClassID() == SCLCLASSID_CSCLFILELNODETYPE)
		{
			while(tmpPos!=NULL)
			{
				if (objPos==NULL)
				{
					return true;
				} 
				else
				{
					pTmpDOValue = (CDOValue *)pTmpDataType->GetNext(tmpPos);
					pObjDOValue = (CDOValue *)pObjDataType->GetNext(objPos);
					if ((pTmpDOValue->m_strID != pObjDOValue->m_strID)||(pTmpDOValue->m_strName != pObjDOValue->m_strName)||(pTmpDOValue->m_strType != pObjDOValue->m_strType)||(pTmpDOValue->m_strTransient != pObjDOValue->m_strTransient))
					{
						return true;
					}
				}
			}
		} 
		else if (pTmpDataType->GetClassID() == SCLCLASSID_CSCLFILEDOTYPE)
		{
			while(tmpPos!=NULL)
			{
				if (objPos==NULL)
				{
					return true;
				} 
				else
				{
					pTmpValue = pTmpDataType->GetNext(tmpPos);

					if (pTmpValue->GetClassID() == SCLCLASSID_CSCLFILE_DADETAIL)
					{
						pTmpDAValue = (CDAValue *)pTmpValue;
						pObjDAValue = (CDAValue *)pObjDataType->GetNext(objPos);
						if ((pTmpDAValue->m_strID != pObjDAValue->m_strID)||(pTmpDAValue->m_strName != pObjDAValue->m_strName)||(pTmpDAValue->m_strBType != pObjDAValue->m_strBType)
							||(pTmpDAValue->m_strValue != pObjDAValue->m_strValue)||(pTmpDAValue->m_strQchg != pObjDAValue->m_strQchg)||(pTmpDAValue->m_strDchg != pObjDAValue->m_strDchg)
							||(pTmpDAValue->m_strFC != pObjDAValue->m_strFC))
						{
							return true;
						}
					}
					else if (pTmpValue->GetClassID() == SCLCLASSID_CSCLFILE_SDODETAIL)
					{
						pTmpSDOValue = (CSDOValue *)pTmpValue;
						pObjSDOValue = (CSDOValue *)pObjDataType->GetNext(objPos);
						if ((pTmpSDOValue->m_strID != pObjSDOValue->m_strID)||(pTmpSDOValue->m_strName != pObjSDOValue->m_strName))
						{
							return true;
						}
					}
				}
			}
		}
		else if (pTmpDataType->GetClassID() == SCLCLASSID_CSCLFILEDATYPE)
		{
			while(tmpPos!=NULL)
			{
				if (objPos==NULL)
				{
					return true;
				} 
				else
				{
					pTmpBDAValue = (CBDAValue *)pTmpDataType->GetNext(tmpPos);
					pObjBDAValue = (CBDAValue *)pObjDataType->GetNext(objPos);
					if ((pTmpBDAValue->m_strID != pObjBDAValue->m_strID)||(pTmpBDAValue->m_strName != pObjBDAValue->m_strName)||(pTmpBDAValue->m_strBType != pObjBDAValue->m_strBType))
					{
						return true;
					}
				}
			}
		}
		else if (pTmpDataType->GetClassID() == SCLCLASSID_CSCLFILEENUMTYPE)
		{
			while(tmpPos!=NULL)
			{
				if (objPos==NULL)
				{
					return true;
				} 
				else
				{
					pTmpEnumValue = (CEnumValue *)pTmpDataType->GetNext(tmpPos);
					pObjEnumValue = (CEnumValue *)pObjDataType->GetNext(objPos);
					if ((pTmpEnumValue->m_strID != pObjEnumValue->m_strID)||(pTmpEnumValue->m_strName != pObjEnumValue->m_strName))
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

BOOL CSclCheckView::TemplateCheckIsEmpty(CDLT860ModelChecks *pDLT860ModelChecks)
{
	POS pos = pDLT860ModelChecks->GetHeadPosition();
	CCheckObject *pCheckObject = NULL;

	while(pos != NULL)
	{
		pCheckObject = (CCheckObject*)pDLT860ModelChecks->GetNext(pos);

		if ((pCheckObject->m_strName.Find("冲突性检查") == -1)&&(pCheckObject->m_nChoose))
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CSclCheckView::TemplateCompareIsEmpty(CDLT860ModelChecks *pDLT860ModelChecks)
{
	POS pos = pDLT860ModelChecks->GetHeadPosition();
	CCheckObject *pCheckObject = NULL;

	while(pos != NULL)
	{
		pCheckObject = (CCheckObject*)pDLT860ModelChecks->GetNext(pos);

		if ((pCheckObject->m_strName.Find("冲突性检查") != -1)&&(pCheckObject->m_nChoose))
		{
			return FALSE;
		}
	}
	return TRUE;
}

void CSclCheckView::StartTemplatesCheckComp1396()
{
	StartTemplateCheck1396(m_pDLT860ModelChecks);
	StartTemplatesCompare(m_pDLT860ModelChecks);
	m_oDLT860TmpsResultsRec.Statis_AllResults();
	m_pDLT860TempsView->ShowGridDatas(&m_oDLT860TmpsResultsRec);

	CWaitingTimeDlg::g_bOver =  true;
}

UINT CSclCheckView::StartTemplatesCheckCompThread(LPVOID pParam)
{
	CSclCheckView *pSclCheckView = (CSclCheckView *)pParam;
	pSclCheckView->StartTemplatesCheckComp1396();
	return 1;
}

void CSclCheckView::StartTmpsCheckComp1396Thr()
{
	CWinThread *pThread; //线程指针
	pThread = AfxBeginThread(StartTemplatesCheckCompThread, this); //启动线程 
	pThread->m_bAutoDelete = TRUE;
}

void CSclCheckView::StartTemplateCheck1396(CDLT860ModelChecks *pDLT860ModelChecks)
{
	CString strObjectID;
	CCheckObject *pCheckObject = NULL;
	/////////////////第一步：判断是否含有相关检测项目/////////////////////////////////////////////////////////////

	if(TemplateCheckIsEmpty(pDLT860ModelChecks))
		return;

	/////////////////////////////第二步：打开待测文件，将其DataTypeTemplates部分存入链表中////////////////////////////////////////////
	if (m_pSCLTestObjectFile == NULL)
	{
		m_pSCLTestObjectFile = new CSCLTemplates();
		m_pSCLTestObjectFile->m_bUTF8 = TRUE;
		m_pSCLTestObjectFile->OpenSclTemplatesFile(m_strSclFilePath);
	}
	else if (m_pSCLTestObjectFile->m_strName != m_strSclFilePath)
	{
		delete m_pSCLTestObjectFile;
		m_pSCLTestObjectFile = new CSCLTemplates();
		m_pSCLTestObjectFile->m_bUTF8 = TRUE;
		m_pSCLTestObjectFile->OpenSclTemplatesFile(m_strSclFilePath);
	}
	
	//////////////////////////////第三步：进行比对验证，将测试结果存入对应测试结果链表中去//////////////////////////////////////////////
	CExBaseList *pTemplates1396 = (CExBaseList*)m_pTemplateFile1396->FindByID("DataTypeTemplates");
	CExBaseList *pTestObjectTemplates = (CExBaseList*)m_pSCLTestObjectFile->FindByID("DataTypeTemplates");
	if (pTemplates1396==NULL)
	{
		AddCheckResultDLT860Tmps("fatalerror","国网1396标准检测模板存放位置有误，或模板文件被更改;" );
		return;
	}
	if (pTestObjectTemplates== NULL)
	{
		AddCheckResultDLT860Tmps("fatalerror" ,"被测文件SCL根节点下不存在 DataTypeTemplates 节点;");
		return;
	}

	POS testObjecPos = pTestObjectTemplates->GetHeadPosition();

	CExBaseList *pObjDataType = NULL;
	long nCount = 0;
	CString strErrorText;
	while (testObjecPos != NULL)
	{
		pObjDataType = (CExBaseList*)pTestObjectTemplates->GetNext(testObjecPos);

		if (pObjDataType->GetClassID() == SCLCLASSID_CSCLFILELNODETYPE)
		{
			pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("LNodeType-repeat");

			if (BeCheckThisObject(pCheckObject ,strObjectID))
			{
				nCount = pTestObjectTemplates->SearchByID(pObjDataType->m_strID);
				if (nCount!=1)
				{
					strErrorText.Format("LNodeType: id=%s 在DataTypeTemplates重复定义了 %d 次 ;",pObjDataType->m_strID ,nCount);
					AddCheckResultDLT860Tmps(strObjectID , strErrorText ,((CLNodeType*)pObjDataType)->m_strErrorPos);
				}
			}

			CheckLNodeTypeOfGDW1396((CLNodeType*)pObjDataType ,pTemplates1396 ,pDLT860ModelChecks);
		}
		else if (pObjDataType->GetClassID() == SCLCLASSID_CSCLFILEDOTYPE)
		{
			pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DOType-repeat");

			if (BeCheckThisObject(pCheckObject ,strObjectID))
			{
				nCount = pTestObjectTemplates->SearchByID(pObjDataType->m_strID);
				if (nCount!=1)
				{
					strErrorText.Format("DOType: id=%s 在DataTypeTemplates重复定义了 %d 次 ;",pObjDataType->m_strID ,nCount);
					AddCheckResultDLT860Tmps(strObjectID , strErrorText ,((CDOType*)pObjDataType)->m_strErrorPos);
				}
			}

			CheckDOTypeOfGDW1396((CDOType*)pObjDataType ,pTemplates1396 ,pDLT860ModelChecks );
		}
		else if (pObjDataType->GetClassID() == SCLCLASSID_CSCLFILEDATYPE)
		{
			pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DAType-repeat");

			if (BeCheckThisObject(pCheckObject ,strObjectID))
			{
				nCount = pTestObjectTemplates->SearchByID(pObjDataType->m_strID);
				if (nCount!=1)
				{
					strErrorText.Format("DAType: id=%s 在DataTypeTemplates重复定义了 %d 次 ;",pObjDataType->m_strID ,nCount);
					AddCheckResultDLT860Tmps(strObjectID , strErrorText ,((CDAType*)pObjDataType)->m_strErrorPos);
				}
			}

			CheckDATypeOfGDW1396((CDAType*)pObjDataType ,pTemplates1396 ,pDLT860ModelChecks );
		}
		else if (pObjDataType->GetClassID() == SCLCLASSID_CSCLFILEENUMTYPE)
		{
			pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("EnumType-repeat");

			if (BeCheckThisObject(pCheckObject ,strObjectID))
			{
				nCount = pTestObjectTemplates->SearchByID(pObjDataType->m_strID);
				if (nCount!=1)
				{
					strErrorText.Format("EnumType: id=%s 在DataTypeTemplates重复定义了 %d 次 ;",pObjDataType->m_strID ,nCount);
					AddCheckResultDLT860Tmps(strObjectID , strErrorText ,((CEnumType*)pObjDataType)->m_strErrorPos);
				}
			}

			CheckEnumTypeOfGDW1396((CEnumType*)pObjDataType ,pTemplates1396 ,pDLT860ModelChecks );
		}
	}
}

void CSclCheckView::StartTemplatesCompare(CDLT860ModelChecks *pDLT860ModelChecks)
{
	if(TemplateCompareIsEmpty(pDLT860ModelChecks))
		return;

	CString  strObjectID;
	CCheckObject *pCheckObject = NULL;

	if (m_pSCLTestObjectFile == NULL)
	{
		m_pSCLTestObjectFile = new CSCLTemplates();
		m_pSCLTestObjectFile->m_bUTF8 = TRUE;
		m_pSCLTestObjectFile->OpenSclTemplatesFile(m_strSclFilePath);
	}
	else if (m_pSCLTestObjectFile->m_strName != m_strSclFilePath)
	{
		delete m_pSCLTestObjectFile;
		m_pSCLTestObjectFile = new CSCLTemplates();
		m_pSCLTestObjectFile->m_bUTF8 = TRUE;
		m_pSCLTestObjectFile->OpenSclTemplatesFile(m_strSclFilePath);
	}

	CSCLTemplates *pSCLDataTypeTemplates = new CSCLTemplates();
	CString strTmpPath = _P_GetBinPath();
	strTmpPath += "国网1396标准模板文件\\DataTypeTemplates.xml";
	pSCLDataTypeTemplates->OpenSclTemplatesFile(strTmpPath);

	CExBaseList *pDataTypeTemplates = (CExBaseList*)pSCLDataTypeTemplates->FindByID("DataTypeTemplates");
	CExBaseList *pTestObjectTemplates = (CExBaseList*)m_pSCLTestObjectFile->FindByID("DataTypeTemplates");
	if (pDataTypeTemplates==NULL)
	{
		AddCheckResultDLT860Tmps("fatalerror","DataTypeTemplates 模板文件存放位置有误，或模板文件被更改;");
		return;
	}
	if (pTestObjectTemplates== NULL)
	{
		AddCheckResultDLT860Tmps("fatalerror" ,"被测文件SCL根节点下不存在 DataTypeTemplates 节点;");
		return;
	}

	POS testObjecPos = pTestObjectTemplates->GetHeadPosition();

	CExBaseList *pObjDataType = NULL;
	CExBaseList *pTmpDataType = NULL;
	long nCount = 0;
	CString strErrorText;
	bool bDif = false;
	while (testObjecPos != NULL)
	{
		pObjDataType = (CExBaseList*)pTestObjectTemplates->GetNext(testObjecPos);

		nCount = pDataTypeTemplates->SearchByID(pObjDataType->m_strID);
		if (nCount != 0)
		{
			pTmpDataType = (CExBaseList*)pDataTypeTemplates->FindByID(pObjDataType->m_strID);
			bDif = DataTypeCompareWithTemplates(pTmpDataType , pObjDataType );

			if (bDif)
			{
				if (pObjDataType->GetClassID() == SCLCLASSID_CSCLFILELNODETYPE)
				{
					pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("LNodeType-conflict");

					if (BeCheckThisObject(pCheckObject ,strObjectID))
					{
						strErrorText.Format("LNodeType: id=%s desc=%s 与模板库中的 %s 文件中的同名类冲突;",pObjDataType->m_strID ,pObjDataType->m_strName,((CLNodeType*)pTmpDataType)->m_strPrivateMSG);
						AddCheckResultDLT860Tmps(strObjectID , strErrorText ,((CLNodeType*)pObjDataType)->m_strErrorPos);
					}
				}
				else if (pObjDataType->GetClassID() == SCLCLASSID_CSCLFILEDOTYPE)
				{
					pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DOType-conflict");

					if (BeCheckThisObject(pCheckObject ,strObjectID))
					{
						strErrorText.Format("DOType: id=%s 与模板库中的 %s 文件中的同名类冲突;",pObjDataType->m_strID ,((CDOType*)pTmpDataType)->m_strPrivateMSG);
						AddCheckResultDLT860Tmps(strObjectID , strErrorText ,((CDOType*)pObjDataType)->m_strErrorPos);
					}
				}
				else if (pObjDataType->GetClassID() == SCLCLASSID_CSCLFILEDATYPE)
				{
					pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DAType-conflict");

					if (BeCheckThisObject(pCheckObject ,strObjectID))
					{
						strErrorText.Format("DAType: id=%s 与模板库中的 %s 文件中的同名类冲突;",pObjDataType->m_strID ,((CDAType*)pTmpDataType)->m_strPrivateMSG);
						AddCheckResultDLT860Tmps(strObjectID , strErrorText ,((CDAType*)pObjDataType)->m_strErrorPos);
					}
				}
				else if (pObjDataType->GetClassID() == SCLCLASSID_CSCLFILEENUMTYPE)
				{
					pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("EnumType-conflict");

					if (BeCheckThisObject(pCheckObject ,strObjectID))
					{
						strErrorText.Format("EnumType: id=%s 与模板库中的 %s 文件中的同名类冲突;",pObjDataType->m_strID ,((CEnumType*)pTmpDataType)->m_strPrivateMSG);
						AddCheckResultDLT860Tmps(strObjectID , strErrorText ,((CEnumType*)pObjDataType)->m_strErrorPos);
					}
				}
			}
		}
	}

	delete pSCLDataTypeTemplates;
}

void CSclCheckView::AddNewDataTypesToTemplates(CString strSclFilePath ,BOOL bAddLNodeType ,BOOL bAddDOType ,BOOL bAddDAType ,BOOL bAddEnumType)
{
	CSCLTemplates *pSCLTestObjectFile = new CSCLTemplates();
	pSCLTestObjectFile->m_bUTF8 = TRUE;
	pSCLTestObjectFile->OpenSclTemplatesFile(strSclFilePath);

	CString strSCLFileName;
	long nIndex = strSclFilePath.ReverseFind('\\');
	strSCLFileName = strSclFilePath.Mid(nIndex+1);

	CExBaseList *pDataTypeTemplates = (CExBaseList*)m_pSCLDataTypeTemplates->FindByID("DataTypeTemplates");
	CExBaseList *pTestObjectTemplates = (CExBaseList*)pSCLTestObjectFile->FindByID("DataTypeTemplates");
	if (pDataTypeTemplates==NULL)
	{
		AddCheckResultDLT860Tmps("fatalerror","DataTypeTemplates 模板文件存放位置有误，或模板文件被更改;");
		return;
	}
	if (pTestObjectTemplates== NULL)
	{
		AddCheckResultDLT860Tmps("fatalerror" ,"被测文件SCL根节点下不存在 DataTypeTemplates 节点;");
		return;
	}

	POS testObjecPos = pTestObjectTemplates->GetHeadPosition();

	CExBaseList *pObjDataType = NULL;
	CLNodeType *pTmpLNodeType = NULL;
	CLNodeType *pObjLNodeType = NULL;
	CDOType *pTmpDOType = NULL;
	CDOType *pObjDOType = NULL;
	CDAType *pTmpDAType = NULL;
	CDAType *pObjDAType = NULL;
	CEnumType *pTmpEnumType = NULL;
	CEnumType *pObjEnumType = NULL;
	long nCount = 0;
	CString strErrorText;
	bool bDif = false;
	while (testObjecPos != NULL)
	{
		pObjDataType = (CExBaseList*)pTestObjectTemplates->GetNext(testObjecPos);

		nCount = pDataTypeTemplates->SearchByID(pObjDataType->m_strID);
		if (nCount == 0)
		{
			if ((pObjDataType->GetClassID() == SCLCLASSID_CSCLFILELNODETYPE)&&(bAddLNodeType))
			{
				pObjLNodeType = (CLNodeType *)pObjDataType;
				pTmpLNodeType = (CLNodeType *)pObjLNodeType->Clone();
				pTmpLNodeType->m_strPrivateMSG = strSCLFileName;
				pDataTypeTemplates->AddNewChild(pTmpLNodeType);

				strErrorText.Format("向模块库中新增 LNodeType: id=%s desc=%s ; 所在文件名:%s ;",pTmpLNodeType->m_strID ,pTmpLNodeType->m_strName ,strSCLFileName);
				AddCheckResultDLT860Tmps("tips" , strErrorText ,((CLNodeType*)pObjDataType)->m_strErrorPos);
			}
			else if ((pObjDataType->GetClassID() == SCLCLASSID_CSCLFILEDOTYPE)&&(bAddDOType))
			{
				pObjDOType = (CDOType *)pObjDataType;
				pTmpDOType = (CDOType *)pObjDOType->Clone();
				pTmpDOType->m_strPrivateMSG = strSCLFileName;
				pDataTypeTemplates->AddNewChild(pTmpDOType);

				strErrorText.Format("向模块库中新增 DOType: id=%s ; 所在文件名:%s ;",pObjDataType->m_strID ,strSCLFileName);
				AddCheckResultDLT860Tmps("tips" , strErrorText ,((CDOType*)pObjDataType)->m_strErrorPos);
			}
			else if ((pObjDataType->GetClassID() == SCLCLASSID_CSCLFILEDATYPE)&&(bAddDAType))
			{
				pObjDAType = (CDAType *)pObjDataType;
				pTmpDAType = (CDAType *)pObjDAType->Clone();
				pTmpDAType->m_strPrivateMSG = strSCLFileName;
				pDataTypeTemplates->AddNewChild(pTmpDAType);

				strErrorText.Format("向模块库中新增 DAType: id=%s ; 所在文件名:%s ;",pObjDataType->m_strID ,strSCLFileName);
				AddCheckResultDLT860Tmps("tips" , strErrorText ,((CDAType*)pObjDataType)->m_strErrorPos);
			}
			else if ((pObjDataType->GetClassID() == SCLCLASSID_CSCLFILEENUMTYPE)&&(bAddEnumType))
			{
				pObjEnumType = (CEnumType *)pObjDataType;
				pTmpEnumType = (CEnumType *)pObjEnumType->Clone();
				pTmpEnumType->m_strPrivateMSG = strSCLFileName;
				pDataTypeTemplates->AddNewChild(pTmpEnumType);

				strErrorText.Format("向模块库中新增 EnumType: id=%s ; 所在文件名:%s ;",pObjDataType->m_strID ,strSCLFileName);
				AddCheckResultDLT860Tmps("tips" , strErrorText ,((CEnumType*)pObjDataType)->m_strErrorPos);
			}
		}
	}
//	pSCLDataTypeTemplates->SaveSclTemplatesFile();

	delete pSCLTestObjectFile;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////通过tinyxml解析整个SCL文件获取结果的检测项目////////////////////////////////////////////////////////////

void CSclCheckView::GetIEDMSG(TiXmlElement* pTinyIEDNode , CString &strIEDMSG)
{
	strIEDMSG  = pTinyIEDNode->Attribute("name");
	CString strDesc = pTinyIEDNode->Attribute("desc");
	UTF8ToMultiByte(strDesc);

	if (strIEDMSG.IsEmpty())
	{
		strIEDMSG = strDesc;
	} 
	else if (!strDesc.IsEmpty())
	{
		strIEDMSG += "--";
		strIEDMSG += strDesc;
	}
}

void CSclCheckView::CheckAccessPointName(TiXmlElement* pTinyAccessPointNode ,CString strAccessPoint ,CString strIEDMSG ,CString  strObjectID)
{
	CString strErrorText;
	CString strErrorPos;
	CString strAccPoint = strAccessPoint;
	DelTailDigtal(&strAccPoint);

	if ((strAccPoint != "S")&&(strAccPoint != "M")&&(strAccPoint != "G"))
	{
		strErrorPos.Format("行号=%d ,列号=%d" ,pTinyAccessPointNode->Row(),pTinyAccessPointNode->Column() );
		strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 命名不符合 Q/GDW 1396中的7.1.2的要求;",strIEDMSG ,strAccessPoint);
		AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
	}
}

void CSclCheckView::GetIEDMaxConfigNum(TiXmlElement *pTinyAccessPointNode,long &nConfDataSet ,long &nConfReportControl ,long &nConfLogControl)
{
	CString strMaxNum;
	TiXmlElement *pTinyMaxNum = (TiXmlElement*)pTinyAccessPointNode->FirstChild("ConfDataSet");

	if (pTinyMaxNum != NULL)
	{
		strMaxNum = pTinyMaxNum->Attribute("max");
		if (!strMaxNum.IsEmpty())
		{
			nConfDataSet = atoi(strMaxNum);
		}
	}

	pTinyMaxNum = (TiXmlElement*)pTinyAccessPointNode->FirstChild("ConfReportControl");

	if (pTinyMaxNum != NULL)
	{
		strMaxNum = pTinyMaxNum->Attribute("max");
		if (!strMaxNum.IsEmpty())
		{
			nConfReportControl = atoi(strMaxNum);
		}
	}

	pTinyMaxNum = (TiXmlElement*)pTinyAccessPointNode->FirstChild("ConfLogControl");

	if (pTinyMaxNum != NULL)
	{
		strMaxNum = pTinyMaxNum->Attribute("max");
		if (!strMaxNum.IsEmpty())
		{
			nConfLogControl = atoi(strMaxNum);
		}
	}
}

void CSclCheckView::CheckLDeviceInst(TiXmlElement* pTinyLDNode ,CString strLDevice ,CString strAccessPoint ,CString strIEDMSG ,CString strObjectID)
{
	CString strErrorText;
	CString strErrorPos;
	CString strLDNew = strLDevice;

	if (strLDNew != "LD0")
	{
		DelTailDigtal(&strLDNew);

		if ((strLDNew != "MEAS")&&(strLDNew != "PROT")&&(strLDNew != "CTRL")&&(strLDNew != "PIGO")&&(strLDNew != "PISV")&&(strLDNew != "RPIT")&&(strLDNew != "RCD")&&(strLDNew != "MUGO")
			&&(strLDNew != "MUSV")&&(strLDNew != "PQLD"))
		{
			strErrorPos.Format("行号=%d ,列号=%d" ,pTinyLDNode->Row(),pTinyLDNode->Column() );
			strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\"下的 LD \"%s\"命名不符合 Q/GDW 1396中的7.1.3(或Q/GDW1650.3中5.2.3)的要求;",strIEDMSG ,strAccessPoint ,strLDevice);
			AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
		}
	}
}

void CSclCheckView::CheckDataSetRelated(TiXmlElement* pTinyLNNode ,TiXmlElement* pTinyLDNode ,map<CString ,TiXmlElement*> *mapLNFullName ,CString strLDevice ,
										CString strAccessPoint ,CString strIEDMSG ,CProjAppModelChecks *pProjAppModelChecks ,long &nCurDataSetNum)
{
	if (pTinyLNNode == NULL)
	{
		return;
	}

	CCheckObject *pCheckObject = NULL;
	CString strErrorText;
	CString  strObjectID;
	CString strErrorPos;
	CString strFCDAPath;
	CString strSecond;
	CString strLdInst;
	CString strDaName;
	CString strMsg;

	long nIndex = 0;

	map<CString ,CString> mapFCDA ,mapFCDALog;
	map<CString ,CString>::iterator iterFCDA ,iterFCDALog;

	TiXmlElement* pTinyDataSetNode = (TiXmlElement *)pTinyLNNode->FirstChild("DataSet");
	TiXmlElement* pTinyFCDANode = NULL;
	CString strDataSetName ,strDataSetNameNew;

	pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("LD-desc");

	if (BeCheckThisObject(pCheckObject ,strObjectID))
	{
		CString strLDdesc;
		strLDdesc = pTinyLDNode->Attribute("desc");

		if (strLDdesc.IsEmpty())
		{
			strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下的 LDevice \"%s\" 的 desc 属性为空 ,不符合标准要求;",strIEDMSG ,strAccessPoint ,strLDevice);
			strErrorPos.Format("行号=%d ,列号=%d" ,pTinyLDNode->Row(),pTinyLDNode->Column() );
			AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
		}
	}

	mapFCDA.clear();
	mapFCDALog.clear();

	while(pTinyDataSetNode != NULL)
	{
		if (strcmp(pTinyDataSetNode->Value() , "DataSet") != 0)
		{
			pTinyDataSetNode = (TiXmlElement *)pTinyDataSetNode->GetNext();
			continue;
		}
		nCurDataSetNum++;

		strDataSetName = pTinyDataSetNode->Attribute("name");
		strDataSetNameNew = strDataSetName;
		DelTailDigtal(&strDataSetNameNew);
		pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("DataSet-Name");

		if (BeCheckThisObject(pCheckObject ,strObjectID))
		{
			if ((strDataSetNameNew!="dsAin")&&(strDataSetNameNew!="dsDin")&&(strDataSetNameNew!="dsInterLock")&&(strDataSetNameNew!="dsAlarm")&&(strDataSetNameNew!="dsWarning")&&(strDataSetNameNew!="dsCommState")&&
				(strDataSetNameNew!="dsParameter")&&(strDataSetNameNew!="dsGOOSE")&&(strDataSetNameNew!="dsTripInfo")&&(strDataSetNameNew!="dsRelayDin")&&(strDataSetNameNew!="dsRelayEna")&&(strDataSetNameNew!="dsRelayRec")&&
				(strDataSetNameNew!="dsRelayAin")&&(strDataSetNameNew!="dsDeviceState")&&(strDataSetNameNew!="dsRelayState")&&(strDataSetNameNew!="dsRelayBlk")&&(strDataSetNameNew!="dsRelayFunEn")&&(strDataSetNameNew!="dsSetGrpNum")&&
				(strDataSetNameNew!="dsSetting")&&(strDataSetNameNew!="dsSV")&&(strDataSetNameNew!="dsLog")&&(strDataSetNameNew!="dsRtFre")&&(strDataSetNameNew!="dsRtMMXU")&&(strDataSetNameNew!="dsRtMSQI")&&(strDataSetNameNew!="dsRtHarm")
				&&(strDataSetNameNew!="dsRtIHarm")&&(strDataSetNameNew!="dsStMMXU")&&(strDataSetNameNew!="dsStMSQI")&&(strDataSetNameNew!="dsStHarm")&&(strDataSetNameNew!="dsStIHarm")&&(strDataSetNameNew!="dsPST")
				&&(strDataSetNameNew!="dsPLT")&&(strDataSetNameNew!="dsFluc")&&(strDataSetNameNew!="dsMMTR")&&(strDataSetNameNew!="dsEveQFVR")&&(strDataSetNameNew!="dsEveQIUB")&&(strDataSetNameNew!="dsEveQVUB")
				&&(strDataSetNameNew!="dsEveQVVR")&&(strDataSetNameNew!="dsEveRDRE")&&(strDataSetNameNew!="dsEveQVTR")&&(strDataSetNameNew!="dsEveQITR")&&(strDataSetNameNew!="dsDevice"))
			{
				strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下的 LDevice \"%s\" 的DataSet \"%s\" 命名不符合Q/GDW 1396中的8.3.1;",strIEDMSG ,strAccessPoint ,strLDevice ,strDataSetName);
				strErrorPos.Format("行号=%d ,列号=%d" ,pTinyDataSetNode->Row(),pTinyDataSetNode->Column() );
				AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
			}
		}

		pTinyFCDANode = (TiXmlElement*)pTinyDataSetNode->FirstChild("FCDA");
		
		nIndex = 0;

		while(pTinyFCDANode != NULL)
		{
			if (pTinyFCDANode->Type() == 2)//TINYXML_COMMENT
			{
				pTinyFCDANode = (TiXmlElement*)pTinyFCDANode->GetNext();
				continue;
			}

			nIndex++;
			strSecond.Format("数据集:%s ,序号%d" ,strDataSetName ,nIndex);

			strMsg.Format("本IED \"%s\"中 AccessPoint \"%s\" 下的 LDevice \"%s\" 的 %s " ,strIEDMSG ,strAccessPoint ,strLDevice ,strSecond );
			CheckFCDARefValid(pTinyFCDANode ,mapLNFullName, strMsg, strLdInst, strDaName, strFCDAPath,strDataSetNameNew, pProjAppModelChecks);

			if (strDataSetNameNew == "dsLog")
			{
				iterFCDALog = mapFCDALog.find(strFCDAPath);

				if (iterFCDALog != mapFCDALog.end())
				{
					pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("FCDA-Unique");

					if (BeCheckThisObject(pCheckObject ,strObjectID))
					{
						strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下的 LDevice \"%s\" 的 %s FCDA路径 \"%s\" 与 %s 重复 ;",strIEDMSG ,strAccessPoint ,strLDevice ,strSecond ,
							strFCDAPath,iterFCDALog->second );
						strErrorPos.Format("行号=%d ,列号=%d" ,pTinyFCDANode->Row(),pTinyFCDANode->Column() );
						AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
					}
				} 
				else
				{
					mapFCDALog.insert(make_pair(strFCDAPath ,strSecond));
				}
			} 
			else
			{
				iterFCDA = mapFCDA.find(strFCDAPath);

				if (iterFCDA != mapFCDA.end())
				{
					pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("FCDA-Unique");

					if (BeCheckThisObject(pCheckObject ,strObjectID))
					{
						strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下的 LDevice \"%s\" 的 %s FCDA路径 \"%s\" 与 %s 重复 ;",strIEDMSG ,strAccessPoint ,strLDevice ,strSecond ,strFCDAPath,iterFCDA->second );
						strErrorPos.Format("行号=%d ,列号=%d" ,pTinyFCDANode->Row(),pTinyFCDANode->Column() );
						AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
					}
				} 
				else
				{
					mapFCDA.insert(make_pair(strFCDAPath ,strSecond));
				}
			}

			pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("FCDA-FCD");

			if (BeCheckThisObject(pCheckObject ,strObjectID))
			{
				if ((strDataSetNameNew == "dsGOOSE")&&(strDaName.IsEmpty()))
				{
					strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下的 LDevice \"%s\" 的 %s FCDA路径 \"%s\" 不包含daName ,不符合dsGOOSE数据集定义 ;",strIEDMSG ,strAccessPoint ,strLDevice ,strSecond ,strFCDAPath);
					strErrorPos.Format("行号=%d ,列号=%d" ,pTinyFCDANode->Row(),pTinyFCDANode->Column() );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
				else if ((strDataSetNameNew != "dsGOOSE")&&(!strDaName.IsEmpty()))
				{
					strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下的 LDevice \"%s\" 的 %s FCDA路径 \"%s\" 包含daName ,不符合非dsGOOSE数据集定义 ;",strIEDMSG ,strAccessPoint ,strLDevice ,strSecond ,strFCDAPath);
					strErrorPos.Format("行号=%d ,列号=%d" ,pTinyFCDANode->Row(),pTinyFCDANode->Column() );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
			}

			pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("FCDA-LdInst");

			if (BeCheckThisObject(pCheckObject ,strObjectID))
			{
				if (strLdInst != strLDevice)
				{
					strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下的 LDevice \"%s\" 的 %s FCDA路径 \"%s\" 跨LD不符合标准要求 ;",strIEDMSG ,strAccessPoint ,strLDevice ,strSecond ,strFCDAPath);
					strErrorPos.Format("行号=%d ,列号=%d" ,pTinyFCDANode->Row(),pTinyFCDANode->Column() );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
			}
			
			pTinyFCDANode = (TiXmlElement*)pTinyFCDANode->GetNext();
		}

		if (nIndex > 256)
		{
			pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("FCDA-Number");

			if (BeCheckThisObject(pCheckObject ,strObjectID))
			{
				strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下的 LDevice \"%s\" 的数据集 %s 中数据集成员 %ld个, 定义超过了256个 ;",strIEDMSG ,strAccessPoint ,strLDevice ,strDataSetName ,nIndex);
				strErrorPos.Format("行号=%d ,列号=%d" ,pTinyDataSetNode->Row(),pTinyDataSetNode->Column() );
				AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
			}
		}

		pTinyDataSetNode = (TiXmlElement *)pTinyDataSetNode->GetNext();
	}

	mapFCDA.clear();
	mapFCDALog.clear();
}

void CSclCheckView::CheckInputsExtRef(TiXmlElement *pTinyLN0Node ,TiXmlElement *pTinyLDNode ,map<CString ,TiXmlElement*> *mapLNFullName ,CString strLDevice ,CString strAccessPoint ,
					 CString strIEDMSG ,CProjAppModelChecks *pProjAppModelChecks )
{
	if (pTinyLN0Node == NULL)
	{
		return;
	}

	CCheckObject *pCheckObject = NULL;
	CString strErrorText;
	CString  strObjectID;
	CString strErrorPos;
	CString strIEDPath;

	TiXmlElement* pTinyInputs = (TiXmlElement *)pTinyLN0Node->FirstChild("Inputs");
	TiXmlElement* pTinyExtRef = NULL;

	while(pTinyInputs != NULL)
	{
		if (strcmp(pTinyInputs->Value(),"Inputs") == 0)
		{
			pTinyExtRef = (TiXmlElement *)pTinyInputs->FirstChild();

			while(pTinyExtRef != NULL)
			{
				CheckIntAddrOfExRef(pTinyExtRef ,pTinyExtRef->Attribute("intAddr") ,mapLNFullName ,strLDevice ,strAccessPoint ,strIEDMSG ,pProjAppModelChecks);

				pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("Inputs-ExtAddr");

				if (BeCheckThisObject(pCheckObject ,strObjectID))
				{
					CString strName = pTinyExtRef->Attribute("iedName");
					CExBaseList *pIED = (CExBaseList *)m_oTinySCLStation.FindByID(strName);

					if (pIED == NULL)
					{
						strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下的 LDevice \"%s\" 的inputs 关联的外部 iedName \"%s\" 不存在;",strIEDMSG ,strAccessPoint ,strLDevice ,strName );
						strErrorPos.Format("行号=%d ,列号=%d" ,pTinyExtRef->Row(),pTinyExtRef->Column() );
						AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
					} 
					else
					{
						strName = pTinyExtRef->Attribute("ldInst");
						CExBaseList *pLDevice = (CExBaseList *)pIED->FindByID(strName);

						if (pLDevice == NULL)
						{
							strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下的 LDevice \"%s\" 的inputs 关联的外部IED \"%s\" 的 ldInst \"%s\" 不存在;",strIEDMSG ,
								strAccessPoint ,strLDevice ,pIED->m_strName , strName );
							strErrorPos.Format("行号=%d ,列号=%d" ,pTinyExtRef->Row(),pTinyExtRef->Column() );
							AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
						} 
						else
						{
							strIEDPath = strName;
							strIEDPath += '/';
							strIEDPath += pTinyExtRef->Attribute("prefix");
							strIEDPath += pTinyExtRef->Attribute("lnClass");
							strIEDPath += pTinyExtRef->Attribute("lnInst");
							strIEDPath += '.';
							strIEDPath += pTinyExtRef->Attribute("doName");
							strName = pTinyExtRef->Attribute("daName");

							if (!strName.IsEmpty())
							{
								strIEDPath += '.';
								strIEDPath += strName;
							}
							CTinyExtRef *pExtRef = (CTinyExtRef *)pLDevice->FindByID(strIEDPath);

							if (pExtRef == NULL)
							{
								strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下的 LDevice \"%s\" 的inputs 关联的外部 IED \"%s\" 的通道路径 \"%s\" 不存在;",
									strIEDMSG ,strAccessPoint ,strLDevice ,pIED->m_strName ,strIEDPath );
								strErrorPos.Format("行号=%d ,列号=%d" ,pTinyExtRef->Row(),pTinyExtRef->Column() );
								AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
							} 
						}
					}
				}
				pTinyExtRef = (TiXmlElement *)pTinyExtRef->GetNext();
			}
		}

		pTinyInputs = (TiXmlElement *)pTinyInputs->GetNext();
	}

}

void CSclCheckView::CheckIntAddrOfExRef(TiXmlElement *pTinyExtRef,CString strIntAddr ,map<CString ,TiXmlElement*> *mapLNFullName ,CString strLDevice ,CString strAccessPoint ,CString strIEDMSG ,
										CProjAppModelChecks *pProjAppModelChecks)
{
	CCheckObject *pCheckObject = NULL;
	CString strErrorText;
	CString  strObjectID;
	CString strErrorPos;

	CString strPort,strIntPath = strIntAddr;
	long nIndex = strIntAddr.Find(':');

	pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("physConn-InPort");
	if (nIndex != -1)
	{
		strPort = strIntAddr.Left(nIndex);
		strIntPath = strIntAddr.Mid(nIndex + 1);

		if (BeCheckThisObject(pCheckObject ,strObjectID))
		{
			if (!CheckPortNameValid(strPort))
			{
				strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下的 LDevice \"%s\" 的inputs 关联的外部索引intAddr \"%s\" 中输入端端口的描述信息格式出错 ;",strIEDMSG ,strAccessPoint ,strLDevice ,strIntAddr );
				strErrorPos.Format("行号=%d ,列号=%d" ,pTinyExtRef->Row(),pTinyExtRef->Column() );
				AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
			}
		}
	}
	else if (BeCheckThisObject(pCheckObject ,strObjectID))
	{
		strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下的 LDevice \"%s\" 的inputs 关联的外部索引intAddr \"%s\" 中缺少输入端端口的描述信息 ;",strIEDMSG ,strAccessPoint ,strLDevice ,strIntAddr );
		strErrorPos.Format("行号=%d ,列号=%d" ,pTinyExtRef->Row(),pTinyExtRef->Column() );
		AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
	}

	pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("Inputs-intAddr");

	if (BeCheckThisObject(pCheckObject ,strObjectID))
	{
		nIndex = strIntPath.Find('/');
		strIntPath = strIntPath.Mid(nIndex + 1);
		nIndex = strIntPath.Find('.');
		CString strLNName = strIntPath.Left(nIndex);
		strIntPath = strIntPath.Mid(nIndex + 1);
		map<CString ,TiXmlElement*>::iterator iterLNFullName;
		iterLNFullName = mapLNFullName->find(strLNName);

		TiXmlElement *pTinyLNNode = NULL;
		TiXmlElement *pTinyDOI = NULL;
		TiXmlElement *pTinySDI = NULL;

		if (iterLNFullName == mapLNFullName->end())
		{
			strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下的 LDevice \"%s\" 的inputs 关联的外部索引intAddr \"%s\" 未找到对应实例化LN节点 \"%s\" ;",strIEDMSG ,strAccessPoint ,strLDevice ,strIntAddr ,strLNName );
			strErrorPos.Format("行号=%d ,列号=%d" ,pTinyExtRef->Row(),pTinyExtRef->Column() );
			AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
		} 
		else
		{
			pTinyLNNode = iterLNFullName->second;
			nIndex = strIntPath.Find('.');
			CString strDOName = strIntPath;

			if (nIndex != -1)
			{
				strDOName = strIntPath.Left(nIndex);
				strIntPath = strIntPath.Mid(nIndex + 1);
			}

			if (!FindTinyChildAttrValue(pTinyLNNode ,&pTinyDOI ,"name" ,strDOName))
			{
				strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下的 LDevice \"%s\" 的inputs 关联的外部索引intAddr \"%s\" 未找到对应实例化DOI name = \"%s\" ;",strIEDMSG ,strAccessPoint ,strLDevice ,
					strIntAddr ,strDOName );
				strErrorPos.Format("行号=%d ,列号=%d" ,pTinyLNNode->Row(),pTinyLNNode->Column() );
				AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
			}
			else if (nIndex != -1)
			{
				nIndex = strIntPath.Find('.');
				strDOName = strIntPath;

				if (nIndex != -1)
				{
					strDOName = strIntPath.Left(nIndex);
					strIntPath = strIntPath.Mid(nIndex + 1);
				}

				if (!FindTinyChildAttrValue(pTinyDOI ,&pTinySDI ,"name" ,strDOName))
				{
					strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下的 LDevice \"%s\" 的inputs 关联的外部索引intAddr \"%s\" 未找到对应实例化SDI 或 DAI name = \"%s\" ;",strIEDMSG ,strAccessPoint ,strLDevice ,
						strIntAddr ,strDOName );
					strErrorPos.Format("行号=%d ,列号=%d" ,pTinyDOI->Row(),pTinyDOI->Column() );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
				else if (nIndex != -1)
				{
					TiXmlElement *pTinyDAI = NULL;
					if (!FindTinyChildAttrValue(pTinySDI ,&pTinyDAI ,"name" ,strIntPath))
					{
						strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下的 LDevice \"%s\" 的inputs 关联的外部索引intAddr \"%s\" 未找到对应实例化DAI 或 DAI name = \"%s\" ;",strIEDMSG ,strAccessPoint ,strLDevice ,
							strIntAddr ,strIntPath );
						strErrorPos.Format("行号=%d ,列号=%d" ,pTinyDAI->Row(),pTinyDAI->Column() );
						AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
					}
				}
			}
			
		}
	}
}

void CSclCheckView::CheckReportCtrlRelated(TiXmlElement *pTinyLN0Node ,std::list<CString> list_DataSetName ,CString strLDevice ,CString strAccessPoint ,CString strIEDMSG ,
										   CProjAppModelChecks *pProjAppModelChecks ,long &nCurRptNum)
{
	if (pTinyLN0Node == NULL)
	{
		return;
	}

	CCheckObject *pCheckObject = NULL;
	CString strErrorText;
	CString  strObjectID;
	CString strErrorPos;
	CString strDataSetName;
	CString strRptID;
	CString strRptName;
	CString strRptIDPort = strLDevice;
	strRptIDPort += "/LLN0";
	long nMax = 0;
	CString strMax;

	TiXmlElement *pTinyRptEnabled;

	std::list<CString>::iterator iter = list_DataSetName.begin();
	std::list<CString>::iterator iend = list_DataSetName.end();

	TiXmlElement *pTinyReportCtrl = (TiXmlElement*)pTinyLN0Node->FirstChild("ReportControl");
	while(pTinyReportCtrl != NULL)
	{
		if (strcmp(pTinyReportCtrl->Value() ,"ReportControl") == 0)
		{
			nCurRptNum++;
			strRptName = pTinyReportCtrl->Attribute("name");

			pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("ReportCtrl-DataSet");

			if(BeCheckThisObject(pCheckObject ,strObjectID))
			{
				strDataSetName = pTinyReportCtrl->Attribute("datSet");
				for(iter = list_DataSetName.begin(); iter != iend; iter++)
				{
					if (*iter == strDataSetName)
					{
						break;
					}
				}

				if (iter == iend)
				{
					strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下, LDevice \"%s\"对象中 报告控制块 \"%s\" 关联的数据集 \"%s\" 未定义;",strIEDMSG ,strAccessPoint ,strLDevice ,
						strRptName ,strDataSetName);
					strErrorPos.Format("行号=%d ,列号=%d" ,pTinyReportCtrl->Row(),pTinyReportCtrl->Column() );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
			}

			pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("ReportCtrl-rptID");

			if(BeCheckThisObject(pCheckObject ,strObjectID))
			{
				strRptID = pTinyReportCtrl->Attribute("rptID");

				if (strRptID.Find(strRptIDPort) >= 0)
				{
					strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下, LDevice \"%s\"对象中 报告控制块 \"%s\" 的 rptID = \"%s\" 错误, 应该为上送的路径;",strIEDMSG ,strAccessPoint ,
						strLDevice ,strRptName ,strRptID);
					strErrorPos.Format("行号=%d ,列号=%d" ,pTinyReportCtrl->Row(),pTinyReportCtrl->Column() );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
			}

			pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("ReportCtrlName-Valid");

			if(BeCheckThisObject(pCheckObject ,strObjectID))
			{
				if (!((strRptName.Find("urcb") == 0)||((strRptName.Find("brcb") == 0))))
				{
					strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下, LDevice \"%s\"对象中 报告控制块 \"%s\" 的命名错误, 应该以 urcb 或 brcb 开头;",strIEDMSG ,strAccessPoint ,
						strLDevice ,strRptName );
					strErrorPos.Format("行号=%d ,列号=%d" ,pTinyReportCtrl->Row(),pTinyReportCtrl->Column() );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
			}

			pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("RptEnabled-Max");

			if(BeCheckThisObject(pCheckObject ,strObjectID))
			{
				pTinyRptEnabled = (TiXmlElement *)pTinyReportCtrl->FirstChild("RptEnabled");

				if (pTinyRptEnabled != NULL)
				{
					strMax = pTinyRptEnabled->Attribute("max");
					nMax = atoi(strMax);

					if (nMax < 12)
					{
						strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下, LDevice \"%s\"对象中 报告控制块 \"%s\" 的RptEnabled 下的 max = \"%s\" 小于12 或 无效 ;",strIEDMSG ,strAccessPoint ,
							strLDevice ,strRptName ,strMax );
						strErrorPos.Format("行号=%d ,列号=%d" ,pTinyRptEnabled->Row(),pTinyRptEnabled->Column() );
						AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
					}
				} 
				else
				{
					strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下, LDevice \"%s\"对象中 报告控制块 \"%s\" 的RptEnabled 数据未初始化 ;",strIEDMSG ,strAccessPoint ,
						strLDevice ,strRptName );
					strErrorPos.Format("行号=%d ,列号=%d" ,pTinyReportCtrl->Row(),pTinyReportCtrl->Column() );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
			}
		}

		pTinyReportCtrl = (TiXmlElement*)pTinyReportCtrl->GetNext();
	}
}

void CSclCheckView::CheckLogCtrlRelated(TiXmlElement *pTinyLN0Node ,std::list<CString> list_DataSetName ,CString strLDevice ,CString strAccessPoint ,CString strIEDMSG ,
										   CProjAppModelChecks *pProjAppModelChecks ,long &nCurLogNum)
{
	if (pTinyLN0Node == NULL)
	{
		return;
	}

	CCheckObject *pCheckObject = NULL;
	CString strErrorText;
	CString  strObjectID;
	CString strErrorPos;
	CString strDataSetName;

	std::list<CString>::iterator iter = list_DataSetName.begin();
	std::list<CString>::iterator iend = list_DataSetName.end();

	TiXmlElement *pTinyLogCtrl = (TiXmlElement*)pTinyLN0Node->FirstChild("LogControl");
	while(pTinyLogCtrl != NULL)
	{
		if (strcmp(pTinyLogCtrl->Value() ,"LogControl") == 0)
		{
			nCurLogNum++;
			pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("LogCtrl-DataSet");

			if(BeCheckThisObject(pCheckObject ,strObjectID))
			{
				strDataSetName = pTinyLogCtrl->Attribute("datSet");

				for(iter = list_DataSetName.begin(); iter != iend; iter++)
				{
					if (*iter == strDataSetName)
					{
						break;
					}
				}

				if (iter == iend)
				{
					strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下, LDevice \"%s\"对象中 日志控制块 \"%s\" 关联的数据集 \"%s\" 未定义;",strIEDMSG ,strAccessPoint ,strLDevice ,
						pTinyLogCtrl->Attribute("name") ,strDataSetName);
					strErrorPos.Format("行号=%d ,列号=%d" ,pTinyLogCtrl->Row(),pTinyLogCtrl->Column() );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
			}
		}

		pTinyLogCtrl = (TiXmlElement*)pTinyLogCtrl->GetNext();
	}
}

void CSclCheckView::CheckSMVCtrlRelated(TiXmlElement *pTinyLN0Node ,std::list<CString> list_DataSetName ,CString strLDevice ,CString strAccessPoint ,CString strIEDMSG ,
										CProjAppModelChecks *pProjAppModelChecks)
{
	if (pTinyLN0Node == NULL)
	{
		return;
	}

	CCheckObject *pCheckObject = NULL;
	CString strErrorText;
	CString  strObjectID;
	CString strErrorPos;
	CString strDataSetName;

	std::list<CString>::iterator iter = list_DataSetName.begin();
	std::list<CString>::iterator iend = list_DataSetName.end();

	TiXmlElement *pTinySMVCtrl = (TiXmlElement*)pTinyLN0Node->FirstChild("SampledValueControl");
	while(pTinySMVCtrl != NULL)
	{
		if (strcmp(pTinySMVCtrl->Value() ,"SampledValueControl") == 0)
		{
			pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("SMVCtrl-DataSet");

			if(BeCheckThisObject(pCheckObject ,strObjectID))
			{
				strDataSetName = pTinySMVCtrl->Attribute("datSet");

				for(iter = list_DataSetName.begin(); iter != iend; iter++)
				{
					if (*iter == strDataSetName)
					{
						break;
					}
				}

				if (iter == iend)
				{
					strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下, LDevice \"%s\"对象中 采样值控制块 \"%s\" 关联的数据集 \"%s\" 未定义;",strIEDMSG ,strAccessPoint ,strLDevice ,
						pTinySMVCtrl->Attribute("name") ,strDataSetName);
					strErrorPos.Format("行号=%d ,列号=%d" ,pTinySMVCtrl->Row(),pTinySMVCtrl->Column() );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
			}
		}

		pTinySMVCtrl = (TiXmlElement*)pTinySMVCtrl->GetNext();
	}
}

void CSclCheckView::CheckGSECtrlRelated(TiXmlElement *pTinyLN0Node ,std::list<CString> list_DataSetName ,CString strLDevice ,CString strAccessPoint ,CString strIEDMSG ,
										CProjAppModelChecks *pProjAppModelChecks)
{
	if (pTinyLN0Node == NULL)
	{
		return;
	}

	CCheckObject *pCheckObject = NULL;
	CString strErrorText;
	CString  strObjectID;
	CString strErrorPos;
	CString strDataSetName;

	std::list<CString>::iterator iter = list_DataSetName.begin();
	std::list<CString>::iterator iend = list_DataSetName.end();

	TiXmlElement *pTinyGSECtrl = (TiXmlElement*)pTinyLN0Node->FirstChild("GSEControl");
	while(pTinyGSECtrl != NULL)
	{
		if (strcmp(pTinyGSECtrl->Value() ,"GSEControl") == 0)
		{
			pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("GSECtrl-DataSet");

			if(BeCheckThisObject(pCheckObject ,strObjectID))
			{
				strDataSetName = pTinyGSECtrl->Attribute("datSet");

				for(iter = list_DataSetName.begin(); iter != iend; iter++)
				{
					if (*iter == strDataSetName)
					{
						break;
					}
				}

				if (iter == iend)
				{
					strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下, LDevice \"%s\"对象中 GOOSE控制块 \"%s\" 关联的数据集 \"%s\" 未定义;",strIEDMSG ,strAccessPoint ,strLDevice ,
						pTinyGSECtrl->Attribute("name") ,strDataSetName);
					strErrorPos.Format("行号=%d ,列号=%d" ,pTinyGSECtrl->Row(),pTinyGSECtrl->Column() );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
			}
		}

		pTinyGSECtrl = (TiXmlElement*)pTinyGSECtrl->GetNext();
	}
}

void CSclCheckView::CheckSettingCtrlRelated(TiXmlElement *pTinyLN0Node ,std::list<CString> list_DataSetName ,CString strLDevice ,CString strAccessPoint ,CString strIEDMSG ,
										CProjAppModelChecks *pProjAppModelChecks)
{
	if (pTinyLN0Node == NULL)
	{
		return;
	}

	CCheckObject *pCheckObject = NULL;
	CString strErrorText;
	CString  strObjectID;
	CString strErrorPos;
	CString strDataSetName;
	BOOL bCheck = FALSE;

	std::list<CString>::iterator iter = list_DataSetName.begin();
	std::list<CString>::iterator iend = list_DataSetName.end();

	pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("SettingCtrl-Related");

	if(BeCheckThisObject(pCheckObject ,strObjectID))
	{
		for(iter = list_DataSetName.begin(); iter != iend; iter++)
		{
			if ((*iter).Find("dsSetting") == 0)
			{
				bCheck = TRUE;
				break;
			}
		}

		TiXmlElement *pTinySettingCtrl = (TiXmlElement*)pTinyLN0Node->FirstChild("SettingControl");

		if (pTinySettingCtrl != NULL)
		{
			long nNumSGs = -1;
			CString strNum = pTinySettingCtrl->Attribute("numOfSGs");

			if (strNum.IsEmpty())
			{
				strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下, LDevice \"%s\"对象中 的定值控制块中缺少 numOfSGs(定值区数目)属性;",strIEDMSG ,strAccessPoint ,strLDevice);
				strErrorPos.Format("行号=%d ,列号=%d" ,pTinySettingCtrl->Row(),pTinySettingCtrl->Column() );
				AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
			} 
			else
			{
				nNumSGs = atoi(strNum);
				if (nNumSGs < 2)
				{
					strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下, LDevice \"%s\"对象中 的定值控制块中 numOfSGs(定值区数目)属性值小于2;",strIEDMSG ,strAccessPoint ,strLDevice);
					strErrorPos.Format("行号=%d ,列号=%d" ,pTinySettingCtrl->Row(),pTinySettingCtrl->Column() );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
			}

			strNum = pTinySettingCtrl->Attribute("actSG");

			if (strNum.IsEmpty())
			{
				strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下, LDevice \"%s\"对象中 的定值控制块中缺少 actSG(激活定值区)属性;",strIEDMSG ,strAccessPoint ,strLDevice);
				strErrorPos.Format("行号=%d ,列号=%d" ,pTinySettingCtrl->Row(),pTinySettingCtrl->Column() );
				AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
			} 
			else
			{
				long nActSG = atoi(strNum);

				if ((nNumSGs != -1)&&(nActSG > nNumSGs))
				{
					strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下, LDevice \"%s\"对象中 的定值控制块中 actSG(激活定值区)属性值\"%ld\" 大于 numOfSGs(定值区数目)属性值\"%ld\";",strIEDMSG ,strAccessPoint ,
						strLDevice ,nActSG ,nNumSGs);
					strErrorPos.Format("行号=%d ,列号=%d" ,pTinySettingCtrl->Row(),pTinySettingCtrl->Column() );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
			}
		}
		else if (bCheck)
		{
			strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下, LDevice \"%s\"对象中 包含定值数据集 但缺少定值控制块;",strIEDMSG ,strAccessPoint ,strLDevice);
			strErrorPos.Format("行号=%d ,列号=%d" ,pTinyLN0Node->Row(),pTinyLN0Node->Column() );
			AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
		}
		else if (strLDevice == "PROT")
		{
			strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下, LDevice \"%s\"对象中 缺少定值控制块;",strIEDMSG ,strAccessPoint ,strLDevice);
			strErrorPos.Format("行号=%d ,列号=%d" ,pTinyLN0Node->Row(),pTinyLN0Node->Column() );
			AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
		}
	}
}

void CSclCheckView::GetSDOFromDoName(CString &strDOName ,CString &strSDOName )
{
	long nIndex = strDOName.ReverseFind('.');

	if (nIndex != -1)
	{
		strSDOName = strDOName.Mid(nIndex+1);
		strDOName = strDOName.Left(nIndex);
	}
}

void CSclCheckView::CheckFCDARefValid(TiXmlElement* pTinyFCDANode , map<CString ,TiXmlElement*> *mapLNFullName ,CString strMsg ,CString &strLdInst, CString &strDaName, CString &strFCDAPath, 
									 CString strDataSetNameNew , CProjAppModelChecks *pProjAppModelChecks)
{
	CCheckObject *pCheckObject = NULL;
	CString strErrorText;
	CString  strObjectID;
	CString strErrorPos;

	CString strLnFullName;
	CString strDOName;
	CString strSDOName;
	map<CString ,TiXmlElement*>::iterator iterLNFullName;

	TiXmlElement* pTinyLNNode = NULL;
	TiXmlElement* pTinyDOI = NULL;
	TiXmlElement *pTinySDO = NULL;
	TiXmlElement* pTinyDAI = NULL;

	strLdInst = pTinyFCDANode->Attribute("ldInst");
	strDaName = pTinyFCDANode->Attribute("daName");

	strFCDAPath = strLdInst;
	strFCDAPath += "/";
	strLnFullName = pTinyFCDANode->Attribute("prefix");
	strLnFullName += pTinyFCDANode->Attribute("lnClass");
	strLnFullName += pTinyFCDANode->Attribute("lnInst");
	strFCDAPath += strLnFullName;
	strFCDAPath += "$";
	strFCDAPath += pTinyFCDANode->Attribute("fc");
	strFCDAPath += "$";
	strDOName = pTinyFCDANode->Attribute("doName");
	strFCDAPath += strDOName;

	if (!strDaName.IsEmpty())
	{
		strFCDAPath += ".";
		strFCDAPath += strDaName;
	}

	GetSDOFromDoName(strDOName ,strSDOName );

	pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("FCDA-RefValid");

	iterLNFullName = mapLNFullName->find(strLnFullName);

	if (iterLNFullName != mapLNFullName->end())
	{
		pTinyLNNode = iterLNFullName->second;

		if (!FindTinyChildAttrValue(pTinyLNNode ,&pTinyDOI ,"name" ,strDOName))
		{
			if (BeCheckThisObject(pCheckObject ,strObjectID))
			{
				strErrorText.Format("%s 的FCDA路径 \"%s\" ,其中DO name = \"%s\"未实例化;", strMsg , strFCDAPath ,strDOName);
				strErrorPos.Format("行号=%d ,列号=%d" ,pTinyLNNode->Row(),pTinyLNNode->Column() );
				AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
			}
		}
		else
		{
			if (!strSDOName.IsEmpty())
			{
				if ((!FindTinyChildAttrValue(pTinyDOI ,&pTinySDO ,"name" ,strSDOName))&&(BeCheckThisObject(pCheckObject ,strObjectID)))
				{
					strErrorText.Format("%s 的FCDA路径 \"%s\" ,其中SDO name = \"%s\"未实例化;", strMsg , strFCDAPath ,strSDOName);
					strErrorPos.Format("行号=%d ,列号=%d" ,pTinyDOI->Row(),pTinyDOI->Column() );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
			}
			else
			{
				pTinySDO = pTinyDOI;
			}

			if ((!strDaName.IsEmpty())&&(pTinySDO != NULL))
			{
				if ((!FindTinyChildAttrValue(pTinySDO ,&pTinyDAI ,"name" ,strDaName))&&(BeCheckThisObject(pCheckObject ,strObjectID)))
				{
					strErrorText.Format("%s 的FCDA路径 \"%s\" ,其中DA name = \"%s\"未实例化;", strMsg , strFCDAPath ,strDaName);
					strErrorPos.Format("行号=%d ,列号=%d" ,pTinySDO->Row(),pTinySDO->Column() );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
			}

			if (strDataSetNameNew == "dsRelayEna")//检查保护压板数据的ctlModel,sboTimeout数值初始化情况
			{
				CheckRelayEnaInit(pTinyDOI ,strMsg ,strFCDAPath ,pProjAppModelChecks);
			}
		}
	} 
	else if(BeCheckThisObject(pCheckObject ,strObjectID))
	{
		strErrorText.Format("%s 的FCDA路径 \"%s\" ,其中LN = \"%s\"未实例化;", strMsg , strFCDAPath ,strLnFullName);
		strErrorPos.Format("行号=%d ,列号=%d" ,pTinyFCDANode->Row(),pTinyFCDANode->Column() );
		AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
	}

	pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("LN-DOIdesc");

	if(BeCheckThisObject(pCheckObject ,strObjectID))
	{
		CString strDesc;
		if (pTinyLNNode != NULL)
		{
			strDesc = pTinyLNNode->Attribute("desc");

			if (strDesc.IsEmpty())
			{
				strErrorText.Format("%s 的FCDA路径 \"%s\" ,其中LN = \"%s\" 的desc 属性为空;", strMsg , strFCDAPath ,strLnFullName);
				strErrorPos.Format("行号=%d ,列号=%d" ,pTinyLNNode->Row(),pTinyLNNode->Column() );
				AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
			}

			if (pTinyDOI != NULL)
			{
				strDesc = pTinyDOI->Attribute("desc");

				if (strDesc.IsEmpty())
				{
					strErrorText.Format("%s 的FCDA路径 \"%s\" ,其中DOI name = \"%s\" 的desc 属性为空;", strMsg , strFCDAPath ,strDOName);
					strErrorPos.Format("行号=%d ,列号=%d" ,pTinyDOI->Row(),pTinyDOI->Column() );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}

				if (FindTinyChildAttrValue(pTinySDO ,&pTinyDAI ,"name" ,"dU" ))
				{
					pTinyDAI = (TiXmlElement *)pTinyDAI->FirstChild();

					if (pTinyDAI == NULL)
					{
						strErrorText.Format("%s 的FCDA路径 \"%s\" ,其中DOI name = \"%s\" 下的dU 未创建Val子节点;", strMsg , strFCDAPath ,strDOName);
						strErrorPos.Format("行号=%d ,列号=%d" ,pTinySDO->Row(),pTinySDO->Column() );
						AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
					} 
					else
					{
						strDesc = pTinyDAI->FirstChildText();

						UTF8ToMultiByte(strDesc);

						if (strDesc.IsEmpty())
						{
							strErrorText.Format("%s 的FCDA路径 \"%s\" ,其中dU 赋值为空;", strMsg , strFCDAPath );
							strErrorPos.Format("行号=%d ,列号=%d" ,pTinyDAI->Row(),pTinyDAI->Column() );
							AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
						}
					}
				} 
				else
				{
					strErrorText.Format("%s 的FCDA路径 \"%s\" ,关联的dU 未实例化;", strMsg , strFCDAPath);
					strErrorPos.Format("行号=%d ,列号=%d" ,pTinyFCDANode->Row(),pTinyFCDANode->Column() );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
			} 
		}
	}
}

BOOL CSclCheckView::FindTinyChildAttrValue(TiXmlElement *pTinyElement ,TiXmlElement **pTinyChild ,CString strAttrName ,CString strChildAttrValue)
{
	*pTinyChild = (TiXmlElement *)pTinyElement->FirstChild();

	while((*pTinyChild) != NULL)
	{
		if ((*pTinyChild)->Type() != 2)//TINYXML_COMMENT
		{
			const char* pTmp = (*pTinyChild)->Attribute(strAttrName);

			if (pTmp != NULL)
			{
				if (strcmp(pTmp , strChildAttrValue) == 0)
				{
					break;
				}
			}
		}

		*pTinyChild = (TiXmlElement *)(*pTinyChild)->GetNext();
	}
	return (*pTinyChild) != NULL;
}

void CSclCheckView::CheckPhysConnPort(TiXmlElement *pTinyCommu ,CString strObjectID )
{
	if (pTinyCommu == NULL)
	{
		return;
	}

	CString strErrorText;
	CString strErrorPos;

	CString strSubNetwork;
	CString strIEDMSG;
	CString strPhysConnType;
	CString strPortName;

	BOOL bHasPhysConn;

	TiXmlElement *pTinySubNetwork = (TiXmlElement*)pTinyCommu->FirstChild();
	TiXmlElement *pTinyConnectedAP = NULL;
	TiXmlElement *pTinyPhysConn = NULL;
	TiXmlElement *pTinyP = NULL;
	while(pTinySubNetwork != NULL)
	{
		if (strcmp(pTinySubNetwork->Value() , "SubNetwork") == 0 )
		{
			GetTinyDescAndName(pTinySubNetwork ,strSubNetwork);
			pTinyConnectedAP = (TiXmlElement*)pTinySubNetwork->FirstChild();

			while(pTinyConnectedAP != NULL)
			{
				if (strcmp(pTinyConnectedAP->Value() , "ConnectedAP") == 0 )
				{
					bHasPhysConn = FALSE;
					strIEDMSG.Format("iedName == \"%s\" 访问点名称 \"%s\" ",pTinyConnectedAP->Attribute("iedName") ,pTinyConnectedAP->Attribute("apName"));
					pTinyPhysConn = (TiXmlElement*)pTinyConnectedAP->FirstChild();

					while(pTinyPhysConn != NULL)
					{
						if (strcmp(pTinyPhysConn->Value() , "PhysConn") == 0 )
						{
							bHasPhysConn = TRUE;
							strPhysConnType = pTinyPhysConn->Attribute("type");
							pTinyP = (TiXmlElement*)pTinyPhysConn->FirstChild();

							while(pTinyP != NULL)
							{
								if (strcmp(pTinyP->Attribute("type") , "Port") == 0 )
								{
									break;
								}

								pTinyP = (TiXmlElement*)pTinyP->GetNext();
							}

							if (pTinyP == NULL)
							{
								strErrorText.Format("%s 网络中 IED设备 %s 中 物理连接 %s 中缺少端口信息描述;", strSubNetwork , strIEDMSG ,strPhysConnType);
								strErrorPos.Format("行号=%d ,列号=%d" ,pTinyPhysConn->Row(),pTinyPhysConn->Column() );
								AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
							} 
							else
							{
								strPortName = pTinyP->FirstChildText();

								if (!CheckPortNameValid(strPortName))
								{
									strErrorText.Format("%s 网络中 IED设备 %s 中 物理连接 %s 中缺少端口信息 %s 描述格式错误;", strSubNetwork , strIEDMSG ,strPhysConnType ,strPortName);
									strErrorPos.Format("行号=%d ,列号=%d" ,pTinyP->Row(),pTinyP->Column() );
									AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
								}
							}
						}

						pTinyPhysConn = (TiXmlElement*)pTinyPhysConn->GetNext();
					}

					if (!bHasPhysConn)
					{
						strErrorText.Format("%s 网络中 IED设备 %s 中 缺少物理端口信息 \"PhysConn\" 节点;", strSubNetwork , strIEDMSG);
						strErrorPos.Format("行号=%d ,列号=%d" ,pTinyConnectedAP->Row(),pTinyConnectedAP->Column() );
						AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
					}
				}

				pTinyConnectedAP = (TiXmlElement*)pTinyConnectedAP->GetNext();
			}
		}

		pTinySubNetwork = (TiXmlElement*)pTinySubNetwork->GetNext();
	}
}

BOOL CSclCheckView::CheckPortNameValid(CString strPortName)
{
	if (strPortName.IsEmpty())
	{
		return FALSE;
	} 
	else
	{
		int nIndex = strPortName.GetLength();
		nIndex = strPortName.Find('-');

		if (nIndex == -1)
		{
			return FALSE;
		}

		CString strBoardNum = strPortName.Left(nIndex);
		CString strPortNum = strPortName.Mid(nIndex+1);

		if (strBoardNum.IsEmpty()||strPortNum.IsEmpty())
		{
			return FALSE;
		}

		int nCount = 0;
		nIndex = strBoardNum.GetLength();
		for(nCount = 0;nCount < nIndex;nCount++)
		{
			if ((strBoardNum[nCount]<'0')||(strBoardNum[nCount]>'9'))
			{
				return FALSE;
			}
		}

		nIndex = strPortNum.GetLength();
		for(nCount = 0;nCount < nIndex;nCount++)
		{
			if ((strPortNum[nCount]<'A')||(strPortNum[nCount]>'Z'))
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}

void CSclCheckView::GetIEDInputsRef(TiXmlElement *pDocRoot)
{
	if (pDocRoot == NULL)
	{
		return;
	}

	CExBaseList *pIED = NULL;
	CExBaseList *pLDevice = NULL;
	CTinyExtRef *pTinyExtRef = NULL;
	CString strIEDName;
	CString strAccessPoint;
	CString strDatasetName;
	CString strCtrlName;
	CString strIEDPath;
	CString strDaName;

	TiXmlElement *pTinyIED = (TiXmlElement*)pDocRoot->FirstChild("IED");
	TiXmlElement *pTinyAccessPoint = NULL;
	TiXmlElement *pTinyServer = NULL;
	TiXmlElement *pTinyLDevice = NULL;
	TiXmlElement *pTinyLN = NULL;
	TiXmlElement *pTinyDataSet = NULL;
	TiXmlElement *pTinyFCDA = NULL;
	TiXmlElement *pTinyCtrl = NULL;

	while(pTinyIED != NULL)
	{
		if (strcmp(pTinyIED->Value() ,"IED") == 0)
		{
			pIED = new CExBaseList;
			m_oTinySCLStation.AddNewChild(pIED);
			pIED->m_strID = pTinyIED->Attribute("name");
			GetTinyDescAndName(pTinyIED ,strIEDName);
			pIED->m_strName = strIEDName;

			pTinyAccessPoint = (TiXmlElement *)pTinyIED->FirstChild("AccessPoint");
			while(pTinyAccessPoint != NULL)
			{
				if (strcmp(pTinyAccessPoint->Value() ,"AccessPoint") == 0)
				{
					strAccessPoint = pTinyAccessPoint->Attribute("name");
					pTinyServer = (TiXmlElement *)pTinyAccessPoint->FirstChild("Server");
					while(pTinyServer != NULL)
					{
						if (strcmp(pTinyServer->Value() ,"Server") == 0)
						{
							pTinyLDevice = (TiXmlElement *)pTinyServer->FirstChild("LDevice");
							while(pTinyLDevice != NULL)
							{
								if (strcmp(pTinyLDevice->Value() ,"LDevice") == 0)
								{
									pLDevice = new CExBaseList;
									pIED->AddNewChild(pLDevice);
									pLDevice->m_strID = pTinyLDevice->Attribute("inst");
									pLDevice->m_strName = strAccessPoint;
									pTinyLN = (TiXmlElement *)pTinyLDevice->FirstChild("LN0");

									if (pTinyLN != NULL)
									{
										pTinyCtrl = (TiXmlElement *)pTinyLN->FirstChild();
										while(pTinyCtrl != NULL)
										{
											if ((strcmp(pTinyCtrl->Value() ,"SampledValueControl") == 0)||(strcmp(pTinyCtrl->Value() ,"GSEControl") == 0))
											{
												strDatasetName = pTinyCtrl->Attribute("datSet");
												strCtrlName = pTinyCtrl->Attribute("name");
												pTinyDataSet = (TiXmlElement *)pTinyLN->FirstChild("DataSet");
												while(pTinyDataSet != NULL)
												{
													if (strcmp(pTinyDataSet->Attribute("name") ,strDatasetName) == 0)
													{
														pTinyFCDA = (TiXmlElement*)pTinyDataSet->FirstChild();
														while(pTinyFCDA != NULL)
														{
															pTinyExtRef = new CTinyExtRef;
															pLDevice->AddNewChild(pTinyExtRef);
															pTinyExtRef->m_strCtrlName = strCtrlName;
															pTinyExtRef->m_strName = strDatasetName;
															strIEDPath = pTinyFCDA->Attribute("ldInst");
															strIEDPath += '/';
															strIEDPath += pTinyFCDA->Attribute("prefix");
															strIEDPath += pTinyFCDA->Attribute("lnClass");
															strIEDPath += pTinyFCDA->Attribute("lnInst");
															strIEDPath += '.';
															strIEDPath += pTinyFCDA->Attribute("doName");
															strDaName = pTinyFCDA->Attribute("daName");

															if (!strDaName.IsEmpty())
															{
																strIEDPath += '.';
																strIEDPath += strDaName;
															}
															pTinyExtRef->m_strID = strIEDPath;

															pTinyFCDA = (TiXmlElement*)pTinyFCDA->GetNext();
														}
														break;
													}

													pTinyDataSet = (TiXmlElement*)pTinyDataSet->GetNext();
												}
											}

											pTinyCtrl = (TiXmlElement*)pTinyCtrl->GetNext();
										}
									}
								}

								pTinyLDevice = (TiXmlElement*)pTinyLDevice->GetNext();
							}
						}

						pTinyServer = (TiXmlElement*)pTinyServer->GetNext();
					}
				}

				pTinyAccessPoint = (TiXmlElement*)pTinyAccessPoint->GetNext();
			}
		}

		pTinyIED = (TiXmlElement*)pTinyIED->GetNext();
	}
}

void CSclCheckView::GetTinyDescAndName(TiXmlElement *pTinySubNetwork ,CString &strSubNetwork)
{
	strSubNetwork = pTinySubNetwork->Attribute("desc");

	if (!strSubNetwork.IsEmpty())
	{
		strSubNetwork += "-";
	}

	strSubNetwork += pTinySubNetwork->Attribute("name");

	UTF8ToMultiByte(strSubNetwork);
}

void CSclCheckView::CheckRelayEnaInit(TiXmlElement* pTinyDOI ,CString strMsg ,CString strFCDAPath ,CProjAppModelChecks *pProjAppModelChecks)
{
	CString strDOName = pTinyDOI->Attribute("name");

	if ((strDOName == "RemGoEna")||(strDOName == "RemGrpEna")||(strDOName == "RemSetEna"))
	{
		return;
	}

	CCheckObject *pCheckObject = NULL;
	CString strErrorText;
	CString  strObjectID;
	CString strErrorPos;
	TiXmlElement* pTinyDAI;
	CString strDAIName;
	CString strCtlModel;
	CString strSboTimeOut;
	BOOL bCtlModelFind = FALSE;
	BOOL bSboTimeoutFind = FALSE;

	pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("ctlModel-sboTimeout");

	if(BeCheckThisObject(pCheckObject ,strObjectID))
	{
		pTinyDAI = (TiXmlElement*)pTinyDOI->FirstChild();

		while(pTinyDAI != NULL)
		{
			strDAIName = pTinyDAI->Attribute("name");

			if (strcmp(strDAIName , "ctlModel") == 0)
			{
				bCtlModelFind = TRUE;
				strCtlModel = pTinyDAI->GetAttributeText("Val");
				if (strCtlModel.IsEmpty())
				{
					strErrorText.Format("%s 的FCDA路径 \"%s\" ,此压板的ctlModel 数据初始化为空;",strMsg ,strFCDAPath );
					strErrorPos.Format("行号=%d ,列号=%d" ,pTinyDAI->Row(),pTinyDAI->Column() );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
				else if ((strCtlModel!="status-only")&&(strCtlModel!="direct-with-normal-security")&&(strCtlModel!="sbo-with-normal-security")&&
					(strCtlModel!="direct-with-enhanced-security")&&(strCtlModel!="sbo-with-enhanced-security"))
				{
					strErrorText.Format("%s 的FCDA路径 \"%s\" ,此压板的ctlModel 实例化 赋值为 %s 与枚举类型值不一致;",strMsg ,strFCDAPath ,strCtlModel);
					strErrorPos.Format("行号=%d ,列号=%d" ,pTinyDAI->Row(),pTinyDAI->Column() );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
			}

			if (strcmp(strDAIName , "sboTimeout") == 0)
			{
				bSboTimeoutFind = TRUE;
				strSboTimeOut = pTinyDAI->GetAttributeText("Val");
				if (strSboTimeOut.IsEmpty())
				{
					strErrorText.Format("%s 的FCDA路径 \"%s\" ,此压板的sboTimeout 数据初始化为空;",strMsg ,strFCDAPath );
					strErrorPos.Format("行号=%d ,列号=%d" ,pTinyDAI->Row(),pTinyDAI->Column() );
					AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
				}
			}

			pTinyDAI = (TiXmlElement*)pTinyDAI->GetNext();
		}

		if (!bCtlModelFind)
		{
			strErrorText.Format("%s 的FCDA路径 \"%s\" ,此压板的ctlModel 数据未实例化;",strMsg ,strFCDAPath );
			strErrorPos.Format("行号=%d ,列号=%d" ,pTinyDOI->Row(),pTinyDOI->Column() );
			AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
		}

		if (!bSboTimeoutFind)
		{
			strErrorText.Format("%s 的FCDA路径 \"%s\" ,此压板的sboTimeout 数据未实例化;",strMsg ,strFCDAPath );
			strErrorPos.Format("行号=%d ,列号=%d" ,pTinyDOI->Row(),pTinyDOI->Column() );
			AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
		}
	}
}

void CSclCheckView::AddCheckResultProjAppModel(CString strErrorType ,CString strText ,CString strErrorPos)
{
	CResultRec *pResultRec = new CResultRec();
	m_oProjAppModelResultsRec.AddNewChild(pResultRec);
	pResultRec->m_strErrorText = strText;
	pResultRec->m_strErrorPos = strErrorPos;
	if (strErrorType == "tips")
	{
		m_oProjAppModelResultsRec.m_nAllTipIndex++;
		pResultRec->m_strErrorType.Format("提示%d" , m_oProjAppModelResultsRec.m_nAllTipIndex);
		pResultRec->m_nTipIndex = 1;	
	}
	else if (strErrorType == "warning")
	{
		m_oProjAppModelResultsRec.m_nAllWarningIndex++;
		pResultRec->m_strErrorType.Format("告警%d" , m_oProjAppModelResultsRec.m_nAllWarningIndex);
		pResultRec->m_nWarningIndex = 1;	
	}
	else if (strErrorType == "error")
	{
		m_oProjAppModelResultsRec.m_nAllErrorIndex++;
		pResultRec->m_strErrorType.Format("错误%d" , m_oProjAppModelResultsRec.m_nAllErrorIndex);
		pResultRec->m_nErrorIndex = 1;
	}
	else if (strErrorType == "fatalerror")
	{
		m_oProjAppModelResultsRec.m_nAllFatalErrorIndex++;
		pResultRec->m_strErrorType.Format("严重%d" , m_oProjAppModelResultsRec.m_nAllFatalErrorIndex);
		pResultRec->m_nFatalErrorIndex = 1;	
	}
}

void CSclCheckView::CheckDOI_SDI_DAI_RefValid(TiXmlElement *pTinyLNNode ,TiXmlElement *pTinyLDNode  ,CExBaseList *pTestObjectTemplates ,map<CString ,TiXmlElement*> *mapLNFullName ,
							   CString strLDevice ,CString strAccessPoint ,CString strIEDMSG ,CProjAppModelChecks *pProjAppModelChecks)
{
	map<CString ,TiXmlElement*>::iterator iterLNFullName;
	std::list<CString>	list_DOI;
	CString strLNFullName;

	CCheckObject *pCheckObject = NULL;
	CString strErrorText;
	CString  strObjectID;
	CString strErrorPos;
	CString strLnType;
	CString strLnClass;
	CString strDOIName;
	CString strMSGFull;

	CLNodeType *pLNodeType = NULL;
	CDOValue *pDOValue = NULL;

	TiXmlElement *pTinyDOI = NULL;

	strLNFullName = pTinyLNNode->Attribute("prefix");
	strLnClass = pTinyLNNode->Attribute("lnClass");
	strLNFullName += strLnClass;
	strLNFullName += pTinyLNNode->Attribute("inst");
	iterLNFullName = mapLNFullName->find(strLNFullName);

	pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("LNObject-Repeat");

	if (iterLNFullName == mapLNFullName->end())
	{
		mapLNFullName->insert(make_pair(strLNFullName ,pTinyLNNode));
	} 
	else if (BeCheckThisObject(pCheckObject ,strObjectID))
	{
		strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下的 LDevice \"%s\" 的实例化LN \"%s\" 冲突, 出现重复实例化 ;",strIEDMSG ,strAccessPoint ,strLDevice , strLNFullName);
		strErrorPos.Format("行号=%d ,列号=%d" ,pTinyLNNode->Row(),pTinyLNNode->Column() );
		AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
	}

	strLnType = pTinyLNNode->Attribute("lnType");
	pLNodeType = (CLNodeType *)pTestObjectTemplates->FindByID(strLnType);

	pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("LN-DOI-DAI-Valid");

	if (BeCheckThisObject(pCheckObject ,strObjectID))
	{
		if (pLNodeType == NULL)
		{
			strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下的 LDevice \"%s\" 的实例化LN \"%s\" 的lnType \"%s\" 未定义 ;",strIEDMSG ,strAccessPoint ,strLDevice , strLNFullName ,strLnType);
			strErrorPos.Format("行号=%d ,列号=%d" ,pTinyLNNode->Row(),pTinyLNNode->Column() );
			AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
		}
		else if (pLNodeType->m_strLnClass != strLnClass)
		{
			strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下的 LDevice \"%s\" 的实例化LN \"%s\" 的lnType \"%s\" 定义的lnClass = \"%s\" 与实例化关联的lnClass = \"%s\" 不一致;",strIEDMSG ,
				strAccessPoint ,strLDevice , strLNFullName ,strLnType ,pLNodeType->m_strLnClass ,strLnClass);
			strErrorPos.Format("行号=%d ,列号=%d" ,pTinyLNNode->Row(),pTinyLNNode->Column() );
			AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
		}
	}

	if (pLNodeType != NULL)
	{
		pTinyDOI = (TiXmlElement *)pTinyLNNode->FirstChild();
		while(pTinyDOI != NULL)
		{
			if (strcmp(pTinyDOI->Value() , "DOI") != 0)
			{
				pTinyDOI = (TiXmlElement *)pTinyDOI->GetNext();
				continue;
			}

			strDOIName = pTinyDOI->Attribute("name");
			pDOValue = (CDOValue *)pLNodeType->FindByID(strDOIName);

			pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("LN-DOI-DAI-Valid");

			if ((BeCheckThisObject(pCheckObject ,strObjectID))&&(pDOValue == NULL))
			{
				strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下的 LDevice \"%s\" 的实例化LN \"%s\" 下的DOI \"%s\" 在lnType = \"%s\"下未定义;",strIEDMSG ,strAccessPoint ,
					strLDevice , strLNFullName ,strDOIName ,strLnType);
				strErrorPos.Format("行号=%d ,列号=%d" ,pTinyDOI->Row(),pTinyDOI->Column() );
				AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
			}

			strMSGFull.Format("本IED \"%s\"中 AccessPoint \"%s\" 下的 LDevice \"%s\" 的实例化LN \"%s\" 下的DOI \"%s\" ",strIEDMSG ,strAccessPoint ,strLDevice , strLNFullName ,strDOIName);

			pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("LEDRs-ctlModel");

			if (BeCheckThisObject(pCheckObject ,strObjectID))
			{
				if (strDOIName == "LEDRs")//单独检查 信号复归的 ctlModel 是否初始化
				{
					CString strLEDRsVal;
					TiXmlElement *pTinyDAI = (TiXmlElement *)pTinyDOI->FirstChild();

					while(pTinyDAI != NULL)
					{
						if (strcmp(pTinyDAI->Attribute("name") , "ctlModel") == 0)
						{
							strLEDRsVal = pTinyDAI->GetAttributeText("Val");
							if (strLEDRsVal.IsEmpty())
							{
								strErrorText.Format("%s 的ctlModel 实例化 赋值为空;",strMSGFull);
								strErrorPos.Format("行号=%d ,列号=%d" ,pTinyDAI->Row(),pTinyDAI->Column() );
								AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
							}
							else if ((strLEDRsVal!="status-only")&&(strLEDRsVal!="direct-with-normal-security")&&(strLEDRsVal!="sbo-with-normal-security")&&
								(strLEDRsVal!="direct-with-enhanced-security")&&(strLEDRsVal!="sbo-with-enhanced-security"))
							{
								strErrorText.Format("%s 的ctlModel 实例化 赋值为 %s 与枚举类型值不一致;",strMSGFull ,strLEDRsVal);
								strErrorPos.Format("行号=%d ,列号=%d" ,pTinyDAI->Row(),pTinyDAI->Column() );
								AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
							}
							break;
						}

						pTinyDAI = (TiXmlElement *)pTinyDAI->GetNext();
					}

					if (pTinyDAI == NULL)
					{
						strErrorText.Format("%s 的ctlModel 未实例化;",strMSGFull);
						strErrorPos.Format("行号=%d ,列号=%d" ,pTinyDOI->Row(),pTinyDOI->Column() );
						AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
					}
				}
			}

			if (pDOValue != NULL)
			{
				pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("DOI-Repeat");

				if (BeCheckThisObject(pCheckObject ,strObjectID))
				{
					if (list_DOI.empty())
					{
						list_DOI.push_back(CString(strDOIName));
					}
					else
					{
						std::list<CString>::iterator iter = list_DOI.begin();
						std::list<CString>::iterator iend = list_DOI.end();
						for(; iter != iend; iter++)
						{
							if (*iter == strDOIName)
							{
								strErrorText.Format("%s 冲突, 出现重复实例化;",strMSGFull);
								strErrorPos.Format("行号=%d ,列号=%d" ,pTinyDOI->Row(),pTinyDOI->Column() );
								AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
								break;
							}
						}

						if (iter == iend)
						{
							list_DOI.push_back(CString(strDOIName));
						}
					}
				}

				pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("LN-DOI-DAI-Valid");

				if (BeCheckThisObject(pCheckObject ,strObjectID))
				{
					CheckSDI_DAIValid(pTinyDOI ,pTestObjectTemplates , pDOValue->m_strType ,strMSGFull ,strObjectID);
				}
			}

			pTinyDOI = (TiXmlElement *)pTinyDOI->GetNext();
		}
		list_DOI.clear();
	}
}

void CSclCheckView::CheckSDI_DAIValid(TiXmlElement* pTinyDOI ,CExBaseList *pTestObjectTemplates, CString strType, CString strMSGFull ,CString strObjectID)
{
	CString strErrorText;
	CString strErrorPos;
	CString strDAIName;
	CString strMSGFullNew;
	std::list<CString>	list_DAI;

	TiXmlElement* pTinyDAI = NULL;

	CDOType *pDOType = (CDOType *)pTestObjectTemplates->FindByID(strType);
	CExBaseObject *pDAValue = NULL;

	if (pDOType == NULL)
	{
		strErrorText.Format("%s 引用的 type = \"%s\" 未定义;",strMSGFull ,strType);
		strErrorPos.Format("行号=%d ,列号=%d" ,pTinyDOI->Row(),pTinyDOI->Column() );
		AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
	}
	else
	{
		pTinyDAI = (TiXmlElement *)pTinyDOI->FirstChild();
		while(pTinyDAI != NULL)
		{
			if ((strcmp(pTinyDAI->Value() , "SDI") != 0)&&(strcmp(pTinyDAI->Value() , "DAI") != 0))
			{
				pTinyDAI = (TiXmlElement *)pTinyDAI->GetNext();
				continue;
			}

			strDAIName = pTinyDAI->Attribute("name");
			pDAValue = pDOType->FindByID(strDAIName);

			if (pDAValue == NULL)
			{
				strErrorText.Format("%s 引用的 DOType = \"%s\" 下的实例化 DAI name = \"%s\"未定义;",strMSGFull ,strType ,strDAIName);
				strErrorPos.Format("行号=%d ,列号=%d" ,pTinyDAI->Row(),pTinyDAI->Column() );
				AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
			}
			else if (pDAValue->GetClassID() == SCLCLASSID_CSCLFILE_SDODETAIL)
			{
				strMSGFullNew.Format("%s 下的SDI name = \"%s\" " ,strMSGFull ,strDAIName);
				CheckSDI_DAIValid(pTinyDAI ,pTestObjectTemplates , pDAValue->m_strName ,strMSGFullNew ,strObjectID);
			}

			if (list_DAI.empty())
			{
				list_DAI.push_back(CString(strDAIName));
			}
			else
			{
				std::list<CString>::iterator iter = list_DAI.begin();
				std::list<CString>::iterator iend = list_DAI.end();
				for(; iter != iend; iter++)
				{
					if (*iter == strDAIName)
					{
						strErrorText.Format("%s 下的DAI name = \"%s\" 冲突, 出现重复实例化;",strMSGFull ,strDAIName);
						strErrorPos.Format("行号=%d ,列号=%d" ,pTinyDAI->Row(),pTinyDAI->Column() );
						AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
						break;
					}
				}

				if (iter == iend)
				{
					list_DAI.push_back(CString(strDAIName));
				}
			}

			pTinyDAI = (TiXmlElement *)pTinyDAI->GetNext();
		}
		list_DAI.clear();
	}
}

void CSclCheckView::GetDataSetName(TiXmlElement* pTinyLN0Node ,std::list<CString> &list_DataSetName)
{
	if (pTinyLN0Node == NULL)
	{
		return;
	}

	TiXmlElement *pTinyDataSet = (TiXmlElement*)pTinyLN0Node->FirstChild("DataSet");
	while(pTinyDataSet != NULL)
	{
		if (strcmp(pTinyDataSet->Value() ,"DataSet") == 0)
		{
			list_DataSetName.push_back(CString(pTinyDataSet->Attribute("name")));
		}

		pTinyDataSet = (TiXmlElement*)pTinyDataSet->GetNext();
	}
}

void CSclCheckView::CheckDataSetRptCtrlLogCtrlMaxNum(TiXmlElement *pTinyIEDNode ,long nConfDataSet ,long nCurDataSetNum ,long nConfReportControl ,long nCurRptNum ,long nConfLogControl ,long nCurLogNum ,
									  CString strIEDMSG, CProjAppModelChecks *pProjAppModelChecks )
{
	CCheckObject *pCheckObject = NULL;
	CString strErrorText;
	CString  strObjectID;
	CString strErrorPos;

	pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("IEDMaxNum-Valid");

	if (BeCheckThisObject(pCheckObject ,strObjectID))
	{
		if ((nConfDataSet != -1)&&(nConfDataSet < nCurDataSetNum))
		{
			strErrorText.Format("本IED \"%s\"中 ConfDataSet(最大数据集数目) 值为 %ld ,小于 实际配置数据集数目 %ld;",strIEDMSG ,nConfDataSet ,nCurDataSetNum);
			strErrorPos.Format("行号=%d ,列号=%d" ,pTinyIEDNode->Row(),pTinyIEDNode->Column() );
			AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
		}

		if ((nConfReportControl != -1)&&(nConfReportControl < nCurRptNum))
		{
			strErrorText.Format("本IED \"%s\"中 ConfReportControl(最大报告控制块数目) 值为 %ld ,小于 实际配置报告控制块数目 %ld;",strIEDMSG ,nConfReportControl ,nCurRptNum);
			strErrorPos.Format("行号=%d ,列号=%d" ,pTinyIEDNode->Row(),pTinyIEDNode->Column() );
			AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
		}

		if ((nConfLogControl != -1)&&(nConfLogControl < nCurLogNum))
		{
			strErrorText.Format("本IED \"%s\"中 ConfLogControl(最大日志控制块数目) 值为 %ld ,小于 实际配置日志控制块数目 %ld;",strIEDMSG ,nConfLogControl ,nCurLogNum);
			strErrorPos.Format("行号=%d ,列号=%d" ,pTinyIEDNode->Row(),pTinyIEDNode->Column() );
			AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
		}
	}
}

BOOL CSclCheckView::ProjAppModelCheckIsEmpty(CProjAppModelChecks *pProjAppModelChecks)
{
	POS pos = pProjAppModelChecks->GetHeadPosition();
	CCheckObject *pCheckObject = NULL;

	while(pos != NULL)
	{
		pCheckObject = (CCheckObject*)pProjAppModelChecks->GetNext(pos);

		if (pCheckObject->m_nChoose)
		{
			return FALSE;
		}
	}
	return TRUE;
}

void CSclCheckView::StartCheckProjAppModel()
{
	if (m_pStrSclPath != NULL)
	{
		CheckProjAppModelBytinyxml(m_pProjAppModelChecks ,*m_pStrSclPath);
	}
//	CheckProjAppModelBytinyxml(m_pProjAppModelChecks ,theApp.m_strSCLFilePath);
	m_oProjAppModelResultsRec.Statis_AllResults();
	pProjAppModelView->ShowGridDatas(&m_oProjAppModelResultsRec);

	CWaitingTimeDlg::g_bOver =  true;
}

UINT CSclCheckView::StartCheckProjAppModelThread(LPVOID pParam)
{
	CSclCheckView *pSclCheckView = (CSclCheckView *)pParam;
	pSclCheckView->StartCheckProjAppModel();
	return 1;
}

void CSclCheckView::StartCheckProjAppModelThr()
{
	CWinThread *pThread; //线程指针
	pThread = AfxBeginThread(StartCheckProjAppModelThread, this); //启动线程 
	pThread->m_bAutoDelete = TRUE;
}

void CSclCheckView::CheckProjAppModelBytinyxml(CProjAppModelChecks *pProjAppModelChecks , CString strPath)
{
	if(ProjAppModelCheckIsEmpty(pProjAppModelChecks))
		return;

	if (!IsFileExist(strPath))//调用FileApi.h中的全局函数，判断文件路径中文件是否存在；
	{
		return;
	}
	TiXmlDocument oDoc;// = new TiXmlDocument();

	if ( !oDoc.LoadFile(strPath)) //调用XML2Interface.h中的全局函数，加载资源，入口返回给oDoc；
	{
		return ;
	}

	CCheckObject *pCheckObject = NULL;
	CString strErrorText;
	CString  strObjectID;
	CString strErrorPos;

	TiXmlElement* pDocRoot = oDoc.RootElement();
	TiXmlElement* pTinyCommu = (TiXmlElement*)pDocRoot->FirstChild("Communication");
	TiXmlElement* pTinyIEDNode = (TiXmlElement*)pDocRoot->FirstChild("IED");
	TiXmlElement* pTinyAccessPointNode = NULL;
	TiXmlElement* pTinyServerNode = NULL;
	TiXmlElement* pTinyLDNode = NULL;
	TiXmlElement* pTinyLNNode = NULL;
	TiXmlElement* pTinyLN0Node = NULL;

	if (m_pSCLTestObjectFile == NULL)
	{
		m_pSCLTestObjectFile = new CSCLTemplates();
		m_pSCLTestObjectFile->m_bUTF8 = TRUE;
		m_pSCLTestObjectFile->m_strName = strPath;
		m_pSCLTestObjectFile->OpenSclTemplatesFileByTinyRoot(pDocRoot);
	}
	else if (m_pSCLTestObjectFile->m_strName != strPath)
	{
		delete m_pSCLTestObjectFile;
		m_pSCLTestObjectFile = new CSCLTemplates();
		m_pSCLTestObjectFile->m_bUTF8 = TRUE;
		m_pSCLTestObjectFile->m_strName = strPath;
		m_pSCLTestObjectFile->OpenSclTemplatesFileByTinyRoot(pDocRoot);
	}
	CExBaseList *pTestObjectTemplates = (CExBaseList*)m_pSCLTestObjectFile->FindByID("DataTypeTemplates");

	map<CString ,TiXmlElement*> mapLNFullName;
	std::list<CString> list_DataSetName;

	CString strIEDMSG;
	CString strAccessPoint;
	CString strLDevice;

	long nIEDCount = 0;
	long nAccessPoint, nServer ,nLDevice ,nLN;
	long nConfDataSet ,nConfReportControl ,nConfLogControl ,nCurDataSetNum ,nCurRptNum ,nCurLogNum;
	BOOL bHasLLN0,bHasLPHD;

	GetIEDInputsRef(pDocRoot);
	pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("physConn-OutPort");

	if (BeCheckThisObject(pCheckObject ,strObjectID))
	{
		CheckPhysConnPort(pTinyCommu ,strObjectID );
	}

	while(pTinyIEDNode != NULL)
	{
		if (strcmp(pTinyIEDNode->Value() , "IED") == 0)
		{
			nIEDCount ++;
			nAccessPoint = 0;
			GetIEDMSG(pTinyIEDNode ,strIEDMSG);
			nConfDataSet = -1 ,nConfReportControl = -1 ,nConfLogControl = -1;
			nCurDataSetNum = 0 ,nCurRptNum = 0,nCurLogNum = 0;
			pTinyAccessPointNode = (TiXmlElement*)pTinyIEDNode->FirstChild();

			while(pTinyAccessPointNode != NULL)
			{
				if (strcmp(pTinyAccessPointNode->Value() , "AccessPoint") == 0)
				{
					nAccessPoint ++;
					nServer = 0;
					strAccessPoint = pTinyAccessPointNode->Attribute("name");
					pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("AccessPoint-Name");

					if (BeCheckThisObject(pCheckObject ,strObjectID))
					{
						CheckAccessPointName(pTinyAccessPointNode ,strAccessPoint ,strIEDMSG ,strObjectID);
					}
					
					pTinyServerNode = (TiXmlElement*)pTinyAccessPointNode->FirstChild();

					while(pTinyServerNode != NULL)
					{
						if (strcmp(pTinyServerNode->Value() , "Server") == 0)
						{
							nServer ++;
							nLDevice = 0;
							pTinyLDNode = (TiXmlElement*)pTinyServerNode->FirstChild();

							while(pTinyLDNode != NULL)
							{
								if (strcmp(pTinyLDNode->Value() , "LDevice") == 0)
								{
									nLDevice ++;
									nLN = 0;
									bHasLLN0 = FALSE;
									bHasLPHD = FALSE;
									strLDevice = pTinyLDNode->Attribute("inst");
									pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("LDevice-Inst");

									if (BeCheckThisObject(pCheckObject ,strObjectID))
									{
										CheckLDeviceInst(pTinyLDNode ,strLDevice ,strAccessPoint ,strIEDMSG ,strObjectID);
									}

									pTinyLNNode = (TiXmlElement*)pTinyLDNode->FirstChild();
									mapLNFullName.clear();
									list_DataSetName.clear();

									while(pTinyLNNode != NULL)
									{
										if (strcmp(pTinyLNNode->Value() ,"LN0") == 0)
										{
											nLN ++;
											bHasLLN0 = TRUE;
											pTinyLN0Node = pTinyLNNode;
										}
										else if (strcmp(pTinyLNNode->Value() ,"LN") == 0)
										{
											nLN ++;
											if (strcmp(pTinyLNNode->Attribute("lnClass"),"LPHD") == 0)
											{
												bHasLPHD = TRUE;
											}
										}

										if (pTinyLNNode->Type() != 2)//TINYXML_COMMENT
										{
											CheckDOI_SDI_DAI_RefValid(pTinyLNNode ,pTinyLDNode  ,pTestObjectTemplates,&mapLNFullName ,strLDevice ,strAccessPoint ,strIEDMSG ,pProjAppModelChecks);
										}

										pTinyLNNode = (TiXmlElement*)pTinyLNNode->GetNext();
									}

									CheckDataSetRelated(pTinyLN0Node ,pTinyLDNode ,&mapLNFullName ,strLDevice ,strAccessPoint ,strIEDMSG ,pProjAppModelChecks ,nCurDataSetNum);
									CheckInputsExtRef(pTinyLN0Node ,pTinyLDNode ,&mapLNFullName ,strLDevice ,strAccessPoint ,strIEDMSG ,pProjAppModelChecks );
									GetDataSetName(pTinyLN0Node ,list_DataSetName);
									CheckReportCtrlRelated(pTinyLN0Node ,list_DataSetName ,strLDevice ,strAccessPoint ,strIEDMSG ,pProjAppModelChecks ,nCurRptNum);
									CheckLogCtrlRelated(pTinyLN0Node ,list_DataSetName ,strLDevice ,strAccessPoint ,strIEDMSG ,pProjAppModelChecks ,nCurLogNum);
									CheckSMVCtrlRelated(pTinyLN0Node ,list_DataSetName ,strLDevice ,strAccessPoint ,strIEDMSG ,pProjAppModelChecks);
									CheckGSECtrlRelated(pTinyLN0Node ,list_DataSetName ,strLDevice ,strAccessPoint ,strIEDMSG ,pProjAppModelChecks);
									CheckSettingCtrlRelated(pTinyLN0Node ,list_DataSetName ,strLDevice ,strAccessPoint ,strIEDMSG ,pProjAppModelChecks);
									pTinyLN0Node = NULL;
									mapLNFullName.clear();
									list_DataSetName.clear();

									pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("LN-Object");

									if (BeCheckThisObject(pCheckObject ,strObjectID))
									{
										strErrorPos.Format("行号=%d ,列号=%d" ,pTinyLDNode->Row(),pTinyLDNode->Column() );

										if (!bHasLLN0)
										{
											strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下, LDevice \"%s\"对象中 缺少 \"LLN0\";",strIEDMSG ,strAccessPoint ,strLDevice);
											AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
										}

										if (!bHasLPHD)
										{
											strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下, LDevice \"%s\"对象中 缺少 \"LPHD\";",strIEDMSG ,strAccessPoint ,strLDevice);
											AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
										}

										if (nLN < 3)
										{
											strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下, LDevice \"%s\"对象中 LN对象(LLN0、LPHD、其他应用逻辑接点)少于三个;",strIEDMSG ,strAccessPoint ,strLDevice);
											AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
										}
									}
								}
								pTinyLDNode = (TiXmlElement*)pTinyLDNode->GetNext();
							}
						}
						pTinyServerNode = (TiXmlElement*)pTinyServerNode->GetNext();
					}

					pCheckObject = (CCheckObject*)pProjAppModelChecks->FindByID("Server-Object");

					if ((BeCheckThisObject(pCheckObject ,strObjectID))&&(nServer == 0))
					{
						strErrorText.Format("本IED \"%s\"中 AccessPoint \"%s\" 下不包含任何Server对象;",strIEDMSG ,strAccessPoint);
						strErrorPos.Format("行号=%d ,列号=%d" ,pTinyAccessPointNode->Row(),pTinyAccessPointNode->Column() );
						AddCheckResultProjAppModel(strObjectID , strErrorText ,strErrorPos);
					}
				}
				else if (strcmp(pTinyAccessPointNode->Value() , "Services") == 0)
				{
					GetIEDMaxConfigNum(pTinyAccessPointNode, nConfDataSet ,nConfReportControl ,nConfLogControl);
				}
				pTinyAccessPointNode = (TiXmlElement*)pTinyAccessPointNode->GetNext();
			}

			CheckDataSetRptCtrlLogCtrlMaxNum(pTinyIEDNode ,nConfDataSet ,nCurDataSetNum ,nConfReportControl ,nCurRptNum ,nConfLogControl ,nCurLogNum ,strIEDMSG ,pProjAppModelChecks );
		}
		pTinyIEDNode = (TiXmlElement*)pTinyIEDNode->GetNext();
	}

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////虚回路描述及冲突检查 部分函数及成员变量////////////////////////////////////////////////////////////	
void CSclCheckView::AddCheckResultVirLoop(CString strErrorType ,CString strText ,CString strErrorPos)
{
	CResultRec *pResultRec = new CResultRec();
	m_oVirLoopResultsRec.AddNewChild(pResultRec);
	pResultRec->m_strErrorText = strText;
	pResultRec->m_strErrorPos = strErrorPos;
	if (strErrorType == "tips")
	{
		m_oVirLoopResultsRec.m_nAllTipIndex++;
		pResultRec->m_strErrorType.Format("提示信息 %d" , m_oVirLoopResultsRec.m_nAllTipIndex);
		pResultRec->m_nTipIndex = 1;	
	}
	else if (strErrorType == "warning")
	{
		m_oVirLoopResultsRec.m_nAllWarningIndex++;
		pResultRec->m_strErrorType.Format("告警%d" , m_oVirLoopResultsRec.m_nAllWarningIndex);
		pResultRec->m_nWarningIndex = 1;	
	}
	else if (strErrorType == "error")
	{
		m_oVirLoopResultsRec.m_nAllErrorIndex++;
		pResultRec->m_strErrorType.Format("错误%d" , m_oVirLoopResultsRec.m_nAllErrorIndex);
		pResultRec->m_nErrorIndex = 1;
	}
	else if (strErrorType == "fatalerror")
	{
		m_oVirLoopResultsRec.m_nAllFatalErrorIndex++;
		pResultRec->m_strErrorType.Format("严重%d" , m_oVirLoopResultsRec.m_nAllFatalErrorIndex);
		pResultRec->m_nFatalErrorIndex = 1;	
	}
}

void CSclCheckView::AddStringAvoidRepeat(CString &strDesc ,CString strChild)
{
	int nIndex = 0;
	nIndex = strDesc.Find(strChild);
	if (nIndex == -1)
	{
		strDesc += "  ";
		strDesc += strChild;
	} 
}

bool CSclCheckView::CheckMACAddrValidity(CString strMAC ,bool bSMVType)
{
	strMAC.MakeLower();
	long nIndex = -1;
	if (strMAC.GetLength()!=17)
	{
		return false;
	}

	if (bSMVType)
	{
		nIndex = strMAC.Find("01-0c-cd-04-0");
		if ((nIndex==0)&&((strMAC[13]=='0')||(strMAC[13]=='1'))&&IsHex(strMAC[15])&&IsHex(strMAC[16]))
		{
			return true;
		}
	} 
	else
	{
		nIndex = strMAC.Find("01-0c-cd-01-0");
		if ((nIndex==0)&&((strMAC[13]=='0')||(strMAC[13]=='1'))&&IsHex(strMAC[15])&&IsHex(strMAC[16]))
		{
			return true;
		}
	}
	return false;
}

bool CSclCheckView::IsHex(unsigned char ch)
{
	if ((ch>47)&&(ch<58))
	{
		return true;
	}
	else if ((ch>96)&&(ch<103))
	{
		return true;
	}
	return false;
}

void CSclCheckView::CheckSmvOutVirLoop(CSclCtrlSmvOut *pSclCtrlSmvOut ,CString strErrorIedPos ,CVirLoopChecks *pVirLoopChecks)
{
	CString  strObjectID;
	CString strDesc;
	CCheckObject *pCheckObject = NULL;
	CString strErrorText;
//////////////////////////////////////////////////////Start检查AppID、SVID、GOOSEID的唯一性检查////////////////////////////////////////////////////////////////////////////////////////////
	map<long ,CString>::iterator iterAppID;
	map<CString ,CString>::iterator iterSVID;

	pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("APPID-Unique");

	if (BeCheckThisObject(pCheckObject ,strObjectID))
	{
		iterAppID = m_mapAppID.find(pSclCtrlSmvOut->m_dwAppID);
		if (iterAppID != m_mapAppID.end())
		{
			strErrorText.Format("本IED中输出的\"%s\"采样值控制块中, APPID\"%x\" 全站不唯一 , 与\"%s\" 控制块冲突;",pSclCtrlSmvOut->m_strSVID ,pSclCtrlSmvOut->m_dwAppID ,iterAppID->second);
			AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
		}
		else
		{
			strDesc = strErrorIedPos;
			strDesc += "---";
			strDesc += pSclCtrlSmvOut->m_strSVID;
			m_mapAppID.insert(make_pair(pSclCtrlSmvOut->m_dwAppID ,strDesc));
		}
	}

	pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("SVID-Unique");

	if (BeCheckThisObject(pCheckObject ,strObjectID))
	{
		iterSVID = m_mapSMVID.find(pSclCtrlSmvOut->m_strSVID);
		if (iterSVID != m_mapSMVID.end())
		{
			strErrorText.Format("本IED中输出的\"%s\"采样值控制块中, SVID 全站不唯一 , 与\"%s\" 控制块冲突;",pSclCtrlSmvOut->m_strSVID ,iterSVID->second);
			AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
		}
		else
		{
			strDesc = strErrorIedPos;
			strDesc += "---";
			strDesc += pSclCtrlSmvOut->m_strSVID;
			m_mapSMVID.insert(make_pair(pSclCtrlSmvOut->m_strSVID ,strDesc));
		}
	}
/////////////////////////////////////////////////////////////////END///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////Start检查MAC地址、AppID、VlanID、Vlan优先级的有效性//////////////////////////////////////////////////////////////////////////////
	pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("MAC-SMV");

	if (BeCheckThisObject(pCheckObject ,strObjectID))
	{
		if (!CheckMACAddrValidity(pSclCtrlSmvOut->m_strMac ,1))
		{
			strErrorText.Format("本IED中输出的\"%s\"控制块中, MAC地址为\"%s\" 不在9-2 SV 组播地址范围01-0C-CD-04-00-00 ~ 01-0C-CD-04-01-FF 之间;",pSclCtrlSmvOut->m_strSVID ,pSclCtrlSmvOut->m_strMac);
			AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
		}
	}

	pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("APPID-Valid");

	if (BeCheckThisObject(pCheckObject ,strObjectID))
	{
		if ((pSclCtrlSmvOut->m_dwAppID < 0x4000)||(pSclCtrlSmvOut->m_dwAppID > 0x7FFF))
		{
			strErrorText.Format("本IED中输出的\"%s\"采样值控制块中, APPID为\"%x\" 不在标准要求的0x4000~0x7FFF 之间;",pSclCtrlSmvOut->m_strSVID ,pSclCtrlSmvOut->m_dwAppID);
			AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
		}
	}

	pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("VLANID-Valid");

	if (BeCheckThisObject(pCheckObject ,strObjectID))
	{
		if (pSclCtrlSmvOut->scl_smv_VLANID > 0xFFF)
		{
			strErrorText.Format("本IED中输出的\"%s\" SMV控制块中, VlanID为\"%x\" 不在标准要求的3位16进制内;",pSclCtrlSmvOut->m_strSVID ,pSclCtrlSmvOut->scl_smv_VLANID);
			AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
		}
	}

	pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("VlanPriority-Valid");

	if (BeCheckThisObject(pCheckObject ,strObjectID))
	{
		if (pSclCtrlSmvOut->scl_smv_VLANPRI > 7)
		{
			strErrorText.Format("本IED中输出的\"%s\" SMV控制块中, VLAN优先级为\"%x\" 不在标准要求的0-7之间;",pSclCtrlSmvOut->m_strSVID ,pSclCtrlSmvOut->scl_smv_VLANPRI);
			AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
		}
	}

	///////////////////END////检查MAC地址、AppID的正确性//////////////////////////////////////////////////////////////////////////////
	POS chPos = pSclCtrlSmvOut->GetHeadPosition();
	CSclChSmvOut *pSclChSmvOut = NULL;

	long nCount = 0;

	while(chPos!=NULL)
	{
		pSclChSmvOut = (CSclChSmvOut *)pSclCtrlSmvOut->GetNext(chPos);
		nCount++;

		pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("Channel-DataType");

		if (BeCheckThisObject(pCheckObject ,strObjectID))
		{

			if (pSclChSmvOut->fcda_cdc != "SAV")
			{
				strErrorText.Format("本IED输出的\"%s\"控制块中, 通道%d : \"%s\" 所用cdc 为\"%s\" ,所在DOType为\"%s\" ,标准要求使用cdc为\"SAV\";",pSclCtrlSmvOut->m_strSVID ,nCount ,
					pSclChSmvOut->fcda_desc ,pSclChSmvOut->fcda_cdc ,pSclChSmvOut->fcda_DOType);
				AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
			}
		}

		pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("dU-DOI");

		if (BeCheckThisObject(pCheckObject ,strObjectID))
		{
			if (pSclChSmvOut->fcda_dodesc != pSclChSmvOut->fcda_desc)
			{
				strErrorText.Format("本IED输出的\"%s\"控制块中, 通道%d的 DOI描述\"%s\" 与dU赋值 \"%s\" 两者不相同 ;",pSclCtrlSmvOut->m_strSVID ,nCount ,
					pSclChSmvOut->fcda_dodesc ,pSclChSmvOut->fcda_desc);
				AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
			}
		}
	}
}

void CSclCheckView::CheckSmvInVirLoop(CSclCtrlSmvIn *pSclCtrlSmvIn ,CString strErrorIedPos ,CVirLoopChecks *pVirLoopChecks)
{
	CString  strObjectID;
	CCheckObject *pCheckObject = NULL;
	POS chPos = pSclCtrlSmvIn->GetHeadPosition();
	CSclChSmvIn *pSclChSmvIn = NULL;

	CString strErrorText;

	CString strInDesc ,strOutDesc;

	while(chPos!=NULL)
	{
		pSclChSmvIn = (CSclChSmvIn *)pSclCtrlSmvIn->GetNext(chPos);

		strInDesc = pSclChSmvIn->inDADesc;
		AddStringAvoidRepeat(strInDesc ,pSclChSmvIn->inDODesc);
		AddStringAvoidRepeat(strInDesc ,pSclChSmvIn->inLNDesc);
		AddStringAvoidRepeat(strInDesc ,pSclCtrlSmvIn->m_strLDdesc);
		
		strOutDesc = pSclChSmvIn->fcda_desc;
		AddStringAvoidRepeat(strOutDesc ,pSclChSmvIn->fcda_dodesc);
		AddStringAvoidRepeat(strOutDesc ,pSclChSmvIn->fcda_lndesc);
		AddStringAvoidRepeat(strOutDesc ,pSclCtrlSmvIn->m_strExLDdesc);

		pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("smvin-check-KeyDB");

		if (BeCheckThisObject(pCheckObject ,strObjectID))
		{
			CString strKeysDesc;

			if (!m_oXMatchVirTerminal.Match(strInDesc ,strOutDesc ,m_pSMVKeyDB ,strKeysDesc))
			{
				strErrorText.Format("本IED中SMVIN接收的\"%s\"控制块中, 通道%d的 输入端描述 \"%s\" , 输出端描述 \"%s\" ,其中关键字 \"%s\" 冲突 ",pSclCtrlSmvIn->iedStr ,
					pSclChSmvIn->outIndex ,strInDesc ,strOutDesc ,strKeysDesc);
				AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
			}
		}

		pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("Channel-DataType");

		if (BeCheckThisObject(pCheckObject ,strObjectID))
		{
			if (pSclChSmvIn->inputRef_cdc != "MV")
			{
				strErrorText.Format("本IED中SMVIN接收的\"%s\"控制块中, 内部通道%d : \"%s\" 所用cdc 为\"%s\" ,所在type为\"%s\" ,标准要求使用cdc为\"MV\";",pSclCtrlSmvIn->iedStr ,pSclChSmvIn->inIndex ,
					pSclChSmvIn->inDADesc ,pSclChSmvIn->inputRef_cdc ,pSclChSmvIn->inputRef_DOType);
				AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
			}

			if (pSclChSmvIn->fcda_cdc != "SAV")
			{
				strErrorText.Format("本IED中SMVIN接收的\"%s\"控制块中, 外部通道%d : \"%s\" 所用cdc 为\"%s\" ,所在DOType为\"%s\" ,标准要求使用cdc为\"SAV\";",pSclCtrlSmvIn->iedStr ,pSclChSmvIn->outIndex ,
					pSclChSmvIn->fcda_desc ,pSclChSmvIn->fcda_cdc ,pSclChSmvIn->fcda_DOType);
				AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
			}
		}

		pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("dU-DOI");

		if (BeCheckThisObject(pCheckObject ,strObjectID))
		{
			if (pSclChSmvIn->inDODesc != pSclChSmvIn->inDADesc)
			{
				strErrorText.Format("本IED中SMVIN接收的\"%s\"控制块中, 通道%d的内部 DOI描述\"%s\" 与dU赋值 \"%s\" 两者不相同 ;",pSclCtrlSmvIn->iedStr ,pSclChSmvIn->outIndex ,
					pSclChSmvIn->inDODesc ,pSclChSmvIn->inDADesc);
				AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
			}

			if (pSclChSmvIn->fcda_dodesc != pSclChSmvIn->fcda_desc)
			{
				strErrorText.Format("本IED中SMVIN接收的\"%s\"控制块中, 通道%d的外部 DOI描述\"%s\" 与dU赋值 \"%s\" 两者不相同 ;",pSclCtrlSmvIn->iedStr ,pSclChSmvIn->outIndex ,
					pSclChSmvIn->fcda_dodesc ,pSclChSmvIn->fcda_desc);
				AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
			}
		}
	}
}

void CSclCheckView::CheckGsOutVirLoop(CSclCtrlGsOut *pSclCtrlGsOut ,CString strErrorIedPos ,CVirLoopChecks *pVirLoopChecks)
{
	CString  strObjectID;
	CString strDesc;
	CCheckObject *pCheckObject = NULL;
	CString strErrorText;
	//////////////////////////////////////////////////////Start检查AppID、SVID、GOOSEID的唯一性检查////////////////////////////////////////////////////////////////////////////////////////////
	map<long ,CString>::iterator iterAppID;
	map<CString ,CString>::iterator iterGoID;

	pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("APPID-Unique");

	if (BeCheckThisObject(pCheckObject ,strObjectID))
	{
		iterAppID = m_mapAppID.find(pSclCtrlGsOut->m_dwAppID);
		if (iterAppID != m_mapAppID.end())
		{
			strErrorText.Format("本IED中输出的\"%s\"GOOSE控制块中, APPID\"%x\" 全站不唯一 , 与\"%s\" 控制块冲突;",pSclCtrlGsOut->m_strGooseId ,pSclCtrlGsOut->m_dwAppID ,iterAppID->second);
			AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
		}
		else
		{
			strDesc = strErrorIedPos;
			strDesc += "---";
			strDesc += pSclCtrlGsOut->m_strGooseId;
			m_mapAppID.insert(make_pair(pSclCtrlGsOut->m_dwAppID ,strDesc));
		}
	}

	pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("GoID-Unique");

	if (BeCheckThisObject(pCheckObject ,strObjectID))
	{
		iterGoID = m_mapGOOSEID.find(pSclCtrlGsOut->m_strGooseId);
		if (iterGoID != m_mapGOOSEID.end())
		{
			strErrorText.Format("本IED中输出的\"%s\"GOOSE控制块中, GoID 全站不唯一 , 与\"%s\" 控制块冲突;",pSclCtrlGsOut->m_strGooseId ,iterGoID->second);
			AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
		}
		else
		{
			strDesc = strErrorIedPos;
			strDesc += "---";
			strDesc += pSclCtrlGsOut->m_strGooseId;
			m_mapGOOSEID.insert(make_pair(pSclCtrlGsOut->m_strGooseId ,strDesc));
		}
	}
	/////////////////////////////////////////////////////////////////END///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////Start检查MAC地址、AppID、VLANID、VLAN-PRIORITY的有效性//////////////////////////////////////////////////////////////////////////////
	pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("MAC-GOOSE");

	if (BeCheckThisObject(pCheckObject ,strObjectID))
	{
		if (!CheckMACAddrValidity(pSclCtrlGsOut->m_strMac ,0))
		{
			strErrorText.Format("本IED中输出的\"%s\"控制块中, MAC地址为\"%s\" 不在GOOSE 组播地址范围01-0C-CD-01-00-00 ~ 01-0C-CD-01-01-FF 之间;",pSclCtrlGsOut->m_strGooseId ,pSclCtrlGsOut->m_strMac);
			AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
		}
	}

	pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("APPID-Valid");

	if (BeCheckThisObject(pCheckObject ,strObjectID))
	{
		if (pSclCtrlGsOut->m_dwAppID > 0x3FFF)
		{
			strErrorText.Format("本IED中输出的\"%s\" GOOSE控制块中, APPID为\"%x\" 不在标准要求的0x0000~0x3FFF 之间;",pSclCtrlGsOut->m_strGooseId ,pSclCtrlGsOut->m_dwAppID);
			AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
		}
	}

	pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("VLANID-Valid");

	if (BeCheckThisObject(pCheckObject ,strObjectID))
	{
		if (pSclCtrlGsOut->m_dwVLandID > 0xFFF)
		{
			strErrorText.Format("本IED中输出的\"%s\" GOOSE控制块中, VlanID为\"%x\" 不在标准要求的3位16进制内;",pSclCtrlGsOut->m_strGooseId ,pSclCtrlGsOut->m_dwVLandID);
			AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
		}
	}

	pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("VlanPriority-Valid");

	if (BeCheckThisObject(pCheckObject ,strObjectID))
	{
		if (pSclCtrlGsOut->m_dwVLandPriority > 7)
		{
			strErrorText.Format("本IED中输出的\"%s\" SMV控制块中, VLAN优先级为\"%x\" 不在标准要求的0-7之间;",pSclCtrlGsOut->m_strGooseId ,pSclCtrlGsOut->m_dwVLandPriority);
			AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
		}
	}

	///////////////////END////检查MAC地址、AppID的正确性//////////////////////////////////////////////////////////////////////////////
	POS chPos = pSclCtrlGsOut->GetHeadPosition();
	CSclChGsOut *pSclChGsOut = NULL;

	long nCount = 0;

	while(chPos!=NULL)
	{
		pSclChGsOut = (CSclChGsOut *)pSclCtrlGsOut->GetNext(chPos);
		nCount++;

		pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("dU-DOI");

		if (BeCheckThisObject(pCheckObject ,strObjectID))
		{
			if (pSclChGsOut->fcda_dodesc != pSclChGsOut->fcda_desc)
			{
				strErrorText.Format("本IED输出的\"%s\"控制块中, 通道%d的 DOI描述\"%s\" 与dU赋值 \"%s\" 两者不相同 ;",pSclCtrlGsOut->m_strGooseId ,nCount ,
					pSclChGsOut->fcda_dodesc ,pSclChGsOut->fcda_desc);
				AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
			}
		}
	}
}

void CSclCheckView::CheckGsInVirLoop(CSclCtrlGsIn *pSclCtrlGsIn ,CString strErrorIedPos ,CVirLoopChecks *pVirLoopChecks)
{
	CString  strObjectID;
	CCheckObject *pCheckObject = NULL;
	POS chPos = pSclCtrlGsIn->GetHeadPosition();
	CSclChGsIn *pSclChGsIn = NULL;

	CString strDesc;
	CString strErrorText;

	CString strGSInDesc ,strGSOutDesc;

	while(chPos!=NULL)
	{
		pSclChGsIn = (CSclChGsIn *)pSclCtrlGsIn->GetNext(chPos);

		strGSInDesc = pSclChGsIn->inDADesc;
		AddStringAvoidRepeat(strGSInDesc ,pSclChGsIn->inDODesc);
		AddStringAvoidRepeat(strGSInDesc ,pSclChGsIn->inLNDesc);
		AddStringAvoidRepeat(strGSInDesc ,pSclCtrlGsIn->m_strExLDdesc);

		strGSOutDesc = pSclChGsIn->fcda_desc;
		AddStringAvoidRepeat(strGSOutDesc ,pSclChGsIn->fcda_dodesc);
		AddStringAvoidRepeat(strGSOutDesc ,pSclChGsIn->fcda_lndesc);
		AddStringAvoidRepeat(strGSOutDesc ,pSclCtrlGsIn->m_strLDdesc);

		pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("goosein-check-KeyDB");

		if (BeCheckThisObject(pCheckObject ,strObjectID))
		{
			CString strKeysDesc;

			if (!m_oXMatchVirTerminal.Match(strGSInDesc ,strGSOutDesc ,m_pGSKeyDB ,strKeysDesc))
			{
				strErrorText.Format("本IED中GSIN接收的\"%s\"控制块中, 通道%d的输入端描述\"%s\" , 输出端描述\"%s\" ,其中关键字\"%s\" 冲突",pSclCtrlGsIn->m_strIedDesc ,
					pSclChGsIn->outIndex ,strGSInDesc ,strGSOutDesc ,strKeysDesc);
				AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
			}
		}

		pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("Channel-DataType");

		if (BeCheckThisObject(pCheckObject ,strObjectID))
		{
			if (pSclChGsIn->inputRef_type != pSclChGsIn->fcda_type)
			{
				strErrorText.Empty();
				strErrorText.Format("本IED中GSIN接收的\"%s\"控制块中, 内部通道%ld:%s 所用通道数据类型为\"%s\", 与之相连的外部通道%ld: %s 所用数据类型为\"%s\" 两者不一致 ;",pSclCtrlGsIn->m_strIedDesc ,
					pSclChGsIn->inIndex ,pSclChGsIn->inDADesc,pSclChGsIn->inputRef_type ,pSclChGsIn->outIndex  ,pSclChGsIn->fcda_desc,pSclChGsIn->fcda_type);
				AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
			}
		}

		pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("dU-DOI");

		if (BeCheckThisObject(pCheckObject ,strObjectID))
		{
			if (pSclChGsIn->inDODesc != pSclChGsIn->inDADesc)
			{
				strErrorText.Format("本IED中GSIN接收的\"%s\"控制块中, 通道%d的内部 DOI描述\"%s\" 与dU赋值 \"%s\" 两者不相同 ;",pSclCtrlGsIn->m_strIedDesc ,pSclChGsIn->outIndex ,
					pSclChGsIn->inDODesc ,pSclChGsIn->inDADesc);
				AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
			}

			if (pSclChGsIn->fcda_dodesc != pSclChGsIn->fcda_desc)
			{
				strErrorText.Format("本IED中GSIN接收的\"%s\"控制块中, 通道%d的外部 DOI描述\"%s\" 与dU赋值 \"%s\" 两者不相同 ;",pSclCtrlGsIn->m_strIedDesc ,pSclChGsIn->outIndex ,
					pSclChGsIn->fcda_dodesc ,pSclChGsIn->fcda_desc);
				AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
			}
		}
	}
}

void CSclCheckView::CheckRptCtrlBrcb(CExBaseList *pSclLogicDev ,CString strErrorIedPos ,CVirLoopChecks *pVirLoopChecks)
{
	if (pSclLogicDev->GetClassID() != DVMCLASSID_CDVMLOGICDEVICE)
	{
		return;
	}

	CString  strObjectID;
	CCheckObject *pCheckObject = NULL;

	pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("Rpt-Brcb");

	if (!BeCheckThisObject(pCheckObject ,strObjectID))
	{
		return;
	}
	
	POS RptsPos = pSclLogicDev->GetHeadPosition();
	POS RptPos = NULL;

	CRptCtrl *pRptCtrl = NULL;

	CExBaseList *pRptCtrls = NULL;
 
	CDataSet *pDataSetTmps = NULL;

	CString strDatasetName;
	CString strErrorText;

	long nFind = -1;

	while(RptsPos!=NULL)
	{
		pRptCtrls = (CExBaseList*)pSclLogicDev->GetNext(RptsPos);

		if (pRptCtrls->GetClassID() == DVMCLASSID_CRPTCTRLS)
		{
			RptPos  = pRptCtrls->GetHeadPosition();
			while(RptPos!=NULL)
			{
				pRptCtrl = (CRptCtrl*)pRptCtrls->GetNext(RptPos);

				strDatasetName = pRptCtrl->m_strDatSet;
				DelTailDigtal(&strDatasetName);
				pDataSetTmps = (CDataSet *)m_pTemplateFile1396->FindByID(strDatasetName);

				if (pDataSetTmps!=NULL)
				{
					if (pDataSetTmps->m_strBrcbname.IsEmpty())
					{
						strErrorText.Format("本IED中的 逻辑设备\"%s\"下的报告控制块name值为\"%s\" 其对应数据集\"%s\" 不能关联报告控制块 ;",pRptCtrls->m_strName ,pRptCtrl->m_strName ,pRptCtrl->m_strDatSet);
						AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);
						continue;
					}

					nFind = pRptCtrl->m_strName.Find(pDataSetTmps->m_strBrcbname);
					if (nFind == 0)
					{
						if(CheckTailDigital(pRptCtrl->m_strName))
						{
							strErrorText.Format("本IED中的 逻辑设备\"%s\"下的报告控制块name值为\"%s\" 命名错误， 标准要求多个同类型的报告控制块应加字母后缀区分 ;",pRptCtrls->m_strName ,pRptCtrl->m_strName);
							AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);	
						}
					}
					else
					{
						strErrorText.Format("本IED中的 逻辑设备\"%s\"下的报告控制块name值为\"%s\" 与 标准要求的\"%s\" 不一致 ;",pRptCtrls->m_strName ,pRptCtrl->m_strName ,pDataSetTmps->m_strBrcbname);
						AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);	
					}
				}
			}
		}
	}
}

void CSclCheckView::CheckLogCtrlLcb(CExBaseList *pSclLogicDev ,CString strErrorIedPos ,CVirLoopChecks *pVirLoopChecks)
{
	if (pSclLogicDev->GetClassID() != DVMCLASSID_CDVMLOGICDEVICE)
	{
		return;
	}

	CString  strObjectID;
	CCheckObject *pCheckObject = NULL;

	pCheckObject = (CCheckObject*)pVirLoopChecks->FindByID("Log-Lcb");

	if (!BeCheckThisObject(pCheckObject ,strObjectID))
	{
		return;
	}

	POS LogsPos = pSclLogicDev->GetHeadPosition();
	POS LogPos = NULL;

	CLogCtrl *pLogCtrl = NULL;

	CExBaseList *pLogCtrls = NULL;

	CDataSet *pDataSetTmps = NULL;

	CString strDatasetName;
	CString strErrorText;

	long nFind = -1;

	while(LogsPos!=NULL)
	{
		pLogCtrls = (CExBaseList*)pSclLogicDev->GetNext(LogsPos);

		if (pLogCtrls->GetClassID() == DVMCLASSID_CLOGCTRLS)
		{
			LogPos  = pLogCtrls->GetHeadPosition();
			while(LogPos!=NULL)
			{
				pLogCtrl = (CLogCtrl*)pLogCtrls->GetNext(LogPos);

				strDatasetName = pLogCtrl->m_strDatSet;
				DelTailDigtal(&strDatasetName);
				pDataSetTmps = (CDataSet *)m_pTemplateFile1396->FindByID(strDatasetName);

				if (pDataSetTmps!=NULL)
				{
					if (pDataSetTmps->m_strLcbname.IsEmpty())
					{
						continue;
					}

					nFind = pLogCtrl->m_strID.Find(pDataSetTmps->m_strLcbname);
					if (nFind == 0)
					{
						if(CheckTailDigital(pLogCtrl->m_strID))
						{
							strErrorText.Format("本IED中的 逻辑设备\"%s\"下的日志控制块name值为\"%s\" 命名错误， 标准要求多个同类型的日志控制块应加字母后缀区分 ;",pLogCtrls->m_strName ,pLogCtrl->m_strID);
							AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);	
						}
					}
					else
					{
						strErrorText.Format("本IED中的 逻辑设备\"%s\"下的日志控制块name值为\"%s\" 与 标准要求的\"%s\" 不一致 ;",pLogCtrls->m_strName ,pLogCtrl->m_strID ,pDataSetTmps->m_strLcbname);
						AddCheckResultVirLoop(strObjectID , strErrorText ,strErrorIedPos);	
					}
				}
			}
		}
	}
}

BOOL CSclCheckView::VirLoopCheckIsEmpty(CVirLoopChecks *pVirLoopChecks)
{
	POS pos = pVirLoopChecks->GetHeadPosition();
	CCheckObject *pCheckObject = NULL;

	while(pos != NULL)
	{
		pCheckObject = (CCheckObject*)pVirLoopChecks->GetNext(pos);

		if (pCheckObject->m_nChoose)
		{
			return FALSE;
		}
	}
	return TRUE;
}

void CSclCheckView::StartVirLoopCheck()
{
	CXKeyDB oSMVKeyDB ,oGSKeyDB;
	CString strKeyDBPath = _P_GetLibraryPath();
	strKeyDBPath += "SMVVirtualTermCheckKeyDb.xml";
	oSMVKeyDB.OpenKeyDbFile(strKeyDBPath);
	m_pSMVKeyDB = &oSMVKeyDB;

	strKeyDBPath = _P_GetLibraryPath();
	strKeyDBPath += "GSVirtualTermCheckKeyDb.xml";
	oGSKeyDB.OpenKeyDbFile(strKeyDBPath);
	m_pGSKeyDB = &oGSKeyDB;

	StartVirLoopCheck(m_pVirLoopChecks);
	m_oVirLoopResultsRec.Statis_AllResults();
	m_pSclVirLoopView->ShowGridDatas(&m_oVirLoopResultsRec);

	CWaitingTimeDlg::g_bOver =  true;
}

UINT CSclCheckView::StartVirLoopCheckThread(LPVOID pParam)
{
	CSclCheckView *pSclCheckView = (CSclCheckView *)pParam;
	pSclCheckView->StartVirLoopCheck();
	return 1;
}

void CSclCheckView::StartVirLoopCheckThr()
{
	CWinThread *pThread; //线程指针
	pThread = AfxBeginThread(StartVirLoopCheckThread, this); //启动线程 
	pThread->m_bAutoDelete = TRUE;
}

void CSclCheckView::StartVirLoopCheck(CVirLoopChecks *pVirLoopChecks)
{
	if(VirLoopCheckIsEmpty(pVirLoopChecks))
		return;

	if (m_pSclChStation == NULL)
	{
		return;
	}

	CSclStation *pSclStation = m_pSclChStation /*= theApp.GetCurrentSclStation()*/;
	POS iedPos = pSclStation->GetHeadPosition();
	POS ctrlsPos = NULL;
	POS ctrlPos = NULL;
	CExBaseList *pIedDev = NULL;
	CExBaseList *pIedCtrls = NULL;
	CSclIed *pSclIed = NULL;

	CString strErrorIedPos;

	m_mapAppID.clear();
	m_mapSMVID.clear();
	m_mapGOOSEID.clear();

	while(iedPos!=NULL)
	{
		pIedDev = (CExBaseList *)pSclStation->GetNext(iedPos);
		if (pIedDev->GetClassID() == SCLIECCLASSID_IED)
		{
			pSclIed = (CSclIed *)pIedDev;

			strErrorIedPos.Format("Ied: name=\"%s\" desc=\"%s\" type=\"%s\" manufacturer=\"%s\" ",pSclIed->m_strID ,pSclIed->m_strName ,pSclIed->m_strModel ,pSclIed->m_strManufacturer);

			ctrlsPos = pSclIed->GetHeadPosition();

			while(ctrlsPos!=NULL)
			{
				pIedCtrls = (CExBaseList *)pSclIed->GetNext(ctrlsPos);
				ctrlPos = pIedCtrls->GetHeadPosition();

				if (pIedCtrls->GetClassID() == SCLIECCLASSID_CTRLS_SMV_OUT)
				{
					while(ctrlPos!=NULL)
					{
						CheckSmvOutVirLoop((CSclCtrlSmvOut *)pIedCtrls->GetNext(ctrlPos) ,strErrorIedPos ,pVirLoopChecks);
					}
				} 
				else if (pIedCtrls->GetClassID() == SCLIECCLASSID_CTRLS_SMV_IN)
				{
					while(ctrlPos!=NULL)
					{
						CheckSmvInVirLoop((CSclCtrlSmvIn *)pIedCtrls->GetNext(ctrlPos) ,strErrorIedPos ,pVirLoopChecks);
					}
				}
				else if (pIedCtrls->GetClassID() == SCLIECCLASSID_CTRLS_GS_OUT)
				{
					while(ctrlPos!=NULL)
					{
						CheckGsOutVirLoop((CSclCtrlGsOut *)pIedCtrls->GetNext(ctrlPos) ,strErrorIedPos ,pVirLoopChecks);
					}
				}
				else if (pIedCtrls->GetClassID() == SCLIECCLASSID_CTRLS_GS_IN)
				{
					while(ctrlPos!=NULL)
					{
						CheckGsInVirLoop((CSclCtrlGsIn *)pIedCtrls->GetNext(ctrlPos) ,strErrorIedPos ,pVirLoopChecks);
					}
				}
				else if (pIedCtrls->GetClassID() == DVMCLASSID_CDVMDEVICE)
				{
					CExBaseList *pCtrlLog = NULL;
					while(ctrlPos!=NULL)
					{
						pCtrlLog = (CExBaseList *)pIedCtrls->GetNext(ctrlPos);
						CheckRptCtrlBrcb(pCtrlLog ,strErrorIedPos ,pVirLoopChecks);
						CheckLogCtrlLcb(pCtrlLog ,strErrorIedPos ,pVirLoopChecks);
					}
				}
			}
		}

	}
	m_mapAppID.clear();
	m_mapSMVID.clear();
	m_mapGOOSEID.clear();
}

LRESULT CSclCheckView::OnFinishSchemaCheck(WPARAM wParam, LPARAM lParam)
{
	if (m_pSclCheckObject != NULL)
	{
		delete m_pSclCheckObject;
		m_pSclCheckObject = NULL;
	}

	return 0;
}