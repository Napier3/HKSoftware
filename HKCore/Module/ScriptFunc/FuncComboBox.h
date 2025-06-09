#pragma once
#include "afxwin.h"
#include <list>

typedef struct FuncData{
	CString strname;
	CString strMsg;
	CString strFunc;
}*PFUNCDATA,FUNCDATA;

class CFuncComboBox :
	public CComboBox
{
public:
	CFuncComboBox(void);
	~CFuncComboBox(void);
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

public:


	typedef std::list<PFUNCDATA> LISTFUNC;

	LISTFUNC m_listFunc;
	CString GetSelectedstrFunc();
	CString GetSelectedstrMsg();
	PFUNCDATA GetSelectedData();

protected:
	virtual void PreSubclassWindow();
	void DeleteAll();

};
