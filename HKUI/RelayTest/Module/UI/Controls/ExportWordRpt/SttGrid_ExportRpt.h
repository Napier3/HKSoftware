#ifndef SttGrid_ExportRpt_H
#define SttGrid_ExportRpt_H

#include "../../Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../../../../Module/DataMngr/DataGroup.h"
#include "../../../../../Module/DataMngr/DataTypes.h"
#include "../../Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "../../../SttCmd/GuideBook/SttGuideBook.h"

#define _postfix_ID_TimesTerm     _T("_timesterm")   //固定后缀：过量欠量倍数条件
#define _postfix_ID_ErrRange      _T("_errrange")     //固定后缀：时间/动作值误差范围

#define _prefix_ID_Precision _T("rpt_precision_")   //固定前缀：保留小数位数配置
#define _prefix_ID_Tec       _T("rpt_tec_")         //固定前缀：技术要求

class QExBaseListComBoxDeleg_Edit : public QExBaseListComBoxDelegBase
{
public:
	//设置Data节点，代理会自动获取当前行和列，并设置值
	QExBaseListComBoxDeleg_Edit(QObject *parent=NULL);
	~QExBaseListComBoxDeleg_Edit();

	virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, 
		const QModelIndex &index ) const;
};
//////////////////////////////////////////////////////////////////////////
//
//导出word报告，对“报告中保留小数位数”进行配置和编辑
class CSttGrid_ExportRpt : public QExBaseListGridBase
{
public:
	CSttGrid_ExportRpt(QWidget* pparent);
	virtual ~CSttGrid_ExportRpt();

	CSttGuideBook *m_pGuideBook;
	CDataTypes m_oDataTypes;
	CExBaseList *m_pUiParas;

protected:
	QExBaseListComBoxDeleg_Edit *m_pDataDecimal;  //保留小数位数的下拉框

public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	void InitDataTypes();
	virtual CDataType* FindDataType(const CString &strDataType);
	virtual void  Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, const CString &strDataType, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc=NULL);
	virtual void  Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, CDataType *pDataType, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc=NULL);

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	void SetGuideBook(CSttGuideBook *pGuideBook);
	void SetItems(CExBaseObject *pItems);
	BOOL IsEnable(CExBaseObject *pData);
	void GetAllParas(CExBaseList *pList);
	void GetAllParasEx(CExBaseList *pParas, CDataGroup *pUIParas, CExBaseList *pRoot);

	static void EndEditCell_DataType_Val_Edit(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
};

BOOL IsDataItemsTec(CDvmData *pData);  //是否是技术要求

#endif // SttGrid_ExportRpt_H
