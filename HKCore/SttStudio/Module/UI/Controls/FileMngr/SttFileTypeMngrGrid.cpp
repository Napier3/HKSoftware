#include "SttFileTypeMngrGrid.h"
#include "../../../../../Module/DataMngr/DvmData.h"
#include "../../../XLangResource_Native.h"
#include "SttFileMngrChildren.h"
#include <QApplication>
#include <QProcess>


CFileTypeMngrGrid::CFileTypeMngrGrid(QWidget* pParent): QExBaseListGridBase(pParent)
{
	//m_nAdjustBeginCol = 1;
	InitGrid();
	m_bRunning = FALSE;
	installEventFilter(this);
}

CFileTypeMngrGrid::~CFileTypeMngrGrid()
{

}


void CFileTypeMngrGrid::InitGrid()
{

	InitGridTitle();
	SetDefaultRowHeight(50);
}

void CFileTypeMngrGrid::InitGridTitle()
{
	CString cTempStr[3]={/*_T("�ļ�������")*/g_sLangTxt_FileMngr_FolderName,/*_T("�ļ���˵��")*/g_sLangTxt_FileMngr_FolderIllustrate,/*_T("��С")*/g_sLangTxt_Size2};
	int iWidth[3]={300, 400,100};

	QExBaseListGridBase::InitGridTitle(cTempStr, iWidth, 3);

}

void CFileTypeMngrGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{

	if (pData->GetClassID() != DVMCLASSID_CDVMDATA)
	{
		return;
	}

	CDvmData *pDvmData = (CDvmData*) pData;

	Show_StaticString(pData, nRow,0, &pDvmData->m_strName);
	CString strFileType;
	strFileType = pDvmData->m_strDataType;
	CString strChildNodeID;
	strChildNodeID.Format("%s_FileType",pDvmData->m_strID.GetString());//zhouhj 2024.3.4 �ӽڵ��ID�������Ӹ��ڵ��ID,��������Դ���������
	CExBaseObject *pCurrObj = pDvmData->FindByID(strChildNodeID);

	if (pCurrObj != NULL)
	{
		strFileType = pCurrObj->m_strName;
	}

//	pDvmData->GetValueByID("FileType",strFileType);//zhouhj 2024.2.26  �����ļ������ӽڵ�ʱ,���ļ������ӽڵ��е�Ϊ׼
	Show_StaticString(pData, nRow,1, strFileType);
	Show_StaticString(pData, nRow,2,&pDvmData->m_strMax);

	nRow++;
}

bool CFileTypeMngrGrid::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonDblClick)
	{
		QMouseEvent *pMouseEvent = (QMouseEvent *)event;
		m_bRunning = TRUE;
		mouseDoubleClickEvent((QMouseEvent *)pMouseEvent);
		m_bRunning = FALSE;
		return  true;
	}

	return QExBaseListGridBase::eventFilter(obj,event);

}

void CFileTypeMngrGrid::mousePressEvent(QMouseEvent * event)
{
	if (m_bRunning)
	{
		QExBaseListGridBase::mousePressEvent(event);
		return;
	}

	QMouseEvent *pEvent = new QMouseEvent(QEvent::MouseButtonDblClick,event->pos(),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
	QApplication::postEvent(this,pEvent);
	QExBaseListGridBase::mousePressEvent(event);

}
