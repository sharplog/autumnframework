# Microsoft Developer Studio Project File - Name="TestDll" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=TestDll - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TestDll.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TestDll.mak" CFG="TestDll - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TestDll - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TestDll - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TestDll - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "TESTDLL_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "." /I "..\..\include" /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "TESTDLL_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib AutumnFramework.lib /nologo /dll /machine:I386 /libpath:"..\..\lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy        release\TestDll.dll        ..\lib\  	copy        release\TestDll.dll        ..\lib\TestDll2.dll
# End Special Build Tool

!ELSEIF  "$(CFG)" == "TestDll - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "TESTDLL_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I "..\..\include" /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "TESTDLL_EXPORTS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib AutumnFramework_D.lib /nologo /dll /debug /machine:I386 /out:"Debug/TestDll_D.dll" /pdbtype:sept /libpath:"..\..\lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy          debug\TestDll_D.dll          ..\lib\         	copy          debug\TestDll_D.dll         ..\lib\TestDll2_D.dll
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "TestDll - Win32 Release"
# Name "TestDll - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BasicTypesBean_Wrapper.cpp
# End Source File
# Begin Source File

SOURCE=.\BeanTypeBean_Wrapper.cpp
# End Source File
# Begin Source File

SOURCE=.\Factories_Wrapper.cpp
# End Source File
# Begin Source File

SOURCE=.\FactoryMethodBean.cpp
# End Source File
# Begin Source File

SOURCE=.\FactoryMethodBean_Wrapper.cpp
# End Source File
# Begin Source File

SOURCE=.\InitDestBean_Wrapper.cpp
# End Source File
# Begin Source File

SOURCE=.\IProduct_Wrapper.cpp
# End Source File
# Begin Source File

SOURCE=.\MultiInheriteBean_Wrapper.cpp
# End Source File
# Begin Source File

SOURCE=.\MyBasicType_Wrapper.cpp
# End Source File
# Begin Source File

SOURCE=.\MyTypeBean_Wrapper.cpp
# End Source File
# Begin Source File

SOURCE=.\SelfManagedBean_Wrapper.cpp
# End Source File
# Begin Source File

SOURCE=.\SingletonBean_Wrapper.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BasicTypesBean.h

!IF  "$(CFG)" == "TestDll - Win32 Release"

USERDEP__BASIC="..\..\bin\AutumnGen.exe"	
# Begin Custom Build - Generating wrapper files for $(InputName).h
InputPath=.\BasicTypesBean.h
InputName=BasicTypesBean

BuildCmds= \
	..\..\bin\AutumnGen.exe $(InputName).h

"$(InputName)_Wrapper.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_Wrapper.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TestDll - Win32 Debug"

USERDEP__BASIC="..\..\bin\AutumnGen.exe"	
# Begin Custom Build - Generating wrapper files for $(InputName).h
InputPath=.\BasicTypesBean.h
InputName=BasicTypesBean

BuildCmds= \
	..\..\bin\AutumnGen.exe $(InputName).h

"$(InputName)_Wrapper.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_Wrapper.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\BasicTypesBean_Wrapper.h
# End Source File
# Begin Source File

SOURCE=.\BeanTypeBean.h

!IF  "$(CFG)" == "TestDll - Win32 Release"

USERDEP__BEANT="..\..\bin\AutumnGen.exe"	
# Begin Custom Build - Generating wrapper files for $(InputName).h
InputPath=.\BeanTypeBean.h
InputName=BeanTypeBean

BuildCmds= \
	..\..\bin\AutumnGen.exe $(InputName).h

"$(InputName)_Wrapper.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_Wrapper.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TestDll - Win32 Debug"

USERDEP__BEANT="..\..\bin\AutumnGen.exe"	
# Begin Custom Build - Generating wrapper files for $(InputName).h
InputPath=.\BeanTypeBean.h
InputName=BeanTypeBean

BuildCmds= \
	..\..\bin\AutumnGen.exe $(InputName).h

"$(InputName)_Wrapper.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_Wrapper.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\BeanTypeBean_Wrapper.h
# End Source File
# Begin Source File

SOURCE=.\Factories.h

!IF  "$(CFG)" == "TestDll - Win32 Release"

USERDEP__FACTO="..\..\bin\AutumnGen.exe"	
# Begin Custom Build - Generating wrapper files for $(InputName).h
InputPath=.\Factories.h
InputName=Factories

