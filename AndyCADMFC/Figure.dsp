# Microsoft Developer Studio Project File - Name="Figure" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=Figure - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Figure.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Figure.mak" CFG="Figure - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Figure - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "Figure - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Figure - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "Figure - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Figure - Win32 Release"
# Name "Figure - Win32 Debug"
# Begin Source File

SOURCE=.\AABB.cpp
# End Source File
# Begin Source File

SOURCE=.\AABB.h
# End Source File
# Begin Source File

SOURCE=.\AddinManager.cpp
# End Source File
# Begin Source File

SOURCE=.\AddinManager.h
# End Source File
# Begin Source File

SOURCE=.\AddinManager1.cpp
# End Source File
# Begin Source File

SOURCE=.\AddinManager1.h
# End Source File
# Begin Source File

SOURCE=.\AddinSettingsDialog1.cpp
# End Source File
# Begin Source File

SOURCE=.\AddinSettingsDialog1.h
# End Source File
# Begin Source File

SOURCE=.\AndyCad.cpp
# End Source File
# Begin Source File

SOURCE=.\AndyCad.h
# End Source File
# Begin Source File

SOURCE=.\AndyCadAddin.cpp
# End Source File
# Begin Source File

SOURCE=.\AndyCadAddin.h
# End Source File
# Begin Source File

SOURCE=.\Application.cpp
# End Source File
# Begin Source File

SOURCE=.\Application.h
# End Source File
# Begin Source File

SOURCE=.\arcprop.cpp
# End Source File
# Begin Source File

SOURCE=.\arcprop.h
# End Source File
# Begin Source File

SOURCE=.\ArrayAngle.cpp
# End Source File
# Begin Source File

SOURCE=.\ArrayAngle.h
# End Source File
# Begin Source File

SOURCE=.\barrowc.cpp
# End Source File
# Begin Source File

SOURCE=.\barrowc.h
# End Source File
# Begin Source File

SOURCE=.\BArrowP.cpp
# End Source File
# Begin Source File

SOURCE=.\BArrowP.h
# End Source File
# Begin Source File

SOURCE=.\Bezier.cpp
# End Source File
# Begin Source File

SOURCE=.\Bezier.h
# End Source File
# Begin Source File

SOURCE=.\Bezier1.cpp
# End Source File
# Begin Source File

SOURCE=.\cad.cpp
# End Source File
# Begin Source File

SOURCE=.\cad.h
# End Source File
# Begin Source File

SOURCE=.\res\cad.ico
# End Source File
# Begin Source File

SOURCE=.\cad.rc
# End Source File
# Begin Source File

SOURCE=.\CadAddIn.h
# End Source File
# Begin Source File

SOURCE=.\CadAddIn_i.c
# End Source File
# Begin Source File

SOURCE=.\CadAddIn_p.c
# End Source File
# Begin Source File

SOURCE=.\CadAddInCP.h
# End Source File
# Begin Source File

SOURCE=.\CadAutoCamera.cpp
# End Source File
# Begin Source File

SOURCE=.\CadAutoCamera.h
# End Source File
# Begin Source File

SOURCE=.\CadAutoCanvas.cpp
# End Source File
# Begin Source File

SOURCE=.\CadAutoCanvas.h
# End Source File
# Begin Source File

SOURCE=.\CadAutoCollection.cpp
# End Source File
# Begin Source File

SOURCE=.\CadAutoCollection.h
# End Source File
# Begin Source File

SOURCE=.\CadAutoDrawing.cpp
# End Source File
# Begin Source File

SOURCE=.\CadAutoDrawing.h
# End Source File
# Begin Source File

SOURCE=.\CadAutoDrawingCollection.cpp
# End Source File
# Begin Source File

SOURCE=.\CadAutoDrawingCollection.h
# End Source File
# Begin Source File

SOURCE=.\CadAutoEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\CadAutoEdit.h
# End Source File
# Begin Source File

SOURCE=.\CAdAutoShape.cpp
# End Source File
# Begin Source File

