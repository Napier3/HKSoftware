#pragma once
// CCharElmentBaseDlg
#include "..\Module\Characteristic\CharElement.h"

class CCharElmentBaseDlg : public CExBaseObject
{
public:
	CCharElmentBaseDlg();
	virtual ~CCharElmentBaseDlg();

	CDialog *m_pDialog;
	CCharElement *m_pCharElementBase;

	virtual void CreateDlg(CWnd *pParent)=0 ; //建立对话框
	virtual void GetData()=0; //获取数据
	virtual void ShowData()=0;  //显示数据	
	virtual BOOL IsEnable()=0;  //数据是否有效，若是无效数据，则不保存数据

	virtual void Hide(); //隐藏对话框
	virtual void SetWindowPos(const CRect &rcWnd); //获取对话框位置
	virtual void ShowCharElement(CCharElement *pObj);

};


class CCharElementMngrDlg : public CTLinkListEx<CCharElmentBaseDlg>
{
public:
	CCharElementMngrDlg();
	virtual ~CCharElementMngrDlg();
};

