//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttXuiDataFileMngrGrid.cpp  CSttXuiDataFileMngrGrid


#include "stdafx.h"
#include "SttXuiDataFileMngrGrid.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttXuiDataFileMngrGrid::CSttXuiDataFileMngrGrid()
{
	//初始化属性
	m_nX = 0;
	m_nY = 0;
	m_nCx = 0;
	m_nCy = 0;

	//初始化成员变量
}

CSttXuiDataFileMngrGrid::~CSttXuiDataFileMngrGrid()
{
}

long CSttXuiDataFileMngrGrid::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttXuiDataBase::XmlReadOwn(oNode, pXmlRWKeys);

	CSttXMainConfigXmlRWKeys *pXmlKeys = (CSttXMainConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strXKey, oNode, m_nX);
	xml_GetAttibuteValue(pXmlKeys->m_strYKey, oNode, m_nY);
	xml_GetAttibuteValue(pXmlKeys->m_strCxKey, oNode, m_nCx);
	xml_GetAttibuteValue(pXmlKeys->m_strCyKey, oNode, m_nCy);
	xml_GetAttibuteValue(pXmlKeys->m_strEmit_ModeKey, oNode, m_strEmit_Mode);
	return 0;
}

long CSttXuiDataFileMngrGrid::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttXuiDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttXMainConfigXmlRWKeys *pXmlKeys = (CSttXMainConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strXKey, oElement, m_nX);
	xml_SetAttributeValue(pXmlKeys->m_strYKey, oElement, m_nY);
	xml_SetAttributeValue(pXmlKeys->m_strCxKey, oElement, m_nCx);
	xml_SetAttributeValue(pXmlKeys->m_strCyKey, oElement, m_nCy);
	xml_SetAttributeValue(pXmlKeys->m_strEmit_ModeKey, oElement, m_strEmit_Mode);
	return 0;
}

long CSttXuiDataFileMngrGrid::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CSttXuiDataBase::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nX);
		BinarySerializeCalLen(oBinaryBuffer, m_nY);
		BinarySerializeCalLen(oBinaryBuffer, m_nCx);
		BinarySerializeCalLen(oBinaryBuffer, m_nCy);
		BinarySerializeCalLen(oBinaryBuffer, m_strEmit_Mode);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nX);
		BinarySerializeRead(oBinaryBuffer, m_nY);
		BinarySerializeRead(oBinaryBuffer, m_nCx);
		BinarySerializeRead(oBinaryBuffer, m_nCy);
		BinarySerializeRead(oBinaryBuffer, m_strEmit_Mode);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nX);
		BinarySerializeWrite(oBinaryBuffer, m_nY);
		BinarySerializeWrite(oBinaryBuffer, m_nCx);
		BinarySerializeWrite(oBinaryBuffer, m_nCy);
		BinarySerializeWrite(oBinaryBuffer, m_strEmit_Mode);
	}
	return 0;
}

void CSttXuiDataFileMngrGrid::InitAfterRead()
{
}

BOOL CSttXuiDataFileMngrGrid::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CSttXuiDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttXuiDataFileMngrGrid *p = (CSttXuiDataFileMngrGrid*)pObj;

	if(m_nX != p->m_nX)
	{
		return FALSE;
	}

	if(m_nY != p->m_nY)
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

	if(m_strEmit_Mode != p->m_strEmit_Mode)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttXuiDataFileMngrGrid::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttXuiDataBase::CopyOwn(pDest);

	CSttXuiDataFileMngrGrid *p = (CSttXuiDataFileMngrGrid*)pDest;

	p->m_nX = m_nX;
	p->m_nY = m_nY;
	p->m_nCx = m_nCx;
	p->m_nCy = m_nCy;
	p->m_strEmit_Mode = m_strEmit_Mode;
	return TRUE;
}

CBaseObject* CSttXuiDataFileMngrGrid::Clone()
{
	CSttXuiDataFileMngrGrid *p = new CSttXuiDataFileMngrGrid();
	Copy(p);
	return p;
}

CBaseObject* CSttXuiDataFileMngrGrid::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttXuiDataFileMngrGrid *p = new CSttXuiDataFileMngrGrid();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttXuiDataFileMngrGrid::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTTXUIDATAFILETYPES)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSTTXUIDATACMD)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttXuiDataFileMngrGrid::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttXMainConfigXmlRWKeys *pXmlKeys = (CSttXMainConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttXuiDataFileTypesKey)
	{
		pNew = new CSttXuiDataFileTypes();
	}
	else if (strClassID == pXmlKeys->m_strCSttXuiDataCmdKey)
	{
		pNew = new CSttXuiDataCmd();
	}

	return pNew;
}

CExBaseObject* CSttXuiDataFileMngrGrid::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTTXUIDATAFILETYPES)
	{
		pNew = new CSttXuiDataFileTypes();
	}
	else if (nClassID == MNGRCLASSID_CSTTXUIDATACMD)
	{
		pNew = new CSttXuiDataCmd();
	}

	return pNew;
}
