#ifndef QCHAREDITRADIOHARMWIDGET_H
#define QCHAREDITRADIOHARMWIDGET_H

#include "ui_QCharEditRadioHarmWidget.h"
#include <QWidget>
#include "CharEditWidgetBase.h"
#include "../../SttTestCntrFrameApi.h"
#include "../../Module/CommonMethod/commonMethod.h"
#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../../Module/DataMngr/DvmValues.h"
#include "../../../XLangResource_Native.h"
#include "../../../../../Module/FaultCal/DiffCharCal.h"
#include "../../../../../AutoTest/Module/Characteristic/Characteristic.h"
#include "CharEditWidget_Diff.h"


class QCharEditRadioHarmWidget : public QWidget ,public CExBaseListGridOptrInterface
{
    Q_OBJECT

public:
	QCharEditRadioHarmWidget(QWidget *parent = 0, CDiffCharCal *pDiffCharCal = NULL);
    ~QCharEditRadioHarmWidget();

	QCharEditGrid_DiffLine *m_pGridCharLine;

private:
    Ui::QCharEditRadioHarmWidget ui;
	
	QStringList m_astrTranSortList;	//变压器接线方式
	CDiffCharCal *m_pDiffCharCal;

public:
	void InitUI();
	void InitConnect();
	void InitChar();
	void SetDiffFont(); 
        void InitLanguage();
	void InitDiffData();
	void InitUI_Unit();
	void UpdateEditsDisEnable();
	long GetSettingMinAxisIndex();
	float SetParaI(QLineEdit* pEdit, float& fv);
	float SetParaK(QLineEdit* pEdit, float& fv);
	float SetLimit(float min,float max,float val);
	float CalLineK(CCharElementLined* pLine);
	void UpdateEdit_IrValueUserPoint();//更新用户自定义点制动电流值
	void UpdateTranSortIndex(int index);//20230713-wxy 修改变压器接线形式
	void InitDataToChar();
	void SetCDiffCharCal(CDiffCharCal *pDiffCharCal);
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);

signals:
	void sig_CharChanged(CExBaseObject *,int);//改特性图
	void sig_ChangeICMAxisName();//修改坐标系
	void sig_MainWidgetCharChange();//改变主界面中
	void sig_IdValue_editingFinished(CString);//制动电流完成编辑
	void sig_ChangeTranSortIndex(int);//20230713-wxy-改变变压器接线形式
	void sig_ChangeSettingMinAxisIndex(int);//修改定值整式方式
	void sig_ChangeInset(float);//20230713-wxy-改变基准电流
	void sig_ChangeCTPoint(bool);
	void sig_UpdateChar(bool,bool,bool);
	void sig_ChangeIstart(float);
	void sig_ChangeIsd(float);
	void sig_TestPointsErrorBandChanged();
	void sig_ActiveSegment(CCharElement *);

protected:
	CCharacteristic* GetCurrentCharacter();

private slots:
	void on_m_edtSet_Istart_editingFinished();
	void on_m_edtSet_Isd_editingFinished();
	void on_m_onlineEdit_Changed();

	void slot_TestPointsErrorBandChanged();
	void slot_DiffCharChanged();
	void slot_IdValue_editingFinished();
	void slot_btnUserAdd(bool bState);
	void slot_btnUserClear(bool bState);

	void slot_CmbSettingMinAxisIndexChanged(int nIndex);
	void slot_CmbHarmIndexChanged(int nIndex);
	void slot_cmb_TranSortIndexChanged(int index);
	void slot_InSet_editingFinished();
	void slot_HarmCoef_editingFinished();
	void slot_normalChangeTransSort(int index);//2023-07-13 wxy 由比率差动的变压器接线方式变化
	void slot_normalChangeSettingMinAxis(int index);//2023-07-13 wxy 由比率差动的定值变化
	void slot_normalChangeInSet(float InSet);
	void slot_normalChangeCTPoint(bool bAmbo);
	void slot_normalChangeIstart(float Istart);
	void slot_normalChangeIsd(float Isd);

public:
	bool m_bAmbo;
	long m_nTranSort;//2023-07-14 wxy 变压器接线形式
};
#endif // QCHAREDITRADIOHARMWIDGET_H
