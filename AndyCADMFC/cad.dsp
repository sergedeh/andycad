# Microsoft Developer Studio Project File - Name="cad" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=cad - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "cad.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "cad.mak" CFG="cad - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "cad - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "cad - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "cad - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zd /I "C:\Program Files\HTML Help Workshop\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /libpath:"C:\Program Files\HTML Help Workshop\LIB" /MAPINFO:LINES /MAPINFO:EXPORTS
# SUBTRACT LINK32 /pdb:none /map /nodefaultlib

!ELSEIF  "$(CFG)" == "cad - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FAcs /Yu"stdafx.h" /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /pdb:none /debug /machine:I386
# SUBTRACT LINK32 /map /force

!ENDIF 

# Begin Target

# Name "cad - Win32 Release"
# Name "cad - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AABB.cpp
# End Source File
# Begin Source File

SOURCE=.\AddinManager1.cpp
# End Source File
# Begin Source File

SOURCE=.\AddinSettingsDialog1.cpp
# End Source File
# Begin Source File

SOURCE=.\AndyCad.cpp
# End Source File
# Begin Source File

SOURCE=.\AndyCadAddin.cpp
# End Source File
# Begin Source File

SOURCE=.\ArrayAngle.cpp
# End Source File
# Begin Source File

SOURCE=.\BArrowC.cpp
# End Source File
# Begin Source File

SOURCE=.\BArrowP.cpp
# End Source File
# Begin Source File

SOURCE=.\Bezier.cpp
# End Source File
# Begin Source File

SOURCE=.\BoolP.cpp
# End Source File
# Begin Source File

SOURCE=.\cad.cpp
# End Source File
# Begin Source File

SOURCE=.\hlp\cad.hpj

!IF  "$(CFG)" == "cad - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__CAD_H="hlp\AfxCore.rtf"	"hlp\AfxPrint.rtf"	"hlp\$(TargetName).hm"	
# Begin Custom Build - Making help file...
OutDir=.\Release
TargetName=cad
InputPath=.\hlp\cad.hpj
InputName=cad

"$(OutDir)\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /wait hcw /C /E /M "hlp\$(InputName).hpj" 
	if errorlevel 1 goto :Error 
	if not exist "hlp\$(InputName).hlp" goto :Error 
	copy "hlp\$(InputName).hlp" $(OutDir) 
	goto :done 
	:Error 
	echo hlp\$(InputName).hpj(1) : error: 
	type "hlp\$(InputName).log" 
	:done 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "cad - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__CAD_H="hlp\AfxCore.rtf"	"hlp\AfxPrint.rtf"	"hlp\$(TargetName).hm"	
# Begin Custom Build - Making help file...
OutDir=.\Debug
TargetName=cad
InputPath=.\hlp\cad.hpj
InputName=cad

"$(OutDir)\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /wait hcw /C /E /M "hlp\$(InputName).hpj" 
	if errorlevel 1 goto :Error 
	if not exist "hlp\$(InputName).hlp" goto :Error 
	copy "hlp\$(InputName).hlp" $(OutDir) 
	goto :done 
	:Error 
	echo hlp\$(InputName).hpj(1) : error: 
	type "hlp\$(InputName).log" 
	:done 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\cad.odl
# End Source File
# Begin Source File

SOURCE=.\cad.rc
# End Source File
# Begin Source File

SOURCE=.\CadAddIn.idl
# End Source File
# Begin Source File

SOURCE=.\CadAutoCamera.cpp
# End Source File
# Begin Source File

SOURCE=.\CadAutoCanvas.cpp
# End Source File
# Begin Source File

SOURCE=.\CadAutoCollection.cpp
# End Source File
# Begin Source File

SOURCE=.\CadAutoDrawing.cpp
# End Source File
# Begin Source File

SOURCE=.\CadAutoDrawingCollection.cpp
# End Source File
# Begin Source File

SOURCE=.\CadAutoEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\CAdAutoShape.cpp
# End Source File
# Begin Source File

SOURCE=.\CadAutoSurface.cpp
# End Source File
# Begin Source File

SOURCE=.\CadAutoTransform.cpp
# End Source File
# Begin Source File

SOURCE=.\CadAutoUtils.cpp
# End Source File
# Begin Source File

