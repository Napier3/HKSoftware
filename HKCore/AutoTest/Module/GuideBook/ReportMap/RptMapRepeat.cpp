#include "StdAfx.h"
#include "RptMapRepeat.h"
#include "RptBkmk.h"
#include "RptData.h"
#include "../MacroTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CRptMapRepeat::CRptMapRepeat(void)
{
	m_strID = L"_rpt_map_repeat";
	m_strName = m_strID;
	m_nIndex = 0;
}

CRptMapRepeat::~CRptMapRepeat(void)
{
	//DeleteAll();
}

CBaseObject* CRptMapRepeat::Clone()
{
	CRptMapRepeat *pNew = new CRptMapRepeat();
	Copy(pNew);
	return pNew;
}


BOOL CRptMapRepeat::CopyOwn(CBaseObject* pDest)
{
	ASSERT(pDest != NULL);

	if(this == pDest)
		return TRUE;

	((CRptMapRepeat*)pDest)->m_nIndex = m_nIndex;

	CExBaseObject::CopyOwn(pDest);

	return TRUE;
}


CExBaseObject* CRptMapRepeat::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CGbXMLKeys *pKeys = (CGbXMLKeys*)pXmlRWKeys;

	if (strClassID == pKeys->m_strDataKey)
	{
		return new CRptData();
	}

	return NULL;

}

CExBaseObject* CRptMapRepeat::CreateNewChild(long nClassID)
{
	if(nClassID == RPTCLASSID_RPTDATA)
	{
		return new CRptData();
	}

	return NULL;
}


//ReadXML && WriteXML
long CRptMapRepeat::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(((CGbXMLKeys *)pXmlRWKeys)->m_strIndexKey, oNode, m_nIndex);

	return 0;
}


long CRptMapRepeat::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	xml_SetAttributeValue(((CGbXMLKeys *)pXmlRWKeys)->m_strIndexKey, oElement, m_nIndex);

	return 0;
}

long CRptMapRepeat::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer,m_nIndex);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer,m_nIndex);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer,m_nIndex);
	}

	return 0;
}

CString CRptMapRepeat::GetRptMapRepeatName()
{
	CString strName;
	CExBaseObject *pParent = (CExBaseObject*)GetParent();
	pParent = (CExBaseObject*)pParent->GetParent();
	CGbItemBase *pGbItem = (CGbItemBase *)pParent;
	UINT nClassID = pGbItem->GetClassID();
	long nMaxCount = 0;
	CString strCalMode;

	if (nClassID == GBCLASSID_MACROTEST)
	{
		nMaxCount = ((CMacroTest*)pGbItem)->m_nRepeatTimes;
		strCalMode = ((CMacroTest*)pGbItem)->m_strReportMode;
	}
	else if (nClassID == GBCLASSID_COMMCMD)
	{
		CCommCmd *pCommCmd = (CCommCmd*)pGbItem;
		CCmd *pCmd = pCommCmd->GetCmd();
		nMaxCount = pCmd->m_nRepeatTimes;
		strCalMode = pCmd->m_strCalMode;
	}

	if (m_nIndex == 0 || m_nIndex == nMaxCount || m_nIndex == -1)
	{
		strName = Gb_GetReportCalModeText(strCalMode);

		if (strName == g_sLangTxt_None/*_T("无")*/)
		{
			strName.Format(g_sLangTxt_ReDTest/*_T("重复第%d次测试")*/, m_nIndex + 1);
		}
	}
	else
	{
		strName.Format(g_sLangTxt_ReDTest/*_T("重复第%d次测试")*/, m_nIndex + 1);
	}

	return strName;
}

