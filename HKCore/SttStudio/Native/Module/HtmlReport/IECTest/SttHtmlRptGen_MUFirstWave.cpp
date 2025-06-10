#include <QBuffer>
#include "SttHtmlRptGen_MUFirstWave.h"
#include "..\HtmlReport\SttXHtmlRptGenFactoryBase.h"
#include "..\..\SmartCap\61850Cap\CapDevice\CapDeviceBase.h"
#include "..\RecordTest\UI\MUTest\FirstCircleWave\SttMUTestFirstCwWidget.h"
#include "..\..\SmartCap\61850Cap\CapDevice\CapAnalysisConfig.h"
#include "..\..\SmartCap\XSmartCapMngr.h"

CSttHtmlRptGen_MUFirstWave::CSttHtmlRptGen_MUFirstWave()
{
}

CSttHtmlRptGen_MUFirstWave::~CSttHtmlRptGen_MUFirstWave()
{
}

void CSttHtmlRptGen_MUFirstWave::GenHtml()
{
	m_pHtmlBuffer->ZeroBuffer();

	GenRootDiv();
	GenRootDiv_H1();
	GenMUFirstWave();
	GenRootDiv_End();
}

void CSttHtmlRptGen_MUFirstWave::GenRootDiv_H1()
{
	m_pHtmlBuffer->AppendString("<h1>���ܲ�����</h1>");
	
}

void CSttHtmlRptGen_MUFirstWave::GenRootDiv()
{
	GenModule_RootDiv(g_theHtmlRptGenFactory->m_strMacroID.GetString());
}

void CSttHtmlRptGen_MUFirstWave::GenRootDiv_End()
{
	m_pHtmlBuffer->AppendString("</div>");
}

//����ͼ
//ͨ�����		ͨ������		���ֵ		��̬��Ӧʱ��
//1				��������A��		����ֵ		2.35��s
void CSttHtmlRptGen_MUFirstWave::GenMUFirstWave()
{
	if (g_theXSmartCapMngr == NULL)
	{
		return;
	}
	if (g_pMUTestFirstCwWidget == NULL)
	{
		return;
	}
	CCapDevice92 *pCapDevice92 = g_pMUTestFirstCwWidget->m_pCapDevice92;
	if (pCapDevice92 == NULL)
	{
		return;
	}
	POS pos = pCapDevice92->GetHeadPosition();
	CCapDeviceSmvCh *pCapDeviceSmvCh = NULL;
	long nChIndex = 0;
	while(pos)
	{
		pCapDeviceSmvCh = (CCapDeviceSmvCh *)pCapDevice92->GetNext(pos);
		if (pCapDeviceSmvCh->m_nChType != CAPDEVICE_CHTYPE_I && pCapDeviceSmvCh->m_nChType != CAPDEVICE_CHTYPE_U)
		{
			continue;
		}

		//���벨��ͼ
		QImage *pImage = g_pMUTestFirstCwWidget->m_pImage[nChIndex];
		GenPicture(pImage);
		//�����ͷ
		GenMUFirstWave_Table_th();
		//����������
		m_pHtmlBuffer->AppendString("<tr>");
		Gen_Table_td(nChIndex);
		Gen_Table_td(pCapDeviceSmvCh->m_strName.GetString());
		if (g_oCapAnalysisConfig.m_nShowPrimaryValue = 0)
		{
			CString strTemp = _T("����ֵ");
			Gen_Table_td(strTemp.GetString());
		}
		else
		{
			CString strTemp = _T("һ��ֵ");
			Gen_Table_td(strTemp.GetString());
		}
		Gen_Table_td(pCapDevice92->m_dFirstCW_TransientTime[nChIndex], 3);
		m_pHtmlBuffer->AppendString("<tr>");
	}
}

void CSttHtmlRptGen_MUFirstWave::GenMUFirstWave_Table_th()
{
	GenModule_Table_th("MUFirstWave");

	m_pHtmlBuffer->AppendString("<tr>");

	Gen_Table_th("ͨ�����");
	Gen_Table_th("ͨ������");
	Gen_Table_th("���ֵ");
	Gen_Table_th("��̬��Ӧʱ��");

	m_pHtmlBuffer->AppendString("</tr>");
}

void CSttHtmlRptGen_MUFirstWave::GenPicture(QImage *pImage)
{
	m_pHtmlBuffer->AppendString("</tr>");
	QByteArray byteArray;
	QBuffer buffer(&byteArray);
	buffer.open(QIODevice::WriteOnly);
	pImage->save(&buffer, "PNG");

	// �� QByteArray ת��Ϊ Base64 �����ַ���
	QString base64Image = QString::fromLatin1(byteArray.toBase64().data());

	// ���� HTML �ַ��������� Base64 ͼƬ
	QString html = "<img src='data:image/png;base64," + base64Image + "' alt='Your Image'>";

	// �����ɵ� HTML �ַ�����ӵ� m_pHtmlBuffer ��
	const char *htmlData = html.toUtf8().constData();
	m_pHtmlBuffer->AppendString(htmlData);
	m_pHtmlBuffer->AppendString("</tr>");
}

