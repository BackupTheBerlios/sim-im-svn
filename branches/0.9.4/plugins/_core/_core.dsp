# Microsoft Developer Studio Project File - Name="_core" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=_core - Win32 Debug
!MESSAGE Dies ist kein g�ltiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und f�hren Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "_core.mak".
!MESSAGE 
!MESSAGE Sie k�nnen beim Ausf�hren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "_core.mak" CFG="_core - Win32 Debug"
!MESSAGE 
!MESSAGE F�r die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "_core - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "_core - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\Release"
# PROP Intermediate_Dir "..\..\Release_Wrk"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_core_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O1 /I "$(QTDIR)\include" /I "..\..\sim" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "QT_DLL" /D "UNICODE" /D "QT_THREAD_SUPPORT" /D VERSION=\"0.9.4\" /D PACKAGE=\"SIM\" /D USE_QT=1 /FR"Debug/" /Fo"Debug/" /Fd"Debug/" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x417 /i "../.." /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 ..\..\Release\sim.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib winmm.lib $(QTDIR)\lib\$(QTLIB) /nologo /dll /pdb:none /machine:I386 /out:"../../Release/plugins/_core.dll"

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\Debug"
# PROP Intermediate_Dir "..\..\Debug_Wrk"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_core_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(QTDIR)\include" /I "..\..\sim" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "QT_DLL" /D "UNICODE" /D "QT_THREAD_SUPPORT" /D VERSION=\"0.9.4\" /D PACKAGE=\"SIM\" /D USE_QT=1 /D "DEBUG" /FR /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x417 /i "../.." /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\..\Debug\sim.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib winmm.lib $(QTDIR)\lib\$(QTLIB) /nologo /dll /debug /machine:I386 /out:"../../Debug/plugins/_core.dll" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "_core - Win32 Release"
# Name "_core - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\arcfg.cpp
# End Source File
# Begin Source File

SOURCE=.\arcfgbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\autoreply.cpp
# End Source File
# Begin Source File

SOURCE=.\autoreplybase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\cfgdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\cfgdlgbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\cmenu.cpp
# End Source File
# Begin Source File

SOURCE=.\commands.cpp
# End Source File
# Begin Source File

SOURCE=.\connectionsettings.cpp
# End Source File
# Begin Source File

SOURCE=.\connectionsettingsbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\connectwnd.cpp
# End Source File
# Begin Source File

SOURCE=.\connectwndbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\container.cpp
# End Source File
# Begin Source File

SOURCE=.\core.cpp
# End Source File
# Begin Source File

SOURCE=.\declinedlg.cpp
# End Source File
# Begin Source File

SOURCE=.\declinedlgbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\editmail.cpp
# End Source File
# Begin Source File

SOURCE=.\editmailbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\editphone.cpp
# End Source File
# Begin Source File

SOURCE=.\editphonebase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\filecfg.cpp
# End Source File
# Begin Source File

SOURCE=.\filecfgbase.cpp
# End Source File
# Begin Source File

SOURCE=.\filetransfer.cpp
# End Source File
# Begin Source File

SOURCE=.\filetransferbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\history.cpp
# End Source File
# Begin Source File

SOURCE=.\historycfg.cpp
# End Source File
# Begin Source File

SOURCE=.\historycfgbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\historywnd.cpp
# End Source File
# Begin Source File

SOURCE=.\interfacecfg.cpp
# End Source File
# Begin Source File

SOURCE=.\interfacecfgbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\kpopup.cpp
# End Source File
# Begin Source File

SOURCE=.\logindlg.cpp
# End Source File
# Begin Source File

SOURCE=.\logindlgbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\maininfo.cpp
# End Source File
# Begin Source File

SOURCE=.\maininfobase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\mainwin.cpp
# End Source File
# Begin Source File

SOURCE=.\manager.cpp
# End Source File
# Begin Source File

SOURCE=.\managerbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_arcfg.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_arcfgbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_autoreply.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_autoreplybase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_cfgdlg.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_cfgdlgbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_cmenu.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_commands.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_connectionsettings.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_connectionsettingsbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_connectwnd.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_connectwndbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_container.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_core.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_declinedlg.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_declinedlgbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_editmail.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_editmailbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_editphone.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_editphonebase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_filecfg.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_filecfgbase.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_filetransfer.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_filetransferbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_historycfg.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_historycfgbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_historywnd.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_interfacecfg.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_interfacecfgbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_kpopup.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_logindlg.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_logindlgbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_maininfo.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_maininfobase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_mainwin.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_manager.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_managerbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_msgauth.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_msgcfg.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_msgcfgbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_msgcontacts.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_msgedit.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_msgfile.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_msggen.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_msgrecv.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_msgsms.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_msgurl.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_msgview.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_newprotocol.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_newprotocolbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_nonim.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_nonimbase.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_pagerbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_pagerdetails.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_phonebase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_phonedetails.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_plugincfg.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_plugincfgbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_prefcfg.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_prefcfgbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_search.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_searchall.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_searchallbase.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_searchbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_smscfg.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_smscfgbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_status.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_statuswnd.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_tmpl.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_toolsetup.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_toolsetupbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_usercfg.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_userhistorycfg.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_userhistorycfgbase.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_userlist.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_userview.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_userviewcfg.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_userviewcfgbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\moc_userwnd.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\msgauth.cpp
# End Source File
# Begin Source File

SOURCE=.\msgcfg.cpp
# End Source File
# Begin Source File

SOURCE=.\msgcfgbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\msgcontacts.cpp
# End Source File
# Begin Source File

