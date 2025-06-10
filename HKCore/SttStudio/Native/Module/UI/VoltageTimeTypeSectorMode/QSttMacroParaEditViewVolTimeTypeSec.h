#include "ui_QSttFAParasSetDialog.h"
#include "../Interface/SttMacroParaEditViewOriginal.h"
#include "../Controls/SttLineEdit.h"
#include <QWidget>
#include "../Module/GooseParaWidget/qgooseparawidget.h"
#include "../SttTestCntrCmdDefine.h"
#include "../Module/FT3Widget/FT3OutParaWidget.h"
#include "../../UI/Module/FAParasSetWidget/QSttFAParasSetDialog.h"
#include "../../UI/Module/FACommonSpyWidget/Grid/QSttFAStateSequenceGroupGrid.h"
#include "../../UI/Module/FACommonSpyWidget/Grid/QSttFATestResultViewGroupGrid.h"
#include "../../SttTest/Common/FAParasSet/tmt_fa_Paras_set.h"
#include "QSttVoltageTimeGroupTestItemWidget.h"


class QSttMacroParaEditViewVolTimeTypeSec : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	QSttMacroParaEditViewVolTimeTypeSec(QWidget *parent = 0);
	virtual ~QSttMacroParaEditViewVolTimeTypeSec();

public:
	void InitUI();
	void UpdateFaParasSet();
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas);//��Ҫ�Ľṹ�������Լ������е�����

	virtual PTMT_PARAS_HEAD CreateTestParas(const char * pszMacroID);
	virtual PTMT_PARAS_HEAD GetTestParas() { return m_oTmtFaParasSet;}
	virtual char* GetMacroID(){ return STT_ORG_MACRO_VolTimeTypeSecTest; }
	virtual void SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
		long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub);//���л����Բ����ṹ��,������Ҫ����

	virtual void startInit();//�Խ���Ŀؼ�����ʧ��״̬����
	virtual void stopInit();
	virtual void OnViewTestStart();//���Կ�ʼ�������Ӧ
	virtual void OnViewTestStop();
	void SetData(PTMT_PARAS_HEAD pCur);

	QTabWidget *m_pVolTimeTypeSectorModeTab;					   //��ѹʱ���ͷֶ�ģʽTab
	QSttVoltageTimeGroupTestItemWidget *m_pTestItemWidget;		   //������Ŀ
	QSttFAParasSetDialog *m_pSttFAParasSetDialog;				   //FA��������

	QSttFATestResultViewGroupGrid *m_pFATestResultViewGroupGrid;   //���Խ����ͼ���
	QSttFAStateSequenceGroupGrid *m_pFAStateSequenceGroupGrid;     //״̬���б��
	QSplitter* m_pVolTimeTypeSecSplitter;       //�и�

	QHBoxLayout* m_pTestItemLayout;			    //������Ŀ����
	QHBoxLayout* m_pTestResulLayout;			//���Խ����ͼ����
	QHBoxLayout* m_pStateLayout;				//״̬���в���

	QTabWidget* m_pTestWidget;					//������Ŀ��ǩҳ
	QTabWidget* m_pFACommonSpyWidget;		    //���Խ����ͼ��״̬���б�ǩҳ

	QWidget* m_pTestResultViewWidget;           //���Խ����ͼ
	QWidget* m_pStateSequenceWidget;   		    //״̬����

	CDataGroup m_TotalDynamicList;              //���Խ����ͼ����
	tmt_FaParasSetTest* m_oTmtFaParasSet;
};

extern QSttMacroParaEditViewVolTimeTypeSec* g_pVolTimeTypeSecTestMain;

