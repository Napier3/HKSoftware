#ifndef CSTTINTELGOUTTOBINGRID_H
#define CSTTINTELGOUTTOBINGRID_H

#include "../QExBaseListGridBase/QExBaseListGridBase.h"
#include "../QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgDataMngrGlobal.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgGoutCh.h"
#include "IecCfgGoutChsGrid.h"
#define STTINTELGOUTTOBINGRID_GRID_COLS		6
class CSttIntelGoutToBinGrid : public QExBaseListGridBase
{
	Q_OBJECT
public:
	CSttIntelGoutToBinGrid(QWidget* pparent);
	virtual ~CSttIntelGoutToBinGrid();

	BOOL m_bIsUpdateParas;//�жϵ�ǰ�Ƿ��ڸ��²���;�������·����²�������ʱ,CtickCount�������DoEvents����,�����ظ����͸��²�������  20220816 zhouhj

public:
	void SetRunState(long nRunState);//���ñ��״̬,��Ϊ3��:1��ֹͣ���״̬(���޸��������͡�ͨ��ӳ��ֵ��);2��һ������״̬(��ʵʱ�޸�����ֵ);3���ݱ�״̬(�����ȫ���ɱ༭)
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	void UpdateDatas_Revert();
	virtual CDataType* FindDataType(const CString &strDataType);
	void GridCellResultVlaues(float ResultTimeVlaue,char strCharacterIndex);
	void setGooseResultVlaues();
	void startInit();

	virtual void ShowCheck_BOOLEAN(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString, GRID_CELL_EDIT_FUNC pFunc=NULL);
	virtual void ShowCheck_Dbpos(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString, GRID_CELL_EDIT_FUNC pFunc=NULL);

	void EnableInverseCol(BOOL bEnable);
	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *);
public:
	//�༭������
	static void EndEditCell_GoutChSelChangged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_AppCh_GoutDefaultValue(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);//zhouhj 20210912 ���ӶԲ�ͬ�������͵ĳ�ʼֵ���ж�
	static void EndEditCell_AppCh_GoutInverse(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	BOOL IsCheckedState_ChValue(const CString &strChValue);

protected:
	void UpdateData_ByDataType(CIecCfgGoutCh *pGoutCh,int nRow);
	void UpdateDatas_ByRevert(CIecCfgGoutCh *pGoutCh,int nRow);
	void UpdateData_Value(CIecCfgGoutCh *pGoutCh,int nRow);
	void UpdateData_Inverse(QGV_ITEM *pCell,int nRow);
	void UpdateData_ByInverse(QGV_ITEM *pCell,int nRow);

private:
	QExBaseListComBoxDelegBase *m_pDataType_DelegBase;
	QExBaseListComBoxDelegBase *m_pValue_DelegBase;
	QExBaseListCheckBoxDelegate *m_pExBaseListCheckBoxDelegate;

	int m_nRowIndex;
	CString m_strResultVlaues;
	BOOL m_bGooseFlag;
signals:
//	void sig_Iec61850Cfg_Changed();//����61850���ø����ź�
	void sig_GoutValue_Changed();//����Goose����ֵ�����ź�
	void sig_GoutMap_Changed();//�������ڿ����������͸ı���߿���ӳ��ı�
	void sig_GoutRowIndex(int nRowIndex);

 protected slots:
 	void slot_GridCellClicked(int nrow, int ncolumn);

};


#endif // CSTTINTELGOUTTOBINGRID_H
