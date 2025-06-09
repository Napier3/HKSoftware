#ifndef QRSLTEXPRMNGR_H
#define QRSLTEXPRMNGR_H

#include "../../../../../Module/DataMngr/DataGroup.h"
#include "../../../../../Module/DataMngr/DataTypes.h"
#include "../../../Module/API/GlobalConfigApi.h"

// mym 2021-7-20   表达式管理对象类
//表达式管理可分为多个层级，表达式从XML文件中读取。
class QRsltExprMngr 
{
public:
	QRsltExprMngr();
	~QRsltExprMngr();

	static long g_nRsltExprMngr;

	static QRsltExprMngr* g_pRsltExprMngr;

	 CString  m_strExprFileName;

	CDataGroup * m_pRoot;
	CDataGroup * m_pDataGroup_Curr;

public:
	static QRsltExprMngr* Create();
	static QRsltExprMngr* GetRsltExprMngr();
	static void Release();
	static long   GetExprCount();
	static CString   GetExprContent(CString strID,  int nIndex);
	static CDataGroup *  FindDataGroupByID(const CString &strIDPath);
	static void InitDataGroupByID(const CString &strIDPath);

public:
	//void InitRsltExprMngr();
// 	CString GetRsltExprXMLPath();
// 	CString GetRsltExprXMLFile();

	void SetExprFileName(CString strFileName);

};

//2021-7-21  lijunqing mym sf
/*
<group name="SttTmtRsltExprDefineMngr" id="SttTmtRsltExprDefineMngr" data-type="SttTmtRsltExprDefineMngr" value="5">
	<group name="SttTmtRsltExprDefine" id="SttTmtRsltExprDefine" data-type="" value="Distance">
		<group name="ExprDatasDef" id="ExprDatasDef" data-type="ExprDatasDef" value="ExprDatasDef">
			<data name="跳A" id="TtripA" data-type="" value=""/>
			<data name="跳B" id="TtripB" data-type="" value=""/>
			<data name="跳C" id="TtripC" data-type="" value=""/>
		</group>
		<group name="ExprViewDatasDef" id="ExprViewDatasDef" data-type="ExprViewDatasDef" value="ExprViewDatasDef">
			<data name="跳A" id="TtripA" data-type="" value=""/>
			<data name="跳B" id="TtripB" data-type="" value=""/>
			<data name="跳C" id="TtripC" data-type="" value=""/>
			<data name="跳D" id="TtripD" data-type="" value=""/>
			<data name="跳E" id="TtripE" data-type="" value=""/>
		</group>
	</group>
</group>
*/
//<group name="SttTmtRsltExprDefine" id="SttTmtRsltExprDefine" data-type="" value="Distance">
class CSttTmtRsltExprDefine : public CExBaseObject
{
public:
	CSttTmtRsltExprDefine();
	virtual ~CSttTmtRsltExprDefine();

	//pRsltExprDefine为SttTmtRsltExprDefine 节点
	////<group name="SttTmtRsltExprDefine" id="SttTmtRsltExprDefine" data-type="" value="Distance">
	void InitRsltExprDefine(CDataGroup *pRsltExprDefine);

	//<group name="ExprDatasDef" id="ExprDatasDef" data-type="ExprDatasDef" value="ExprDatasDef">
	CDataGroup *m_pExprDatasDef;

	//<group name="ExprViewDatasDef" id="ExprViewDatasDef" data-type="ExprViewDatasDef" value="ExprViewDatasDef">
	CDataGroup *m_pExprViewDatasDef;

// 
// 	CString  m_strExprTitle[EXPR_COUNT];//表达式标题，例如“跳A”、“跳B”
// 	CString  m_strExprValueID[EXPR_COUNT];//表达式对应的数据ID，例如“TtripA”、“TtripB”
// 	
// 	//表达式对应的数据ID，例如“TtripA”、“TtripB”
// 	//表达式对应的数据名称，例如“A相动作时间”、“B相动作时间”，根据RsltDataID从g_pTmt_TestItemResultRef查找
// 	CString  m_strRsltDataID[EXPR_COUNT];
// 
// 	int  m_nExprCount;  //表达式个数
// 	int  m_nRsltDataCount; //评估界面显示的结果数据的个数
// 
// 	void AddExprData(char *pszExprTitle, char *pszExprValueID)
// 	{
// 		m_strExprTitle[m_nExprCount] = pszExprTitle;
// 		m_strExprValueID[m_nExprCount] = pszExprValueID;
// 		m_nExprCount++;
// 	}
// 
// 	void AddRsltData(char *pszRsltDataID )
// 	{
// 		m_strRsltDataID[m_nRsltDataCount] = pszRsltDataID;
// 		m_nRsltDataCount++;
// 	}
};

//<group name="SttTmtRsltExprDefineMngr" id="SttTmtRsltExprDefineMngr" data-type="SttTmtRsltExprDefineMngr" value="5">
class CSttTmtRsltExprDefineMngr: public CDataGroup
{
public:
	CSttTmtRsltExprDefineMngr();
	virtual ~CSttTmtRsltExprDefineMngr();

	void InitRsltExprDefineMngr(const CString &strFile);
	CSttTmtRsltExprDefine* FindRsltExprDefine(const CString &strTmtID);

	CDataGroup * m_pDataGroup ;
	CString  m_strTmtID;

private:
	CSttTmtRsltExprDefine m_oRsltExprDefine;
};

extern CSttTmtRsltExprDefineMngr g_oSttTmtRsltExprDefineMngr;

void stt_init_rslt_expr_mngr(const CString &strExprFile, const CString &strExprDataFile);
void stt_free_rslt_expr_mngr();

#endif // QRSLTEXPRMNGR_H
