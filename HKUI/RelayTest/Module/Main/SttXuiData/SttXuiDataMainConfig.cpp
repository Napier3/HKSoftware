//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttXuiDataMainConfig.cpp  CSttXuiDataMainConfig


#include "stdafx.h"
#include "SttXuiDataMainConfig.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttXuiDataMainConfig::CSttXuiDataMainConfig()
{
	//初始化属性
	m_nCx = 0;
	m_nCy = 0;
	m_nShowBatteryBtn = 1;
    m_dStartupDelayTime = 3.0f;

	//初始化成员变量
}

CSttXuiDataMainConfig::~CSttXuiDataMainConfig()
{
}

long CSttXuiDataMainConfig::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttXuiDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CSttXMainConfigXmlRWKeys *pXmlKeys = (CSttXMainConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strVersionKey, oNode, m_strVersion);
	xml_GetAttibuteValue(pXmlKeys->m_strTitleKey, oNode, m_strTitle);
	xml_GetAttibuteValue(pXmlKeys->m_strPicKey, oNode, m_strPic);
	xml_GetAttibuteValue(pXmlKeys->m_strCxKey, oNode, m_nCx);
	xml_GetAttibuteValue(pXmlKeys->m_strCyKey, oNode, m_nCy);
	xml_GetAttibuteValue(pXmlKeys->m_StrShowBatteryBtnKey, oNode, m_nShowBatteryBtn);
	xml_GetAttibuteValue(pXmlKeys->m_strStartupDelayTimeKey, oNode, m_dStartupDelayTime);
	return 0;
}

long CSttXuiDataMainConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttXuiDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CSttXMainConfigXmlRWKeys *pXmlKeys = (CSttXMainConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strVersionKey, oElement, m_strVersion);
	xml_SetAttributeValue(pXmlKeys->m_strTitleKey, oElement, m_strTitle);
	xml_SetAttributeValue(pXmlKeys->m_strPicKey, oElement, m_strPic);
	xml_SetAttributeValue(pXmlKeys->m_strCxKey, oElement, m_nCx);
	xml_SetAttributeValue(pXmlKeys->m_strCyKey, oElement, m_nCy);
	xml_SetAttributeValue(pXmlKeys->m_StrShowBatteryBtnKey, oElement, m_nShowBatteryBtn);
	xml_SetAttributeValue(pXmlKeys->m_strStartupDelayTimeKey, oElement, m_dStartupDelayTime);
	return 0;
}

long CSttXuiDataMainConfig::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CSttXuiDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strVersion);
		BinarySerializeCalLen(oBinaryBuffer, m_strTitle);
		BinarySerializeCalLen(oBinaryBuffer, m_strPic);
		BinarySerializeCalLen(oBinaryBuffer, m_nCx);
		BinarySerializeCalLen(oBinaryBuffer, m_nCy);
		BinarySerializeCalLen(oBinaryBuffer, m_nShowBatteryBtn);
		BinarySerializeCalLen(oBinaryBuffer, m_dStartupDelayTime);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strVersion);
		BinarySerializeRead(oBinaryBuffer, m_strTitle);
		BinarySerializeRead(oBinaryBuffer, m_strPic);
		BinarySerializeRead(oBinaryBuffer, m_nCx);
		BinarySerializeRead(oBinaryBuffer, m_nCy);
		BinarySerializeCalLen(oBinaryBuffer, m_nShowBatteryBtn);
		BinarySerializeCalLen(oBinaryBuffer, m_dStartupDelayTime);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strVersion);
		BinarySerializeWrite(oBinaryBuffer, m_strTitle);
		BinarySerializeWrite(oBinaryBuffer, m_strPic);
		BinarySerializeWrite(oBinaryBuffer, m_nCx);
		BinarySerializeWrite(oBinaryBuffer, m_nCy);
		BinarySerializeCalLen(oBinaryBuffer, m_nShowBatteryBtn);
		BinarySerializeCalLen(oBinaryBuffer, m_dStartupDelayTime);
	}
	return 0;
}

void CSttXuiDataMainConfig::InitAfterRead()
{
}

