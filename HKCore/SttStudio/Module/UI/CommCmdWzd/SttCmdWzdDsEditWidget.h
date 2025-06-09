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

//ͨѶ�����򵼣�������
class QSttCmdWzdDsEditWidget : public QDialog, public CExBaseListGridOptrInterface 
{
    Q_OBJECT
public:
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);

public:
    explicit QSttCmdWzdDsEditWidget(QFont font,QWidget *parent = 0);
    virtual ~QSttCmdWzdDsEditWidget();

	CSttCmdWzdDsEditGrid *m_pEditGrid_Write;   //����д��������С��޸�Ϊ��
	CSttCmdWzdDsEditGrid *m_pEditGrid_Read;   //����д����������С��޸�Ϊ��
	CSttCmdWzdDsEditGrid_Register *m_pRegisterGrid;
	void ShowCmd(CSttItemBase *pSttItem);
	void OnAtsQueryItem(CExBaseObject *pItemPara);
	void AutoSave_AfterEdit();
	void GetDsKey(CStringArray &strKeyArray, const CString &strKey);

	BOOL m_bAutoSave;  //�ر�ҳ��ʱ���Ƿ��Զ����棬Ĭ���Զ�����
	CGbMacroGenWzd *m_pCurrWzd;
	CSttCommCmd *m_pCurrCmdItem;
	CGbWzdCommCmdAdd *m_pCommCmdAdd;  //ͨ����Ӳ���ִ�еĵ���ָ��

	CSttCommCmd m_oSttCommCmd;  //��ǰ�༭��ͨ��������Ŀ
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
	void AddDataToSttCommCmd_ByDefaultVal();  //������Ĭ��ֵ�Ƚϣ�����޸Ĺ��Ĳ�����ͨѶ����

	void DeleteDataFromSttCommCmd(CDvmData *pDvmData);
	void DeleteDataFromWzdCmdCfg(const CString &strDataID);
	void DeleteDataFromWzdCmdCfg_Single(const CString &strDataID);

	void UpdateDataToWzdCmdCfg(CDvmData *pDvmData);
	void DeleteAllDatasToWzdCmdCfg();

	//ͨ��QueryItem��ȡ����Ŀ�󣬸�����Ŀ�Ĳ������������ݼ�
	//��������Ŀ�ģ��Ǳ����ʱ����ͳһ����ֵ��Ĭ��ֵ�ıȽ�ȷ������Ĳ���
	void UpDateDataset(CDvmDataset *pDataset, CSttCommCmdData *pCmdDatas);

	void UpdateShowDataset(const CString &strDsPath);
	void ClearEmptyCmdParas();

	BOOL IsCommCmdChanged();  //ͨѶ����Ĳ������Ƿ����ı�
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
