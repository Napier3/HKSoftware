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
'2014-4-2 自编by cc  用本来的Nakatsu算法编写

Function GetLCSseq_Nakatsu(ByVal Str1 As String, ByVal Str2 As String) As String
    Dim LM() As Integer
    Dim i As Integer, j As Integer, k As Integer, DL As Integer, jTmp As Integer
    Dim N As Integer, M As Integer
    Dim iTmp As Integer, posB As Integer, kTmp As Integer
    Dim strRet As String
    Const ConstVal = 9999
    
    N = Len(Str1)
    M = Len(Str2)
    If N > M Then       'str1取长度小的字符串，节约时间与空间，否则先交换
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
  
    For DL = 0 To N - 1           'diagonal line 对角线
        For k = 1 To N - DL         '对角线逐渐向右边移动
           ' If k = 5 Then Stop
            rst = ConstVal
            i = k + DL               'J 满足{ai=bj And j＞L(k-1,i-1)},且J>K(因左三角阵不可能,全为无效值
            jTmp = k
            If jTmp <= LM(k - 1, i - 1) + 1 Then jTmp = LM(k - 1, i - 1) + 1
            For j = jTmp To M           '求最小J 值
                If Mid(Str1, i, 1) = Mid(Str2, j, 1) Then       '满足{ai=bj}
                    rst = j
                    Exit For   '已找到最小J，后面均比其大
                End If
            Next j
            LM(k, i) = IIf(rst < LM(k, i - 1), rst, LM(k, i - 1))       '公式（3）取最小值（J，L(k,i-1)）
            If LM(k, i) = ConstVal Then Exit For       '对角线右下角J已经不存在,无须再继续
        Next k
        If LM(N - DL, i) <> ConstVal Then Exit For   ' 对角线已满了（均为有用值）,最大子序列已找到，后面对角非最大
    Next DL
    kTmp = N - DL
RETsrt:
    If 1 = 1 Then
        strRet = "": For it = 1 To N:  For j = 1 To N
                 strRet = strRet + IIf(LM(it, j) = ConstVal, " - ", Format(LM(it, j), " 00"))
        Next j: strRet = strRet + Format(it, "    0 ") + vbCrLf: Next it
        Debug.Print strRet
    End If
    
    iTmp = kTmp + DL                        '逆序回溯,找加其中一个子序列,可能不是唯一的
    posB = ConstVal
    strRet = ""
    For k = kTmp To 1 Step -1
        For i = k To iTmp
            If LM(k, i) <> ConstVal And LM(k, i) <= posB Then      '取k行,第一个有效值，同时应比k+1行的值要小
                posB = LM(k, i)                      '此前的k+1行的值, 字符串B中的位置
                strRet = Mid(Str2, posB, 1) + strRet
                Exit For
            End If
        Next i
        iTmp = i
    Next k
    GetLCSseq_Nakatsu = strRet
    '    StrVar2 = "21232 52331 1324"
End Function

