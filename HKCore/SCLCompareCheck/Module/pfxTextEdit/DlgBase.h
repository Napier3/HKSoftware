#pragma once

/////////////////////////////////////////////////////////////////////////////
// CDlgBase 对话框
class CDlgBase : public CDialog
{
        DECLARE_DYNCREATE(CDlgBase)
        // Construction
public:
        CDlgBase(UINT nIDTemplate = 0, CWnd* pParent = NULL);
        virtual        ~CDlgBase();
        
        // 如果用户击中标题栏上的“帮助”按钮，显示弹出式帮助，否则调动帮助系
        // 统显示具体主题。
        BOOL           m_bHitHelp;

public:
        BOOL           DlgIsItemChecked(int nIDItem);
        BOOL           DlgIsItemEnabled(int nIDItem);
        BOOL           DlgIsItemVisible(int nIDItem);

        void           DlgShowItem(int nIDItem, BOOL bShow);
        void           DlgCheckItem(int nIDItem, BOOL bCheck);
        void           DlgEnableItem(int nIDItem, BOOL bEnable);

        BOOL           DlgGetItemINT(int nIDItem, UINT nIDErrMsgFormat, INT& iRetVal, INT iMinVal, INT iMaxVal);
        BOOL           DlgGetItemUINT(int nIDItem, UINT nIDErrMsgFormat, UINT& uRetVal, UINT uMinVal, UINT uMaxVal);
        BOOL           DlgGetItemFLOAT(int nIDItem, UINT nIDErrMsgFormat, FLOAT& fRetVal, FLOAT fMinVal, FLOAT fMaxVal);

        LRESULT        DlgSimulateItemCmdMessage(int nIDItem, WORD wMsg);
        LRESULT        DlgSimulateItemNotifyMessage(int nIDItem, WORD wMsg);

public:
        static BOOL    DlgIsItemChecked(CWnd* pOwner, int nIDItem);
        static BOOL    DlgIsItemEnabled(CWnd* pOwner, int nIDItem);
        static BOOL    DlgIsItemVisible(CWnd* pOwner, int nIDItem);

        static void    DlgShowItem(CWnd* pOwner, int nIDItem, BOOL bShow);
        static void    DlgCheckItem(CWnd* pOwner, int nIDItem, BOOL bCheck);
        static void    DlgEnableItem(CWnd* pOwner, int nIDItem, BOOL bEnable);

        static BOOL    DlgGetItemINT(CWnd* pOwner, int nIDItem, UINT nIDErrMsgFormat, INT& iRetVal, INT iMinVal, INT iMaxVal);
        static BOOL    DlgGetItemUINT(CWnd* pOwner, int nIDItem, UINT nIDErrMsgFormat, UINT& uRetVal, UINT uMinVal, UINT uMaxVal);
        static BOOL    DlgGetItemFLOAT(CWnd* pOwner, int nIDItem, UINT nIDErrMsgFormat, FLOAT& fRetVal, FLOAT fMinVal, FLOAT fMaxVal);

        static LRESULT DlgSimulateItemCmdMessage(CWnd* pOwner, int nIDItem, WORD wMsg);
        static LRESULT DlgSimulateItemNotifyMessage(CWnd* pOwner, int nIDItem, WORD wMsg);
        
protected:
        afx_msg BOOL   OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void   OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void   OnNcLButtonDown(UINT nHitTest, CPoint point);
        DECLARE_MESSAGE_MAP()
};

inline BOOL            CDlgBase::DlgIsItemChecked(int nIDItem)
{ return DlgIsItemChecked(this, nIDItem); }
inline BOOL            CDlgBase::DlgIsItemEnabled(int nIDItem)
{ return DlgIsItemEnabled(this, nIDItem); }
inline BOOL            CDlgBase::DlgIsItemVisible(int nIDItem)
{ return DlgIsItemVisible(this, nIDItem); }
inline void            CDlgBase::DlgCheckItem(int nIDItem, BOOL bCheck)
{ DlgCheckItem(this, nIDItem, bCheck); }
inline void            CDlgBase::DlgEnableItem(int nIDItem, BOOL bEnable)
{ DlgEnableItem(this, nIDItem, bEnable); }
inline void            CDlgBase::DlgShowItem(int nIDItem, BOOL bShow)
{ DlgShowItem(this, nIDItem, bShow); }

inline BOOL            CDlgBase::DlgGetItemINT(int nIDItem, UINT nIDErrMsgFormat, INT& iRetVal, INT iMinVal, INT iMaxVal)
{ return DlgGetItemINT(this, nIDItem, nIDErrMsgFormat, iRetVal, iMinVal, iMaxVal); }
inline BOOL            CDlgBase::DlgGetItemUINT(int nIDItem, UINT nIDErrMsgFormat, UINT& uRetVal, UINT uMinVal, UINT uMaxVal)
{ return DlgGetItemUINT(this, nIDItem, nIDErrMsgFormat, uRetVal, uMinVal, uMaxVal); }
inline BOOL            CDlgBase::DlgGetItemFLOAT(int nIDItem, UINT nIDErrMsgFormat, FLOAT& fRetVal, FLOAT fMinVal, FLOAT fMaxVal)
{ return DlgGetItemFLOAT(this, nIDItem, nIDErrMsgFormat, fRetVal, fMinVal, fMaxVal); }

inline LRESULT         CDlgBase::DlgSimulateItemCmdMessage(int nIDItem, WORD wMsg)
{ return DlgSimulateItemCmdMessage(this, nIDItem, wMsg); }
inline LRESULT         CDlgBase::DlgSimulateItemNotifyMessage(int nIDItem, WORD wMsg)
{ return DlgSimulateItemNotifyMessage(nIDItem, wMsg); }
