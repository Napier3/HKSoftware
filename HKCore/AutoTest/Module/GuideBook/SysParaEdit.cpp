#include "stdafx.h"
#include "SysParaEdit.h"
//#include "SysParaEditGroupMngr.h"
#include "Device.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CSysParaEdit::CSysParaEdit()
{
	m_pParas = NULL;
	m_strDatasetPath = g_strwSysPara;
	m_pSysParaEditGroups = NULL;
}

CSysParaEdit::~CSysParaEdit()
{
	m_oListMsgs.RemoveAll();
	m_oListCommCmds.RemoveAll();

// 	if (m_pSysParaEditGroups != NULL)
// 	{
// 		CSysParaEditGroups *pSysParaEditGroups = (CSysParaEditGroups*)m_pSysParaEditGroups;
// 		pSysParaEditGroups->Release(TRUE);
// 		delete pSysParaEditGroups;
// 		m_pSysParaEditGroups = NULL;
// 	}

	m_oListDataTotal.RemoveAll();
	m_oListDataEdit.RemoveAll();
}

CGbItemBase* CSysParaEdit::CloneForTempFile()
{
	return new CSysParaEdit();
}

BOOL CSysParaEdit::GetItemParaValue(const CString &strValueID, double &dValue)
{
	return 0;
}

long CSysParaEdit::SetItemParaValue(const CString & strValueID, const CString & strValue, BOOL bAddNew)
{
	return 0;
}

BOOL CSysParaEdit::IsDeviceIndexPara(const CString &strID)
{
	if (strID == DATAID_DEVICEID)
	{
		return TRUE;
	}

	if (strID == DATAID_LDEVICEID)
	{
		return TRUE;
	}
	
	return FALSE;
}


//重写父类方法
long CSysParaEdit::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CGbItemBase::SerializeOwn(oBinaryBuffer);

	long nCount = 0;

	if (oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer,m_strDatasetPath);
	}
	else if (oBinaryBuffer.IsReadMode())
	{	
		BinarySerializeRead(oBinaryBuffer,m_strDatasetPath);
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer,m_strDatasetPath);
	}

	return 0;
}

long CSysParaEdit::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbItemBase::XmlReadOwn(oNode,pXmlRWKeys);

	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strTypeKey,oNode,m_strDatasetPath);

	return 0 ;
}

long CSysParaEdit::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbItemBase::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	if (g_bGbExportXmlReportFile)
	{
		if (CGuideBookExportConfig::g_pGuideBookExportConfig->m_nExportItemAttrSimplify)
		{
			return 0;
		}
	}

	if (g_bGbSaveGbStruDscFile)
	{
		return 0;
	}

	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strTypeKey,oElement,m_strDatasetPath);

	return 0;
}

CExBaseObject* CSysParaEdit::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strMsgKey)
	{
		CMsg* pMsg = new CMsg();
		return pMsg;
	}
	else if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strCValuesKey)
	{
		m_pParas = new CValues();
		return m_pParas;
	}
	else if(strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strCommCmdKey)
	{
		CCommCmd* pCommCmd = new CCommCmd();
		return pCommCmd;
	}

	return CGbItemBase::CreateNewChild(strClassID,bAddToTail,pXmlRWKeys);
}

CExBaseObject* CSysParaEdit::CreateNewChild(long nClassID)
{
	if(nClassID == GBCLASSID_MSG)
	{
		CMsg* pMsg = new CMsg();
		return pMsg;
	}
	else if (nClassID == DTMCLASSID_CVALUES)
	{
		m_pParas = new CValues();
		return m_pParas;
	}
	else if(nClassID == GBCLASSID_COMMCMD)
	{
		CCommCmd* pCommCmd = new CCommCmd();
		return pCommCmd;
	}

	return CGbItemBase::CreateNewChild(nClassID);
}


BOOL CSysParaEdit::IsEqual(CBaseObject* pObj)
{
	return FALSE;
}

BOOL CSysParaEdit::CopyOwn(CBaseObject* pDesObj)
{
	ASSERT(pDesObj != NULL);

	if(pDesObj == this)
		return TRUE;

	CSysParaEdit *p = (CSysParaEdit*)pDesObj;

	p->m_strDatasetPath = m_strDatasetPath;

	CGbItemBase::CopyOwn(pDesObj);
	
	return TRUE;
}

void CSysParaEdit::InitAfterRead()
{
	CGbItemBase::InitAfterRead();

	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;
	m_oListMsgs.RemoveAll();
	m_oListCommCmds.RemoveAll();

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		switch (nClassID)
		{
		case GBCLASSID_MSG:
			m_oListMsgs.AddTail(p);
			break;
		case GBCLASSID_COMMCMD:
			m_oListCommCmds.AddTail(p);
			m_oSubGbItems.AddTail(p);
			((CGbItemBase*)p)->m_bIsSubItem = TRUE;
			break;
		case DTMCLASSID_CVALUES:
			m_pParas = (CValues*)p;
			break;

		default:
			break;
		}
	}

	if (m_pParas == NULL)
	{
		m_pParas = new CValues();
		AddNewChild(m_pParas);
	}
}

CBaseObject* CSysParaEdit::Clone()
{
	CSysParaEdit* pSysEdit = new CSysParaEdit();

	Copy(pSysEdit);

	return pSysEdit;
}

CValues* CSysParaEdit::GetParas()
{
	if (m_pParas == NULL)
	{
		m_pParas = new CValues();
		AddNewChild(m_pParas);
	}

	return m_pParas;				
}

