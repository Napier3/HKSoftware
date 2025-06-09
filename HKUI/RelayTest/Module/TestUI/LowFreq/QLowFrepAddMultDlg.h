#ifndef QLOWFREPADDMULTDLG_H
#define QLOWFREPADDMULTDLG_H

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
#include "ui_QLowFrepAddMultDlg.h"
#include "../../DataMngr/DataGroup.h"
#include "../../DataMngr/DataMngrGlobal.h"
#include "../../API/GlobalConfigApi.h"
#include "../../UI/Controls/SttCheckBox.h"
#include "QLowFrepResultAssessDlg.h"
#include "SttMultiMacroLowFreqParasDefine.h"
//#include "QLowFrepBinBoutDlg.h"

#define TIPS_DISPLAY_TIME	3000

namespace Ui{
	class QLowFrepAddMultDlg;
}

class QLowFrepAddMultDlg : public QDialog
{
	Q_OBJECT

public:
	Ui::QLowFrepAddMultDlg *ui;

	QLowFrepAddMultDlg(QWidget *parent = 0);
	virtual ~QLowFrepAddMultDlg();

	CDataGroup m_oLowFrepDataGroup;

private:
	void SetApplyTips(CString strTips);
	void timerEvent(QTimerEvent* ev);
protected:

	int m_nTipsTime;//页面提示计时ID

public:
	void InitUI();
	void InitFont();
	void InitConnects();
	void OpenXmlFile();
	void InitDatas();
	void ShowOneChecked(QCheckBox* pCurrentCheckBox, bool state);
public slots:
	void slot_TripFreCheck();
	void slot_FActTimeCheck(bool state);
	void slot_DvdtCloseCheck(bool state);
	void slot_TripILockCheck(bool state);
	void slot_TripULockCheck(bool state);

	void slot_EditFAct();
	void slot_EditFstart();
	void slot_EditFend();
	void slot_EditFstep();
	void slot_EditdvdtRate();
	void slot_EditFActTime();
	void slot_EditFend1();
	void slot_Editdvdt1Rate();
	void slot_EditDvdtClose();
	void slot_EditBeginVal();
	void slot_EditEndVal();
	void slot_EditStep();
	void slot_EditFreqEnd();
	void slot_EditTripILock();
	void slot_EditBeginVal1();
	void slot_EditEndVal1();
	void slot_EditStep1();
	void slot_EditRampTo();
	void slot_EditDvdt2Rate();
	void slot_EditTripULock();
	void slot_EditBeginVal2();
	void slot_EditEndVal2();
	void slot_EditStep2();
	void slot_EditRampTo1();
	void slot_EditDvdt3Rate();
	void slot_EditHoldTime();
	void slot_CmbUSetMode();
	void slot_CmbUVariable();
	void slot_BtnResultAssess();
	void slot_Exit();
	void slot_Ok();

	void GetBinarysParas(CExBaseList *pParas);
	void CheckForBinarys(CExBaseList *pParas, CString strMapID, CString strID);
};

#endif 
