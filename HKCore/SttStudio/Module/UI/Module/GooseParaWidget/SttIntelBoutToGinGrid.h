#ifndef CSTTINTELBOUTTOGINGRID_H
#define CSTTINTELBOUTTOGINGRID_H

#include "../QExBaseListGridBase/QExBaseListGridBase.h"
#include "../QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgDataMngrGlobal.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgGinCh.h"
#include "../../IEC61850Config/Grid/IecCfgGinChsGrid.h"

#define STTINTELBOUTTOGINGRID_GRID_COLS		6

class CSttIntelBoutToGinGrid : public QExBaseListGridBase
{
	Q_OBJECT
public:
	CSttIntelBoutToGinGrid(QWidget* pparent);
	virtual ~CSttIntelBoutToGinGrid();

public:
	virtual void SetRunState(long nRunState);//���ñ��״̬,��Ϊ3��:1��ֹͣ���״̬(���޸��������͡�ͨ��ӳ��ֵ��);2��һ������״̬(��ʵʱ�޸�����ֵ);3���ݱ�״̬(�����ȫ���ɱ༭)
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual CDataType* FindDataType(const CString &strDataType);
	void GridCellResultVlaues(float fResultTimeVlaue,char strCharacterIndex);
	void UpdateState(int nStateValue);//���ٿ���״ֵ̬
	void startInit();

	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *);

public:
	//�༭������
	static void EndEditCell_GinChSelChangged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_AppCh_GinDefaultValue(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

protected:
	void UpdateData_ByDataType(CIecCfgGinCh *pGoutCh,int nRow);
	void UpdateData_Inverse(QGV_ITEM *pCell,int nRow);

private:
	QExBaseListComBoxDelegBase *m_pDataType_DelegBase;
	QExBaseListComBoxDelegBase *m_pMap_DelegBase;
	QExBaseListComBoxDelegBase *m_pValue_DelegBase;

	int m_nCheckState;
	BOOL m_bBinFlag;
	BOOL m_bGooseFlag;
signals:
//	void sig_Iec61850Cfg_Changed();//����61850���ø����ź�
	void sig_GoutValue_Changed();//����Goose����ֵ�����ź�
	void sig_GinRowIndex(int nRowIndex,float fActTime);
};


#endif // CSTTINTELBOUTTOGINGRID_H
