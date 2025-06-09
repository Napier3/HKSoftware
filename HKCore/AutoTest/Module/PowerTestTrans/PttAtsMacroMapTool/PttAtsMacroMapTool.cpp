//PttAtsMacroMapTool.cpp  CPttAtsMacroMapTool

#include "stdafx.h"
#include "PttAtsMacroMapTool.h"
#include "..\PttGlobalDefine.h"

CPttAtsMacroMapTool::CPttAtsMacroMapTool()
{
	m_pMacroMaps = new CMacroMaps();
	m_pMapsMsgRcvWnd = NULL;
}

CPttAtsMacroMapTool::~CPttAtsMacroMapTool()
{
	delete m_pMacroMaps;
	m_pMacroMaps = NULL;

	m_listBinaryPara.RemoveAll();
}

void CPttAtsMacroMapTool::InitTool()
{
	ASSERT (m_pMacroMaps != NULL);
	m_pMacroMaps->OpenMacroMaps();
}

void CPttAtsMacroMapTool::SaveMapFile()
{
	ASSERT (m_pMacroMaps != NULL);
	m_pMacroMaps->SaveMapFile();
	SetModifiedFlag(FALSE);
}


void CPttAtsMacroMapTool::AnalyseFile (const CString& strFile)
{
	m_oFileParse.ReadFromTemplate(strFile);

	AddAllTestItemMacroToMaps(m_oFileParse.GetRoot());
}

void CPttAtsMacroMapTool::AnalyseFolder(const CString &strFolder)
{
	CXFileMngr oXFileMngr;
	CExBaseList listAllFile;
	CXFileType *pFileType = oXFileMngr.AddFileType(_T("tpl"), _T("tpl"), _T(""), _T(""));
	pFileType->AddNewPostfix(_T("tpl"), _T("tpl"));

	oXFileMngr.InitByXFileTypes();
	oXFileMngr.SetLibraryPath(strFolder);
	oXFileMngr.SelectAllFiles(listAllFile);

	POS pos = listAllFile.GetHeadPosition();
	CXFile *pFile = NULL;

	while (pos != NULL)
	{
		pFile = (CXFile *)listAllFile.GetNext(pos);
		AnalyseFile(pFile->GetTotalFileName());
	}

	//listAllFile.RemoveAll();
}
// 
// void CPttAtsMacroMapTool::AnalyseFolder (CXFolder *pXFolder)
// {
// 	CString strFolderPath;
// 	CExBaseObject *pObj;
// 
// 	POS pos = pXFolder->GetHeadPosition();

// 	while(pos != NULL)
// 	{
// 		pObj = pXFolder->GetNext(pos);
// 
// 		if (pObj->GetClassID() == CLASSID_XFOLDER)
// 		{
// 			AnalyseFolder((CXFolder *)pObj);
// 		}
// 		else if (pObj->GetClassID() == CLASSID_XFILE)
// 		{
// 			strFolderPath = ((CXFile*)pObj)->GetFolderPath(TRUE);
// 			strFolderPath += pObj->m_strName;
// 			AnalyseFile(strFolderPath);
// 		}
// 	}
// }

//UINT CPttAtsMacroMapTool::AnalyseThread(LPVOID pPara)
//{
//	return 0;
//}

void CPttAtsMacroMapTool::AddAllTestItemMacroToMaps(CPNTplRoot* pRoot)
{
	ASSERT(pRoot != NULL);
 
	POS pos = pRoot->GetHeadPosition();
	CExBaseObject *p = NULL;

	while(pos != NULL)
	{
		p = pRoot->GetNext(pos);
	
		if (p->m_strName == PTT_KEY_Binary)
		{
			m_listBinaryPara.RemoveAll();  //把上一个Binary参数清空
			AddBinaryParatoMap((CPNTplElement*)p);
		}
		else if(p->m_strName == PTT_KEY_TestItem)
		{
			AddMacroAndParatoMap((CPNTplElement*)p);
		}
		else if (p->GetClassID() == MNGRCLASSID_CPNTPLELEMENT)
		{
			AddAllTestItemMacroToMaps((CPNTplRoot*)p);	
		}
	}
}