SOURCE=.\CadAutoVector.cpp
# End Source File
# Begin Source File

SOURCE=.\CadAutoWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\cadDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\cadView.cpp
# End Source File
# Begin Source File

SOURCE=.\CAM.cpp
# End Source File
# Begin Source File

SOURCE=.\CameraDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Cercle.cpp
# End Source File
# Begin Source File

SOURCE=.\ChamfD.cpp
# End Source File
# Begin Source File

SOURCE=.\Chamfer.cpp
# End Source File
# Begin Source File

SOURCE=.\ChFi.cpp
# End Source File
# Begin Source File

SOURCE=.\Click.cpp
# End Source File
# Begin Source File

SOURCE=.\CLineSty.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorD.cpp
# End Source File
# Begin Source File

SOURCE=.\Command.cpp
# End Source File
# Begin Source File

SOURCE=.\CPaperSize.cpp
# End Source File
# Begin Source File

SOURCE=.\CTreeCtrl.cpp

!IF  "$(CFG)" == "cad - Win32 Release"

!ELSEIF  "$(CFG)" == "cad - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CustomSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomWidth.cpp
# End Source File
# Begin Source File

SOURCE=.\CVector.cpp
# End Source File
# Begin Source File

SOURCE=.\Dim.cpp
# End Source File
# Begin Source File

SOURCE=.\DimA.cpp
# End Source File
# Begin Source File

SOURCE=.\DimL.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCap.cpp
# End Source File
# Begin Source File

SOURCE=.\Dot.cpp
# End Source File
# Begin Source File

SOURCE=.\Draw.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\Edge.cpp
# End Source File
# Begin Source File

SOURCE=.\EditMacroDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EditParse.cpp
# End Source File
# Begin Source File

SOURCE=.\Face.cpp
# End Source File
# Begin Source File

SOURCE=.\FFD.cpp
# End Source File
# Begin Source File

SOURCE=.\Figure.cpp
# End Source File
# Begin Source File

SOURCE=.\FileMacroDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FilenameEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\FloatP.cpp
# End Source File
# Begin Source File

SOURCE=.\font.cpp
# End Source File
# Begin Source File

SOURCE=.\geometry.cpp
# End Source File
# Begin Source File

SOURCE=.\GridPag.cpp
# End Source File
# Begin Source File

SOURCE=.\GridPage.cpp
# End Source File
# Begin Source File

SOURCE=.\Image.cpp
# End Source File
# Begin Source File

SOURCE=.\Imagex.cpp
# End Source File
# Begin Source File

SOURCE=.\InfoBar.cpp
# End Source File
# Begin Source File

SOURCE=.\Inter.cpp
# End Source File
# Begin Source File

SOURCE=.\IntP.cpp
# End Source File
# Begin Source File

SOURCE=.\LayBar.cpp
# End Source File
# Begin Source File

SOURCE=.\Layerad.cpp
# End Source File
# Begin Source File

SOURCE=.\LayerD.cpp
# End Source File
# Begin Source File

SOURCE=.\LayList.cpp
# End Source File
# Begin Source File

SOURCE=.\LComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\Libdialog.cpp
# End Source File
# Begin Source File

SOURCE=.\LibS.cpp
# End Source File
# Begin Source File

SOURCE=.\LightD.cpp
# End Source File
# Begin Source File

SOURCE=.\Line.cpp
# End Source File
# Begin Source File

SOURCE=.\LineAgain.cpp
# End Source File
# Begin Source File

SOURCE=.\LineBar.cpp
# End Source File
# Begin Source File

SOURCE=.\Linestyle.cpp
# End Source File
# Begin Source File

SOURCE=.\MacroManager.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Matrix1.cpp
# End Source File
# Begin Source File

SOURCE=.\MClick.cpp
# End Source File
# Begin Source File

SOURCE=.\mdccombo.cpp
# End Source File
# Begin Source File

SOURCE=.\Memento.cpp
# End Source File
# Begin Source File

SOURCE=.\Mesh.cpp
# End Source File
# Begin Source File

SOURCE=.\Mouse.cpp
# End Source File
# Begin Source File

SOURCE=.\MultVar.cpp
# End Source File
# Begin Source File

SOURCE=.\NewMacroDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\NumCopy.cpp
# End Source File
# Begin Source File

