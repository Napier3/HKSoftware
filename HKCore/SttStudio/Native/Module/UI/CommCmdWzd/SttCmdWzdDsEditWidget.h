#ifndef SttCmdWzdDsEditWidget_H
#define SttCmdWzdDsEditWidget_H

#include <QDialog>
#include <QFont>
#include "SttCmdWzdDsEditGrid.h"

#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbMacroGenWzd.h"
#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbWzdCommCmdAdd.h"
#include "../../SttCmd/GuideBook/SttItems.h"

namespace Ui {
class QSttCmdWzdDsEditWidget;
}

//通讯命令向导，主窗口
class QSttCmdWzdDsEditWidget : public QDialog, public CExBaseListGridOptrInterface 
{
    Q_OBJECT
public:
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);

public:
    explicit QSttCmdWzdDsEditWidget(QFont font,QWidget *parent = 0);
    virtual ~QSttCmdWzdDsEditWidget();

	CSttCmdWzdDsEditGrid *m_pEditGrid_Write;   //用于写命令，含有列“修改为”
	CSttCmdWzdDsEditGrid *m_pEditGrid_Read;   //用于写命令，不包含列“修改为”
	CSttCmdWzdDsEditGrid_Register *m_pRegisterGrid;
	void ShowCmd(CSttItemBase *pSttItem);
	void OnAtsQueryItem(CExBaseObject *pItemPara);
	void AutoSave_AfterEdit();
	void GetDsKey(CStringArray &strKeyArray, const CString &strKey);

	BOOL m_bAutoSave;  //关闭页面时，是否自动保存，默认自动保存
	CGbMacroGenWzd *m_pCurrWzd;
	CSttCommCmd *m_pCurrCmdItem;
	CGbWzdCommCmdAdd *m_pCommCmdAdd;  //通过添加操作执行的单独指令

	CSttCommCmd m_oSttCommCmd;  //当前编辑的通信命令项目
	CString m_strDatasetKey;
	CExBaseList m_listDataset;
	CDvmDataset *m_pCurrDataset;
	BOOL m_bIsCommcmdChanged;

public:
	void InitLanguage();
	void UI_SetFont(QFont font);
	void AddDataToSttCommCmd(CDvmData *pData);
	void AddDataToWzdCmdCfg(CDvmData *pData);
	void AddDataToWzdCmdCfg_Single(CDvmData *pData);
	void AddDataToWzdCmdCfg_Value(CValue *pValue);
	void AddDataToWzdCmdCfg_Single_Value(CValue *pValue);
	void AddDataToSttCommCmd_ByDefaultVal();  //根据与默认值比较，添加修改过的参数到通讯命令

	void DeleteDataFromSttCommCmd(CDvmData *pDvmData);
	void DeleteDataFromWzdCmdCfg(const CString &strDataID);
	void DeleteDataFromWzdCmdCfg_Single(const CString &strDataID);

	void UpdateDataToWzdCmdCfg(CDvmData *pDvmData);
	void DeleteAllDatasToWzdCmdCfg();

	//通过QueryItem获取到项目后，根据项目的参数，更新数据集
	//这样做的目的，是保存的时候，能统一根据值与默认值的比较确定命令的参数
	void UpDateDataset(CDvmDataset *pDataset, CSttCommCmdData *pCmdDatas);

	void UpdateShowDataset(const CString &strDsPath);
	void ClearEmptyCmdParas();

	BOOL IsCommCmdChanged();  //通讯命令的参数，是否发生改变
signals:
	void sig_Show_CommCmd();

private slots:
	void slot_Show_CommCmd();
	void slot_CmdWzd_AddData(CDvmData *pData);
	void slot_CmdWzd_UpdateData(CDvmData *pDvmData);
	void slot_CmdWzd_UpdateData_Value(CValue *pValue);
	void on_m_btnInsertData_clicked();
	void on_m_btnDeleteData_clicked();
	void on_m_cmbDataset_currentIndexChanged(int index);
	void on_m_cmbSetZone_currentIndexChanged(int index);
	void on_m_cmbDelayBft_currentIndexChanged(int index);
	void on_m_cmbDelayAft_currentIndexChanged(int index);

    void on_m_btnSave_clicked();
	void EnableSettingZone();
	void Show_CommCmd_DelayBft();
	void Show_CommCmd_DelayAft();
	void EnableBtns();
    void on_m_btnExecCmd_clicked();

private:
	Ui::QSttCmdWzdDsEditWidget *ui;

};

#endif // SttCmdWzdDsEditWidget_H
