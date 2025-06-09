#ifndef QSttBinRecordSetDlg_H
#define QSttBinRecordSetDlg_H

#include <QDialog>
#include "ui_QSttBinRecordSetDlg.h"
#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapDeviceRecord.h"
#include "Grid/QSttBinRecordSetGrid.h"
namespace Ui{
	class QSttBinRecordSetDlg;
}

class QSttBinRecordSetDlg : public QDialog
{
	Q_OBJECT

public:
	Ui::QSttBinRecordSetDlg ui;

	QSttBinRecordSetDlg(CCapDeviceMngr *pCapDeviceAll, CDataGroup *pBinRecordCfgDataGroup,QWidget *parent);
	~QSttBinRecordSetDlg();
	void InitData();												//��ʼ������
	void InitConnect();
	void InitComboBox(CCapDeviceMngr *pCapDeviceAll);				//��ʼ��combobox
	void SaveDataToCfg();											//�������ݵ������ļ�
	void BinRecordSort(CDvmData *pRecordAllData);					//���� ������ǰ/�������
	CDataGroup *m_pBinRecordSetGroup;		
	QSttBinRecordSetGrid *m_pSttBinRecordSetGrid;				//¼�����ñ��

public slots:
	void slot_BinRecordChannelUp();				//ͨ�����Ʋۺ���
	void slot_BinRecordChannelDown();			//ͨ�����Ʋۺ���
	void slot_BinRecordTop();					//�ö��ۺ���
	void slot_BinRecordBottom();				//�ײ��ۺ���
	void slot_BinRecordDefault();				//�ָ�Ĭ�ϲۺ���
	void slot_BinRecordBrowse();				//����ۺ���
	void slot_BinRecordOK();					//ȷ���ۺ���
	void slot_BinRecordCancel();				//ȡ���ۺ���

	void slot_BtnArrange();						//���вۺ���
	void slot_BinRecordTime(bool bState);		//��¼ʱ��RButton
	void slot_BinRecordDisplay(bool bState);	//������ͨ��RButton
	void slot_BinRecordTrigger(bool bState);	//������ʽRButton
	void slot_BtnEnable(int nValue);

	void slot_EditBinCustomize();
	void slot_EditBinHour();
	void slot_EditBinminute();
	void slot_EditBinsecond();

};

#endif // BINRECORDCHMAPDLG_H