SOURCE=.\msgedit.cpp
# End Source File
# Begin Source File

SOURCE=.\msgfile.cpp
# End Source File
# Begin Source File

SOURCE=.\msggen.cpp
# End Source File
# Begin Source File

SOURCE=.\msgrecv.cpp
# End Source File
# Begin Source File

SOURCE=.\msgsms.cpp
# End Source File
# Begin Source File

SOURCE=.\msgurl.cpp
# End Source File
# Begin Source File

SOURCE=.\msgview.cpp
# End Source File
# Begin Source File

SOURCE=.\newprotocol.cpp
# End Source File
# Begin Source File

SOURCE=.\newprotocolbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\nonim.cpp
# End Source File
# Begin Source File

SOURCE=.\nonimbase.cpp
# End Source File
# Begin Source File

SOURCE=.\pagerbase.cpp
# End Source File
# Begin Source File

SOURCE=.\pagerdetails.cpp
# End Source File
# Begin Source File

SOURCE=.\phonebase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\phonedetails.cpp
# End Source File
# Begin Source File

SOURCE=.\plugincfg.cpp
# End Source File
# Begin Source File

SOURCE=.\plugincfgbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\prefcfg.cpp
# End Source File
# Begin Source File

SOURCE=.\prefcfgbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\search.cpp
# End Source File
# Begin Source File

SOURCE=.\searchall.cpp
# End Source File
# Begin Source File

SOURCE=.\searchallbase.cpp
# End Source File
# Begin Source File

SOURCE=.\searchbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\smscfg.cpp
# End Source File
# Begin Source File

SOURCE=.\smscfgbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\status.cpp
# End Source File
# Begin Source File

SOURCE=.\statuswnd.cpp
# End Source File
# Begin Source File

SOURCE=.\tmpl.cpp
# End Source File
# Begin Source File

SOURCE=.\toolsetup.cpp
# End Source File
# Begin Source File

SOURCE=.\toolsetupbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\usercfg.cpp
# End Source File
# Begin Source File

SOURCE=.\userhistorycfg.cpp
# End Source File
# Begin Source File

SOURCE=.\userhistorycfgbase.cpp
# End Source File
# Begin Source File

SOURCE=.\userlist.cpp
# End Source File
# Begin Source File

SOURCE=.\userview.cpp
# End Source File
# Begin Source File

SOURCE=.\userviewcfg.cpp
# End Source File
# Begin Source File

SOURCE=.\userviewcfgbase.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=.\userwnd.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\arcfg.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\arcfg.h
InputName=arcfg

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\arcfg.h
InputName=arcfg

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\arcfgbase.h
# End Source File
# Begin Source File

SOURCE=.\autoreply.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\autoreply.h
InputName=autoreply

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\autoreply.h
InputName=autoreply

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\autoreplybase.h
# End Source File
# Begin Source File

SOURCE=.\cfgdlg.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\cfgdlg.h
InputName=cfgdlg

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\cfgdlg.h
InputName=cfgdlg

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\cfgdlgbase.h
# End Source File
# Begin Source File

SOURCE=.\cmenu.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\cmenu.h
InputName=cmenu

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\cmenu.h
InputName=cmenu

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\commands.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\commands.h
InputName=commands

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\commands.h
InputName=commands

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\connectionsettings.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\connectionsettings.h
InputName=connectionsettings

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\connectionsettings.h
InputName=connectionsettings

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\connectionsettingsbase.h
# End Source File
# Begin Source File

SOURCE=.\connectwnd.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\connectwnd.h
InputName=connectwnd

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\connectwnd.h
InputName=connectwnd

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\connectwndbase.h
# End Source File
# Begin Source File

SOURCE=.\container.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\container.h
InputName=container

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\container.h
InputName=container

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\core.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\core.h
InputName=core

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\core.h
InputName=core

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\declinedlg.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\declinedlg.h
InputName=declinedlg

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\declinedlg.h
InputName=declinedlg

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\declinedlgbase.h
# End Source File
# Begin Source File

SOURCE=.\editmail.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\editmail.h
InputName=editmail

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\editmail.h
InputName=editmail

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\editmailbase.h
# End Source File
# Begin Source File

SOURCE=.\editphone.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\editphone.h
InputName=editphone

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\editphone.h
InputName=editphone

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\editphonebase.h
# End Source File
# Begin Source File

SOURCE=.\filecfg.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\filecfg.h
InputName=filecfg

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\filecfg.h
InputName=filecfg

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\filecfgbase.h
# End Source File
# Begin Source File

SOURCE=.\filetransfer.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\filetransfer.h
InputName=filetransfer

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\filetransfer.h
InputName=filetransfer

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\filetransferbase.h
# End Source File
# Begin Source File

SOURCE=.\history.h
# End Source File
# Begin Source File

SOURCE=.\historycfg.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\historycfg.h
InputName=historycfg

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\historycfg.h
InputName=historycfg

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\historycfgbase.h
# End Source File
# Begin Source File

SOURCE=.\historywnd.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\historywnd.h
InputName=historywnd

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\historywnd.h
InputName=historywnd

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\interfacecfg.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\interfacecfg.h
InputName=interfacecfg

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\interfacecfg.h
InputName=interfacecfg

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\interfacecfgbase.h
# End Source File
# Begin Source File

SOURCE=.\kpopup.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\kpopup.h
InputName=kpopup

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\kpopup.h
InputName=kpopup

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\logindlg.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\logindlg.h
InputName=logindlg

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\logindlg.h
InputName=logindlg

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\logindlgbase.h
# End Source File
# Begin Source File

