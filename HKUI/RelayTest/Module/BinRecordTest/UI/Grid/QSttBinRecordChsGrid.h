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
	void InitComboBox();             //初始化下拉框数据
	void JudgCurOrVol(int nRow);     //判断档位是电压还是电流
	CString FormatFloat(float value);
	void ComputeGearValue(float fValue, int nRow, int nCol);   //根据夹钳比率的值计算档位值
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
