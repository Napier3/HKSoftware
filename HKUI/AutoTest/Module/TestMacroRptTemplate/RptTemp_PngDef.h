//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_PngDef.h  CRptTemp_PngDef

#pragma once

#include "TestMacroRptTemplateGlobal.h"

//插入图片，1、结果图片；2、曲线方程图片
class CRptTemp_PngDef : public CExBaseObject
{
public:
	CRptTemp_PngDef();
	virtual ~CRptTemp_PngDef();

	CString  m_strPngPath;
	CString  m_strName;  //插入图片时，以文本形式插入图片名称。固定加粗、黑体
	CString  m_strMode;  //故障类型，AN、BN、CN、AB、BC、AC、ABC等
	long m_nPngChar;  //是否是曲线方程？0=不是，1=是。

	BOOL m_bHasExport; //是否已经导出。对于差动等试验，RptData配置时按row-items来配置，但图片是所有测试点汇总后导出一次就行，因此增加标记，避免重复导出

//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CRPTTEMP_PNGDEF;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroRptTemplateXmlRWKeys::CRptTemp_PngDefKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
};

