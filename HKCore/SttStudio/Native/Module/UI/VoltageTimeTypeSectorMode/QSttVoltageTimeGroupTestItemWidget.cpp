#include "../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../SttTestCntrFrameBase.h"
#include "../../SttGlobalDef.h"
#include "../Controls/SttTabWidget.h"
#include "../Module/XLangResource_Native.h"
#include "../../Module/XLanguage/XLanguageResource.h"
#include "../Module/UI/Module/FAParasSetWidget/QSttFAParasSetDialog.h"
#include "QSttVoltageTimeGroupTestItemWidget.h"
#include <QHeaderView>
#include <QCheckBox>
#include "QSttMacroParaEditViewVolTimeTypeSec.h"
#include "../../UI/Controls/SttCheckBox.h"


QSttVoltageTimeGroupTestItemWidget::QSttVoltageTimeGroupTestItemWidget(QWidget *parent) :
ui(new Ui::QSttVoltageTimeGroupTestItemWidget)
{
	ui->setupUi(this);
	OpenTestTestMngrFile(_T(""));
	InitUI();
	InitConnections();

	//SetDatas(&m_oVolTimeTypeSecDataGroup);
}

QSttVoltageTimeGroupTestItemWidget::~QSttVoltageTimeGroupTestItemWidget()
{

}

void QSttVoltageTimeGroupTestItemWidget::GetDatas(CDataGroup *pParas)
{
	ASSERT(pParas != NULL);
	//pParas->DeleteAll();

	// 	POS pos = m_oVolTimeTypeSecDataGroup.GetHeadPosition();
	// 	CDvmData *pDvmData = NULL;
	// 	long nIndex = 0;
	// 	while(pos)
	// 	{
	// 		pDvmData = (CDvmData *)m_oVolTimeTypeSecDataGroup.GetNext(pos);
	// 		m_oVolTimeTypeSecDataGroup.SetDataValue(pDvmData->m_strID, m_nItemSelect[nIndex]);
	// 		nIndex ++ ; 
	// 	}
	// 
	// 	m_oVolTimeTypeSecDataGroup.CopyChildren(pParas);
}

void QSttVoltageTimeGroupTestItemWidget::InitSOEDatas()
{
	g_pVolTimeTypeSecTestMain->m_TotalDynamicList.DeleteAll();
	CString strID = "";
	CString strValue = "";
	CString strDefaultValue = "";
	CString strName = "";
	int statusCounts[] = {5, 5, 7, 9, 7, 7};
	for (int i = 0; i < 6; i++)
	{
		CDataGroup *pDataGroup = new CDataGroup;
		strID.Format(_T("TestItem%d"), i + 1);
		pDataGroup->m_strID = strID;

		int innerLoopCount = statusCounts[i];

		for(int j = 0; j < innerLoopCount; j++)
		{
			CDvmData *pDvmData = new CDvmData;
			strName.Format(_T("״̬%d"), j+1); 
			pDvmData->m_strName = strName;
			//strValue.Format(_T("��λ%d"), j+1); 
			//pDvmData->m_strValue = strValue;
			//strDefaultValue.Format(_T("��λ%d"), j+1);
			//pDvmData->m_strDefaultValue = strDefaultValue;
			pDataGroup->AddNewChild(pDvmData);
		}
		g_pVolTimeTypeSecTestMain->m_TotalDynamicList.AddNewChild(pDataGroup, 0);
	}
}

void QSttVoltageTimeGroupTestItemWidget::InitUI()
{
	InitStyle();
	ui->m_pVolTimeTypeTestItemTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->m_pVolTimeTypeTestItemTableWidget->setHorizontalHeaderLabels(QStringList() << g_sLtxt_SICDSelect << 
		g_sLangTxt_Name << g_sLangTxt_Status); 
	ui->m_pVolTimeTypeTestItemTableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //���ñ�ͷ����ɫ
	ui->m_pVolTimeTypeTestItemTableWidget->setStyleSheet("selection-background-color: grey;selection-color: black");

	POS pos = m_oVolTimeTypeSecDataGroup.GetHeadPosition();
	CDvmData *pDvmData  = NULL;
	long nIndex = 0;
	while(pos)
	{
		pDvmData = (CDvmData *)m_oVolTimeTypeSecDataGroup.GetNext(pos);
		QTableWidgetItem *pNameItem = new QTableWidgetItem();//����
		pNameItem->setText(pDvmData->m_strName);
		pNameItem->setTextAlignment(Qt::AlignCenter); // �����ı����ж���
		ui->m_pVolTimeTypeTestItemTableWidget->setItem(nIndex,1,pNameItem);
		// ����ѡ����벼��
		m_pCheckBox = new QSttCheckBox();
		if (pDvmData->m_strValue == _T("1"))
		{
			m_pCheckBox->setChecked(true); // ��� value �� "1"�������ø�ѡ��Ϊѡ��״̬
		}
		else
		{
			m_pCheckBox->setChecked(false); // �������ø�ѡ��Ϊδѡ��״̬
		}
		// ����ѡ����벼��
		QWidget *pWidget = new QWidget();
		QHBoxLayout *pLayout = new QHBoxLayout(pWidget);
		pLayout->addWidget(m_pCheckBox);
		pLayout->setContentsMargins(0, 0, 0, 0);
		pLayout->setAlignment(m_pCheckBox, Qt::AlignCenter);
		pWidget->setLayout(pLayout);

		// ���õ�Ԫ����Զ���ؼ�
		ui->m_pVolTimeTypeTestItemTableWidget->setCellWidget(nIndex, 0, pWidget);
		checkBoxList.append(m_pCheckBox); // ����ѡ������б�
		nIndex++;
	}
}

