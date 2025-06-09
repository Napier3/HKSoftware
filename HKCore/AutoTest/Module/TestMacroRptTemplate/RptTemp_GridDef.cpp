//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_GridDef.cpp  CRptTemp_GridDef


#include "stdafx.h"
#include "RptTemp_GridDef.h"
#include "RptTemp_ReportTemplateDef.h"
#include "RptTemp_MacroCharItems.h"
#include "RptTemp_Items.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRptTemp_GridDef::CRptTemp_GridDef()
{
	//初始化属性
	m_pEnable = NULL;
	m_nShowBorders = 1;  //默认显示边框
	//初始化成员变量
}

CRptTemp_GridDef::~CRptTemp_GridDef()
{
}

long CRptTemp_GridDef::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strData_ModeKey, oNode, m_strData_Mode);
	xml_GetAttibuteValue(pXmlKeys->m_strShow_BordersKey, oNode, m_nShowBorders);
	return 0;
}

long CRptTemp_GridDef::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strData_ModeKey, oElement, m_strData_Mode);
	xml_SetAttributeValue(pXmlKeys->m_strShow_BordersKey, oElement, m_nShowBorders);
	return 0;
}

long CRptTemp_GridDef::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CRptTemp_GridDef::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == MNGRCLASSID_CRPTTEMP_ENABLE)
		{
			m_pEnable = (CRptTemp_Enable*)p;
		}
	}
}

BOOL CRptTemp_GridDef::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CRptTemp_GridDef *p = (CRptTemp_GridDef*)pObj;

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

BOOL CRptTemp_GridDef::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CRptTemp_GridDef *p = (CRptTemp_GridDef*)pDest;

	p->m_strData_Mode = m_strData_Mode;
	p->m_nShowBorders = m_nShowBorders;
	return TRUE;
}

CBaseObject* CRptTemp_GridDef::Clone()
{
	CRptTemp_GridDef *p = new CRptTemp_GridDef();
	Copy(p);
	return p;
}

CBaseObject* CRptTemp_GridDef::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CRptTemp_GridDef *p = new CRptTemp_GridDef();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CRptTemp_GridDef::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CRPTTEMP_COLSDEF)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CRPTTEMP_ROWSDEF)
	{
		return TRUE;
	}

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

	if (nClassID == MNGRCLASSID_CRPTTEMP_ENABLE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CRptTemp_GridDef::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCRptTemp_ColsDefKey)
	{
		pNew = new CRptTemp_ColsDef();
	}
	else if (strClassID == pXmlKeys->m_strCRptTemp_RowsDefKey)
	{
		pNew = new CRptTemp_RowsDef();
	}
	else if (strClassID == pXmlKeys->m_strCRptTemp_HeadKey)
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
	else if (strClassID == pXmlKeys->m_strCRptTemp_EnableKey)
	{
		pNew = new CRptTemp_Enable();
	}

	return pNew;
}

CExBaseObject* CRptTemp_GridDef::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CRPTTEMP_COLSDEF)
	{
		pNew = new CRptTemp_ColsDef();
	}
	else if (nClassID == MNGRCLASSID_CRPTTEMP_ROWSDEF)
	{
		pNew = new CRptTemp_RowsDef();
	}
	else if (nClassID == MNGRCLASSID_CRPTTEMP_HEAD)
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
	else if (nClassID == MNGRCLASSID_CRPTTEMP_ENABLE)
	{
		pNew = new CRptTemp_Enable();
	}

	return pNew;
}

/*
#define RPT_TEMPLATE_DATAMODE_ROW_ITEM    _T("row-item")
#define RPT_TEMPLATE_DATAMODE_COL_ITEM    _T("col-item")
#define RPT_TEMPLATE_DATAMODE_ROW_RPT     _T("row-rpt")
#define RPT_TEMPLATE_DATAMODE_COL_RPT     _T("col-rpt")
#define RPT_TEMPLATE_DATAMODE_NOT_DEF     _T("not-def") 
*/
long CRptTemp_GridDef::GetRowsCount()
{
	if (m_strData_Mode == RPT_TEMPLATE_DATAMODE_ROW_ITEM)
	{
		return GetRowsCount_RowItem();
	}
	else if (m_strData_Mode == RPT_TEMPLATE_DATAMODE_COL_ITEM)
	{
		return GetRowsCount_ColItem();
	}
	else if (m_strData_Mode == RPT_TEMPLATE_DATAMODE_ROW_RPT)
	{
		return GetRowsCount_RowRpt();
	}
	else if (m_strData_Mode == RPT_TEMPLATE_DATAMODE_COL_RPT)
	{
		return GetRowsCount_ColRpt();
	}

	return -1;
}

