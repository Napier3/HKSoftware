#include "ZKFeatureDig.h"
#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../XLangResource_Native.h"
#include "QCharElementDlg.h"

ZKFeatureDig::ZKFeatureDig(CCharacteristic *pObj,BOOL bSetting,QWidget *parent):m_pCharaObj(pObj)
	, QDialog(parent)
{
	ui.setupUi(this);
	m_bSetting = bSetting;
	m_pInterface = (CCharInterface*)m_pCharaObj->GetCharInterface();
	m_pCharArea = (CCharacterArea *)m_pCharaObj->GetCharacterArea();

	m_pInterfacebak = (CCharInterface*)m_pCharaObj->GetCharInterface()->Clone();
	m_pCharAreabak = (CCharacterArea *)m_pCharaObj->GetCharacterArea()->Clone();
	InitTableWidget();
 	InitInterfaceData();
 	InitAreaData();
        InitLanguage();
 	InitConnections();
}

ZKFeatureDig::~ZKFeatureDig()
{

}

void ZKFeatureDig::InitLanguage()
{
    xlang_SetLangStrToWidget_Txt(ui.pbn_Add, g_sLangTxt_Gradient_InsertElement, XLang_Ctrls_QPushButton);
    xlang_SetLangStrToWidget_Txt(ui.pbn_Del, g_sLangTxt_Gradient_DeleteElement, XLang_Ctrls_QPushButton);
    xlang_SetLangStrToWidget_Txt(ui.pbn_DelAll, g_sLangTxt_Native_DeleteAll, XLang_Ctrls_QPushButton);
    xlang_SetLangStrToWidget_Txt(ui.pbn_Ok, g_sLangTxt_OK, XLang_Ctrls_QPushButton);
    xlang_SetLangStrToWidget_Txt(ui.pbn_Cancel, g_sLangTxt_Cancel, XLang_Ctrls_QPushButton);
}
void ZKFeatureDig::InitTableWidget()
{
	QHeaderView* pTop = ui.tableWidget_Info->horizontalHeader();
	pTop->setClickable(false);
	pTop->setMovable(false);
	QHeaderView* pLeft = ui.tableWidget_Info->verticalHeader();
	pLeft->setDefaultSectionSize(25);
	pLeft->setVisible(false);

	ui.tableWidget_Info->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
	ui.tableWidget_Info->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	QHeaderView* pTop1 = ui.tableWidget_Info2->horizontalHeader();
	pTop1->setClickable(false);
	pTop1->setMovable(false);
	QHeaderView* pLeft1 = ui.tableWidget_Info2->verticalHeader();
	pLeft1->setDefaultSectionSize(25);
	pLeft1->setVisible(false);

	ui.tableWidget_Info2->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
	ui.tableWidget_Info2->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableWidget_Info2->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	QStringList headers;
	if (m_bSetting)
	{
		ui.tableWidget_Info->setColumnCount(5);

        headers << /* tr("编号") */ g_sLangTxt_Index << /* tr("变量名称") */ g_sLangTxt_Native_VarName
                << /* tr("变量ID") */ g_sLangTxt_VariableID << /* tr("数值") */ g_sLangTxt_Value
                << /* tr("关联定值") */ g_sLangTxt_AssociationValue;
		ui.tableWidget_Info->setHorizontalHeaderLabels(headers);
		ui.tableWidget_Info->setColumnWidth(0,40);
		ui.tableWidget_Info->setColumnWidth(1,80);
		ui.tableWidget_Info->setColumnWidth(2,80);
		ui.tableWidget_Info->setColumnWidth(3,80);
		ui.tableWidget_Info->setColumnWidth(4,200);

		CSettingDelegate *comboBox = new CSettingDelegate();
		ui.tableWidget_Info->setItemDelegateForColumn(4,comboBox);
	}
	else
	{
		ui.tableWidget_Info->setColumnCount(4);

        headers << /* tr("编号") */ g_sLangTxt_Index << /* tr("变量名称") */ g_sLangTxt_Native_VarName
                << /* tr("变量ID") */ g_sLangTxt_VariableID << /* tr("数值") */ g_sLangTxt_Value;
		ui.tableWidget_Info->setHorizontalHeaderLabels(headers);
		ui.tableWidget_Info->setColumnWidth(0,40);
		ui.tableWidget_Info->setColumnWidth(1,80);
		ui.tableWidget_Info->setColumnWidth(2,80);
		ui.tableWidget_Info->setColumnWidth(3,80);
	}

	QStringList headers_2;
	ui.tableWidget_Info2->setColumnCount(5);

    headers_2 << /* tr("编号") */ g_sLangTxt_Index << /* tr("边类型") */ g_sLangTxt_EdgeType
              << /* tr("测点数") */ g_sLangTxt_TestPoint << /* tr("误差带") */ g_sLangTxt_ErrorBand
              << /* tr("边详细信息") */ g_sLangTxt_EdgeDetails;
	ui.tableWidget_Info2->setHorizontalHeaderLabels(headers_2);
	ui.tableWidget_Info2->setColumnWidth(0,40);
	ui.tableWidget_Info2->setColumnWidth(1,80);
	ui.tableWidget_Info2->setColumnWidth(2,60);
	ui.tableWidget_Info2->setColumnWidth(3,100);
	ui.tableWidget_Info2->setColumnWidth(4,400);
}

