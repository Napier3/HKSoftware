#include "SclDataTypeTmpsCheckTool.h"
#include "../../../SttStudio/Test_Win/SCLCompareTool/XLangResource_SCLCompare.h"
#include <QMessageBox>

CSclDataTypeTmpsCheckTool::CSclDataTypeTmpsCheckTool(void)
{
	m_pDLT860ModelChecks = NULL;
	m_pDL860Results = NULL;
	m_pStartCheckThread = NULL;
	m_BeCheckFinished = TRUE;
	m_strSclFilePath = "";
}

CSclDataTypeTmpsCheckTool::~CSclDataTypeTmpsCheckTool(void)
{
}

BOOL CSclDataTypeTmpsCheckTool::OpenConfigs(const CString &strSGCCFilePath,const CString &strTmpsFilePath)
{
	BOOL bRet = TRUE;

	if (!m_oTemplateFile1396.OpenTemplateFile1396(strSGCCFilePath))
	{
		bRet = FALSE;
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("打开配置文件(%s)失败.")*/g_sLangTxt_configurationfile.GetString(),strSGCCFilePath.GetString());
	}

	if (!m_oStdDataTypeTemplates.OpenSclTemplatesFile(strTmpsFilePath))
	{
		bRet = FALSE;
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("打开标准模板库文件(%s)失败."),strTmpsFilePath.GetString());
	}

	return TRUE;
}

UINT CSclDataTypeTmpsCheckTool::StartCheckThread(LPVOID pParam)
{
	CSclDataTypeTmpsCheckTool *pDataTypeTmpsCheckObject = (CSclDataTypeTmpsCheckTool *)pParam;
	return pDataTypeTmpsCheckObject->StartCheck();
}

void CSclDataTypeTmpsCheckTool::FreeStartCheckThread()
{
#ifdef _PSX_IDE_QT_
	if (m_pStartCheckThread != NULL)
	{
		m_pStartCheckThread->PostThreadMessage(WM_QUIT, 0, 0);
		m_pStartCheckThread->wait();
		m_pStartCheckThread = NULL;
	}
#endif
}

int CSclDataTypeTmpsCheckTool::Start1396CheckFromThread(CString &strSclFilePath,CDLT860ModelChecks *pDLT860ModelChecks,CResultsRec *pDL860Results)
{
	m_strSclFilePath = strSclFilePath;
	m_pDLT860ModelChecks = pDLT860ModelChecks;
	m_pDL860Results = pDL860Results;
#ifdef _PSX_IDE_QT_
	FreeStartCheckThread();
	m_BeCheckFinished = FALSE;
	m_pStartCheckThread = new CWinThread(StartCheckThread, this);
	m_pStartCheckThread->m_bAutoDelete = FALSE;
	m_pStartCheckThread->ResumeThread();
#else
	m_pStartCheckThread = AfxBeginThread(StartCheckThread, this); //启动线程 
	m_pStartCheckThread->m_bAutoDelete = TRUE;
#endif

	return 1;
}

int CSclDataTypeTmpsCheckTool::Start1396CheckNormal(CString &strSclFilePath,CDLT860ModelChecks *pDLT860ModelChecks,CResultsRec *pDL860Results)
{
	m_strSclFilePath = strSclFilePath;
	m_pDLT860ModelChecks = pDLT860ModelChecks;
	m_pDL860Results = pDL860Results;
	return StartCheck();
}

BOOL CSclDataTypeTmpsCheckTool::StartCheck()
{

	if (m_pDLT860ModelChecks == NULL)
	{
		m_BeCheckFinished = TRUE;
		return FALSE;
	}

	m_oSCLTestObjectFile.DeleteAll();

	/////////////////////////////打开待测文件，将其DataTypeTemplates部分存入链表中////////////////////////////////////////////

	if (!m_oSCLTestObjectFile.OpenSclTemplatesFile(m_strSclFilePath))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, /*_T("打开文件(%s)失败.")*/g_sLangTxt_Native_OpenFail.GetString(), m_strSclFilePath.GetString());
		m_BeCheckFinished = TRUE;
		
		return FALSE;
	}

	StartTemplateCheck1396(m_pDLT860ModelChecks);
	StartTemplatesCompare(m_pDLT860ModelChecks);
	m_BeCheckFinished = TRUE;
	return TRUE;
}

