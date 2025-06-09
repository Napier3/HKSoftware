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

//�ñ�����������ͨѶ�����
//��ͬ�����ݼ��£�ѹ���ID�����ظ�����ֵ��ID�����ظ�
class CSttImportDvmFile_EditGrid : public QExBaseListGridBase
{
	Q_OBJECT
public:
	CSttImportDvmFile_EditGrid(QWidget* pparent);
	virtual ~CSttImportDvmFile_EditGrid();

public:
	CValues *m_pValues;  //ͨѶ����Я���Ĳ�������¼����ͨѶ���������еĲ���
	CExBaseList *m_pDatasEdit;  //�༭���Ĳ������ŵ���ʱ����
	CExBaseList *m_pDatasList;  //��ʾ�������б��Ӳ�ͬ�����ݼ����Ϲ���
	void ClearCmdsValues();  //���m_pValues
	void InitCmdsValues(CSttCommCmd *pCommCmd);  //��ʼ��m_pValues��
	void AddDataToEditList(CDvmData *pData);     //���༭���Ĳ�������ӵ��༭����m_pDatasEdit
	void ClearEditList();  //���m_pDatasEdit
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