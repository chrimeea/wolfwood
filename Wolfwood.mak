# Microsoft Developer Studio Generated NMAKE File, Based on Wolfwood.dsp
!IF "$(CFG)" == ""
CFG=Wolfwood - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Wolfwood - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Wolfwood - Win32 Release" && "$(CFG)" != "Wolfwood - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Wolfwood - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\Wolfwood.exe"


CLEAN :
	-@erase "$(INTDIR)\AnimatedEntity.obj"
	-@erase "$(INTDIR)\AttributeManager.obj"
	-@erase "$(INTDIR)\AudioEngine.obj"
	-@erase "$(INTDIR)\AudioSource.obj"
	-@erase "$(INTDIR)\Background.obj"
	-@erase "$(INTDIR)\C3DSModel.obj"
	-@erase "$(INTDIR)\CAnimatedMesh.obj"
	-@erase "$(INTDIR)\CBufferPool.obj"
	-@erase "$(INTDIR)\Character.obj"
	-@erase "$(INTDIR)\CImageAreaBufferPool.obj"
	-@erase "$(INTDIR)\CLight.obj"
	-@erase "$(INTDIR)\CMaterial.obj"
	-@erase "$(INTDIR)\CMD2Model.obj"
	-@erase "$(INTDIR)\CMesh.obj"
	-@erase "$(INTDIR)\CMeshBufferPool.obj"
	-@erase "$(INTDIR)\Config.obj"
	-@erase "$(INTDIR)\CPathFinder.obj"
	-@erase "$(INTDIR)\CRenderer.obj"
	-@erase "$(INTDIR)\CTextureBufferPool.obj"
	-@erase "$(INTDIR)\CTextureMap.obj"
	-@erase "$(INTDIR)\CWorldMap.obj"
	-@erase "$(INTDIR)\Dictionary.obj"
	-@erase "$(INTDIR)\Entity.obj"
	-@erase "$(INTDIR)\EventsManager.obj"
	-@erase "$(INTDIR)\Logger.obj"
	-@erase "$(INTDIR)\Main.obj"
	-@erase "$(INTDIR)\Scene.obj"
	-@erase "$(INTDIR)\ScriptManager.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vector.obj"
	-@erase "$(OUTDIR)\Wolfwood.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\Wolfwood.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Wolfwood.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=vorbisfile_static.lib vorbisenc_static.lib vorbis_static.lib ogg_static.lib core.lib standard.lib opengl32.lib glu32.lib glaux.lib corona.lib alut.lib openal32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\Wolfwood.pdb" /machine:I386 /nodefaultlib:"libcmt.lib" /out:"$(OUTDIR)\Wolfwood.exe" /libpath:"lib\al" /libpath:"lib\corona" /libpath:"lib\ogg" /libpath:"lib\lua" 
LINK32_OBJS= \
	"$(INTDIR)\AudioEngine.obj" \
	"$(INTDIR)\AudioSource.obj" \
	"$(INTDIR)\CMD2Model.obj" \
	"$(INTDIR)\C3DSModel.obj" \
	"$(INTDIR)\CAnimatedMesh.obj" \
	"$(INTDIR)\CLight.obj" \
	"$(INTDIR)\CMaterial.obj" \
	"$(INTDIR)\CMesh.obj" \
	"$(INTDIR)\CMeshBufferPool.obj" \
	"$(INTDIR)\CRenderer.obj" \
	"$(INTDIR)\CTextureBufferPool.obj" \
	"$(INTDIR)\CTextureMap.obj" \
	"$(INTDIR)\vector.obj" \
	"$(INTDIR)\EventsManager.obj" \
	"$(INTDIR)\ScriptManager.obj" \
	"$(INTDIR)\AnimatedEntity.obj" \
	"$(INTDIR)\AttributeManager.obj" \
	"$(INTDIR)\Character.obj" \
	"$(INTDIR)\Entity.obj" \
	"$(INTDIR)\Scene.obj" \
	"$(INTDIR)\CBufferPool.obj" \
	"$(INTDIR)\Config.obj" \
	"$(INTDIR)\Dictionary.obj" \
	"$(INTDIR)\Logger.obj" \
	"$(INTDIR)\CPathFinder.obj" \
	"$(INTDIR)\CWorldMap.obj" \
	"$(INTDIR)\CImageAreaBufferPool.obj" \
	"$(INTDIR)\Main.obj" \
	"$(INTDIR)\Background.obj"

"$(OUTDIR)\Wolfwood.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Wolfwood - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Wolfwood.exe"


