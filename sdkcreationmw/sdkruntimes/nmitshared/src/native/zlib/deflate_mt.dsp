# Microsoft Developer Studio Project File - Name="deflate_mt" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=deflate_mt - Win32 DLL Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "deflate_mt.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "deflate_mt.mak" CFG="deflate_mt - Win32 DLL Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "deflate_mt - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "deflate_mt - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "deflate_mt - Win32 DLL Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "deflate_mt - Win32 DLL Release" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "deflate_mt - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "build/mt/release"
# PROP BASE Intermediate_Dir "build/mt/release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "build/mt/release"
# PROP Intermediate_Dir "build/mt/release"
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /U "DEBUG" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "deflate_mt - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "build/mt/debug"
# PROP BASE Intermediate_Dir "build/mt/debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "build/mt/debug"
# PROP Intermediate_Dir "build/mt/debug"
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /GX /Z7 /Od /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /U "DEBUG" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"build/mt/debug/deflate_mtd.lib"

!ELSEIF  "$(CFG)" == "deflate_mt - Win32 DLL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "build/mt/debug"
# PROP BASE Intermediate_Dir "build/mt/debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "build/mt/debug"
# PROP Intermediate_Dir "build/mt/debug"
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /MDd /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /GX /Z7 /Od /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /U "DEBUG" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"build/mt/debug/deflate_mtd.lib"
# ADD LIB32 /nologo /out:"build/mt/debug/deflate_mtd.lib"

!ELSEIF  "$(CFG)" == "deflate_mt - Win32 DLL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "build/mt/release"
# PROP BASE Intermediate_Dir "build/mt/release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "build/mt/release"
# PROP Intermediate_Dir "build/mt/release"
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /U "DEBUG" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /U "DEBUG" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "deflate_mt - Win32 Release"
# Name "deflate_mt - Win32 Debug"
# Name "deflate_mt - Win32 DLL Debug"
# Name "deflate_mt - Win32 DLL Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\adler32.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\compress.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\crc32.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\deflate.c
# End Source File
# Begin Source File

SOURCE=.\gzio.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\infblock.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\infcodes.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\inffast.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\inflate.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\inftrees.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\infutil.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\trees.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\uncompr.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\zutil.c
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\deflate.h
# End Source File
# Begin Source File

SOURCE=.\infblock.h
# End Source File
# Begin Source File

SOURCE=.\infcodes.h
# End Source File
# Begin Source File

SOURCE=.\inffast.h
# End Source File
# Begin Source File

SOURCE=.\inffixed.h
# End Source File
# Begin Source File

SOURCE=.\inftrees.h
# End Source File
# Begin Source File

SOURCE=.\infutil.h
# End Source File
# Begin Source File

SOURCE=.\trees.h
# End Source File
# Begin Source File

SOURCE=.\zconf.h
# End Source File
# Begin Source File

SOURCE=.\zlib.h
# End Source File
# Begin Source File

SOURCE=.\zutil.h
# End Source File
# End Group
# End Target
# End Project