SOURCE=.\OBJEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\Observer.cpp
# End Source File
# Begin Source File

SOURCE=.\Operation.cpp
# End Source File
# Begin Source File

SOURCE=.\Optionsheet.cpp
# End Source File
# Begin Source File

SOURCE=.\OwnCombo.cpp
# End Source File
# Begin Source File

SOURCE=.\OwnList.cpp
# End Source File
# Begin Source File

SOURCE=.\PaperPag.cpp
# End Source File
# Begin Source File

SOURCE=.\PaperPage.cpp
# End Source File
# Begin Source File

SOURCE=.\ParseDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Parser.cpp
# End Source File
# Begin Source File

SOURCE=.\ParserFloat.cpp
# End Source File
# Begin Source File

SOURCE=.\ParserObject.cpp
# End Source File
# Begin Source File

SOURCE=.\ParserVar.cpp
# End Source File
# Begin Source File

SOURCE=.\ParserVerb.cpp
# End Source File
# Begin Source File

SOURCE=.\Pattern.cpp
# End Source File
# Begin Source File

SOURCE=.\PatternA.cpp

!IF  "$(CFG)" == "cad - Win32 Release"

# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "cad - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\picture.cpp
# End Source File
# Begin Source File

SOURCE=.\Plane.cpp
# End Source File
# Begin Source File

SOURCE=.\PolarTrackDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PopBar.cpp
# End Source File
# Begin Source File

SOURCE=.\Property.cpp
# End Source File
# Begin Source File

SOURCE=.\PropPage.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\QLine.cpp
# End Source File
# Begin Source File

SOURCE=.\QuadTree.cpp
# End Source File
# Begin Source File

SOURCE=.\Quaternion.cpp
# End Source File
# Begin Source File

SOURCE=.\Ray.cpp
# End Source File
# Begin Source File

SOURCE=.\RecArray.cpp
# End Source File
# Begin Source File

SOURCE=.\RecColor.cpp
# End Source File
# Begin Source File

SOURCE=.\RecPattern.cpp
# End Source File
# Begin Source File

SOURCE=.\Rectangle.cpp
# End Source File
# Begin Source File

SOURCE=.\RegDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\Register.cpp
# End Source File
# Begin Source File

SOURCE=.\Render.cpp
# End Source File
# Begin Source File

SOURCE=.\RTFACTN.CPP
# End Source File
# Begin Source File

SOURCE=.\Rtfreadr.cpp
# End Source File
# Begin Source File

SOURCE=.\Ruler1.cpp
# End Source File
# Begin Source File

SOURCE=.\RunMacroDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SmoothD.cpp
# End Source File
# Begin Source File

SOURCE=.\Snap.cpp
# End Source File
# Begin Source File

SOURCE=.\SnapDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SnapGridDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SnapObject.cpp
# End Source File
# Begin Source File

SOURCE=.\SnapObjectDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Splash.cpp
# End Source File
# Begin Source File

SOURCE=.\Spline.cpp
# End Source File
# Begin Source File

SOURCE=.\SplineProp.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\State.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StringP.cpp
# End Source File
# Begin Source File

SOURCE=.\Subject.cpp
# End Source File
# Begin Source File

SOURCE=.\SubWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\TextCad.cpp
# End Source File
# Begin Source File

SOURCE=.\textd.cpp
# End Source File
# Begin Source File

SOURCE=.\TextDi.cpp
# End Source File
# Begin Source File

SOURCE=.\ThickD.cpp
# End Source File
# Begin Source File

SOURCE=.\TipDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TransDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Translate.cpp
# End Source File
# Begin Source File

SOURCE=.\Triangle.cpp
# End Source File
# Begin Source File

SOURCE=.\TVector.cpp
# End Source File
# Begin Source File

SOURCE=.\TxtED.cpp
# End Source File
# Begin Source File

SOURCE=.\Unclick.cpp
# End Source File
# Begin Source File

SOURCE=.\Undo.cpp
# End Source File
# Begin Source File

SOURCE=.\Vector.cpp
# End Source File
# Begin Source File

SOURCE=.\Vectorm.cpp
# End Source File
# Begin Source File

SOURCE=.\Vectorp.cpp
# End Source File
# Begin Source File

