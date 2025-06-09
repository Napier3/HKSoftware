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
	//CDvmValue* GetDataValue(CDvmData *pData) const;  //�ƶ���CDvmData��, shaolei 2023-7-28

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

	CDvmDataset *m_pDataset;  //�豸����ģ��

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
};


//�ñ��������ʾ��writeָ����������ݼ�������
class CSttCmdWzdDsEditGrid : public CSttCmdWzdDsShowGrid
{
	Q_OBJECT
public:
	CSttCmdWzdDsEditGrid(QWidget* pparent);
	virtual ~CSttCmdWzdDsEditGrid();

	CDataGroup* m_pDataGroupBK;

public:
	CValues *m_pValues;  //ͨѶ����Я���Ĳ���
	UINT m_nTypeRwOptr;
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData_Read(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void ShowData_Write(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	void ShowData_CmdValue_String(CDvmData *pData, int& nRow);
	void ShowData_CmdValue_BOOL(CDvmData *pData, int& nRow);
	void ShowData_CmdValue_Hex(CDvmData *pData, int& nRow);
	virtual void ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars=TRUE);
	
	//����Ǳ༭m_pDvmDevice�Ļص�����
	static void EndEditCell_CmdDataValue(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_CmdDataValue_BOOL(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_CmdDataValue_Hex(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

	//����Ǳ༭m_pValues�Ļص�����
	static void EndEditCell_CmdDataValue_CmdValue(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_CmdDataValue_CmdValue_BOOL(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_CmdDataValue_CmdValue_Hex(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

	//�����ڳ�ʼ������Ŀʱ�Ļص�����
	static void EndEditCell_Init_String(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_Init_BOOL(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_Init_Hex(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

	//CDvmValue* GetDataValue(CDvmData *pData);  //�ƶ���CDvmData��  2023-7-28 shaolei
	void InitTypeRwOptr(const CString &strRwOptr);
	CValue* AddDataToSttCommCmd(CDvmData *pData);
	//QSttCmdWzdDsEditGrid_CheckBoxDelegate *m_pValue_Bool;
	void FillCmdValues();

signals:
	void sig_CmdWzd_UpdateData(CDvmData *pDvmData);
	void sig_CmdWzd_UpdateData_Value(CValue *pValue);
};

//////////////////////////////////////////////////////////////////////////////
//�ñ������registerָ���ʾָ�����ʹ��
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
