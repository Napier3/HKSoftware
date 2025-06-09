#pragma once
#include "DlgBase.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgFind dialog

class CDlgFind : public CDlgBase
{
        // Construction
public:
        CDlgFind(CWnd* pParent = NULL);   // standard constructor
        
        // Dialog Data
        enum { IDD = IDD_SEARCH_FIND };
        CComboBox      m_cbxFindWhat;
        CString        m_strFindWhat;
        
        BOOL           m_bMatchCase;
        BOOL           m_bMatchWholeWord;
        BOOL           m_bDirectDown;
        
protected:
        BOOL           DoUpdateInfo(BOOL bSaveAndValidate);

// Overrides
protected:
        virtual void   DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        virtual BOOL   OnInitDialog();
        virtual void   OnOK();
        virtual void   OnCancel();
        
        // Implementation
protected:
        afx_msg void   OnFind();
        afx_msg void   OnMarkAll();
        afx_msg void   OnCbxEdtChangeFindWhat();
        afx_msg void   OnCbxSelChangeFindWhat();
        DECLARE_MESSAGE_MAP()
};
