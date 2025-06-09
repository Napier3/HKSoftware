#ifndef STTMACROPARAEDITVIEWMNGR_H
#define STTMACROPARAEDITVIEWMNGR_H

#include "SttMacroParaEditInterface.h"

class CSttMacroParaEditViewMngr			//测试功能参数视图管理类
{
private:
	CSttMacroParaEditViewMngr();
	virtual ~CSttMacroParaEditViewMngr();

	static long g_nSttMacroParaEditRef;
	static CSttMacroParaEditViewMngr *g_pSttMacroParaEditViewMngr;

public:
	static CSttMacroParaEditViewMngr* Create();
	static void Release();

	CString m_strMacroID;
	CSttMacroParaEditInterface* m_pMacroParaView;
	void* m_pSttMacroParaEditViewHtml;
	void* m_pSttMacroParaEditViewHtmlForDelete;

	//根据测试功能ID生成唯一的测试功能参数视图对象
	static void DeleteSttMacroParaEditViewHtml();
	static CSttMacroParaEditInterface* CreateSttMacroParaEditView(const CString &strMacroID,const CString &strGridFile, BOOL bUseExist=TRUE);
	static CSttMacroParaEditInterface* GetSttMacroParaEditViewHtml();//zhouhj 20220221 获取网页视图,用于显示系统参数、通道映射等
	static CString GetCurMacroID() { return g_pSttMacroParaEditViewMngr->m_strMacroID; };
	static void* SttMacroParaEditViewHtmlForDelete()	{	return g_pSttMacroParaEditViewMngr->m_pSttMacroParaEditViewHtmlForDelete; }
	static void ClearSttMacroParaEditViewHtmlForDelete()	{	g_pSttMacroParaEditViewMngr->m_pSttMacroParaEditViewHtmlForDelete = NULL; }


	void Clear(void *pView);
	void DeletePrev();
};


#endif // STTMACROPARAEDITVIEWMNGR_H