SOURCE=.\CAdAutoShape.h
# End Source File
# Begin Source File

SOURCE=.\CadAutoSurface.cpp
# End Source File
# Begin Source File

SOURCE=.\CadAutoSurface.h
# End Source File
# Begin Source File

SOURCE=.\CadAutoTransform.cpp
# End Source File
# Begin Source File

SOURCE=.\CadAutoTransform.h
# End Source File
# Begin Source File

SOURCE=.\CadAutoUtils.cpp
# End Source File
# Begin Source File

SOURCE=.\CadAutoUtils.h
# End Source File
# Begin Source File

SOURCE=.\CadAutoVector.cpp
# End Source File
# Begin Source File

SOURCE=.\CadAutoVector.h
# End Source File
# Begin Source File

SOURCE=.\CadAutoWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\CadAutoWnd.h
# End Source File
# Begin Source File

SOURCE=.\res\cadd.ico
# End Source File
# Begin Source File

SOURCE=.\cadDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\cadDoc.h
# End Source File
# Begin Source File

SOURCE=.\res\cadDoc.ico
# End Source File
# Begin Source File

SOURCE=.\cadView.cpp
# End Source File
# Begin Source File

SOURCE=.\cadView.h
# End Source File
# Begin Source File

SOURCE=.\CAM.cpp
# End Source File
# Begin Source File

SOURCE=.\CAM.h
# End Source File
# Begin Source File

SOURCE=.\CameraDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CameraDlg.h
# End Source File
# Begin Source File

SOURCE=.\Cercle.cpp
# End Source File
# Begin Source File

SOURCE=.\Cercle.h
# End Source File
# Begin Source File

SOURCE=.\chamfd.cpp
# End Source File
# Begin Source File

SOURCE=.\chamfd.h
# End Source File
# Begin Source File

SOURCE=.\Chamfer.cpp
# End Source File
# Begin Source File

SOURCE=.\Chamfer.h
# End Source File
# Begin Source File

SOURCE=.\chfi.cpp
# End Source File
# Begin Source File

SOURCE=.\chfi.h
# End Source File
# Begin Source File

SOURCE=.\childfrm.h
# End Source File
# Begin Source File

SOURCE=.\Click.cpp
# End Source File
# Begin Source File

SOURCE=.\Click.h
# End Source File
# Begin Source File

SOURCE=.\clinesty.cpp
# End Source File
# Begin Source File

SOURCE=.\clinesty.h
# End Source File
# Begin Source File

SOURCE=.\cmemdc.h
# End Source File
# Begin Source File

SOURCE=.\cmemdoc.h
# End Source File
# Begin Source File

SOURCE=.\cmoveandrotatebar.cpp
# End Source File
# Begin Source File

SOURCE=.\cmoveandrotatebar.h
# End Source File
# Begin Source File

SOURCE=.\Colord.cpp
# End Source File
# Begin Source File

SOURCE=.\Colord.h
# End Source File
# Begin Source File

SOURCE=.\Command.cpp
# End Source File
# Begin Source File

SOURCE=.\Command.h
# End Source File
# Begin Source File

SOURCE=".\Copie (3) de Textcad.cpp"
# End Source File
# Begin Source File

SOURCE=".\Copie (3) de Textcad.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of AABB.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of AddinManager.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of AddinManager1.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of AddinSettingsDialog1.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of AndyCad.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of AndyCadAddin.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of Application.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of arcprop.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of ArrayAngle.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of barrowc.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of BArrowP.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of Bezier.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of cad.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of CadAddIn.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of CadAddInCP.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of CadAutoCamera.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of CadAutoCanvas.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of CadAutoCollection.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of CadAutoDrawing.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of CadAutoDrawingCollection.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of CadAutoEdit.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of CAdAutoShape.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of CadAutoSurface.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of CadAutoTransform.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of CadAutoUtils.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of CadAutoVector.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of CadAutoWnd.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of cadDoc.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of cadView.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of CAM.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of CameraDlg.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of Cercle.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of chamfd.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of Chamfer.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of chfi.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of childfrm.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of Click.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of clinesty.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of cmemdc.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of cmemdoc.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of cmoveandrotatebar.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of Colord.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of Command.h"
# End Source File
# Begin Source File

