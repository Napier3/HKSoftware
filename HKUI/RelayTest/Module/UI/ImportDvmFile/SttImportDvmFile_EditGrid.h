#ifndef SttImportDvmFile_EditGrid_H
#define SttImportDvmFile_EditGrid_H

#include "../Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "../../../../Module/DataMngr/Values.h"
#include "../../../../Module/DataMngr/DvmData.h"
#include "../../SttCmd/GuideBook/SttCommCmd.h"

class QSttImportDvmFile_EditGrid_CheckBoxDelegate : public QExBaseListCheckBoxDelegate
{
public:
	QSttImportDvmFile_EditGrid_CheckBoxDelegate(QObject *parent=NULL);
	~QSttImportDvmFile_EditGrid_CheckBoxDelegate();

public:

private:
	virtual void paint(QPainter * painter, const QStyleOptionViewItem & option,
		const QModelIndex & index) const;

	QPixmap m_oEmptyPixmap;
};

//该表格，是针对批量通讯命令的
//不同的数据集下，压板的ID不会重复。定值的ID不会重复
class CSttImportDvmFile_EditGrid : public QExBaseListGridBase
{
	Q_OBJECT
public:
	CSttImportDvmFile_EditGrid(QWidget* pparent);
	virtual ~CSttImportDvmFile_EditGrid();

public:
	CValues *m_pValues;  //通讯命令携带的参数。记录的是通讯命令中已有的参数
	CExBaseList *m_pDatasEdit;  //编辑过的参数，放到临时链表
	CExBaseList *m_pDatasList;  //显示的数据列表，从不同的数据集整合过来
	void ClearCmdsValues();  //清空m_pValues
	void InitCmdsValues(CSttCommCmd *pCommCmd);  //初始化m_pValues；
	void AddDataToEditList(CDvmData *pData);     //将编辑过的参数，添加到编辑链表m_pDatasEdit
	void ClearEditList();  //清空m_pDatasEdit
	void InitDatasList(const CString &strDsKey);
	void InitDatasList(CStringArray &oDsKeyArray);
	void ClearEmptyDatas();
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	void ShowData_CmdValue_String(CDvmData *pData, int& nRow);
	void ShowData_CmdValue_BOOL(CDvmData *pData, int& nRow);
	void ShowData_CmdValue_Hex(CDvmData *pData, int& nRow);
	virtual void ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars=TRUE);
	void ShowDatas();

	static void EndEditCell_CmdDataValue(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_CmdDataValue_BOOL(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_CmdDataValue_Hex(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);


signals:
};

#endif //SttImportDvmFile_EditGrid_H