void CSclDataTypeTmpsCheckTool::StartTemplateCheck1396(CDLT860ModelChecks *pDLT860ModelChecks)
{
	CString strObjectID;
	CCheckObject *pCheckObject = NULL;
	/////////////////第一步：判断是否含有相关检测项目/////////////////////////////////////////////////////////////

	if(!HasSelectChecks(TRUE))
		return;

	//////////////////////////////第二步：进行比对验证，将测试结果存入对应测试结果链表中去//////////////////////////////////////////////
	CExBaseList *pTemplates1396 = (CExBaseList*)m_oTemplateFile1396.FindByID("DataTypeTemplates");
	CExBaseList *pTestObjectTemplates = (CExBaseList*)m_oSCLTestObjectFile.FindByID("DataTypeTemplates");

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
					strErrorText.Format("LNodeType: id=%s 在DataTypeTemplates重复定义了 %d 次 ;",pObjDataType->m_strID.GetString() ,nCount);
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
					strErrorText.Format("DOType: id=%s 在DataTypeTemplates重复定义了 %d 次 ;",pObjDataType->m_strID.GetString() ,nCount);
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
					strErrorText.Format("DAType: id=%s 在DataTypeTemplates重复定义了 %d 次 ;",pObjDataType->m_strID.GetString() ,nCount);
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
					strErrorText.Format("EnumType: id=%s 在DataTypeTemplates重复定义了 %d 次 ;",pObjDataType->m_strID.GetString() ,nCount);
					AddCheckResultDLT860Tmps(strObjectID , strErrorText ,((CEnumType*)pObjDataType)->m_strErrorPos);
				}
			}

			CheckEnumTypeOfGDW1396((CEnumType*)pObjDataType ,pTemplates1396 ,pDLT860ModelChecks );
		}
	}
}


void CSclDataTypeTmpsCheckTool::StartTemplatesCompare(CDLT860ModelChecks *pDLT860ModelChecks)
{
	if(!HasSelectChecks(FALSE))
		return;

	CString  strObjectID;
	CCheckObject *pCheckObject = NULL;

	CExBaseList *pDataTypeTemplates = (CExBaseList*)m_oStdDataTypeTemplates.FindByID("DataTypeTemplates");
	CExBaseList *pTestObjectTemplates = (CExBaseList*)m_oSCLTestObjectFile.FindByID("DataTypeTemplates");
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
						strErrorText.Format("LNodeType: id=%s desc=",pObjDataType->m_strID.GetString());
						strErrorText += pObjDataType->m_strName;
						strErrorText.AppendFormat(_T(" 与模板库中的 %s 文件中的同名类冲突;"),((CLNodeType*)pTmpDataType)->m_strPrivateMSG.GetString());

// 						strErrorText.Format("LNodeType: id=%s desc=%s 与模板库中的 %s 文件中的同名类冲突;",pObjDataType->m_strID.GetString(),
// 							pObjDataType->m_strName.GetString(),((CLNodeType*)pTmpDataType)->m_strPrivateMSG.GetString());
						AddCheckResultDLT860Tmps(strObjectID , strErrorText ,((CLNodeType*)pObjDataType)->m_strErrorPos);
					}
				}
				else if (pObjDataType->GetClassID() == SCLCLASSID_CSCLFILEDOTYPE)
				{
					pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DOType-conflict");

					if (BeCheckThisObject(pCheckObject ,strObjectID))
					{
						strErrorText.Format("DOType: id=%s 与模板库中的 %s 文件中的同名类冲突;",pObjDataType->m_strID.GetString(),
							((CDOType*)pTmpDataType)->m_strPrivateMSG.GetString());
						AddCheckResultDLT860Tmps(strObjectID , strErrorText ,((CDOType*)pObjDataType)->m_strErrorPos);
					}
				}
				else if (pObjDataType->GetClassID() == SCLCLASSID_CSCLFILEDATYPE)
				{
					pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DAType-conflict");

					if (BeCheckThisObject(pCheckObject ,strObjectID))
					{
						strErrorText.Format("DAType: id=%s 与模板库中的 %s 文件中的同名类冲突;",pObjDataType->m_strID.GetString() ,
							((CDAType*)pTmpDataType)->m_strPrivateMSG.GetString());
						AddCheckResultDLT860Tmps(strObjectID , strErrorText ,((CDAType*)pObjDataType)->m_strErrorPos);
					}
				}
				else if (pObjDataType->GetClassID() == SCLCLASSID_CSCLFILEENUMTYPE)
				{
					pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("EnumType-conflict");

					if (BeCheckThisObject(pCheckObject ,strObjectID))
					{
						strErrorText.Format("EnumType: id=%s 与模板库中的 %s 文件中的同名类冲突;",pObjDataType->m_strID.GetString() ,
							((CEnumType*)pTmpDataType)->m_strPrivateMSG.GetString());
						AddCheckResultDLT860Tmps(strObjectID , strErrorText ,((CEnumType*)pObjDataType)->m_strErrorPos);
					}
				}
			}
		}
	}
}