SOURCE=".\Copy of Copie (2) de Textcad.h"
# End Source File
# Begin Source File

SOURCE=.\cpapersize.cpp
# End Source File
# Begin Source File

SOURCE=.\cpapersize.h
# End Source File
# Begin Source File

SOURCE=.\CTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\CTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\res\cur00002.cur
# End Source File
# Begin Source File

SOURCE=.\customsheet.cpp
# End Source File
# Begin Source File

SOURCE=.\customsheet.h
# End Source File
# Begin Source File

SOURCE=.\customwidth.cpp
# End Source File
# Begin Source File

SOURCE=.\customwidth.h
# End Source File
# Begin Source File

SOURCE=.\CVector.cpp
# End Source File
# Begin Source File

SOURCE=.\CVector.h
# End Source File
# Begin Source File

SOURCE=.\dim.cpp
# End Source File
# Begin Source File

SOURCE=.\dim.h
# End Source File
# Begin Source File

SOURCE=.\dima.cpp
# End Source File
# Begin Source File

SOURCE=.\dima.h
# End Source File
# Begin Source File

SOURCE=.\diml.cpp
# End Source File
# Begin Source File

SOURCE=.\diml.h
# End Source File
# Begin Source File

SOURCE=.\DlgCap.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCap.h
# End Source File
# Begin Source File

SOURCE=.\dlldata.c
# End Source File
# Begin Source File

SOURCE=.\dot.cpp
# End Source File
# Begin Source File

SOURCE=.\dot.h
# End Source File
# Begin Source File

SOURCE=.\Draw.cpp
# End Source File
# Begin Source File

SOURCE=.\Draw.h
# End Source File
# Begin Source File

SOURCE=.\Draw1.cpp
# End Source File
# Begin Source File

SOURCE=.\drawwnd.cpp
# End Source File
# Begin Source File

SOURCE=.\drawwnd.h
# End Source File
# Begin Source File

SOURCE=.\Edge.cpp
# End Source File
# Begin Source File

SOURCE=.\Edge.h
# End Source File
# Begin Source File

SOURCE=.\EditMacroDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EditMacroDlg.h
# End Source File
# Begin Source File

SOURCE=.\EditParse.cpp
# End Source File
# Begin Source File

SOURCE=.\EditParse.h
# End Source File
# Begin Source File

SOURCE=.\Face.cpp
# End Source File
# Begin Source File

SOURCE=.\Face.h
# End Source File
# Begin Source File

SOURCE=.\FFD.cpp
# End Source File
# Begin Source File

SOURCE=.\FFD.h
# End Source File
# Begin Source File

SOURCE=.\Figure.cpp
# End Source File
# Begin Source File

SOURCE=.\Figure.h
# End Source File
# Begin Source File

SOURCE=.\Figure10.cpp
# End Source File
# Begin Source File

SOURCE=.\Figureback.h
# End Source File
# Begin Source File

SOURCE=.\FileMacroDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FileMacroDlg.h
# End Source File
# Begin Source File

SOURCE=.\FilenameEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\FilenameEdit.h
# End Source File
# Begin Source File

SOURCE=.\geometry.cpp
# End Source File
# Begin Source File

SOURCE=.\geometry.h
# End Source File
# Begin Source File

SOURCE=.\gridpag.cpp
# End Source File
# Begin Source File

SOURCE=.\gridpag.h
# End Source File
# Begin Source File

SOURCE=.\gridpage.cpp
# End Source File
# Begin Source File

SOURCE=.\gridpage.h
# End Source File
# Begin Source File

SOURCE=.\res\ico00006.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon4.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon5.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_cadt.ico
# End Source File
# Begin Source File

SOURCE=.\image.cpp
# End Source File
# Begin Source File

