#ifndef SMVABNORMALPARASET_H
#define SMVABNORMALPARASET_H

#include <QWidget>
#include <QDialog>
#include "../../../../Module/SttTest/Common/Abnormal/tmt_abnormal_test.h"
#include "../../Controls/SttLineEdit.h"
#include "ui_SmvAbnormalParaset.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfg92Data.h"
#include "../../../SttTest/Common/tmt_state_test.h"


class QSmvAbnormalParaset : public QWidget
{
	Q_OBJECT

public:
	Ui::QSmvAbnormalParaset *ui;

	/*explicit*/ QSmvAbnormalParaset(QWidget *parent = NULL);
	~QSmvAbnormalParaset();

	void setData(tmt_StateAbnormalSMV *pSMV,tmt_StateParas *pStateParas);
	void initcmb_APPIDbyBlockData();

	void startInit();
	void stopInit();
	void SetSmvAbnormalParasetFont();

//	CIecCfg92Data* GetSMVDataByIndex(int nFindIndex);
//	BOOL SetAbnSmvMessage(CIecCfg92Data* pIecCfgSmvData);

protected slots:
	void slot_cmb_APPIDChanged(int index);
	void slot_cmb_sendtypeChanged(int index);
	void slot_lne_sendcircleChanged();
	void slot_lne_sendcircleKeyBoard();
	void slot_lne_circlepersecondChanged();
	void slot_lne_circlepersecondKeyBoard();
	void slot_lne_sendtimeChanged();
	void slot_lne_sendtimeKeyBoard();
	void slot_ck_losestepChanged(int state);
	
	//void slot_edit_Engchanged(QSttLineEdit* pEditLine, bool bIsNor);
	//void slot_edit_Digchanged(QSttLineEdit* pEditLine, bool bIsNor);
	void slot_lne_flypointvoltChanged();
	void slot_lne_flypointvoltKeyBoard();
	void slot_lne_flypoitcurrentChanged();
	void slot_lne_flypointcurrentKeyBoard();
	void slot_lne_jitterChanged();
	void slot_lne_jitterKeyBoard();
	void slot_lne_errcmptChanged();
	void slot_lne_errcmptKeyBoard();
	void slot_lne_offsettimeChanged();
	void slot_lne_offsettingKeyBoard();
	void slot_lne_modifytimeChanged();
	void slot_lne_modifytimeKeyBoard();
	void slot_lne_indexerrChanged();
	void slot_lne_indexerrKeyBoard();

	void slot_radio_lostClicked();
	void slot_radio_flypointClicked();
	void slot_radio_jitterClicked();
	void slot_radio_errcmptClicked();
	void slot_radio_delayoffsetClicked();
	void slot_radio_delaymodifyClicked();
	void slot_radio_indexerrClicked();
	void slot_radio_qualityinvalidChanged();

	void slot_CkUabcIabcClicked();

//	void slot_ChannelNumOk(QList<int> &channelnum);
	void slot_ValidPoint(QList<bool> &pointlist);

	void slot_pbn_AbnomalPointSet();
	void slot_ptn_ChannelSelect();
	void slot_pbn_MessageSet();
	void slot_checkBox_SelOrgPkgSet_changed(int nState);
	void slot_pbn_qualitySet();

	void slot_radio_noClicked();
	void slot_QualityParaChanged(QList<int> &listQuality);

private:
	void InitUI_BySendType();
	void initConnect();
	void initData();
	void InitLanguage();

	tmt_StateAbnormalSMV *m_pAbnormalSMV;
	tmt_StateParas *m_pStateParas;
	
//	hqyAbnormalState::abnormalstate* m_data;
//	hqyIEC61850_9_2_Setting::IEC61850_9_2* m_blockdata;

	QList<int> m_ovalidPointNum;
	QList<bool> m_oabnomalPointEnabled;
//	QList<int> m_ochannelNum;
//	QList<int> m_olistAppIDs;
	QList<int> m_olistQualityParas;

	int m_nCurIndex;

    QStringList m_sendtype;
};

extern CFont *g_pSttGlobalFont;  

#endif // SMVABNORMALPARASET_H