BOOL CSclDataTypeTmpsCheckTool::HasSelectChecks(BOOL bIsTemplateCheck)
{
	if (m_pDLT860ModelChecks == NULL)
	{
		return FALSE;
	}

	POS pos = m_pDLT860ModelChecks->GetHeadPosition();
	CCheckObject *pCheckObject = NULL;

	while(pos != NULL)
	{
		pCheckObject = (CCheckObject*)m_pDLT860ModelChecks->GetNext(pos);

		if (pCheckObject->m_nChoose == 0)
		{
			continue;
		}

		//在1396检查时,检查项包含"冲突性检查"标识为模板库比较
		if ((pCheckObject->m_strName.Find("冲突性检查") != -1)&&(bIsTemplateCheck))
		{
			continue;
		}

		//在模板库比较时,检查不项包含"冲突性检查"标识为1396检查
		if ((pCheckObject->m_strName.Find("冲突性检查") == -1)&&(!bIsTemplateCheck))
		{
			continue;
		}

		return TRUE;
	}

	return FALSE;
}

void CSclDataTypeTmpsCheckTool::AddCheckResultDLT860Tmps(CString strErrorType ,CString strText ,CString strErrorPos)
{
	CResultRec *pResultRec = new CResultRec();
	m_pDL860Results->AddNewChild(pResultRec);
	pResultRec->m_strErrorText = strText;
	pResultRec->m_strErrorPos = strErrorPos;
	if (strErrorType == "tips")
	{
		m_pDL860Results->m_nAllTipIndex++;
		pResultRec->m_strErrorType = /*"提示"*/g_sLangTxt_Native_LangTip;
		pResultRec->m_strErrorType.AppendFormat("%d ",m_pDL860Results->m_nAllTipIndex);
		pResultRec->m_nTipIndex = 1;	
	}
	else if (strErrorType == "warning")
	{
		m_pDL860Results->m_nAllWarningIndex++;
		pResultRec->m_strErrorType = /*"告警"*/g_sLangTxt_SCLCompare_Warning;
		pResultRec->m_strErrorType.AppendFormat("%d ",m_pDL860Results->m_nAllWarningIndex);
		pResultRec->m_nWarningIndex = 1;	
	}
	else if (strErrorType == "error")
	{
		m_pDL860Results->m_nAllErrorIndex++;
		pResultRec->m_strErrorType = /*"错误"*/g_sLangTxt_Native_error;
		pResultRec->m_strErrorType.AppendFormat("%d ",m_pDL860Results->m_nAllErrorIndex);
		pResultRec->m_nErrorIndex = 1;
	}
	else if (strErrorType == "fatalerror")
	{
		m_pDL860Results->m_nAllFatalErrorIndex++;
		pResultRec->m_strErrorType = /*"严重"*/g_sLangTxt_SCLCompare_Serious;
		pResultRec->m_strErrorType.AppendFormat("%d ",m_pDL860Results->m_nAllFatalErrorIndex);
		pResultRec->m_nFatalErrorIndex = 1;	
	}
}

BOOL CSclDataTypeTmpsCheckTool::BeCheckThisObject(CCheckObject *pCheckObject ,CString &strObjectID)
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

bool CSclDataTypeTmpsCheckTool::CheckTailDigital(const CString &strText)
{
	if (strText.IsEmpty())
	{
		return false;
	}
	unsigned char zfTmp = strText.GetAt(strText.GetLength()-1);
	return (('0'<=zfTmp)&&(zfTmp<='9'));
}

long CSclDataTypeTmpsCheckTool::DelTailDigtal(CString &strName)
{
	long nIndex = 0;
	char szDigtal[20] = {""};
	char szNew[20] = {""};
	szDigtal[0] = strName.GetAt(strName.GetLength()-1);
	char *pzfTmp = szDigtal;
	bool bSmb = ('0'<=*pzfTmp)&&(*pzfTmp<='9');

	while(bSmb)
	{
		pzfTmp++;
		strName = strName.Left(strName.GetLength()-1);
		*pzfTmp = strName.GetAt(strName.GetLength()-1);
		bSmb = ('0'<=*pzfTmp)&&(*pzfTmp<='9');
	}
	*pzfTmp = '\0';

	nIndex = strlen(szDigtal);
	for (int i=0; i<nIndex;i++)
	{
		szNew[i] = szDigtal[nIndex-i-1];
	}

	nIndex = CString_To_long(szNew);
	return nIndex;
}

