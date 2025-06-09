#include "stdafx.h"
#include "ChineseKeyboard.h"
#include <QLineEdit>
#include <QtGui>
#include <QString>
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../Module/OSInterface/QT/XMessageBox.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../SttTestCntrFrameBase.h"
#include "../../XLangResource_Native.h"
QMap<QString, QList<QPair<QString, QString> > > g_mapPinyinData;

ChineseKeyboard::ChineseKeyboard(QWidget *parent /* = NULL */) : QDialog(parent)
{
	setupUi(this);
	m_bCaps = false;
	m_bChinese = false;
	m_bFuhao = false;
	m_pParent = parent;
	InitUI();
	InitChineseList();
	InitLanguage();

	setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
}

ChineseKeyboard::~ChineseKeyboard()
{
	if(m_pSignalMapper)
	{
		 delete m_pSignalMapper;
		 m_pSignalMapper = NULL;
	}
}

void ChineseKeyboard::InitLanguage()
{
	xlang_SetLangStrToWidget_Txt(ui->btnClear,g_sLangTxt_Native_Clear,XLang_Ctrls_QToolButton);
}

void ChineseKeyboard::InitUI()
{
	int FontSize  = 20;
	this->setWindowFlags(Qt::Tool);

	CString strText;
	xlang_GetLangStrByFile(strText, "Native_Enter");
	btnReturn->setText(strText);
	xlang_GetLangStrByFile(strText, "Native_Esc");
	btnEsc->setText(strText);
	xlang_GetLangStrByFile(strText, "Native_Delete");
	btnBackSpace->setText(strText);
	xlang_GetLangStrByFile(strText, "Native_Space");
	btnSpace->setText(strText);
	xlang_GetLangStrByFile(strText, "Native_Caps");
	btnCaps->setText(strText);

	m_pSignalMapper = new QSignalMapper(this);
	changeTextCaps(false);
	m_pButtonsList = findChildren<QToolButton *>();
	for (int i = 0; i < m_pButtonsList.count(); i++)
	{
		connect(m_pButtonsList.at(i), SIGNAL(clicked()), m_pSignalMapper, SLOT(map()));
		m_pButtonsList.at(i)->setFont(QFont("宋体", FontSize, 2));
		m_pButtonsList.at(i)->setStyleSheet("QToolButton{background-color: #313131;border-style: flat;color:white;}"
			"QToolButton:pressed{background-color: #414141;border-style: flat;}");
		m_pSignalMapper->setMapping(m_pButtonsList.at(i), i);
	}
	connect(m_pSignalMapper, SIGNAL(mapped(int)), this, SLOT(on_btn_clicked(int)));
	btnCaps->setStyleSheet("QToolButton{background-color: #191615;border-style: flat;color:white;}"
		"QToolButton:pressed{background-color: #414141;border-style: flat;}");
	btnBackSpace->setStyleSheet("QToolButton{background-color: #191615;border-style: flat;color:white;}"
		"QToolButton:pressed{background-color: #414141;border-style: flat;}");
	btnReturn->setStyleSheet("QToolButton{background-color: #191615;border-style: flat;color:white;}"
		"QToolButton:pressed{background-color: #414141;border-style: flat;}");
	btnEsc->setStyleSheet("QToolButton{background-color: #191615;border-style: flat;color:white;}"
		"QToolButton:pressed{background-color: #414141;border-style: flat;}");
	btnSpace->setStyleSheet("QToolButton{background-color: #191615;border-style: flat;color:white;}"
		"QToolButton:pressed{background-color: #414141;border-style: flat;}");
	btnChinese->setStyleSheet("QToolButton{background-color: #577b7c;border-style: flat;color:white;}"
		"QToolButton:pressed{background-color: #414141;border-style: flat;}");
	btnFuhao->setStyleSheet("QToolButton{background-color: #577b7c;border-style: flat;color:white;}"
		"QToolButton:pressed{background-color: #414141;border-style: flat;}");
	btnClear->setStyleSheet("QToolButton{background-color: #e60000;border-style: flat;color:white;}"
		"QToolButton:pressed{background-color: #414141;border-style: flat;}");

	lineEdit->setFocus(Qt::MouseFocusReason);
	lineEdit->setFont(QFont("宋体", FontSize, 2));
	lineEdit->installEventFilter(this);
}

