#pragma once

/*
<ats-cmd name="ConfigEngine" id="" testor="" >
    <paras name="" id="">
        <data id=" log-data-bind " value=" "/>����ʾ���ݰ󶨴���
        <data id=" log-pkg-data-infor " value=" "/>����ʾ����������Ϣ��
        <data id=" log-pkg " value=" "/>����ʾ���͡����ܱ��ġ�
        <data id=" log-protocol-debug-infor " value=" "/>����ʾ������Ϣ��
        <data id=" log-server-debug-infor " value=" "/>����ʾ������Ϣ��
        <data id=" no-change-when-same " value=" "/>��������ͬ��ִ���޸ġ�
    </paras>
</ats -cmd>
*/

/*
 * /Source/Protocol/Module/Engine/PpGlobalDefine.cpp
long g_bLogBindQueryErrorInfor = FALSE;
long g_bLogPackageInfor = FALSE;
long g_bLogEngineDebugInfor = FALSE;
*/

//���ӷ���˵��������Ϣ
extern long g_nSttLogServerDebugInfor;

//���ӷ�������е������
extern long g_nSttLogServerSpyAllCmd;

//2020-12-08  lijunqing
extern long g_nCloseTestWhenDisconnect;
