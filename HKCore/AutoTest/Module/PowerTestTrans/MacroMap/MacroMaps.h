//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//MacroMaps.h  CMacroMaps

#pragma once

#include "MacroMapMngrGlobal.h"


#include "MacroMap.h"

class CMacroMaps : public CExBaseList
{
public:
	CMacroMaps();
	virtual ~CMacroMaps();


//���غ���
public:
	virtual UINT GetClassID() {    return MPCLASSID_CMACROMAPS;   }
	virtual BSTR GetXmlElementKey()  {      return CMacroMapMngrXmlRWKeys::CMacroMapsKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:
	BOOL m_bModifiedFlag;

//˽�г�Ա�������ʷ���
public:
	BOOL IsModified()	{	return m_bModifiedFlag;	}
	void SetModifiedFlag(BOOL bModify=TRUE)	{	m_bModifiedFlag = bModify;	}

	void OpenMacroMaps();
	void SaveMapFile();
	CString GetMapFilePath();

	CMacroMap* FindMacroMap(const CString &strPttMacroID);
	CMacroMap* FindMacroMapByMapID(const CString &strMapID);
};

