#pragma once
#include "../../../../Module/BaseClass/ExBaseList.h"
#include "../../../../Module/DataMngr/DataGroup.h"

class CSttCmdWzd_CmdDataset :
	public CExBaseObject
{
public:
	CSttCmdWzd_CmdDataset(void);
	virtual ~CSttCmdWzd_CmdDataset(void);

	CDataGroup *m_pCmdGrpRef;
	long m_nSelect;   //是否勾选。仅用于read、register指令

	//以下属性，只适用于register指令
	long m_nChange;   //报告类指令，是否变化上送
	long m_nQuqlity;  //报告类指令，是否品质上送
	long m_nPeriod;   //报告类指令，是否周期上送
	long m_nPeriod_Time; //报告类指令，周期上送的周期，单位ms
};


class CSttCmdWzd_CmdDatasets :
	public CExBaseList
{
public:
	CSttCmdWzd_CmdDatasets(void);
	virtual ~CSttCmdWzd_CmdDatasets(void);

	CDataGroup *m_pCmdGrpRef;
	long m_nZoneIndex;  //定值区号
};