#include "SttWgtBase.h"
#include "SttWgtFactory.h"
#include "../Ctrls/SttWgtNativeMainLinux.h"
#include <QFont>

QSttWgtBase::QSttWgtBase(QWidget* pParent)
{
	m_pParent = pParent;
	m_pWgtRef = NULL;
	m_pXuiData = NULL;
}

QSttWgtBase::~QSttWgtBase()
{
// 	if(m_pWgtRef)//该指针对象就是自身,无意义
// 	{
// 		delete m_pWgtRef;
// 		m_pWgtRef = NULL;
// 	}
//
// 	if(m_pXuiData)//防止重复删除
// 	{
// 		delete m_pXuiData;
// 		m_pXuiData = NULL;
// 	}
}

void QSttWgtBase::InitUI(CExBaseObject *pSttXuiData)
{
	if (pSttXuiData)
	{
		InitUIOwn(pSttXuiData);
		InitUIChildren(pSttXuiData);
	}
}

void QSttWgtBase::InitUIOwn(CExBaseObject *pSttXuiData)
{

}

void QSttWgtBase::InitUIChildren(CExBaseObject *pSttXuiData)
{

}

QSttWgtBase* QSttWgtBase::FindWgtBase(CExBaseObject *pXuiData)
{
	return 0;
}

QSttWgtStyle* QSttWgtBase::GetWgtStyle(const CString& strStyleType, const CString& strStyleID)
{
	CExBaseList* pStyleType = (CExBaseList*)m_gQSttWgtNativeMainLinux->m_pGlobalStyle->FindByID(strStyleType);
	return (QSttWgtStyle*)pStyleType->FindByID(strStyleID);
}

void QSttWgtBase::SetWgtStyle(QWidget* pWidget, QSttWgtStyle* pStyle)
{
	if(!pStyle)
	{
		return;
	}

//#ifdef _PSX_QT_LINUX_
	QFont font = pWidget->font();
	font.setPointSize(pStyle->m_nSize);
	pWidget->setFont(font);
//#endif
}