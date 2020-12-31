# Microsoft Developer Studio Project File - Name="Wolfwood" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Wolfwood - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Wolfwood.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Wolfwood.mak" CFG="Wolfwood - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Wolfwood - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Wolfwood - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Wolfwood", BAAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Wolfwood - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x418 /d "NDEBUG"
# ADD RSC /l 0x418 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 vorbisfile_static.lib vorbisenc_static.lib vorbis_static.lib ogg_static.lib core.lib standard.lib opengl32.lib glu32.lib glaux.lib corona.lib alut.lib openal32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"libcmt.lib" /nodefaultlib:"libcd.lib" /libpath:"lib\al" /libpath:"lib\corona" /libpath:"lib\ogg" /libpath:"lib\lua"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Wolfwood - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /GX /O2 /I "include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x418 /d "_DEBUG"
# ADD RSC /l 0x418 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 vorbisfile_static_d.lib vorbisenc_static_d.lib vorbis_static_d.lib ogg_static_d.lib core.lib standard.lib opengl32.lib glu32.lib glaux.lib corona.lib alut.lib openal32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libcmtd.lib" /pdbtype:sept /libpath:"lib\lua" /libpath:"lib\al" /libpath:"lib\corona" /libpath:"lib\ogg"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "Wolfwood - Win32 Release"
# Name "Wolfwood - Win32 Debug"
# Begin Group "audio"

# PROP Default_Filter ""
# Begin Group "al"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\audio\al\al.h
# End Source File
# Begin Source File

SOURCE=.\include\audio\al\alc.h
# End Source File
# Begin Source File

SOURCE=.\include\audio\al\alctypes.h
# End Source File
# Begin Source File

SOURCE=.\include\audio\al\altypes.h
# End Source File
# Begin Source File

SOURCE=.\include\audio\al\alu.h
# End Source File
# Begin Source File

SOURCE=.\include\audio\al\alut.h
# End Source File
# Begin Source File

SOURCE=.\include\audio\al\aluttypes.h
# End Source File
# Begin Source File

SOURCE=.\include\audio\al\alutypes.h
# End Source File
# Begin Source File

SOURCE=.\include\audio\al\eax.h
# End Source File
# End Group
# Begin Group "ogg"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\audio\ogg\codec.h
# End Source File
# Begin Source File

SOURCE=.\include\audio\ogg\ogg.h
# End Source File
# Begin Source File

SOURCE=.\include\audio\ogg\os_types.h
# End Source File
# Begin Source File

SOURCE=.\include\audio\ogg\vorbisenc.h
# End Source File
# Begin Source File

SOURCE=.\include\audio\ogg\vorbisfile.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\src\audio\AudioEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\include\audio\AudioEngine.h
# End Source File
# Begin Source File

SOURCE=.\src\audio\AudioSource.cpp
# End Source File
# Begin Source File

SOURCE=.\include\audio\AudioSource.h
# End Source File
# End Group
# Begin Group "rendering"

# PROP Default_Filter ""
# Begin Group "corona"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\rendering\corona.h
# End Source File
# End Group
# Begin Group "md2"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\rendering\CMD2Model.cpp
# End Source File
# Begin Source File

SOURCE=.\include\rendering\CMD2Model.h
# End Source File
# Begin Source File

SOURCE=.\include\rendering\MD2Normals.h
# End Source File
# End Group
# Begin Group "3ds"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\rendering\C3DSModel.cpp
# End Source File
# Begin Source File

SOURCE=.\include\rendering\C3DSModel.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\include\rendering\3DSFormat_defines.h
# End Source File
# Begin Source File

SOURCE=.\src\rendering\CAnimatedMesh.cpp
# End Source File
# Begin Source File

SOURCE=.\include\rendering\CAnimatedMesh.h
# End Source File
# Begin Source File

SOURCE=.\src\rendering\CLight.cpp
# End Source File
# Begin Source File

SOURCE=.\include\rendering\CLight.h
# End Source File
# Begin Source File

SOURCE=.\src\rendering\CMaterial.cpp
# End Source File
# Begin Source File

SOURCE=.\include\rendering\CMaterial.h
# End Source File
# Begin Source File

SOURCE=.\src\rendering\CMesh.cpp
# End Source File
# Begin Source File

SOURCE=.\include\rendering\CMesh.h
# End Source File
# Begin Source File

SOURCE=.\src\rendering\CMeshBufferPool.cpp
# End Source File
# Begin Source File

SOURCE=.\include\rendering\CMeshBufferPool.h
# End Source File
# Begin Source File

SOURCE=.\src\rendering\CRenderer.cpp
# End Source File
# Begin Source File

SOURCE=.\include\rendering\CRenderer.h
# End Source File
# Begin Source File

SOURCE=.\src\rendering\CTextureBufferPool.cpp
# End Source File
# Begin Source File

