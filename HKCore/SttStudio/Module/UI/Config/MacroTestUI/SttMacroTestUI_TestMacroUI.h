//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttMacroTestUI_TestMacroUI.h  CSttMacroTestUI_TestMacroUI

#pragma once

#include "SttTestCtrrlMacroTestUIMngrGlobal.h"
#include "../../../../../Module/DataMngr/DataGroup.h"

class CSttMacroTestUI_TestMacroUI : public CExBaseObject
{
public:
	CSttMacroTestUI_TestMacroUI();
	virtual ~CSttMacroTestUI_TestMacroUI();


	//����жϵ�ǰҳ����ԭ��̬������ҳ����m_strGenFile��m_strUI_File��Ϊ��ʱ������ԭ��̬��
	CString  m_strGenFile;     //������Ŀ�������ɵĹ����ļ���·��ΪDB/atsgen
	CString  m_strUI_File;     //�����ļ�����Ӧһ��HTML�ļ���·��ΪDB/ui
	CString  m_strUI_ParaFile; //��������ļ�����Ӧһ��CDataGroup��·��ΪDB/atsgen
	CString  m_strReportFile;  //�����ļ�����Ӧһ��HTML�ļ���·��ΪDB/ui
	CString  m_strHdRsFile;    //Ӳ����Դ�ļ�����Ӧһ��Ӳ����Դ���ã�·��ΪDB/atsgen
	CString  m_strCharlibFile; //�������߿��ļ�����Ӧһ���������߿⣬·��ΪConfig��Ŀ¼
	CString  m_strGirdFile;//���ʰ������������ļ� grid-file
	CString  m_strUI_ID;//�������ID
	//shaolei 2023-6-20
	CString  m_strrpt_Data_CfgFile;   //����xml���漰word��������������ļ����������������ļ���
	//shaolei 2023-6-21
	long m_nDefaultRepeatTimes;  //���õ�Ĭ�ϵ��ظ�����
//���غ���
public:
	virtual UINT GetClassID() {    return MACROTESTUIMNGRCLASSID_CSTTMACROTESTUI_TESTMACROUI;   }
	virtual BSTR GetXmlElementKey()  {      return CSttTestCtrrlMacroTestUIMngrXmlRWKeys::CSttMacroTestUI_TestMacroUIKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);

public:
	//��TestMacroUIת��ΪDataGroup���� sf 20220114
	CDataGroup *GetTestMacroUIDataGroup();
	void GetTestMacroUIDataGroup(CDataGroup *pDataParas);
//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
	//zhouhj 2023.11.9 �ϲ���Ԫ�Զ����Ը�Ϊ����ģ�������ļ����ɷ�ʽ
	//��ʱ�Ƿ����ģ�������ļ�������Ϊԭ��������о�,�������m_strUI_File��Ϊ��ҳ����,����Ϊԭ������
	BOOL IsUIOriginal()		{	return ( /*m_strGenFile.IsEmpty() &&*/ m_strUI_File.IsEmpty() );	}
	BOOL IsUIWeb()		{	return ( /*!m_strGenFile.IsEmpty() &&*/ !m_strUI_File.IsEmpty() );	}
	BOOL HasCharLib()	{	return m_strCharlibFile.GetLength() > 0;	}  //2022-6-30  lijunqing
};

