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
	void InitData();												//初始化数据
	void InitConnect();
	void InitComboBox(CCapDeviceMngr *pCapDeviceAll);				//初始化combobox
	void SaveDataToCfg();											//保存数据到配置文件
	void BinRecordSort(CDvmData *pRecordAllData);					//排序 排列最前/排列最后
	CDataGroup *m_pBinRecordSetGroup;		
	QSttBinRecordSetGrid *m_pSttBinRecordSetGrid;				//录波设置表格

public slots:
	void slot_BinRecordChannelUp();				//通道上移槽函数
	void slot_BinRecordChannelDown();			//通道下移槽函数
	void slot_BinRecordTop();					//置顶槽函数
	void slot_BinRecordBottom();				//底部槽函数
	void slot_BinRecordDefault();				//恢复默认槽函数
	void slot_BinRecordBrowse();				//浏览槽函数
	void slot_BinRecordOK();					//确定槽函数
	void slot_BinRecordCancel();				//取消槽函数

	void slot_BtnArrange();						//排列槽函数
	void slot_BinRecordTime(bool bState);		//记录时长RButton
	void slot_BinRecordDisplay(bool bState);	//开关量通道RButton
	void slot_BinRecordTrigger(bool bState);	//触发方式RButton
	void slot_BtnEnable(int nValue);

	void slot_EditBinCustomize();
	void slot_EditBinHour();
	void slot_EditBinminute();
	void slot_EditBinsecond();

};

#endif // BINRECORDCHMAPDLG_H
