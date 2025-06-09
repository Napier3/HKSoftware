//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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

//���غ���
public:
	virtual UINT GetClassID() {    return RBACLASSID_CRPTBKMKBATCHCELL;   }
	virtual BSTR GetXmlElementKey()  {      return CRptBkmkBatchAddXmlRWKeys::CRptBkmkBatchCellKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
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

