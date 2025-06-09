#pragma once
#include "MacroCharItems.h"
#include "MacroTest.h"
#include "../Characteristic/CharacteristicTmplate.h"

//2022-7-24  lijunqing ÒÆ¶¯µ½AutoTestGlobalDefine.h
// #define MACRO_CHAR_TEST_AXISMODE_XY       _T("x-y")
// #define MACRO_CHAR_TEST_AXISMODE_RANGLE   _T("r-angle")

class CMacroCharItemLineDef : public CExBaseObject
{
public:
	CMacroCharItemLineDef();
	virtual ~CMacroCharItemLineDef();

	CString  m_strType;  //Test Type: line, point
	CString  m_strAxisMode;   //Axis mode:x-y; r-angle
	CString  m_strParaIdXb;
	CString  m_strParaIdYb;
	CString  m_strParaIdXe;
	CString  m_strParaIdYe;
	CString  m_strParaIdXset;
	CString  m_strParaIdYset;
	CString  m_strParaIdXact;
	CString  m_strParaIdYact;
	CString  m_strParaIdFlagAct;

	CString  m_strParaIdSearchXb;
	CString  m_strParaIdSearchYb;
	CString  m_strParaIdSearchActb;
	CString  m_strParaIdSearchXe;
	CString  m_strParaIdSearchYe;
	CString  m_strParaIdSearchActe;
	CString  m_strParaIdSearchXc;
	CString  m_strParaIdSearchYc;

	double m_fXb;
	double m_fYb;
	double m_fXe;
	double m_fYe;
	double m_fXset;
	double m_fYset;
	double m_fXact;
	double m_fYact;
	long m_nFlagAct;  //2022-07-28 shaolei

	double m_fSearchXb;
	double m_fSearchYb;
	long   m_nSearchActb;
	double m_fSearchXe;
	double m_fSearchYe;
	long   m_nSearchActe;
	double m_fSearchXc;
	double m_fSearchYc;
	
public:
	virtual UINT GetClassID() {    return GBCLASSID_MACROCHARITEMLINEDEF;   }
	virtual BSTR GetXmlElementKey()  {      return CGbXMLKeys::g_pGbXMLKeys->m_strCMacroCharItemLineDefKey;     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	BOOL IsAxisMode_x_y();
	BOOL IsAxisMode_r_angle();
	BOOL IsLineDef_point();
	BOOL IsLineDef_line();

	void InitSearchValues(CValues *pSearchReport);
	void ChangeValueXY(double &dX, double &dY);
};

class CMacroCharItems :public CGbItemBase
{
public:
	CMacroCharItems(void);
	virtual ~CMacroCharItems(void);

	static CMacroCharItems* _New(CBaseObject *pParent=NULL)
	{
		CMacroCharItems *pNew = new CMacroCharItems();
		pNew->InitAfterRead();
		pNew->SetParent(pParent);
		pNew->InitMacroID();
		return pNew;
	}

private:
	static CShortDatas *g_pMacroCharItemsDatas;
	static long  g_nMacroCharItemsDatas;

public:
	static void CreateMacroCharItemsDatas();
	static void ReleaseMacroCharItemsDatas();
	static CShortDatas* GetMacroCharItemsDatas();

	static CString  g_strKeyParaIdXb;
	static CString  g_strKeyParaIdYb;
	static CString  g_strKeyParaIdXe;
	static CString  g_strKeyParaIdYe;
	static CString  g_strKeyParaIdXset;
	static CString  g_strKeyParaIdYset;
	static CString  g_strKeyParaIdXact;
	static CString  g_strKeyParaIdYact;
	static CString  g_strKeyCharGraph;

public:
	void InitMacroID();
	CString GetTestMacroID();

public:
	//attribute
	//CString m_strCharacteristicID;
	CMacroTestPara* m_pPara;
	CMacroCharItemLineDef *m_pItemLineDef;
	//lijq 2020-3-13
	//CCharacteristicTmplate *m_pCharTemplate;
	CCharacteristic *m_pCharTemplate;

public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()		{		return GBCLASSID_MACROCHARITEMS;			}
	virtual BSTR GetXmlElementKey()  {      return CGbXMLKeys::g_pGbXMLKeys->m_strCMacroCharItemsKey;     }

	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(CExBaseObject *pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual void InitAfterRead();

	CCharacteristic* SetCharacteristicTmplate(CCharacteristic *pCharTemp);
	CString GetMacroTestDataID(const CString &strID);

public:
	BOOL WriteCharGraphFile();
	BOOL IsAllMacroTestFinished();
	CMacroTestPara* GetMacroTestPara();
	CMacroCharItemLineDef* GetCMacroCharItemLineDef();
	CCharacteristic* GetCharacteristicTmplate();

	void InitMacroTestItems();
	void UpdateMacroTestItems();
	void InitTestLinesRef();
	CMacroCharItemLineDef* UpdateMacroTest(CMacroTest *pMacroTest, CValues *pSearchReport);
	CCharElementTestLine* UpdateMacroTest(CMacroTest *pMacroTest, CReport *pReport);
	long GetMacroTestIndex(CMacroTest *pMacroTest);

	void InitMacroTestIDByIndex();
	void GetAllMacroTestItemsEx(CExBaseList *pList);

protected:
	void GetAllMacroTestItems(CExBaseList *pList);
	void CreateMacroTestItem(CCharElementTestLine *pTestLine, CTestMacro* pTestMacro);
	void AddMacroTestPara(CMacroTest *pMacroTest, CShortDatas *pFaultParas, const CString &strParaID, double dValue);
	void AddMacroTestPara_r_angle(CMacroTest *pMacroTest, CShortDatas *pFaultParas, const CString &strParaID, double dValue, const CString &strParaID2, double dValue2);
	void AddMacroTestPara(CMacroTest *pMacroTest, CShortDatas *pFaultParas, const CString &strParaID, const CString &strValue);
	void UpateMacroTestItem(CCharElementTestLine *pTestLine, CMacroTest *pMacroTest, CTestMacro* pTestMacro);
	void InitByMacroTestPara_r_angle(CValues *pValues, const CString &strParaIDX, double &dValueX, const CString &strParaIDY, double &dValueY, const CString &strParaIDFlag, long &nValueFlag);

public:
	CCharElementTestLine* FindTestLine(CMacroTest *pMacroTest);
	void UpdateTestLineDef(CMacroTest *pMacroTest);

	virtual long GetItemTestCount();
	virtual void ClearReport(BOOL bBack=TRUE);
};

CString char_test_GetCharGraphFile();