SOURCE=.\maininfo.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\maininfo.h
InputName=maininfo

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\maininfo.h
InputName=maininfo

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\maininfobase.h
# End Source File
# Begin Source File

SOURCE=.\mainwin.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\mainwin.h
InputName=mainwin

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\mainwin.h
InputName=mainwin

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\manager.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\manager.h
InputName=manager

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\manager.h
InputName=manager

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\managerbase.h
# End Source File
# Begin Source File

SOURCE=.\msgauth.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\msgauth.h
InputName=msgauth

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\msgauth.h
InputName=msgauth

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\msgcfg.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\msgcfg.h
InputName=msgcfg

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\msgcfg.h
InputName=msgcfg

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\msgcfgbase.h
# End Source File
# Begin Source File

SOURCE=.\msgcontacts.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\msgcontacts.h
InputName=msgcontacts

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\msgcontacts.h
InputName=msgcontacts

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\msgedit.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\msgedit.h
InputName=msgedit

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\msgedit.h
InputName=msgedit

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\msgfile.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\msgfile.h
InputName=msgfile

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\msgfile.h
InputName=msgfile

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\msggen.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\msggen.h
InputName=msggen

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\msggen.h
InputName=msggen

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\msgrecv.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\msgrecv.h
InputName=msgrecv

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\msgrecv.h
InputName=msgrecv

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\msgsms.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\msgsms.h
InputName=msgsms

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\msgsms.h
InputName=msgsms

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\msgurl.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\msgurl.h
InputName=msgurl

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\msgurl.h
InputName=msgurl

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\msgview.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\msgview.h
InputName=msgview

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\msgview.h
InputName=msgview

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\newprotocol.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\newprotocol.h
InputName=newprotocol

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\newprotocol.h
InputName=newprotocol

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\newprotocolbase.h
# End Source File
# Begin Source File

SOURCE=.\nonim.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\nonim.h
InputName=nonim

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\nonim.h
InputName=nonim

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\nonimbase.h
# End Source File
# Begin Source File

SOURCE=.\pagerbase.h
# End Source File
# Begin Source File

SOURCE=.\pagerdetails.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\pagerdetails.h
InputName=pagerdetails

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\pagerdetails.h
InputName=pagerdetails

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\phonebase.h
# End Source File
# Begin Source File

SOURCE=.\phonedetails.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\phonedetails.h
InputName=phonedetails

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\phonedetails.h
InputName=phonedetails

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\plugincfg.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\plugincfg.h
InputName=plugincfg

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\plugincfg.h
InputName=plugincfg

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\plugincfgbase.h
# End Source File
# Begin Source File

SOURCE=.\prefcfg.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\prefcfg.h
InputName=prefcfg

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\prefcfg.h
InputName=prefcfg

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\prefcfgbase.h
# End Source File
# Begin Source File

SOURCE=.\search.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\search.h
InputName=search

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\search.h
InputName=search

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\searchall.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\searchall.h
InputName=searchall

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\searchall.h
InputName=searchall

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\searchallbase.h
# End Source File
# Begin Source File

SOURCE=.\searchbase.h
# End Source File
# Begin Source File

SOURCE=.\smscfg.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\smscfg.h
InputName=smscfg

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\smscfg.h
InputName=smscfg

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\smscfgbase.h
# End Source File
# Begin Source File

SOURCE=.\status.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\status.h
InputName=status

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\status.h
InputName=status

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\statuswnd.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\statuswnd.h
InputName=statuswnd

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\statuswnd.h
InputName=statuswnd

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\tmpl.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\tmpl.h
InputName=tmpl

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\tmpl.h
InputName=tmpl

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\toolsetup.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\toolsetup.h
InputName=toolsetup

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\toolsetup.h
InputName=toolsetup

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\toolsetupbase.h
# End Source File
# Begin Source File

SOURCE=.\usercfg.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\usercfg.h
InputName=usercfg

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\usercfg.h
InputName=usercfg

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\userhistorycfg.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\userhistorycfg.h
InputName=userhistorycfg

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\userhistorycfg.h
InputName=userhistorycfg

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\userhistorycfgbase.h
# End Source File
# Begin Source File

SOURCE=.\userlist.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\userlist.h
InputName=userlist

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\userlist.h
InputName=userlist

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\userview.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\userview.h
InputName=userview

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\userview.h
InputName=userview

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\userviewcfg.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\userviewcfg.h
InputName=userviewcfg

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\userviewcfg.h
InputName=userviewcfg

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\userviewcfgbase.h
# End Source File
# Begin Source File

SOURCE=.\userwnd.h

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\userwnd.h
InputName=userwnd

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\userwnd.h
InputName=userwnd

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\core.rc
# End Source File
# End Group
# Begin Group "Interfaces"

# PROP Default_Filter "ui"
# Begin Source File