SOURCE=.\Vectorv.cpp
# End Source File
# Begin Source File

SOURCE=.\Verb.cpp
# End Source File
# Begin Source File

SOURCE=.\Vertex.cpp
# End Source File
# Begin Source File

SOURCE=.\Zoombar.cpp
# End Source File
# Begin Source File

SOURCE=.\ZoomD.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AABB.h
# End Source File
# Begin Source File

SOURCE=.\AddinManager1.h
# End Source File
# Begin Source File

SOURCE=.\AddinSettingsDialog1.h
# End Source File
# Begin Source File

SOURCE=.\AndyCad.h
# End Source File
# Begin Source File

SOURCE=.\AndyCadAddin.h
# End Source File
# Begin Source File

SOURCE=.\ArrayAngle.h
# End Source File
# Begin Source File

SOURCE=.\BArrowC.h
# End Source File
# Begin Source File

SOURCE=.\BArrowP.h
# End Source File
# Begin Source File

SOURCE=.\Bezier.h
# End Source File
# Begin Source File

SOURCE=.\BoolP.h
# End Source File
# Begin Source File

SOURCE=.\cad.h
# End Source File
# Begin Source File

SOURCE=.\Cad_i.h
# End Source File
# Begin Source File

SOURCE=.\CadAddInCP.h
# End Source File
# Begin Source File

SOURCE=.\CadAutoCamera.h
# End Source File
# Begin Source File

SOURCE=.\CadAutoCanvas.h
# End Source File
# Begin Source File

SOURCE=.\CadAutoCollection.h
# End Source File
# Begin Source File

SOURCE=.\CadAutoDrawing.h
# End Source File
# Begin Source File

SOURCE=.\CadAutoDrawingCollection.h
# End Source File
# Begin Source File

SOURCE=.\CadAutoEdit.h
# End Source File
# Begin Source File

SOURCE=.\CAdAutoShape.h
# End Source File
# Begin Source File

SOURCE=.\CadAutoSurface.h
# End Source File
# Begin Source File

SOURCE=.\CadAutoTransform.h
# End Source File
# Begin Source File

SOURCE=.\CadAutoUtils.h
# End Source File
# Begin Source File

SOURCE=.\CadAutoVector.h
# End Source File
# Begin Source File

SOURCE=.\CadAutoWnd.h
# End Source File
# Begin Source File

SOURCE=.\cadDoc.h
# End Source File
# Begin Source File

SOURCE=.\cadView.h
# End Source File
# Begin Source File

SOURCE=.\CAM.h
# End Source File
# Begin Source File

SOURCE=.\CameraDlg.h
# End Source File
# Begin Source File

SOURCE=.\Cercle.h
# End Source File
# Begin Source File

SOURCE=.\ChamfD.h
# End Source File
# Begin Source File

SOURCE=.\Chamfer.h
# End Source File
# Begin Source File

SOURCE=.\ChFi.h
# End Source File
# Begin Source File

SOURCE=.\Click.h
# End Source File
# Begin Source File

SOURCE=.\CLineSty.h
# End Source File
# Begin Source File

SOURCE=.\ColorD.h
# End Source File
# Begin Source File

SOURCE=.\Command.h
# End Source File
# Begin Source File

SOURCE=.\CPaperSize.h
# End Source File
# Begin Source File

SOURCE=.\CTreeCtrl.h

!IF  "$(CFG)" == "cad - Win32 Release"

!ELSEIF  "$(CFG)" == "cad - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CustomSheet.h
# End Source File
# Begin Source File

SOURCE=.\CustomWidth.h
# End Source File
# Begin Source File

SOURCE=.\CVector.h
# End Source File
# Begin Source File

SOURCE=.\Dim.h
# End Source File
# Begin Source File

SOURCE=.\DimA.h
# End Source File
# Begin Source File

SOURCE=.\DimL.h
# End Source File
# Begin Source File

SOURCE=.\DlgCap.h
# End Source File
# Begin Source File

SOURCE=.\Dot.h
# End Source File
# Begin Source File

SOURCE=.\Draw.h
# End Source File
# Begin Source File

SOURCE=.\DrawWnd.h
# End Source File
# Begin Source File

SOURCE=.\Edge.h
# End Source File
# Begin Source File

