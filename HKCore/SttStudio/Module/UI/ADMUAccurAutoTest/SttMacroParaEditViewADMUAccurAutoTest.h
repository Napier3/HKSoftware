#ifndef STTMACROPARAEDITVIEWADMUACCURAUTOTEST_H
#define STTMACROPARAEDITVIEWADMUACCURAUTOTEST_H

#include "../Interface/SttMacroParaEditViewOriginal.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

class QSttMacroParaEditViewAdmuAccurAutoTest : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	explicit QSttMacroParaEditViewAdmuAccurAutoTest(QWidget *parent = 0);
	virtual ~QSttMacroParaEditViewAdmuAccurAutoTest();

public:
	virtual char* GetMacroID(){ return STT_ORG_MACRO_MUAccurAutoTest; }
	void InitUI();
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas);
	virtual BOOL OpenTestTestMngrFile(const CString& strParasFile);
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	void GetCheckBoxValue(CDataGroup *pParas,QCheckBox * pCheckBox,CString strID);
	void GetLineEditValue(CDataGroup *pParas,QLineEdit * pLineEdit,CString strID);
	void GetGroupBoxCheckable(CDataGroup *pParas,QGroupBox * pGroupBox,CString strID);
	void SaveADMUAutoTestParasXml();
	CString ProcessString(CString &str);//�����ַ�����ȷ���䳤��Ϊ3�����Ƴ��ٷֺ�
	virtual BOOL SetValues_dsRcdStep6U6I(CDvmDataset *pDsRcdStep6U6I);


protected slots:	
	void slot_ParasSetPushButton_Clicked();
 	void slot_FirstHarmTimeseditFinished();
 	void slot_LastHarmTimeseditFinished();
	void slot_CheckBoxStateChanged(int);
	void slot_LineEditFinished();
	void slot_GroupBoxtoggled(bool);

public:
	CDataGroup m_pADMUAutoTestDataGroup;
	QLineEdit *m_pFirstHarmTimesLineEdit;
	QLineEdit *m_pLastHarmTimesLineEdit;
	QPushButton *m_pParasSetBtn;
	QList<QCheckBox*> m_pAllCheckBoxList;
	QList<QLineEdit *> m_pAllLineEditList;
	QList<QGroupBox *> m_pAllGroupBoxList;

};
extern QSttMacroParaEditViewAdmuAccurAutoTest* g_pAdmuAccurAutoTest;

#endif 