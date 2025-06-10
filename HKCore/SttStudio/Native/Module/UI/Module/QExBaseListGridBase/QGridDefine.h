#ifndef QGRIDDEFINE_H
#define QGRIDDEFINE_H

#include <QTableWidgetItem>
#include "../CommonCtrl_QT/CommonCtrlInterface.h"

#define VCD_LONG				0
#define VCD_DOUBLE			    1
#define VCD_STRING		    	2
#define VCD_DWORD		    	3
#define VCD_FLOAT				4
#define VCD_STRCMPBLKS	        5
#define VCD_WSTRING			    6
#define VCD_SYSTEMTIME	        7
#define VCD_INT  				8

// Edit Types
#define QT_GVET_NOEDIT             0x00000000	// Edit Not Allowed
#define QT_GVET_EDITBOX            0x00010000	// InPlace EditBox
#define QT_GVET_LISTBOX            0x00020000	// InPlace ListBox
#define QT_GVET_COMBOBOX           0x00040000	// InPlace ComboBox
#define QT_GVET_COMBOBOXDROPLIST   0x00080000	// InPlace ComboBox
#define QT_GVET_CHECKBOX           0x00100000	// InPlace CheckBox
#define QT_GVET_TREECTRL           0x00200000
#define QT_GVET_DATECTRL           0x00400000
#define QT_GVET_COLOR				0x00800000  //颜色 
#define QT_GVET_COMBO_CHECKBOX		0x01000000  
#define QT_GVET_HEXEDIT			0x02000000  
#define QT_GVET_MACEDIT			0x04000000  
#define QT_GVET_BINARYEDIT			0x08000000  //zhouhj 20201208增加用于二进制显示，如61850数据对象中的品质位



class QGV_ITEM;
class QExBaseListGridBase;

typedef void (GRID_CELL_EDIT_FUNC) (int, int, QGV_ITEM*, QExBaseListGridBase*);


class QGV_ITEM : public QTableWidgetItem,public CCommonCtrlInterface
{

public:
	QGV_ITEM(const QString &text);
	virtual ~QGV_ITEM();

	virtual void UpdateText(const QString &strText);

	 unsigned long   lParam;      // 32-bit value to associate with item 
	 unsigned long   nDataType;   //data type
	 unsigned long    dwValue;     //value ref
	 int      iMaxLen;     //数据的最大长度 用于Hex 0x4000代表长度为2 即字节长度
	GRID_CELL_EDIT_FUNC *m_pEditFunc; //edit function
private:
	
};


#endif // QGRIDDEFINE_H