//行为项目模式，行数 = 表头 + 项目数
long CRptTemp_GridDef::GetRowsCount_RowItem()
{
	long nCount = 0;
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != MNGRCLASSID_CRPTTEMP_HEAD)
		{
			continue;
		}

		//先统计表头的数量
		nCount++;
	}

	//找到最近的CRptTemp_Items节点  或者  CRptTemp_MacroCharItems节点
	CRptTemp_ReportTemplateDef *pRptTemplateDef = (CRptTemp_ReportTemplateDef *)GetParent();
	CExBaseObject *pParent = (CExBaseObject *)pRptTemplateDef->GetParent();

	if (pParent->GetClassID() == MNGRCLASSID_CRPTTEMP_MACROCHARITEMS)
	{
		CRptTemp_MacroCharItems *pMacroCharItems = (CRptTemp_MacroCharItems *)pParent;
		nCount += pMacroCharItems->GetMacroTestCount();
	}
	else if (pParent->GetClassID() == MNGRCLASSID_CRPTTEMP_ITEMS)
	{
		CRptTemp_Items *pItems = (CRptTemp_Items *)pParent;
		nCount += pItems->GetMacroTestCount();
	}

	return nCount;
}

long CRptTemp_GridDef::GetRowsCount_ColItem()
{
	//暂不实现
	return -1;
}

long CRptTemp_GridDef::GetRowsCount_RowRpt()
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

long CRptTemp_GridDef::GetRowsCount_ColRpt()
{
	//暂不实现
	return -1;
}

long CRptTemp_GridDef::GetColsCount()
{
	if (m_strData_Mode == RPT_TEMPLATE_DATAMODE_ROW_ITEM)
	{
		return GetColsCount_RowItem();
	}
	else if (m_strData_Mode == RPT_TEMPLATE_DATAMODE_COL_ITEM)
	{
		return GetColsCount_ColItem();
	}
	else if (m_strData_Mode == RPT_TEMPLATE_DATAMODE_ROW_RPT)
	{
		return GetColsCount_RowRpt();
	}
	else if (m_strData_Mode == RPT_TEMPLATE_DATAMODE_COL_RPT)
	{
		return GetColsCount_ColRpt();
	}

	return -1;
}

long CRptTemp_GridDef::GetColsCount_RowItem()
{
	CRptTemp_ColsDef *pColsDef = (CRptTemp_ColsDef *)FindByClassID(MNGRCLASSID_CRPTTEMP_COLSDEF);

	if (pColsDef == NULL)
	{
		return -1;
	}

	return pColsDef->GetCount();
}

long CRptTemp_GridDef::GetColsCount_ColItem()
{
	//列模式：列为项目。暂不处理
	return -1;
}

long CRptTemp_GridDef::GetColsCount_RowRpt()
{
	CRptTemp_ColsDef *pColsDef = (CRptTemp_ColsDef *)FindByClassID(MNGRCLASSID_CRPTTEMP_COLSDEF);

	if (pColsDef == NULL)
	{
		return -1;
	}

	return pColsDef->GetCount();
}

long CRptTemp_GridDef::GetColsCount_ColRpt()
{
	//列模式：列为报告。暂不处理
	return -1;
}

long CRptTemp_GridDef::GetHeadCount()
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
BOOL CRptTemp_GridDef::IsDataMode_Row()
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
BOOL CRptTemp_GridDef::IsDataMode_Col()
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

//表格为row-item模式下，根据索引号，找到对应的项目
CRptTemp_MacroTest* CRptTemp_GridDef::GetMacroTest(long nIndex)
{
	CRptTemp_MacroTest *pFind = NULL;
	CRptTemp_ReportTemplateDef *pReportTemplateDef = (CRptTemp_ReportTemplateDef *)GetParent();
	CExBaseObject *pParent = (CExBaseObject *)pReportTemplateDef->GetParent();
	UINT nClassID = pParent->GetClassID();

	if (nClassID == MNGRCLASSID_CRPTTEMP_ITEMS)
	{
		CRptTemp_Items *pItems = (CRptTemp_Items *)pParent;
		pFind = (CRptTemp_MacroTest *)pItems->GetMacroTestByIndex(nIndex);
	}
	else if (nClassID == MNGRCLASSID_CRPTTEMP_MACROCHARITEMS)
	{
		CRptTemp_MacroCharItems *pMacroCharItems = (CRptTemp_MacroCharItems *)pParent;
		pFind = (CRptTemp_MacroTest *)pMacroCharItems->GetMacroTestByIndex(nIndex);
	}

	return pFind;
}

BOOL CRptTemp_GridDef::IsEnable(CExBaseList *pParas)
{
	if (m_pEnable == NULL)
	{
		//默认使能为1
		return TRUE;
	}

	return m_pEnable->IsEnable(pParas);
}