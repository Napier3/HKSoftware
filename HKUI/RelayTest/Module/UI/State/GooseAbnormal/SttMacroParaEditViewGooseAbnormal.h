#ifndef STTMACROPARAEDITVIEWGOOSEABNORMAL_H
#define STTMACROPARAEDITVIEWGOOSEABNORMAL_H

#include "../SttMacroParaEditViewState.h"
#include "GooseAbnormalParaset.h"

#define FILE_GOOSEABNORMALTEST		"GooseAbnormalTest"
#define POSTFIX_GOOSEABNORMALTEST   "gatxml"

class QSttMacroParaEditViewGooseAbnormal: public QSttMacroParaEditViewState
{
	Q_OBJECT

public:
    explicit QSttMacroParaEditViewGooseAbnormal(bool bHorizontal = true,QWidget *parent = 0);
	virtual ~QSttMacroParaEditViewGooseAbnormal();

	QGooseAbnormalParaSet* m_pGooseAbnParaWidget;

	virtual void initUI();
	virtual void UpdateStateParas();
	virtual char* GetMacroID(){ return STT_MACRO_ID_GseAbnTest; }

	virtual void SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
		long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub);
	virtual CString GetDefaultParaFile();

	virtual void UpdateGoutTab(BOOL bUpdateList = FALSE);
	void InitGooseAbnormalTmt();

	virtual void UpdateFT3Tab(BOOL bUpdateList = FALSE);

	virtual void OnViewTestStart();
	virtual void OnViewTestStop();
	virtual void initUI_Paras(bool bHorizontal, bool bAbnormal);

	void SetMacroParaEditViewGooseAbnormalFont(); //2022-10-24 sy 设置字体
	virtual void UpdateEventMsg(CEventResult *pCurrEventResult);//dingxy 20240522 处理动作时间动作值操作

};

CIecCfgGooseDataBase* Gloabal_GetGooseAbnDataByIndex(int nGroupIndex);
BOOL Global_SetGooseAbnormalData(CIecCfgGooseDataBase *pIecCfgGooseData,tmt_StatePara *pStatePara);
BOOL Global_SetGooseAbnormalData(long nGroupIndex,tmt_StateParas *pStateParas);
BOOL Global_SetGooseAbnormalData(CIecCfgGooseDataBase *pIecCfgGooseData,tmt_StateAbnormalGOOSE *pAbnormalGoose);
void Global_SetGooseAbnormalTmtValues_ByIecConfig(tmt_StateAbnormalGOOSE *pAbnormalGoose,BOOL bJudgeMacEmpty);//参数2判断Mac地址是否为空,如果为空才赋值

extern QSttMacroParaEditViewGooseAbnormal* g_pGooseTest;

#endif // STTMACROPARAEDITVIEWGOOSE_H
