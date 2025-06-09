#include "QItemParaEditWidgetBase.h"

extern void Global_CreateAllParaDatas(CSttMacroTestParaDatas* pSttTestParaDatas,CTestMacro *pSingleMacro);//创建全部的参数数据,对于不存在的参数数据从CTestMacro中获取

QItemParaEditWidgetBase::QItemParaEditWidgetBase(QWidget *parent)
	: QWidget(parent)
{
	m_pCurrMacroTest_External = NULL;
	m_pSingleMacroRef = NULL;
	m_oSttMacroTest_Inner.m_strName = "item";
	m_oSttMacroTest_Inner.m_strID = "item";
// 	CSttMacroTestPara *pSttMacroTestPara = (CSttMacroTestPara*)m_oSttMacroTest_Inner.CreateNewChild(STTGBXMLCLASSID_CSTTMACROPARA);
// 	m_oSttMacroTest_Inner.AddNewChild(pSttMacroTestPara);
// 	CSttMacroTestParaDatas *pSttMacroTestParaDatas = (CSttMacroTestParaDatas*)pSttMacroTestPara->CreateNewChild(STTGBXMLCLASSID_CSTTMACROPARADATAS);
// 	pSttMacroTestPara->AddNewChild(pSttMacroTestParaDatas);

}

QItemParaEditWidgetBase::~QItemParaEditWidgetBase()
{

}

void QItemParaEditWidgetBase::InitUI()
{
}

void QItemParaEditWidgetBase::InitDatas(CTestMacro *pSingleMacroRef)
{
	m_pSingleMacroRef = pSingleMacroRef;

    if (pSingleMacroRef == NULL)
    {
        return;
    }

	ASSERT(pSingleMacroRef);
	CSttMacroTestParaDatas *pSttMacroTestParaDatas = m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(TRUE,pSingleMacroRef->m_strID);

    CLogPrint::LogString(XLOGLEVEL_TRACE, _T("QItemParaEditWidgetBase::InitDatas : 1"));

	Global_CreateAllParaDatas(pSttMacroTestParaDatas, m_pSingleMacroRef);

    CLogPrint::LogString(XLOGLEVEL_TRACE, _T("QItemParaEditWidgetBase::InitDatas : 2"));

    UpdateParas(NULL);

    CLogPrint::LogString(XLOGLEVEL_TRACE, _T("QItemParaEditWidgetBase::InitDatas : 3"));
}

void QItemParaEditWidgetBase::UpdateParas(CSttMacroTest *pSttMacroTest)
{
	m_pCurrMacroTest_External = pSttMacroTest;

	if (m_pSingleMacroRef == NULL)
	{
		return;
	}

	if (m_pCurrMacroTest_External != NULL)
	{
		CSttMacroTestParaDatas *pSrcDatas = m_pCurrMacroTest_External->GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);
		CSttMacroTestParaDatas *pDstDatas = m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);
		m_oSttMacroTest_Inner.m_strName = m_pCurrMacroTest_External->m_strName;
		m_oSttMacroTest_Inner.m_strID = m_pCurrMacroTest_External->m_strID;
		pSrcDatas->CopyChildren(pDstDatas);
	}
}

//20240805 huangliang 更新外部对象数据
bool QItemParaEditWidgetBase::UpdateParaForLineEdit(CString strID, QObject *pObject)
{
	if (pObject == NULL)
		return false;
	if (!pObject->inherits("QLineEdit"))
		return false;
	QString strValue = ((QLineEdit*)pObject)->text();

	bool bRet = false;
	if (Stt_Global_IsSetting(pObject))
	{
		bRet = true;
		strValue = ((QSettingLineEdit*)pObject)->GetText();		//是定值就获取关联字符串，否则获取控件本身值
	}		
	if (!bRet)	//20240926 huangliang 添加非定值，将执行原逻辑处理
	{
		return false;
	}

	CSttMacroTestParaDatas *pSttMacroTestParaDatas_External = NULL;

	if (m_pSingleMacroRef == NULL)
	{
		return bRet;
	}
	if (m_pCurrMacroTest_External != NULL)
	{
		pSttMacroTestParaDatas_External = m_pCurrMacroTest_External->GetSttMacroTestParaDatas(TRUE, m_pSingleMacroRef->m_strID);
	}

	CSttMacroTestParaDatas *pSttMacroTestParaDatas_Inner = m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(TRUE, m_pSingleMacroRef->m_strID);
	//CSttMacroTestParaDatas *pSttMacroTestParaDatas_External = m_pCurrMacroTest_External->GetSttMacroTestParaDatas(TRUE,m_pSingleMacroRef->m_strID);

	CSttMacroTestParaData *pDataInner = (CSttMacroTestParaData *)pSttMacroTestParaDatas_Inner->FindByID(strID);
	//CSttMacroTestParaData *pDataExternal = (CSttMacroTestParaData *)pSttMacroTestParaDatas_External->FindByID(strID);

	if (pDataInner != NULL)
	{
		//pDataInner->m_strValue = strValue;
		if (pSttMacroTestParaDatas_External != NULL)
		{
			pSttMacroTestParaDatas_External->SetDataValue(strID, strValue, TRUE);
			emit sig_UpdateCurrSelGridData(m_pCurrMacroTest_External);
		}
	}

	return bRet;
}

CExBaseList * QItemParaEditWidgetBase::GetMacroTestParaDatas_Inner()
{
	if (m_oSttMacroTest_Inner.GetCount() == 0)
	{
		CSttMacroTestParaDatas *pSttMacroTestParaDatas = m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(TRUE,
			m_pSingleMacroRef->m_strID);
		Global_CreateAllParaDatas(pSttMacroTestParaDatas, m_pSingleMacroRef);
//		m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(TRUE, m_pSingleMacroRef->m_strID);
	}
	
	return m_oSttMacroTest_Inner.GetSttMacroTestParaDatas(FALSE, "");
//	return NULL;
}
