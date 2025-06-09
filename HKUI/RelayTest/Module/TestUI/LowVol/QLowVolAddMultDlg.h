#ifndef QLOWVOLADDMULTDLG_H
#define QLOWVOLADDMULTDLG_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "../../UI/Controls/SttCheckBox.h"
#include <QGroupBox>
#include "ui_QLowVolAddMultDlg.h"
#include "../../DataMngr/DataGroup.h"
#include "../../DataMngr/DataMngrGlobal.h"
#include "../../API/GlobalConfigApi.h"
#include "../../UI/Controls/SttCheckBox.h"
#include "QLowVolAssessDlg.h"
#include "SttMultiMacroLowVolParasDefine.h"

#define TIPS_DISPLAY_TIME	3000

namespace Ui{
	class QLowVolAddMultDlg;
}

class QLowVolAddMultDlg : public QDialog
{
	Q_OBJECT

public:
	Ui::QLowVolAddMultDlg *ui;

	QLowVolAddMultDlg(QWidget *parent = 0);
	virtual ~QLowVolAddMultDlg();
protected:
	int m_nTipsTime;//页面提示计时ID

private:
	void SetApplyTips(CString strTips);
	void timerEvent(QTimerEvent* ev);
public:
	void InitUI();
	void InitFont();
	void InitConnects();
	void OpenXmlFile();
	void InitDatas();
	void ShowOneChecked(QCheckBox* pCurrentCheckBox, bool state);

	CDataGroup m_oLowVolDataGroup;

public slots:
	void slot_TripVolCheck();
	void slot_UActTimeCheck(bool state);
	void slot_DvdtCloseCheck(bool state);
	void slot_IAtresiacheck(bool state);
	void slot_Exit();
	void slot_Ok();

	void slot_EditUAct();
	void slot_EditUActTime();
	void slot_EditDvdtClose();
	void slot_CmbUSetMode(int nIndex);

	void slot_BtnResultAssess();

	void slot_EditVstart();
	void slot_EditVend();
	void slot_EditVstep();
	void slot_EditUdvdtRate();
	void slot_EditVend1();
	void slot_EditPreTime();
	void slot_Editdvdt1Rate();
	void slot_EditVend2();
	void slot_EditBeginVal();
	void slot_EditEndVal();
	void slot_EditStep();
	void slot_EditHoldTime();

	void slot_EditIAtresiaValue();
	void slot_EditIAtresiaStart();
	void slot_EditIAtresiaEnd();
	void slot_EditIAtresiaStep();
	void slot_EditIAtresiaVend2();

	void on_m_UaCheck_clicked(bool checked);
	void on_m_UbCheck_clicked(bool checked);
	void on_m_UcCheck_clicked(bool checked);
	void on_m_UabcCheck_clicked(bool checked);
	
	bool CheckErrorState();
	void GetBinarysParas(CExBaseList *pParas);
	void CheckForBinarys(CExBaseList *pParas, CString strMapID, CString strID);
};

#endif 
