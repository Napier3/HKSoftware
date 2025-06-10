//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttSysState_Gb.h  CSttSysState_Gb_Gb

#pragma once

#include "SttSysState.h"
#include "SttParas_Gb.h"

class CSttSysState_Gb : public CSttSysState
{
public:
	CSttSysState_Gb();
	CSttSysState_Gb(const CString &strRetType);
	virtual ~CSttSysState_Gb();

	static CXObjectRefBase* New()
	{
		return new CSttSysState_Gb();
	}

//���غ���
public:
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	//2023-9-9
	virtual CSttParas* NewSttParas();
};

/*
<sys-state name="" id="QueryItems" mater-host="" ret-type="REPLY" id-cmd="ats-cmd">
	<paras name="" id="">
		<data id="ExecStatus" data-type=" " value="1|2|3|4" unit=""/>
		<data name="" id="DeviceSN" data-type="" value="װ��SN"/>
		<data id="TestID" data-type="string" value="" unit=""/>
		<data name="" id="ItemPath" data-type="" value="Device$ManulTest"/>
		<items name="" id="" tkid="65535" select="1">
			������������
			<safety name="������ʾ" id="Safety" tkid="65535" select="0">
				<msg type="1"><![CDATA[
����ʾ�˹����в�������Ϣ��
]]></msg>
				<datas name="" id="">
					<data name="���վ����" id="Test1" data-type="" unit="" value="220KV����վ" format="" remark="" default="220KV����վ" reserved="1" time="0"/>
					<data name="��������" id="Test2" data-type="" unit="" value="1������" format="" remark="" default="1������" reserved="1" time="0"/>
					<data name="���ر��" id="Test3" data-type="" unit="" value="110" format="" remark="" default="110" reserved="1" time="0"/>
					<data name="data1" id="data1" data-type="combobox" unit="" value="eligible" format="Eligible" remark="" default="eligible" reserved="1" time="0" />
					<data name="data2" id="data2" data-type="combobox" unit="" value="right" format="Right" remark="" default="" reserved="1" time="0" />
				</datas>
			</safety>
������������
		</items>
		<data-types name="" id="">
			<data-type name="�ϸ�/���ϸ�" id="Eligible">
				<value name="�ϸ�" id="eligible" index="1"/>
				<value name="���ϸ�" id="inlegible" index="2"/>
			</data-type>
			<data-type name="��ȷ/����ȷ" id="Right">
				<value name="��ȷ" id="right" index="1"/>
				<value name="����ȷ" id="wrong" index="2"/>
			</data-type>
			������������
		</data-types>
	</paras>
</sys-state>
*/
