//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharacterArea.h  CCharacterArea

#pragma once

#include "CharacteristicGlobal.h"

#include "CharElementTestLines.h"
#include "CharElementLens.h"
#include "CharElementArc.h"
#include "CharElementArcd.h"
#include "CharElementArcp.h"
#include "CharElementLine.h"
#include "CharElementLinep.h"
#include "CharElementLined.h"
#include "CharElementLiner.h"
#include "CharElementMho.h"

#include "CharElementI2T.h"
#include "CharElementIAC.h"
#include "CharElementIEC.h"
#include "CharElementIEEE.h"

#include "CharElementUIVP.h"
#include "CharElementIUF.h"

#include "CharElementDCOverLoad.h"

#include "CharElementInvOwnDef.h"
#include "CharInterface.h"


class CCharacterArea : public CExBaseList
{
public:
	CCharacterArea();
	virtual ~CCharacterArea();

	BOOL m_bAutoClose;

//重载函数
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARACTERAREA;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharacterAreaKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);	
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE,BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual long InitListCtrlColumns(CListCtrl *pListCtrl);
	virtual long InsertToListCtrl(CListCtrl *pListCtrl);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long Serialize(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL CopyChildren(CBaseObject* pDest);

//私有成员变量
private:
	//所有角平分线的管理对象
	CCharElement *m_pCharBisector;
	
	//用户自定义测试线、测试点的管理对象:2019-9-12
	CCharElement *m_pUserDefTestDef;

	//2020-3-10  lijq 关联的绘图曲线模块
	CExBaseList *m_pDrawListRef;
	BOOL m_bDrawListRefOwn;

	BOOL m_bHasSerializeChildren;
	BOOL m_bUseIntersectionTestPoint;//20230620 zhouhj 是否创建测试线交点测试项
	CCharElementTestLines *m_pTestLines;
//私有成员变量访问方法
public:
	CCharElementTestLines* GetCharElementTestLines()	{	return m_pTestLines;	}
	BOOL IsAutoclose();
	virtual void CalCharElement(CExBaseList *pDrawList, UINT nTestLineMode=CHAR_TESTLINE_MODE_INDEX_PLUMB);
	virtual void CalTestLines(UINT nTestLineMode);
	CCharElement* GetCharBisector()	{	return m_pCharBisector;	}
	CCharElement* GetUserDefTestDef()	{	return m_pUserDefTestDef;	}
	void GetAllMacroTestLines(CExBaseList *pList);

protected:
	void InitCharDrawElementsLine(CCharElement *pChar1, CCharElement *pChar2, UINT nTestLineMode);
	void InitCharDrawElementsLineEx(CCharElement *pChar1, CCharElement *pChar2, UINT nTestLineMode);

	void InitCharDrawElementsLineEx(CXDrawData_Line *pDrawData1, CXDrawData_Line *pDrawData2, double dErrLen, DWORD nTestLineMode, long nTestLineID);
	void InitCharDrawElementsLineEx(CXDrawData_Line *pDrawData1, CXDrawData_Arc *pDrawData2, double dErrLen, DWORD nTestLineMode, long nTestLineID);
	void InitCharDrawElementsLineEx(CXDrawData_Arc *pDrawData1, CXDrawData_Line *pDrawData2, double dErrLen, DWORD nTestLineMode, long nTestLineID);
	void InitCharDrawElementsLineEx(CXDrawData_Arc *pDrawData1, CXDrawData_Arc *pDrawData2, double dErrLen, DWORD nTestLineMode, long nTestLineID);

	void InitCharDrawElementsLineEx_Plumb(double x, double y, CXDrawData_Line *pDrawData1, CXDrawData_Line *pDrawData2, double dErrLen, long nTestLineID);
	void InitCharDrawElementsLineEx(double x, double y, CXDrawData_Line *pDrawData1, CXDrawData_Arc *pDrawData2, double dErrLen, DWORD nTestLineMode, long nTestLineID);
	void InitCharDrawElementsLineEx_Vert(CXDrawDataBase *pDrawData1, CXDrawDataBase *pDrawData2, double dErrLen, long nTestLineID);
	void InitCharDrawElementsLineEx_Horz(CXDrawDataBase *pDrawData1, CXDrawDataBase *pDrawData2, double dErrLen, long nTestLineID);

	void InitCharDrawLined2Line(CCharElementLined *pXLine1, CCharElementLined *pXLine2,double dErrorLen, UINT nTestLineMode);
	void InitCharDrawLined2Line(CCharElementLined *pXLine1, CCharElementLiner *pXLine2,double dErrorLen, UINT nTestLineMode);
	void InitCharDrawLined2Line_Plumb(CCharElementLined *pXLine1, CCharElementLined *pXLine2,double dErrorLen);
	void InitCharDrawLined2Line_Vert(CCharElementLined *pXLine1, CCharElementLined *pXLine2,double dErrorLen);
	void InitCharDrawLined2Line_Horz(CCharElementLined *pXLine1, CCharElementLined *pXLine2,double dErrorLen);
	
	void InitCharDrawElementsLine(CCharElement *pChar, UINT nTestLineMode);
	void InitCharDrawElementsLine(CCharElementLens *pCharLens, UINT nTestLineMode);

	CCharElementTestLine* FindBisectorTestLine(long nTestLineID);
	void InitTestLineID(CCharElementTestLine *pTestLine, CCharElement *pChar1, CCharElement *pChar2);
	CCharElementTestLine* AddTestLine(CCharElement *pChar1, CCharElement *pChar2);
	CCharElementTestLine* AddTestLine(long nTestLineID);

public:
	CExBaseList* CreateDrawListRef();
	CExBaseList* DettachDrawListRef();
	void SetDrawListRef(CExBaseList *pDrawListRef)		{	m_pDrawListRef = pDrawListRef;	}
	CExBaseList* GetDrawListRef()		{	return m_pDrawListRef;		}
	void InitCharDrawElement(CXDrawList *pDrawList, BOOL bCalTestLines);
	void InitCharDrawElementTestLines(CXDrawList *pDrawList);

protected:
	BOOL NeedSolvEqation();
	void InitCharDrawElement_Equation(CXDrawList *pDrawList, BOOL bCalTestLines);
	void InitCharDrawElement_LineD(CXDrawList *pDrawList, CCharElementLined *pCharLined, BOOL bCalTestLines);
	void InitCharDrawElement_LineR(CXDrawList *pDrawList, CCharElementLiner *pCharLiner, BOOL bCalTestLines);
	void InitCharDrawElement_Mho(CXDrawList *pDrawList, CCharElementMho *pCharMho, BOOL bCalTestLines);
	void InitCharDrawElement_Lens(CXDrawList *pDrawList, CCharElementLens *pCharLens, BOOL bCalTestLines);
	void InitCharDrawElement_Inverse(CXDrawList *pDrawList, CCharElementInverse *pCharInverse, BOOL bCalTestLines);
	void InitCharDrawElementTestLines(CXDrawList *pDrawList, CCharElement *pCharElement);

public:
	//添加特性曲线与测试测试项目的接口
	//2020-3-19
	void DeleteAllTestLines();
	void AddTestLines(CXDrawData_Line *pValRange, double dLenStep);
	void AddTestLine(CXDrawData_Line *pCurrValLine);

	//根据数据接口，初始化points子对象
	void InitElementTestLines(CCharInterface *pCharInterface);
	void InitElementTestLines_CalValue(CCharInterface *pCharInterface, const CString& strExpression, double &dValue);

	//shaolei 2023-9-18 
	CCharElement* GetFirstCharElemet();
};

