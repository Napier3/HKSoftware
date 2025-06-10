// RtVariables.h: interface for the CRtVariables class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTVARIABLES_H__C0F945B6_69F9_4670_B757_9D8A74B3638D__INCLUDED_)
#define AFX_RTVARIABLES_H__C0F945B6_69F9_4670_B757_9D8A74B3638D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ExBaseList.h"
#include "RtMultiVariable.h"
#include "RtSingleVariable.h"
#include "RtBinaryVariable.h"
#include "RtComplexVariable.h"

// #define _CAL_USE_REF_VARIABLE_

class CRtVariables : public CExBaseList  
{
public:
	CRtVariables();
	virtual ~CRtVariables();

//属性
public:
	//关键字属性
// 	static const char *g_pszKeyVariables;
// 	static const char *g_pszKeyRefVariable;

	CString m_strRefVariable;//基准通道

	//参数计算相关属性
	CMemBuffer_UShort *m_pAttrTimeBuffer;   //时间缓冲区

	//和参数计算缓存位置有关的变量，fdp add 2010.4.15
	__int64 m_n64AttrReadBeginPos;
	DWORD  m_dwReadBeginPos;
	DWORD m_dwReadEndPos;
	DWORD m_dwTimeReadBeginPos;
	DWORD m_dwTimeReadEndPos;
	
	//自适应功能的通道源
	CRtSingleVariable *m_pUSourceVariable;
	CRtSingleVariable *m_pISourceVariable;
	CRtSingleVariable *m_pUdcSourceVariable;
	CRtSingleVariable *m_pIdcSourceVariable;
	CRtBinaryVariable *m_pBSourceVariable;

	//自适应创建三种multi的channal名称
	char *m_pszAutoMultiChsName[AUTO_MULTI_CH_NAME_COUNT];
	
	//判断启动的链表
	CExBaseList m_listAnalogInstAttrs;//模拟量瞬时值属性链表
	CExBaseList m_listBinaryInstAttrs;//开关量瞬时值链表
	CExBaseList m_listAnalogAttrs;//模拟量非瞬时值属性

	//试验中的模拟单通道、开关量链表
	CExBaseList m_oListAnologVariable;
	CExBaseList m_oListBinaryVariable;
	
	//试验中的模拟交流电压通道链表
	CExBaseList m_oListACVariable_U;

	//试验中的模拟交流电流通道链表
	CExBaseList m_oListACVariable_I;

	//克隆的CRtVariables
	CRtVariables* m_pClone;

//方法
public:
	//重载的方法
	virtual UINT GetClassID();
#ifdef _record_use_all_mode_
	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);	
	virtual const char* GetXmlElementKey();
	virtual long WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement);
	BOOL ReadSetsValueXml(MSXML::IXMLDOMNodeListPtr &oNodes);
	BOOL WriteSetsValueXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oParent);
