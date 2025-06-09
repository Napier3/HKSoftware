#pragma once
//#include "..\..\Pmc2000\Pmc2000\resource.h"
//#include "..\..\Pmc2000\Pmc2000\PMC2000ClassDefine.h"
// CDialogPage �Ի���

class CDialogPage : public CDialog
{
	DECLARE_DYNAMIC(CDialogPage)

public:
	CDialogPage(UINT nIDD, const CString &strCaption, CSize sz, CWnd *pParent);   // ��׼���캯��
	virtual ~CDialogPage();

	friend class CDialogSheet;
 
public:
	CString m_strCaption;
	UINT m_nIDD;
	CSize m_szPage;

private:
	DWORD m_dwItemData;		//����������

public:
	virtual void OnKillActive();
	virtual void OnSetActive();
	virtual void CreatePage(CWnd *pParent);
	virtual void SetItemData(DWORD dwItemData)	{	m_dwItemData = dwItemData;	}
	virtual DWORD GetItemData()					{	return m_dwItemData;		}
	virtual void OnOK()	{}
	virtual void OnCancel()	{}
};
