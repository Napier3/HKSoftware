#ifndef _xctrl_qt_h__
#define _xctrl_qt_h__

#include <qfile.h>
#include <QObject>
#include "CString_QT.h"
#ifndef _USE_NO_GUI_
#include <QComboBox>
#endif

#ifdef _PSX_QT_LINUX_
#define HTREEITEM   void*
#define TVI_ROOT                ((HTREEITEM)(unsigned long)-0x10000)
#define TVI_FIRST               ((HTREEITEM)(unsigned long)-0x0FFFF)
#define TVI_LAST                ((HTREEITEM)(unsigned long)-0x0FFFE)
#define TVI_SORT                ((HTREEITEM)(unsigned long)-0x0FFFD)

#define CB_ERR   -1

#else
#include "commctrl.h"
#endif

class CScrollBar
{
public:
    CScrollBar()
    {

    }

    virtual ~CScrollBar()
    {

    }
};

class CCmdUI
{
public:
    CCmdUI()
    {

    }

    virtual ~CCmdUI()
    {

    }
};

#ifdef _PSX_QT_LINUX_
typedef struct _NMHDR
{

}NMHDR, *PNMHDR;
#endif

class CTreeCtrl
{
public:
    CTreeCtrl()
    {

    }

    virtual ~CTreeCtrl()
    {
    }

    HTREEITEM InsertItem( CString lpszItem, int nImage, int nSelectedImage,
                          HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST)
    {
        hParent = 0;
        hInsertAfter=0;
        nImage=0;
        nSelectedImage = 0;
        return NULL;
    }
    bool SetItemData(HTREEITEM hItem, unsigned long dwData)
    {
        hItem = 0;
        dwData = 0;
        return 0;
    }
};

class CListCtrl
{
public:
    CListCtrl()
    {

    }
    virtual ~CListCtrl()
    {
    }

    inline BOOL SetItemText(int nItem, int nSubItem, const CString &lpszText)
    {
        CString str = lpszText;
        nItem = 0;
        nSubItem = 0;
        return FALSE;
    }
    inline BOOL SetItemData(int nItem, unsigned long dwItemData)
    {
        nItem = 0;
        dwItemData = 0;
        return FALSE;
    }

    inline void DeleteAllItems()
    {

    }

    inline bool DeleteColumn(int nCol)
    {
        nCol = 0;
        return 1;
    }

    inline int InsertItem(int nItem, CString &lpszItem)
    {
        nItem = 0;
        lpszItem.Empty();
        return 0;
    }

    inline int InsertItem(int nItem, CString lpszItem, int nImage)
    {
        nItem = 0;
        nImage = 0;
        return 0;
    }

    int InsertColumn(int nCol, const CString &lpszColumnHeading)
    {
        CString str = lpszColumnHeading;  //类似这样的代码，都是避免QT编译下，一大堆warning
        nCol = 0;
        return 0;
    }

    bool SetColumnWidth(int nCol, int cx)
    {
        nCol = 0;
        cx = 0;
        return 1;
    }

    unsigned long SetExtendedStyle(unsigned long dwNewStyle)
    {
        dwNewStyle = 0;
        return 0;
    }
};

#ifndef _USE_NO_GUI_
class CComboBox : public QComboBox
#else
class CComboBox
#endif
{
public:
    CComboBox()
    {

    }
    virtual ~CComboBox()
    {
    }

    inline int AddString(CString &lpszString)
    {
#ifndef _USE_NO_GUI_
        addItem(lpszString);
        return count()-1;
#else
        return 0;
#endif
    }

    inline int AddString(char *lpszString)
    {
#ifndef _USE_NO_GUI_
        addItem(lpszString);
        return count()-1;
#else
        return 0;
#endif
    }


    inline int DeleteString(UINT nIndex)
    {
#ifndef _USE_NO_GUI_
        removeItem(nIndex);
        return count()-1;
#else
        return 0;
#endif
    }

    inline int InsertString(int nIndex, CString &lpszString)
    {
#ifndef _USE_NO_GUI_
        insertItem(nIndex, lpszString);
        return count()-1;
#else
        return 0;
#endif
    }

    inline void ResetContent()
    {
#ifndef _USE_NO_GUI_
        clear();
#endif
    }

    inline void SetItemDataPtr(int nIndex, void* pData)
    {
#ifndef _USE_NO_GUI_
        QVariant var;
        long nValue = (long)(pData);
        var = (int)nValue;
        setItemData(nIndex, var);
#endif
    }

    inline void SetItemData(int nIndex, long nData)
    {
#ifndef _USE_NO_GUI_
        QVariant var;
        var = (int)nData;
        setItemData(nIndex, var);
#endif
    }

    inline unsigned long GetItemData(int nIndex)
    {
#ifndef _USE_NO_GUI_
        QVariant var = itemData(nIndex);
        return var.toUInt();
#else
        return 0;
#endif
    }

    inline void SetCurSel(int nIndex)
    {
#ifndef _USE_NO_GUI_
        setCurrentIndex(nIndex);
#endif
    }

    inline int GetCurSel()
    {
#ifndef _USE_NO_GUI_
        return currentIndex();
#else
        return 0;
#endif
    }
};


class CListBox
{
public:
    CListBox()
    {

    }
    virtual ~CListBox()
    {
    }

    inline int AddString(CString &lpszString)
    {
        lpszString.Empty();
        return 0;
    }

    inline int DeleteString(UINT nIndex)
    {
        nIndex=0;
        return 0;
    }

    inline int InsertString(int nIndex, CString &lpszString)
    {
        nIndex=0;
        lpszString.Empty();
        return 0;
    }

    inline void ResetContent()
    {

    }

    inline void SetItemDataPtr(int nIndex, void* pData)
    {
        nIndex=0;
        pData=0;
    }
};

void Stt_Global_SetComboBoxIndexByText(CComboBox *pCombox, CString strText); //2024.10.16 zhangyq 获取文本对应的combox下拉框，设置item

#endif   //_xctrl_qt_h__