void CSclDataTypeTmpsCheckTool::CheckLNodeTypeOfGDW1396(CLNodeType *pObjDataType ,CExBaseList *pTemplates1396 ,CDLT860ModelChecks *pDLT860ModelChecks)
{
	CString strObjectID;
	CCheckObject *pCheckObject = NULL;
	////////////////第一步：准备好模板和SCD文件的DataTypeTemplates对象//////////////////////////////////////////////////
	CExBaseList *pTestObjectTemplates = (CExBaseList*)m_oSCLTestObjectFile.FindByID("DataTypeTemplates");
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
			strErrorText.Format(/*"LNodeType: id=%s,lnClass=%s 采用了未经标准定义的逻辑节点类 , 此类不得私自扩充;"*/g_sLangTxt_SCLCompare_DL860Description1.GetString(),
				pObjDataType->m_strID.GetString() ,
				pObjDataType->m_strLnClass.GetString());
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
		strErrorText.Format(/*"LNodeType: id=%s,lnClass=%s 逻辑节点下未定义任何DO;"*/g_sLangTxt_SCLCompare_DL860Description2.GetString(),
			pObjDataType->m_strID.GetString() ,pObjDataType->m_strLnClass.GetString());
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
						strErrorText.Format(/*"LNodeType: id=%s,lnClass=%s 中缺少必备DO: name=%s ;"*/g_sLangTxt_SCLCompare_DL860Description3.GetString(),
							pObjDataType->m_strID.GetString(),
							pObjDataType->m_strLnClass.GetString() ,pTmpDOValue->m_strID.GetString());
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
			DelTailDigtal(strDOValueName);
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
					strErrorText.Format(/*"LNodeType: id=%s,lnClass=%s 中DO: name=%s 对应cdc=%s定义错误 ,标准定义为%s;"*/g_sLangTxt_SCLCompare_DL860Description4.GetString(),
						pObjDataType->m_strID.GetString(),
						pObjDataType->m_strLnClass.GetString(),pTmpDOValue->m_strID.GetString(),
						pDOType->m_strName.GetString(),pTmpDOValue->m_strName.GetString());
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
					strErrorText.Format(/*"LNodeType: id=%s,lnClass=%s 中缺少必备DO: name=%s ;"*/g_sLangTxt_SCLCompare_DL860Description5.GetString(),
						pObjDataType->m_strID.GetString(),
						pObjDataType->m_strLnClass.GetString() ,pTmpDOValue->m_strID.GetString());
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
					strErrorText.Format(/*"LNodeType: id=%s,lnClass=%s 中DO: name=%s 顺序与标准定义不一致;"*/g_sLangTxt_SCLCompare_DL860Description6.GetString(),
						pObjDataType->m_strID.GetString(),
						pObjDataType->m_strLnClass.GetString() ,pTmpDOValue->m_strID.GetString());
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
				strErrorText.Format(/*"LNodeType: id=%s,lnClass=%s 中DO: name=%s 对应type=%s 未在DOType中定义;"*/g_sLangTxt_SCLCompare_DL860Description7.GetString(),
					pObjDataType->m_strID.GetString(),
					pObjDataType->m_strLnClass.GetString() ,pObjDOValue->m_strID.GetString(),pObjDOValue->m_strType.GetString());
				AddCheckResultDLT860Tmps(strObjectID , strErrorText  ,pObjDOValue->m_strErrorPos);
			}
		}
	}
}