void ChineseKeyboard::InitChineseList()
{
	listChinese->setFocusPolicy(Qt::NoFocus);
	listChinese->setViewMode(QListView::ListMode);
	listChinese->setFlow(QListView::LeftToRight);
	listChinese->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	listChinese->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	listChinese->setHorizontalScrollMode(QListWidget::ScrollPerPixel);
	listChinese->setStyleSheet("                                                                           \
				  QListWidget { outline: none; border:1px solid #00000000; color: black; }    \
				  QListWidget::Item { width: 50px; height: 50px; }                            \
				  QListWidget::Item:hover { background: #4395ff; color: white; }              \
				  QListWidget::item:selected { background: #4395ff; color: black; }           \
				  QListWidget::item:selected:!active { background: #00000000; color: black; } \
				  ");

	connect(listChinese, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(onItemClicked(QListWidgetItem *)));
}

void ChineseKeyboard::keyPressEvent(QKeyEvent *event)
{
	switch(event->key())
	{
		//进行界面退出，重写Esc键，否则重写reject()方法
	case Qt::Key_Escape:
		{
			// this->close();
			on_btnEsc_clicked(true);
		}
		break;
	case Qt::Key_Return:
		{
			//this->close();
			on_btnReturn_clicked(true);
		}
		break;
	case Qt::Key_Home:
		{
			//this->close();
			//       homeActive(this);
		}
		break;
	default:
		QDialog::keyPressEvent(event);
	}
}

bool ChineseKeyboard::eventFilter(QObject *obj, QEvent *event)
{
	if(event->type() == QEvent::KeyPress)
	{
		QKeyEvent *pe = (QKeyEvent*)event;
		if (pe->key()==Qt::Key_Home)
		{
			//            homeActive(this);
			return true;
		}
	}
	return QDialog::eventFilter(obj,event);
}

void ChineseKeyboard::showToEdit(QRect rc)
{
	lineEdit->setText(m_strEditInfo);
	lineEdit->setFocus(Qt::MouseFocusReason);
	lineEdit->setCursorPosition(lineEdit->text().size());

	long nHeight = 210 + rc.height() - 600;
	setGeometry(rc.left(), rc.top() + nHeight, 1024, 350);
}

void ChineseKeyboard::on_btn_clicked(int btn)
{
	QString strKeyId;
	strKeyId = m_pButtonsList.at(btn)->accessibleName();
	bool isOk;
	int keyId = strKeyId.toInt(&isOk, 16);
	if (strKeyId.isEmpty() || !isOk)
	{
		CXMessageBox::information(0,0,"Key Not Found");
		return;
	}

	bool isTextKey = false;
	bool bIsNum = false;
	QString ch = m_pButtonsList.at(btn)->text().trimmed();
	if (ch=="&&")
		ch = "&";
	else if (keyId==Qt::Key_Space)
		ch = " ";
	else if (checkNotTextKey(keyId))
		ch = QString();
	else if (keyId >= 0x30 && keyId <= 0x39)
		bIsNum = true;
	else
		isTextKey = true;	    

	if(isTextKey)
	{
		QKeyEvent keyEventIns(QEvent::KeyPress, Qt::Key_Delete, Qt::NoModifier);
		QApplication::sendEvent(lineEdit, &keyEventIns);
		QApplication::sendEvent(m_pParent->focusWidget(), &keyEventIns);
	}

	if(keyId == 0x4D)
	{
		CString strText;
		xlang_GetLangStrByFile(strText, "Native_Delete");
		if (ch==strText)
		{
			//删除
			if(!m_strTempText.length())
			{
				QString strLineText = lineEdit->text().mid(0, lineEdit->text().length() - 1);
				lineEdit->setText(strLineText);
			}
			else
			{
				m_strTempText = m_strTempText.mid(0, m_strTempText.length() - 1);
				ParsePinyin("");
			}
			return;
		}
		else
		{
			//清空
			lineEdit->setText("");
			m_strTempText = "";
			listChinese->clear();
			return;
		}
	}

	if(m_bChinese)
	{
		if(!isTextKey || m_bCaps)
		{
			QKeyEvent keyEvent(QEvent::KeyPress, keyId, Qt::NoModifier, ch, false, 1);
			QApplication::sendEvent(lineEdit/*->focusWidget()*/, &keyEvent);
		}
		else
		{
			ParsePinyin(ch);
		}
	}
	else
	{
		QKeyEvent keyEvent(QEvent::KeyPress, keyId, Qt::NoModifier, ch, false, 1);
		QApplication::sendEvent(lineEdit/*->focusWidget()*/, &keyEvent);
	}
}