SOURCE=.\EditMacroDlg.h
# End Source File
# Begin Source File

SOURCE=.\EditParse.h
# End Source File
# Begin Source File

SOURCE=.\Face.h
# End Source File
# Begin Source File

SOURCE=.\FFD.h
# End Source File
# Begin Source File

SOURCE=.\Figure.h
# End Source File
# Begin Source File

SOURCE=.\FileMacroDlg.h
# End Source File
# Begin Source File

SOURCE=.\FilenameEdit.h
# End Source File
# Begin Source File

SOURCE=.\FloatP.h
# End Source File
# Begin Source File

SOURCE=.\font.h
# End Source File
# Begin Source File

SOURCE=.\geometry.h
# End Source File
# Begin Source File

SOURCE=.\GridPag.h
# End Source File
# Begin Source File

SOURCE=.\GridPage.h
# End Source File
# Begin Source File

SOURCE=.\Image.h
# End Source File
# Begin Source File

SOURCE=.\Imagex.h
# End Source File
# Begin Source File

SOURCE=.\InfoBar.h
# End Source File
# Begin Source File

SOURCE=.\Inter.h
# End Source File
# Begin Source File

SOURCE=.\IntP.h
# End Source File
# Begin Source File

SOURCE=.\LayBar.h
# End Source File
# Begin Source File

SOURCE=.\Layerad.h
# End Source File
# Begin Source File

SOURCE=.\LayerD.h
# End Source File
# Begin Source File

SOURCE=.\LayList.h
# End Source File
# Begin Source File

SOURCE=.\LComboBox.h
# End Source File
# Begin Source File

SOURCE=.\Libdialog.h
# End Source File
# Begin Source File

SOURCE=.\LibS.h
# End Source File
# Begin Source File

SOURCE=.\LightD.h
# End Source File
# Begin Source File

SOURCE=.\Line.h
# End Source File
# Begin Source File

SOURCE=.\LineAgain.h
# End Source File
# Begin Source File

SOURCE=.\LineBar.h
# End Source File
# Begin Source File

SOURCE=.\LinePattern.h
# End Source File
# Begin Source File

SOURCE=.\Linestyle.h
# End Source File
# Begin Source File

SOURCE=.\LMenu.h
# End Source File
# Begin Source File

SOURCE=.\LNSTLYE.h
# End Source File
# Begin Source File

SOURCE=.\MacroManager.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Matrix1.h
# End Source File
# Begin Source File

SOURCE=.\MClick.h
# End Source File
# Begin Source File

SOURCE=.\mdccombo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\grace\ParticleTest\memdc.h
# End Source File
# Begin Source File

SOURCE=.\Memento.h
# End Source File
# Begin Source File

SOURCE=.\Mesh.h
# End Source File
# Begin Source File

SOURCE=.\Mouse.h
# End Source File
# Begin Source File

SOURCE=.\MultVar.h
# End Source File
# Begin Source File

SOURCE=.\NewMacroDlg.h
# End Source File
# Begin Source File

SOURCE=.\NumCopy.h
# End Source File
# Begin Source File

SOURCE=.\OBJEdit.h
# End Source File
# Begin Source File

SOURCE=.\Observer.h
# End Source File
# Begin Source File

SOURCE=.\Operation.h
# End Source File
# Begin Source File

SOURCE=.\Optionsheet.h
# End Source File
# Begin Source File

SOURCE=.\OwnCombo.h
# End Source File
# Begin Source File

SOURCE=.\OwnList.h
# End Source File
# Begin Source File

SOURCE=.\PaperPag.h
# End Source File
# Begin Source File

SOURCE=.\PaperPage.h
# End Source File
# Begin Source File

SOURCE=.\ParseDlg.h
# End Source File
# Begin Source File

SOURCE=.\Parser.h
# End Source File
# Begin Source File

SOURCE=.\ParserFloat.h
# End Source File
# Begin Source File

SOURCE=.\ParserObject.h
# End Source File
# Begin Source File

SOURCE=.\ParserVar.h
# End Source File
# Begin Source File

SOURCE=.\ParserVerb.h
# End Source File
# Begin Source File

SOURCE=.\Pattern.h
# End Source File
# Begin Source File

SOURCE=.\PatternA.h

