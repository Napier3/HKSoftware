#include "QTemplateWidget.h"
#include <QSplitter>
#include <QVBoxLayout>
#include <QTextCodec>

QTemplateWidget::QTemplateWidget(void)
{
/*统一用main的编码
	QTextCodec *codec = QTextCodec::codecForName("utf-8");    //获取系统编码
	QTextCodec::setCodecForCStrings(codec);
*/
	m_pParaTab = NULL;
	m_pSyncParaSet = NULL;
}

QTemplateWidget::~QTemplateWidget(void)
{
}

