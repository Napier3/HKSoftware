// BaseObject.h: interface for the TfBaseObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_BASEOBJECTLIST_H__)
#define _BASEOBJECTLIST_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*
class CBaseObjectOrg : public CObject  
{
public:
	DECLARE_DYNCREATE(CBaseObjectOrg)
public:
	CBaseObjectOrg();
	virtual ~CBaseObjectOrg();
	
	virtual CBaseObjectOrg* GetNewObject(BOOL bCopy=FALSE);
	
	virtual BOOL operator==(CBaseObjectOrg &odTemp) ;
	virtual BOOL operator!=(CBaseObjectOrg &odTemp) ;
	virtual const CBaseObjectOrg & operator =(CBaseObjectOrg &odTemp);
	
};
*/
class CBaseObjectList : public CPtrList
{
public:	  
	CBaseObjectList();
	CBaseObjectList(int);
	~CBaseObjectList();
	void EndIt();
	
	void RemoveOneItem(POSITION pos,BOOL);
};

//ͨ�ù���
CString GetAppModuleFilePath();
void GetIPFromString(CString strIP,BYTE *bytIP);
//��ʽת��
int ConverStrToNum(CString m_DealStr);
CString BinToDec(CString strBin);	//2����ת��10����
CString DecToBin(CString strDec);	//10���Ƶ�2����
CString BinToHex(CString m_strBin);	//2-16
CString HexToBin(CString m_strHex);	//16-2
CString DecToHex(CString m_strDec);	//10-16
CString HexToDec(CString m_strHex);	//16-10
//��ȡMac��ַ
int GetDataFromHex(CString strTemp);
int GetDataFrom2Hex(CString strTemp);

#ifdef UNICODE
char*	StringToChar(CString &strTrans);
CString CharToString(const char *chTrans);
#endif

#endif // !defined(_BASEOBJECT_H__)