!IF  "$(CFG)" == "cad - Win32 Release"

# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "cad - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PGrid.h
# End Source File
# Begin Source File

SOURCE=.\picture.h
# End Source File
# Begin Source File

SOURCE=.\Plane.h
# End Source File
# Begin Source File

SOURCE=.\PolarTrackDlg.h
# End Source File
# Begin Source File

SOURCE=.\PopBar.h
# End Source File
# Begin Source File

SOURCE=.\Property.h
# End Source File
# Begin Source File

SOURCE=.\PropPage.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\QLine.h
# End Source File
# Begin Source File

SOURCE=.\QuadTree.h
# End Source File
# Begin Source File

SOURCE=.\Quaternion.h
# End Source File
# Begin Source File

SOURCE=.\Ray.h
# End Source File
# Begin Source File

SOURCE=.\RecArray.h
# End Source File
# Begin Source File

SOURCE=.\RecColor.h
# End Source File
# Begin Source File

SOURCE=.\RecPattern.h
# End Source File
# Begin Source File

SOURCE=.\Rectangle.h
# End Source File
# Begin Source File

SOURCE=.\RegDialog.h
# End Source File
# Begin Source File

SOURCE=.\Register.h
# End Source File
# Begin Source File

SOURCE=.\Render.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h

!IF  "$(CFG)" == "cad - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=cad
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "cad - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=cad
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Rtfdecl.h
# End Source File
# Begin Source File

SOURCE=.\Rtftype.h
# End Source File
# Begin Source File

SOURCE=.\Ruler1.h
# End Source File
# Begin Source File

SOURCE=.\RunMacroDlg.h
# End Source File
# Begin Source File

SOURCE=.\SmoothD.h
# End Source File
# Begin Source File

SOURCE=.\Snap.h
# End Source File
# Begin Source File

SOURCE=.\SnapDlg.h
# End Source File
# Begin Source File

SOURCE=.\SnapGridDlg.h
# End Source File
# Begin Source File

SOURCE=.\SnapObject.h
# End Source File
# Begin Source File

SOURCE=.\SnapObjectDlg.h
# End Source File
# Begin Source File

SOURCE=.\Splash.h
# End Source File
# Begin Source File

SOURCE=.\Spline.h
# End Source File
# Begin Source File

SOURCE=.\SplineProp.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\State.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StringP.h
# End Source File
# Begin Source File

SOURCE=.\Subject.h
# End Source File
# Begin Source File

SOURCE=.\SubWnd.h
# End Source File
# Begin Source File

SOURCE=.\TextCad.h
# End Source File
# Begin Source File

SOURCE=.\TextD.h
# End Source File
# Begin Source File

SOURCE=.\TextDi.h
# End Source File
# Begin Source File

SOURCE=.\ThickD.h
# End Source File
# Begin Source File

SOURCE=.\TipDlg.h
# End Source File
# Begin Source File

SOURCE=.\TransDlg.h
# End Source File
# Begin Source File

SOURCE=.\Translate.h
# End Source File
# Begin Source File

SOURCE=.\Triangle.h
# End Source File
# Begin Source File

SOURCE=.\tritest.h
# End Source File
# Begin Source File

SOURCE=.\TVector.h
# End Source File
# Begin Source File

SOURCE=.\TxtED.h
# End Source File
# Begin Source File

SOURCE=.\Unclick.h
# End Source File
# Begin Source File

SOURCE=.\Undo.h
# End Source File
# Begin Source File

SOURCE=.\CVector.h
# End Source File
# Begin Source File

SOURCE=.\Vectorm.h
# End Source File
# Begin Source File

SOURCE=.\Vectorp.h
# End Source File
# Begin Source File

SOURCE=.\Vectorv.h
# End Source File
# Begin Source File

SOURCE=.\Verb.h
# End Source File
# Begin Source File

SOURCE=.\Vertex.h
# End Source File
# Begin Source File

SOURCE=.\Zoombar.h
# End Source File
# Begin Source File

SOURCE=.\ZoomD.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\about.bmp
# End Source File
# Begin Source File

SOURCE=.\res\about1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Acrobat38.ico
# End Source File
# Begin Source File

SOURCE=.\res\andcad2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\andycad.bmp
# End Source File
# Begin Source File

