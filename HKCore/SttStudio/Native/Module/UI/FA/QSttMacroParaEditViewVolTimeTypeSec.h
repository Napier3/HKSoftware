#ifndef QSTTMACROPARAEDITVIEWVOLTIMETYPSEC_H
#define QSTTMACROPARAEDITVIEWVOLTIMETYPSEC_H

#include "../Interface/SttMacroParaEditViewOriginal.h"
#include <QWidget>
#include "../SttTestCntrCmdDefine.h"
#include "../../UI/Module/FAParasSetWidget/QSttFAParasSetDialog.h"
#include "../../UI/Module/FACommonSpyWidget/Grid/QSttFAStateSequenceGroupGrid.h"
//#include "../../UI/Module/FACommonSpyWidget/Grid/QSttFATestResultViewGroupGrid.h"
#include "QSttVoltageTimeGroupTestItemWidget.h"


class QSttMacroParaEditViewVolTimeTypeSec : public CSttMacroParaEditViewOriginal
{
	Q_OBJECT

public:
	QSttMacroParaEditViewVolTimeTypeSec(QWidget *parent = 0);
	virtual ~QSttMacroParaEditViewVolTimeTypeSec();

public:
	void InitUI();	
	virtual void GetDatas(CDataGroup *pParas);
	virtual void SetDatas(CDataGroup *pParas);
	virtual BOOL OpenTestTestMngrFile(const CString& strParasFile);
	virtual void UpdateFAParasData(CDataGroup *pParas);
	void UpdateBinDataValue( CDataGroup *pParas,const CString &strID1,const CString &strID2 );
	void UpdateBoutDataValue( CDataGroup *pParas,const CString &strID1,const CString &strID2 );
	CString UpdateDataValue( const CString &strID );
	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	virtual char* GetMacroID(){ return STT_ORG_MACRO_VolTimeTypeSecTest; }
	void SaveXml();
	void InitData();
	virtual void UpdateEventMsg(CEventResult *pCurrEventResult);//处理动作时间动作值
	virtual void UpdateTestResource(BOOL bCreateChMaps);
	void UpdateStateData( CDataGroup *pParas);
	void UpdateResultState(CString strID,const CString &strState);
	//virtual BOOL GetDatas_Reports( CSttReport *pReport,CSttItemBase *pSttItem);
	CString GetSoeAttrValue(CDvmData *pCurrData,const CString &strSearchID);

public:
	QSttVoltageTimeGroupTestItemWidget *m_pTestItemWidget;		   //测试项目
	//QSttFATestResultViewGroupGrid *m_pFATestResultViewGroupGrid;   //测试结果试图表格
	QSttFAStateSequenceGroupGrid *m_pFAStateSequenceGroupGrid;     //状态序列表格
	CDataGroup m_pVolTimeTypeSecData;             
	CDvmValues *m_pMacroTestValues;
	float m_fTimeValues[6];//存放X,Y,Z,S,XL,X2时间
	float fVoltage,fCurrent,fDuration;//存放FA参数设置中的值
	CString	m_strEndBinIn[2];//存放合闸分闸对应的开入
};

extern QSttMacroParaEditViewVolTimeTypeSec* g_pVolTimeTypeSecTestMain;

#endif