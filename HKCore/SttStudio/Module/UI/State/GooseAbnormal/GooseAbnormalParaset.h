#ifndef GOOSEPARASET_H
#define GOOSEPARASET_H

#include <QWidget>
#include "ui_GooseAbnormalParaset.h"

#include <QStringList>
#include <QLineEdit>
#include "../../../../Module/SttTest/Common/tmt_state_test.h"
#include "../../Controls/SttLineEdit.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgGooseDataBase.h"

class QGooseAbnormalParaSet : public QWidget
{
	Q_OBJECT

public:
	QGooseAbnormalParaSet(QWidget *parent = 0);
	~QGooseAbnormalParaSet();

	void setData(tmt_StatePara* pStatePara,tmt_StateParas* pStateParas);//类的对外接口
	void setName(QString strName);
	void setStateTime(float fvalue);
	void UpdateStateTimeUI();
	void UpdateStateNameUI();

	void initcmb_APPIDbyBlock();

	CIecCfgGooseDataBase* GetGooseAbnDataByIndex(int nFindIndex);
	BOOL SetAbnGooseMessage(CIecCfgGooseDataBase *pIecCfgGooseData);
	void initGooseOrigPkg();

private:
	void init();
	void initConnect();
	void initData();
	void SetGooseAbnormalFont();//20230831 cl 设置字体
        void InitLanguage();
protected slots:
	void slot_ckYMAC_clicked(bool b);
	//void slot_ckYMAC_clickedKeyBoard();
	//void slot_edit_changed(QSttLineEdit* pEditLine, bool bIsNor);
	void slot_lneYMAC_editingFinished();
	void slot_lneYMAC_clickedKeyBoard();

	void slot_ckMMAC_clicked(bool b);
	void slot_lneMMAC_editingFinished();
	void slot_lneMMAC_clickedKeyBoard();

	void slot_ckGcRef_clicked(bool b);
	void slot_lneGcRef_editingFinished();
	void slot_lneGcRef_clickedKeyBoard();

	void slot_ckGoID_clicked(bool b);
	void slot_lneGoID_editingFinished();
	void slot_lneGoID_clickedKeyBoard();

	void slot_ckDataSet_clicked(bool b);
	void slot_lneDataSet_editingFinished();
	void slot_lneDataSet_clickedKeyBoard();

	void slot_ckSetVerion_clicked(bool b);
	void slot_lneSetVerion_editingFinished();
	void slot_lneSetVerion_clickedKeyBoard();

	void slot_ckSt_clicked(bool b);
	void slot_lneSt_editingFinished();
	void slot_lneSt_clickedKeyBoard();

	void slot_ckSq_clicked(bool b);
	void slot_lneSq_editingFinished();
	void slot_lneSq_clickedKeyBoard();

	void slot_ckTTl_clicked(bool b);
	void slot_lneTTl_editingFinished();
	void slot_lneTTl_clickedKeyBoard();

	void slot_ckAPPID_clicked(bool b);
	void slot_lneAPPID_editingFinished();
	void slot_lneAPPID_clickedKeyBoard();

	void slot_ckWT_clicked(bool b);
	void slot_cbWT_currentIndexChanged(int index);
	void slot_ckTest_clicked(bool b);
	void slot_cbTest_currentIndexChanged(int index);
	void slot_ckVlan_clicked(bool b);
	void slot_lneVlan_editingFinished();
	void slot_lneVlan_clickedKeyBoard();

	void slot_ckNet_clicked(bool b);
	void slot_lneNet_editingFinished();
	void slot_lneNet_clickedKeyBoard();

	void slot_lneVlanPriority_editingFinished();
	void slot_lneVlanPriority_clickedKeyBoard();

	void slot_lneTimeQuality_editingFinished();
	void slot_lneTimeQuality_clickedKeyBoard();

	void slot_ComboxSelChanged_GroupIndex(int nCurIndex);
	
	void slot_btnAdd_clicked();
	void slot_btnDelete_clicked();
	void slot_btnClear_clicked();
	void slot_lneStateName_editingFinished();
	void slot_lneStateTime_editingFinished();
	void slot_lneStateTime_clickedKeyBoard();

signals:
	void sig_delete();
	void sig_add();
	void sig_clearResult();
	void sig_NameChanged(bool bSetStateName);


private:
	Ui::QGooseAbnormalParaSet ui;
	tmt_StatePara* m_pCurrStatePara;
	tmt_StateAbnormalGOOSE* m_pAbnormalGOOSE;
	tmt_StateParas* m_pStateParas;
	QStringList m_strList;
};

#endif // GOOSEPARASET_H