void QSttVoltageTimeGroupTestItemWidget::InitStyle()
{

	// ��ֹ��ͷ���
    ui->m_pVolTimeTypeTestItemTableWidget->horizontalHeader()->setSectionsClickable(false);
	// ��ֹ��ͷ��С�޸�
    ui->m_pVolTimeTypeTestItemTableWidget->horizontalHeader()->setSectionsMovable(false);
    ui->m_pVolTimeTypeTestItemTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

	ui->m_pVolTimeTypeTestItemTableWidget->setColumnCount(3);
	ui->m_pVolTimeTypeTestItemTableWidget->setRowCount(m_oVolTimeTypeSecDataGroup.GetCount());
	ui->m_pVolTimeTypeTestItemTableWidget->verticalHeader()->setVisible(false);
	ui->m_pVolTimeTypeTestItemTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->m_pVolTimeTypeTestItemTableWidget->resizeRowsToContents();
	ui->m_pVolTimeTypeTestItemTableWidget->setFont(*g_pSttGlobalFont);
	ui->m_pVolTimeTypeTestItemTableWidget->horizontalHeader()->setFont(*g_pSttGlobalFont);
	ui->m_CheckBoxSelectAll->setFont(*g_pSttGlobalFont);
	ui->m_CheckBoxUnSelectAll->setFont(*g_pSttGlobalFont);

	// ���ñ���п�
    ui->m_pVolTimeTypeTestItemTableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->m_pVolTimeTypeTestItemTableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->m_pVolTimeTypeTestItemTableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
}

void QSttVoltageTimeGroupTestItemWidget::InitConnections()
{
	foreach (m_pCheckBox, checkBoxList) 
	{
		connect(m_pCheckBox, SIGNAL(clicked(bool)), this, SLOT(slot_CheckBoxClicked(bool)));
	}
	connect(ui->m_pVolTimeTypeTestItemTableWidget, SIGNAL(cellClicked(int, int)), this, SLOT(slot_TableWidgetClicked(int, int)));
	connect(ui->m_CheckBoxSelectAll, SIGNAL(clicked(bool)), this, SLOT(slot_SelectAllClicked(bool)));
	connect(ui->m_CheckBoxUnSelectAll, SIGNAL(clicked(bool)), this, SLOT(slot_UnSelectAllClicked(bool)));
}


// ȫѡ�Ĳۺ���
void QSttVoltageTimeGroupTestItemWidget::slot_SelectAllClicked(bool checked)
{
	for (int row = 0; row < ui->m_pVolTimeTypeTestItemTableWidget->rowCount(); ++row)
	{
		QWidget *pWidget = ui->m_pVolTimeTypeTestItemTableWidget->cellWidget(row, 0);
		if (pWidget != NULL)
		{
			QList<QWidget*> childWidgets = pWidget->findChildren<QWidget*>();
			foreach (QWidget *pChildWidget, childWidgets)
		{
				QCheckBox *pCheckBox = qobject_cast<QCheckBox*>(pChildWidget);
				if (pCheckBox != NULL)
			{
					pCheckBox->setChecked(true);
					break;
				}
			}
		}
	}
	ui->m_CheckBoxUnSelectAll->setChecked(false);
}

// ȫ��ѡ�Ĳۺ���
void QSttVoltageTimeGroupTestItemWidget::slot_UnSelectAllClicked(bool checked)
{
	for (int row = 0; row < ui->m_pVolTimeTypeTestItemTableWidget->rowCount(); ++row)
	{
		QWidget *pWidget = ui->m_pVolTimeTypeTestItemTableWidget->cellWidget(row, 0);
		if (pWidget != NULL)
	{
			QList<QWidget*> childWidgets = pWidget->findChildren<QWidget*>();
			foreach (QWidget *pChildWidget, childWidgets)
		{
				QCheckBox *pCheckBox = qobject_cast<QCheckBox*>(pChildWidget);
				if (pCheckBox != NULL)
		{
					pCheckBox->setChecked(false);
					break;
				}
			}
		}
	}
	ui->m_CheckBoxSelectAll->setChecked(false);
}