void CSclDataTypeTmpsCheckTool::CheckDOTypeOfGDW1396(CDOType *pObjDOType ,CExBaseList *pTemplates1396 ,CDLT860ModelChecks *pDLT860ModelChecks)
{
	CString  strObjectID,strFormatText;
	CCheckObject *pCheckObject = NULL;
	CExBaseList *pTestObjectTemplates = (CExBaseList*)m_oSCLTestObjectFile.FindByID("DataTypeTemplates");
	CExBaseObject *pChildType = NULL;
	CDOType *pTemplate = NULL;
	pTemplate = (CDOType*)pTemplates1396->FindByID(pObjDOType->m_strID);
	CString strErrorText;

	if (pTemplate == NULL)
	{
		pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DOType-illegal");

		if (BeCheckThisObject(pCheckObject ,strObjectID))
		{
			strFormatText = /*"DOType: id=%s,cdc=%s 采用了未经标准定义的DOType , 此类不得私自扩充;"*/g_sLangTxt_SCLCompare_DL860Description8;
			strErrorText.Format(strFormatText.GetString(),pObjDOType->m_strID.GetString(),pObjDOType->m_strName.GetString());
			AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjDOType->m_strErrorPos);
		}
		return;
	}

	POS objPos = pObjDOType->GetHeadPosition();
	POS tmpPos = pTemplate->GetHeadPosition();
	POS SymbolPos = NULL;
	if (objPos == NULL)
	{
		strErrorText.Format(/*"DOType: id=%s,cdc=%s DOType下未定义任何DA;"*/g_sLangTxt_SCLCompare_DL860Description9.GetString(),
			pObjDOType->m_strID.GetString() ,pObjDOType->m_strName.GetString());
		AddCheckResultDLT860Tmps("error" , strErrorText  ,pObjDOType->m_strErrorPos);
		return;
	}
	else if (pObjDOType->m_strName != pTemplate->m_strName)
	{
		pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DOType-cdc-illegal");

		if (BeCheckThisObject(pCheckObject ,strObjectID))
		{
			strErrorText.Format(/*"DOType: id=%s,cdc=%s 中cdc定义与标准不一致 , 标准定义为 cdc=%s;"*/g_sLangTxt_SCLCompare_DL860Description10.GetString(),
				pObjDOType->m_strID.GetString(),
				pObjDOType->m_strName.GetString() ,pTemplate->m_strName.GetString());
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
					strErrorText.Format(/*"DOType: id=%s 中缺少 DA: name=%s ;"*/g_sLangTxt_SCLCompare_DL860Description11.GetString(),pObjDOType->m_strID.GetString() ,pTmpValue->m_strID.GetString());
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
							strErrorText.Format(/*"DOType: id=%s 中缺少 DA: name=%s ;"*/g_sLangTxt_SCLCompare_DL860Description11.GetString(),
								pObjDOType->m_strID.GetString() ,pTmpValue->m_strID.GetString());
							AddCheckResultDLT860Tmps(strObjectID , strErrorText  ,pObjDOType->m_strErrorPos);
						}
					} 
					else
					{
						pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DOType-DA-order");

						if (BeCheckThisObject(pCheckObject ,strObjectID))
						{
							strErrorText.Format(/*"DOType: id=%s 中 DA: name=%s 顺序与标准不一致;"*/g_sLangTxt_SCLCompare_DL860Description12.GetString(),
								pObjDOType->m_strID.GetString(),pTmpValue->m_strID.GetString());
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
							strErrorText.Format(/*"DOType: id=%s 中 DA: name=%s 的 bType=%s 与标准 bType=%s 不一致;"*/g_sLangTxt_SCLCompare_DL860Description13.GetString(),
								pObjDOType->m_strID.GetString(),
								pTmpValue->m_strID.GetString() ,pObjDAValue->m_strBType.GetString() ,pTmpDAValue->m_strBType.GetString());
							AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjDAValue->m_strErrorPos);
						}
					}
					if (pObjDAValue->m_strFC!=pTmpDAValue->m_strFC)
					{
						pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DOType-DA-attr");

						if (BeCheckThisObject(pCheckObject ,strObjectID))
						{
							strErrorText.Format(/*"DOType: id=%s 中 DA: name=%s 的 fc=%s 与标准 fc=%s 不一致;"*/g_sLangTxt_SCLCompare_DL860Description14.GetString(),
								pObjDOType->m_strID.GetString(),
								pTmpValue->m_strID.GetString() ,pObjDAValue->m_strFC.GetString() ,pTmpDAValue->m_strFC.GetString());
							AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjDAValue->m_strErrorPos);
						}
					}
					if (pObjDAValue->m_strName!=pTmpDAValue->m_strName)
					{
						pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DOType-DA-attr");

						if (BeCheckThisObject(pCheckObject ,strObjectID))
						{
							strErrorText.Format(/*"DOType: id=%s 中 DA: name=%s 的 type=%s 与标准 type=%s 不一致;"*/g_sLangTxt_SCLCompare_DL860Description15.GetString(),
								pObjDOType->m_strID.GetString(),
								pTmpValue->m_strID.GetString() ,pObjDAValue->m_strName.GetString() ,pTmpDAValue->m_strName.GetString());
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
								strErrorText.Format(/*"DOType: id=%s 中 DA: name=%s 的 type=%s 未定义;"*/g_sLangTxt_SCLCompare_DL860Description16.GetString(),
									pObjDOType->m_strID.GetString(),
									pTmpValue->m_strID.GetString(),pObjDAValue->m_strName.GetString());
								AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjDAValue->m_strErrorPos);
							}
						}
					}
					if (pObjDAValue->m_strDchg!=pTmpDAValue->m_strDchg)
					{
						pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DOType-DA-attr");

						if (BeCheckThisObject(pCheckObject ,strObjectID))
						{
							strErrorText.Format(/*"DOType: id=%s 中 DA: name=%s 的 dchg=%s 与标准 dchg=%s 不一致;"*/g_sLangTxt_SCLCompare_DL860Description17.GetString(),
								pObjDOType->m_strID.GetString(),
								pTmpValue->m_strID.GetString(),pObjDAValue->m_strDchg.GetString(),pTmpDAValue->m_strDchg.GetString());
							AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjDAValue->m_strErrorPos);
						}
					}
					if (pObjDAValue->m_strQchg!=pTmpDAValue->m_strQchg)
					{
						pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DOType-DA-attr");

						if (BeCheckThisObject(pCheckObject ,strObjectID))
						{
							strErrorText.Format(/*"DOType: id=%s 中 DA: name=%s 的 qchg=%s 与标准 qchg=%s 不一致;"*/g_sLangTxt_SCLCompare_DL860Description18.GetString(),
								pObjDOType->m_strID.GetString(),
								pTmpValue->m_strID.GetString(),pObjDAValue->m_strQchg.GetString(),pTmpDAValue->m_strQchg.GetString());
							AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjDAValue->m_strErrorPos);
						}
					}
					if (pObjDAValue->m_strValue!=pTmpDAValue->m_strValue)
					{
						pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DOType-DA-attr");

						if (BeCheckThisObject(pCheckObject ,strObjectID))
						{
							strErrorText.Format(/*"DOType: id=%s 中 DA: name=%s 的 Val=%s 与标准 Val=%s 不一致;"*/g_sLangTxt_SCLCompare_DL860Description19.GetString(),
								pObjDOType->m_strID.GetString(),
								pTmpValue->m_strID.GetString() ,pObjDAValue->m_strValue.GetString(),pTmpDAValue->m_strValue.GetString());
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
					strErrorText.Format(/*"DOType: id=%s 中缺少 SDO: name=%s ;"*/g_sLangTxt_SCLCompare_DL860Description20.GetString(),
						pObjDOType->m_strID.GetString() ,pTmpValue->m_strID.GetString());
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
							strErrorText.Format(/*"DOType: id=%s 中缺少 SDO: name=%s ;"*/g_sLangTxt_SCLCompare_DL860Description20.GetString(),
								pObjDOType->m_strID.GetString() ,pTmpValue->m_strID.GetString());
							AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjDOType->m_strErrorPos);
						}
					} 
					else
					{
						pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DOType-DA-order");

						if (BeCheckThisObject(pCheckObject ,strObjectID))
						{
							strErrorText.Format(/*"DOType: id=%s 中 SDO: name=%s 顺序与标准不一致;"*/g_sLangTxt_SCLCompare_DL860Description21.GetString(),
								pObjDOType->m_strID.GetString() ,pTmpValue->m_strID.GetString());
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
							strErrorText.Format(/*"DOType: id=%s 中 SDO: name=%s 的 type=%s 与标准 type=%s 不一致;"*/g_sLangTxt_SCLCompare_DL860Description22.GetString(),
								pObjDOType->m_strID.GetString(),
								pTmpValue->m_strID.GetString() ,pObjSDOValue->m_strName.GetString() ,pTmpSDOValue->m_strName.GetString());
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
								strErrorText.Format(/*"DOType: id=%s 中 SDO: name=%s 的 type=%s 未定义;"*/g_sLangTxt_SCLCompare_DL860Description23.GetString(),
									pObjDOType->m_strID.GetString(),
									pTmpValue->m_strID.GetString(),pObjSDOValue->m_strName.GetString());
								AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjSDOValue->m_strErrorPos);
							}
						}
					}
				}
			}
		}
	}

}