SOURCE=.\arcfgbase.ui

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\arcfgbase.ui
InputName=arcfgbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\arcfgbase.ui
InputName=arcfgbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\autoreplybase.ui

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\autoreplybase.ui
InputName=autoreplybase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\autoreplybase.ui
InputName=autoreplybase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\cfgdlgbase.ui

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\cfgdlgbase.ui
InputName=cfgdlgbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\cfgdlgbase.ui
InputName=cfgdlgbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\connectionsettingsbase.ui

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\connectionsettingsbase.ui
InputName=connectionsettingsbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\connectionsettingsbase.ui
InputName=connectionsettingsbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\connectwndbase.ui

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\connectwndbase.ui
InputName=connectwndbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\connectwndbase.ui
InputName=connectwndbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\declinedlgbase.ui

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\declinedlgbase.ui
InputName=declinedlgbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\declinedlgbase.ui
InputName=declinedlgbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\editmailbase.ui

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\editmailbase.ui
InputName=editmailbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\editmailbase.ui
InputName=editmailbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\editphonebase.ui

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\editphonebase.ui
InputName=editphonebase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\editphonebase.ui
InputName=editphonebase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\filecfgbase.ui

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\filecfgbase.ui
InputName=filecfgbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\filecfgbase.ui
InputName=filecfgbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\filetransferbase.ui

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\filetransferbase.ui
InputName=filetransferbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\filetransferbase.ui
InputName=filetransferbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\historycfgbase.ui

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\historycfgbase.ui
InputName=historycfgbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\historycfgbase.ui
InputName=historycfgbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\interfacecfgbase.ui

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\interfacecfgbase.ui
InputName=interfacecfgbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\interfacecfgbase.ui
InputName=interfacecfgbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\logindlgbase.ui

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\logindlgbase.ui
InputName=logindlgbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\logindlgbase.ui
InputName=logindlgbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\maininfobase.ui

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\maininfobase.ui
InputName=maininfobase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\maininfobase.ui
InputName=maininfobase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\managerbase.ui

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\managerbase.ui
InputName=managerbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\managerbase.ui
InputName=managerbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\msgcfgbase.ui

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\msgcfgbase.ui
InputName=msgcfgbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\msgcfgbase.ui
InputName=msgcfgbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\newprotocolbase.ui

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\newprotocolbase.ui
InputName=newprotocolbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\newprotocolbase.ui
InputName=newprotocolbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\nonimbase.ui

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\nonimbase.ui
InputName=nonimbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\nonimbase.ui
InputName=nonimbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\pagerbase.ui

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\pagerbase.ui
InputName=pagerbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\pagerbase.ui
InputName=pagerbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\phonebase.ui

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\phonebase.ui
InputName=phonebase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\phonebase.ui
InputName=phonebase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\plugincfgbase.ui

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\plugincfgbase.ui
InputName=plugincfgbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\plugincfgbase.ui
InputName=plugincfgbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\prefcfgbase.ui

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\prefcfgbase.ui
InputName=prefcfgbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\prefcfgbase.ui
InputName=prefcfgbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\searchallbase.ui

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\searchallbase.ui
InputName=searchallbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\searchallbase.ui
InputName=searchallbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\searchbase.ui

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\searchbase.ui
InputName=searchbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\searchbase.ui
InputName=searchbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\smscfgbase.ui

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\smscfgbase.ui
InputName=smscfgbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\smscfgbase.ui
InputName=smscfgbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\toolsetupbase.ui

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\toolsetupbase.ui
InputName=toolsetupbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\toolsetupbase.ui
InputName=toolsetupbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\userhistorycfgbase.ui

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\userhistorycfgbase.ui
InputName=userhistorycfgbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\userhistorycfgbase.ui
InputName=userhistorycfgbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\userviewcfgbase.ui

!IF  "$(CFG)" == "_core - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\userviewcfgbase.ui
InputName=userviewcfgbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\userviewcfgbase.ui
InputName=userviewcfgbase

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "po"

# PROP Default_Filter "po"
# Begin Source File

SOURCE=..\..\po\bg.po

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Release
InputPath=..\..\po\bg.po
InputName=bg

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Debug
InputPath=..\..\po\bg.po
InputName=bg

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\po\ca.po

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Release
InputPath=..\..\po\ca.po
InputName=ca

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Debug
InputPath=..\..\po\ca.po
InputName=ca

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\po\cs.po

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Release
InputPath=..\..\po\cs.po
InputName=cs

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Debug
InputPath=..\..\po\cs.po
InputName=cs

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\po\de.po

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Release
InputPath=..\..\po\de.po
InputName=de

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Debug
InputPath=..\..\po\de.po
InputName=de

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\po\el.po

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Release
InputPath=..\..\po\el.po
InputName=el

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Debug
InputPath=..\..\po\el.po
InputName=el

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\po\es.po

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Release
InputPath=..\..\po\es.po
InputName=es

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Debug
InputPath=..\..\po\es.po
InputName=es

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\po\fr.po

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Release
InputPath=..\..\po\fr.po
InputName=fr

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Debug
InputPath=..\..\po\fr.po
InputName=fr

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\po\he.po

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Release
InputPath=..\..\po\he.po
InputName=he

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Debug
InputPath=..\..\po\he.po
InputName=he

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\po\hu.po

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Release
InputPath=..\..\po\hu.po
InputName=hu

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Debug
InputPath=..\..\po\hu.po
InputName=hu

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\po\it.po

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Release
InputPath=..\..\po\it.po
InputName=it

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Debug
InputPath=..\..\po\it.po
InputName=it

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\po\nl.po

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Release
InputPath=..\..\po\nl.po
InputName=nl

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Debug
InputPath=..\..\po\nl.po
InputName=nl

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\po\pl.po

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Release
InputPath=..\..\po\pl.po
InputName=pl

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Debug
InputPath=..\..\po\pl.po
InputName=pl

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\po\pt_BR.po

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Release
InputPath=..\..\po\pt_BR.po
InputName=pt_BR

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Debug
InputPath=..\..\po\pt_BR.po
InputName=pt_BR

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\po\ru.po

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Release
InputPath=..\..\po\ru.po
InputName=ru

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Debug
InputPath=..\..\po\ru.po
InputName=ru

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\po\sk.po

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Release
InputPath=..\..\po\sk.po
InputName=sk

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Debug
InputPath=..\..\po\sk.po
InputName=sk

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\po\sw.po

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Release
InputPath=..\..\po\sw.po
InputName=sw

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Debug
InputPath=..\..\po\sw.po
InputName=sw

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\po\th.po

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Release
InputPath=..\..\po\th.po
InputName=th

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Debug
InputPath=..\..\po\th.po
InputName=th

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\po\tr.po

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Release
InputPath=..\..\po\tr.po
InputName=tr

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Debug
InputPath=..\..\po\tr.po
InputName=tr

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\po\uk.po

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Release
InputPath=..\..\po\uk.po
InputName=uk

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Debug
InputPath=..\..\po\uk.po
InputName=uk

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\po\zh_TW.po

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Release
InputPath=..\..\po\zh_TW.po
InputName=zh_TW

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - msg2qm on $(InputPath)
OutDir=.\..\..\Debug
InputPath=..\..\po\zh_TW.po
InputName=zh_TW

