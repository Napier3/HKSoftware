Attribute VB_Name = "Module1"

Sub main()
    Dim StrVar1 As String, StrVar2 As String
    Dim j As Integer
    
    j = 3
  If j = 1 Then
    StrVar1 = "481234781"   ' "ggatcga"
    StrVar2 = "4411327431"  ' "gaattcagtta"
  ElseIf j = 2 Then
    StrVar1 = "706212771311"
    StrVar2 = "46725370307"
  ElseIf j = 3 Then
    StrVar1 = "312123223445"
    StrVar2 = "21232523311324"
  Else
    StrVar1 = "64242"
    StrVar2 = "70404"
  End If

'    ChangCut2str StrVar1, StrVar2
    strRst = GetLCSseq_Nakatsu(StrVar1, StrVar2)

    Debug.Print "s1:" + StrVar1
    Debug.Print "s2:" + StrVar2
    Debug.Print ("LCS Nakatsu:") + strRst
    
   ' strRst1 = GetLCSseq_DP(StrVar1, StrVar2)
    Debug.Print ("LCS DP:") + strRst1

End Sub
'2014-4-2 �Ա�by cc  �ñ�����Nakatsu�㷨��д

Function GetLCSseq_Nakatsu(ByVal Str1 As String, ByVal Str2 As String) As String
    Dim LM() As Integer
    Dim i As Integer, j As Integer, k As Integer, DL As Integer, jTmp As Integer
    Dim N As Integer, M As Integer
    Dim iTmp As Integer, posB As Integer, kTmp As Integer
    Dim strRet As String
    Const ConstVal = 9999
    
    N = Len(Str1)
    M = Len(Str2)
    If N > M Then       'str1ȡ����С���ַ�������Լʱ����ռ䣬�����Ƚ���
        strRet = Str1
        Str1 = Str2
        Str2 = strRet
        jTmp = N
        N = M
        M = jTmp
    End If
    ReDim LM(N, N)
    For k = 0 To N: For i = 0 To N
        LM(k, i) = ConstVal
            Next i
        LM(0, k) = 0
    Next k
  
    For DL = 0 To N - 1           'diagonal line �Խ���
        For k = 1 To N - DL         '�Խ��������ұ��ƶ�
           ' If k = 5 Then Stop
            rst = ConstVal
            i = k + DL               'J ����{ai=bj And j��L(k-1,i-1)},��J>K(���������󲻿���,ȫΪ��Чֵ
            jTmp = k
            If jTmp <= LM(k - 1, i - 1) + 1 Then jTmp = LM(k - 1, i - 1) + 1
            For j = jTmp To M           '����СJ ֵ
                If Mid(Str1, i, 1) = Mid(Str2, j, 1) Then       '����{ai=bj}
                    rst = j
                    Exit For   '���ҵ���СJ������������
                End If
            Next j
            LM(k, i) = IIf(rst < LM(k, i - 1), rst, LM(k, i - 1))       '��ʽ��3��ȡ��Сֵ��J��L(k,i-1)��
            If LM(k, i) = ConstVal Then Exit For       '�Խ������½�J�Ѿ�������,�����ټ���
        Next k
        If LM(N - DL, i) <> ConstVal Then Exit For   ' �Խ��������ˣ���Ϊ����ֵ��,������������ҵ�������ԽǷ����
    Next DL
    kTmp = N - DL
RETsrt:
    If 1 = 1 Then
        strRet = "": For it = 1 To N:  For j = 1 To N
                 strRet = strRet + IIf(LM(it, j) = ConstVal, " - ", Format(LM(it, j), " 00"))
        Next j: strRet = strRet + Format(it, "    0 ") + vbCrLf: Next it
        Debug.Print strRet
    End If
    
    iTmp = kTmp + DL                        '�������,�Ҽ�����һ��������,���ܲ���Ψһ��
    posB = ConstVal
    strRet = ""
    For k = kTmp To 1 Step -1
        For i = k To iTmp
            If LM(k, i) <> ConstVal And LM(k, i) <= posB Then      'ȡk��,��һ����Чֵ��ͬʱӦ��k+1�е�ֵҪС
                posB = LM(k, i)                      '��ǰ��k+1�е�ֵ, �ַ���B�е�λ��
                strRet = Mid(Str2, posB, 1) + strRet
                Exit For
            End If
        Next i
        iTmp = i
    Next k
    GetLCSseq_Nakatsu = strRet
    '    StrVar2 = "21232 52331 1324"
End Function