BOOL QSttVoltageTimeGroupTestItemWidget::OpenTestTestMngrFile(const CString& strParasFile)
{
	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		return FALSE;
	}

	CDataGroup*  pDataGroup = g_theTestCntrFrame->GetTestMacroUI_Paras();

	if (pDataGroup->GetCount() <= 0)
	{
		return FALSE;
	}

	pDataGroup->CopyChildren(&m_oVolTimeTypeSecDataGroup);
	return TRUE;
}

void QSttVoltageTimeGroupTestItemWidget::slot_TableWidgetClicked(int row, int col)
{
	if (row < 0)
	{
		return;
	}

	if (col == 0 || col == 1 || col == 2)
	{
		m_pCheckItem = ui->m_pVolTimeTypeTestItemTableWidget->item(row, 0);
		m_pItem = ui->m_pVolTimeTypeTestItemTableWidget->item(row, 1);

		if (m_pItem == NULL)
		{
			return;
		}

		QString strText = m_pItem->text();
		CDataGroup* pCurData = (CDataGroup*)m_oVolTimeTypeSecDataGroup.FindByName(strText);
		g_pVolTimeTypeSecTestMain->m_pFAStateSequenceGroupGrid->ShowDatas(pCurData);
		SaveXmlParas();

		CString strID = pCurData->m_strID;
		CDataGroup* pSOEData = (CDataGroup*)g_pVolTimeTypeSecTestMain->m_TotalDynamicList.FindByID(strID);
		g_pVolTimeTypeSecTestMain->m_pFATestResultViewGroupGrid->ShowDatas(pSOEData);
	}
}

void QSttVoltageTimeGroupTestItemWidget::slot_CheckBoxClicked(bool checked)
{
	QSttCheckBox* senderCheckBox = qobject_cast<QSttCheckBox*>(sender()); // ��ȡ�����źŵĸ�ѡ��
	if (!senderCheckBox) 
	{
		return;
	}

	QPoint checkBoxPos = senderCheckBox->mapToGlobal(QPoint(0, 0)); // ���ؼ�����ת��Ϊȫ����Ļ����
	int rowIndex = ui->m_pVolTimeTypeTestItemTableWidget->indexAt(ui->m_pVolTimeTypeTestItemTableWidget->viewport()->mapFromGlobal(checkBoxPos)).row(); // ��ȡ��ѡ�����ڵ���

	if (rowIndex < 0) 
	{
		return;
	}

	QTableWidgetItem* m_pNameItem = ui->m_pVolTimeTypeTestItemTableWidget->item(rowIndex, 1);
	CDataGroup* m_pCurValue = (CDataGroup*)m_oVolTimeTypeSecDataGroup.FindByName(m_pNameItem->text()); // �������ƻ�ȡ���������
	CString strID = m_pCurValue->m_strID;
	CDataGroup* pSOEData = (CDataGroup*)g_pVolTimeTypeSecTestMain->m_TotalDynamicList.FindByID(strID);

	if (m_pCurValue) 
	{
		QString value = checked ? "1" : "0"; // �����ѡ��ѡ�У��򽫶�Ӧ��ֵ����Ϊ "1"����������Ϊ "0"
		m_pCurValue->m_strValue = value;
		g_pVolTimeTypeSecTestMain->m_pFAStateSequenceGroupGrid->ShowDatas(m_pCurValue);
		SaveXmlParas();

		g_pVolTimeTypeSecTestMain->m_pFATestResultViewGroupGrid->ShowDatas(pSOEData);
	}
	ui->m_pVolTimeTypeTestItemTableWidget->selectRow(rowIndex); // �Զ�ѡ�ж�Ӧ��

	bool allChecked = true;
	for (int row = 0; row < ui->m_pVolTimeTypeTestItemTableWidget->rowCount(); ++row)
	{
		QWidget* pWidget = ui->m_pVolTimeTypeTestItemTableWidget->cellWidget(row, 0);
		if (pWidget != NULL)
		{
			QCheckBox* pCheckBox = qobject_cast<QCheckBox*>(pWidget->findChild<QCheckBox*>());
			if (pCheckBox && !pCheckBox->isChecked())
			{
				allChecked = false;
				break;
			}
		}
	}
	// �������и�ѡ��״̬����ȫѡ��ť״̬
	ui->m_CheckBoxSelectAll->setChecked(allChecked);
	ui->m_CheckBoxUnSelectAll->setChecked(allChecked);
}

void QSttVoltageTimeGroupTestItemWidget::SaveXmlParas()
{
	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("atsgen/VolTimeTypeSec_Paras.xml");
	m_oVolTimeTypeSecDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

