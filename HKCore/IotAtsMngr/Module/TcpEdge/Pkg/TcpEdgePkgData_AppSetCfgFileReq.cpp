//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_AppSetCfgFileReq.cpp  CTcpEdgePkgData_AppSetCfgFileReq


#include "stdafx.h"
#include "TcpEdgePkgData_AppSetCfgFileReq.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgData_AppSetCfgFileReq::CTcpEdgePkgData_AppSetCfgFileReq()
{
	//初始化属性

	//初始化成员变量
	m_pTcpEdgePkgFile = NULL;
}

CTcpEdgePkgData_AppSetCfgFileReq::~CTcpEdgePkgData_AppSetCfgFileReq()
{
}

long CTcpEdgePkgData_AppSetCfgFileReq::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strContainerKey, oNode, m_strContainer);
	xml_GetAttibuteValue(pXmlKeys->m_strAppKey, oNode, m_strApp);
	return 0;
}

long CTcpEdgePkgData_AppSetCfgFileReq::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strContainerKey, oElement, m_strContainer);
	xml_SetAttributeValue(pXmlKeys->m_strAppKey, oElement, m_strApp);
	return 0;
}

long CTcpEdgePkgData_AppSetCfgFileReq::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strContainer);
		BinarySerializeCalLen(oBinaryBuffer, m_strApp);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strContainer);
		BinarySerializeRead(oBinaryBuffer, m_strApp);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strContainer);
		BinarySerializeWrite(oBinaryBuffer, m_strApp);
	}
	return 0;
}

void CTcpEdgePkgData_AppSetCfgFileReq::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == MNGRCLASSID_CTCPEDGEPKGFILE)
		{
			m_pTcpEdgePkgFile = (CTcpEdgePkgFile*)p;
		}
	}

	if (m_pTcpEdgePkgFile == NULL)
	{
		m_pTcpEdgePkgFile = (CTcpEdgePkgFile*)AddNewChild(new CTcpEdgePkgFile());
	}

}

BOOL CTcpEdgePkgData_AppSetCfgFileReq::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_AppSetCfgFileReq *p = (CTcpEdgePkgData_AppSetCfgFileReq*)pObj;

	if(m_strContainer != p->m_strContainer)
	{
		return FALSE;
	}

	if(m_strApp != p->m_strApp)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpEdgePkgData_AppSetCfgFileReq::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_AppSetCfgFileReq *p = (CTcpEdgePkgData_AppSetCfgFileReq*)pDest;

	p->m_strContainer = m_strContainer;
	p->m_strApp = m_strApp;
	return TRUE;
}

CBaseObject* CTcpEdgePkgData_AppSetCfgFileReq::Clone()
{
	CTcpEdgePkgData_AppSetCfgFileReq *p = new CTcpEdgePkgData_AppSetCfgFileReq();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgData_AppSetCfgFileReq::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgData_AppSetCfgFileReq *p = new CTcpEdgePkgData_AppSetCfgFileReq();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgData_AppSetCfgFileReq::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CTCPEDGEPKGFILE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_AppSetCfgFileReq::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCTcpEdgePkgFileKey)
	{
		pNew = new CTcpEdgePkgFile();
	}

	return pNew;
}

CExBaseObject* CTcpEdgePkgData_AppSetCfgFileReq::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CTCPEDGEPKGFILE)
	{
		pNew = new CTcpEdgePkgFile();
	}

	return pNew;
}
long CTcpEdgePkgData_AppSetCfgFileReq::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strContainerKey, m_strContainer);
	pRecordset->GetFieldValue(pXmlKeys->m_strAppKey, m_strApp);
	return 0;
}

long CTcpEdgePkgData_AppSetCfgFileReq::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strContainerKey, m_strContainer);
	pRecordset->SetFieldValue(pXmlKeys->m_strAppKey, m_strApp);
	return 0;
}


long CTcpEdgePkgData_AppSetCfgFileReq::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("Container"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("App"));
	pListCtrl->SetColumnWidth(2, 80);

	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CTcpEdgePkgData_AppSetCfgFileReq::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strContainer);
	pListCtrl->SetItemText(lItemIndex, 2, m_strApp);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

CDvmDataset* CTcpEdgePkgData_AppSetCfgFileReq::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_Data;
	pDataset->m_strDataType = PkgData_Type_Object;
	pDataset->m_dwItemData = 1;
	pDataset->m_dwReserved = 1;

	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_Container);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_App);
	CTcpEdgePkgData::AddNewData(pDataset, CTcpEdgePkgFile::ToDataset());

	return pDataset;
}