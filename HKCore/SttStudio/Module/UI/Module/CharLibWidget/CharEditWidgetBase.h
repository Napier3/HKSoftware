#ifndef CharEditWidgetBase_H
#define CharEditWidgetBase_H

#include <QWidget>
#include "../QExBaseListGridBase/QExBaseListGridBase.h"
#include "../QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "../../../../../Module/DataMngr/DataTypes.h"
#include "../../../../../Module/DataMngr/DataGroup.h"
#include "../../../../../Module/OSInterface/OSInterface.h"

class QCharEditGridBase : public QExBaseListGridBase
{
	Q_OBJECT
protected:
	CDataTypes m_oTestDataTypes;
	BOOL m_bRunning;

public:
	QCharEditGridBase(QWidget* pParent);
	virtual ~QCharEditGridBase();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void InitDataTypes();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual CDataType* FindTestDataType(const CString& strDataTypeID);
	virtual void EmitCharChanged();
	virtual CDataType* FindDataType(const CString &strDataType);

	static void EndEditCell_String(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_Double(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_Long(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);

signals:
	void sig_CharChanged(CExBaseObject *);
};

class QCharEditWidgetBase
{
public:
	QCharEditWidgetBase();
	virtual ~QCharEditWidgetBase();

	QWidget *m_pCharEditWidget;
	
public:
	void DeleteCharEditWidget();
	virtual void UpdateCharScriptByUIParas(CDataGroup *pCurrentUIParas);
	virtual void GroupDatasToChar(CDataGroup *pDatas){}//将模板视图数据赋值给特性曲线界面
	virtual void CharToGroupDatas(CDataGroup *pDatas){}//将特性曲线界面参数数据赋值给模板视图数据
//	virtual void AddTestPoint(CExBaseList* pValue) {} //增加固定点  20230311 zhouhj  增加固定点在QCharEditMainWidget中实现
	virtual void OnLeftButtonDown(){}
	virtual void UpdateCharacters(BOOL bCharChaged){}// 传递参数是否改变
};

#endif//!CharEditWidgetBase_H