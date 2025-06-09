#include "TcpEdgeUserEditDlg.h"
#include "TcpEdgeTestDlg.h"
#include "TcpEdgeInformationDlg.h"
#include "ui_TcpEdgeUserEditDlg.h"
#include <Qsci/qscilexerjson.h>
#include <QToolButton>
#include "../../../../Module/xml/JSON/CJSON.h"

CTcpEdgeUserEditDlg::CTcpEdgeUserEditDlg(QWidget *parent) :
	CTcpEdgeFormUI(parent),
	ui(new Ui::CTcpEdgeUserEditDlg)
{
	ui->setupUi(this);
	InitWriteUI();
}

CTcpEdgeUserEditDlg::CTcpEdgeUserEditDlg(const QString& strPkg, const QString& strError) :
	CTcpEdgeFormUI(NULL),
	ui(new Ui::CTcpEdgeUserEditDlg)
{
	ui->setupUi(this);
	InitReadUI();
	QString strShowPkg = ResizePkg(strPkg);
	m_pTextBox->setText(strShowPkg);
	ui->textError->setText(strError);
	ui->textError->UsePkgAction(false);
}

QString CTcpEdgeUserEditDlg::ResizePkg(QString strPkg)
{
	if(strPkg.indexOf("{") == -1
		|| strPkg.indexOf("}") == -1)
	{
		QsciLexer* pLexer = m_pTextBox->lexer();
		delete pLexer;
		m_pTextBox->setLexer(0);
		return strPkg;
	}

	CJSON* pJson = CJSON_Parse(strPkg.toStdString().c_str());
	if(!pJson)
	{
		return strPkg;
	}

	QString strTemp = CJSON_Print(pJson);
	CJSON_Delete(pJson);
	strTemp.replace("{\n}", "{}");
	return strTemp;
}

void CTcpEdgeUserEditDlg::InitWriteUI()
{
	setWindowTitle("自定义编辑报文");
	ui->titleName->setText("自定义编辑报文");
	InitFormUI(this, ui->title);
	InitScintilla();
	m_pTextBox->setReadOnly(false);

	QAction* pAction = m_oMenu.addAction("撤销(&Z)");
	connect(pAction, SIGNAL(triggered(bool)), this, SLOT(slot_menuUndo(bool)));
	pAction = m_oMenu.addAction("重做(&Y)");
	connect(pAction, SIGNAL(triggered(bool)), this, SLOT(slot_menuRedo(bool)));
	pAction = m_oMenu.addAction("复制(&C)");
	connect(pAction, SIGNAL(triggered(bool)), this, SLOT(slot_menuCopy(bool)));
	pAction = m_oMenu.addAction("粘贴(&V)");
	connect(pAction, SIGNAL(triggered(bool)), this, SLOT(slot_menuPaste(bool)));
	pAction = m_oMenu.addAction("全选(&A)");
	connect(pAction, SIGNAL(triggered(bool)), this, SLOT(slot_menuSelectAll(bool)));
	pAction = m_oMenu.addAction("清空(&D)");
	connect(pAction, SIGNAL(triggered(bool)), this, SLOT(slot_menuClear(bool)));

	ui->textError->setVisible(false);
	ui->labelError->setVisible(false);
}

void CTcpEdgeUserEditDlg::InitReadUI()
{
	setWindowTitle("查看报文");
	ui->titleName->setText("查看报文");
	InitFormUI(this, ui->title);
	InitScintilla();
	m_pTextBox->setReadOnly(true);
	ui->rbDataCh->setVisible(false);
	ui->rbMngrCh->setVisible(false);
	ui->btnOK->setVisible(false);

	QAction* pAction = m_oMenu.addAction("复制(&C)");
	connect(pAction, SIGNAL(triggered(bool)), this, SLOT(slot_menuCopy(bool)));
	pAction = m_oMenu.addAction("全选(&A)");
	connect(pAction, SIGNAL(triggered(bool)), this, SLOT(slot_menuSelectAll(bool)));
}

void CTcpEdgeUserEditDlg::InitFunctionBtns(CExBaseList* pDataset)
{
	CDvmDatasetGroup* pBtnGroup = (CDvmDatasetGroup*)pDataset->FindByID(Cfg_TcpServerFunc);
	long nIndex = 0;
	POS pos = pBtnGroup->GetHeadPosition();
	while (pos)
	{
		CDvmDatasetGroup* pGroup = (CDvmDatasetGroup*)pBtnGroup->GetNext(pos);
		QToolButton* pButton = new QToolButton();
		ui->layoutToolbtns->insertWidget(nIndex, pButton);
		nIndex++;
		pButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
		pButton->setAutoRaise(true);
		pButton->setText(pGroup->m_strName);
		pButton->setObjectName(pGroup->m_strID);
		pButton->setPopupMode(QToolButton::InstantPopup);

		QMenu* pFuncMenu = new QMenu;
		POS pos = pGroup->GetHeadPosition();
		while (pos)
		{
			CDvmData* pData = (CDvmData*)pGroup->GetNext(pos);
			if(pData->GetCount())
			{
				QMenu* pChildMenu = new QMenu(pData->m_strName, pFuncMenu);
				POS posChild = pData->GetHeadPosition();
				while (posChild)
				{
					CDvmValue* pValue = (CDvmValue*)pData->GetNext(posChild);
					QAction* pChildAction = new QAction(pValue->m_strName, pChildMenu);
					pChildAction->setData(QVariant::fromValue<QString>(pValue->m_strID));
					connect(pChildAction, SIGNAL(triggered()), this, SLOT(slot_menuTriggered()));
					pChildMenu->addAction(pChildAction);
				}

				pFuncMenu->addMenu(pChildMenu);
			}
			else
			{
				if(pData->m_strID != PkgData_UserEdit)
				{
					QAction* pAction = new QAction(pData->m_strName, pFuncMenu);
					pAction->setData(QVariant::fromValue<QString>(pData->m_strID));
					connect(pAction, SIGNAL(triggered()), this, SLOT(slot_menuTriggered()));
					pFuncMenu->addAction(pAction);					
				}
			}
		}

		pButton->setMenu(pFuncMenu);
	}
}

