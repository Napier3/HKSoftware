#pragma once

#include "GbSmartGenWzdGlobal.h"

class CSttCmdWzd_CmdDataset : public CExBaseObject
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

//最开始的设计，对于写命令，一个数据集是一个步骤。对于读命令，所有的数据集为一个步骤
class CSttCmdWzd_Step :	public CExBaseList
{
public:
	CSttCmdWzd_Step(void);
	virtual ~CSttCmdWzd_Step(void);

	/*  对于写指令
		在点击下一步时，根据参数是否修改（value与default-value比较），会删除m_pCmdGrpRef中未修改的参数；
		当点击“上一步”时，需要通过m_pCmdGrpBk，还原被删除的参数，以便重新修改
	*/
	CDataGroup *m_pCmdGrpRef;
	CDataGroup *m_pCmdGrpBk;  //备份的参数信息
	long m_nZoneIndex;  //定值区号
	CString m_strDelayBft;  //通讯前延时
	CString m_strDelayAft;  //通讯后延时

	CString m_strType; //步骤类型：_AfterTest_   _BeforeTest_

	//写指令，点击“上一步”时，恢复命令的参数
	void RecoverCmdGrpRef();
};