SOURCE=.\image.h
# End Source File
# Begin Source File

SOURCE=.\Imagex.cpp
# End Source File
# Begin Source File

SOURCE=.\Imagex.h
# End Source File
# Begin Source File

SOURCE=.\Infobar.cpp
# End Source File
# Begin Source File

SOURCE=.\infobar.h
# End Source File
# Begin Source File

SOURCE=.\inplaceframe.cpp
# End Source File
# Begin Source File

SOURCE=.\inplaceframe.h
# End Source File
# Begin Source File

SOURCE=.\inter.cpp
# End Source File
# Begin Source File

SOURCE=.\inter.h
# End Source File
# Begin Source File

SOURCE=.\laybar.cpp
# End Source File
# Begin Source File

SOURCE=.\laybar.h
# End Source File
# Begin Source File

SOURCE=.\Layerad.cpp
# End Source File
# Begin Source File

SOURCE=.\Layerad.h
# End Source File
# Begin Source File

SOURCE=.\LayerD.cpp
# End Source File
# Begin Source File

SOURCE=.\LayerD.h
# End Source File
# Begin Source File

SOURCE=.\laylist.cpp
# End Source File
# Begin Source File

SOURCE=.\laylist.h
# End Source File
# Begin Source File

SOURCE=.\lcombobox.cpp
# End Source File
# Begin Source File

SOURCE=.\lcombobox.h
# End Source File
# Begin Source File

SOURCE=.\libdialog.cpp
# End Source File
# Begin Source File

SOURCE=.\libdialog.h
# End Source File
# Begin Source File

SOURCE=.\Libs.cpp
# End Source File
# Begin Source File

SOURCE=.\Libs.h
# End Source File
# Begin Source File

SOURCE=.\LightD.cpp
# End Source File
# Begin Source File

SOURCE=.\LightD.h
# End Source File
# Begin Source File

SOURCE=.\Line.cpp
# End Source File
# Begin Source File

SOURCE=.\line.h
# End Source File
# Begin Source File

SOURCE=.\lineagain.cpp
# End Source File
# Begin Source File

SOURCE=.\lineagain.h
# End Source File
# Begin Source File

SOURCE=.\linebar.cpp
# End Source File
# Begin Source File

SOURCE=.\linebar.h
# End Source File
# Begin Source File

SOURCE=.\linestyle.cpp
# End Source File
# Begin Source File

SOURCE=.\linestyle.h
# End Source File
# Begin Source File

SOURCE=.\MacroManager.cpp
# End Source File
# Begin Source File

SOURCE=.\MacroManager.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\matrix.cpp
# End Source File
# Begin Source File

SOURCE=.\matrix.h
# End Source File
# Begin Source File

SOURCE=.\matrix1.cpp
# End Source File
# Begin Source File

SOURCE=.\matrix1.h
# End Source File
# Begin Source File

SOURCE=.\MClick.cpp
# End Source File
# Begin Source File

SOURCE=.\MClick.h
# End Source File
# Begin Source File

SOURCE=.\memdc.h
# End Source File
# Begin Source File

SOURCE=.\Memento.cpp
# End Source File
# Begin Source File

SOURCE=.\Memento.h
# End Source File
# Begin Source File

SOURCE=.\Mesh.cpp
# End Source File
# Begin Source File

SOURCE=.\Mesh.h
# End Source File
# Begin Source File

SOURCE=.\mlinestyle.cpp
# End Source File
# Begin Source File

SOURCE=.\mlinestyle.h
# End Source File
# Begin Source File

SOURCE=.\mouse.cpp
# End Source File
# Begin Source File

SOURCE=.\mouse.h
# End Source File
# Begin Source File

SOURCE=.\msxml.tlh
# End Source File
# Begin Source File

SOURCE=.\MultVar.cpp
# End Source File
# Begin Source File

SOURCE=.\MultVar.h
# End Source File
# Begin Source File

SOURCE=.\NewMacroDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\NewMacroDlg.h
# End Source File
# Begin Source File