BOOL CSttXuiDataMainConfig::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CSttXuiDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttXuiDataMainConfig *p = (CSttXuiDataMainConfig*)pObj;

	if(m_strName != p->m_strName)
	{
		return FALSE;
	}

	if(m_strVersion != p->m_strVersion)
	{
		return FALSE;
	}

	if(m_strTitle != p->m_strTitle)
	{
		return FALSE;
	}

	if(m_strPic != p->m_strPic)
	{
		return FALSE;
	}

	if(m_nCx != p->m_nCx)
	{
		return FALSE;
	}

	if(m_nCy != p->m_nCy)
	{
		return FALSE;
	}

	if (m_nShowBatteryBtn != p->m_nShowBatteryBtn)
	{
		return FALSE;
	}

	if (m_dStartupDelayTime != p->m_dStartupDelayTime)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CSttXuiDataMainConfig::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttXuiDataBase::CopyOwn(pDest);

	CSttXuiDataMainConfig *p = (CSttXuiDataMainConfig*)pDest;

	p->m_strName = m_strName;
	p->m_strVersion = m_strVersion;
	p->m_strTitle = m_strTitle;
	p->m_strPic = m_strPic;
	p->m_nCx = m_nCx;
	p->m_nCy = m_nCy;
	p->m_nShowBatteryBtn = m_nShowBatteryBtn;
	p->m_dStartupDelayTime = m_dStartupDelayTime;
	return TRUE;
}

CBaseObject* CSttXuiDataMainConfig::Clone()
{
	CSttXuiDataMainConfig *p = new CSttXuiDataMainConfig();
	Copy(p);
	return p;
}

CBaseObject* CSttXuiDataMainConfig::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttXuiDataMainConfig *p = new CSttXuiDataMainConfig();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttXuiDataMainConfig::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTTXUIDATAGLOBAL)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSTTXUIDATATABS)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSTTXUIDATABTNSGROUP)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSTTXUIDATABUTTON)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSTTXUIDATAFILEMNGRGRID)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSTTXUIDATATESTBTNSGROUP)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSTTXUIDATATEXT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttXuiDataMainConfig::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttXMainConfigXmlRWKeys *pXmlKeys = (CSttXMainConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttXuiDataGlobalKey)
	{
		pNew = new CSttXuiDataGlobal();
	}
	else if (strClassID == pXmlKeys->m_strCSttXuiDataTabsKey)
	{
		pNew = new CSttXuiDataTabs();
	}
	else if (strClassID == pXmlKeys->m_strCSttXuiDataBtnsGroupKey)
	{
		pNew = new CSttXuiDataBtnsGroup();
	}
	else if (strClassID == pXmlKeys->m_strCSttXuiDataButtonKey)
	{
		pNew = new CSttXuiDataButton();
	}
	else if (strClassID == pXmlKeys->m_strCSttXuiDataFileMngrGridKey)
	{
		pNew = new CSttXuiDataFileMngrGrid();
	}
	else if (strClassID == pXmlKeys->m_strCSttXuiDataTestBtnsGroupKey)
	{
		pNew = new CSttXuiDataTestBtnsGroup();
	}
	else if (strClassID == pXmlKeys->m_strCSttXuiDataTextKey)
	{
		pNew = new CSttXuiDataText();
	}

	return pNew;
}

CExBaseObject* CSttXuiDataMainConfig::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTTXUIDATAGLOBAL)
	{
		pNew = new CSttXuiDataGlobal();
	}
	else if (nClassID == MNGRCLASSID_CSTTXUIDATATABS)
	{
		pNew = new CSttXuiDataTabs();
	}
	else if (nClassID == MNGRCLASSID_CSTTXUIDATABTNSGROUP)
	{
		pNew = new CSttXuiDataBtnsGroup();
	}
	else if (nClassID == MNGRCLASSID_CSTTXUIDATABUTTON)
	{
		pNew = new CSttXuiDataButton();
	}
	else if (nClassID == MNGRCLASSID_CSTTXUIDATAFILEMNGRGRID)
	{
		pNew = new CSttXuiDataFileMngrGrid();
	}
	else if (nClassID == MNGRCLASSID_CSTTXUIDATATESTBTNSGROUP)
	{
		pNew = new CSttXuiDataTestBtnsGroup();
	}
	else if (nClassID == MNGRCLASSID_CSTTXUIDATATEXT)
	{
		pNew = new CSttXuiDataText();
	}

	return pNew;
}
