#pragma once

#include "SclTextCCView.h"
#include "DlgBase.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgReplace dialog
class CDlgReplace : public CDlgBase
{
        // Construction
public:
        CDlgReplace(CWnd* pParent = NULL);   // standard constructor

        // Dialog Data
        enum { IDD = IDD_SEARCH_REPLACE };
        CComboBox      m_cbxFindWhat;
        CComboBox      m_cbxReplaceWith;

        CString        m_strFindWhat;
        CString        m_strReplaceWith;

        BOOL           m_bMatchCase;
        BOOL           m_bMatchWholeWord;
        BOOL           m_bInSelection;

protected:
        BOOL           DoUpdateInfo(BOOL bSaveAndValidate);
        BOOL           DoFind();
        BOOL           IsFindTargetMatchCurrentSelection(CSclTextCCView* pView);

protected:
        virtual void   DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        virtual BOOL   OnInitDialog();
        virtual void   OnOK();
        virtual void   OnCancel();

protected:
        DECLARE_MESSAGE_MAP()
        afx_msg void   OnFind();
        afx_msg void   OnReplace();
        afx_msg void   OnReplaceAll();
        afx_msg void   OnCbxEdtChangeFindWhat();
        afx_msg void   OnCbxSelChangeFindWhat();
        afx_msg void   OnRdoClickedReplaceRange();
};