void CSclDataTypeTmpsCheckTool::CheckDATypeOfGDW1396(CDAType *pObjDAType ,CExBaseList *pTemplates1396 ,CDLT860ModelChecks *pDLT860ModelChecks)
{
	CString  strObjectID;
	CCheckObject *pCheckObject = NULL;
	CExBaseList *pTestObjectTemplates = (CExBaseList*)m_oSCLTestObjectFile.FindByID("DataTypeTemplates");
	CExBaseObject *pChildType = NULL;
	CDAType *pTemplate = NULL;
	pTemplate = (CDAType*)pTemplates1396->FindByID(pObjDAType->m_strID);
	CString strErrorText;

	if (pTemplate == NULL)
	{
		pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DAType-illegal");

		if (BeCheckThisObject(pCheckObject ,strObjectID))
		{
			strErrorText.Format(/*"DAType: id=%s 采用了未经标准定义的DAType ;"*/g_sLangTxt_SCLCompare_DL860Description24.GetString(),
				pObjDAType->m_strID.GetString());
			AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjDAType->m_strErrorPos);
		}
		return;
	}

	POS objPos = pObjDAType->GetHeadPosition();
	POS tmpPos = pTemplate->GetHeadPosition();
	POS SymbolPos = NULL;
	if (objPos == NULL)
	{
		strErrorText.Format(/*"DAType: id=%s DAType下未定义任何BDA;"*/g_sLangTxt_SCLCompare_DL860Description25.GetString(), pObjDAType->m_strID.GetString() );
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
				strErrorText.Format(/*"DAType: id=%s 中缺少 BDA: name=%s ;"*/g_sLangTxt_SCLCompare_DL860Description26.GetString(),
					pObjDAType->m_strID.GetString() ,pTmpBDAValue->m_strID.GetString());
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
						strErrorText.Format(/*"DAType: id=%s 中缺少 BDA: name=%s ;"*/g_sLangTxt_SCLCompare_DL860Description26.GetString(),
							pObjDAType->m_strID.GetString() ,pTmpBDAValue->m_strID.GetString());
						AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjDAType->m_strErrorPos);
					}
				} 
				else
				{
					pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DAType-BDA-order");

					if (BeCheckThisObject(pCheckObject ,strObjectID))
					{
						strErrorText.Format(/*"DAType: id=%s 中 BDA: name=%s 顺序与标准不一致;"*/g_sLangTxt_SCLCompare_DL860Description27.GetString(),
							pObjDAType->m_strID.GetString() ,pTmpBDAValue->m_strID.GetString());
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
						strErrorText.Format(/*"DAType: id=%s 中 BDA: name=%s 的 bType=%s 与标准 bType=%s 不一致;"*/g_sLangTxt_SCLCompare_DL860Description28.GetString(),
							pObjDAType->m_strID.GetString(),
							pTmpBDAValue->m_strID.GetString() ,pObjBDAValue->m_strBType.GetString() ,pTmpBDAValue->m_strBType.GetString());
						AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjBDAValue->m_strErrorPos);
					}
				}
				if (pObjBDAValue->m_strName!=pTmpBDAValue->m_strName)
				{
					pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("DAType-BDA-attr");

					if (BeCheckThisObject(pCheckObject ,strObjectID))
					{
						strErrorText.Format(/*"DAType: id=%s 中 BDA: name=%s 的 type=%s 与标准 type=%s 不一致;"*/g_sLangTxt_SCLCompare_DL860Description29.GetString(),
							pObjDAType->m_strID.GetString(),
							pTmpBDAValue->m_strID.GetString() ,pObjBDAValue->m_strName.GetString() ,pTmpBDAValue->m_strName.GetString());
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
							strErrorText.Format(/*"DAType: id=%s 中 BDA: name=%s 的 type=%s 未定义;"*/g_sLangTxt_SCLCompare_DL860Description30.GetString(),
								pObjDAType->m_strID.GetString(),
								pTmpBDAValue->m_strID.GetString() ,pObjBDAValue->m_strName.GetString());
							AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjBDAValue->m_strErrorPos);
						}
					}
				}
			}
		}
	} 
}

