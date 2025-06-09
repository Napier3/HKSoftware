#include "QCIFeatureAddDig.h"
#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../XLangResource_Native.h"

QCIFeatureAddDig::QCIFeatureAddDig(const CString &strCharLibPath,QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	CCharacteristicXmlRWKeys::Create();
	CString strTitle;
	xlang_GetLangStrByFile(strTitle, "CharLib_AddChar");
	setWindowTitle(strTitle);
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);
	m_oLib.OpenXmlFile(strCharLibPath,CCharacteristicXmlRWKeys::CCharacteristicLibKey(),CCharacteristicXmlRWKeys::g_pXmlKeys);
	Init();
	InitConnect();
    InitLanguage();
}

QCIFeatureAddDig::~QCIFeatureAddDig()
{
	CCharacteristicXmlRWKeys::Release();
}

void QCIFeatureAddDig::InitLanguage()
{
    xlang_SetLangStrToWidget_Txt(ui.pbn_Ok, g_sLangTxt_OK, XLang_Ctrls_QPushButton);
    xlang_SetLangStrToWidget_Txt(ui.pbn_Cancel, g_sLangTxt_Cancel, XLang_Ctrls_QPushButton);
}

void QCIFeatureAddDig::Init()
{
	ui.treeWidget->setStyle(QStyleFactory::create("windows"));
	POS pos = m_oLib.GetHeadPosition();
 	CCharacterFolder *pForder = NULL;
 	CCharacteristic *pChara = NULL;

 	while(pos)
 	{
 		CExBaseObject *pObj = m_oLib.GetNext(pos);
 		if (pObj->GetClassID() == CHARCLASSID_CCHARFOLDER)
 		{
 			pForder = (CCharacterFolder*)pObj;
 			QTreeWidgetItem *topItem = new QTreeWidgetItem(ui.treeWidget);
 			topItem->setText(0,pForder->m_strName);
			ui.treeWidget->addTopLevelItem(topItem);
 
			RecursionShowObj(pForder,topItem);
 		}
		else if (pObj->GetClassID() == CHARCLASSID_CCHARACTERISTIC)
		{
			pChara = (CCharacteristic*)pObj;
			QTreeWidgetItem *topItem = new QTreeWidgetItem(ui.treeWidget);
			topItem->setText(0,pChara->m_strName);
			ui.treeWidget->addTopLevelItem(topItem);
		}
	}
	
}

void QCIFeatureAddDig::RecursionShowObj( CExBaseList *pList , QTreeWidgetItem *pTreeItem)
{
	POS pos = pList->GetHeadPosition();
	
	while(pos)
	{
		CExBaseObject *pObj = pList->GetNext(pos);
		if (pObj->GetClassID() == CHARCLASSID_CCHARFOLDER)
		{
			CCharacterFolder *pForder = (CCharacterFolder*)pObj;
			QTreeWidgetItem *Item = new QTreeWidgetItem(pTreeItem);
			Item->setText(0,pForder->m_strName);

			RecursionShowObj(pForder,Item);
		}
		else if (pObj->GetClassID() == CHARCLASSID_CCHARACTERISTIC)
		{
			CCharacteristic *pChara = (CCharacteristic*)pObj;
			QTreeWidgetItem *Item = new QTreeWidgetItem(pTreeItem);
			Item->setText(0,pChara->m_strName);
		}
	}
}

void QCIFeatureAddDig::InitConnect()
{
	connect(ui.pbn_Ok, SIGNAL(clicked ()), this, SLOT(slot_PbnOkClicked()));
	connect(ui.pbn_Cancel, SIGNAL(clicked ()), this, SLOT(slot_PbnCancelClicked()));
}
void QCIFeatureAddDig::slot_PbnOkClicked()
{
// 	QTreeWidgetItem *item = ui.treeWidget->currentItem();
// 
// 	CCharacteristic *pChara = NULL;
// 	
// 	pChara = m_oLib.FindCharTempByName(item->text(0));
// 
// 	if (pChara == NULL)
// 	{
// 		pChara = RecursionFindObj(&m_oLib,item->text(0));
// 	}
// 	emit sig_clickOK(pChara);
// 
// 	close();
	accept();
}

CCharacteristic* QCIFeatureAddDig::GetSelectedChar()
{
	QTreeWidgetItem *item = ui.treeWidget->currentItem();

	CCharacteristic *pChara = NULL;

	pChara = m_oLib.FindCharTempByName(item->text(0));

	if (pChara == NULL)
	{
		pChara = RecursionFindObj(&m_oLib,item->text(0));
	}

	return pChara;
}

CCharacteristic* QCIFeatureAddDig::RecursionFindObj( CExBaseList *pList,CString strName )
{
	CCharacteristic* pChar = NULL;

	POS pos = pList->GetHeadPosition();
	while(pos)
	{
		CExBaseObject *pObj = pList->GetNext(pos);

		if (pObj->GetClassID() == CHARCLASSID_CCHARFOLDER)
		{
			CCharacterFolder *pForder = (CCharacterFolder*)pObj;
			
			pChar = pForder->FindCharTempByName(strName);

			if (pChar == NULL)
			{
				pChar = RecursionFindObj(pForder,strName);
				if (pChar != NULL)
				{
					return pChar;
				}
			}
			else
			{
				return pChar;
			}
		}
	}

	return pChar;
}

void QCIFeatureAddDig::slot_PbnCancelClicked()
{
	close();
}