void ZKFeatureDig::InitConnections()
{
	connect(ui.tableWidget_Info, SIGNAL(cellChanged ( int , int  )), this, SLOT(slot_Table_cellChanged ( int , int  )));
	connect(ui.tableWidget_Info2, SIGNAL(cellDoubleClicked ( int , int  )), this, SLOT(slot_Double_Clicked ( int , int  )));
	connect(ui.pbn_Add, SIGNAL(clicked ()), this, SLOT(slot_PbnAddClicked()));
	connect(ui.pbn_Del, SIGNAL(clicked ()), this, SLOT(slot_PbnDelClicked()));
	connect(ui.pbn_DelAll, SIGNAL(clicked ()), this, SLOT(slot_PbnDelAllClicked()));
	connect(ui.pbn_Ok, SIGNAL(clicked ()), this, SLOT(slot_PbnOkClicked()));
	connect(ui.pbn_Cancel, SIGNAL(clicked ()), this, SLOT(slot_PbnCancelClicked()));
}
void ZKFeatureDig::slot_PbnAddClicked()
{
	QCharElementDlg dlg(NULL,this);
	dlg.exec();

	if (dlg.m_nIsOK == 1)
	{
		CCharElement *pNew = dlg.GetNewElement();
		if (pNew->GetClassID() == CHARCLASSID_CCHARELEMENTMHO)
		{
			m_pCharArea->DeleteChildren();
		}
		m_pCharArea->AddTail(pNew);
		InitAreaData();
		emit sig_ZKChanged();
	}
}

void ZKFeatureDig::slot_PbnDelClicked()
{
	CCharElement *pObj = (CCharElement*)m_pCharArea->GetAtIndex(ui.tableWidget_Info2->currentRow());
	m_pCharArea->Delete(pObj);
	InitAreaData();
	emit sig_ZKChanged();
}

void ZKFeatureDig::slot_PbnOkClicked()
{
	/*m_pCharaObj->SetCharInterface(m_pInterface);*/
// 	CCharInterface *pInterface = m_pCharaObj->GetCharInterface();
// 	CCharacterArea *pCharArea = m_pCharaObj->GetCharacterArea();
// 
// 	m_pCharArea->Copy(pCharArea);
// 	m_pInterface->Copy(pInterface);

	close();
}

void ZKFeatureDig::slot_PbnCancelClicked()
{
	m_pCharAreabak->Copy(m_pCharArea);
	m_pInterfacebak->Copy(m_pInterface);

	delete m_pCharAreabak;
	m_pCharAreabak = NULL;

	delete m_pInterfacebak;
	m_pInterfacebak = NULL;

	close();
}

void ZKFeatureDig::InitInterfaceData()
{
	CCharInterfaceVariable *pCurObj = NULL;

	POS pos = m_pInterface->GetHeadPosition();
	int i = 0;
	while(pos)
	{
		pCurObj = (CCharInterfaceVariable*)m_pInterface->GetNext(pos);
		
		ui.tableWidget_Info->insertRow(i);
		QTableWidgetItem* pitem1 = new QTableWidgetItem(QString::number(i+1));
		pitem1->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter );
		pitem1->setFlags(Qt::ItemIsEditable);
		ui.tableWidget_Info->setItem(i,0,pitem1);

		QTableWidgetItem* pitem5 = new QTableWidgetItem(pCurObj->m_strName);
		pitem5->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter );
		pitem5->setFlags(Qt::ItemIsEditable);
		ui.tableWidget_Info->setItem(i,1,pitem5);

		QTableWidgetItem* pitem2 = new QTableWidgetItem(pCurObj->m_strID);
		pitem2->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter );
		pitem2->setFlags(Qt::ItemIsEditable);
		ui.tableWidget_Info->setItem(i,2,pitem2);

 		QTableWidgetItem* pitem3 = new QTableWidgetItem(pCurObj->m_strValue);
 		pitem3->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter );
 		ui.tableWidget_Info->setItem(i,3,pitem3);
 
		if (m_bSetting)
		{
			QTableWidgetItem* pitem4 = new QTableWidgetItem(g_TestWinBase->GetSetName(pCurObj->m_strScript));
			pitem4->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter );
			ui.tableWidget_Info->setItem(i,4,pitem4);
		}
		
		i++;
	}
}