void CSclDataTypeTmpsCheckTool::CheckEnumTypeOfGDW1396(CEnumType *pObjEnumType ,CExBaseList *pTemplates1396 ,CDLT860ModelChecks *pDLT860ModelChecks)
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
			strErrorText.Format(/*"EnumType: id=%s 采用了未经标准定义的EnumType ;"*/g_sLangTxt_SCLCompare_DL860Description31.GetString(),
				pObjEnumType->m_strID.GetString() );
			AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjEnumType->m_strErrorPos);
		}
		return;
	}

	POS objPos = pObjEnumType->GetHeadPosition();
	POS tmpPos = pTemplate->GetHeadPosition();
	POS SymbolPos = NULL;
	if (objPos == NULL)
	{
		strErrorText.Format(/*"EnumType: id=%s DAType下未定义任何EnumVal;"*/g_sLangTxt_SCLCompare_DL860Description32.GetString(), pObjEnumType->m_strID.GetString() );
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
				strErrorText.Format(/*"EnumType: id=%s 中缺少 EnumVal: ord=%s 值为%s;"*/g_sLangTxt_SCLCompare_DL860Description33.GetString(),
					pObjEnumType->m_strID.GetString(),
					pTmpEnumVal->m_strID.GetString() ,pTmpEnumVal->m_strName.GetString());
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
						strErrorText.Format(/*"EnumType: id=%s 中 EnumVal值为%s :ord=%s 与标准定义 ord=%s 不一致;"*/g_sLangTxt_SCLCompare_DL860Description34.GetString(),
							pObjEnumType->m_strID.GetString(),
							pObjEnumVal->m_strName.GetString() ,pObjEnumVal->m_strID.GetString() ,pTmpEnumVal->m_strID.GetString());
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
							strErrorText.Format(/*"EnumType: id=%s 中缺少 EnumVal:ord=%s 值为%s ;"*/g_sLangTxt_SCLCompare_DL860Description35.GetString(),
								pObjEnumType->m_strID.GetString(),
								pTmpEnumVal->m_strID.GetString() ,pTmpEnumVal->m_strName.GetString());
							AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjEnumType->m_strErrorPos);
						}
					} 
					else
					{
						pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("EnumType-EnumVal-order");

						if (BeCheckThisObject(pCheckObject ,strObjectID))
						{
							strErrorText.Format(/*"EnumType: id=%s 中 EnumVal值为%s 顺序与标准不一致;"*/g_sLangTxt_SCLCompare_DL860Description36.GetString(),
								pObjEnumType->m_strID.GetString(),
								pTmpEnumVal->m_strName.GetString());
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
							strErrorText.Format(/*"EnumType: id=%s 中缺少 EnumVal:ord=%s 值为%s ;"*/g_sLangTxt_SCLCompare_DL860Description37.GetString(),
								pObjEnumType->m_strID.GetString(),
								pTmpEnumVal->m_strID.GetString() ,pTmpEnumVal->m_strName.GetString());
							AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjEnumType->m_strErrorPos);
						}
					} 
					else
					{
						pCheckObject = (CCheckObject*)pDLT860ModelChecks->FindByID("EnumType-EnumVal-order");

						if (BeCheckThisObject(pCheckObject ,strObjectID))
						{
							strErrorText.Format(/*"EnumType: id=%s 中 EnumVal值为%s 顺序与标准不一致;"*/g_sLangTxt_SCLCompare_DL860Description38.GetString(),
								pObjEnumType->m_strID.GetString()
								,pTmpEnumVal->m_strName.GetString());
							AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjEnumVal->m_strErrorPos);
						}
					}
				} 
			}
		}
	}
}

