# Microsoft Developer Studio Project File - Name="AutumnFramework" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=AutumnFramework - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AutumnFramework.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AutumnFramework.mak" CFG="AutumnFramework - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AutumnFramework - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "AutumnFramework - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AutumnFramework - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "AUTUMNFRAMEWORK_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\ext\log4cxx0.9.7\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "AUTUMNFRAMEWORK_EXPORTS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib log4cxx.lib /nologo /dll /machine:I386 /libpath:"..\..\ext\log4cxx0.9.7\lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy release\autumnframework.dll  ..\lib\	copy release\autumnframework.lib  ..\lib\	copy IBeanWrapper.h ..\include	copy IBeanFactory.h ..\include
# End Special Build Tool

!ELSEIF  "$(CFG)" == "AutumnFramework - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "AUTUMNFRAMEWORK_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W2 /Gm /GX /ZI /Od /I "..\..\ext\log4cxx0.9.7\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "AUTUMNFRAMEWORK_EXPORTS" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib log4cxx.lib /nologo /dll /debug /machine:I386 /out:"Debug/AutumnFramework_D.dll" /pdbtype:sept /libpath:"..\..\ext\log4cxx0.9.7\lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy debug\autumnframework_d.dll  ..\lib\	copy debug\autumnframework_d.lib  ..\lib\	copy IBeanWrapper.h ..\include	copy IBeanFactory.h ..\include
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "AutumnFramework - Win32 Release"
# Name "AutumnFramework - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AutumnConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\AutumnLog.cpp
# End Source File
# Begin Source File

SOURCE=.\BeanConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\BeanFactoryImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\BeanManager.cpp
# End Source File
# Begin Source File

SOURCE=.\BeanProperty.cpp
# End Source File
# Begin Source File

SOURCE=.\IBeanFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\IBeanWrapper.cpp
# End Source File
# Begin Source File

SOURCE=.\LocalLibrary.cpp
# End Source File
# Begin Source File

SOURCE=.\PointerType.cpp
# End Source File
# Begin Source File

SOURCE=.\TypeManager.cpp
# End Source File
# Begin Source File

SOURCE=.\ValueWrapper.cpp
# End Source File
# Begin Source File

SOURCE=.\xmlParser.cpp
# End Source File
# Begin Source File

SOURCE=.\XMLResource.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ArrayType.h
# End Source File
# Begin Source File

SOURCE=.\AutumnConfig.h
# End Source File
# Begin Source File

SOURCE=.\AutumnDefinition.h
# End Source File
# Begin Source File

SOURCE=.\AutumnException.h
# End Source File
# Begin Source File

SOURCE=.\AutumnLog.h
# End Source File
# Begin Source File

SOURCE=.\Basic.h
# End Source File
# Begin Source File

SOURCE=.\BasicType.h
# End Source File
# Begin Source File

SOURCE=.\BeanConfig.h
# End Source File
# Begin Source File

SOURCE=.\BeanFactoryImpl.h
# End Source File
# Begin Source File

SOURCE=.\BeanManager.h
# End Source File
# Begin Source File

SOURCE=.\BeanProperty.h
# End Source File
# Begin Source File

SOURCE=.\ConsoleLogger.h
# End Source File
# Begin Source File

SOURCE=.\DynamicLibrary.h
# End Source File
# Begin Source File

SOURCE=.\IBasicType.h
# End Source File
# Begin Source File

SOURCE=.\IBeanFactory.h
# End Source File
# Begin Source File

SOURCE=.\IBeanWrapper.h
# End Source File
# Begin Source File

SOURCE=.\ICombinedType.h
# End Source File
# Begin Source File

SOURCE=.\ILibrary.h
# End Source File
# Begin Source File

SOURCE=.\ILogAdapter.h
# End Source File
# Begin Source File

SOURCE=.\IResource.h
# End Source File
# Begin Source File

SOURCE=.\LocalLibrary.h
# End Source File
# Begin Source File

SOURCE=.\MapHashTable.h
# End Source File
# Begin Source File

SOURCE=.\ObjectType.h
# End Source File
# Begin Source File

SOURCE=.\PointerType.h
# End Source File
# Begin Source File

SOURCE=.\PropertyDefinition.h
# End Source File
# Begin Source File

SOURCE=.\StringType.h
# End Source File
# Begin Source File

SOURCE=.\TypeManager.h
# End Source File
# Begin Source File

SOURCE=.\ValueWrapper.h
# End Source File
# Begin Source File

SOURCE=.\xmlParser.h
# End Source File
# Begin Source File

SOURCE=.\XMLResource.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
