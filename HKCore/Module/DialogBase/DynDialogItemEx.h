// DynDialogItemEx.h: interface for the CDynDialogItemEx class. 
// 
////////////////////////////////////////////////////////////////////// 

#if !defined(_DYNDIALOGITEMEX_H__) 
#define _DYNDIALOGITEMEX_H__ 

#if _MSC_VER > 1000 
#pragma once 
#endif // _MSC_VER > 1000 

typedef enum 
{ 
	NOCONTROL		= 0, 
	BUTTON			= 0x0080, 
	EDITCONTROL		= 0x0081, 
	STATICTEXT		= 0x0082, 
	LISTBOX			= 0x0083, 
	HSCROLL			= 0x0084, 
	COMBOBOX			= 0x0085, 
	SPIN, 
	PROGRES, 
	SLIDER, 
	HOTKEY, 
	LISTCTRL, 
	TREECTRL, 
	TABCTRL, 
	ANIMATE, 
	RICHEDIT, 
	DATETIMEPICKER, 
	MONTHCALENDER, 
	IPADRESS, 
	COMBOBOXEX 
} DLGITEMTEMPLATECONTROLS; 

class CDynDialogItemEx : public CWnd 
{ 
public: 
	// Construction 
	CDynDialogItemEx(); 
	// Operations 
public: 
	UINT InitDialogItem(DLGITEMTEMPLATECONTROLS TypeControl, 
		DWORD dwStyle, 
		DWORD dwExtendedStyle, 
		LPRECT pRect, 
		const CString & lpszCaption,  
		UINT nID = 0, 
		BOOL bSubclassed = FALSE, 
		void	*pData = NULL); 
	UINT InitDialogItem(const CString & lpszClassName, 
		DWORD dwStyle, 
		DWORD dwExtendedStyle, 
		LPRECT pRect, 
		const CString & lpszCaption,  
		UINT nID = 0, 
		BOOL bSubclassed = FALSE, 
		void	*pData = NULL); 
	BOOL CreateEx(CWnd *pParent); 
	void SetFont(CFont* pFont, BOOL bRedraw = TRUE); 

	// Operations 
public: 
	virtual void DoDataExchange(CDataExchange* pDX); 

	// Overrides 
	// ClassWizard generated virtual function overrides 
	//{{AFX_VIRTUAL(CDynDialogItemEx) 
	//}}AFX_VIRTUAL 

	// Implementation 
public: 
	//virtual ~CDynDialogItemEx(); 
	BOOL SetWindowPos(CWnd *pParent); 
	PBYTE FillBufferWithItemTemplate(BYTE* pdest); 

	UINT GetControlID()								{return m_ControlID;} 
	DLGITEMTEMPLATECONTROLS GetControlType()	{return m_eTypeControl;} 
	long GetCaptionLength()							{return m_strCaption.GetLength();} 
	BOOL IsDlgItemSubclassed()						{return m_bSubclassed;} 
	CString GetClassName()							{return m_strClassName;}		 

protected: 
	DLGITEMTEMPLATECONTROLS GetClassTypeByName(const CString & lpszClassName); 

	CString						m_strClassName; 
	DLGITEMTEMPLATECONTROLS	m_eTypeControl; 
	UINT							m_ControlID; 
	UINT							m_dwStyle; 
	UINT							m_dwStyleEx; 
	CRect							m_Rect; 
	CString						m_strCaption; 
	void							*m_pData; 
	BOOL							m_bSubclassed; 

	// Generated message map functions 
protected: 
	BOOL IsDataMemberPointerToWnd(); 
	BSTR GetRuntimeLicense(CString &strControlName); 
	TCHAR* GetClassNameByType(DLGITEMTEMPLATECONTROLS TypeControl); 

	//{{AFX_MSG(CDynDialogItemEx) 
	// NOTE - the ClassWizard will add and remove member functions here. 
	//}}AFX_MSG 
	DECLARE_MESSAGE_MAP() 
}; 

#endif // !defined(_DYNDIALOGITEMEX_H__) 