void ChineseKeyboard::ParsePinyin(const QString& strText)
{
	m_strTempText += strText;

	for (int i = 0; i < listChinese->count(); i++) {
		QListWidgetItem *item = listChinese->takeItem(i);
		delete item;
		item = NULL;
	}

	listChinese->clear();

	AddItem(m_strTempText);

	if (!g_mapPinyinData.contains(m_strTempText.left(1))) {
		return;
	}

	/* 通过获取首字母索引词库内容，用于加快匹配词(组)。 */
	const QList<QPair<QString, QString> > &tmp = g_mapPinyinData[m_strTempText.left(1)];
	for (int i = 0; i < tmp.count(); i++) {
		const QPair<QString, QString> &each = tmp.at(i);
		//模糊匹配
		if (each.first.left(m_strTempText.count()) != m_strTempText)
			continue;
		//精确匹配
		//if (each.first != m_strTempText)
		//	continue;

		/* 添加到候选栏, 并限制数量 */
		if (listChinese->count() <= 30) {
			AddItem(each.second);
		}
		else {
			break;
		}
	}
}

void ChineseKeyboard::on_btnCaps_toggled(bool checked)
{
	changeTextCaps(checked);
	m_bCaps = checked;
}

void ChineseKeyboard::on_btnFuhao_toggled(bool checked)
{
	m_bFuhao = checked;
	if (m_bFuhao)
	{
		btn0->setText(QChar(')'));
		btn1->setText(QChar('('));
		btn2->setText(QChar('['));
		btn3->setText(QChar(']'));
		btn4->setText(QChar('@'));
		btn5->setText(QChar('#'));
		btn6->setText(QChar('$'));
		btn7->setText(QChar('-'));
		btn8->setText(QChar('_'));
		btn9->setText(QChar('.'));
		btnFuhao->setText("123");
	}
	else
	{
		btn0->setText(QChar('0'));
		btn1->setText(QChar('1'));
		btn2->setText(QChar('2'));
		btn3->setText(QChar('3'));
		btn4->setText(QChar('4'));
		btn5->setText(QChar('5'));
		btn6->setText(QChar('6'));
		btn7->setText(QChar('7'));
		btn8->setText(QChar('8'));
		btn9->setText(QChar('9'));
		btnFuhao->setText("#+%");
	}
}

void ChineseKeyboard::changeTextCaps(bool isCaps)
{    
	if (isCaps)
	{
		btnQ->setText(QChar('Q'));
		btnW->setText(QChar('W'));
		btnE->setText(QChar('E'));
		btnR->setText(QChar('R'));
		btnT->setText(QChar('T'));
		btnY->setText(QChar('Y'));
		btnU->setText(QChar('U'));
		btnI->setText(QChar('I'));
		btnO->setText(QChar('O'));
		btnP->setText(QChar('P'));

		btnA->setText(QChar('A'));
		btnS->setText(QChar('S'));
		btnD->setText(QChar('D'));
		btnF->setText(QChar('F'));
		btnG->setText(QChar('G'));
		btnH->setText(QChar('H'));
		btnJ->setText(QChar('J'));
		btnK->setText(QChar('K'));
		btnL->setText(QChar('L'));

		btnZ->setText(QChar('Z'));
		btnX->setText(QChar('X'));
		btnC->setText(QChar('C'));
		btnV->setText(QChar('V'));
		btnB->setText(QChar('B'));
		btnN->setText(QChar('N'));
		btnM->setText(QChar('M'));        
	}
	else
	{
		btnQ->setText(QChar('q'));
		btnW->setText(QChar('w'));
		btnE->setText(QChar('e'));
		btnR->setText(QChar('r'));
		btnT->setText(QChar('t'));
		btnY->setText(QChar('y'));
		btnU->setText(QChar('u'));
		btnI->setText(QChar('i'));
		btnO->setText(QChar('o'));
		btnP->setText(QChar('p'));

		btnA->setText(QChar('a'));
		btnS->setText(QChar('s'));
		btnD->setText(QChar('d'));
		btnF->setText(QChar('f'));
		btnG->setText(QChar('g'));
		btnH->setText(QChar('h'));
		btnJ->setText(QChar('j'));
		btnK->setText(QChar('k'));
		btnL->setText(QChar('l'));

		btnZ->setText(QChar('z'));
		btnX->setText(QChar('x'));
		btnC->setText(QChar('c'));
		btnV->setText(QChar('v'));
		btnB->setText(QChar('b'));
		btnN->setText(QChar('n'));
		btnM->setText(QChar('m'));
	}
}

void ChineseKeyboard::AddItem(const QString &strText)
{
	QListWidgetItem *item = new QListWidgetItem(strText, listChinese);
	QFont font;
	font.setPointSize(18);
	font.setBold(true);
	font.setWeight(50);
	item->setFont(font);

	item->setTextAlignment(Qt::AlignCenter);
	item->setSizeHint(QSize(150, 50));
	listChinese->addItem(item);
}