BuildCmds= \
	..\..\bin\AutumnGen.exe $(InputName).h

"$(InputName)_Wrapper.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_Wrapper.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TestDll - Win32 Debug"

USERDEP__FACTO="..\..\bin\AutumnGen.exe"	
# Begin Custom Build - Generating wrapper files for $(InputName).h
InputPath=.\Factories.h
InputName=Factories

BuildCmds= \
	..\..\bin\AutumnGen.exe $(InputName).h

"$(InputName)_Wrapper.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_Wrapper.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Factories_Wrapper.h
# End Source File
# Begin Source File

SOURCE=.\FactoryMethodBean.h

!IF  "$(CFG)" == "TestDll - Win32 Release"

USERDEP__FACTOR="..\..\bin\AutumnGen.exe"	
# Begin Custom Build - Generating wrapper files for $(InputName).h
InputPath=.\FactoryMethodBean.h
InputName=FactoryMethodBean

BuildCmds= \
	..\..\bin\AutumnGen.exe $(InputName).h

"$(InputName)_Wrapper.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_Wrapper.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TestDll - Win32 Debug"

USERDEP__FACTOR="..\..\bin\AutumnGen.exe"	
# Begin Custom Build - Generating wrapper files for $(InputName).h
InputPath=.\FactoryMethodBean.h
InputName=FactoryMethodBean

BuildCmds= \
	..\..\bin\AutumnGen.exe $(InputName).h

"$(InputName)_Wrapper.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_Wrapper.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FactoryMethodBean_Wrapper.h
# End Source File
# Begin Source File

SOURCE=..\include\IBasicTypesBean.h
# End Source File
# Begin Source File

SOURCE=.\IFactory.h
# End Source File
# Begin Source File

SOURCE=..\include\IMultiBase.h
# End Source File
# Begin Source File

SOURCE=.\InitDestBean.h

!IF  "$(CFG)" == "TestDll - Win32 Release"

USERDEP__INITD="..\..\bin\AutumnGen.exe"	
# Begin Custom Build - Generating wrapper files for $(InputName).h
InputPath=.\InitDestBean.h
InputName=InitDestBean

BuildCmds= \
	..\..\bin\AutumnGen.exe $(InputName).h

"$(InputName)_Wrapper.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_Wrapper.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TestDll - Win32 Debug"

USERDEP__INITD="..\..\bin\AutumnGen.exe"	
# Begin Custom Build - Generating wrapper files for $(InputName).h
InputPath=.\InitDestBean.h
InputName=InitDestBean

BuildCmds= \
	..\..\bin\AutumnGen.exe $(InputName).h

"$(InputName)_Wrapper.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_Wrapper.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\InitDestBean_Wrapper.h
# End Source File
# Begin Source File

SOURCE=..\include\IProduct.h

!IF  "$(CFG)" == "TestDll - Win32 Release"

USERDEP__IPROD="..\..\bin\AutumnGen.exe"	
# Begin Custom Build - Generating wrapper files for $(InputName).h
InputPath=..\include\IProduct.h
InputName=IProduct

BuildCmds= \
	..\..\bin\AutumnGen.exe -out . $(InputPath)

"$(InputName)_Wrapper.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_Wrapper.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TestDll - Win32 Debug"

USERDEP__IPROD="..\..\bin\AutumnGen.exe"	
# Begin Custom Build - Generating wrapper files for $(InputName).h
InputPath=..\include\IProduct.h
InputName=IProduct

BuildCmds= \
	..\..\bin\AutumnGen.exe -out . $(InputPath)

"$(InputName)_Wrapper.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_Wrapper.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\IProduct_Wrapper.h
# End Source File
# Begin Source File

SOURCE=.\MultiInheriteBean.h

!IF  "$(CFG)" == "TestDll - Win32 Release"

USERDEP__MULTI="..\..\bin\AutumnGen.exe"	
# Begin Custom Build - Generating wrapper files for $(InputName).h
InputPath=.\MultiInheriteBean.h
InputName=MultiInheriteBean

BuildCmds= \
	..\..\bin\AutumnGen.exe $(InputName).h

"$(InputName)_Wrapper.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_Wrapper.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TestDll - Win32 Debug"

