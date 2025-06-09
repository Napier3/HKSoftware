//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AudioData.h  CAudioData

#pragma once

#include "VoiceWordGlobal.h"



class CAudioData : public CExBaseList
{
public:
	CAudioData();
	virtual ~CAudioData();

	CString  m_strData_Type;
	CString  m_strValue;
//重载函数
public:
	virtual UINT GetClassID() {    return VWCLASSID_CAUDIODATA;   }
	virtual BSTR GetXmlElementKey()  {      return CVoiceWordXmlRWKeys::CAudioDataKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long InitListCtrlColumns(CListCtrl *pListCtrl);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:

//私有成员变量访问方法
public:
	//功能处理  
	int m_nFunctionFlag;
	//当前语音 发生的 1 用户 2 语音播报  默认值 -1
	int m_nPersonFlag;
	//当前步骤         默认值 -1
	int m_nCurrentStep;
	//当前的命令    默认值 -1
	int m_nStepFlag;
	//在确认信息，回答 1 确定 0 否定  默认值  -1
	int m_nConfirmFlag;
	//当前文字信息
	CString m_strResultMess;
	//当前确认好的参数  没有确认为空  ""
	CString m_strParaValue;

};

