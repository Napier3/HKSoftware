//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttMacroTestUI_TestMacroUI.h  CSttMacroTestUI_TestMacroUI

#pragma once

#include "SttTestCtrrlMacroTestUIMngrGlobal.h"
#include "../../../../../Module/DataMngr/DataGroup.h"

class CSttMacroTestUI_TestMacroUI : public CExBaseObject
{
public:
	CSttMacroTestUI_TestMacroUI();
	virtual ~CSttMacroTestUI_TestMacroUI();


	//如何判断当前页面是原生态还是网页？【m_strGenFile和m_strUI_File均为空时，则是原生态】
	CString  m_strGenFile;     //测试项目智能生成的规则文件，路径为DB/atsgen
	CString  m_strUI_File;     //界面文件，对应一个HTML文件，路径为DB/ui
	CString  m_strUI_ParaFile; //界面参数文件，对应一个CDataGroup，路径为DB/atsgen
	CString  m_strReportFile;  //报告文件，对应一个HTML文件，路径为DB/ui
	CString  m_strHdRsFile;    //硬件资源文件，对应一个硬件资源配置，路径为DB/atsgen
	CString  m_strCharlibFile; //特性曲线库文件，对应一个特性曲线库，路径为Config根目录
	CString  m_strGirdFile;//国际版软件表格配置文件 grid-file
	CString  m_strUI_ID;//界面对象ID
	//shaolei 2023-6-20
	CString  m_strrpt_Data_CfgFile;   //导出xml报告及word报告的数据配置文件（报告数据配置文件）
	//shaolei 2023-6-21
	long m_nDefaultRepeatTimes;  //配置的默认的重复次数
//重载函数
public:
	virtual UINT GetClassID() {    return MACROTESTUIMNGRCLASSID_CSTTMACROTESTUI_TESTMACROUI;   }
	virtual BSTR GetXmlElementKey()  {      return CSttTestCtrrlMacroTestUIMngrXmlRWKeys::CSttMacroTestUI_TestMacroUIKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);

public:
	//将TestMacroUI转化为DataGroup类型 sf 20220114
	CDataGroup *GetTestMacroUIDataGroup();
	void GetTestMacroUIDataGroup(CDataGroup *pDataParas);
//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
	//zhouhj 2023.11.9 合并单元自动测试改为采用模板生成文件生成方式
	//此时是否包含模板生成文件不能作为原生界面的判据,如果包含m_strUI_File则为网页界面,否则为原生界面
	BOOL IsUIOriginal()		{	return ( /*m_strGenFile.IsEmpty() &&*/ m_strUI_File.IsEmpty() );	}
	BOOL IsUIWeb()		{	return ( /*!m_strGenFile.IsEmpty() &&*/ !m_strUI_File.IsEmpty() );	}
	BOOL HasCharLib()	{	return m_strCharlibFile.GetLength() > 0;	}  //2022-6-30  lijunqing
};

