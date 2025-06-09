//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XSclFileMngr.h  CXSclFileMngr

#pragma once

#include "SclFileMngrGlobal.h"


#include "XSclFileObj.h"

#define XSCL_FILE_MAX_MNGR_NUM          10000  //管理对象中最大支持的导入的SCD文件的数量

class CXSclFileMngr : public CExBaseList
{
public:
	CXSclFileMngr();
	virtual ~CXSclFileMngr();


//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CXSCLFILEMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CSclFileMngrXmlRWKeys::CXSclFileMngrKey();     }
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
	BOOL m_bHasOpenCfgFile;//记录是否已打开此配置文件

//属性变量访问方法
public:
	BOOL OpenSclFileMngrCfg(const CString &strPath = _T(""));
	BOOL SaveSclFileMngrCfg(const CString &strPath = _T(""));
	BOOL ValidSetSelectState(CXSclFileObj *pXSclFileObj);
	void ClearAll_WithFolderFiles();
	CString GetCurrSelSsclFilePah();
	CString GetCurrSelTscdFilePah();
	CString GenerateSclFileObjID();//遍历当前所有CXSclFileObj子对象,从1开始编号,生成对应的ID
	void DelecteAll_UnExistTscd();//删除tscd不存在的测试记录
	void DelecteAll_RepeatScdTscd();//删除scd路径和tscd重复的测试记录
};

extern CXSclFileMngr g_oXSclFileMngr;