USERDEP__MULTI="..\..\bin\AutumnGen.exe"	
# Begin Custom Build - Generating wrapper files for $(InputName).h
InputPath=.\MultiInheriteBean.h
InputName=MultiInheriteBean

BuildCmds= \
	..\..\bin\AutumnGen.exe $(InputName).h

"$(InputName)_Wrapper.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_Wrapper.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MultiInheriteBean_Wrapper.h
# End Source File
# Begin Source File

SOURCE=.\MyBasicType.h

!IF  "$(CFG)" == "TestDll - Win32 Release"

USERDEP__MYBAS="..\..\bin\AutumnGen.exe"	
# Begin Custom Build - Generating wrapper files for $(InputName).h
InputPath=.\MyBasicType.h
InputName=MyBasicType

BuildCmds= \
	..\..\bin\AutumnGen.exe $(InputName).h

"$(InputName)_Wrapper.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_Wrapper.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TestDll - Win32 Debug"

USERDEP__MYBAS="..\..\bin\AutumnGen.exe"	
# Begin Custom Build - Generating wrapper files for $(InputName).h
InputPath=.\MyBasicType.h
InputName=MyBasicType

BuildCmds= \
	..\..\bin\AutumnGen.exe $(InputName).h

"$(InputName)_Wrapper.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_Wrapper.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MyBasicType_Wrapper.h
# End Source File
# Begin Source File

SOURCE=.\MyCombinedTypeMap.h
# End Source File
# Begin Source File

SOURCE=.\MyData.h
# End Source File
# Begin Source File

SOURCE=.\MyTypeBean.h

!IF  "$(CFG)" == "TestDll - Win32 Release"

USERDEP__MYTYP="..\..\bin\AutumnGen.exe"	
# Begin Custom Build - Generating wrapper files for $(InputName).h
InputPath=.\MyTypeBean.h
InputName=MyTypeBean

BuildCmds= \
	..\..\bin\AutumnGen.exe $(InputName).h

"$(InputName)_Wrapper.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_Wrapper.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TestDll - Win32 Debug"

USERDEP__MYTYP="..\..\bin\AutumnGen.exe"	
# Begin Custom Build - Generating wrapper files for $(InputName).h
InputPath=.\MyTypeBean.h
InputName=MyTypeBean

BuildCmds= \
	..\..\bin\AutumnGen.exe $(InputName).h

"$(InputName)_Wrapper.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_Wrapper.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MyTypeBean_Wrapper.h
# End Source File
# Begin Source File

SOURCE=.\Products.h
# End Source File
# Begin Source File

SOURCE=.\SelfManagedBean.h

!IF  "$(CFG)" == "TestDll - Win32 Release"

USERDEP__SELFM="..\..\bin\AutumnGen.exe"	
# Begin Custom Build - Generating wrapper files for $(InputName).h
InputPath=.\SelfManagedBean.h
InputName=SelfManagedBean

BuildCmds= \
	..\..\bin\AutumnGen.exe $(InputName).h

"$(InputName)_Wrapper.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_Wrapper.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TestDll - Win32 Debug"

USERDEP__SELFM="..\..\bin\AutumnGen.exe"	
# Begin Custom Build - Generating wrapper files for $(InputName).h
InputPath=.\SelfManagedBean.h
InputName=SelfManagedBean

BuildCmds= \
	..\..\bin\AutumnGen.exe $(InputName).h

"$(InputName)_Wrapper.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_Wrapper.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SelfManagedBean_Wrapper.h
# End Source File
# Begin Source File

SOURCE=.\SingletonBean.h

!IF  "$(CFG)" == "TestDll - Win32 Release"

USERDEP__SINGL="..\..\bin\AutumnGen.exe"	
# Begin Custom Build - Generating wrapper files for $(InputName).h
InputPath=.\SingletonBean.h
InputName=SingletonBean

BuildCmds= \
	..\..\bin\AutumnGen.exe $(InputName).h

"$(InputName)_Wrapper.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_Wrapper.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TestDll - Win32 Debug"

USERDEP__SINGL="..\..\bin\AutumnGen.exe"	
# Begin Custom Build - Generating wrapper files for $(InputName).h
InputPath=.\SingletonBean.h
InputName=SingletonBean

BuildCmds= \
	..\..\bin\AutumnGen.exe $(InputName).h

"$(InputName)_Wrapper.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_Wrapper.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SingletonBean_Wrapper.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
