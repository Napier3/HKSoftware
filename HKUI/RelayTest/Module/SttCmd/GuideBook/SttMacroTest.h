//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttMacroTest.h  CSttMacroTest

#pragma once

#include "../SttCmdDefineGlobal.h"

#include "SttItemBase.h"

#include "SttCommCmd.h"
#include "SttSafety.h"
#include "SttTestMacroUiParas.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CSttMacroTestParaData : public CExBaseList
{
public:
	CSttMacroTestParaData();
	virtual ~CSttMacroTestParaData();


public:
	virtual UINT GetClassID()		{		return STTGBXMLCLASSID_CSTTMACROPARADATA;			}
	//ReadXML
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	//WriteXML
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElemen, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	//缓冲区串行化
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BSTR GetXmlElementKey();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual BOOL IsEqual(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();

	CString m_strValue;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CSttMacroTestParaDatas : public CExBaseList
{
public:
	CSttMacroTestParaDatas();
	virtual ~CSttMacroTestParaDatas();


public:
	virtual UINT GetClassID()		{		return STTGBXMLCLASSID_CSTTMACROPARADATAS;			}
	//ReadXML
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	//WriteXML
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElemen, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	//缓冲区串行化
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BSTR GetXmlElementKey();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual BOOL IsEqual(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();
	virtual BOOL CopyChildren(CBaseObject* pDest);

	BOOL SetDataValue(const CString &strID,const CString &strValue,BOOL bCreate = TRUE);
	CSttMacroTestParaData* AddData(const CString &strName, const CString &strID, const CString &strValue);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CSttMacroTestPara : public CExBaseList
{
public:
	CSttMacroTestPara();
	virtual ~CSttMacroTestPara();

protected:
	CString m_strMacroID;
	CString m_strTestMode;

public:
	virtual UINT GetClassID()		{		return STTGBXMLCLASSID_CSTTMACROPARA;			}
	//ReadXML
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	//WriteXML
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElemen, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	//缓冲区串行化
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BSTR GetXmlElementKey();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual BOOL IsEqual(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();
	//接口函数
	void SetTestMode(const CString &strMode){m_strTestMode = strMode;}
	CString GetTestMode()				{		return m_strTestMode;		}
	void SetMacroID(const CString &strMacroID){m_strMacroID = strMacroID;}
	CString GetMacroID()				{		return m_strMacroID;		}

	CSttMacroTestParaData* FindMacroTestParaDataByID(const CString &strID);
	CSttMacroTestParaDatas* GetSttMacroTestParaDatas(BOOL bCreate = TRUE);//如果不存在,则创建缺省的

protected:
	CSttMacroTestParaDatas *m_pParaDatas;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CSttMacroTest : public CSttItemBase
{
public:
	CSttMacroTest();
	virtual ~CSttMacroTest();


	CString  m_strType;
	long  m_nRepeatTimes;
	CString  m_strReportMode;
	long  m_nReportFillUseNoRepeat;
	CString m_strMacroID;   //2022-4-14  lijunqing
	long m_nModified;//2024.6.29 zhouhj  标记是否被修改

protected:
	CSttMacroTestPara* m_pPara;

//重载函数
public:
	virtual UINT GetClassID() {    return STTGBXMLCLASSID_CSTTMACROTEST;   }
	virtual BSTR GetXmlElementKey();//  {      return CSttCmdDefineXmlRWKeys::CSttMacroTestKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	//2023-2-27  shaolei
	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);	
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
	CString GetTestMacroID();
	CSttTestMacroUiParas* GetSttTestMacroUiParas(BOOL bCreate = TRUE);
	virtual long GetItemTestCount();
	long GetItemsRepeatTimes()	{	return m_nRepeatTimes;	}  // = 1，表示不重复
	CSttMacroTestPara* GetSttMacroTestPara(BOOL bCreate=FALSE);
	CSttMacroTestPara* GetAddMacroTestPara(const CString &strMacroID);
	CSttMacroTestParaDatas* GetSttMacroTestParaDatas(BOOL bCreate ,const CString &strMacroID);//如果不存在,则创建缺省的
	//根据最后一次报告的结果判断值,更新当前测试项目状态  zhouhj 2024.7.6
	BOOL UpdateItemState_ByLastRptRsltJdg();
	CDvmValues* GetLastRptDvmValues();//获取最后一次报告的结果数据链表 

//属性变量访问方法
public:
};

