#ifndef MESSAGESET_H
#define MESSAGESET_H

#include <QDialog>
#include "ui_SmvAbnormalMessageset.h"
#include "../../Module/SttTest/Common/Abnormal/tmt_abnormal_test.h"
#include "ui_SmvAbnormalMessageset.h"
#include "../../../../../Module/OSInterface/OSInterface.h"


class QSmvAbnormalMessageSet : public QDialog
{
	Q_OBJECT

public:
	Ui::SmvAbnormalMessageSet *ui;

	QSmvAbnormalMessageSet(tmt_SmvAbnormalMsg* pSMVMsg,bool RefrTm,QWidget *parent = 0);
	~QSmvAbnormalMessageSet();

private slots:
	void slot_edit_changed(QSttLineEdit* pEditLine, bool bIsNor);
	void slot_lne_sourceMacChanged();
	void slot_lne_destMACChanged();
	void slot_lne_VIanIDChanged();
	void slot_lne_VIanPriorityChanged();
	void slot_lne_nettypeChanged();
	void slot_lne_APPIDChanged();
	void slot_lne_SVIDChanged();
	void slot_cmb_synchroChanged();
	void slot_lne_versionChanged();
	void slot_lne_sampledelayChanged();
	void slot_lne_datsetChanged();
	void slot_lne_RefrTmChanged();

	void slot_lne_sourceMacKeyBoard();
	void slot_lne_destMACKeyBoard();
	void slot_lne_VIanIDKeyBoard();
	void slot_lne_VIanPriorityKeyBoard();
	void slot_lne_nettypeKeyBoard();
	void slot_lne_APPIDKeyBoard();
	void slot_lne_SVIDKeyBoard();
	void slot_lne_datsetKeyBoard();
	void slot_lne_versionKeyBoard();


	void slot_pbn_OkClicked();
	void slot_pbn_Cancle();

private:
	void initConnect();
	void initData();
	void SetSmvAbnormalMessageFont();
	void InitLanguage();
	tmt_SmvAbnormalMsg* m_pSMVMsg;
	bool brefrtm;
};

extern CFont *g_pSttGlobalFont;  

#endif // MESSAGESET_H
