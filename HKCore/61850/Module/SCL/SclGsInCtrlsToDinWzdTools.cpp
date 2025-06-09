// SclGsInCtrlsToDinWzdTools.cpp : 实现文件
//

#include "stdafx.h"
#include "SclGsInCtrlsToDinWzdTools.h"

CSclGsInCtrlsToDinWzdTools::CSclGsInCtrlsToDinWzdTools()
{
	CGbWzdToolXmlRWKeys::Create();
	InitKeyMapDataTypes();
}

CSclGsInCtrlsToDinWzdTools::~CSclGsInCtrlsToDinWzdTools()
{
	CGbWzdToolXmlRWKeys::Release();
}

//导出遥信向导配置文件
void CSclGsInCtrlsToDinWzdTools::ExportDinWzdFile(const CString &strFile, CSclCtrlsGsIn *pGsInCtrls)
{
	m_oDinWzdFromSclGinChs.DeleteAll();
	ExportDinWzdFromSclGinCh(&m_oDinWzdFromSclGinChs, pGsInCtrls);
	m_oDinWzdFromSclGinChs.SaveXmlFile(strFile, CGbWzdToolXmlRWKeys::g_pXmlKeys);
}

void CSclGsInCtrlsToDinWzdTools::InitKeyMapDataTypes()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("SclGsInCtrlsToDinWzdKeyMap.xml");
	m_oKeyMapDataTypes.Open(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

CString CSclGsInCtrlsToDinWzdTools::GetNameKey(const CString &strGinChPath)
{
	POS pos = m_oKeyMapDataTypes.GetHeadPosition();
	CDataType *pDataType = NULL;
	CDataType *pFind = NULL;

	while (pos != NULL)
	{
		pDataType = (CDataType *)m_oKeyMapDataTypes.GetNext(pos);

		if (strGinChPath.Find(pDataType->m_strID) >= 0)
		{
			pFind = pDataType;
			break;
		}
	}

	if (pFind != NULL)
	{
		return pFind->m_strName;
	}
	else
	{
		return _T("");
	}
}

void CSclGsInCtrlsToDinWzdTools::Set_DinWzdFromSclGinCh(CSclCtrlGsIn *pGsInCtrl, CSclChGsIn *pGsChIn, CDinWzdFromSclGinCh *pWzdCh)
{
	if (pGsChIn->fcda_desc.GetLength() > 0)
	{
		pWzdCh->m_strName.Format(_T("%s:%s"), pGsInCtrl->m_strIedDesc, pGsChIn->fcda_desc);
	}
	else if (pGsChIn->fcda_dodesc.GetLength() > 0)
	{
		pWzdCh->m_strName.Format(_T("%s:%s"), pGsInCtrl->m_strIedDesc, pGsChIn->fcda_dodesc);
	}
	else if (pGsChIn->inDADesc.GetLength() > 0)
	{
		pWzdCh->m_strName.Format(_T("%s:%s"), pGsInCtrl->m_strIedDesc, pGsChIn->inDADesc);
	}
	else if (pGsChIn->inDODesc.GetLength() > 0)
	{
		pWzdCh->m_strName.Format(_T("%s:%s"), pGsInCtrl->m_strIedDesc, pGsChIn->inDODesc);
	}

	CString strNameKey = GetNameKey(pGsChIn->fcda_name);

	if (strNameKey.GetLength() > 0)
	{
		pWzdCh->m_strName.AppendFormat(_T(";%s"), strNameKey);
	}

	pWzdCh->m_strID = pGsChIn->fcda_name;
	pWzdCh->m_strAppID.Format(_T("%d"), pGsInCtrl->m_dwAppID);
	pWzdCh->m_strGsChIndex.Format(_T("%d"), pGsChIn->outIndex);
	pWzdCh->m_strDataType = pGsChIn->fcda_type;
}

void  CSclGsInCtrlsToDinWzdTools::ExportDinWzdGsInCtrl(CDinWzdFromSclGinChs *pDinWzdFromSclGinChs, CSclCtrlGsIn *pGsInCtrl)
{
	POS pos = pGsInCtrl->GetHeadPosition();
	CSclChGsIn *pGsChIn = NULL;
	CDinWzdFromSclGinCh *pWzdCh = NULL;

	while (pos != NULL)
	{
		pGsChIn = (CSclChGsIn *)pGsInCtrl->GetNext(pos);
		pWzdCh = new CDinWzdFromSclGinCh();
		Set_DinWzdFromSclGinCh(pGsInCtrl, pGsChIn, pWzdCh);
		pDinWzdFromSclGinChs->AddTail(pWzdCh);
	}
}



void  CSclGsInCtrlsToDinWzdTools::ExportDinWzdFromSclGinCh(CDinWzdFromSclGinChs *pDinWzdFromSclGinChs, CSclCtrlsGsIn *pGsInCtrls)
{
	POS pos = pGsInCtrls->GetHeadPosition();
	CSclCtrlGsIn *pGsIn = NULL;

	while (pos != NULL)
	{
		pGsIn = (CSclCtrlGsIn *)pGsInCtrls->GetNext(pos);
		ExportDinWzdGsInCtrl(pDinWzdFromSclGinChs, pGsIn);
	}
}

