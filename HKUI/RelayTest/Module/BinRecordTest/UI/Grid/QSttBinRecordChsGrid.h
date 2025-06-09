#ifndef  QSTTBINRECORDCHSGRID
#define  QSTTBINRECORDCHSGRID

#include "../../../UI/Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../../../Module/DataMngr/DataGroup.h"
#include "../../../../../Module/DataMngr/DataTypes.h"
#include "../../../UI/Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "../../../../../Module/SmartCap/61850Cap/CapDevice/CapDeviceRcdCh.h"

#define QSTTTESTITEMGRIDCOL   7

class QSttBinRecordChsGrid :public QExBaseListGridBase
{
	Q_OBJECT

public:
	QSttBinRecordChsGrid(QWidget *parent = NULL);
	virtual ~QSttBinRecordChsGrid();


	virtual void InitGrid();
	virtual void InitGridTitle();
	void InitComboBox();             //��ʼ������������
	void JudgCurOrVol(int nRow);     //�жϵ�λ�ǵ�ѹ���ǵ���
	CString FormatFloat(float value);
	void ComputeGearValue(float fValue, int nRow, int nCol);   //���ݼ�ǯ���ʵ�ֵ���㵵λֵ
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow = TRUE);
	static void EndEditCell_ComboBoxChanged(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_GearComboBoxChanged(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_ClampRateLineEditChanged(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);

	BOOL m_bRunning;
	long m_nEtypeValue;
	CDataTypes m_oBinRcdDataTypes;
	QExBaseListComBoxDelegBase *m_pDelegEtype;
	QExBaseListComBoxDelegBase *m_pMeasGear;
	QExBaseListComBoxDelegBase *m_pChAngType;
	
public slots:
	void slot_BinRecordMeasGear(long nValue, int nRow, int nCol);

signals:
	void sig_BinRecordEtype(long nValue,int nRow, int nCol);
};


#endif
