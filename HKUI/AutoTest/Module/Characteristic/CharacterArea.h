//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharacterArea.h  CCharacterArea

#pragma once

#include "CharacteristicGlobal.h"

#include "CharTestObjects.h"
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

#include "CharElementRICurve.h"
#include "CharElementLabIecCurve.h"
#include "CharElementI2TEx.h"
#include "CharElementIT.h"
#include "CharElementRXIDG.h"

#include "CharElementInvOwnDef.h"
#include "CharInterface.h"

#include "CharElementExpr.h"


class CCharacterArea : public CExBaseList
{
public:
	CCharacterArea();
	virtual ~CCharacterArea();

	BOOL m_bAutoClose;

	void SetErrorBandLen(double ffErrorBandLen);
    void SetIsShowErrorBand(BOOL bShow) {   m_bShowErrBand = bShow; }

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
	CExBaseList *m_pDrawListRef;  //改为外部引用和定义的对象，lijunqing 2024-9-7
	BOOL m_bDrawListRefOwn;

	//lijunqing 2024-9-7  定义特性曲线相关的对象
	double m_fErrorBandLen;
	CXDrawListEx m_listCharElement;  //边界图元对象
	CXDrawListEx m_listErrorOut;     //外部误差边界：幅值大的部分
	CXDrawListEx m_listErrorIn;      //内部误差边界：幅值小的部分

	BOOL m_bHasSerializeChildren;
	BOOL m_bUseIntersectionTestPoint;//20230620 zhouhj 是否创建测试线交点测试项
    CCharTestObjects *m_pTestObjects;

    BOOL m_bShowErrBand;    //20241015 wanmj 是否显示误差带

//私有成员变量访问方法
public:
    CCharTestObjects* GetCharTestObjects()	{	return m_pTestObjects;	}
    void SetCharTestObjects(CCharTestObjects *p)	{	m_pTestObjects = p;	}
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

	CCharTestLine* FindBisectorTestLine(long nTestLineID);
	void InitTestLineID(CCharTestLine *pTestLine, CCharElement *pChar1, CCharElement *pChar2);
	CCharTestLine* AddTestLine(CCharElement *pChar1, CCharElement *pChar2);
	CCharTestLine* AddTestLine(long nTestLineID);

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
	void InitCharDrawElement_Lens_Err(CXDrawArc *pArc1, CXDrawArc *pArc2, double fErrLen, CXDrawListEx &oList);
	void InitCharDrawElement_Inverse(CXDrawList *pDrawList, CCharElementInverse *pCharInverse, BOOL bCalTestLines);
	void InitCharDrawElementTestLines(CXDrawList *pDrawList, CCharElement *pCharElement);
    void InitCharDrawElement_Expr(CXDrawList *pDrawList, CCharElementExpr *pCharExpr, BOOL bCalTestLines);

	//2024-9-24 lijunqing
	void InitCharDrawElement_Equation_ErrBand(CXDrawList *pDrawList);
	void InitCharDrawElement_Equation_ErrBand_Adjust(CXDrawList &oList);
	bool InitCharDrawElement_Equation_ErrBand_Adjust(CXDrawList &oList, CXDrawBase *pElement);

	void CalErrorBand(CXDrawBase *pDraw);
	void CalErrorBand(CXDrawArc *pArc);
	void CalErrorBand(CXDrawLine *pLine);
	void CalErrorBand_Arc(CXDrawListEx &oList);
	CXDrawBase* CalErrorBand_Arc_GetPrev(CXDrawListEx &oList, long nIndex);
	CXDrawBase* CalErrorBand_Arc_GetNext(CXDrawListEx &oList, long nIndex);
	void CalErrorBand_Solv(CXDrawListEx &oList);
	void CalErrorBand_SortBy_B_E(CXDrawListEx &oList);
	void ErrBand_Solv_Equation(CXDrawDataBase* pDrawData1, CXDrawDataBase *pDrawData2, long nIndex, CXDrawList *pDrawList, CXDrawData_Point *pPoint);
	void ErrBand_Solv_Equation_LL_Arc(CXDrawDataBase* pDrawData1, CXDrawDataBase *pDrawData2, long nIndex, CXDrawList *pDrawList, CXDrawData_Point *pPoint);
	void ErrBand_Solv_Equation(CXDrawDataBase* pDrawData1, CXDrawDataBase *pDrawData2, long nIndex, CXDrawList *pDrawList);

public:
	//2024-9-24 添加边界元素对象
	void AddElementDraw(CXDrawList *pDrawList, CXDrawBase *pDrawBase);

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

public:
	//2024-9-26 lijunqing 求取线段与曲线的交点
	void GetIntersectPoint(CXDrawData_Line *pLine, CXDrawDatas &oList);
	bool IsPointInErrBand(double x, double y);

	//2024-10-11 lijunqing 获取线段与曲线的TestLine
	long GetIntersectTestLine(CXDrawData_Line *pLine, CExBaseList &oList);

protected:
	void GetIntersectPoint(CXDrawData_Line *pLine, CXDrawDatas &oList, CXDrawDataBase *pCharElement, bool bJdgInLine=true);
	void GetIntersectPoint2(CXDrawDataBase *pLine, CXDrawDatas &oList, CXDrawDataBase *pCharElement, bool bJdgInLine=true);
	void GetIntersectTestLine(CXDrawData_Line *pLine, CXDrawDatas &oListPoint, CXDrawListEx &listElement, bool bJdgInLine);

	bool FindTestLine(CXDrawData_Line *pLine, CXDrawDatas &listIn, CXDrawDatas &listOut, CXDrawData_Point *pPoint
		, CXDrawData_Point &oPtIn, CXDrawData_Point &oPtOut);
	long FindTestLine(CXDrawData_Line *pLine, CXDrawDatas &listErr, CXDrawData_Point *pPoint, double dAngleDir, CXDrawData_Point &oPtErr);
	long FindTestLineShortest(CXDrawData_Line *pLine, CXDrawDatas &listErr, CXDrawData_Point *pPoint, double dAngleDir, CXDrawData_Point &oPtErr);
};

