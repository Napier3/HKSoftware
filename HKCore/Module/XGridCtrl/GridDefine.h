// GridDefine.h
//
//////////////////////////////////////////////////////////////////////

#if !defined(_GRID_DEFINE_H__)
#define _GRID_DEFINE_H__

#include <afxtempl.h>
#include <afxole.h>                     // This is sloppy I know...
#include "..\StringCmp\StringCmpBlocks.h"


#define SELECTED_CELL_FONT_WEIGHT 600    // wieght of text for selected items

// Use this as the classname when inserting this control as a custom control
// in the MSVC++ dialog editor
#define GRIDCTRL_CLASSNAME _T("MFCXGridCtrlBase")

#define IsSHIFTpressed() ( (GetKeyState(VK_SHIFT) & (1 << (sizeof(SHORT)*8-1))) != 0   )
#define IsCTRLpressed()  ( (GetKeyState(VK_CONTROL) & (1 << (sizeof(SHORT)*8-1))) != 0 )

class CGridCell;
class CXGridCtrlBase;

typedef void (GRID_CELL_EDIT_FUNC) (int, int, CGridCell*, CXGridCtrlBase*);

// Used for Get/SetItem calls.
typedef struct _GV_ITEM { 
    int      row,col;     // Row and Column of item
    UINT     mask;        // Mask for use in getting/setting cell data
    UINT     state;       // cell state (focus/hilighted etc)
    UINT     nFormat;     // Format of cell
    CString  szText;      // Text in cell
	CStringCmpBlocks *pStrCmpBlocks;
    int      iImage;      // index of the list view item抯 icon
    COLORREF crBkClr;     // Background colour (or CLR_DEFAULT)
    COLORREF crFgClr;     // Forground colour (or CLR_DEFAULT)
    LPARAM   lParam;      // 32-bit value to associate with item 
    LOGFONT  lfFont;      // Cell font
	BOOL     bReadOnly;   //只读属性
	DWORD    nDataType;   //data type
	DWORD    dwValue;     //value ref
	int      iMaxLen;     //数据的最大长度
	GRID_CELL_EDIT_FUNC *pEditFunc; //edit function
} GV_ITEM; 

// Grid line selection
#define GVL_NONE                0
#define GVL_HORZ                1
#define GVL_VERT                2
#define GVL_BOTH                3

// Cell data mask
#define GVIF_TEXT               0x0001
#define GVIF_IMAGE              0x0002
#define GVIF_PARAM              0x0004
#define GVIF_STATE              0x0008
#define GVIF_BKCLR              0x0010
#define GVIF_FGCLR              0x0020
#define GVIF_FORMAT             0x0040
#define GVIF_FONT               0x0080
#define GVIF_DATATYPE           0x0100
#define GVIF_VALUE              0x0200
#define GVIF_FUNC               0x0400
#define GVIF_MAXLEN             0x0800
#define GVIF_STRBLOCKS          0x1000

// Cell states
#define GVIS_FOCUSED            0x0001
#define GVIS_SELECTED           0x0002
#define GVIS_DROPHILITED        0x0004
#define GVIS_READONLY           0x0008
#define GVIS_STATIC             0x0010

// Cell Searching options
#define GVNI_FOCUSED            0x0001
#define GVNI_SELECTED           0x0002
#define GVNI_DROPHILITED        0x0004
#define GVNI_READONLY           0x0008

#define GVNI_ABOVE              LVNI_ABOVE
#define GVNI_BELOW              LVNI_BELOW
#define GVNI_TOLEFT             LVNI_TOLEFT
#define GVNI_TORIGHT            LVNI_TORIGHT
#define GVNI_ALL                (LVNI_BELOW|LVNI_TORIGHT)

// Hit test values (not yet implemented)
#define GVHT_DATA               0x0000
#define GVHT_TOPLEFT            0x0001
#define GVHT_COLHDR             0x0002
#define GVHT_ROWHDR             0x0004
#define GVHT_COLSIZER           0x0008
#define GVHT_ROWSIZER           0x0010
#define GVHT_LEFT               0x0020
#define GVHT_RIGHT              0x0040
#define GVHT_ABOVE              0x0080
#define GVHT_BELOW              0x0100

