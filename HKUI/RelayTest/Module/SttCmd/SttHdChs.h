//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttHdChs.h  CSttHdChs

#pragma once

#include "SttCmdDefineGlobal.h"


#include "SttHdCh.h"

class CSttHdChs : public CExBaseList
{
public:
	CSttHdChs();
	virtual ~CSttHdChs();


//重载函数
public:
	virtual UINT GetClassID() {    return STTCMDCLASSID_CSTTHDCHS;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmdDefineXmlRWKeys::CSttHdChsKey();     }
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
	BOOL HasHdCh(char zfChType,const long &nModuleIndex,long nChIndex);
	CSttHdCh* AddHdCh(const CString &strHdRsName,const CString &strHdRsID,float fHdChCoef = 1.0f);
	CSttHdCh* FindAddHdCh(const CString &strHdRsName,const CString &strHdRsID,float fHdChCoef = 1.0f);//先查找该通道,如果查找不到,则创建该对象
	void InitHdChsByString(char zfChType,CString &strHdChsString);//参数1为电压电流通道标识值为'U'或'I',参数2为硬件通道字符串,如:"U1_1;U1_2;U1_3;",如字符串中存在无效字符,将其删除,参数2为硬件通道类型,用于验证通道
	BOOL HasAnalogCurrModuleHdCh(long nModuleIndex);//判断是否包含模拟量电流插件模块,Index从1开始编号  zhouhj20211005

protected:
	void InitHdChsByString_Analog(char zfChType,CString &strHdChsString);//参数1为硬件通道字符串,如:"U1_1;U1_2;U1_3;",如字符串中存在无效字符,将其删除,参数2为硬件通道类型,用于验证通道
	void InitHdChsByString_Digital(char zfChType,CString &strHdChsString);//参数1为硬件通道字符串,如:"U1_1;U1_2;U1_3;",如字符串中存在无效字符,将其删除,参数2为硬件通道类型,用于验证通道
	void InitHdChsByString_Weak(char zfChType,CString &strHdChsString);//参数1为硬件通道字符串,如:"U1_1;U1_2;U1_3;",如字符串中存在无效字符,将其删除,参数2为硬件通道类型,用于验证通道
};