void CTcpEdgeUserEditDlg::InitScintilla()
{
	QVBoxLayout* layout = (QVBoxLayout*)ui->layoutTextBox;
	m_pTextBox = new QsciScintilla(this);
	layout->addWidget(m_pTextBox);

	QsciLexerJSON* pLexer = new QsciLexerJSON;
	m_pTextBox->setLexer(pLexer);

	//缩进设置
	m_pTextBox->setIndentationsUseTabs(false);
	m_pTextBox->setIndentationWidth(4);
	m_pTextBox->setTabWidth(4);
	m_pTextBox->setAutoIndent(true);
	m_pTextBox->setCaretLineVisible(false);
	m_pTextBox->setIndentationGuides(true);

	//设置UTF8输入
	m_pTextBox->setUtf8(true);
	connect(m_pTextBox, SIGNAL(SCN_CHARADDED(int)), this, SLOT(slot_CharAdded(int)));

	//行号
	m_pTextBox->setMarginType(0, QsciScintilla::NumberMargin);
	m_pTextBox->setMarginLineNumbers(0, true);
	m_pTextBox->setMarginWidth(0, 48);
	m_pTextBox->setMarginsBackgroundColor(Qt::gray);
	m_pTextBox->setMarginsForegroundColor(Qt::white);
	m_pTextBox->setFoldMarginColors(Qt::gray,Qt::lightGray);

	//括号匹配
	m_pTextBox->setUnmatchedBraceBackgroundColor(Qt::red);
	m_pTextBox->setMatchedBraceBackgroundColor(Qt::green);
	m_pTextBox->setUnmatchedBraceForegroundColor(Qt::blue);
	m_pTextBox->setMatchedBraceForegroundColor(Qt::blue);
	m_pTextBox->setBraceMatching(QsciScintilla::SloppyBraceMatch);

	//设置编辑框状态
	m_pTextBox->setWrapMode(QsciScintilla::WrapWord); 
	m_pTextBox->setFolding(QsciScintilla::BoxedTreeFoldStyle);

	//菜单
	m_pTextBox->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(m_pTextBox, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(slot_showMenu(const QPoint&)));
}

CTcpEdgeUserEditDlg::~CTcpEdgeUserEditDlg()
{
	delete ui;
}

QString CTcpEdgeUserEditDlg::text()
{
	return m_pTextBox->text();
}

bool CTcpEdgeUserEditDlg::ch()
{
	return ui->rbMngrCh->isChecked();
}

void CTcpEdgeUserEditDlg::slot_CharAdded(int charadded)
{
	switch(charadded)
	{
	case '{': 
		m_pTextBox->insert("}");
		break;
	case '[': 
		m_pTextBox->insert("]");
		break;
	case '\"': 
		m_pTextBox->insert("\"");
		break;
	default:
		break;
	}
}

void CTcpEdgeUserEditDlg::slot_showMenu(const QPoint& pt)
{
	m_oMenu.move(cursor().pos());
	m_oMenu.show();
}

void CTcpEdgeUserEditDlg::slot_menuUndo(bool checked)
{
	m_pTextBox->undo();
}

void CTcpEdgeUserEditDlg::slot_menuRedo(bool checked)
{
	m_pTextBox->redo();
}

void CTcpEdgeUserEditDlg::slot_menuCopy(bool checked)
{
	m_pTextBox->copy();
}

void CTcpEdgeUserEditDlg::slot_menuPaste(bool checked)
{
	m_pTextBox->paste();
}

void CTcpEdgeUserEditDlg::slot_menuSelectAll(bool checked)
{
	m_pTextBox->selectAll();
}

void CTcpEdgeUserEditDlg::slot_menuClear(bool checked)
{
	m_pTextBox->clear();
}

void CTcpEdgeUserEditDlg::slot_menuTriggered()
{
	QAction* pToolBtn = (QAction*)sender();
	QString strName = pToolBtn->text();
	CString strFuncID = pToolBtn->data().value<QString>();

	CTcpEdgeTestDlg dlg;
	dlg.AttachDevice(m_pDevice);

	if(dlg.exec(strName, strFuncID) == QDialog::Accepted)
	{
		CDvmDataset* pDataset = dlg.GetDataset();

		CTcpEdgePrcdrBase* pPrcdr = CTcpEdgeProtocol::CreateUserProcedure(strFuncID);
		pPrcdr->m_strID = strFuncID;
		QString strJson = pPrcdr->GetUserString(pDataset);

		if(m_pTextBox->text().length())
		{
			CTcpEdgeInformationDlg dlg;
			if(dlg.exec(CTcpEdgeInformationDlg::INFO, "编辑框存在内容,是否覆盖?") == QDialog::Accepted)
			{
				m_pTextBox->setText(strJson);
			}
		}
		else
		{
			m_pTextBox->setText(strJson);
		}
	}
}