// Edit Types
#define GVET_NOEDIT             0x00000000	// Edit Not Allowed
#define GVET_EDITBOX            0x00010000	// InPlace EditBox
#define GVET_LISTBOX            0x00020000	// InPlace ListBox
#define GVET_COMBOBOX           0x00040000	// InPlace ComboBox
#define GVET_COMBOBOXDROPLIST   0x00080000	// InPlace ComboBox
#define GVET_CHECKBOX           0x00100000	// InPlace CheckBox
#define GVET_TREECTRL           0x00200000
#define GVET_DATECTRL           0x00400000
#define GVET_COLOR				0x00800000  //颜色 
#define GVET_COMBO_CHECKBOX		0x01000000  
#define GVET_HEXEDIT			0x02000000  
#define GVET_MACEDIT			0x04000000  

inline BOOL GVET_IsEditBox(UINT nDataType)
{
	return ( (nDataType & GVET_EDITBOX) == GVET_EDITBOX);
}

inline BOOL GVET_IsListBox(UINT nDataType)
{
	return ( (nDataType & GVET_LISTBOX) == GVET_LISTBOX);
}

inline BOOL GVET_IsComboBox(UINT nDataType)
{
	return ( (nDataType & GVET_COMBOBOX) == GVET_COMBOBOX);
}

inline BOOL GVET_IsComboDropListBox(UINT nDataType)
{
	return ( (nDataType & GVET_COMBOBOXDROPLIST) == GVET_COMBOBOXDROPLIST);
}

inline BOOL GVET_IsCheckBox(UINT nDataType)
{
	return ( (nDataType & GVET_CHECKBOX) == GVET_CHECKBOX);
}

inline DWORD GVET_CreateDataTyp(DWORD dwGvet, unsigned short nDataType)
{
	return dwGvet + nDataType;
}

inline void InitGirdItem(GV_ITEM& Item, long nDataType = GVET_NOEDIT, long nState=GVIS_READONLY, long nmask=GVIF_FORMAT|GVIF_TEXT | GVIF_FGCLR|GVIF_BKCLR | GVIF_DATATYPE ,long nFormat=DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS)
{
	Item.state  = nState;
	Item.mask=nmask;	
	Item.nFormat = nFormat;
	Item.nDataType = nDataType;
	Item.pStrCmpBlocks = NULL;
	Item.pEditFunc = NULL;
}

///////////////////////////////////////////////////////////////////////


typedef struct tagNM_GRIDVIEW { 
    NMHDR hdr; 
    int   iRow; 
    int   iColumn; 
} NM_GRIDVIEW;

typedef struct tagGV_DISPINFO { 
    NMHDR   hdr; 
    GV_ITEM item; 
	DWORD   dwItemData;
} GV_DISPINFO;

//2002.01.12 0:38
typedef struct tagRB_MOUSEPOS {
	int iActCellRow;	//活动Cell的行列位置
	int iActCellCol;
	int iMouseCol;		//鼠标所在的Cell的位置
	int iMouseRow;
	CPoint ptMousePos;	//鼠标的在网格的位置
	unsigned long	ulHWnd;
} RB_MOUSEPOS;
// Messages sent to the grid's parent (More will be added in future)
#define	GVN_BEGINDRAG           LVN_BEGINDRAG        // LVN_FIRST-9
#define	GVN_BEGINLABELEDIT      LVN_BEGINLABELEDIT   // LVN_FIRST-5
#define	GVN_BEGINRDRAG          LVN_BEGINRDRAG
#define GVN_COLUMNCLICK         LVN_COLUMNCLICK
#define	GVN_DELETEITEM          LVN_DELETEITEM
#define GVN_ENDLABELEDIT        LVN_ENDLABELEDIT     // LVN_FIRST-6
#define GVN_SELCHANGING         LVN_BEGINLABELEDIT+1 // LVN_FIRST-4
#define GVN_SELCHANGED          LVN_BEGINLABELEDIT+2 // LVN_FIRST-3
#define GVN_ENDPOINTEDIT        LVN_ENDLABELEDIT+12    // LVN_FIRST-6
#define GVN_ENDCOMBOBOXEDIT     LVN_ENDLABELEDIT+13    // LVN_FIRST-6
#define GVN_GRIDDBCLICK         LVN_ENDLABELEDIT+14    // LVN_FIRST-6
#define GVN_GRIDDBCLICKR        LVN_ENDLABELEDIT+15    // LVN_FIRST-6


enum GRIDEDIT_FORMAT{GEFM_NONE, GEFM_Float, GEFM_Integer, GEFM_Password, GEFM_String, GEFM_Text};

#endif // !defined(_GRID_DEFINE_H__)