CExBaseList* CSysParaEdit::GetMsgs()
{
	return &m_oListMsgs;
}

CExBaseList* CSysParaEdit::GetCommCmds()
{	
	return &m_oListCommCmds;		
}

CExBaseList* CSysParaEdit::GetSysParaEditGroup()
{
// 	if (m_pSysParaEditGroups == NULL)
// 	{
// 		CSysParaEditGroups *pSysParaEditGroups = new CSysParaEditGroups();
// 		pSysParaEditGroups->InitSysParaEditGroups(this);
// 		m_pSysParaEditGroups = pSysParaEditGroups;
// 
// 		CExBaseObject *pDevice = (CExBaseObject*)GetAncestor(GBCLASSID_DEVICE);
// 
// 		if (pDevice != NULL)
// 		{
// 			m_pSysParaEditGroups->m_strName = pDevice->m_strName;
// 			m_pSysParaEditGroups->m_strID = pDevice->m_strID;
// 		}
// 	}
// 
// 	return m_pSysParaEditGroups;
	return NULL;
}

CExBaseList* CSysParaEdit::GetDatasetRef()
{
	CDevice *pDevice = (CDevice*)GetAncestor(GBCLASSID_DEVICE);
	ASSERT (pDevice != NULL);
	CExBaseList oList;
	pDevice->SelectDataSetList(m_strDatasetPath, oList, DSID_ALL_DVM);

	CExBaseList *pDatasRef = (CExBaseList*)oList.GetHead();
	oList.RemoveAll();

	return pDatasRef;
}

CString CSysParaEdit::InitDataList(long &nDatasCount)
{
	m_oListDataTotal.RemoveAll();
	m_oListDataEdit.RemoveAll();

	CDevice *pDevice = (CDevice*)GetAncestor(GBCLASSID_DEVICE);
	ASSERT (pDevice != NULL);
	CExBaseList oList;
	CExBaseObject *p = NULL;
	CDataSet *pDataSetHead = NULL;
	CString strDatasetNamePath;

	pDevice->SelectDataSetList(m_strDatasetPath, oList, DSID_ALL_DVM);

	POS pos = oList.GetHeadPosition();

	while (pos != NULL)
	{
		p = oList.GetNext(pos);

		UINT nClassID = p->GetClassID();

		if ((nClassID == GBCLASSID_DATASET)
			|| (nClassID == GBCLASSID_DATASETGROUP)
			|| (nClassID == GBCLASSID_DEVICE_SYSPARAS))
		{
			CDataSet *pDataset = (CDataSet*)p;
			m_oListDataTotal.Append(pDataset);
			pDataSetHead = pDataset;
		}
	}

	oList.RemoveAll();

	if (m_pParas->GetCount() == 0)
	{
		nDatasCount = -1;
		m_oListDataEdit.Append(m_oListDataTotal);
	}
	else
	{
		POS pos = m_pParas->GetHeadPosition();
		CValue *pValue = NULL;
		CDataObj *pFind = NULL;

		while (pos != NULL)
		{
			pValue = (CValue *)m_pParas->GetNext(pos);
			pFind = (CDataObj*)m_oListDataTotal.FindByID(pValue->m_strID);

			if (pFind != NULL)
			{
				m_oListDataEdit.AddTail(pFind);
				pFind->m_dwItemData = (DWORD)pValue;
				pFind->m_strValue = pValue->m_strValue;
			}
		}

		nDatasCount = m_oListDataEdit.GetCount();
	}

	if (pDataSetHead != NULL)
	{
		strDatasetNamePath = pDataSetHead->GetNamePathEx(GBCLASSID_DEVICE);
	}

	return strDatasetNamePath;
}

CValues* CSysParaEdit::GetReportValues()
{
	CValues *pValues = new CValues();

	POS pos = m_oListDataEdit.GetHeadPosition();
	CDataObj *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDataObj *)m_oListDataEdit.GetNext(pos);
		pValues->AddNew(pData->m_strID, pData->m_strName, pData->m_strValue);
	}

	return pValues;
}


long CSysParaEdit::CalTestTimeLong()
{
	return 0;
}

//shaolei 20220607
void CSysParaEdit::SetItemState(long nShow, long nEnable, long nSelect, BOOL bSetShow, BOOL bSetEnable, BOOL bSetSelect)
{
	CGbItemBase::SetItemState(nShow, nEnable, nSelect, bSetShow, bSetEnable, bSetSelect);

	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		//系统参数编辑下的子项目类型，只有通讯命令项目
		if (nClassID != GBCLASSID_COMMCMD)
		{
			continue;
		}

		CCommCmd* pCmd = (CCommCmd *)pObj;
		//此处是否应当考虑，如果设置成1，子项目是不是不需要设置？
		pCmd->SetItemState(nShow, nEnable, nSelect, bSetShow, bSetEnable, bSetSelect);
	}
}

long CSysParaEdit::GetItemTestCount()
{
	CGbItemBase *pParent = (CGbItemBase *)GetParent();

	return pParent->GetItemTestCount();
}

void CSysParaEdit::ClearReport(BOOL bBack)
{
	CGbItemBase::ClearReport(bBack);

	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if(p->GetClassID() == GBCLASSID_COMMCMD)
		{
			CCommCmd *pCommCmd = (CCommCmd*)p;
			pCommCmd->ClearReport(bBack);
		}
	}	
}