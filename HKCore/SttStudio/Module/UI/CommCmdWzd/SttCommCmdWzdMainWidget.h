#ifndef SttCommCmdWzdMainWidget_H
#define SttCommCmdWzdMainWidget_H

#include <QDialog>
#include <QFont>
#include "SttCommCmdWzdGrid.h"
#include "..\Module\QExBaseListGridBase\QExBaseListGridBase.h"
#include "SttCommCmdWzd_SelMacroWidget.h"
#include "SttCmdWzdGrid_Register.h"
#include "SttCommCmdWzd_DsWriteWidget.h"
#include "SttCommCmdWzd_DsReadWidget.h"
#include "SttCommCmdWzd_ErrorValueWidget.h"

//lijunqing 2022-9-9
#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbMacroGenWzd.h"

namespace Ui {
class QSttCommCmdWzdMainWidget;
}

//ͨѶ�����򵼣�������
class QSttCommCmdWzdMainWidget : public QDialog, public CExBaseListGridOptrInterface 
{
    Q_OBJECT
public:
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);

public:
    explicit QSttCommCmdWzdMainWidget(QFont font,QWidget *parent = 0);
    virtual ~QSttCommCmdWzdMainWidget();

	QFont m_font;
	CExBaseList *m_pParentItem;  //�½���ʱ����Ŀ����ѡ�еĸ���Ŀ
	CSttCommCmdWzdGrid *m_pGridWzd;
	BOOL m_bClickedFinish;

	CGbMacroGenWzd *m_pGbMacroGenWzd;

	CString m_strBFDelayTime_Setting;
	CString m_strAFTDelayTime_Setting;
	CString m_strBFDelayTime_Ena;
	CString m_strAFTDelayTime_Ena;
	CString m_strBFDelayTime_Parameter;
	CString m_strAFTDelayTime_Parameter;

public:
	void UI_SetFont();
	void EnableBtns(QWidget *pWidget);
	virtual void reject();
	virtual void accept();
	void SetNextBtnText(const CString &strText);

public slots:
	void slot_PreClick();
	void slot_NextClick();
	void slot_CancelClick();

signals:
	void sig_Show_Hide_Widget(QWidget *pWidget, bool bShow);
	void sig_DisableNextBtn(bool bDisable);
	void sig_DisablePreBtn(bool bDisable);
	void sig_SetNextBtnText(const CString& strText);
	void sig_SetNextBtnTextEx(const CString& strText);
	void sig_UpdateShowDsWrite(CDataGroup *pCmdGrp);
	void sig_FreeCommCmdWzdWidget();
	void sig_OnAtsGenerateItems_CmdWzd(CExBaseList *pCmdGrp);

private slots:
	void slot_Show_Hide_Widget(QWidget *pWidget, bool bShow);
	void slot_DisableNextBtn(bool bDisable);
	void slot_DisablePreBtn(bool bDisable);
	void slot_SetNextBtnText(const CString& strText);
	void slot_SetNextBtnTextEx(const CString& strText);
	void slot_UpdateShowDsWrite(CDataGroup *pCmdGrp);
	void slot_OnAtsGenerateItems_CmdWzd(CExBaseList *pCmdGrp);

private:
    Ui::QSttCommCmdWzdMainWidget *ui;

	QSttCommCmdWzd_SelMacroWidget *m_pSttSelMacroWidget;
	QSttCommCmdWzd_DsReadWidget *m_pReadDsWidget;
	CSttCmdWzdGrid_Register *m_pRegisterWidget;
	QSttCommCmdWzd_DsWriteWidget *m_pWriteDsWidget;
	QSttCommCmdWzd_ErrorValueWidget *m_pErrorValueWidget;

public:
	void NewGbMacroGenWzd(CString &strParentItemsID);
 	void OnAtsGenerateItems_CmdWzd(CExBaseList *pCmdGrp);
	long Shwo_Hide_Widgets(BOOL bNext=TRUE);  //����0 = �޲�����1 = ��һ����2 = ��һ����3 = ���
	void UpdateCmdGrid_ShowCurrStep(BOOL bReset);  //���ݵ�ǰ���裬������ʾ�򵼱���еĵ�ǰ��
	void NextClick_Init();
	void NextClick_Step_Write();
	void NextClick_Step_Register();
	void NextClick_Step_Read();
	void NextClick_Finish();
	void OnChangeDelayTime(CDataGroup* pDataGroup);
	void InitGenerateItemsParas(CSttCmdWzd_Step *pCmdDatasets, CDataGroup *pA_Bft);
	void ResetDataset(CDataGroup* pDataGroup);
	//CDvmValue* GetDataValue(CDvmData *pData);  �ƶ���CDvmData��  shaolei 2023-7-28
	void AutoCompleteAfterTest();
	CDvmData* SelectReleatedData(CDataGroup *pSrcGrp, CDataGroup* pSrcdsGrp, CDvmData *pDestData);
	void AddErrorEvaluteStep();  //����ѡ��Ĺ��ܣ��Զ����������ò���
	void AutoClick(long nOptr);
};

#endif // SttCommCmdWzdMainWidget_H