SOURCE=.\include\rendering\CTextureBufferPool.h
# End Source File
# Begin Source File

SOURCE=.\src\rendering\CTextureMap.cpp
# End Source File
# Begin Source File

SOURCE=.\include\rendering\CTextureMap.h
# End Source File
# Begin Source File

SOURCE=.\src\rendering\FontSet.cpp
# End Source File
# Begin Source File

SOURCE=.\include\rendering\FontSet.h
# End Source File
# Begin Source File

SOURCE=.\include\rendering\glext.h
# End Source File
# Begin Source File

SOURCE=.\include\rendering\GLExtensions_Defs.h
# End Source File
# Begin Source File

SOURCE=.\include\rendering\MD2Structs.h
# End Source File
# Begin Source File

SOURCE=.\src\rendering\vector.cpp
# End Source File
# Begin Source File

SOURCE=.\include\rendering\vector.h
# End Source File
# End Group
# Begin Group "terrain"

# PROP Default_Filter ""
# End Group
# Begin Group "utils"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\utils\CBufferPool.cpp
# End Source File
# Begin Source File

SOURCE=.\include\utils\CBufferPool.h
# End Source File
# Begin Source File

SOURCE=.\src\utils\Config.cpp
# End Source File
# Begin Source File

SOURCE=.\include\utils\Config.h
# End Source File
# Begin Source File

SOURCE=.\src\utils\Dictionary.cpp
# End Source File
# Begin Source File

SOURCE=.\include\utils\Dictionary.h
# End Source File
# Begin Source File

SOURCE=.\include\utils\LinkedList.h
# End Source File
# Begin Source File

SOURCE=.\src\utils\Logger.cpp
# End Source File
# Begin Source File

SOURCE=.\include\utils\Logger.h
# End Source File
# Begin Source File

SOURCE=.\include\utils\Tree.h
# End Source File
# End Group
# Begin Group "ai"

# PROP Default_Filter ""
# End Group
# Begin Group "game"

# PROP Default_Filter ""
# Begin Group "scripting"

# PROP Default_Filter ""
# Begin Group "lua"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\game\scripting\lua\lauxlib.h
# End Source File
# Begin Source File

SOURCE=.\include\game\scripting\lua\lua.h
# End Source File
# Begin Source File

SOURCE=.\include\game\scripting\lua\lualib.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\src\game\scripting\Console.cpp
# End Source File
# Begin Source File

SOURCE=.\include\game\scripting\Console.h
# End Source File
# Begin Source File

SOURCE=.\src\game\scripting\ScriptCommands.cpp
# End Source File
# Begin Source File

SOURCE=.\include\game\scripting\ScriptCommands.h
# End Source File
# Begin Source File

SOURCE=.\src\game\scripting\ScriptManager.cpp
# End Source File
# Begin Source File

SOURCE=.\include\game\scripting\ScriptManager.h
# End Source File
# End Group
# Begin Group "events"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\game\events\Event.h
# End Source File
# Begin Source File

SOURCE=.\src\game\events\EventsManager.cpp
# End Source File
# Begin Source File

SOURCE=.\include\game\events\EventsManager.h
# End Source File
# Begin Source File

SOURCE=.\include\game\events\KeyPressedEvent.h
# End Source File
# Begin Source File

SOURCE=.\include\game\events\MoveEvent.h
# End Source File
# Begin Source File

SOURCE=.\include\game\events\Observer.h
# End Source File
# Begin Source File

SOURCE=.\include\game\events\Source.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\src\game\AnimatedEntity.cpp
# End Source File
# Begin Source File

SOURCE=.\include\game\AnimatedEntity.h
# End Source File
# Begin Source File

SOURCE=.\src\game\AttributeManager.cpp
# End Source File
# Begin Source File

SOURCE=.\include\game\AttributeManager.h
# End Source File
# Begin Source File

SOURCE=.\include\game\AttributeTypes.h
# End Source File
# Begin Source File

SOURCE=.\src\game\Character.cpp
# End Source File
# Begin Source File

SOURCE=.\include\game\Character.h
# End Source File
# Begin Source File

SOURCE=.\src\game\Entity.cpp
# End Source File
# Begin Source File

SOURCE=.\include\game\Entity.h
# End Source File
# Begin Source File

SOURCE=.\src\game\Scene.cpp
# End Source File
# Begin Source File

SOURCE=.\include\game\Scene.h
# End Source File
# End Group
# Begin Group "background"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\background\Background.cpp
# End Source File
# Begin Source File

SOURCE=.\include\background\Background.h
# End Source File
# Begin Source File

SOURCE=.\src\background\CImageAreaBufferPool.cpp
# End Source File
# Begin Source File

SOURCE=.\include\background\CImageAreaBufferPool.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Main.cpp
# End Source File
# End Target
# End Project
