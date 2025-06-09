#pragma once

//功能描述 报告中的位置定义,对于Word/WPS来说为书签
#include "../GuideBookDefine.h"
#include "../GbDataTypeMngr.h"

#define RPTBKMK_ATTRID_VALUE   0
#define RPTBKMK_ATTRID_NAME    1


inline long Bkmk_GetIndexFromID(const CString &strID)
{
	DWORD nPos = strID.ReverseFind(_T('_'));
	DWORD nLength = strID.GetLength();
	CString strTemp = strID.Right(nLength - nPos-1);

#ifdef _UNICODE
	return _wtoi(strTemp);
#else
    return atoi(strTemp.GetString());
#endif
}

class CWordBkmk;

#define BKMK_FILLMODE_CELL   0
#define BKMK_FILLMODE_COL    1
#define BKMK_FILLMODE_ROW    2

inline CString rpt_bkmk_GetFillMode(UINT nFillMode)
{
	switch (nFillMode)
	{
	case BKMK_FILLMODE_CELL:
		return g_strDataFillModeTypeID_Cell;

	case BKMK_FILLMODE_COL:
		return g_strDataFillModeTypeID_Col;

	case BKMK_FILLMODE_ROW:
		return g_strDataFillModeTypeID_Row;

	default:
		return g_strDataFillModeTypeID_Cell;
	}
}

inline UINT rpt_bkmk_GetFillMode(const CString &strFillMode)
{
	if (strFillMode.GetLength() == 0)
	{
		return BKMK_FILLMODE_CELL;
	}

	if (strFillMode == g_strDataFillModeTypeID_Cell)
	{
		return BKMK_FILLMODE_CELL;
	}

	if (strFillMode == g_strDataFillModeTypeID_Row)
	{
		return BKMK_FILLMODE_ROW;
	}

	if (strFillMode == g_strDataFillModeTypeID_Col)
	{
		return BKMK_FILLMODE_COL;
	}

	return BKMK_FILLMODE_CELL;
}

inline BOOL rpt_bkmk_is_FillMode_cell(const CString &strFillMode)
{
	if (strFillMode.GetLength() == 0)
	{
		return TRUE;
	}

	if (strFillMode == g_strDataFillModeTypeID_Cell)
	{
		return TRUE;
	}

	return FALSE;
}

inline BOOL rpt_bkmk_is_FillMode_col(const CString &strFillMode)
{
	if (strFillMode == g_strDataFillModeTypeID_Col)
	{
		return TRUE;
	}

	return FALSE;
}

inline BOOL rpt_bkmk_is_FillMode_row(const CString &strFillMode)
{
	if (strFillMode == g_strDataFillModeTypeID_Row)
	{
		return TRUE;
	}

	return FALSE;
}

class CRptBkmk :	public CExBaseObject
{
public:
	CRptBkmk(void);
	virtual ~CRptBkmk(void);

//属性
public:
	long m_dwIndex;		//索引，标签后的数字
	CString m_strDataAttrID;   //数据属性ID，name、id、value、unit等
	CString m_strProcess;      //数据的处理
	CString m_strFillMode;     //cell=0,col=1,row=2
	CString m_strMgrpCmbnMode;   //多通道测试报告合并处理模式  2017-10-12
	CWordBkmk *m_pBkmk;
	void GetIndexFromID()		{	m_dwIndex = Bkmk_GetIndexFromID(m_strID);	}

//重写父类函数
public:
	virtual UINT GetClassID()													{        return RPTCLASSID_RPTBKMK;												}  
	virtual BSTR GetXmlElementKey()								{      return CGbXMLKeys::g_pGbXMLKeys->m_strBkmkKey;		}
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	BOOL IsFillMode_Cell()	{	return rpt_bkmk_is_FillMode_cell(m_strFillMode);	}
	BOOL IsFillMode_Col()	{	return rpt_bkmk_is_FillMode_col(m_strFillMode);		}
	BOOL IsFillMode_Row()	{	return rpt_bkmk_is_FillMode_row(m_strFillMode);		}
	void GetRowCol(UINT &nRow, UINT &nCol);
	void SetRowCol(UINT nRow,  UINT nCol);
};

class CWordBkmk : public CExBaseObject
{
public:
	CWordBkmk();
	virtual ~CWordBkmk();

	CRptBkmk *m_pBkmk;
};

CExBaseList* _FindRptBkmkByID(CExBaseList *pList, const CString &strID, CExBaseList *pListDest);