//添加测试功能及对应测试参数到链表
BOOL CPttAtsMacroMapTool::AddMacroAndParatoMap(CPNTplElement* pTestItemElement)
{
	ASSERT(pTestItemElement != NULL);

	POS pos = pTestItemElement->GetHeadPosition();
	CExBaseObject *p = NULL;
	CMacroMap* pMacroMap = NULL;
	BOOL bNewMaps = FALSE;

	while(pos != NULL)
	{
		p = pTestItemElement->GetNext(pos);

		if (p->m_strName == PTT_KEY_TestComName2)
		{
			pMacroMap = (CMacroMap*)m_pMacroMaps->FindByID(( (CPNTplEquation*) p)->m_strValue);

			if (pMacroMap == NULL)
			{
				pMacroMap = new CMacroMap();
				m_pMacroMaps->AddNewChild(pMacroMap);
				pMacroMap->m_strName = ((CPNTplEquation*)p)->m_strValue;
				pMacroMap->m_strID = ((CPNTplEquation*)p)->m_strValue;	
				bNewMaps = TRUE;
			}

			break;
		}
	}

	if (pMacroMap == NULL)
	{
		CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("错误！"));
	}
	else
	{
		AddParatoMap(pMacroMap, pTestItemElement);
		POS pos2 = m_listBinaryPara.GetHeadPosition();
		CExBaseObject* p2 = NULL;
		while (pos2 != NULL)
		{
			p2 = m_listBinaryPara.GetNext(pos2);
			if (pMacroMap->FindByID(p2->m_strID) == NULL)
			{
				pMacroMap->AddNewChild(p2);
			}
		}
	}

	if (bNewMaps && m_pMapsMsgRcvWnd != NULL)
	{
		SetModifiedFlag();
		m_pMapsMsgRcvWnd->PostMessage(WM_INSERT_NEW_MAP, (WPARAM)pMacroMap, (LPARAM)pMacroMap);
		//发送消息给窗口，标识新添加一个映射项目，在
	}

	return bNewMaps;
}

//添加测试参数到链表
void CPttAtsMacroMapTool::AddParatoMap(CMacroMap* pMacroMap, CPNTplElement* pElement)
{
	ASSERT(pElement != NULL);

	POS pos = pElement->GetHeadPosition();
	CExBaseObject *p = NULL;
	CParaMap* pParaMap = NULL;

	while(pos != NULL)
	{
		p = pElement->GetNext(pos);

		if (p->m_strName == PTT_KEY_TestComName2)
		{
			continue;
		}

		pParaMap = (CParaMap*)pMacroMap->FindByID(p->m_strName);

		if (pParaMap == NULL)
		{
			pParaMap = new CParaMap;
			pMacroMap->AddNewChild(pParaMap);
			pParaMap->m_strName = p->m_strName;
			pParaMap->m_strID = p->m_strName;	
			SetModifiedFlag();
		}
	}
}

void CPttAtsMacroMapTool::AddBinaryParatoMap(CPNTplElement* pBinary)
{
	ASSERT(pBinary != NULL);

	POS pos = pBinary->GetHeadPosition();
	CPNTplGroup* pGroup = NULL;
	CParaMap* pBinaryPara = NULL;
	CPNTplEquation *pEquationID = NULL;
	CPNTplEquation *pEquationN = NULL;

	while (pos != NULL)
	{
		pGroup = (CPNTplGroup*)pBinary->GetNext(pos);
		pEquationID = (CPNTplEquation *)pGroup->FindByID(PTT_KEY_DATA_ATTR_ID);
		pEquationN = (CPNTplEquation *)pGroup->FindByID(PTT_KEY_DATA_ATTR_N);

		if (pEquationID == NULL || pEquationN == NULL)
		{
			continue;
		}

		pBinaryPara = (CParaMap*)m_listBinaryPara.FindByID(pEquationID->m_strValue);

		if (pBinaryPara == NULL)
		{
			pBinaryPara = new CParaMap;
			m_listBinaryPara.AddNewChild(pBinaryPara);
			pBinaryPara->m_strName = pEquationN->m_strValue;
			pBinaryPara->m_strID = pEquationID->m_strValue;
		}
	}
}
