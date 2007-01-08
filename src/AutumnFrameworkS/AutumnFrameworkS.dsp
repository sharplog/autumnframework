# Microsoft Developer Studio Project File - Name="AutumnFrameworkS" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=AutumnFrameworkS - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AutumnFrameworkS.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AutumnFrameworkS.mak" CFG="AutumnFrameworkS - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AutumnFrameworkS - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "AutumnFrameworkS - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AutumnFrameworkS - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\ext\log4cxx0.9.7\include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy    release\autumnframeworks.lib    ..\lib\	copy ..\autumnframework\IBeanFactory.h ..\include	copy ..\autumnframework\IBeanWrapper.h ..\include
# End Special Build Tool

!ELSEIF  "$(CFG)" == "AutumnFrameworkS - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\ext\log4cxx0.9.7\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Debug\AutumnFrameworkS_D.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy  debug\autumnframeworks_d.lib  ..\lib\	copy ..\autumnframework\IBeanWrapper.h ..\include	copy ..\autumnframework\IBeanFactory.h ..\include
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "AutumnFrameworkS - Win32 Release"
# Name "AutumnFrameworkS - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\AutumnFramework\AutumnConfig.cpp
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\AutumnLog.cpp
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\BeanConfig.cpp
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\BeanFactoryImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\BeanManager.cpp
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\BeanProperty.cpp
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\IBeanWrapper.cpp
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\LocalLibrary.cpp
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\PointerType.cpp
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\TypeManager.cpp
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\ValueWrapper.cpp
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\xmlParser.cpp
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\XMLResource.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\AutumnFramework\ArrayType.h
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\AutumnConfig.h
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\AutumnDefinition.h
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\AutumnException.h
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\AutumnLog.h
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\Basic.h
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\BasicType.h
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\BeanConfig.h
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\BeanFactoryImpl.h
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\BeanManager.h
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\BeanProperty.h
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\ConsoleLogger.h
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\DynamicLibrary.h
# End Source File
# Begin Source File

SOURCE=..\autumnframework\FileLogger.h
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\IBasicType.h
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\IBeanFactory.h
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\IBeanWrapper.h
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\ICombinedType.h
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\ILibrary.h
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\ILogAdapter.h
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\IResource.h
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\LocalLibrary.h
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\MapHashTable.h
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\ObjectType.h
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\PointerType.h
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\PropertyDefinition.h
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\StringType.h
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\TypeManager.h
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\ValueWrapper.h
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\xmlParser.h
# End Source File
# Begin Source File

SOURCE=..\AutumnFramework\XMLResource.h
# End Source File
# End Group
# End Target
# End Project
