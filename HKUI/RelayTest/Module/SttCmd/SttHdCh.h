//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttHdCh.h  CSttHdCh

#pragma once

#include "SttCmdDefineGlobal.h"


#include "../../../Module/DataMngr/DvmData.h"

//zhouhj 2023.8.3 用于设置弱信号缺省变比
#define STT_WEEK_USE_MODE_NORMAL                           0//普通弱信号[120/7.07][30/7.07]
#define STT_WEEK_USE_MODE_DistriTerm                       1//配电终端弱信号[1:1]


class CSttHdCh : public CExBaseList
{
public:
	CSttHdCh();
	virtual ~CSttHdCh();

	float m_fCoef;//20210602zhouhongjun 硬件通道系数,用于合并电流电压通道输出时使用


//重载函数
public:
	virtual UINT GetClassID() {    return STTCMDCLASSID_CSTTHDCH;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmdDefineXmlRWKeys::CSttHdChKey();     }
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
	void SetTransRate_Weak(float fPrimValue,float fSecondValue);//zhouhj 20210714 增加用于弱型号变比设置
	float GetPrimaryValue_Float();
	float GetSecondaryValue_Float();
	CDvmData* GetPrimaryValue_DvmData();
	CDvmData* GetSecondaryValue_DvmData();
	void SetWeakRateValue(float fWeakRateValue,BOOL bPrimaryValue);
	void UpdateWeekRateValue();
};


extern long g_nSttWeekUseMode;//zhouhj 2023.8.3 用于设置弱信号的缺省变比