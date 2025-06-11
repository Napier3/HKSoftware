#ifndef QCHAREDITRADIONORMALWIDGET_H
#define QCHAREDITRADIONORMALWIDGET_H

#include "ui_QCharEditRadioNormalWidget.h"
#include <QWidget>
#include "CharEditWidgetBase.h"
#include "../../SttTestCntrFrameBase.h"
#include "../../Module/CommonMethod/commonMethod.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../Module/DataMngr/DvmValues.h"
#include "../../../XLangResource_Native.h"
#include "../../../Module/FaultCal/DiffCharCal.h"
#include "../../../AutoTest/Module/Characteristic/Characteristic.h"
#include "../QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "CharEditWidget_Diff.h"


class QCharEditRadioNormalWidget : public QWidget ,public CExBaseListGridOptrInterface
{
    Q_OBJECT

public:
	 QCharEditRadioNormalWidget(QWidget *parent = 0,CDiffCharCal *pDiffCharCal = NULL);
    ~QCharEditRadioNormalWidget();

	QCharEditGrid_DiffLine *m_pGridCharLine;

private:
    Ui::QCharEditRadioNormalWidget ui;
	QStringList m_astrTranSortList;	//��ѹ�����߷�ʽ
	CDiffCharCal *m_pDiffCharCal;

public:
	void InitUI();
	void InitConnect();
	void InitChar();
        void InitLanguage();
	void SetDiffFont(); 
	void InitDiffData();
	void InitUI_Unit();
	void EnableEdit(long nIndex);
	void DisableEdit(long nIndex);
	void UpdateEditsDisEnable();
	float SetParaI(QLineEdit* pEdit, float& fv);
	float SetParaK(QLineEdit* pEdit, float& fv);
	float SetLimit(float min,float max,float val);
	float CalLineK(CCharElementLined* pLine);

	void UpdateTransSortPicture(int index);
	void UpdateEdit_IrValueUserPoint();//�����û��Զ�����ƶ�����ֵ
	void InitDataToChar(long nRateCoef2Check);
	void SetCDiffCharCal(CDiffCharCal *pDiffCharCal);
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);

protected:
	CCharacteristic* GetCurrentCharacter();

signals:
	void sig_CharChanged(CExBaseObject *,int);//������ͼ
	void sig_ChangeSettingMinAxisIndex(int);//20230713-wxy-�޸Ķ�ֵ��ʽ��ʽ
	void sig_ChangeICMAxisName();//�޸�����ϵ
	void sig_MainWidgetCharChange();
	void sig_IdValue_editingFinished(CString);//�ƶ�������ɱ༭
	void sig_ChangeTranSortIndex(int);//20230713-wxy-�ı��ѹ��������ʽ
	void sig_ChangeInset(float);
	void sig_ChangeCTPoint(bool);
	void sig_UpdateChar(bool,bool,bool);
	void sig_ChangeIstart(float);
	void sig_ChangeIsd(float);
	void sig_TestPointsErrorBandChanged();
	void sig_ActiveSegment(CCharElement *);
	

private slots:
	void on_m_chkStart_clicked();
	void on_m_chkLine1_clicked();
	void on_m_chkLine2_clicked();
	void on_m_chkLineSd_clicked();
	
	void on_m_edtSet_Istart_editingFinished();//���������༭����ɱ༭
	void on_m_edtSet_Kstart_editingFinished();
	void on_m_edtSet_Ip1_editingFinished();
	void on_m_edtSet_K1_editingFinished();
	void on_m_edtSet_Ip2_editingFinished();
	void on_m_edtSet_K2_editingFinished();
	void on_m_edtSet_Isd_editingFinished();
	void on_m_onlineEdit_Changed();
	
	void slot_btnUserAdd(bool bState);
	void slot_btnUserClear(bool bState);

	void slot_InSet_editingFinished();//20230707-wxy-��׼����
	void slot_IdValue_editingFinished();////20230707-wxy-�ƶ�������ɱ༭

	void slot_cmb_TranSortIndexChanged(int index);//20230707-wxy-��ѹ�����߷�ʽ
	void slot_CmbSettingMinAxisIndexChanged(int nIndex);

	void slot_TestPointsErrorBandChanged();
	void slot_DiffCharChanged();
	void slot_HarmChangeTransSort(int index);//20230713 wxy ��г���ƶ��ı�ѹ�����߷�ʽ�仯
	void slot_HarmChangeSettingMinAxis(int index);//20230713 wxy �ɱ��ʲ�Ķ�ֵ�仯
	void slot_HarmChangeInSet(float InSet);//20230713 wxy �ɱ��ʲ�Ļ�׼�����仯
	void slot_HarmChangeCTPoint(bool bAmbo);
	void slot_HarmChangeIstart(float Istart);
	void slot_HarmChangeIsd(float Isd);

public:
	bool m_bAmbo;
	long m_nTranSort;//2023-07-14 wxy ��ѹ��������ʽ
	
	
};

#endif // QCHAREDITRADIONORMALWIDGET_H
