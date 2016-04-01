'------------------------------------------------ 
' \file format_source.vbs
' \brief 格式化代码
'
' 使用Astyle.exe格式化代码
'
' \author wangyang
' \date 2015/04/10
' \version 1.0
'------------------------------------------------ 

Const COM_FSO           = "Scripting.FileSystemObject"
Const COM_SHELL         = "WScript.Shell"

Dim config
Set config = CreateObject("Scripting.Dictionary")
config("AStyle")		= ".\src_tools\AStyle.exe --style=linux --s4 --p --H --U --f --v --w --c --xe --xL --xW"
'------------------------------------------------
' FSO
Const ForReading = 1
Const ForWriting = 2
Const ForAppending = 8
'------------------------------------------------
' CScriptRun
Sub CScriptRun 
    Dim Args
    Dim Arg
    If LCase(Right(WScript.FullName,11)) = "wscript.exe" Then
        Args = Array("cmd.exe /k CScript.exe", """" & WScript.ScriptFullName & """" )
            For Each Arg In WScript.Arguments
            ReDim Preserve Args(UBound(Args)+1)
            Args(UBound(Args)) = """" & Arg & """"
        Next
        WScript.Quit CreateObject("WScript.Shell").Run(Join(Args), 1, True)
    End If
End Sub

'------------------------------------------------
' 打印字符串
Sub Echo(message)
    WScript.Echo message
End Sub


'------------------------------------------------
' 路径末尾添加\
Function DisposePath(sPath)
    On Error Resume Next
    
    If Right(sPath, 1) = "\" Then
        DisposePath = sPath
    Else
        DisposePath = sPath & "\"
    End If
    
    DisposePath = Trim(DisposePath)
End Function 

'------------------------------------------------
' 获取文件路径
Function GetFilePath(filename)
    Dim FSO
    Set FSO = CreateObject(COM_FSO)
    GetFilePath = DisposePath(FSO.GetParentFolderName(filename))
End Function 


'------------------------------------------------
' 获取文件绝对路径
Function GetAbsolutePathName(filename)
    Dim FSO, file
    Set FSO = CreateObject(COM_FSO)
    Set file = FSO.GetFile(filename)
    GetAbsolutePathName = FSO.GetAbsolutePathName(file)
End Function

'------------------------------------------------
' 获取文件名
Function GetFileName(filename)
    Dim FSO, file
    Set FSO = CreateObject(COM_FSO)
    Set file = FSO.GetFile(filename)
    GetFileName = FSO.GetFileName(file)
End Function

'------------------------------------------------
' 获取基本文件名
Function GetBaseName(filename)
    Dim FSO, file
    Set FSO = CreateObject(COM_FSO)
    Set file = FSO.GetFile(filename)
    GetBaseName = FSO.GetBaseName(file)
End Function


Function ExecAStyle(filename)
    Dim objShell, objExec, astyle, arrStr
    Set objShell = CreateObject(COM_SHELL)
    astyle = config("AStyle") 
    Set objExec = objShell.Exec(astyle & " """ & filename & """")
    ExecPHP = objExec.StdOut.ReadAll
End Function


Sub EachFiles(dir, pattern, method)
    Dim FSO, re
    Set FSO = CreateObject(COM_FSO)
    Set root = FSO.GetFolder(dir)
    Set re = new RegExp
    re.Pattern    = pattern
    re.IgnoreCase = True
    
    Call EachSubFolder(root, re, method)
    
    Set FSO = Nothing
    Set re = Nothing
End Sub

Sub EachSubFolder(root, re, method)
    Dim subfolder, file, script
    
    For Each file In root.Files
        If re.Test(file.Name) Then
            Call method(file.Path)            
        End If
    Next
    
    For Each subfolder In root.SubFolders
        Call EachSubFolder(subfolder, re, method)    
    Next
End Sub

Function format_source(filename)
    Echo filename
    ExecAStyle filename
End Function

	


CScriptRun


Call Main

Sub Main()
    Set callback_function = GetRef("format_source")
    Call EachFiles(".\3rdparty\DuiLib", "\.(?:cpp|cxx|h|hpp)$", callback_function)
End Sub
	