SOURCE=.\newtext.cpp
# End Source File
# Begin Source File

SOURCE=.\newtext.h
# End Source File
# Begin Source File

SOURCE=.\nstatusbar.cpp
# End Source File
# Begin Source File

SOURCE=.\nstatusbar.h
# End Source File
# Begin Source File

SOURCE=.\numcopy.cpp
# End Source File
# Begin Source File

SOURCE=.\numcopy.h
# End Source File
# Begin Source File

SOURCE=.\OBJEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\OBJEdit.h
# End Source File
# Begin Source File

SOURCE=.\Observer.cpp
# End Source File
# Begin Source File

SOURCE=.\Observer.h
# End Source File
# Begin Source File

SOURCE=.\operation.cpp
# End Source File
# Begin Source File

SOURCE=.\operation.h
# End Source File
# Begin Source File

SOURCE=.\optionsheet.cpp
# End Source File
# Begin Source File

SOURCE=.\optionsheet.h
# End Source File
# Begin Source File

SOURCE=.\owncombo.cpp
# End Source File
# Begin Source File

SOURCE=.\owncombo.h
# End Source File
# Begin Source File

SOURCE=.\OwnCombo1.cpp
# End Source File
# Begin Source File

SOURCE=.\OwnCombo1.h
# End Source File
# Begin Source File

SOURCE=.\ownlist.cpp
# End Source File
# Begin Source File

SOURCE=.\ownlist.h
# End Source File
# Begin Source File

SOURCE=.\paperpag.cpp
# End Source File
# Begin Source File

SOURCE=.\paperpag.h
# End Source File
# Begin Source File

SOURCE=.\paperpage.cpp
# End Source File
# Begin Source File

SOURCE=.\paperpage.h
# End Source File
# Begin Source File

SOURCE=.\ParseDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ParseDlg.h
# End Source File
# Begin Source File

SOURCE=.\Parser.cpp
# End Source File
# Begin Source File

SOURCE=.\Parser.h
# End Source File
# Begin Source File

SOURCE=.\ParserArc.cpp
# End Source File
# Begin Source File

SOURCE=.\ParserArc.h
# End Source File
# Begin Source File

SOURCE=.\ParserCircle.cpp
# End Source File
# Begin Source File

SOURCE=.\ParserCircle.h
# End Source File
# Begin Source File

SOURCE=.\ParserFloat.cpp
# End Source File
# Begin Source File

SOURCE=.\ParserFloat.h
# End Source File
# Begin Source File

SOURCE=.\ParserObject.cpp
# End Source File
# Begin Source File

SOURCE=.\ParserObject.h
# End Source File
# Begin Source File

SOURCE=.\ParserPoint.cpp
# End Source File
# Begin Source File

SOURCE=.\ParserPoint.h
# End Source File
# Begin Source File

SOURCE=.\ParserRectangle.cpp
# End Source File
# Begin Source File

SOURCE=.\ParserRectangle.h
# End Source File
# Begin Source File

SOURCE=.\ParserVar.cpp
# End Source File
# Begin Source File

SOURCE=.\ParserVar.h
# End Source File
# Begin Source File

SOURCE=.\ParserVerb.cpp
# End Source File
# Begin Source File

SOURCE=.\ParserVerb.h
# End Source File
# Begin Source File

SOURCE=.\Pattern.cpp
# End Source File
# Begin Source File

SOURCE=.\Pattern.h
# End Source File
# Begin Source File

SOURCE=.\pgrid.cpp
# End Source File
# Begin Source File

SOURCE=.\pgrid.h
# End Source File
# Begin Source File

SOURCE=.\Plane.cpp
# End Source File
# Begin Source File

SOURCE=.\Plane.h
# End Source File
# Begin Source File

SOURCE=.\popbar.cpp
# End Source File
# Begin Source File

SOURCE=.\popbar.h
# End Source File
# Begin Source File

SOURCE=.\ProgressBar.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgressBar.h
# End Source File
# Begin Source File

