//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CSttFrame_GlobalDatas.cpp  CSttFrame_GlobalDatas


#include "stdafx.h"
#include "SttFrame_GlobalDatas.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CSttFrame_GlobalDatas::CSttFrame_GlobalDatas()
{
	//初始化属性

	//初始化成员变量
	m_pGlobalData =NULL;
}

CSttFrame_GlobalDatas::~CSttFrame_GlobalDatas()
{
}

long CSttFrame_GlobalDatas::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttFrame_GlobalDatas::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttFrame_GlobalDatas::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CSttFrame_GlobalDatas::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == MNGRCLASSID_CSTTFRAME_GLOBALDATA)
		{
			m_pGlobalData = (CSttFrame_GlobalData*)p;
		}
	}

	if (m_pGlobalData == NULL)
	{
		m_pGlobalData = (CSttFrame_GlobalData*)AddNewChild(new CSttFrame_GlobalData());
	}
}

BOOL CSttFrame_GlobalDatas::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttFrame_GlobalDatas *p = (CSttFrame_GlobalDatas*)pObj;

	return TRUE;
}

BOOL CSttFrame_GlobalDatas::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttFrame_GlobalDatas *p = (CSttFrame_GlobalDatas*)pDest;

	return TRUE;
}

CBaseObject* CSttFrame_GlobalDatas::Clone()
{
	CSttFrame_GlobalDatas *p = new CSttFrame_GlobalDatas();
	Copy(p);
	return p;
}
CBaseObject* CSttFrame_GlobalDatas::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttFrame_GlobalDatas *p = new CSttFrame_GlobalDatas();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttFrame_GlobalDatas::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTTFRAME_GLOBALDATA)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttFrame_GlobalDatas::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttTestCtrlFrameCfgMngrXmlRWKeys *pXmlKeys = (CSttTestCtrlFrameCfgMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttFrame_GlobalDataKey)
	{
		pNew = new CSttFrame_GlobalData();
	}

	return pNew;
}

CExBaseObject* CSttFrame_GlobalDatas::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTTFRAME_GLOBALDATA)
	{
		pNew = new CSttFrame_GlobalData();
	}

	return pNew;
}

long CSttFrame_GlobalDatas::GetTabHeight()
{
	CSttFrame_GlobalData *pSttFrame_GlobalData = (CSttFrame_GlobalData*)FindByID(STTFRAME_GLOBALDATA_TabHeight_ID);
	long nHeight = 40;

	if (pSttFrame_GlobalData != NULL)
	{
		nHeight = CString_To_long(pSttFrame_GlobalData->m_strValue);
	}

	return nHeight;
}

long CSttFrame_GlobalDatas::GetComBoxItemHeight()
{
	CSttFrame_GlobalData *pSttFrame_GlobalData = (CSttFrame_GlobalData*)FindByID(STTFRAME_GLOBALDATA_ComBoxItemHeight_ID);
	long nHeight = 50;
	
	if (pSttFrame_GlobalData != NULL)
	{
		nHeight = CString_To_long(pSttFrame_GlobalData->m_strValue);
	}
	
	return nHeight;
}

long CSttFrame_GlobalDatas::GetTableVertScrollWidth()
{
	CSttFrame_GlobalData *pSttFrame_GlobalData = (CSttFrame_GlobalData*)FindByID(STTFRAME_GLOBALDATA_TableVertScrollWidth_ID);
	long nHeight = 50;

	if (pSttFrame_GlobalData != NULL)
	{
		nHeight = CString_To_long(pSttFrame_GlobalData->m_strValue);
	}

	return nHeight;
}

long CSttFrame_GlobalDatas::GetTableHorizontalScrollHeight()
{
	CSttFrame_GlobalData *pSttFrame_GlobalData = (CSttFrame_GlobalData*)FindByID(STTFRAME_GLOBALDATA_TableHorizontalScrollHeight_ID);
	long nHeight = 50;

	if (pSttFrame_GlobalData != NULL)
	{
		nHeight = CString_To_long(pSttFrame_GlobalData->m_strValue);
	}

	return nHeight;
}

long CSttFrame_GlobalDatas::GetTreeVertScrollWidth()
{
	CSttFrame_GlobalData *pSttFrame_GlobalData = (CSttFrame_GlobalData*)FindByID(STTFRAME_GLOBALDATA_TreeVertScrollWidth_ID);
	long nHeight = 50;

	if (pSttFrame_GlobalData != NULL)
	{
		nHeight = CString_To_long(pSttFrame_GlobalData->m_strValue);
	}

	return nHeight;
}

long CSttFrame_GlobalDatas::GetTreeHorizontalScrollHeight()
{
	CSttFrame_GlobalData *pSttFrame_GlobalData = (CSttFrame_GlobalData*)FindByID(STTFRAME_GLOBALDATA_TreeHorizontalScrollHeight_ID);
	long nHeight = 50;

	if (pSttFrame_GlobalData != NULL)
	{
		nHeight = CString_To_long(pSttFrame_GlobalData->m_strValue);
	}

	return nHeight;
}

long CSttFrame_GlobalDatas::GetComBoxVertScrollWidth()
{
	CSttFrame_GlobalData *pSttFrame_GlobalData = (CSttFrame_GlobalData*)FindByID(STTFRAME_GLOBALDATA_ComBoxVertScrollWidth_ID);
	long nHeight = 50;

	if (pSttFrame_GlobalData != NULL)
	{
		nHeight = CString_To_long(pSttFrame_GlobalData->m_strValue);
	}

	return nHeight;	

}

