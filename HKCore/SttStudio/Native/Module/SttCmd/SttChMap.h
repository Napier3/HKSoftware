//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttChMap.h  CSttChMap

#pragma once

#include "SttCmdDefineGlobal.h"
#include "../SttTest/Common/tmt_adjust_sys_para_module_def.h"


#include "SttHdChs.h"

#define MACROTYPE_Empty    0	//空
#define MACROTYPE_Analog   1	//模拟
#define MACROTYPE_Digital  2	//数字
#define MACROTYPE_Week     3	//小信号	
#define MACROTYPE_Mix      4	//混合--小信号&数字&模拟


class CSttChMap : public CExBaseList
{
public:
	CSttChMap();
	virtual ~CSttChMap();


	CString  m_strAlias;

	//2021-5-1  lijunqing  为了通道映射的方便性，定义软件资源的编号
	long m_nRsIndex;  
//重载函数
public:
	virtual UINT GetClassID() {    return STTCMDCLASSID_CSTTCHMAP;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmdDefineXmlRWKeys::CSttChMapKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
	long GetRsIndexFromID();//zhouhj 从ID中获取资源编号
	BOOL HasHdCh(const CString &strType, const CString &strChID);
	BOOL HasHdCh();
	CSttHdCh* FindHdCh(const CString &strType, const CString &strChID);//zhouhj 查找对应的硬件通道

	BOOL IsVoltageCh();
	BOOL IsCurrentCh();
	BOOL HasMapHdResource(long nHasAnalog,long nHasDigital,long nHasWeek);//根据当前选择的输出类型，判断该通道是否应该存在软件资源
	BOOL HasMapHdResource(const CString &strHdChsID);
	BOOL HasMapHdResource(const char* cHdChsID);//sf 20211122 兼容Unicode
	CSttHdCh* AddHdMapCh(const CString &strHdChsID,const CString &strHdRsName,const CString &strHdRsID);
	CString GetHdChsString(const CString &strHdChsID);//zhouhj 通道映射界面显示的模拟量、数字量等拼接后的字符串
	void InitHdChs_ByString(CString &strHdChsString,const CString &strHdChsID);//参数1为硬件通道字符串,如:"U1_1;U1_2;U1_3;",参数2为硬件类型标识
	CSttHdChs* GetHdChs(const CString &strHdChsID);
	CSttHdChs* GetHdChs(const char* cHdChsID);//sf 20211122 兼容Unicode
	void SetWeakRateValue(float fWeakRateValue,BOOL bPrimaryValue);//zhouhj 20210716 设置弱信号变比一次值或者二次值,参数2为该值是否为一次值
	BOOL HasAnalogCurrModuleHdCh(long nModuleIndex);//判断是否包含模拟量电流插件模块,Index从1开始编号  zhouhj20211005
	BOOL GetMaxValue_WeekRates(double &dMaxVol,double &dMaxCur);
	void UpdateWeekRateValue();
 	long GetMapChsType();//2023-11-13 suyang 增加区别通道类型是模拟 数字 弱信号 混合 空  
};

long Global_GetCurrChType_Single(long nMixChType,long nHasAnalog,long nHasDigtal,long nWeek);//2023-11-28 suyang 获取到当前通道的类型