SOURCE=.\property.cpp
# End Source File
# Begin Source File

SOURCE=.\property.h
# End Source File
# Begin Source File

SOURCE=.\proppage.cpp
# End Source File
# Begin Source File

SOURCE=.\proppage.h
# End Source File
# Begin Source File

SOURCE=.\qline.cpp
# End Source File
# Begin Source File

SOURCE=.\qline.h
# End Source File
# Begin Source File

SOURCE=.\QuadTree.cpp
# End Source File
# Begin Source File

SOURCE=.\QuadTree.h
# End Source File
# Begin Source File

SOURCE=.\Quaternion.cpp
# End Source File
# Begin Source File

SOURCE=.\Quaternion.h
# End Source File
# Begin Source File

SOURCE=.\Ray.cpp
# End Source File
# Begin Source File

SOURCE=.\Ray.h
# End Source File
# Begin Source File

SOURCE=.\RecArray.cpp
# End Source File
# Begin Source File

SOURCE=.\RecArray.h
# End Source File
# Begin Source File

SOURCE=.\reccolor.cpp
# End Source File
# Begin Source File

SOURCE=.\reccolor.h
# End Source File
# Begin Source File

SOURCE=.\RecPattern.cpp
# End Source File
# Begin Source File

SOURCE=.\RecPattern.h
# End Source File
# Begin Source File

SOURCE=.\rectangle.cpp
# End Source File
# Begin Source File

SOURCE=.\rectangle.h
# End Source File
# Begin Source File

SOURCE=.\RegDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\RegDialog.h
# End Source File
# Begin Source File

SOURCE=.\Register.cpp
# End Source File
# Begin Source File

SOURCE=.\Register.h
# End Source File
# Begin Source File

SOURCE=.\Render.cpp
# End Source File
# Begin Source File

SOURCE=.\Render.h
# End Source File
# Begin Source File

SOURCE=.\resourc.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\RTFACTN.CPP
# End Source File
# Begin Source File

SOURCE=.\Rtfdecl.h
# End Source File
# Begin Source File

SOURCE=.\Rtfreadr.cpp
# End Source File
# Begin Source File

SOURCE=.\Rtftype.h
# End Source File
# Begin Source File

SOURCE=.\ruler.cpp
# End Source File
# Begin Source File

SOURCE=.\ruler.h
# End Source File
# Begin Source File

SOURCE=.\ruler1.cpp
# End Source File
# Begin Source File

SOURCE=.\ruler1.h
# End Source File
# Begin Source File

SOURCE=.\RunMacroDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RunMacroDlg.h
# End Source File
# Begin Source File

SOURCE=.\ScriptObject.tlh
# End Source File
# Begin Source File

SOURCE=.\ScriptObject.tli
# End Source File
# Begin Source File

SOURCE=.\SmoothD.cpp
# End Source File
# Begin Source File

SOURCE=.\SmoothD.h
# End Source File
# Begin Source File

SOURCE=.\Snap.cpp
# End Source File
# Begin Source File

SOURCE=.\Snap.h
# End Source File
# Begin Source File

SOURCE=.\splash.cpp
# End Source File
# Begin Source File

SOURCE=.\splash.h
# End Source File
# Begin Source File

SOURCE=.\Spline.cpp
# End Source File
# Begin Source File

SOURCE=.\Spline.h
# End Source File
# Begin Source File

SOURCE=.\State.cpp
# End Source File
# Begin Source File

SOURCE=.\State.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Subject.cpp
# End Source File
# Begin Source File

SOURCE=.\Subject.h
# End Source File
# Begin Source File

SOURCE=.\subwnd.cpp
# End Source File
# Begin Source File

SOURCE=.\subwnd.h
# End Source File
# Begin Source File

SOURCE=.\TabOption.cpp
# End Source File
# Begin Source File

SOURCE=.\TabOption.h
# End Source File
# Begin Source File

SOURCE=.\Tangle.cpp
# End Source File
# Begin Source File

SOURCE=.\Tangle.h
# End Source File
# Begin Source File