void ZKFeatureDig::InitAreaData()
{
	ui.tableWidget_Info2->setRowCount(0);

	CCharElement *pCurObj = NULL;

	POS pos = m_pCharArea->GetHeadPosition();
	int i = 0;
	while(pos)
	{
		pCurObj = (CCharElementLined*)m_pCharArea->GetNext(pos);

		ui.tableWidget_Info2->insertRow(i);
		QTableWidgetItem* pitem1 = new QTableWidgetItem(QString::number(i+1));
		pitem1->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter );
		ui.tableWidget_Info2->setItem(i,0,pitem1);

		QTableWidgetItem* pitem2 = new QTableWidgetItem(/* QObject::tr("线段(lined)") */ g_sLangTxt_Lined);
		pitem2->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter );
		ui.tableWidget_Info2->setItem(i,1,pitem2);

		long *nTestPoint = pCurObj->GetTestPointsRef();
		QTableWidgetItem* pitem3 = new QTableWidgetItem(QString::number(*nTestPoint));
		pitem3->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter );
		ui.tableWidget_Info2->setItem(i,2,pitem3);

		QTableWidgetItem* pitem4 = new QTableWidgetItem(pCurObj->m_strErrLength);
		pitem4->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter );
		ui.tableWidget_Info2->setItem(i,3,pitem4);

		QString strInfo;
		if (pCurObj->GetClassID() == CHARCLASSID_CCHARELEMENTLINED)
		{
            pitem2->setText(/* QObject::tr("线段(lined)") */ g_sLangTxt_Lined);
			CCharElementLined *pChar = (CCharElementLined *)pCurObj;
			strInfo = pChar->ReturnXml();
		}
		else if (pCurObj->GetClassID() == CHARCLASSID_CCHARELEMENTMHO)
		{
            pitem2->setText(/* QObject::tr("圆(mho)") */ g_sLangTxt_Mho);
			CCharElementMho *pChar = (CCharElementMho *)pCurObj;
			strInfo = pChar->ReturnXml();
		}
		else if (pCurObj->GetClassID() == CHARCLASSID_CCHARELEMENTLENS)
		{
            pitem2->setText(/* QObject::tr("透镜(lens)") */ g_sLangTxt_Lens);
			CCharElementLens *pChar = (CCharElementLens *)pCurObj;
			strInfo = pChar->ReturnXml();
		}
		else if (pCurObj->GetClassID() == CHARCLASSID_CCHARELEMENTLINER)
		{
            pitem2->setText(/* QObject::tr("射线(liner)") */ g_sLangTxt_Liner);
			CCharElementLiner *pChar = (CCharElementLiner *)pCurObj;
			strInfo = pChar->ReturnXml();
		}
		else if (pCurObj->GetClassID() == CHARCLASSID_CCHARELEMENTLINE)
		{
            pitem2->setText(/* QObject::tr("直线(line)") */ g_sLangTxt_Line);
			CCharElementLine *pChar = (CCharElementLine *)pCurObj;
			strInfo = pChar->ReturnXml();
		}
		else if (pCurObj->GetClassID() == CHARCLASSID_CCHARELEMENTARC)
		{
            pitem2->setText(/* QObject::tr("圆弧(arc)") */ g_sLangTxt_Arc);
			CCharElementArc *pChar = (CCharElementArc *)pCurObj;
			strInfo = pChar->ReturnXml();
		}
		else if (pCurObj->GetClassID() == CHARCLASSID_CCHARELEMENTARCP)
		{
            pitem2->setText(/* QObject::tr("圆弧(arcp)") */ g_sLangTxt_Arcp);
			CCharElementArcp *pChar = (CCharElementArcp *)pCurObj;
			strInfo = pChar->ReturnXml();
		}
		QTableWidgetItem* pitem5 = new QTableWidgetItem(strInfo);
		pitem5->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter );
		ui.tableWidget_Info2->setItem(i,4,pitem5);

		i++;
	}
}

