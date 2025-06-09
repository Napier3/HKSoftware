#ifndef SttGrid_ExportRpt_H
#define SttGrid_ExportRpt_H

#include "../../Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../../../Module/DataMngr/DataGroup.h"
#include "../../../../../Module/DataMngr/DataTypes.h"
#include "../../Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "../../../SttCmd/GuideBook/SttGuideBook.h"

#define _postfix_ID_TimesTerm     _T("_timesterm")   //�̶���׺������Ƿ����������
#define _postfix_ID_ErrRange      _T("_errrange")     //�̶���׺��ʱ��/����ֵ��Χ

#define _prefix_ID_Precision _T("rpt_precision_")   //�̶�ǰ׺������С��λ������
#define _prefix_ID_Tec       _T("rpt_tec_")         //�̶�ǰ׺������Ҫ��

class QExBaseListComBoxDeleg_Edit : public QExBaseListComBoxDelegBase
{
public:
	//����Data�ڵ㣬������Զ���ȡ��ǰ�к��У�������ֵ
	QExBaseListComBoxDeleg_Edit(QObject *parent=NULL);
	~QExBaseListComBoxDeleg_Edit();

	virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, 
		const QModelIndex &index ) const;
};
//////////////////////////////////////////////////////////////////////////
//
//����word���棬�ԡ������б���С��λ�����������úͱ༭
class CSttGrid_ExportRpt : public QExBaseListGridBase
{
public:
	CSttGrid_ExportRpt(QWidget* pparent);
	virtual ~CSttGrid_ExportRpt();

	CSttGuideBook *m_pGuideBook;
	CDataTypes m_oDataTypes;
	CExBaseList *m_pUiParas;

protected:
	QExBaseListComBoxDeleg_Edit *m_pDataDecimal;  //����С��λ����������

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

BOOL IsDataItemsTec(CDvmData *pData);  //�Ƿ��Ǽ���Ҫ��

#endif // SttGrid_ExportRpt_H