#endif
// 	virtual CExBaseObject* CreateNewChild(LPCTSTR pszClassID);
// 	virtual CExBaseObject* CreateNewChild()					{	return NULL;    }
// 	virtual CExBaseObject* CreateNewChild(long nClassID)	{	return NULL;    }

	CRtSingleVariable* FindVariable(const CString &strID);
	CRtVariable* FindByRefRecordData(CExBaseObject *pRefRecordData);
	long GetCountByPhaseID(const CString &strPhaseID, const CString &strType);

	double CalAngleOffset(long nRefPos, long nCurrPos, long nBuffLen, long nSampleRate);

	//参数计算
	void CalValuesRealTime(PRECORD_CAL_LEN_PARA pCalLenPara, DWORD nSampleGap, DWORD dwSampleRate, BOOL bCalPointByPoint=TRUE);
	void CalValuesRealTimeEx(PRECORD_CAL_LEN_PARA pCalLenPara, DWORD nSampleGap, DWORD dwSampleRate, BOOL bCalPointByPoint=TRUE);
	void CalValuesRealTimeEx(CRtVariable * pdVariable, PRECORD_CAL_LEN_PARA pCalLenPara, DWORD nSampleGap, DWORD dwSampleRate, BOOL bCalPointByPoint=TRUE);

	//没有用到？？？？
	BOOL AttrCalPosInFrequencyCalRage(DWORD dwAttrCalBeginPos, DWORD dwAttrCalPoints);

	//？？？？？？？
	BOOL AttrCalPosInFrequencyCalRage2(DWORD dwAttrCalBeginPos, DWORD dwAttrCalEndPos);

	//获得计算频率的数据范围，返回值：获得成功为TRUE,反之FALSE
	//BOOL GetFrequencyCalPos(PRECORD_CAL_LEN_PARA pCalLenPara, long &nCalBuffer1Pos, long &nCalBuffer1Len , long &nCalBuffer2Pos, long &nCalBuffer2Len, BOOL bCalUseRecordBuffer);
	//BOOL GetFrequencyCalPos(CRtVariable *pRtVariable,PRECORD_CAL_LEN_PARA pCalLenPara, long &nCalBuffer1Pos, long &nCalBuffer1Len , long &nCalBuffer2Pos, long &nCalBuffer2Len, BOOL bCalUseRecordBuffer);
	//根据起点查找当前频率计算的范围
	BOOL GetFrequencyCalPos2(PRECORD_CAL_LEN_PARA pCalLenPara, long &nCalBuffer1Pos, long &nCalBuffer1Len , long &nCalBuffer2Pos, long &nCalBuffer2Len,long nBegin = 0);
	
	//参数计算
	void CalInstValue(long nBegin,BOOL bCalUseRecordBuffer);//fdp add 2010.10.8,在数据不够计算其它参数的时候计算瞬时值
	BOOL CalValues(PRECORD_CAL_LEN_PARA pCalLenPara, long nBeginPos, DWORD dwSampleRate,BOOL bCalUseRecordBuffer, BOOL bCalOtherValues);//fdp add 2010.6.3,设置起点计算属性
	BOOL CalValuesFnom(PRECORD_CAL_LEN_PARA pCalLenPara, long nBeginPos, DWORD dwSampleRate,BOOL bCalUseRecordBuffer, BOOL bCalOtherValues);//fdp add 2010.6.3,设置起点计算属性
	BOOL CalValuesFnom_Quick(PRECORD_CAL_LEN_PARA pCalLenPara, long nBeginPos, DWORD dwSampleRate,BOOL bCalUseRecordBuffer, BOOL bCalOtherValues);//fdp add 2010.6.3,设置起点计算属性
	BOOL CalValues_PeakVellay(PRECORD_CAL_LEN_PARA pCalLenPara, long nBeginPos, long nUseLength, DWORD dwSampleRate,BOOL bCalUseRecordBuffer, BOOL bCalOtherValues);//fdp add 2010.6.3,设置起点计算属性
	void CalOtherValues(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bCalUseRecordBuffer);
	void CalStaticValues(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bAddFrequency, BOOL bCalUseRecordBuffer);//计算静态属性参数
	void CalStaticValues_Quick(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bAddFrequency, BOOL bCalUseRecordBuffer);//计算静态属性参数
	void CalValues_PeakVellay(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bAddFrequency, BOOL bCalUseRecordBuffer);//计算静态属性参数
	void CalFrequncy(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bCalUseRecordBuffer);//计算频率	
	void CalFrequncy(CRtVariable * pdVariable, PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bCalUseRecordBuffer);//计算频率	
	void AddAttrValue();//将计算得到的属性参数添加到属性缓存中
	void CalFaultValues(long nBeginPos, long nLen, long nCyclePoints);

	//判断启动
	BOOL JudgeStartupAnalogInst(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, long &nStartup);//录波模拟量瞬时值启动判断
	BOOL JudgeStartupBinaryInst(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, long &nStartup);//录波开关量瞬时值启动判断
	BOOL JudgeStartupAnalog(long &nStartup);//除瞬时值外的录波启动判断

	CRtVariables* GetSingleAndBinaryVariables();
	virtual double* GetValueRefByID(const CString &strID);
	virtual double* GetMutationValueRefByID(const CString &strID);	
	virtual double* GetAttrValueRefByID(const CString &strID);

	void AdjustStaticAttrs();//调整静态属性:包括频率、有效值、相位、基波有效值、基波相位
	BOOL BuildExpression();//构建脚本表达式，包含启动判断脚本和复合通道计算脚本
	void InitBufferMngr(CRtMemBufferMngr *pRtMemBufferMngr);//添加通道缓存、属性时间缓存
	void InitAttrsBuffer(long nPoints);
	BOOL InitDataAttributeCalFunc(BOOL bCalUseRecordBuffer);
	void InitVariablesFIFOIndex();
	void ResetCalPos();
	CRtVariable* FindByVariableID(const char* pstrAttrID);
	CRtVariable* FindByAttrBufferID(const char* pstrAttrBufferID);
	CRtVariable* FindByRecordBufferID(const char* pstrRecordBufferID);
	CRtVariable* FindByBufferID(const char* pstrBufferID);
	CRtVariable* FindByHDChIndex(int nHDChIndex);
	long GetSingleVariableCountUsed();
	long GetBinaryVariableCountUsed();
	long GetVariableCountUsed();
	//在停止后获得各种缓存的读取范围,fdp add 2010.4.15
	void SetFinalDataPos();
	BOOL SetFinalDataRange(unsigned short* pTimeBuffer,long nBegin,long nEnd,__int64 n64AtttrFirst,__int64 n64RecordFirst,DWORD& dwTimeBufferBegin);
	void ResetUseAndSpy();
	void ResetAttrSpyState();
	
	BOOL IsChannelInUse(const CString &strChID);

	//初始化模拟、开关通道链表
	void InitAnologBinaryVariableList();

	//初始化交流模拟电压、交流模拟电流链表,发变组实验专用
	void InitACAnologVariableList();
	
	//定值表格中根据硬件变换器的通道索引获取对应试验通道
	CRtSingleVariable* GetSingleVariableByTranChannelIndex(int nAttachedTranCHIndex);

	//根据HD-CHIndex获取对应的单通道
	CRtSingleVariable* GetSingleVariableByHDIndex(int nHDIndex);
	
	//获取第一个使用的SingleVariable，用于作为默认触发通道
	CRtSingleVariable* GetFirstSingleWithUseState();