bool CSclDataTypeTmpsCheckTool::DataTypeCompareWithTemplates(CExBaseList *pTmpDataType , CExBaseList *pObjDataType )
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

long FindRepeat(CString strParant ,CString strChild)
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

POS CSclDataTypeTmpsCheckTool::checkDO_withRepeat(CLNodeType *pObjDataType , POS pos ,bool bDigtalTail ,CDLT860ModelChecks *pDLT860ModelChecks)
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
		nIndex = DelTailDigtal(strDOName);
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
				nIndexNext = DelTailDigtal(strDONameNext);

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
							strErrorText.Format(/*"LNodeType: id=%s,lnClass=%s 中DO: name=%s 末尾数字标号不连续;"*/g_sLangTxt_SCLCompare_DL860Description39.GetString(),
								pObjDataType->m_strID.GetString() ,
								pObjDataType->m_strLnClass.GetString() ,pObjDOValueNext->m_strID.GetString());
							AddCheckResultDLT860Tmps(strObjectID , strErrorText ,pObjDOValue->m_strErrorPos);
						}
					}	
				}
				else if (pObjDOValueNext->m_strType != pObjDOValue->m_strType)
				{
					strErrorText.Format(/*"LNodeType: id=%s,lnClass=%s 中DO: name=%s 对应type前后不一致;"*/g_sLangTxt_SCLCompare_DL860Description40.GetString(), 
						pObjDataType->m_strID.GetString(),
						pObjDataType->m_strLnClass.GetString() ,pObjDOValueNext->m_strID.GetString());
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

