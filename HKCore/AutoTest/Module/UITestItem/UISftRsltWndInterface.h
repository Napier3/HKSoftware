#pragma once

/*
	功能描述：Safety测试项目单个数据结果录入窗口接口实现，包括：标题、结果控件、单位
*/

#include "../../../Module/BaseClass/ExBaseObject.h"
#include "UISftRsltWndStatic.h"
#include "UISftRsltWndMultiSel.h"

static  const BSTR g_strMultiComboSeparator = L";";

#define ResultWndGap  4

#define RSLTEDITWNDTYPE_None          -1
#define RSLTEDITWNDTYPE_Edit          0
#define RSLTEDITWNDTYPE_ComboBox      1
#define RSLTEDITWNDTYPE_MultiSel      3
#define RSLTEDITWNDTYPE_DateTimeCtrl  4
#define RSLTEDITWNDTYPE_Password      5
#define RSLTEDITWNDTYPE_MacEdit       6
#define RSLTEDITWNDTYPE_IPEdit        7
#define RSLTEDITWNDTYPE_DvmDsDataset  8

class CUISftRsltWndInterface : public CExBaseObject
{
public:
	CUISftRsltWndInterface();
	virtual ~CUISftRsltWndInterface();

public:
	CShortData * m_oRsltData;
	CRect m_rectRsltWnd;

	CUISftRsltWndStatic* m_pTitle;		//标题
	CUISftRsltWndStatic* m_pUnit;		//单位
	CWnd* m_pRsltEditWnd;			    //结果控件

	long m_nRsltEditWndHeight;
	long m_nRsltEditWndType;
	CWnd* m_pParentWnd;

	//窗口的位置定义
	long m_nTitleWidth;

	long m_nHeight;
	long m_nWidth;
	long m_nLeft;
	long m_nTop;

	CRect m_rectTitle;
	CRect m_rectEdit;
	CRect m_rectUnit;

//方法
public:
	void CreateRsltEditWnd(CShortData * oRsltData,CWnd* pParent,long &nID,long nLeft=0,long nTop=0,long nWidth=400);
	void OnResultDataChanged(const CString &strData);
	void CalResultWndSize();
	long AdjustResultWndPosition(long xOffset,long yOffset,long nMaxTitleWidth);
	void SetFont(CFont* pFont);
	void ShowWindow();

	void AdjustLeft(long xPos, long nWidth);
	void AdjustRight(long xPosRight, long nWidth);
	void AdjustLeftRight(long xPosRight, long nWidth);
	void AdjustY(long &yPos, long nHeight);
	BOOL IsSingle();

private:
	void CreateRsltEditWnd(const CString& strDataType,const CString& strDomain,CWnd* pParentWnd,long &nID);
	void EndIt();

public:
	static const long g_nResultTitleWidth;
	static const long g_nResultEditWidth;
	static const long g_nResultUnitWidth;
	static const long g_nResultWndGap;
	static const long g_nResultColGapWidth;
	static const long g_nResultWndMinHeight;
	static const long g_nResultWndHeightEdit;
	static const long g_nResultWndHeightComboBox;
	static const long g_nResultWndHeightMultiComboBox;
	static const long g_nResultDlgMaxHeight;

// 	static const char *g_pszDataType_combobox;
// 	static const char *g_pszDataType_multicombobox;
// 	static const char *g_pszDataType_datetime;
// 	static const char *g_pszDataType_password;
// 	static const char* g_pszDataType_number;
// 	static const char* g_pszDataType_string;
};

long UI_GetOneResultWndMaxWidth();
long UI_GetSftWndMaxWidth();
long UI_GetSftInforWndMaxWidth();


class CUISftRsltWndRow : public CExBaseList
{
public:
	CUISftRsltWndRow()
	{
		m_pLeft = NULL;
		m_pRight = NULL;
		m_pSingle = NULL;
	}

	virtual ~CUISftRsltWndRow()
	{

	}

	long GetHeight()
	{
		long nHeight = 0;
		
		if (m_pLeft != NULL)
		{
			nHeight = m_pLeft->m_nHeight;
		}

		if (m_pRight != NULL)
		{
			nHeight = max(nHeight, m_pRight->m_nHeight);
		}

		if (m_pSingle != NULL)
		{
			nHeight = max(nHeight, m_pSingle->m_nHeight);
		}

		return nHeight;
	}

	long GetWidth()
	{
		return UI_GetOneResultWndMaxWidth();
	}

	void AdjustRow(long &nYPos);
	void SetLeft(CUISftRsltWndInterface *p)
	{
		m_pLeft = p;
	}

	void SetRight(CUISftRsltWndInterface *p)
	{
		m_pRight = p;
	}

