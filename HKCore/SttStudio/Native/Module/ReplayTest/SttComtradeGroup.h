//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttParas.h  CSttParas

#pragma once

#include "SttCmtrdCfgDefineGlobal.h"
#include "../../../Module/DataMngr/DataGroup.h"
#include "../../../Module/Record/RtMemBuffer/MemBuffer_Float.h"

#if 0

class CSttComtradeGroup : public CDataGroup
{//可以描述模块、通道
public:
	CSttComtradeGroup();
	virtual ~CSttComtradeGroup();

public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTTMAPGROUP;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmtrdCfgDefineXmlRWKeys::CSttMapGroupKey();     }
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
    virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
    virtual CExBaseObject* CreateNewChild(long nClassID/ *, BOOL &bAddToTail* /);

public:
	//如果描述通道,最大值，回放通道缓存才有效
	double m_fMaxAbs;	//最大绝对值
	CComplexMemBuffer_Float *m_pReplayBuf;//回放通道缓存

public:
	//如果描述通道
	double CalcChannelMaxValue();
	BOOL IsChannelSelected();
	//初始化通道回放缓存
	void InitChReplayBuf(long nMaxPoints);
	//清空通道回放缓存
	void ResetChReplayBuf();

	//如果描述模块
	BOOL IsModuleType_U()	{	return (m_strDataType == _T("U"));}
	BOOL IsModuleType_I()	{	return (m_strDataType == _T("I"));}
	BOOL IsModuleSelected();
	double CalcChMaxValueByIndex(long nChIndex);
	double GetModuleMaxValue();
	void ScalingModuleMaxValue(float fK);
	void InitModuleReplayBuf(long nMaxPoints);
	void ResetModuleReplayBuf();

	long GetMaxPoints();//获取当前通道总点数
	long GetValue_DataA();
	long GetValue_DataB();
	double GetValue_DataK();
};

///////////////////////////////////

CDvmData* Stt_SetDataAttr(CDataGroup *pGroup,const CString &strID, const CString &strValue);
CDvmData* Stt_SetDataAttr(CDataGroup *pGroup,const CString &strID, long nValue);
CDvmData* Stt_SetDataAttr(CDataGroup *pGroup,const CString &strID, double fValue, long nDecimal);

BOOL Stt_GetDataAttr(CDataGroup *pGroup,const CString &strID, CString &strValue);
BOOL Stt_GetDataAttr(CDataGroup *pGroup,const CString &strID, long &nValue);
BOOL Stt_GetDataAttr(CDataGroup *pGroup,const CString &strID, double &fValue,double fDefaultVal=0);
BOOL Stt_GetDataAttr(CDataGroup *pGroup,const CString &strID, float &fValue,float fDefaultVal=0);
#endif