SOURCE=.\res\andycads.bmp
# End Source File
# Begin Source File

SOURCE=.\Application.rgs
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap10.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap11.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap31.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap9.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_b.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmapat.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00005.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00006.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00007.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00008.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00009.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00010.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00011.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00012.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00013.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00014.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00015.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00016.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00017.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00018.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00019.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00020.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00021.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00022.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp005.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BSmile1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BtnSel.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BtnUSel.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cad.ico
# End Source File
# Begin Source File

SOURCE=.\res\cad.rc2
# End Source File
# Begin Source File

SOURCE=.\Cad.rgs
# End Source File
# Begin Source File

SOURCE=.\res\cad1.bin
# End Source File
# Begin Source File

SOURCE=.\res\cadd.ico
# End Source File
# Begin Source File

SOURCE=.\res\cadDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\camera.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CCHSB.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cer.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cur00001.cur
# End Source File
# Begin Source File

SOURCE=.\res\cur00002.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\dimensio.bmp
# End Source File
# Begin Source File

SOURCE=.\res\edit.bmp
# End Source File
# Begin Source File

SOURCE=.\res\edit1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\flowrpot1.ico
# End Source File
# Begin Source File

SOURCE=.\res\fonts.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hg1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hg3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hg4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00004.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00005.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00006.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00007.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon3.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon4.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon5.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon6.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon7.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_cadt.ico
# End Source File
# Begin Source File

SOURCE=.\res\laydi.bmp
# End Source File
# Begin Source File

SOURCE=.\res\laytoo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\libim.bmp
# End Source File
# Begin Source File

SOURCE=.\res\linestyl.bmp
# End Source File
# Begin Source File

SOURCE=.\res\litebulb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mainfram.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mirror_t.bmp
# End Source File
# Begin Source File

SOURCE=.\res\others.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rulerbl.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rulerblm.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rulerupm.bmp
# End Source File
# Begin Source File

SOURCE=.\res\slopeang.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Smile1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Smile2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Smile3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Smile4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\snapopti.bmp
# End Source File
# Begin Source File

SOURCE=.\res\snapping.bmp
# End Source File
# Begin Source File

SOURCE=.\res\splash.bmp
# End Source File
# Begin Source File

SOURCE=.\Splsh16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\surface.bmp
# End Source File
# Begin Source File

SOURCE=.\res\surface0.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar2.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\toolbar3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tran.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tubile1.ico
# End Source File
# Begin Source File

SOURCE=.\res\weed.ico
# End Source File
# Begin Source File

SOURCE=.\res\zi.ico
# End Source File
# Begin Source File

SOURCE=.\res\zoomb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\zoombar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\zoombars.bmp
# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter "cnt;rtf"
# Begin Source File

SOURCE=.\hlp\AfxCore.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\AfxPrint.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\AppExit.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Bullet.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\cad.cnt

!IF  "$(CFG)" == "cad - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Copying contents file...
OutDir=.\Release
InputPath=.\hlp\cad.cnt
InputName=cad

"$(OutDir)\$(InputName).cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "hlp\$(InputName).cnt" $(OutDir)

# End Custom Build

!ELSEIF  "$(CFG)" == "cad - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Copying contents file...
OutDir=.\Debug
InputPath=.\hlp\cad.cnt
InputName=cad

"$(OutDir)\$(InputName).cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "hlp\$(InputName).cnt" $(OutDir)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\CurArw2.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurArw4.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurHelp.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditCopy.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditCut.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditPast.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditUndo.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileNew.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileOpen.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FilePrnt.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileSave.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\HlpSBar.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\HlpTBar.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecFirst.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecLast.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecNext.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecPrev.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Scmax.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\ScMenu.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Scmin.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\cad.clw
# End Source File
# Begin Source File

SOURCE=.\cad.reg
# End Source File
# Begin Source File