"$(OutDir)\po\$(InputName).qm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	msg2qm $(InputPath) 
	move tr.qm $(OutDir)\po\$(InputName).qm 
	
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Pict"

# PROP Default_Filter "gif"
# Begin Source File

SOURCE=.\pict\connect.gif

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build - Copy $(InputPath)
OutDir=.\..\..\Release
InputPath=.\pict\connect.gif

"$(OutDir)\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy /Y $(InputPath) $(OutDir)\$(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - Copy $(InputPath)
OutDir=.\..\..\Debug
InputPath=.\pict\connect.gif

"$(OutDir)\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy /Y $(InputPath) $(OutDir)\$(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "styles"

# PROP Default_Filter "xsl"
# Begin Source File

SOURCE=.\styles\Separated.2.xsl

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build
OutDir=.\..\..\Release
InputPath=.\styles\Separated.2.xsl

"$(OutDir)\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy /Y $(InputPath) $(OutDir)\$(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - Copy $(InputPath)
OutDir=.\..\..\Debug
InputPath=.\styles\Separated.2.xsl

"$(OutDir)\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy /Y $(InputPath) $(OutDir)\$(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\styles\Separated.3.xsl

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build
OutDir=.\..\..\Release
InputPath=.\styles\Separated.3.xsl

"$(OutDir)\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy /Y $(InputPath) $(OutDir)\$(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - Copy $(InputPath)
OutDir=.\..\..\Debug
InputPath=.\styles\Separated.3.xsl

"$(OutDir)\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy /Y $(InputPath) $(OutDir)\$(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\styles\Separated.4.xsl

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build
OutDir=.\..\..\Release
InputPath=.\styles\Separated.4.xsl

"$(OutDir)\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy /Y $(InputPath) $(OutDir)\$(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - Copy $(InputPath)
OutDir=.\..\..\Debug
InputPath=.\styles\Separated.4.xsl

"$(OutDir)\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy /Y $(InputPath) $(OutDir)\$(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\styles\Separated.5.(2+3).xsl"

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build
OutDir=.\..\..\Release
InputPath=".\styles\Separated.5.(2+3).xsl"

"$(OutDir)\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy /Y $(InputPath) $(OutDir)\$(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - Copy $(InputPath)
OutDir=.\..\..\Debug
InputPath=".\styles\Separated.5.(2+3).xsl"

"$(OutDir)\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy /Y $(InputPath) $(OutDir)\$(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\styles\Separated.6.(2+4).xsl"

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build
OutDir=.\..\..\Release
InputPath=".\styles\Separated.6.(2+4).xsl"

"$(OutDir)\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy /Y $(InputPath) $(OutDir)\$(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - Copy $(InputPath)
OutDir=.\..\..\Debug
InputPath=".\styles\Separated.6.(2+4).xsl"

"$(OutDir)\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy /Y $(InputPath) $(OutDir)\$(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\styles\Separated.7.(3+4).xsl"

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build
OutDir=.\..\..\Release
InputPath=".\styles\Separated.7.(3+4).xsl"

"$(OutDir)\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy /Y $(InputPath) $(OutDir)\$(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - Copy $(InputPath)
OutDir=.\..\..\Debug
InputPath=".\styles\Separated.7.(3+4).xsl"

"$(OutDir)\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy /Y $(InputPath) $(OutDir)\$(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\styles\Separated.8.(2+3+4).xsl"

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build
OutDir=.\..\..\Release
InputPath=".\styles\Separated.8.(2+3+4).xsl"

"$(OutDir)\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy /Y $(InputPath) $(OutDir)\$(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - Copy $(InputPath)
OutDir=.\..\..\Debug
InputPath=".\styles\Separated.8.(2+3+4).xsl"

"$(OutDir)\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy /Y $(InputPath) $(OutDir)\$(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\styles\Separated.xsl

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build
OutDir=.\..\..\Release
InputPath=.\styles\Separated.xsl

"$(OutDir)\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy /Y $(InputPath) $(OutDir)\$(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - Copy $(InputPath)
OutDir=.\..\..\Debug
InputPath=.\styles\Separated.xsl

"$(OutDir)\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy /Y $(InputPath) $(OutDir)\$(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\styles\SIM.2.xsl

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build
OutDir=.\..\..\Release
InputPath=.\styles\SIM.2.xsl

"$(OutDir)\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy /Y $(InputPath) $(OutDir)\$(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - Copy $(InputPath)
OutDir=.\..\..\Debug
InputPath=.\styles\SIM.2.xsl

"$(OutDir)\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy /Y $(InputPath) $(OutDir)\$(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\styles\SIM.3.xsl

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build
OutDir=.\..\..\Release
InputPath=.\styles\SIM.3.xsl