CLEAN :
	-@erase "$(INTDIR)\AnimatedEntity.obj"
	-@erase "$(INTDIR)\AttributeManager.obj"
	-@erase "$(INTDIR)\AudioEngine.obj"
	-@erase "$(INTDIR)\AudioSource.obj"
	-@erase "$(INTDIR)\Background.obj"
	-@erase "$(INTDIR)\C3DSModel.obj"
	-@erase "$(INTDIR)\CAnimatedMesh.obj"
	-@erase "$(INTDIR)\CBufferPool.obj"
	-@erase "$(INTDIR)\Character.obj"
	-@erase "$(INTDIR)\CImageAreaBufferPool.obj"
	-@erase "$(INTDIR)\CLight.obj"
	-@erase "$(INTDIR)\CMaterial.obj"
	-@erase "$(INTDIR)\CMD2Model.obj"
	-@erase "$(INTDIR)\CMesh.obj"
	-@erase "$(INTDIR)\CMeshBufferPool.obj"
	-@erase "$(INTDIR)\Config.obj"
	-@erase "$(INTDIR)\CPathFinder.obj"
	-@erase "$(INTDIR)\CRenderer.obj"
	-@erase "$(INTDIR)\CTextureBufferPool.obj"
	-@erase "$(INTDIR)\CTextureMap.obj"
	-@erase "$(INTDIR)\CWorldMap.obj"
	-@erase "$(INTDIR)\Dictionary.obj"
	-@erase "$(INTDIR)\Entity.obj"
	-@erase "$(INTDIR)\EventsManager.obj"
	-@erase "$(INTDIR)\Logger.obj"
	-@erase "$(INTDIR)\Main.obj"
	-@erase "$(INTDIR)\Scene.obj"
	-@erase "$(INTDIR)\ScriptManager.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vector.obj"
	-@erase "$(OUTDIR)\Wolfwood.exe"
	-@erase "$(OUTDIR)\Wolfwood.ilk"
	-@erase "$(OUTDIR)\Wolfwood.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\Wolfwood.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Wolfwood.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=vorbisfile_static_d.lib vorbisenc_static_d.lib vorbis_static_d.lib ogg_static_d.lib core.lib standard.lib opengl32.lib glu32.lib glaux.lib corona.lib alut.lib openal32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\Wolfwood.pdb" /debug /machine:I386 /nodefaultlib:"libcmtd.lib" /out:"$(OUTDIR)\Wolfwood.exe" /pdbtype:sept /libpath:"lib\al" /libpath:"lib\corona" /libpath:"lib\ogg" /libpath:"lib\lua" 
LINK32_OBJS= \
	"$(INTDIR)\AudioEngine.obj" \
	"$(INTDIR)\AudioSource.obj" \
	"$(INTDIR)\CMD2Model.obj" \
	"$(INTDIR)\C3DSModel.obj" \
	"$(INTDIR)\CAnimatedMesh.obj" \
	"$(INTDIR)\CLight.obj" \
	"$(INTDIR)\CMaterial.obj" \
	"$(INTDIR)\CMesh.obj" \
	"$(INTDIR)\CMeshBufferPool.obj" \
	"$(INTDIR)\CRenderer.obj" \
	"$(INTDIR)\CTextureBufferPool.obj" \
	"$(INTDIR)\CTextureMap.obj" \
	"$(INTDIR)\vector.obj" \
	"$(INTDIR)\EventsManager.obj" \
	"$(INTDIR)\ScriptManager.obj" \
	"$(INTDIR)\AnimatedEntity.obj" \
	"$(INTDIR)\AttributeManager.obj" \
	"$(INTDIR)\Character.obj" \
	"$(INTDIR)\Entity.obj" \
	"$(INTDIR)\Scene.obj" \
	"$(INTDIR)\CBufferPool.obj" \
	"$(INTDIR)\Config.obj" \
	"$(INTDIR)\Dictionary.obj" \
	"$(INTDIR)\Logger.obj" \
	"$(INTDIR)\CPathFinder.obj" \
	"$(INTDIR)\CWorldMap.obj" \
	"$(INTDIR)\CImageAreaBufferPool.obj" \
	"$(INTDIR)\Main.obj" \
	"$(INTDIR)\Background.obj"

"$(OUTDIR)\Wolfwood.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Wolfwood.dep")
!INCLUDE "Wolfwood.dep"
!ELSE 
!MESSAGE Warning: cannot find "Wolfwood.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Wolfwood - Win32 Release" || "$(CFG)" == "Wolfwood - Win32 Debug"
SOURCE=.\src\audio\AudioEngine.cpp

"$(INTDIR)\AudioEngine.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\audio\AudioSource.cpp

"$(INTDIR)\AudioSource.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\rendering\CMD2Model.cpp

"$(INTDIR)\CMD2Model.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\rendering\C3DSModel.cpp

"$(INTDIR)\C3DSModel.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\rendering\CAnimatedMesh.cpp

"$(INTDIR)\CAnimatedMesh.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\rendering\CLight.cpp

"$(INTDIR)\CLight.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\rendering\CMaterial.cpp

"$(INTDIR)\CMaterial.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\rendering\CMesh.cpp

"$(INTDIR)\CMesh.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\rendering\CMeshBufferPool.cpp

"$(INTDIR)\CMeshBufferPool.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\rendering\CRenderer.cpp

"$(INTDIR)\CRenderer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\rendering\CTextureBufferPool.cpp

"$(INTDIR)\CTextureBufferPool.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\rendering\CTextureMap.cpp

"$(INTDIR)\CTextureMap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\rendering\vector.cpp

"$(INTDIR)\vector.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\game\events\EventsManager.cpp

"$(INTDIR)\EventsManager.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\game\scripting\ScriptManager.cpp

"$(INTDIR)\ScriptManager.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\game\AnimatedEntity.cpp

"$(INTDIR)\AnimatedEntity.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\game\AttributeManager.cpp

"$(INTDIR)\AttributeManager.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\game\Character.cpp

"$(INTDIR)\Character.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\game\Entity.cpp

"$(INTDIR)\Entity.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\game\Scene.cpp

"$(INTDIR)\Scene.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\utils\CBufferPool.cpp

"$(INTDIR)\CBufferPool.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\utils\Config.cpp

"$(INTDIR)\Config.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\utils\Dictionary.cpp

"$(INTDIR)\Dictionary.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\utils\Logger.cpp

"$(INTDIR)\Logger.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\ai\CPathFinder.cpp

"$(INTDIR)\CPathFinder.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\terrain\CWorldMap.cpp

"$(INTDIR)\CWorldMap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\background\Background.cpp

"$(INTDIR)\Background.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\background\CImageAreaBufferPool.cpp

"$(INTDIR)\CImageAreaBufferPool.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Main.cpp

"$(INTDIR)\Main.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

