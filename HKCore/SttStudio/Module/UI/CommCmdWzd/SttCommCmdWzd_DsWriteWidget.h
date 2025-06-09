#ifndef SttCommCmdWzd_DsWriteWidget_H
#define SttCommCmdWzd_DsWriteWidget_H

#include <QDialog>
#include <QFont>
#include "../../../../Module/DataMngr/DataGroup.h"
#include "SettingZoneComboBox.h"
// #include "SttCmdWzdGrid_DsData.h"
#include "../../../../Module/DataMngr/DvmDataset.h"

//lijunqing 2022-9-9
#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbMacroGenWzd.h"

#include "CmdDelayComboBox.h"
#include "SttCmdWzdDsEditGrid.h"

namespace Ui {
class QSttCommCmdWzd_DsWriteWidget;
}

//通讯命令向导，写数据集对话框
class QSttCommCmdWzd_DsWriteWidget : public QDialog, public CExBaseListGridOptrInterface
{
    Q_OBJECT
public:
	void InitLanguage();
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);

public:
    explicit QSttCommCmdWzd_DsWriteWidget(QFont font,QWidget *parent = 0);
    virtual ~QSttCommCmdWzd_DsWriteWidget();

	CSettingZoneComboBox* m_cmbSettingZone;
	CCmdDelayComboBox* m_cmbDelayBft;
	CCmdDelayComboBox* m_cmbDelayAft;
	QFont m_font;
	//CSttCmdWzdGrid_DsData* m_pSrcDataGrid;
	CSttCmdWzdDsEditGrid* m_pDesDataGrid;
	CDataGroup *m_pDatasetDes;   //目标数据。从应答中获取，为CDataGroup对象；
	CDvmDataset *m_pDatasetSrc; //源数据，从模型中获取
	//CDvmData* m_pSelSrc; //源数据，选中的数据
	//CDvmData* m_pSelDes; //目标数据，选中的数据
	CSttCmdWzd_Step *m_pSetpWzd;   //当前的步骤

public:
	void UI_SetFont();
	void InitSettingZone();
	//void EnableBtns();
	void EnableSettingZone(const CString &strDsPath);

	void UpdateShow(CDataGroup *pCmdGrp);
	virtual void ShowDatas(CDataGroup* pRef, CDataGroup* pBK);

public slots:
// 	void slot_AddAllClick();
// 	void slot_AddOneClick();
// 	void slot_RemoveAllClick();
// 	void slot_RemoveOneClick();
// 	void slot_AddAs_0_Click();
// 	void slot_AddAs_1_Click();
	void slot_CmdWzd_UpdateData(CDvmData *pDvmData);

signals:

private slots:
	void on_m_cmbSettingZone_currentIndexChanged(int index);
	void on_m_cmbDelayBft_currentIndexChanged(int index);
	void on_m_cmbDelayAft_currentIndexChanged(int index);

private:
    Ui::QSttCommCmdWzd_DsWriteWidget *ui;


};

#endif // SttCommCmdWzd_DsWriteWidget_H