SOURCE=.\res\html1.htm
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section cad : {8BD21D30-EC42-11CE-9E0D-00AA006002F3}
# 	2:21:DefaultSinkHeaderFile:mdccombo.h
# 	2:16:DefaultSinkClass:CMdcCombo
# End Section
# Section cad : {00000000-0000-0000-0000-000000000000}
# 	1:8:IDR_CAD1:223
# End Section
# Section cad : {8BD21D33-EC42-11CE-9E0D-00AA006002F3}
# 	2:5:Class:CMdcCombo
# 	2:10:HeaderFile:mdccombo.h
# 	2:8:ImplFile:mdccombo.cpp
# End Section
# Section cad : {72ADFD54-2C39-11D0-9903-00A0C91BC942}
# 	1:17:CG_IDS_DIDYOUKNOW:112
# 	1:22:CG_IDS_TIPOFTHEDAYMENU:111
# 	1:18:CG_IDS_TIPOFTHEDAY:110
# 	1:22:CG_IDS_TIPOFTHEDAYHELP:127
# 	1:19:CG_IDP_FILE_CORRUPT:114
# 	1:7:IDD_TIP:109
# 	1:13:IDB_LIGHTBULB:107
# 	1:18:CG_IDS_FILE_ABSENT:113
# 	2:17:CG_IDS_DIDYOUKNOW:CG_IDS_DIDYOUKNOW
# 	2:7:CTipDlg:CTipDlg
# 	2:22:CG_IDS_TIPOFTHEDAYMENU:CG_IDS_TIPOFTHEDAYMENU
# 	2:18:CG_IDS_TIPOFTHEDAY:CG_IDS_TIPOFTHEDAY
# 	2:12:CTIP_Written:OK
# 	2:22:CG_IDS_TIPOFTHEDAYHELP:CG_IDS_TIPOFTHEDAYHELP
# 	2:2:BH:
# 	2:19:CG_IDP_FILE_CORRUPT:CG_IDP_FILE_CORRUPT
# 	2:7:IDD_TIP:IDD_TIP
# 	2:8:TipDlg.h:TipDlg.h
# 	2:13:IDB_LIGHTBULB:IDB_LIGHTBULB
# 	2:18:CG_IDS_FILE_ABSENT:CG_IDS_FILE_ABSENT
# 	2:10:TipDlg.cpp:TipDlg.cpp
# End Section
# Section cad : {72ADFD7B-2C39-11D0-9903-00A0C91BC942}
# 	1:17:ID_INDICATOR_TIME:161
# 	1:17:ID_INDICATOR_DATE:129
# 	2:2:BH:
# 	2:17:ID_INDICATOR_TIME:ID_INDICATOR_TIME
# 	2:17:ID_INDICATOR_DATE:ID_INDICATOR_DATE
# End Section
# Section cad : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font.h
# 	2:8:ImplFile:font.cpp
# End Section
# Section cad : {F90F1265-FDCB-4C27-A722-0B08D6C84E3D}
# 	1:13:IDD_REGDIALOG:212
# 	2:16:Resource Include:resource.h
# 	2:11:RegDialog.h:RegDialog.h
# 	2:10:ENUM: enum:enum
# 	2:19:Application Include:cad.h
# 	2:13:IDD_REGDIALOG:IDD_REGDIALOG
# 	2:17:CLASS: CRegDialog:CRegDialog
# 	2:13:RegDialog.cpp:RegDialog.cpp
# End Section
# Section cad : {72ADFD78-2C39-11D0-9903-00A0C91BC942}
# 	1:10:IDB_SPLASH:102
# 	2:21:SplashScreenInsertKey:4.0
# End Section
# Section cad : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture.h
# 	2:8:ImplFile:picture.cpp
# End Section
# Section cad : {72ADFD5E-2C39-11D0-9903-00A0C91BC942}
# 	2:12:InitInstance:MAPI Support Added
# 	2:7:CCadDoc:MAPI Support Added
# End Section
# Section cad : {72ADFD7E-2C39-11D0-9903-00A0C91BC942}
# 	1:17:CG_IDS_DISK_SPACE:188
# 	1:19:CG_IDS_PHYSICAL_MEM:187
# 	1:25:CG_IDS_DISK_SPACE_UNAVAIL:189
# 	2:14:PhysicalMemory:CG_IDS_PHYSICAL_MEM
# 	2:9:DiskSpace:CG_IDS_DISK_SPACE
# 	2:16:SpaceUnavailable:CG_IDS_DISK_SPACE_UNAVAIL
# 	2:7:NewFunc:1
# 	2:10:SysInfoKey:1234
# End Section