public:
	//根据通道名称设置RefVariable
	void SetRefVariableByVariableName(const CString& strName);

	long GetACUSingleVariableCount();
	long GetACISingleVariableCount();
	long GetSingleVariableCount();
	long GetBinaryVariableCount();
	long GetComplexVariableCount();
	long GetMultiVariableCount();
	long GetVariableCountWithRecordBuffer();
	CRtVariable * GetRefVariable()   {    return m_pRefVariable;    }
	void SetRefVariable(CRtVariable* pVariable)	;	
	CMemBufferInterface* GetRefBuffer()   {    return m_pRefBuffer;   }
	void SetVariable(CRtVariable* pVariable,long nIndex);

	//根据通道获取该通道在单通道、开关通道中的索引
	long GetAnalogIndex(CRtSingleVariable* pVar);
	long GetBinaryIndex(CRtBinaryVariable* pVar);

	//自适应功能，
	//备份克隆通道源
	void BackCloneSources();
	virtual long RTUpdateOwnByAutofit(HDINFO &oHDInfo);

	//自适应创建MultiVariable
	void AutofitCreateMultiVariable();
	void AutofitCreateMultiVariable_3U();
	void AutofitCreateMultiVariable_3I();
	void AutofitCreateMultiVariable_UI();

	//初始化自适应创建MultiVariable的channal的名称
	void InitAutofitMultiVariable_ChName(const CString &strName);
	void InitAutoMultiVariable_3U_ChName();
	void InitAutoMultiVariable_3I_ChName();
	void InitAutoMultiVariable_UI_ChName();
	
	//重设基准通道(读取完定值)
	void UpdateRefVariableByVariableUse();
	void InitRefVariable();

	//用于根据在线录波监视表格设置属性监视状态
	void SetAttrSpyStateByVariableSpyConfig(const CString & strAttrID, long nAttrSpyState);

	//判断是否与其他通道名称同名
	BOOL IsHaveSameNameVariable(CRtVariable* pVariable);

	//初始化参考通道
	void ValidateRefVariable(BOOL bCalUseRecordBuffer);

	//克隆Variables
	void CloneVariables(CRtVariables* pSrc,CMemBuffer_UShort** pAttachBuffer = NULL);
	void AdjustRefVariable(MR1200SYSANALYSEMNGR &oMR1200SysAnalyseMngr);

	//设置启动点位置
	void SetStartupPos(long nPos)	{	m_nStartupPos = nPos;	}

	//根据启动点位置计算第一个点位置
	void CalBeginPosByStartupPos(long nStartupPos, DWORD nSampleGap, DWORD dwSampleRate);
	void CalBeginPosByStartupPos(DWORD nSampleGap, DWORD dwSampleRate)
	{
		ASSERT (m_pRefBuffer != NULL);

		if (m_pRefBuffer != NULL)
		{
			CalBeginPosByStartupPos(m_pRefBuffer->GetDataFillBeginPosition(), nSampleGap, dwSampleRate);
		}
	}

	//得到第一个点位置和启动点到第一个点的距离
	void GetFirstDataPos_StartuptoFirstData(__int64& nPos,__int64& nLen)	{nPos = m_nFirstDataPos; nLen = m_nDataLenStartuptoFirstData;}
	
	//判断所有模拟通道是否都不使用
	BOOL IsAllSingleVariableNoUse();

