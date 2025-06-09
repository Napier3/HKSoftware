#ifndef QGRIDDEFINE_H
#define QGRIDDEFINE_H

#include <QTableWidgetItem>


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
class QChMapsGridBase;

typedef void (GRID_CELL_EDIT_FUNC) (int, int, QGV_ITEM*, QChMapsGridBase*);


class QGV_ITEM : public QTableWidgetItem
{

public:
	QGV_ITEM(const QString &text);
	virtual ~QGV_ITEM();

	 unsigned long   lParam;      // 32-bit value to associate with item 
	GRID_CELL_EDIT_FUNC *m_pEditFunc; //edit function
private:
	
};

#endif // QGRIDDEFINE_H
