#ifndef SttGrid_ExportRpt_Tec_H
#define SttGrid_ExportRpt_Tec_H

#include "SttGrid_ExportRpt.h"

//导出word报告，对“技术要求”进行配置和编辑
class CSttGrid_ExportRpt_Tec : public CSttGrid_ExportRpt
{
public:
	CSttGrid_ExportRpt_Tec(QWidget* pparent);
	virtual ~CSttGrid_ExportRpt_Tec();

protected:
	QExBaseListComBoxDeleg_Edit *m_pDataTimesTerm; //过量欠量倍数条件
	QExBaseListComBoxDeleg_Edit *m_pDataErrorRange; //动作时间/动作值误差范围

public:
	void InitDataTypes(CDataTypes *pDataTypes);
	CDataTypes* InitDataTypes(CDataGroup *pItemTec);
	void InitDataTypes(CDvmValue *pValue);
public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual CDataType* FindDataType(const CString &strDataType);
	virtual void  Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, const CString &strDataType, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc=NULL);
	virtual void  Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, CDataType *pDataType, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc=NULL);

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	static void EndEditCell_DataType_Val_Edit(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
};

#endif // SttGrid_ExportRpt_Tec_H