"$(OutDir)\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy /Y $(InputPath) $(OutDir)\$(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - Copy $(InputPath)
OutDir=.\..\..\Debug
InputPath=.\styles\SIM.3.xsl

"$(OutDir)\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy /Y $(InputPath) $(OutDir)\$(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=".\styles\SIM.4.(2+3).xsl"

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build
OutDir=.\..\..\Release
InputPath=".\styles\SIM.4.(2+3).xsl"

"$(OutDir)\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy /Y $(InputPath) $(OutDir)\$(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - Copy $(InputPath)
OutDir=.\..\..\Debug
InputPath=".\styles\SIM.4.(2+3).xsl"

"$(OutDir)\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy /Y $(InputPath) $(OutDir)\$(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\styles\SIM.xsl

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build
OutDir=.\..\..\Release
InputPath=.\styles\SIM.xsl

"$(OutDir)\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy /Y $(InputPath) $(OutDir)\$(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - Copy $(InputPath)
OutDir=.\..\..\Debug
InputPath=.\styles\SIM.xsl

"$(OutDir)\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy /Y $(InputPath) $(OutDir)\$(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\styles\XChat.xsl

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build
OutDir=.\..\..\Release
InputPath=.\styles\XChat.xsl

"$(OutDir)\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy /Y $(InputPath) $(OutDir)\$(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - Copy $(InputPath)
OutDir=.\..\..\Debug
InputPath=.\styles\XChat.xsl

"$(OutDir)\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy /Y $(InputPath) $(OutDir)\$(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\styles\XChat2seconds.xsl

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build
OutDir=.\..\..\Release
InputPath=.\styles\XChat2seconds.xsl

"$(OutDir)\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy /Y $(InputPath) $(OutDir)\$(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - Copy $(InputPath)
OutDir=.\..\..\Debug
InputPath=.\styles\XChat2seconds.xsl

"$(OutDir)\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy /Y $(InputPath) $(OutDir)\$(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\styles\XChat3fullDate.xsl

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build
OutDir=.\..\..\Release
InputPath=.\styles\XChat3fullDate.xsl

"$(OutDir)\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy /Y $(InputPath) $(OutDir)\$(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - Copy $(InputPath)
OutDir=.\..\..\Debug
InputPath=.\styles\XChat3fullDate.xsl

