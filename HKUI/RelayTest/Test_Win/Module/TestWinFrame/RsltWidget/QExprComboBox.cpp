#include "QExprComboBox.h"
#include "../../../../Module/SttTest/Common/tmt_test_mngr.h"

QExprComboBox::QExprComboBox(CDataGroup *pList, char *pszExprRef, QWidget *parent)
	: QComboBox(parent)
{
	SetExprGroup(pList);
	SetExprRef(pszExprRef);

	SetEditingFinished();
}

QExprComboBox::~QExprComboBox()
{

}

void QExprComboBox::SetExprGroup( CDataGroup *pList)
{
	ASSERT(pList);
	m_pList = pList;

	clear();

	POS pos = m_pList->GetHeadPosition();
	int i = 0;
	CDvmData *pData = NULL;
	CString strExprText;
	
	while (pos != NULL)
	{
		pData = (CDvmData*)m_pList->GetNext(pos);

		//调用将表达式转换成文本的函数
		strExprText = g_oTmtTestRsltExprImp.GetExprScriptText(pData->m_strValue);

		insertItem(i++,strExprText);
	}
}
void QExprComboBox::SetExprRef(char *pszExprRef)
{
	m_pszExprRef = pszExprRef;
	disconnect(this,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_currentIndexChanged(int)));

	long nIndex = 0;

	//根据pszExprRef 获得编号  m_pList中查找
	CDvmData *pFind = m_pList->FindDataByValue(pszExprRef);
	nIndex = m_pList->FindIndex(pFind);

	setCurrentIndex(nIndex);

	connect(this,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_currentIndexChanged(int)));
}

void QExprComboBox::slot_currentIndexChanged( int nIndex)
{
	CDvmData *pFind = (CDvmData*)m_pList->GetAtIndex(nIndex);
	
	if (pFind != NULL)
	{
		CString_to_char(pFind->m_strValue, m_pszExprRef);
	}
}

//mym 2021-7-22 增加了可以编辑combox 属性，把编辑框么有的内容添加到list中；
void QExprComboBox::SetEditingFinished()
{
	QLineEdit * pLineEdit = this->lineEdit();
	QObject::connect(pLineEdit,	 SIGNAL(returnPressed()),  this ,SLOT(slot_EditingFinished()));//editingFinished
}

void QExprComboBox::slot_EditingFinished()
{

}

