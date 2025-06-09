#ifndef _CSttReplayBoutModuleChWidget_H_
#define _CSttReplayBoutModuleChWidget_H_

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QRadioButton>
#include "ui_SttReplayBoutModuleChWidget.h"
#include "../Module/CommonMethod/commonMethod.h"
// #include "../Module/Define.h"
#include "../../../Module/DataMngr/DataGroup.h"
#include "../../../Module/ReplayTest/BigComtradeTransPlay.h"
// #include "../../Module/TestWinFrame/QExBaseListGridBase/QExBaseListGridBase.h"
//#include "BinaryOutGrid.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"


#define BOUT_TABLE_BINARYINDEX	0
#define BOUT_TABLE_CHSTATE		1
#define BOUT_TABLE_CHSELECT		2

class CSttReplayBoutModuleChWidget : public QWidget
{
	Q_OBJECT

public:
	CSttReplayBoutModuleChWidget(QWidget *pParent = 0, CSttModuleComtradeBind *pModuleInfo = NULL);
	~CSttReplayBoutModuleChWidget();

	void InitUI();
	void InitTableUI();
	void InitBinaryOutSet();	
	void initSignalSlots();
	void uninitSignalSlots();


	void UpdateButtonEnable(BOOL state);
	void UpdateStateEnabled(BOOL isLeftWidget, int nRow, int nCol);
	void UpdateChWidget();//刷新通道数据
	void SetChSelectList(const QStringList &oBinaryChList);
	void OnBinaryModuleChChanged(CSttModuleComtradeBind *pBinaryModule);
	void UpdateChannelMapChanged(QScrollComboBox *comboBox, int index);//映射通道更新

	int m_nBoutCount;
	CSttModuleComtradeBind *m_pModuleInfo;

public:
	QList<QCheckBox *> m_ChStateList;//开出量状态
	QList<QScrollComboBox *> m_ChSelList;//开出量通道映射选择

public slots:
	void slot_btnDisconnectAll();
	void slot_btnClearMap();
	void slot_tableCellClicked(int row, int column);
	void slot_tableInsCellClicked(int row, int column);
	void slot_ChannelMapChanged(int index);//下拉框
	void slot_ChStateChanged(int index);//通道状态


private:
	Ui::CSttReplayBoutModuleChWidget ui;

};



#endif //_CSttReplayBoutModuleChWidget_H_