"$(OutDir)\$(InputPath)" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy /Y $(InputPath) $(OutDir)\$(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "jisp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\jisp\1downarrow.png
# End Source File
# Begin Source File

SOURCE=.\jisp\1leftarrow.png
# End Source File
# Begin Source File

SOURCE=.\jisp\1rightarrow.png
# End Source File
# Begin Source File

SOURCE=.\jisp\1uparrow.png
# End Source File
# Begin Source File

SOURCE=.\jisp\add.png
# End Source File
# Begin Source File

SOURCE=.\jisp\aim.png
# End Source File
# Begin Source File

SOURCE=.\jisp\auth.png
# End Source File
# Begin Source File

SOURCE=.\jisp\away.png
# End Source File
# Begin Source File

SOURCE=.\jisp\bgcolor.png
# End Source File
# Begin Source File

SOURCE=.\jisp\button_cancel.png
# End Source File
# Begin Source File

SOURCE=.\jisp\button_ok.png
# End Source File
# Begin Source File

SOURCE=.\jisp\cancel.png
# End Source File
# Begin Source File

SOURCE=.\jisp\cell.png
# End Source File
# Begin Source File

SOURCE=.\jisp\chat.png
# End Source File
# Begin Source File

SOURCE=.\jisp\collapsed.png
# End Source File
# Begin Source File

SOURCE=.\jisp\configure.png
# End Source File
# Begin Source File

SOURCE=.\jisp\contacts.png
# End Source File
# Begin Source File

SOURCE=.\jisp\dnd.png
# End Source File
# Begin Source File

SOURCE=.\jisp\editcopy.png
# End Source File
# Begin Source File

SOURCE=.\jisp\editcut.png
# End Source File
# Begin Source File

SOURCE=.\jisp\editpaste.png
# End Source File
# Begin Source File

SOURCE=.\jisp\empty.png
# End Source File
# Begin Source File

SOURCE=.\jisp\encoding.png
# End Source File
# Begin Source File

SOURCE=.\jisp\encrypted.png
# End Source File
# Begin Source File

SOURCE=.\jisp\error.png
# End Source File
# Begin Source File

SOURCE=.\jisp\exit.png
# End Source File
# Begin Source File

SOURCE=.\jisp\expanded.png
# End Source File
# Begin Source File

SOURCE=.\jisp\fax.png
# End Source File
# Begin Source File

SOURCE=.\jisp\ffc.png
# End Source File
# Begin Source File

SOURCE=.\jisp\fgcolor.png
# End Source File
# Begin Source File

SOURCE=.\jisp\file.png
# End Source File
# Begin Source File

SOURCE=.\jisp\fileclose.png
# End Source File
# Begin Source File

SOURCE=.\jisp\fileopen.png
# End Source File
# Begin Source File

SOURCE=.\jisp\filesave.png
# End Source File
# Begin Source File

SOURCE=.\jisp\filter.png
# End Source File
# Begin Source File

SOURCE=.\jisp\find.png
# End Source File
# Begin Source File

SOURCE=.\jisp\grp_collapse.png
# End Source File
# Begin Source File

SOURCE=.\jisp\grp_create.png
# End Source File
# Begin Source File

SOURCE=.\jisp\grp_expand.png
# End Source File
# Begin Source File

SOURCE=.\jisp\grp_off.png
# End Source File
# Begin Source File

SOURCE=.\jisp\grp_on.png
# End Source File
# Begin Source File

SOURCE=.\jisp\grp_rename.png
# End Source File
# Begin Source File

SOURCE=.\jisp\help.png
# End Source File
# Begin Source File

SOURCE=.\jisp\history.png
# End Source File
# Begin Source File

SOURCE=.\jisp\home.png
# End Source File
# Begin Source File

SOURCE=.\jisp\icondef.xml

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build - Make sim.jisp
InputDir=.\jisp
IntDir=.\..\..\Release_Wrk
OutDir=.\..\..\Release
InputPath=.\jisp\icondef.xml

"$(OutDir)\icons\sim.jisp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	mkdir $(IntDir)\jisp 
	copy $(InputDir)\*.png $(IntDir)\jisp 
	copy $(InputDir)\icondef.xml $(IntDir)\jisp 
	jar -cMf $(OutDir)\icons\sim.jisp -C $(IntDir)\jisp . 
	del /Q $(IntDir)\jisp\*.* 
	rmdir /Q $(IntDir)\jisp 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - Make sim.jisp
InputDir=.\jisp
IntDir=.\..\..\Debug_Wrk
OutDir=.\..\..\Debug
InputPath=.\jisp\icondef.xml

"$(OutDir)\icons\sim.jisp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	mkdir $(IntDir)\jisp 
	copy $(InputDir)\*.png $(IntDir)\jisp 
	copy $(InputDir)\icondef.xml $(IntDir)\jisp 
	jar -cMf $(OutDir)\icons\sim.jisp -C $(IntDir)\jisp . 
	del /Q $(IntDir)\jisp\*.* 
	rmdir /Q $(IntDir)\jisp 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\jisp\icq.png
# End Source File
# Begin Source File

SOURCE=.\jisp\info.png
# End Source File
# Begin Source File

SOURCE=.\jisp\listmsg.png
# End Source File
# Begin Source File

SOURCE=.\jisp\mail_generic.png
# End Source File
# Begin Source File

SOURCE=.\jisp\message.png
# End Source File
# Begin Source File

SOURCE=.\jisp\more.png
# End Source File
# Begin Source File

SOURCE=.\jisp\msn.png
# End Source File
# Begin Source File

SOURCE=.\jisp\na.png
# End Source File
# Begin Source File

SOURCE=.\jisp\network.png
# End Source File
# Begin Source File

SOURCE=.\jisp\new.png
# End Source File
# Begin Source File

SOURCE=.\jisp\nonim.png
# End Source File
# Begin Source File

SOURCE=.\jisp\nophone.png
# End Source File
# Begin Source File

SOURCE=.\jisp\occupied.png
# End Source File
# Begin Source File

SOURCE=.\jisp\online_off.png
# End Source File
# Begin Source File

SOURCE=.\jisp\online_on.png
# End Source File
# Begin Source File

SOURCE=.\jisp\pager.png
# End Source File
# Begin Source File

SOURCE=.\jisp\phone.png
# End Source File
# Begin Source File

SOURCE=.\jisp\pict.png
# End Source File
# Begin Source File

SOURCE=.\jisp\redo.png
# End Source File
# Begin Source File

SOURCE=.\jisp\remove.png
# End Source File
# Begin Source File

SOURCE=.\jisp\run.png
# End Source File
# Begin Source File

SOURCE=.\jisp\security.png
# End Source File
# Begin Source File

SOURCE=.\jisp\sms.png
# End Source File
# Begin Source File

SOURCE=.\jisp\text.png
# End Source File
# Begin Source File

SOURCE=.\jisp\text_bold.png
# End Source File
# Begin Source File

SOURCE=.\jisp\text_italic.png
# End Source File
# Begin Source File

SOURCE=.\jisp\text_strike.png
# End Source File
# Begin Source File

SOURCE=.\jisp\text_under.png
# End Source File
# Begin Source File

SOURCE=.\jisp\translit.png
# End Source File
# Begin Source File

SOURCE=.\jisp\typing.png
# End Source File
# Begin Source File

SOURCE=.\jisp\undo.png
# End Source File
# Begin Source File

SOURCE=.\jisp\urgentmsg.png
# End Source File
# Begin Source File

SOURCE=.\jisp\url.png
# End Source File
# Begin Source File

SOURCE=.\jisp\webpress.png
# End Source File
# Begin Source File

SOURCE=.\jisp\work.png
# End Source File
# Begin Source File

SOURCE=.\jisp\yahoo.png
# End Source File
# Begin Source File

SOURCE=.\jisp\yahoo_away.png
# End Source File
# Begin Source File

SOURCE=.\jisp\yahoo_dnd.png
# End Source File
# Begin Source File

SOURCE=.\jisp\yahoo_offline.png
# End Source File
# End Group
# Begin Group "smiles"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\smiles\Angel.png
# End Source File
# Begin Source File

SOURCE=.\smiles\Angry.png
# End Source File
# Begin Source File

SOURCE=.\smiles\Annoyed.png
# End Source File
# Begin Source File

SOURCE=.\smiles\Cool.png
# End Source File
# Begin Source File

SOURCE=.\smiles\Crying.png
# End Source File
# Begin Source File

SOURCE=.\smiles\Embarrassed.png
# End Source File
# Begin Source File

SOURCE=.\smiles\Grin.png
# End Source File
# Begin Source File

SOURCE=.\smiles\icondef.xml

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build - Make smiles.jisp
InputDir=.\smiles
IntDir=.\..\..\Release_Wrk
OutDir=.\..\..\Release
InputPath=.\smiles\icondef.xml

"$(OutDir)\icons\smiles.jisp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	mkdir $(IntDir)\jisp 
	copy $(InputDir)\*.png $(IntDir)\jisp 
	copy $(InputDir)\icondef.xml $(IntDir)\jisp 
	jar -cMf $(OutDir)\icons\smiles.jisp -C $(IntDir)\jisp . 
	del /Q $(IntDir)\jisp\*.* 
	rmdir /Q $(IntDir)\jisp 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - Make smiles.jisp
InputDir=.\smiles
IntDir=.\..\..\Debug_Wrk
OutDir=.\..\..\Debug
InputPath=.\smiles\icondef.xml

"$(OutDir)\icons\smiles.jisp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	mkdir $(IntDir)\jisp 
	copy $(InputDir)\*.png $(IntDir)\jisp 
	copy $(InputDir)\icondef.xml $(IntDir)\jisp 
	jar -cMf $(OutDir)\icons\smiles.jisp -C $(IntDir)\jisp . 
	del /Q $(IntDir)\jisp\*.* 
	rmdir /Q $(IntDir)\jisp 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\smiles\Indifferent.png
# End Source File
# Begin Source File

SOURCE=.\smiles\Kiss.png
# End Source File
# Begin Source File

SOURCE=.\smiles\Sad.png
# End Source File
# Begin Source File

SOURCE=.\smiles\Skeptical.png
# End Source File
# Begin Source File

SOURCE=.\smiles\Smile.png
# End Source File
# Begin Source File

SOURCE=.\smiles\Surprised.png
# End Source File
# Begin Source File

SOURCE=.\smiles\Teaser.png
# End Source File
# Begin Source File

SOURCE=.\smiles\Uptight.png
# End Source File
# Begin Source File

SOURCE=.\smiles\Wink.png
# End Source File
# End Group
# Begin Group "icqlite"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\icqlite\0.png
# End Source File
# Begin Source File

SOURCE=.\icqlite\1.png
# End Source File
# Begin Source File

SOURCE=.\icqlite\10.png
# End Source File
# Begin Source File

SOURCE=.\icqlite\11.png
# End Source File
# Begin Source File

SOURCE=.\icqlite\12.png
# End Source File
# Begin Source File

SOURCE=.\icqlite\13.png
# End Source File
# Begin Source File

SOURCE=.\icqlite\14.png
# End Source File
# Begin Source File

SOURCE=.\icqlite\15.png
# End Source File
# Begin Source File

SOURCE=.\icqlite\16.png
# End Source File
# Begin Source File

SOURCE=.\icqlite\17.png
# End Source File
# Begin Source File

SOURCE=.\icqlite\18.png
# End Source File
# Begin Source File

SOURCE=.\icqlite\19.png
# End Source File
# Begin Source File

SOURCE=.\icqlite\2.png
# End Source File
# Begin Source File

SOURCE=.\icqlite\20.png
# End Source File
# Begin Source File

SOURCE=.\icqlite\21.png
# End Source File
# Begin Source File

SOURCE=.\icqlite\22.png
# End Source File
# Begin Source File

SOURCE=.\icqlite\23.png
# End Source File
# Begin Source File

SOURCE=.\icqlite\24.png
# End Source File
# Begin Source File

SOURCE=.\icqlite\25.png
# End Source File
# Begin Source File

SOURCE=.\icqlite\26.png
# End Source File
# Begin Source File

SOURCE=.\icqlite\27.png
# End Source File
# Begin Source File

SOURCE=.\icqlite\3.png
# End Source File
# Begin Source File

SOURCE=.\icqlite\4.png
# End Source File
# Begin Source File

SOURCE=.\icqlite\5.png
# End Source File
# Begin Source File

SOURCE=.\icqlite\6.png
# End Source File
# Begin Source File

SOURCE=.\icqlite\7.png
# End Source File
# Begin Source File

SOURCE=.\icqlite\8.png
# End Source File
# Begin Source File

SOURCE=.\icqlite\9.png
# End Source File
# Begin Source File

SOURCE=.\icqlite\icondef.xml

!IF  "$(CFG)" == "_core - Win32 Release"

# Begin Custom Build - Make icqlite.jisp
InputDir=.\icqlite
IntDir=.\..\..\Release_Wrk
OutDir=.\..\..\Release
InputPath=.\icqlite\icondef.xml

"$(OutDir)\icons\icqlite.jisp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	mkdir $(IntDir)\jisp 
	copy $(InputDir)\*.png $(IntDir)\jisp 
	copy $(InputDir)\icondef.xml $(IntDir)\jisp 
	jar -cMf $(OutDir)\icons\icqlite.jisp -C $(IntDir)\jisp . 
	del /Q $(IntDir)\jisp\*.* 
	rmdir /Q $(IntDir)\jisp 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "_core - Win32 Debug"

# Begin Custom Build - Make icqlite.jisp
InputDir=.\icqlite
IntDir=.\..\..\Debug_Wrk
OutDir=.\..\..\Debug
InputPath=.\icqlite\icondef.xml

"$(OutDir)\icons\icqlite.jisp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	mkdir $(IntDir)\jisp 
	copy $(InputDir)\*.png $(IntDir)\jisp 
	copy $(InputDir)\icondef.xml $(IntDir)\jisp 
	jar -cMf $(OutDir)\icons\icqlite.jisp -C $(IntDir)\jisp . 
	del /Q $(IntDir)\jisp\*.* 
	rmdir /Q $(IntDir)\jisp 
	
# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