void ZKFeatureDig::slot_Table_cellChanged( int nRow, int nCol)
{
	if (nRow < 0)
	{
		return;
	}

	disconnect(ui.tableWidget_Info, SIGNAL(cellChanged ( int , int  )), this, SLOT(slot_Table_cellChanged ( int , int  )));
	
	ui.tableWidget_Info->setCurrentCell(nRow,nCol);
	CCharInterfaceVariable *pObj = (CCharInterfaceVariable*)m_pInterface->GetAtIndex(nRow);

	if (m_bSetting)
	{
		if (nCol == 3)
		{
			QTableWidgetItem *pItem2 = ui.tableWidget_Info->item(nRow, 3);
			QTableWidgetItem *pItem3 = ui.tableWidget_Info->item(nRow, 4);
			pItem3->setText(QString(tr("")));
			pObj->m_strValue = pItem2->text();
			pObj->m_strScript = _T("");
		}
		else if (nCol == 4)
		{
			QTableWidgetItem *pItem2 = ui.tableWidget_Info->item(nRow, 3);
			QTableWidgetItem *pItem3 = ui.tableWidget_Info->item(nRow, 4);

			CDvmData *pData = (CDvmData*)g_pTmt_SetsRef->FindByName(pItem3->text());
			if (pData != NULL)
			{
				pObj->m_strScript = pData->m_strID;
				pObj->m_strValue = pData->m_strValue;
			}
			else
			{
				pObj->m_strScript = _T("");
				pObj->m_strValue = _T("0");
			}
			pItem3->setText(g_TestWinBase->GetSetName(pObj->m_strScript));
			pItem2->setText(pObj->m_strValue);

		}
	}
	else
	{
		if (nCol == 3)
		{
			QTableWidgetItem *pItem2 = ui.tableWidget_Info->item(nRow, 3);
			pObj->m_strValue = pItem2->text();
		}
	}

	emit sig_ZKChanged();
	
	connect(ui.tableWidget_Info, SIGNAL(cellChanged ( int , int  )), this, SLOT(slot_Table_cellChanged ( int , int  )));

}

void ZKFeatureDig::slot_Double_Clicked( int nRow, int nCol)
{
	if (nRow < 0)
	{
		return;
	}

	ui.tableWidget_Info2->setCurrentCell(nRow,nCol);
	CCharElement *pObj = (CCharElement*)m_pCharArea->GetAtIndex(nRow);
	
	QCharElementDlg dlg(pObj,this);
	dlg.exec();

	if (dlg.m_nIsOK == 1)
	{
		if (dlg.GetNewElement()->GetClassID() == CHARCLASSID_CCHARELEMENTMHO)
		{
			m_pCharArea->DeleteChildren();
			m_pCharArea->AddNewChild(dlg.GetNewElement());
		}
		else
		{
			if (pObj->GetClassID() == dlg.GetNewElement()->GetClassID())
			{
				dlg.GetNewElement()->Copy(pObj);
			}
			else
			{
				m_pCharArea->Delete(pObj);
				m_pCharArea->AddNewChild(dlg.GetNewElement());
			}
		}
		emit sig_ZKChanged();
	}

	InitAreaData();
}

void ZKFeatureDig::slot_PbnDelAllClicked()
{
	m_pCharArea->DeleteChildren();

	InitAreaData();
	emit sig_ZKChanged();
}

///////////////////////////////////////////////////////////////////////

CSettingDelegate::CSettingDelegate(QObject *parent /*= NULL*/ )
{

}

CSettingDelegate::~CSettingDelegate()
{

}

QWidget * CSettingDelegate::createEditor( QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
	QVariant variant = index.data();

	QComboBox *comboBox = new QComboBox(parent);
	return comboBox;
}

void CSettingDelegate::setEditorData( QWidget * editor, const QModelIndex &index ) const
{
	QString strItem = index.model()->data(index,Qt::EditRole).toString();
	QStringList strItemList;
	strItemList<<g_TestWinBase->GetSetName("Zeset1")<<g_TestWinBase->GetSetName("Zeset2")<<g_TestWinBase->GetSetName("Zeset3")
		<<g_TestWinBase->GetSetName("Zeset4")<<g_TestWinBase->GetSetName("Zeset5")<<g_TestWinBase->GetSetName("Zxset1")
		<<g_TestWinBase->GetSetName("Zxset2")<<g_TestWinBase->GetSetName("Zxset3")<<g_TestWinBase->GetSetName("Zxset4")
		<<g_TestWinBase->GetSetName("Zxset5");

	QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
	comboBox->clear();
	int id = 0;
	for (int i=0; i<strItemList.size(); i++)
	{
		QString strValue = strItemList.at(i);
		if (strValue == strItem)
		{
			id = i;
		}
		comboBox->addItem(strValue);
	}
	comboBox->setCurrentIndex(id);
}

void CSettingDelegate::setModelData( QWidget *editor, QAbstractItemModel *model, const QModelIndex &index ) const
{
	QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
	model->setData(index,comboBox->currentText(),Qt::EditRole);
}

void CSettingDelegate::updateEditorGeometry( QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
	editor->setGeometry(option.rect);
}