SOURCE=.\text.cpp
# End Source File
# Begin Source File

SOURCE=.\text.h
# End Source File
# Begin Source File

SOURCE=.\text1.cpp
# End Source File
# Begin Source File

SOURCE=.\text1.h
# End Source File
# Begin Source File

SOURCE=.\Textcad.cpp
# End Source File
# Begin Source File

SOURCE=.\Textcad.h
# End Source File
# Begin Source File

SOURCE=.\Textcad1.cpp
# End Source File
# Begin Source File

SOURCE=.\Textcad1.h
# End Source File
# Begin Source File

SOURCE=.\Textcad_2.cpp
# End Source File
# Begin Source File

SOURCE=.\Textcad_2.h
# End Source File
# Begin Source File

SOURCE=.\textd.cpp
# End Source File
# Begin Source File

SOURCE=.\textd.h
# End Source File
# Begin Source File

SOURCE=.\TextDi.cpp
# End Source File
# Begin Source File

SOURCE=.\TextDi.h
# End Source File
# Begin Source File

SOURCE=.\texts.cpp
# End Source File
# Begin Source File

SOURCE=.\texts.h
# End Source File
# Begin Source File

SOURCE=.\ThickD.cpp
# End Source File
# Begin Source File

SOURCE=.\ThickD.h
# End Source File
# Begin Source File

SOURCE=.\tipdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\tipdlg.h
# End Source File
# Begin Source File

SOURCE=.\toolbarw.cpp
# End Source File
# Begin Source File

SOURCE=.\toolbarw.h
# End Source File
# Begin Source File

SOURCE=.\toolbarx.cpp
# End Source File
# Begin Source File

SOURCE=.\toolbarx.h
# End Source File
# Begin Source File

SOURCE=.\TransDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TransDlg.h
# End Source File
# Begin Source File

SOURCE=.\translate.cpp
# End Source File
# Begin Source File

SOURCE=.\translate.h
# End Source File
# Begin Source File

SOURCE=.\Triangle.cpp
# End Source File
# Begin Source File

SOURCE=.\Triangle.h
# End Source File
# Begin Source File

SOURCE=.\TRIM.cpp
# End Source File
# Begin Source File

SOURCE=.\TRIM.h
# End Source File
# Begin Source File

SOURCE=.\tritest.h
# End Source File
# Begin Source File

SOURCE=.\tvector.cpp
# End Source File
# Begin Source File

SOURCE=.\tvector.h
# End Source File
# Begin Source File

SOURCE=.\txted.cpp
# End Source File
# Begin Source File

SOURCE=.\txted.h
# End Source File
# Begin Source File

SOURCE=.\Unclick.cpp
# End Source File
# Begin Source File

SOURCE=.\Unclick.h
# End Source File
# Begin Source File

SOURCE=.\vector.cpp
# End Source File
# Begin Source File

SOURCE=.\CVector.h
# End Source File
# Begin Source File

SOURCE=.\Vectorm.cpp
# End Source File
# Begin Source File

SOURCE=.\Vectorm.h
# End Source File
# Begin Source File

SOURCE=.\vectorp.cpp
# End Source File
# Begin Source File

SOURCE=.\vectorp.h
# End Source File
# Begin Source File

SOURCE=.\vectorv.cpp
# End Source File
# Begin Source File

SOURCE=.\vectorv.h
# End Source File
# Begin Source File

SOURCE=.\Verb.cpp
# End Source File
# Begin Source File

SOURCE=.\Verb.h
# End Source File
# Begin Source File

SOURCE=.\Vertex.cpp
# End Source File
# Begin Source File

SOURCE=.\Vertex.h
# End Source File
# Begin Source File

SOURCE=.\zoombar.cpp
# End Source File
# Begin Source File

SOURCE=.\zoombar.h
# End Source File
# Begin Source File

SOURCE=.\zoomd.cpp
# End Source File
# Begin Source File

SOURCE=.\zoomd.h
# End Source File
# End Target
# End Project
