//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptBkmkBatchCell.h  CRptBkmkBatchCell

#pragma once

#include "RptBkmkBatchAddGlobal.h"

#include "../WordRptEdit.h"
#include "../WPSRptEdit.h"

class CRptBkmkBatchCell : public CExBaseObject
{
public:
	CRptBkmkBatchCell();
	virtual ~CRptBkmkBatchCell();

public:
	CExBaseObject *m_pGbItem;
	CExBaseObject *m_pData;
//	MSWord::Cell  m_oCell;
	CString m_strPrecision;
	CString m_strDataAttr;
	long m_nRepeatIndex;
	CString m_strDataProcess;

//重载函数
public:
	virtual UINT GetClassID() {    return RBACLASSID_CRPTBKMKBATCHCELL;   }
	virtual BSTR GetXmlElementKey()  {      return CRptBkmkBatchAddXmlRWKeys::CRptBkmkBatchCellKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();

//私有成员变量
private:

//私有成员变量访问方法
public:
};

class CRptBkmkBatchCell_Word : public CRptBkmkBatchCell
{
public:
	CRptBkmkBatchCell_Word(){};
	~CRptBkmkBatchCell_Word(){};

	MSWord::Cell  m_oCell;
};

class CRptBkmkBatchCell_WPS : public CRptBkmkBatchCell
{
public:
	CRptBkmkBatchCell_WPS(){};
	~CRptBkmkBatchCell_WPS(){};

	WPS::Cell  m_oCell;
};

