#ifndef STTMACROPARAEDITVIEWANTISHAKETIME_H
#define STTMACROPARAEDITVIEWANTISHAKETIME_H
#include "../Interface/SttMacroParaEditViewOriginal.h"
#include "../SttTestCntrCmdDefine.h"
#include "Grid/QSttAntiShakeTimeTestItemsGroupGrid.h"
#include "Grid/QSttAntiShakeTimeDinEventGroupGrid.h"
#include "../Module/CommonCtrl_QT/QLongLineEdit.h"
#include "../../../Module/BaseClass/QT/ExBaseListComboBox.h"
#include <QPushButton>
#define STT_ANTISHAKE_TIME_INIT_INTERVAL_SELECT		 "InitIntervalSelect"              //���ѡ��
#define STT_ANTISHAKE_TIME_INIT_TEST_OBJECT			 "InitTestObject"				   //���Զ���
#define STT_ANTISHAKE_TIME_ANTI_SHAKE_TIME             "AntiShakeTime"				   //����ʱ��
#define STT_ANTISHAKE_TIME_SOE_RESOLUTION			 "SOEresolution"                   //SOE�ֱ���
#define STT_ANTISHAKE_TIME_INIT_BOUT_SET			 "InitBoutSet"                     //��������
#define STT_ANTISHAKE_TIME_INIT_STATE1				"InitState1"                       //��ʼ״̬
#define STT_ANTISHAKE_TIME_ITEM_NUM					"ItemNum"						   //����������

#define STT_ANTISHAKE_TIME_Dataset_ID				"Din"								//ң��

#define STT_ANTISHAKE_TIME_TESTITEM_NUMBER			 10					                //����������

class QSttMacroParaEditViewAntiShakeTime : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	QSttMacroParaEditViewAntiShakeTime(QWidget *parent = 0);
	virtual ~QSttMacroParaEditViewAntiShakeTime();

public:
    virtual char* GetMacroID(){ return STT_ORG_MACRO_AntiShakeTimeTest; }

 	void InitUI();						 //��ʼ������
	void InitFont();                     //��ʼ������
	void InitConnections();              
 	void InitComboBox();                 //��ʼ��������
	void SaveXmlParas();
	void OpenXmlFile();
	void UpDataTestItemName();
	void UpDateItemNumValue(int nNewValue);
	void InitData();
	void DeleteIntervalListDatas();
	void InitIntervalListDatas();
	void InitTestObjectListDatas();
	void InitBoutSetListDatas();
	void UpDateButtonState();
	void OpenXml();
	virtual void UpdateDeviceModelRef();
	void DelCmbBoutSetData();
	void AddCmbBoutSetData(QList<QString> oList);
	int FindBoutChans(CString strName);
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas);
	virtual void ShowReport(CDvmValues *pValues);
	virtual void AddShowSoeReports(CDvmDataset *pSoeRptDataset);
	virtual void UpdateDinCount(CDvmValues *pValues,CDvmDataset *pSoeRptDataset,CString strItemID);
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	void GetSelectObject();
	virtual BOOL GetDatas_Reports( CSttReport *pReport,CSttItemBase *pSttItem);


public:
	QLabel *m_pLabelInterval;         //���ѡ���ǩ
	QLabel *m_pLabelTestObject;       //���Զ����ǩ
	QLabel *m_pLabelAntiShakeTime;    //����ʱ���ǩ
	QLabel *m_pLabelTimeMsec;         //����ʱ������ǩ
	QLabel *m_pLabelSOEResolution;	  //SOE�ֱ��ʱ�ǩ
	QLabel *m_pLabelSOEMsec;		  //SOE�ֱ��ʺ����ǩ
	QLabel *m_pLabelBoutSet;		  //��������
	QLabel *m_pLabelInitState;		  //��ʼ״̬
	CExBaseListComboBox *m_pCmbIntervalSelect;  //���ѡ��������
	CExBaseListComboBox *m_pCmbTestObject;	  //���Զ���������
	CExBaseListComboBox *m_pCmbBoutSet;		  //��������������
	QComboBox *m_pCmbInitState;		  //��ʼ״̬������
	QSttLineEdit *m_pEditAntiShakeTime;  //����ʱ��༭��
	QSttLineEdit *m_pEditSOEResolution;  //SOE�ֱ��ʱ༭��
	QPushButton *m_pBtnAddTestItem;   //��Ӳ����ť
	QPushButton *m_pBtnDeleteTestItem;//ɾ�������ť

 	QSttAntiShakeTimeTestItemsGroupGrid *m_pTestRecordsGroupGrid;  //���Լ�¼���
    QSttAntiShakeTimeDinEventGroupGrid *m_pDinEventGroupGrid;      //ң��ʱ����

	CExBaseList m_oTestObjectList;	     //���Զ���
	CExBaseList m_oIntervalList;         //���ѡ��
	CExBaseList m_oBoutSetList;		     //��������
 	CDataGroup m_oTestRecordsDataGroup;  //���Լ�¼������ݶ���
	QList<CString> m_SelectTestObjetcList;


public slots:
	void slot_AddTestItem();
	void slot_DeleteTestItem();

	void slot_CmbIntervalSelect(int nIndex);
	void slot_CmbTestObject(int nIndex);
	void slot_CmbBoutSet(int nIndex);
	void slot_CmbInitState(int nIndex);

	void slot_EditAntiShakeTime();
	void slot_EditSOEResolution();
	void slot_btn_ClearClearEventRecordsClicked();
};


extern QSttMacroParaEditViewAntiShakeTime* g_pAntiShakeTime;


#endif 
