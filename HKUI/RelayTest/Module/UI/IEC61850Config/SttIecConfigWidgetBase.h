/************************************************************************/
/* 列表式配置界面的基类                                                                     */
/************************************************************************/
#ifndef STTIECCONFIG_WIDGETBASE_H
#define STTIECCONFIG_WIDGETBASE_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>

#include "../Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgDatasBase.h"
#include "Grid/IecCfgDataGridBase.h"
#include "../../../../Module/DataMngr/DataGroup.h"

#define STT_IEC_SMVFT3_CRC_16BYTE_VERIFICATION 		   0 //0-标准16字节校验
#define STT_IEC_SMVFT3_CRC_END_VERIFICATION 		   1  //1-报文末尾校验
#define STT_IEC_SMVFT3_CRC_14BYTE_VERIFICATION 		   2 //第一个数据块14字节校验s

class QSttIecConfigWidgetBase : public QWidget ,public CExBaseListGridOptrInterface
{
	Q_OBJECT

public:
	QSttIecConfigWidgetBase(QWidget *parent=NULL);
	~QSttIecConfigWidgetBase();

	void SetFont(const QFont &oFont);
	bool m_bDataSelChanged;
	CIecCfgChsBase* GetCfgChs();
	void AttachRefChsGrid(QExBaseListGridBase *pRefChsGrid);
	void SetChannelEditBtnVisible(bool bVisible);
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGDATABASE;   }

protected:
	virtual void InitUI();
	virtual void InitData(CIecCfgDatasBase* pIecCfgDatasBase);
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);
	virtual void OnScrollGridFinished();
	void CreateCtrlBlocksToolbar();
	virtual void EnableAllButtons();
	virtual void UpdateAppMaps(){}
	virtual CIecCfgDataBase* AddNewIecCfgData();
	void AutoSetCfgDataValue(CIecCfgDataBase *pCfgData, long nOffset);
	void SetIecConfigWidgetFont();

	QVBoxLayout *m_pMainVLayout;

	QPushButton *m_pAdd_PushButton;
	QPushButton *m_pDel_PushButton;
	QPushButton *m_pDeleteN_1_PushButton;
	QPushButton *m_pSelAll_PushButton;
	QPushButton *m_pUnSelectedAll_PushButton;
	QPushButton *m_pCopy_PushButton;
	QPushButton *m_pPaste_PushButton;
	QPushButton *m_pChannelEdit_PushButton;

	QHBoxLayout *m_pCtrlBlocksSetHLayout;

	CIecCfgDataGridBase *m_pIecCfgDataGridBase;
	CIecCfgDatasBase* m_pIecCfgDatasBase;
	CIecCfgDataBase *m_pCopy_IecCfgDataRef;//粘贴时使用的对象,在拷贝时,对该指针赋值
	QFont m_oIecFont;
	CDataGroup m_oPkgTypeList;//20230419 zhouhj 用于FT3订阅和发布使用

signals:
	void sig_UpdateCB_ChDatas(CExBaseList *pCB_Data);
	
protected slots:
	void slot_AddClicked();
	void slot_DelClicked();
	void slot_CopyClicked();
	void slot_PasteClicked();

	void slot_ChannelEditClicked();

	void slot_SelAllClicked();
	void slot_UnSelectedAllClicked();
	void OnDeleteN_1Clicked();
};

extern CFont *g_pSttGlobalFont;  

#endif // STTIECCONFIG_WIDGETBASE_H
