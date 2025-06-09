//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_Grid.cpp  CRptTemp_Grid


#include "stdafx.h"
#include "RptTemp_Grid.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRptTemp_Grid::CRptTemp_Grid()
{
	//初始化属性
	m_nShowBorders = 1;  //默认显示边框
	//初始化成员变量
}

CRptTemp_Grid::~CRptTemp_Grid()
{
}

long CRptTemp_Grid::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strData_ModeKey, oNode, m_strData_Mode);
	xml_GetAttibuteValue(pXmlKeys->m_strShow_BordersKey, oNode, m_nShowBorders);
	return 0;
}

long CRptTemp_Grid::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strData_ModeKey, oElement, m_strData_Mode);
	xml_SetAttributeValue(pXmlKeys->m_strShow_BordersKey, oElement, m_nShowBorders);
	return 0;
}

long CRptTemp_Grid::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strData_Mode);
		BinarySerializeCalLen(oBinaryBuffer, m_nShowBorders);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strData_Mode);
		BinarySerializeRead(oBinaryBuffer, m_nShowBorders);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strData_Mode);
		BinarySerializeWrite(oBinaryBuffer, m_nShowBorders);
	}
	return 0;
}

void CRptTemp_Grid::InitAfterRead()
{
}

BOOL CRptTemp_Grid::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CRptTemp_Grid *p = (CRptTemp_Grid*)pObj;

	if(m_strData_Mode != p->m_strData_Mode)
	{
		return FALSE;
	}

	if(m_nShowBorders != p->m_nShowBorders)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CRptTemp_Grid::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CRptTemp_Grid *p = (CRptTemp_Grid*)pDest;

	p->m_strData_Mode = m_strData_Mode;
	p->m_nShowBorders = m_nShowBorders;
	return TRUE;
}

CBaseObject* CRptTemp_Grid::Clone()
{
	CRptTemp_Grid *p = new CRptTemp_Grid();
	Copy(p);
	return p;
}

CBaseObject* CRptTemp_Grid::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CRptTemp_Grid *p = new CRptTemp_Grid();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CRptTemp_Grid::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CRPTTEMP_HEAD)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CRPTTEMP_ROW)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CRPTTEMP_COL)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CRptTemp_Grid::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCRptTemp_HeadKey)
	{
		pNew = new CRptTemp_Head();
	}
	else if (strClassID == pXmlKeys->m_strCRptTemp_RowKey)
	{
		pNew = new CRptTemp_Row();
	}
	else if (strClassID == pXmlKeys->m_strCRptTemp_ColKey)
	{
		pNew = new CRptTemp_Col();
	}

	return pNew;
}

CExBaseObject* CRptTemp_Grid::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == MNGRCLASSID_CRPTTEMP_HEAD)
	{
		pNew = new CRptTemp_Head();
	}
	else if (nClassID == MNGRCLASSID_CRPTTEMP_ROW)
	{
		pNew = new CRptTemp_Row();
	}
	else if (nClassID == MNGRCLASSID_CRPTTEMP_COL)
	{
		pNew = new CRptTemp_Col();
	}

	return pNew;
}

//统计表格行的数量：表头 + 数据行
long CRptTemp_Grid::GetRowsCount()
{
	if (IsDataMode_Row())
	{
		return GetRowsCount_RowMode();
	}
	else if (IsDataMode_Col())
	{
		return GetRowsCount_ColMode();
	}

	return -1;
}

long CRptTemp_Grid::GetColsCount()
{
	if (IsDataMode_Row())
	{
		return GetColsCount_RowMode();
	}
	else if (IsDataMode_Col())
	{
		return GetColsCount_ColMode();
	}

	return -1;
}

long CRptTemp_Grid::GetRowsCount_RowMode()
{
	long nCount = 0;
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == MNGRCLASSID_CRPTTEMP_HEAD
			|| nClassID == MNGRCLASSID_CRPTTEMP_ROW)
		{
			nCount++;
		}
	}

	return nCount;
}

//行模式下，获取列的数量。可以根据定义的head或者row中，cell子节点的数量来获得
long CRptTemp_Grid::GetColsCount_RowMode()
{
	//先看是否存在head
	CRptTemp_Head* pHead = (CRptTemp_Head *)FindByClassID(MNGRCLASSID_CRPTTEMP_HEAD);

	if (pHead != NULL)
	{
		return pHead->GetCount();
	}

	//找不到head，就找row
	CRptTemp_Row* pRow = (CRptTemp_Row *)FindByClassID(MNGRCLASSID_CRPTTEMP_ROW);

	if (pRow != NULL)
	{
		return pRow->GetCount();
	}

	return -1;
}

long CRptTemp_Grid::GetRowsCount_ColMode()
{
	//列填写模式，暂不实现
	return -1;
}

long CRptTemp_Grid::GetColsCount_ColMode()
{
	//列填写模式，暂不实现
	return -1;
}

long CRptTemp_Grid::GetHeadCount()
{
	long nCount = 0;
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == MNGRCLASSID_CRPTTEMP_HEAD)
		{
			nCount++;
		}
	}

	return nCount;
}

//是否是行填写模式
BOOL CRptTemp_Grid::IsDataMode_Row()
{
	if (m_strData_Mode == RPT_TEMPLATE_DATAMODE_ROW_ITEM)
	{
		return TRUE;
	}
	else if (m_strData_Mode == RPT_TEMPLATE_DATAMODE_ROW_RPT)
	{
		return TRUE;
	}
	else 
	{
		return FALSE;
	}
}

//是否是列填写模式
BOOL CRptTemp_Grid::IsDataMode_Col()
{
	if (m_strData_Mode == RPT_TEMPLATE_DATAMODE_COL_ITEM)
	{
		return TRUE;
	}
	else if (m_strData_Mode == RPT_TEMPLATE_DATAMODE_COL_RPT)
	{
		return TRUE;
	}
	else 
	{
		return FALSE;
	}
}