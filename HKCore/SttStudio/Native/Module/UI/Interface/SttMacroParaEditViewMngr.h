#ifndef STTMACROPARAEDITVIEWMNGR_H
#define STTMACROPARAEDITVIEWMNGR_H

#include "SttMacroParaEditInterface.h"

class CSttMacroParaEditViewMngr			//���Թ��ܲ�����ͼ������
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

	//���ݲ��Թ���ID����Ψһ�Ĳ��Թ��ܲ�����ͼ����
	static void DeleteSttMacroParaEditViewHtml();
	static CSttMacroParaEditInterface* CreateSttMacroParaEditView(const CString &strMacroID,const CString &strGridFile, BOOL bUseExist=TRUE);
	static CSttMacroParaEditInterface* GetSttMacroParaEditViewHtml();//zhouhj 20220221 ��ȡ��ҳ��ͼ,������ʾϵͳ������ͨ��ӳ���
	static CString GetCurMacroID() { return g_pSttMacroParaEditViewMngr->m_strMacroID; };
	static void* SttMacroParaEditViewHtmlForDelete()	{	return g_pSttMacroParaEditViewMngr->m_pSttMacroParaEditViewHtmlForDelete; }
	static void ClearSttMacroParaEditViewHtmlForDelete()	{	g_pSttMacroParaEditViewMngr->m_pSttMacroParaEditViewHtmlForDelete = NULL; }


	void Clear(void *pView);
	void DeletePrev();
};


#endif // STTMACROPARAEDITVIEWMNGR_H
