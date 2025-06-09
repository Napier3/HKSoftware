#ifndef  QSTTBINRECORDSETGRID
#define  QSTTBINRECORDSETGRID

#include "../../../UI/Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../../../Module/DataMngr/DataGroup.h"
#include "../../../../../Module/DataMngr/DataTypes.h"
#include "../../../UI/Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "../../../../../Module/SmartCap/61850Cap/CapDevice/CapDeviceRcdCh.h"
#include "../../../../../Module/SmartCap/61850Cap/CapDevice/CapDeviceMngr.h"

#define QSTTBINRECORDSETGRIDCOL   7


class QSttBinRecordSetGrid :public QExBaseListGridBase
{
	Q_OBJECT

public:
	QSttBinRecordSetGrid(QWidget *parent = NULL);
	virtual ~QSttBinRecordSetGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	void MoveUp();			//ͨ������
	void MoveDown();		//ͨ������
	void MoveToTop();		//ͨ���ö�
	void MoveToBottom();	//ͨ���ײ�
	void InitData();		//�ָ�Ĭ��
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow = TRUE);

public:
	CCapDeviceMngr *m_pCapDeviceAll;
	CCapDeviceMngr *m_pInitCapDeciceAll;

signals:
	void sig_BinSetGridRowValue(int nValue);

public slots:
	void slot_BinRecordSetGrid(int nRow, int nCol);
	void slot_CellChanged(int nRow, int nCol);
public:


};


#endif