bool ChineseKeyboard::checkNotTextKey(int keyId)
{
	if (keyId==Qt::Key_Shift
		|| keyId==Qt::Key_Control
		|| keyId==Qt::Key_Tab
		|| keyId==Qt::Key_Escape
		|| keyId==Qt::Key_Return
		|| keyId==Qt::Key_Insert
		|| keyId==Qt::Key_NumLock
		|| keyId==Qt::Key_F1
		|| keyId==Qt::Key_F2
		|| keyId==Qt::Key_F3
		|| keyId==Qt::Key_F4
		|| keyId==Qt::Key_F5
		|| keyId==Qt::Key_F6
		|| keyId==Qt::Key_F7
		|| keyId==Qt::Key_F8
		|| keyId==Qt::Key_F9
		|| keyId==Qt::Key_F10
		|| keyId==Qt::Key_F11
		|| keyId==Qt::Key_F12
		|| keyId==Qt::Key_Print
		|| keyId==Qt::Key_Pause
		|| keyId==Qt::Key_ScrollLock
		|| keyId==Qt::Key_Enter
		|| keyId==Qt::Key_Home
		|| keyId==Qt::Key_End
		|| keyId==Qt::Key_CapsLock
		|| keyId==Qt::Key_Insert
		|| keyId==Qt::Key_Delete
		|| keyId==Qt::Key_PageUp
		|| keyId==Qt::Key_PageDown
		|| keyId==Qt::Key_Down
		|| keyId==Qt::Key_Up
		|| keyId==Qt::Key_Left
		|| keyId==Qt::Key_Right
		|| keyId==Qt::Key_Alt
		|| keyId==Qt::Key_NumberSign)
	{
		return true;
	}
	else
		return false;
}

void ChineseKeyboard::onItemClicked(QListWidgetItem *item)
{
	QString strItemText = item->text();
	strItemText = lineEdit->text() + strItemText;
	lineEdit->setText(strItemText);
	m_strTempText = "";
	listChinese->clear();
}

void ChineseKeyboard::on_btnReturn_clicked( bool checked )
{
	m_strEditInfo = lineEdit->text();
	this->accept();
}

void ChineseKeyboard::on_btnEsc_clicked( bool checked )
{
	this->close();
}

void ChineseKeyboard::on_btnChinese_toggled(bool checked)
{
	CString strText;
	if(m_bChinese)
	{
		m_bChinese = false;
		//xlang_GetLangStrByFile(strText, "Native_Eng");
		//btnChinese->setText(strText);
		btnChinese->setText(/*QObject::tr("英/中")*/g_sLangTxt_Native_Eng);
		m_strTempText = "";
		listChinese->clear();
	}
	else
	{
		m_bChinese = true;
		//xlang_GetLangStrByFile(strText, "Native_Chs");
		//btnChinese->setText(strText);
		btnChinese->setText(/*QObject::tr("中/英")*/g_sLangTxt_Native_Chs);
	}
}

void Global_InitPinyinLib()
{
	//#ifdef _PSX_QT_LINUX_
	QString strFile = _P_GetConfigPath();
	strFile += "pinyin.txt";
	QFile oFile(strFile);
	if (!oFile.open(QIODevice::ReadOnly)) 
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,/*_T("没有找到中文拼音资源文件!")*/g_sLangTxt_Native_PYResnotFound.GetString());
		return;
	}

	QTextStream in(&oFile);
	in.setCodec("UTF-16"); // change the file codec to UTF-16.

	QStringList lines = in.readAll().split("\n");
	QStringListIterator itor(lines);
	while (itor.hasNext()) 
	{
		QString strText = itor.next();
		long nSpace = strText.indexOf(" ");
		if(nSpace != -1) 
		{
			QString strChinese = strText.mid(0, nSpace); // 汉字
			QString strPinyin = strText.mid(nSpace + 1); // 拼音(可能是词组)

			QStringList strList = strPinyin.split(" ");
			QString strText;
			for (int i = 0; i < strList.count(); i++) 
			{
				/* 获得拼音词组的首字母(用于缩写匹配) */
				strText += strList.at(i).left(1);
			}

			QList<QPair<QString, QString> > &list = g_mapPinyinData[strPinyin.left(1)];
			if (strList.count() > 1) 
			{
				/* 将'拼音(缩写)'和'词组'写入匹配容器 */
				list.append(qMakePair(strText, strChinese));
			}
			/* 将'拼音(全拼)'和'词组'写入匹配容器 */
			list.append(qMakePair(strPinyin.remove(" "), strChinese));
		}
	}

	oFile.close();
	//#endif
}