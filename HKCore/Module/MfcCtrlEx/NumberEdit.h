#if !defined(NUMBEREDIT_H__)
#define NUMBEREDIT_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NumberEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNumberEdit window

#include <math.h>
#define MAXCharacterLength 8
#include "..\API\StringApi.h"

class CNumberEdit : public CEdit
{
// Construction
public:
	CNumberEdit();

// Attributes
public:
	CString m_strText;

private:
	BOOL m_bUseMin;
	BOOL m_bUseMax;
	long m_nMinValue;
	long m_nMaxValue;
	double m_fMinValue;
	double m_fMaxValue;
	CString m_strUnit;
	CString m_strFormat;


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNumberEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	//派生的方法
	//virtual BOOL UICreate(CWnd *pParent);

	//自身的方法
	void ArrowUp();
	void ArrowDown();
	void ArrowRight();
	void ArrowLeft();
	void UpdateText(CString& strText,int nStart,int nEnd);
	void SetValue(long nValue)
	{
		m_strText.Format(m_strFormat, nValue, m_strUnit);
		SetWindowText(m_strText);
	}
	void SetValue(float fValue)
	{
		m_strText.Format(m_strFormat, fValue, m_strUnit);
		SetWindowText(m_strText);
	}

	void SetValue(double dValue)
	{
		m_strText.Format(m_strFormat, dValue, m_strUnit);
		SetWindowText(m_strText);
	}

	void GetValue(long &nValue)
	{
		nValue = CString_To_long(m_strText);
	}

	void GetValue(float &fValue)
	{
		fValue = (float)CString_To_double(m_strText);
	}

	void GetValue(double &dValue)	
	{
		dValue = CString_To_double(m_strText);
	}


	void SetMinMax(long nMin, long nMax, BOOL bUseMin=TRUE, BOOL bUseMax=TRUE)
	{
		m_nMinValue = nMin;
		m_nMaxValue = nMax;
		m_bUseMax = bUseMax;
		m_bUseMin = bUseMin;
	}
	void SetMinMax(double dMin, double dMax, BOOL bUseMin=TRUE, BOOL bUseMax=TRUE)
	{
		m_fMinValue = dMin;
		m_fMaxValue = dMax;
		m_bUseMax = bUseMax;
		m_bUseMin = bUseMin;
	}

	void InitFormat(const CString &strUnit, const CString &strFormat)
	{
		m_strUnit = strUnit;
		m_strFormat = strFormat;
	}

	///////////////
	virtual ~CNumberEdit();

private:
	void InitByMinMaxValue();
	void InitByMinMaxValueLong();
	void InitByMinMaxValueFloat();
	void UpdateUnit();//zhouhj 20210319 更新单位显示信息

// Generated message map functions
protected:
	//{{AFX_MSG(CNumberEdit)
	afx_msg void OnChange();
	afx_msg void OnKillfocus();
	afx_msg void OnSetfocus();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	int m_nFormat;	
	BOOL m_bFocus;
	enum FORMAT{FM_NONE,FM_Float,FM_Integer,FM_Password,FM_String,FM_Text}m_euForamt;
	
public:
	void SetEnumFormatInt()
	{
		m_euForamt = FM_Integer;
	}

	void SetEnumFormatFloat()
	{
		m_strFormat = _T("%.3f");
		m_euForamt = FM_Float;
	}
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(NUMBEREDIT_H__)