#ifdef _CAL_USE_REF_VARIABLE_
	long GetRefBufDataLen()	{	return m_nXRefBufDataLen;	}
#endif

private:
	CRtMemBufferMngr *m_pRtMemBufferMngr;
	CRtVariable *m_pRefVariable;
	__int64 m_nFirstDataPos;
	long m_nStartupPos;
	long m_nDataLenStartuptoFirstData;
	//fdp add 2010.5.12 避免因为线程打断造成Buffer的范围改变，保存原有计算位置
#ifdef _CAL_USE_REF_VARIABLE_
	DWORD m_nXRefBufLen;
	DWORD m_nXRefBufFillBeginPos;
	DWORD m_nXRefBufDataLen;
	DWORD m_nXFrequencyCalBeginPos;          //频率计算的起始位置
	DWORD m_nXAttrCalBeginPos;               //属性计算的起始位置
#endif

	CMemBufferInterface *m_pRefBuffer;
	DWORD m_pdwAttrCalPosition[MAX_FREQ_ZERO_POS_BUFFER];
	BOOL m_bRefVariableChanged;

	long GetLenFromCurrPosToFillPos(long nCurrPos, long nDataFillPos, long nDataLen, long nBufferLen);
	
	BOOL IsPosInRange(long nPos, long nBegin, long nEnd);
	BOOL IsPosInRange(CRtVariable * pdVariable, long nPos, long nBegin, long nEnd);
//	BOOL IsPosInRange(long nPos, long nBegin, long nEnd);
	//fdp add 2010.4.15
	//设置除了频率之外的属性计算的范围
	DWORD GetAttrCalPosition2 (DWORD *pdwAttrCalPosition,PRTATTRIBUTECALFUNCPARA pCalPara);
	DWORD GetAttrCalPosition2 (CRtVariable * pdVariable,PRTATTRIBUTECALFUNCPARA pCalPara);
	//设置缓存读取的起点
	long SetReadBeginPos(/*CMemBuffer_UnsignedShort *pBuffer*/);
	long SetReadBeginPos(CRtVariable * pdVariable/*CMemBuffer_UnsignedShort *pBuffer*/);
	//判断本次参数计算的起点是否是一个过零点
	BOOL IsAttrCalBeginPosInRefZeroPos(DWORD** pBegin,DWORD* pEnd,long& nOffSet);
	BOOL IsAttrCalBeginPosInRefZeroPos(CRtVariable * pdVariable, DWORD** pBegin,DWORD* pEnd,long& nOffSet);
	//不正常时的参数计算的范围设置
	long GetExceptionalAttrCalPos(DWORD* pdwAttrCalPos/*,DWORD dwFillBeginPos*/);
	long GetExceptionalAttrCalPos(CRtVariable * pdVariable,DWORD* pdwAttrCalPos/*,DWORD dwFillBeginPos*/);
	//正常时的参数计算的范围设置
	///long GetNormalAttrCalPos(DWORD* pBegin,DWORD* pEnd,DWORD* pdwAttrCalPos,double dFreqValue);
	long GetNormalAttrCalPos(DWORD* pBegin,DWORD* pEnd,DWORD* pdwAttrCalPos,double dFreqValue, PRTATTRIBUTECALFUNCPARA pCalPara);
	long GetNormalAttrCalPos(CRtVariable * pdVariable,DWORD* pBegin,DWORD* pEnd,DWORD* pdwAttrCalPos,double dFreqValue, PRTATTRIBUTECALFUNCPARA pCalPara);
	
	//添加不正常时的参数值
