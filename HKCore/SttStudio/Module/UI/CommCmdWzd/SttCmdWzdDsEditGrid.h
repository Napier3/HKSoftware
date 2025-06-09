#ifndef SttCmdWzdDsEditGrid_H
#define SttCmdWzdDsEditGrid_H

#include "../Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../../Module/DataMngr/DvmDataset.h"
#include "../../../../Module/DataMngr/Value.h"
#include "../Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "../../../../Module/DataMngr/Values.h"
#include "../../../../Module/DataMngr/DataGroup.h"

class QSttCmdWzdDsEditGrid_CheckBoxDelegate : public QExBaseListCheckBoxDelegate
{
public:
	QSttCmdWzdDsEditGrid_CheckBoxDelegate(QObject *parent=NULL);
	~QSttCmdWzdDsEditGrid_CheckBoxDelegate();

public:
	//CDvmValue* GetDataValue(CDvmData *pData) const;  //移动到CDvmData类, shaolei 2023-7-28

private:
	virtual void paint(QPainter * painter, const QStyleOptionViewItem & option,
		const QModelIndex & index) const;

	QPixmap m_oEmptyPixmap;
};
//////////////////////////////////////////////////////////////////////////
//
class CSttCmdWzdDsShowGrid : public QExBaseListGridBase
{
public:
	CSttCmdWzdDsShowGrid(QWidget* pparent);
	virtual ~CSttCmdWzdDsShowGrid();

	CDvmDataset *m_pDataset;  //设备数据模型

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
};


//该表格用于显示，write指令，关联的数据集的数据
class CSttCmdWzdDsEditGrid : public CSttCmdWzdDsShowGrid
{
	Q_OBJECT
public:
	CSttCmdWzdDsEditGrid(QWidget* pparent);
	virtual ~CSttCmdWzdDsEditGrid();

	CDataGroup* m_pDataGroupBK;

public:
	CValues *m_pValues;  //通讯命令携带的参数
	UINT m_nTypeRwOptr;
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData_Read(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void ShowData_Write(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	void ShowData_CmdValue_String(CDvmData *pData, int& nRow);
	void ShowData_CmdValue_BOOL(CDvmData *pData, int& nRow);
	void ShowData_CmdValue_Hex(CDvmData *pData, int& nRow);
	virtual void ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars=TRUE);
	
	//这边是编辑m_pDvmDevice的回调函数
	static void EndEditCell_CmdDataValue(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_CmdDataValue_BOOL(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_CmdDataValue_Hex(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

	//这边是编辑m_pValues的回调函数
	static void EndEditCell_CmdDataValue_CmdValue(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_CmdDataValue_CmdValue_BOOL(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_CmdDataValue_CmdValue_Hex(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

	//是向导在初始创建项目时的回调函数
	static void EndEditCell_Init_String(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_Init_BOOL(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_Init_Hex(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

	//CDvmValue* GetDataValue(CDvmData *pData);  //移动到CDvmData类  2023-7-28 shaolei
	void InitTypeRwOptr(const CString &strRwOptr);
	CValue* AddDataToSttCommCmd(CDvmData *pData);
	//QSttCmdWzdDsEditGrid_CheckBoxDelegate *m_pValue_Bool;
	void FillCmdValues();

signals:
	void sig_CmdWzd_UpdateData(CDvmData *pDvmData);
	void sig_CmdWzd_UpdateData_Value(CValue *pValue);
};

//////////////////////////////////////////////////////////////////////////////
//该表格用于register指令，显示指令参数使用
class CSttCmdWzdDsEditGrid_Register : public QExBaseListGridBase
{
	Q_OBJECT
public:
	CSttCmdWzdDsEditGrid_Register(QWidget* pparent);
	virtual ~CSttCmdWzdDsEditGrid_Register();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

public:
	CString GetValueName(CValue* pValue);
	BOOL IsValue_Bool(CValue *pValue);

	static void EndEditCell_CmdDataValue(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_CmdDataValue_BOOL(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

signals:
	void sig_CmdWzd_UpdateData_Value(CValue *pValue);
};

#endif // SttCmdWzdGrid_Read_H
