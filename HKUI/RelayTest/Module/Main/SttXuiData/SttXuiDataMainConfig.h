//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttXuiDataMainConfig.h  CSttXuiDataMainConfig

#pragma once

#include "SttXMainConfigGlobal.h"

#include "SttXuiDataBase.h"

#include "SttXuiDataGlobal.h"
#include "SttXuiDataTabs.h"
#include "SttXuiDataBtnsGroup.h"
#include "SttXuiDataButton.h"
#include "SttXuiDataFileMngrGrid.h"
#include "SttXuiDataTestBtnsGroup.h"
#include "SttXuiDataText.h"

class CSttXuiDataMainConfig : public CSttXuiDataBase
{
public:
	CSttXuiDataMainConfig();
	virtual ~CSttXuiDataMainConfig();

	CString  m_strFilePath;
	CString  m_strVersion;
	CString  m_strTitle;
	CString  m_strPic;
	long  m_nCx;
	long  m_nCy;
	long  m_nShowBatteryBtn;//2024-1-22 zhouyangyong 添加用于是否显示电池电量图标
	double m_dStartupDelayTime;//开机启动延时时间 zhouhj 2024.5.24
//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTTXUIDATAMAINCONFIG;   }
	virtual BSTR GetXmlElementKey()  {      return CSttXMainConfigXmlRWKeys::CSttXuiDataMainConfigKey();     }
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
};