// 	long AddAbNormalValue(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos);
// 	long AddAbNormalValue(CRtVariable* pRtVarible,PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos);
// 	long AddAbNormalValue(CRtDataAttribute* pRtDataAttr,PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos);
// 	void AddAbNormalValue(CMemBuffer_Float* pAttrBuffer); 
	//添加第一个属性缓存数据fdp add 2010.4.23
	void AddFirstAttrData();
	void AddFirstAttrData(CRtVariable* pRtVarible);
	void AddFirstAttrData(CRtDataAttribute* pRtDataAttr);
	//添加时间数据到缓存
	void AddTimeValue(RTATTRIBUTECALBUFFERPOS& oRtAttrCalBufPos);
	
	CRtVariable* FindByIDForRdSets(const CString& strID, const CString& strTanModel);	
	DWORD m_paVariables[MAX_RTVARIABLES];
	
	BOOL ValidateVariableRecordBuffer(BOOL bCalUseRecordBuffer);
	//////////////////////////////////////////////////////////////////////////
	//系统分析管理
public:
	void InitByAttrSpy(MR1200SYSANALYSEMNGR &oMR1200SysAnalyseMngr);
	void InitByAttrDedfault(MR1200SYSANALYSEMNGR &oMR1200SysAnalyseMngr);
	void SaveAttrSpy(MR1200SYSANALYSEMNGR &oMR1200SysAnalyseMngr);
	void InitByHarmAttrSpy(MR1200SYSANALYSEMNGR &oMR1200SysAnalyseMngr);

	void SetAttrUse(UINT nAttrID, long nUse);


	void ResetValueCal();
	DWORD* GetVariablesAddr()	{	return m_paVariables;	}
	void ResetValuesByHdIndex(long nHdIndex);
	void InitRtCalVariables();
	void InitCalFuncPara(long nChIndex);
	long GetChIndexByID(const CString &strChID);
};

//根据起始位置和计算的数据长度，获取缓存中的数据范围，包括普通计算和DFT计算
BOOL GetAttrCalPos(long nBeginPos, long nEndPos, long nBufferLen, long nDataLen, long nDataFillBeginPos, PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos);	
BOOL GetAttrCalPos(long nBeginPos, long nEndPos, long nBufferDataLen, long &nCalBuffer1Pos, long &nCalBuffer1Len , long &nCalBuffer2Pos, long &nCalBuffer2Len);
BOOL GetAttrCalPos(long nBeginPos, long nBufferLen, long nDataLen, PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, double dFrequency);	

extern CString g_strWriteRecordData_VariableID;

//2022-4-23  lijunqing 批量数据缓冲，解决多线程访问计算结果数据问题
#define XCYCLE_VARS_COUNT  128
#define XCYCLE_MAX_COUNT  16

typedef struct sttVariablesRtValues
{
	long nCount;
	RTCHANNELATTRVALUE oRtValues[XCYCLE_VARS_COUNT];
}STTVARIABLESRTVALUES, *PSTTVARIABLESRTVALUES;

class CStttVariablesRtValueBuffer
{
public:
	CStttVariablesRtValueBuffer();
	virtual ~CStttVariablesRtValueBuffer();

private:
	long m_nBufferCount;
	long m_nWritePos;

	STTVARIABLESRTVALUES m_oSttVarsVals[XCYCLE_MAX_COUNT];

public:
	PSTTVARIABLESRTVALUES GetNextForWrite();
	PSTTVARIABLESRTVALUES GetCurrForWrite();
	void NextForWrite();
	PSTTVARIABLESRTVALUES GetLast();
	void GetLast(STTVARIABLESRTVALUES &oSttValues);
	void ResetAllValues();
};

extern CStttVariablesRtValueBuffer g_oStttVariablesRtValueBuffer;

#endif // !defined(AFX_RTVARIABLES_H__C0F945B6_69F9_4670_B757_9D8A74B3638D__INCLUDED_)
