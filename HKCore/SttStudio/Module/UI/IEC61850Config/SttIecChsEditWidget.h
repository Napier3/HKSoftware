#ifndef STTIECCHSEDITWIDGET_H
#define STTIECCHSEDITWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QRadioButton>
#include <QScrollArea>
#include <QComboBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include "../../../../61850/Module/CfgDataMngr/IecCfgChsBase.h"
#include "Grid/IecCfgSmv92ChsGrid.h"
#include "Grid/IecCfgSmv92InChsGrid.h"
#include "Grid/IecCfgSmvFT3OutChsGrid.h"
#include "Grid/IecCfgSmvFT3InChsGrid.h"
#include "Grid/IecCfgGinChsGrid.h"
#include "Grid/IecCfgGoutChannelsGrid.h"


#define STT_IEC_CHS_TYPE_SMV92                     0
#define STT_IEC_CHS_TYPE_SMV92IN                   1
#define STT_IEC_CHS_TYPE_GIN                       2
#define STT_IEC_CHS_TYPE_GOUT                      3
#define STT_IEC_CHS_TYPE_SMV_FT3OUT                4
#define STT_IEC_CHS_TYPE_SMV_FT3IN                 5


class QSttIecChsEditWidget : public QWidget
{
	Q_OBJECT

public:
	QSttIecChsEditWidget(int nChsType,QWidget *parent= NULL);
	~QSttIecChsEditWidget();

	virtual void InitData(CIecCfgChsBase *pIecCfgChs);
	virtual void SaveData();
	CIecCfgChsGridBase *m_pIecCfgChsGrid;
	QPushButton *m_pOK_PushButton;

private:
	void InitUI();
	void InitUI_SMV92Map();//增加SMV92中的通道映射内容
	void SetIec92ChsEditFont();
	void InitUI_SMVFT3Map();//增加SMVFT3发布中的通道编辑内容
	void InitUI_SMVFT3InMap();//增加SMVFT3订阅中的通道编辑内容
	void SetIecFT3ChsEditFont();

	void SwitchChMap(long nGroupIndex,BOOL bSetU, BOOL bSetI,BOOL bDC_FT3);

	QVBoxLayout *m_pMain_VLayout;
	QHBoxLayout *m_pOK_CancelHLayout;
	int m_nChsType;
	CIecCfgChsBase *m_pIecCfgChs;

	//SMV92相关
	QPushButton *m_p_SetChsTest_PushButton;
	QComboBox *m_pCurrentMapComboBox;
	QComboBox *m_pVoltageMapComboBox;
	QPushButton *m_p_SelectAll_PushButton;
	QPushButton *m_p_UnSelectAll_PushButton;
	QPushButton *m_p_SelectProtCurr_PushButton;
	QPushButton *m_p_SelectMeasCurr_PushButton;
	QPushButton *m_p_SelectVol_PushButton;
	QLabel *m_pIMap_Label;
	QLabel *m_pUMap_Label;

	//SMVFT3相关
	QPushButton *m_p_SetInitValue_PushButton;
	QPushButton *m_p_DIMap_PushButton;
	//2023/10/19 wjs 添加柔直FT3相关控件
	QLabel *m_pDcIMap_Label;
	QLabel *m_pDcUMap_Label;
	QLabel *m_pAcIMap_Label;
	QLabel *m_pAcUMap_Label;
	QComboBox *m_pDcCurrentMapComboBox;
	QComboBox *m_pDcVoltageMapComboBox;
	QComboBox *m_pAcCurrentMapComboBox;
	QComboBox *m_pAcVoltageMapComboBox;

public slots:
	void slot_SetChsTestClicked();
	void slot_SelectAllClicked();
	void slot_UnSelectAllClicked();
	void slot_SelProtCurrClicked();
	void slot_SelMeasCurrClicked();
	void slot_SelVolClicked();
	void slot_CurrentMapChanged(int);
	void slot_VoltageMapChanged(int);
	void slot_SetInitValueClicked();
	void slot_DIMapClicked();
	void slot_UpdateCB_ChDatas(CExBaseList *pCurrSelData);

	//2023/10/19 wjs
	void slot_DcCurrentMapChanged(int);
	void slot_DcVoltageMapChanged(int);
	void slot_AcCurrentMapChanged(int);
	void slot_AcVoltageMapChanged(int);

	void slot_BinMapEnabled(bool isBinMapEnabled);//2023-10-25 suyang FT3订阅 开入映射使能状态改变
	void slot_SetInitValueEnabled(bool bSetInitValue);//2024-01-22 suyang FT3发布 初值设置按钮使能状态改变
};

#endif  //STTIECCHSEDITWIDGET_H