	void SetSingle(CUISftRsltWndInterface *p)
	{
		m_pSingle = p;
	}

	CUISftRsltWndInterface* GetLeft( )
	{
		return m_pLeft;
	}

	CUISftRsltWndInterface* GetRight( )
	{
		return m_pRight;
	}

	CUISftRsltWndInterface* GetSingle( )
	{
		return m_pSingle;
	}

	void GetMaxWidth(long &nMaxWidthCol1, long &nMaxWidthCol2, long &nMaxWidthSingleCol)
	{
		if (m_pSingle != NULL)
		{
			nMaxWidthSingleCol = max(nMaxWidthSingleCol, m_pSingle->m_nWidth);
		}
		else
		{
			nMaxWidthCol1 = max(nMaxWidthCol1, m_pLeft->m_nWidth);

			if (m_pRight != NULL)
			{
				nMaxWidthCol2 = max(nMaxWidthCol2, m_pRight->m_nWidth);
			}
		}
	}

	void AdjustOne(long xPos, long nWidth)
	{
		if (m_pLeft != NULL)
		{
			m_pLeft->AdjustLeft(xPos, nWidth);
		}
	}

	void AdjustCol1(long xPos, long nWidth)
	{
		if (m_pLeft != NULL)
		{
			m_pLeft->AdjustLeft(xPos, nWidth);
		}
	}

	void AdjustCol2(long xPos, long nWidth)
	{
		if (m_pRight != NULL)
		{
			//m_pRight->AdjustLeft(xPos, nWidth);
			m_pRight->AdjustRight(xPos, nWidth);
		}
	}

	void AdjustColSingle(long xPosRight, long nWidth)
	{
		if (m_pSingle == NULL)
		{
			return;
		}

		m_pSingle->AdjustLeftRight(xPosRight, nWidth);
	}

	void AdjustY(long &yPos)
	{
		if (m_pSingle != NULL)
		{
			long nH = m_pSingle->m_nHeight;
			m_pSingle->AdjustY(yPos, nH);
			yPos += m_pSingle->m_nHeight;
		}
		else
		{
			long nH = m_pLeft->m_nHeight;

			if (m_pRight != NULL)
			{
				nH = max(nH, m_pRight->m_nHeight);
				m_pRight->AdjustY(yPos, nH);
			}

			m_pLeft->AdjustY(yPos, nH);
			yPos += nH;
		}
	}

private:
	CUISftRsltWndInterface *m_pLeft;
	CUISftRsltWndInterface *m_pRight;
	CUISftRsltWndInterface *m_pSingle;

};

class CUISftRsltWndRows : public CExBaseList
{
public:
	CUISftRsltWndRows(){};
	virtual ~CUISftRsltWndRows()
	{
		DeleteAll();
	}

	CUISftRsltWndRow* AddRow()
	{
		CUISftRsltWndRow *pNew = new CUISftRsltWndRow();
		AddTail(pNew);
		return pNew;
	}

	void GetMaxWidth(long &nMaxWidthCol1, long &nMaxWidthCol2, long &nMaxWidthSingleCol)
	{
		POS pos = GetHeadPosition();
		CUISftRsltWndRow *p = NULL;

		while (pos != NULL)
		{
			p = (CUISftRsltWndRow *)GetNext(pos);
			p->GetMaxWidth(nMaxWidthCol1, nMaxWidthCol2, nMaxWidthSingleCol);
		}
	}

	void AdjustCol1(long xPos, long nWidth)
	{
		POS pos = GetHeadPosition();
		CUISftRsltWndRow *p = NULL;

		while (pos != NULL)
		{
			p = (CUISftRsltWndRow *)GetNext(pos);
			p->AdjustCol1(xPos, nWidth);
		}
	}

	void AdjustOne(long xPos, long nWidth)
	{
		POS pos = GetHeadPosition();
		CUISftRsltWndRow *p = NULL;

		while (pos != NULL)
		{
			p = (CUISftRsltWndRow *)GetNext(pos);
			p->AdjustOne(xPos, nWidth);
		}
	}

	void AdjustCol2(long xPos, long nWidth)
	{
		POS pos = GetHeadPosition();
		CUISftRsltWndRow *p = NULL;

		while (pos != NULL)
		{
			p = (CUISftRsltWndRow *)GetNext(pos);
			p->AdjustCol2(xPos, nWidth);
		}
	}

	void AdjustColSingle(long xPosRight, long nWidth)
	{
		POS pos = GetHeadPosition();
		CUISftRsltWndRow *p = NULL;

		while (pos != NULL)
		{
			p = (CUISftRsltWndRow *)GetNext(pos);
			p->AdjustColSingle(xPosRight, nWidth);
		}
	}
};