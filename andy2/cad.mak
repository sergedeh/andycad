# Microsoft Developer Studio Generated NMAKE File, Based on cad.dsp
!IF "$(CFG)" == ""
CFG=cad - Win32 Debug
!MESSAGE No configuration specified. Defaulting to cad - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "cad - Win32 Release" && "$(CFG)" != "cad - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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

!IF  "$(CFG)" == "cad - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : ".\Release\cad.hlp" ".\Release\cad.cnt" "$(OUTDIR)\cad.exe" "$(OUTDIR)\cad.tlb" "$(OUTDIR)\cad.bsc" "$(OUTDIR)\CadAddIn.tlb"


CLEAN :
	-@erase "$(INTDIR)\AABB.obj"
	-@erase "$(INTDIR)\AABB.sbr"
	-@erase "$(INTDIR)\AddinManager1.obj"
	-@erase "$(INTDIR)\AddinManager1.sbr"
	-@erase "$(INTDIR)\AddinSettingsDialog1.obj"
	-@erase "$(INTDIR)\AddinSettingsDialog1.sbr"
	-@erase "$(INTDIR)\AndyCad.obj"
	-@erase "$(INTDIR)\AndyCad.sbr"
	-@erase "$(INTDIR)\AndyCadAddin.obj"
	-@erase "$(INTDIR)\AndyCadAddin.sbr"
	-@erase "$(INTDIR)\ArrayAngle.obj"
	-@erase "$(INTDIR)\ArrayAngle.sbr"
	-@erase "$(INTDIR)\BArrowC.obj"
	-@erase "$(INTDIR)\BArrowC.sbr"
	-@erase "$(INTDIR)\BArrowP.obj"
	-@erase "$(INTDIR)\BArrowP.sbr"
	-@erase "$(INTDIR)\Bezier.obj"
	-@erase "$(INTDIR)\Bezier.sbr"
	-@erase "$(INTDIR)\cad.obj"
	-@erase "$(INTDIR)\cad.pch"
	-@erase "$(INTDIR)\cad.res"
	-@erase "$(INTDIR)\cad.sbr"
	-@erase "$(INTDIR)\cad.tlb"
	-@erase "$(INTDIR)\CadAddIn.tlb"
	-@erase "$(INTDIR)\CadAutoCamera.obj"
	-@erase "$(INTDIR)\CadAutoCamera.sbr"
	-@erase "$(INTDIR)\CadAutoCanvas.obj"
	-@erase "$(INTDIR)\CadAutoCanvas.sbr"
	-@erase "$(INTDIR)\CadAutoCollection.obj"
	-@erase "$(INTDIR)\CadAutoCollection.sbr"
	-@erase "$(INTDIR)\CadAutoDrawing.obj"
	-@erase "$(INTDIR)\CadAutoDrawing.sbr"
	-@erase "$(INTDIR)\CadAutoDrawingCollection.obj"
	-@erase "$(INTDIR)\CadAutoDrawingCollection.sbr"
	-@erase "$(INTDIR)\CadAutoEdit.obj"
	-@erase "$(INTDIR)\CadAutoEdit.sbr"
	-@erase "$(INTDIR)\CAdAutoShape.obj"
	-@erase "$(INTDIR)\CAdAutoShape.sbr"
	-@erase "$(INTDIR)\CadAutoSurface.obj"
	-@erase "$(INTDIR)\CadAutoSurface.sbr"
	-@erase "$(INTDIR)\CadAutoTransform.obj"
	-@erase "$(INTDIR)\CadAutoTransform.sbr"
	-@erase "$(INTDIR)\CadAutoUtils.obj"
	-@erase "$(INTDIR)\CadAutoUtils.sbr"
	-@erase "$(INTDIR)\CadAutoVector.obj"
	-@erase "$(INTDIR)\CadAutoVector.sbr"
	-@erase "$(INTDIR)\CadAutoWnd.obj"
	-@erase "$(INTDIR)\CadAutoWnd.sbr"
	-@erase "$(INTDIR)\cadDoc.obj"
	-@erase "$(INTDIR)\cadDoc.sbr"
	-@erase "$(INTDIR)\cadView.obj"
	-@erase "$(INTDIR)\cadView.sbr"
	-@erase "$(INTDIR)\CAM.obj"
	-@erase "$(INTDIR)\CAM.sbr"
	-@erase "$(INTDIR)\CameraDlg.obj"
	-@erase "$(INTDIR)\CameraDlg.sbr"
	-@erase "$(INTDIR)\Cercle.obj"
	-@erase "$(INTDIR)\Cercle.sbr"
	-@erase "$(INTDIR)\ChamfD.obj"
	-@erase "$(INTDIR)\ChamfD.sbr"
	-@erase "$(INTDIR)\Chamfer.obj"
	-@erase "$(INTDIR)\Chamfer.sbr"
	-@erase "$(INTDIR)\ChFi.obj"
	-@erase "$(INTDIR)\ChFi.sbr"
	-@erase "$(INTDIR)\Click.obj"
	-@erase "$(INTDIR)\Click.sbr"
	-@erase "$(INTDIR)\CLineSty.obj"
	-@erase "$(INTDIR)\CLineSty.sbr"
	-@erase "$(INTDIR)\ColorD.obj"
	-@erase "$(INTDIR)\ColorD.sbr"
	-@erase "$(INTDIR)\Command.obj"
	-@erase "$(INTDIR)\Command.sbr"
	-@erase "$(INTDIR)\CPaperSize.obj"
	-@erase "$(INTDIR)\CPaperSize.sbr"
	-@erase "$(INTDIR)\CTreeCtrl.obj"
	-@erase "$(INTDIR)\CTreeCtrl.sbr"
	-@erase "$(INTDIR)\CustomSheet.obj"
	-@erase "$(INTDIR)\CustomSheet.sbr"
	-@erase "$(INTDIR)\CustomWidth.obj"
	-@erase "$(INTDIR)\CustomWidth.sbr"
	-@erase "$(INTDIR)\CVector.obj"
	-@erase "$(INTDIR)\CVector.sbr"
	-@erase "$(INTDIR)\Dim.obj"
	-@erase "$(INTDIR)\Dim.sbr"
	-@erase "$(INTDIR)\DimA.obj"
	-@erase "$(INTDIR)\DimA.sbr"
	-@erase "$(INTDIR)\DimL.obj"
	-@erase "$(INTDIR)\DimL.sbr"
	-@erase "$(INTDIR)\DlgCap.obj"
	-@erase "$(INTDIR)\DlgCap.sbr"
	-@erase "$(INTDIR)\Dot.obj"
	-@erase "$(INTDIR)\Dot.sbr"
	-@erase "$(INTDIR)\Draw.obj"
	-@erase "$(INTDIR)\Draw.sbr"
	-@erase "$(INTDIR)\DrawWnd.obj"
	-@erase "$(INTDIR)\DrawWnd.sbr"
	-@erase "$(INTDIR)\Edge.obj"
	-@erase "$(INTDIR)\Edge.sbr"
	-@erase "$(INTDIR)\EditParse.obj"
	-@erase "$(INTDIR)\EditParse.sbr"
	-@erase "$(INTDIR)\Face.obj"
	-@erase "$(INTDIR)\Face.sbr"
	-@erase "$(INTDIR)\FFD.obj"
	-@erase "$(INTDIR)\FFD.sbr"
	-@erase "$(INTDIR)\Figure.obj"
	-@erase "$(INTDIR)\Figure.sbr"
	-@erase "$(INTDIR)\geometry.obj"
	-@erase "$(INTDIR)\geometry.sbr"
	-@erase "$(INTDIR)\GridPag.obj"
	-@erase "$(INTDIR)\GridPag.sbr"
	-@erase "$(INTDIR)\GridPage.obj"
	-@erase "$(INTDIR)\GridPage.sbr"
	-@erase "$(INTDIR)\Image.obj"
	-@erase "$(INTDIR)\Image.sbr"
	-@erase "$(INTDIR)\Imagex.obj"
	-@erase "$(INTDIR)\Imagex.sbr"
	-@erase "$(INTDIR)\InfoBar.obj"
	-@erase "$(INTDIR)\InfoBar.sbr"
	-@erase "$(INTDIR)\Inter.obj"
	-@erase "$(INTDIR)\Inter.sbr"
	-@erase "$(INTDIR)\LayBar.obj"
	-@erase "$(INTDIR)\LayBar.sbr"
	-@erase "$(INTDIR)\Layerad.obj"
	-@erase "$(INTDIR)\Layerad.sbr"
	-@erase "$(INTDIR)\LayerD.obj"
	-@erase "$(INTDIR)\LayerD.sbr"
	-@erase "$(INTDIR)\LayList.obj"
	-@erase "$(INTDIR)\LayList.sbr"
	-@erase "$(INTDIR)\LComboBox.obj"
	-@erase "$(INTDIR)\LComboBox.sbr"
	-@erase "$(INTDIR)\Libdialog.obj"
	-@erase "$(INTDIR)\Libdialog.sbr"
	-@erase "$(INTDIR)\LibS.obj"
	-@erase "$(INTDIR)\LibS.sbr"
	-@erase "$(INTDIR)\LightD.obj"
	-@erase "$(INTDIR)\LightD.sbr"
	-@erase "$(INTDIR)\Line.obj"
	-@erase "$(INTDIR)\Line.sbr"
	-@erase "$(INTDIR)\LineAgain.obj"
	-@erase "$(INTDIR)\LineAgain.sbr"
	-@erase "$(INTDIR)\LineBar.obj"
	-@erase "$(INTDIR)\LineBar.sbr"
	-@erase "$(INTDIR)\Linestyle.obj"
	-@erase "$(INTDIR)\Linestyle.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\Matrix1.obj"
	-@erase "$(INTDIR)\Matrix1.sbr"
	-@erase "$(INTDIR)\MClick.obj"
	-@erase "$(INTDIR)\MClick.sbr"
	-@erase "$(INTDIR)\Memento.obj"
	-@erase "$(INTDIR)\Memento.sbr"
	-@erase "$(INTDIR)\Mesh.obj"
	-@erase "$(INTDIR)\Mesh.sbr"
	-@erase "$(INTDIR)\Mouse.obj"
	-@erase "$(INTDIR)\Mouse.sbr"
	-@erase "$(INTDIR)\MultVar.obj"
	-@erase "$(INTDIR)\MultVar.sbr"
	-@erase "$(INTDIR)\NumCopy.obj"
	-@erase "$(INTDIR)\NumCopy.sbr"
	-@erase "$(INTDIR)\OBJEdit.obj"
	-@erase "$(INTDIR)\OBJEdit.sbr"
	-@erase "$(INTDIR)\Observer.obj"
	-@erase "$(INTDIR)\Observer.sbr"
	-@erase "$(INTDIR)\Operation.obj"
	-@erase "$(INTDIR)\Operation.sbr"
	-@erase "$(INTDIR)\Optionsheet.obj"
	-@erase "$(INTDIR)\Optionsheet.sbr"
	-@erase "$(INTDIR)\OwnCombo.obj"
	-@erase "$(INTDIR)\OwnCombo.sbr"
	-@erase "$(INTDIR)\OwnList.obj"
	-@erase "$(INTDIR)\OwnList.sbr"
	-@erase "$(INTDIR)\PaperPag.obj"
	-@erase "$(INTDIR)\PaperPag.sbr"
	-@erase "$(INTDIR)\PaperPage.obj"
	-@erase "$(INTDIR)\PaperPage.sbr"
	-@erase "$(INTDIR)\ParseDlg.obj"
	-@erase "$(INTDIR)\ParseDlg.sbr"
	-@erase "$(INTDIR)\Parser.obj"
	-@erase "$(INTDIR)\Parser.sbr"
	-@erase "$(INTDIR)\ParserFloat.obj"
	-@erase "$(INTDIR)\ParserFloat.sbr"
	-@erase "$(INTDIR)\ParserObject.obj"
	-@erase "$(INTDIR)\ParserObject.sbr"
	-@erase "$(INTDIR)\ParserVar.obj"
	-@erase "$(INTDIR)\ParserVar.sbr"
	-@erase "$(INTDIR)\ParserVerb.obj"
	-@erase "$(INTDIR)\ParserVerb.sbr"
	-@erase "$(INTDIR)\Pattern.obj"
	-@erase "$(INTDIR)\Pattern.sbr"
	-@erase "$(INTDIR)\PGrid.obj"
	-@erase "$(INTDIR)\PGrid.sbr"
	-@erase "$(INTDIR)\Plane.obj"
	-@erase "$(INTDIR)\Plane.sbr"
	-@erase "$(INTDIR)\PopBar.obj"
	-@erase "$(INTDIR)\PopBar.sbr"
	-@erase "$(INTDIR)\QLine.obj"
	-@erase "$(INTDIR)\QLine.sbr"
	-@erase "$(INTDIR)\QuadTree.obj"
	-@erase "$(INTDIR)\QuadTree.sbr"
	-@erase "$(INTDIR)\Quaternion.obj"
	-@erase "$(INTDIR)\Quaternion.sbr"
	-@erase "$(INTDIR)\Ray.obj"
	-@erase "$(INTDIR)\Ray.sbr"
	-@erase "$(INTDIR)\RecArray.obj"
	-@erase "$(INTDIR)\RecArray.sbr"
	-@erase "$(INTDIR)\RecColor.obj"
	-@erase "$(INTDIR)\RecColor.sbr"
	-@erase "$(INTDIR)\RecPattern.obj"
	-@erase "$(INTDIR)\RecPattern.sbr"
	-@erase "$(INTDIR)\Rectangle.obj"
	-@erase "$(INTDIR)\Rectangle.sbr"
	-@erase "$(INTDIR)\RegDialog.obj"
	-@erase "$(INTDIR)\RegDialog.sbr"
	-@erase "$(INTDIR)\Register.obj"
	-@erase "$(INTDIR)\Register.sbr"
	-@erase "$(INTDIR)\Render.obj"
	-@erase "$(INTDIR)\Render.sbr"
	-@erase "$(INTDIR)\RTFACTN.OBJ"
	-@erase "$(INTDIR)\RTFACTN.SBR"
	-@erase "$(INTDIR)\Rtfreadr.obj"
	-@erase "$(INTDIR)\Rtfreadr.sbr"
	-@erase "$(INTDIR)\Ruler1.obj"
	-@erase "$(INTDIR)\Ruler1.sbr"
	-@erase "$(INTDIR)\SmoothD.obj"
	-@erase "$(INTDIR)\SmoothD.sbr"
	-@erase "$(INTDIR)\Snap.obj"
	-@erase "$(INTDIR)\Snap.sbr"
	-@erase "$(INTDIR)\Splash.obj"
	-@erase "$(INTDIR)\Splash.sbr"
	-@erase "$(INTDIR)\Spline.obj"
	-@erase "$(INTDIR)\Spline.sbr"
	-@erase "$(INTDIR)\State.obj"
	-@erase "$(INTDIR)\State.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\Subject.obj"
	-@erase "$(INTDIR)\Subject.sbr"
	-@erase "$(INTDIR)\SubWnd.obj"
	-@erase "$(INTDIR)\SubWnd.sbr"
	-@erase "$(INTDIR)\TextCad.obj"
	-@erase "$(INTDIR)\TextCad.sbr"
	-@erase "$(INTDIR)\textd.obj"
	-@erase "$(INTDIR)\textd.sbr"
	-@erase "$(INTDIR)\TextDi.obj"
	-@erase "$(INTDIR)\TextDi.sbr"
	-@erase "$(INTDIR)\ThickD.obj"
	-@erase "$(INTDIR)\ThickD.sbr"
	-@erase "$(INTDIR)\TipDlg.obj"
	-@erase "$(INTDIR)\TipDlg.sbr"
	-@erase "$(INTDIR)\TransDlg.obj"
	-@erase "$(INTDIR)\TransDlg.sbr"
	-@erase "$(INTDIR)\Translate.obj"
	-@erase "$(INTDIR)\Translate.sbr"
	-@erase "$(INTDIR)\Triangle.obj"
	-@erase "$(INTDIR)\Triangle.sbr"
	-@erase "$(INTDIR)\TVector.obj"
	-@erase "$(INTDIR)\TVector.sbr"
	-@erase "$(INTDIR)\TxtED.obj"
	-@erase "$(INTDIR)\TxtED.sbr"
	-@erase "$(INTDIR)\Unclick.obj"
	-@erase "$(INTDIR)\Unclick.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\Vector.obj"
	-@erase "$(INTDIR)\Vector.sbr"
	-@erase "$(INTDIR)\Vectorm.obj"
	-@erase "$(INTDIR)\Vectorm.sbr"
	-@erase "$(INTDIR)\Vectorp.obj"
	-@erase "$(INTDIR)\Vectorp.sbr"
	-@erase "$(INTDIR)\Vectorv.obj"
	-@erase "$(INTDIR)\Vectorv.sbr"
	-@erase "$(INTDIR)\Verb.obj"
	-@erase "$(INTDIR)\Verb.sbr"
	-@erase "$(INTDIR)\Vertex.obj"
	-@erase "$(INTDIR)\Vertex.sbr"
	-@erase "$(INTDIR)\Zoombar.obj"
	-@erase "$(INTDIR)\Zoombar.sbr"
	-@erase "$(INTDIR)\ZoomD.obj"
	-@erase "$(INTDIR)\ZoomD.sbr"
	-@erase "$(OUTDIR)\cad.bsc"
	-@erase "$(OUTDIR)\cad.exe"
	-@erase "$(OUTDIR)\cad.pdb"
	-@erase ".\Release\cad.cnt"
	-@erase ".\Release\cad.hlp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /Zd /I "C:\Program Files\HTML Help Workshop\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\cad.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\cad.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\cad.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AABB.sbr" \
	"$(INTDIR)\AddinManager1.sbr" \
	"$(INTDIR)\AddinSettingsDialog1.sbr" \
	"$(INTDIR)\AndyCad.sbr" \
	"$(INTDIR)\AndyCadAddin.sbr" \
	"$(INTDIR)\ArrayAngle.sbr" \
	"$(INTDIR)\BArrowC.sbr" \
	"$(INTDIR)\BArrowP.sbr" \
	"$(INTDIR)\Bezier.sbr" \
	"$(INTDIR)\cad.sbr" \
	"$(INTDIR)\CadAutoCamera.sbr" \
	"$(INTDIR)\CadAutoCanvas.sbr" \
	"$(INTDIR)\CadAutoCollection.sbr" \
	"$(INTDIR)\CadAutoDrawing.sbr" \
	"$(INTDIR)\CadAutoDrawingCollection.sbr" \
	"$(INTDIR)\CadAutoEdit.sbr" \
	"$(INTDIR)\CAdAutoShape.sbr" \
	"$(INTDIR)\CadAutoSurface.sbr" \
	"$(INTDIR)\CadAutoTransform.sbr" \
	"$(INTDIR)\CadAutoUtils.sbr" \
	"$(INTDIR)\CadAutoVector.sbr" \
	"$(INTDIR)\CadAutoWnd.sbr" \
	"$(INTDIR)\cadDoc.sbr" \
	"$(INTDIR)\cadView.sbr" \
	"$(INTDIR)\CAM.sbr" \
	"$(INTDIR)\CameraDlg.sbr" \
	"$(INTDIR)\Cercle.sbr" \
	"$(INTDIR)\ChamfD.sbr" \
	"$(INTDIR)\Chamfer.sbr" \
	"$(INTDIR)\ChFi.sbr" \
	"$(INTDIR)\Click.sbr" \
	"$(INTDIR)\CLineSty.sbr" \
	"$(INTDIR)\ColorD.sbr" \
	"$(INTDIR)\Command.sbr" \
	"$(INTDIR)\CPaperSize.sbr" \
	"$(INTDIR)\CTreeCtrl.sbr" \
	"$(INTDIR)\CustomSheet.sbr" \
	"$(INTDIR)\CustomWidth.sbr" \
	"$(INTDIR)\CVector.sbr" \
	"$(INTDIR)\Dim.sbr" \
	"$(INTDIR)\DimA.sbr" \
	"$(INTDIR)\DimL.sbr" \
	"$(INTDIR)\DlgCap.sbr" \
	"$(INTDIR)\Dot.sbr" \
	"$(INTDIR)\Draw.sbr" \
	"$(INTDIR)\DrawWnd.sbr" \
	"$(INTDIR)\Edge.sbr" \
	"$(INTDIR)\EditParse.sbr" \
	"$(INTDIR)\Face.sbr" \
	"$(INTDIR)\FFD.sbr" \
	"$(INTDIR)\Figure.sbr" \
	"$(INTDIR)\geometry.sbr" \
	"$(INTDIR)\GridPag.sbr" \
	"$(INTDIR)\GridPage.sbr" \
	"$(INTDIR)\Image.sbr" \
	"$(INTDIR)\Imagex.sbr" \
	"$(INTDIR)\InfoBar.sbr" \
	"$(INTDIR)\Inter.sbr" \
	"$(INTDIR)\LayBar.sbr" \
	"$(INTDIR)\Layerad.sbr" \
	"$(INTDIR)\LayerD.sbr" \
	"$(INTDIR)\LayList.sbr" \
	"$(INTDIR)\LComboBox.sbr" \
	"$(INTDIR)\Libdialog.sbr" \
	"$(INTDIR)\LibS.sbr" \
	"$(INTDIR)\LightD.sbr" \
	"$(INTDIR)\Line.sbr" \
	"$(INTDIR)\LineAgain.sbr" \
	"$(INTDIR)\LineBar.sbr" \
	"$(INTDIR)\Linestyle.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\Matrix1.sbr" \
	"$(INTDIR)\MClick.sbr" \
	"$(INTDIR)\Memento.sbr" \
	"$(INTDIR)\Mesh.sbr" \
	"$(INTDIR)\Mouse.sbr" \
	"$(INTDIR)\MultVar.sbr" \
	"$(INTDIR)\NumCopy.sbr" \
	"$(INTDIR)\OBJEdit.sbr" \
	"$(INTDIR)\Observer.sbr" \
	"$(INTDIR)\Operation.sbr" \
	"$(INTDIR)\Optionsheet.sbr" \
	"$(INTDIR)\OwnCombo.sbr" \
	"$(INTDIR)\OwnList.sbr" \
	"$(INTDIR)\PaperPag.sbr" \
	"$(INTDIR)\PaperPage.sbr" \
	"$(INTDIR)\ParseDlg.sbr" \
	"$(INTDIR)\Parser.sbr" \
	"$(INTDIR)\ParserFloat.sbr" \
	"$(INTDIR)\ParserObject.sbr" \
	"$(INTDIR)\ParserVar.sbr" \
	"$(INTDIR)\ParserVerb.sbr" \
	"$(INTDIR)\Pattern.sbr" \
	"$(INTDIR)\PGrid.sbr" \
	"$(INTDIR)\Plane.sbr" \
	"$(INTDIR)\PopBar.sbr" \
	"$(INTDIR)\QLine.sbr" \
	"$(INTDIR)\QuadTree.sbr" \
	"$(INTDIR)\Quaternion.sbr" \
	"$(INTDIR)\Ray.sbr" \
	"$(INTDIR)\RecArray.sbr" \
	"$(INTDIR)\RecColor.sbr" \
	"$(INTDIR)\RecPattern.sbr" \
	"$(INTDIR)\Rectangle.sbr" \
	"$(INTDIR)\RegDialog.sbr" \
	"$(INTDIR)\Register.sbr" \
	"$(INTDIR)\Render.sbr" \
	"$(INTDIR)\RTFACTN.SBR" \
	"$(INTDIR)\Rtfreadr.sbr" \
	"$(INTDIR)\Ruler1.sbr" \
	"$(INTDIR)\SmoothD.sbr" \
	"$(INTDIR)\Snap.sbr" \
	"$(INTDIR)\Splash.sbr" \
	"$(INTDIR)\Spline.sbr" \
	"$(INTDIR)\State.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\Subject.sbr" \
	"$(INTDIR)\SubWnd.sbr" \
	"$(INTDIR)\TextCad.sbr" \
	"$(INTDIR)\textd.sbr" \
	"$(INTDIR)\TextDi.sbr" \
	"$(INTDIR)\ThickD.sbr" \
	"$(INTDIR)\TipDlg.sbr" \
	"$(INTDIR)\TransDlg.sbr" \
	"$(INTDIR)\Translate.sbr" \
	"$(INTDIR)\Triangle.sbr" \
	"$(INTDIR)\TVector.sbr" \
	"$(INTDIR)\TxtED.sbr" \
	"$(INTDIR)\Unclick.sbr" \
	"$(INTDIR)\Vector.sbr" \
	"$(INTDIR)\Vectorm.sbr" \
	"$(INTDIR)\Vectorp.sbr" \
	"$(INTDIR)\Vectorv.sbr" \
	"$(INTDIR)\Verb.sbr" \
	"$(INTDIR)\Vertex.sbr" \
	"$(INTDIR)\Zoombar.sbr" \
	"$(INTDIR)\ZoomD.sbr"

"$(OUTDIR)\cad.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\cad.pdb" /debug /machine:I386 /out:"$(OUTDIR)\cad.exe" /libpath:"C:\Program Files\HTML Help Workshop\LIB" /MAPINFO:LINES /MAPINFO:EXPORTS 
LINK32_OBJS= \
	"$(INTDIR)\AABB.obj" \
	"$(INTDIR)\AddinManager1.obj" \
	"$(INTDIR)\AddinSettingsDialog1.obj" \
	"$(INTDIR)\AndyCad.obj" \
	"$(INTDIR)\AndyCadAddin.obj" \
	"$(INTDIR)\ArrayAngle.obj" \
	"$(INTDIR)\BArrowC.obj" \
	"$(INTDIR)\BArrowP.obj" \
	"$(INTDIR)\Bezier.obj" \
	"$(INTDIR)\cad.obj" \
	"$(INTDIR)\CadAutoCamera.obj" \
	"$(INTDIR)\CadAutoCanvas.obj" \
	"$(INTDIR)\CadAutoCollection.obj" \
	"$(INTDIR)\CadAutoDrawing.obj" \
	"$(INTDIR)\CadAutoDrawingCollection.obj" \
	"$(INTDIR)\CadAutoEdit.obj" \
	"$(INTDIR)\CAdAutoShape.obj" \
	"$(INTDIR)\CadAutoSurface.obj" \
	"$(INTDIR)\CadAutoTransform.obj" \
	"$(INTDIR)\CadAutoUtils.obj" \
	"$(INTDIR)\CadAutoVector.obj" \
	"$(INTDIR)\CadAutoWnd.obj" \
	"$(INTDIR)\cadDoc.obj" \
	"$(INTDIR)\cadView.obj" \
	"$(INTDIR)\CAM.obj" \
	"$(INTDIR)\CameraDlg.obj" \
	"$(INTDIR)\Cercle.obj" \
	"$(INTDIR)\ChamfD.obj" \
	"$(INTDIR)\Chamfer.obj" \
	"$(INTDIR)\ChFi.obj" \
	"$(INTDIR)\Click.obj" \
	"$(INTDIR)\CLineSty.obj" \
	"$(INTDIR)\ColorD.obj" \
	"$(INTDIR)\Command.obj" \
	"$(INTDIR)\CPaperSize.obj" \
	"$(INTDIR)\CTreeCtrl.obj" \
	"$(INTDIR)\CustomSheet.obj" \
	"$(INTDIR)\CustomWidth.obj" \
	"$(INTDIR)\CVector.obj" \
	"$(INTDIR)\Dim.obj" \
	"$(INTDIR)\DimA.obj" \
	"$(INTDIR)\DimL.obj" \
	"$(INTDIR)\DlgCap.obj" \
	"$(INTDIR)\Dot.obj" \
	"$(INTDIR)\Draw.obj" \
	"$(INTDIR)\DrawWnd.obj" \
	"$(INTDIR)\Edge.obj" \
	"$(INTDIR)\EditParse.obj" \
	"$(INTDIR)\Face.obj" \
	"$(INTDIR)\FFD.obj" \
	"$(INTDIR)\Figure.obj" \
	"$(INTDIR)\geometry.obj" \
	"$(INTDIR)\GridPag.obj" \
	"$(INTDIR)\GridPage.obj" \
	"$(INTDIR)\Image.obj" \
	"$(INTDIR)\Imagex.obj" \
	"$(INTDIR)\InfoBar.obj" \
	"$(INTDIR)\Inter.obj" \
	"$(INTDIR)\LayBar.obj" \
	"$(INTDIR)\Layerad.obj" \
	"$(INTDIR)\LayerD.obj" \
	"$(INTDIR)\LayList.obj" \
	"$(INTDIR)\LComboBox.obj" \
	"$(INTDIR)\Libdialog.obj" \
	"$(INTDIR)\LibS.obj" \
	"$(INTDIR)\LightD.obj" \
	"$(INTDIR)\Line.obj" \
	"$(INTDIR)\LineAgain.obj" \
	"$(INTDIR)\LineBar.obj" \
	"$(INTDIR)\Linestyle.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Matrix1.obj" \
	"$(INTDIR)\MClick.obj" \
	"$(INTDIR)\Memento.obj" \
	"$(INTDIR)\Mesh.obj" \
	"$(INTDIR)\Mouse.obj" \
	"$(INTDIR)\MultVar.obj" \
	"$(INTDIR)\NumCopy.obj" \
	"$(INTDIR)\OBJEdit.obj" \
	"$(INTDIR)\Observer.obj" \
	"$(INTDIR)\Operation.obj" \
	"$(INTDIR)\Optionsheet.obj" \
	"$(INTDIR)\OwnCombo.obj" \
	"$(INTDIR)\OwnList.obj" \
	"$(INTDIR)\PaperPag.obj" \
	"$(INTDIR)\PaperPage.obj" \
	"$(INTDIR)\ParseDlg.obj" \
	"$(INTDIR)\Parser.obj" \
	"$(INTDIR)\ParserFloat.obj" \
	"$(INTDIR)\ParserObject.obj" \
	"$(INTDIR)\ParserVar.obj" \
	"$(INTDIR)\ParserVerb.obj" \
	"$(INTDIR)\Pattern.obj" \
	"$(INTDIR)\PGrid.obj" \
	"$(INTDIR)\Plane.obj" \
	"$(INTDIR)\PopBar.obj" \
	"$(INTDIR)\QLine.obj" \
	"$(INTDIR)\QuadTree.obj" \
	"$(INTDIR)\Quaternion.obj" \
	"$(INTDIR)\Ray.obj" \
	"$(INTDIR)\RecArray.obj" \
	"$(INTDIR)\RecColor.obj" \
	"$(INTDIR)\RecPattern.obj" \
	"$(INTDIR)\Rectangle.obj" \
	"$(INTDIR)\RegDialog.obj" \
	"$(INTDIR)\Register.obj" \
	"$(INTDIR)\Render.obj" \
	"$(INTDIR)\RTFACTN.OBJ" \
	"$(INTDIR)\Rtfreadr.obj" \
	"$(INTDIR)\Ruler1.obj" \
	"$(INTDIR)\SmoothD.obj" \
	"$(INTDIR)\Snap.obj" \
	"$(INTDIR)\Splash.obj" \
	"$(INTDIR)\Spline.obj" \
	"$(INTDIR)\State.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Subject.obj" \
	"$(INTDIR)\SubWnd.obj" \
	"$(INTDIR)\TextCad.obj" \
	"$(INTDIR)\textd.obj" \
	"$(INTDIR)\TextDi.obj" \
	"$(INTDIR)\ThickD.obj" \
	"$(INTDIR)\TipDlg.obj" \
	"$(INTDIR)\TransDlg.obj" \
	"$(INTDIR)\Translate.obj" \
	"$(INTDIR)\Triangle.obj" \
	"$(INTDIR)\TVector.obj" \
	"$(INTDIR)\TxtED.obj" \
	"$(INTDIR)\Unclick.obj" \
	"$(INTDIR)\Vector.obj" \
	"$(INTDIR)\Vectorm.obj" \
	"$(INTDIR)\Vectorp.obj" \
	"$(INTDIR)\Vectorv.obj" \
	"$(INTDIR)\Verb.obj" \
	"$(INTDIR)\Vertex.obj" \
	"$(INTDIR)\Zoombar.obj" \
	"$(INTDIR)\ZoomD.obj" \
	"$(INTDIR)\cad.res"

"$(OUTDIR)\cad.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "cad - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\Debug\cad.hlp" ".\Debug\cad.cnt" "$(OUTDIR)\cad.exe" "$(OUTDIR)\cad.tlb" "$(OUTDIR)\cad.bsc" "$(OUTDIR)\CadAddIn.tlb"


CLEAN :
	-@erase "$(INTDIR)\AABB.obj"
	-@erase "$(INTDIR)\AABB.sbr"
	-@erase "$(INTDIR)\AddinManager1.obj"
	-@erase "$(INTDIR)\AddinManager1.sbr"
	-@erase "$(INTDIR)\AddinSettingsDialog1.obj"
	-@erase "$(INTDIR)\AddinSettingsDialog1.sbr"
	-@erase "$(INTDIR)\AndyCad.obj"
	-@erase "$(INTDIR)\AndyCad.sbr"
	-@erase "$(INTDIR)\AndyCadAddin.obj"
	-@erase "$(INTDIR)\AndyCadAddin.sbr"
	-@erase "$(INTDIR)\ArrayAngle.obj"
	-@erase "$(INTDIR)\ArrayAngle.sbr"
	-@erase "$(INTDIR)\BArrowC.obj"
	-@erase "$(INTDIR)\BArrowC.sbr"
	-@erase "$(INTDIR)\BArrowP.obj"
	-@erase "$(INTDIR)\BArrowP.sbr"
	-@erase "$(INTDIR)\Bezier.obj"
	-@erase "$(INTDIR)\Bezier.sbr"
	-@erase "$(INTDIR)\cad.obj"
	-@erase "$(INTDIR)\cad.pch"
	-@erase "$(INTDIR)\cad.res"
	-@erase "$(INTDIR)\cad.sbr"
	-@erase "$(INTDIR)\cad.tlb"
	-@erase "$(INTDIR)\CadAddIn.tlb"
	-@erase "$(INTDIR)\CadAutoCamera.obj"
	-@erase "$(INTDIR)\CadAutoCamera.sbr"
	-@erase "$(INTDIR)\CadAutoCanvas.obj"
	-@erase "$(INTDIR)\CadAutoCanvas.sbr"
	-@erase "$(INTDIR)\CadAutoCollection.obj"
	-@erase "$(INTDIR)\CadAutoCollection.sbr"
	-@erase "$(INTDIR)\CadAutoDrawing.obj"
	-@erase "$(INTDIR)\CadAutoDrawing.sbr"
	-@erase "$(INTDIR)\CadAutoDrawingCollection.obj"
	-@erase "$(INTDIR)\CadAutoDrawingCollection.sbr"
	-@erase "$(INTDIR)\CadAutoEdit.obj"
	-@erase "$(INTDIR)\CadAutoEdit.sbr"
	-@erase "$(INTDIR)\CAdAutoShape.obj"
	-@erase "$(INTDIR)\CAdAutoShape.sbr"
	-@erase "$(INTDIR)\CadAutoSurface.obj"
	-@erase "$(INTDIR)\CadAutoSurface.sbr"
	-@erase "$(INTDIR)\CadAutoTransform.obj"
	-@erase "$(INTDIR)\CadAutoTransform.sbr"
	-@erase "$(INTDIR)\CadAutoUtils.obj"
	-@erase "$(INTDIR)\CadAutoUtils.sbr"
	-@erase "$(INTDIR)\CadAutoVector.obj"
	-@erase "$(INTDIR)\CadAutoVector.sbr"
	-@erase "$(INTDIR)\CadAutoWnd.obj"
	-@erase "$(INTDIR)\CadAutoWnd.sbr"
	-@erase "$(INTDIR)\cadDoc.obj"
	-@erase "$(INTDIR)\cadDoc.sbr"
	-@erase "$(INTDIR)\cadView.obj"
	-@erase "$(INTDIR)\cadView.sbr"
	-@erase "$(INTDIR)\CAM.obj"
	-@erase "$(INTDIR)\CAM.sbr"
	-@erase "$(INTDIR)\CameraDlg.obj"
	-@erase "$(INTDIR)\CameraDlg.sbr"
	-@erase "$(INTDIR)\Cercle.obj"
	-@erase "$(INTDIR)\Cercle.sbr"
	-@erase "$(INTDIR)\ChamfD.obj"
	-@erase "$(INTDIR)\ChamfD.sbr"
	-@erase "$(INTDIR)\Chamfer.obj"
	-@erase "$(INTDIR)\Chamfer.sbr"
	-@erase "$(INTDIR)\ChFi.obj"
	-@erase "$(INTDIR)\ChFi.sbr"
	-@erase "$(INTDIR)\Click.obj"
	-@erase "$(INTDIR)\Click.sbr"
	-@erase "$(INTDIR)\CLineSty.obj"
	-@erase "$(INTDIR)\CLineSty.sbr"
	-@erase "$(INTDIR)\ColorD.obj"
	-@erase "$(INTDIR)\ColorD.sbr"
	-@erase "$(INTDIR)\Command.obj"
	-@erase "$(INTDIR)\Command.sbr"
	-@erase "$(INTDIR)\CPaperSize.obj"
	-@erase "$(INTDIR)\CPaperSize.sbr"
	-@erase "$(INTDIR)\CustomSheet.obj"
	-@erase "$(INTDIR)\CustomSheet.sbr"
	-@erase "$(INTDIR)\CustomWidth.obj"
	-@erase "$(INTDIR)\CustomWidth.sbr"
	-@erase "$(INTDIR)\CVector.obj"
	-@erase "$(INTDIR)\CVector.sbr"
	-@erase "$(INTDIR)\Dim.obj"
	-@erase "$(INTDIR)\Dim.sbr"
	-@erase "$(INTDIR)\DimA.obj"
	-@erase "$(INTDIR)\DimA.sbr"
	-@erase "$(INTDIR)\DimL.obj"
	-@erase "$(INTDIR)\DimL.sbr"
	-@erase "$(INTDIR)\DlgCap.obj"
	-@erase "$(INTDIR)\DlgCap.sbr"
	-@erase "$(INTDIR)\Dot.obj"
	-@erase "$(INTDIR)\Dot.sbr"
	-@erase "$(INTDIR)\Draw.obj"
	-@erase "$(INTDIR)\Draw.sbr"
	-@erase "$(INTDIR)\DrawWnd.obj"
	-@erase "$(INTDIR)\DrawWnd.sbr"
	-@erase "$(INTDIR)\Edge.obj"
	-@erase "$(INTDIR)\Edge.sbr"
	-@erase "$(INTDIR)\EditParse.obj"
	-@erase "$(INTDIR)\EditParse.sbr"
	-@erase "$(INTDIR)\Face.obj"
	-@erase "$(INTDIR)\Face.sbr"
	-@erase "$(INTDIR)\FFD.obj"
	-@erase "$(INTDIR)\FFD.sbr"
	-@erase "$(INTDIR)\Figure.obj"
	-@erase "$(INTDIR)\Figure.sbr"
	-@erase "$(INTDIR)\geometry.obj"
	-@erase "$(INTDIR)\geometry.sbr"
	-@erase "$(INTDIR)\GridPag.obj"
	-@erase "$(INTDIR)\GridPag.sbr"
	-@erase "$(INTDIR)\GridPage.obj"
	-@erase "$(INTDIR)\GridPage.sbr"
	-@erase "$(INTDIR)\Image.obj"
	-@erase "$(INTDIR)\Image.sbr"
	-@erase "$(INTDIR)\Imagex.obj"
	-@erase "$(INTDIR)\Imagex.sbr"
	-@erase "$(INTDIR)\InfoBar.obj"
	-@erase "$(INTDIR)\InfoBar.sbr"
	-@erase "$(INTDIR)\Inter.obj"
	-@erase "$(INTDIR)\Inter.sbr"
	-@erase "$(INTDIR)\LayBar.obj"
	-@erase "$(INTDIR)\LayBar.sbr"
	-@erase "$(INTDIR)\Layerad.obj"
	-@erase "$(INTDIR)\Layerad.sbr"
	-@erase "$(INTDIR)\LayerD.obj"
	-@erase "$(INTDIR)\LayerD.sbr"
	-@erase "$(INTDIR)\LayList.obj"
	-@erase "$(INTDIR)\LayList.sbr"
	-@erase "$(INTDIR)\LComboBox.obj"
	-@erase "$(INTDIR)\LComboBox.sbr"
	-@erase "$(INTDIR)\Libdialog.obj"
	-@erase "$(INTDIR)\Libdialog.sbr"
	-@erase "$(INTDIR)\LibS.obj"
	-@erase "$(INTDIR)\LibS.sbr"
	-@erase "$(INTDIR)\LightD.obj"
	-@erase "$(INTDIR)\LightD.sbr"
	-@erase "$(INTDIR)\Line.obj"
	-@erase "$(INTDIR)\Line.sbr"
	-@erase "$(INTDIR)\LineAgain.obj"
	-@erase "$(INTDIR)\LineAgain.sbr"
	-@erase "$(INTDIR)\LineBar.obj"
	-@erase "$(INTDIR)\LineBar.sbr"
	-@erase "$(INTDIR)\Linestyle.obj"
	-@erase "$(INTDIR)\Linestyle.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\Matrix1.obj"
	-@erase "$(INTDIR)\Matrix1.sbr"
	-@erase "$(INTDIR)\MClick.obj"
	-@erase "$(INTDIR)\MClick.sbr"
	-@erase "$(INTDIR)\Memento.obj"
	-@erase "$(INTDIR)\Memento.sbr"
	-@erase "$(INTDIR)\Mesh.obj"
	-@erase "$(INTDIR)\Mesh.sbr"
	-@erase "$(INTDIR)\Mouse.obj"
	-@erase "$(INTDIR)\Mouse.sbr"
	-@erase "$(INTDIR)\MultVar.obj"
	-@erase "$(INTDIR)\MultVar.sbr"
	-@erase "$(INTDIR)\NumCopy.obj"
	-@erase "$(INTDIR)\NumCopy.sbr"
	-@erase "$(INTDIR)\OBJEdit.obj"
	-@erase "$(INTDIR)\OBJEdit.sbr"
	-@erase "$(INTDIR)\Observer.obj"
	-@erase "$(INTDIR)\Observer.sbr"
	-@erase "$(INTDIR)\Operation.obj"
	-@erase "$(INTDIR)\Operation.sbr"
	-@erase "$(INTDIR)\Optionsheet.obj"
	-@erase "$(INTDIR)\Optionsheet.sbr"
	-@erase "$(INTDIR)\OwnCombo.obj"
	-@erase "$(INTDIR)\OwnCombo.sbr"
	-@erase "$(INTDIR)\OwnList.obj"
	-@erase "$(INTDIR)\OwnList.sbr"
	-@erase "$(INTDIR)\PaperPag.obj"
	-@erase "$(INTDIR)\PaperPag.sbr"
	-@erase "$(INTDIR)\PaperPage.obj"
	-@erase "$(INTDIR)\PaperPage.sbr"
	-@erase "$(INTDIR)\ParseDlg.obj"
	-@erase "$(INTDIR)\ParseDlg.sbr"
	-@erase "$(INTDIR)\Parser.obj"
	-@erase "$(INTDIR)\Parser.sbr"
	-@erase "$(INTDIR)\ParserFloat.obj"
	-@erase "$(INTDIR)\ParserFloat.sbr"
	-@erase "$(INTDIR)\ParserObject.obj"
	-@erase "$(INTDIR)\ParserObject.sbr"
	-@erase "$(INTDIR)\ParserVar.obj"
	-@erase "$(INTDIR)\ParserVar.sbr"
	-@erase "$(INTDIR)\ParserVerb.obj"
	-@erase "$(INTDIR)\ParserVerb.sbr"
	-@erase "$(INTDIR)\Pattern.obj"
	-@erase "$(INTDIR)\Pattern.sbr"
	-@erase "$(INTDIR)\PGrid.obj"
	-@erase "$(INTDIR)\PGrid.sbr"
	-@erase "$(INTDIR)\Plane.obj"
	-@erase "$(INTDIR)\Plane.sbr"
	-@erase "$(INTDIR)\PopBar.obj"
	-@erase "$(INTDIR)\PopBar.sbr"
	-@erase "$(INTDIR)\QLine.obj"
	-@erase "$(INTDIR)\QLine.sbr"
	-@erase "$(INTDIR)\QuadTree.obj"
	-@erase "$(INTDIR)\QuadTree.sbr"
	-@erase "$(INTDIR)\Quaternion.obj"
	-@erase "$(INTDIR)\Quaternion.sbr"
	-@erase "$(INTDIR)\Ray.obj"
	-@erase "$(INTDIR)\Ray.sbr"
	-@erase "$(INTDIR)\RecArray.obj"
	-@erase "$(INTDIR)\RecArray.sbr"
	-@erase "$(INTDIR)\RecColor.obj"
	-@erase "$(INTDIR)\RecColor.sbr"
	-@erase "$(INTDIR)\RecPattern.obj"
	-@erase "$(INTDIR)\RecPattern.sbr"
	-@erase "$(INTDIR)\Rectangle.obj"
	-@erase "$(INTDIR)\Rectangle.sbr"
	-@erase "$(INTDIR)\RegDialog.obj"
	-@erase "$(INTDIR)\RegDialog.sbr"
	-@erase "$(INTDIR)\Register.obj"
	-@erase "$(INTDIR)\Register.sbr"
	-@erase "$(INTDIR)\Render.obj"
	-@erase "$(INTDIR)\Render.sbr"
	-@erase "$(INTDIR)\RTFACTN.OBJ"
	-@erase "$(INTDIR)\RTFACTN.SBR"
	-@erase "$(INTDIR)\Rtfreadr.obj"
	-@erase "$(INTDIR)\Rtfreadr.sbr"
	-@erase "$(INTDIR)\Ruler1.obj"
	-@erase "$(INTDIR)\Ruler1.sbr"
	-@erase "$(INTDIR)\SmoothD.obj"
	-@erase "$(INTDIR)\SmoothD.sbr"
	-@erase "$(INTDIR)\Snap.obj"
	-@erase "$(INTDIR)\Snap.sbr"
	-@erase "$(INTDIR)\Splash.obj"
	-@erase "$(INTDIR)\Splash.sbr"
	-@erase "$(INTDIR)\Spline.obj"
	-@erase "$(INTDIR)\Spline.sbr"
	-@erase "$(INTDIR)\State.obj"
	-@erase "$(INTDIR)\State.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\Subject.obj"
	-@erase "$(INTDIR)\Subject.sbr"
	-@erase "$(INTDIR)\SubWnd.obj"
	-@erase "$(INTDIR)\SubWnd.sbr"
	-@erase "$(INTDIR)\TextCad.obj"
	-@erase "$(INTDIR)\TextCad.sbr"
	-@erase "$(INTDIR)\textd.obj"
	-@erase "$(INTDIR)\textd.sbr"
	-@erase "$(INTDIR)\TextDi.obj"
	-@erase "$(INTDIR)\TextDi.sbr"
	-@erase "$(INTDIR)\ThickD.obj"
	-@erase "$(INTDIR)\ThickD.sbr"
	-@erase "$(INTDIR)\TipDlg.obj"
	-@erase "$(INTDIR)\TipDlg.sbr"
	-@erase "$(INTDIR)\TransDlg.obj"
	-@erase "$(INTDIR)\TransDlg.sbr"
	-@erase "$(INTDIR)\Translate.obj"
	-@erase "$(INTDIR)\Translate.sbr"
	-@erase "$(INTDIR)\Triangle.obj"
	-@erase "$(INTDIR)\Triangle.sbr"
	-@erase "$(INTDIR)\TVector.obj"
	-@erase "$(INTDIR)\TVector.sbr"
	-@erase "$(INTDIR)\TxtED.obj"
	-@erase "$(INTDIR)\TxtED.sbr"
	-@erase "$(INTDIR)\Unclick.obj"
	-@erase "$(INTDIR)\Unclick.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\Vector.obj"
	-@erase "$(INTDIR)\Vector.sbr"
	-@erase "$(INTDIR)\Vectorm.obj"
	-@erase "$(INTDIR)\Vectorm.sbr"
	-@erase "$(INTDIR)\Vectorp.obj"
	-@erase "$(INTDIR)\Vectorp.sbr"
	-@erase "$(INTDIR)\Vectorv.obj"
	-@erase "$(INTDIR)\Vectorv.sbr"
	-@erase "$(INTDIR)\Verb.obj"
	-@erase "$(INTDIR)\Verb.sbr"
	-@erase "$(INTDIR)\Vertex.obj"
	-@erase "$(INTDIR)\Vertex.sbr"
	-@erase "$(INTDIR)\Zoombar.obj"
	-@erase "$(INTDIR)\Zoombar.sbr"
	-@erase "$(INTDIR)\ZoomD.obj"
	-@erase "$(INTDIR)\ZoomD.sbr"
	-@erase "$(OUTDIR)\cad.bsc"
	-@erase "$(OUTDIR)\cad.exe"
	-@erase "$(OUTDIR)\cad.map"
	-@erase "$(OUTDIR)\cad.pdb"
	-@erase ".\Debug\cad.cnt"
	-@erase ".\Debug\cad.hlp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /GX /Z7 /Od /I "C:\Program Files\HTML Help Workshop\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FAcs /Fa"$(INTDIR)\\" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\cad.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\cad.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\cad.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AABB.sbr" \
	"$(INTDIR)\AddinManager1.sbr" \
	"$(INTDIR)\AddinSettingsDialog1.sbr" \
	"$(INTDIR)\AndyCad.sbr" \
	"$(INTDIR)\AndyCadAddin.sbr" \
	"$(INTDIR)\ArrayAngle.sbr" \
	"$(INTDIR)\BArrowC.sbr" \
	"$(INTDIR)\BArrowP.sbr" \
	"$(INTDIR)\Bezier.sbr" \
	"$(INTDIR)\cad.sbr" \
	"$(INTDIR)\CadAutoCamera.sbr" \
	"$(INTDIR)\CadAutoCanvas.sbr" \
	"$(INTDIR)\CadAutoCollection.sbr" \
	"$(INTDIR)\CadAutoDrawing.sbr" \
	"$(INTDIR)\CadAutoDrawingCollection.sbr" \
	"$(INTDIR)\CadAutoEdit.sbr" \
	"$(INTDIR)\CAdAutoShape.sbr" \
	"$(INTDIR)\CadAutoSurface.sbr" \
	"$(INTDIR)\CadAutoTransform.sbr" \
	"$(INTDIR)\CadAutoUtils.sbr" \
	"$(INTDIR)\CadAutoVector.sbr" \
	"$(INTDIR)\CadAutoWnd.sbr" \
	"$(INTDIR)\cadDoc.sbr" \
	"$(INTDIR)\cadView.sbr" \
	"$(INTDIR)\CAM.sbr" \
	"$(INTDIR)\CameraDlg.sbr" \
	"$(INTDIR)\Cercle.sbr" \
	"$(INTDIR)\ChamfD.sbr" \
	"$(INTDIR)\Chamfer.sbr" \
	"$(INTDIR)\ChFi.sbr" \
	"$(INTDIR)\Click.sbr" \
	"$(INTDIR)\CLineSty.sbr" \
	"$(INTDIR)\ColorD.sbr" \
	"$(INTDIR)\Command.sbr" \
	"$(INTDIR)\CPaperSize.sbr" \
	"$(INTDIR)\CustomSheet.sbr" \
	"$(INTDIR)\CustomWidth.sbr" \
	"$(INTDIR)\CVector.sbr" \
	"$(INTDIR)\Dim.sbr" \
	"$(INTDIR)\DimA.sbr" \
	"$(INTDIR)\DimL.sbr" \
	"$(INTDIR)\DlgCap.sbr" \
	"$(INTDIR)\Dot.sbr" \
	"$(INTDIR)\Draw.sbr" \
	"$(INTDIR)\DrawWnd.sbr" \
	"$(INTDIR)\Edge.sbr" \
	"$(INTDIR)\EditParse.sbr" \
	"$(INTDIR)\Face.sbr" \
	"$(INTDIR)\FFD.sbr" \
	"$(INTDIR)\Figure.sbr" \
	"$(INTDIR)\geometry.sbr" \
	"$(INTDIR)\GridPag.sbr" \
	"$(INTDIR)\GridPage.sbr" \
	"$(INTDIR)\Image.sbr" \
	"$(INTDIR)\Imagex.sbr" \
	"$(INTDIR)\InfoBar.sbr" \
	"$(INTDIR)\Inter.sbr" \
	"$(INTDIR)\LayBar.sbr" \
	"$(INTDIR)\Layerad.sbr" \
	"$(INTDIR)\LayerD.sbr" \
	"$(INTDIR)\LayList.sbr" \
	"$(INTDIR)\LComboBox.sbr" \
	"$(INTDIR)\Libdialog.sbr" \
	"$(INTDIR)\LibS.sbr" \
	"$(INTDIR)\LightD.sbr" \
	"$(INTDIR)\Line.sbr" \
	"$(INTDIR)\LineAgain.sbr" \
	"$(INTDIR)\LineBar.sbr" \
	"$(INTDIR)\Linestyle.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\Matrix1.sbr" \
	"$(INTDIR)\MClick.sbr" \
	"$(INTDIR)\Memento.sbr" \
	"$(INTDIR)\Mesh.sbr" \
	"$(INTDIR)\Mouse.sbr" \
	"$(INTDIR)\MultVar.sbr" \
	"$(INTDIR)\NumCopy.sbr" \
	"$(INTDIR)\OBJEdit.sbr" \
	"$(INTDIR)\Observer.sbr" \
	"$(INTDIR)\Operation.sbr" \
	"$(INTDIR)\Optionsheet.sbr" \
	"$(INTDIR)\OwnCombo.sbr" \
	"$(INTDIR)\OwnList.sbr" \
	"$(INTDIR)\PaperPag.sbr" \
	"$(INTDIR)\PaperPage.sbr" \
	"$(INTDIR)\ParseDlg.sbr" \
	"$(INTDIR)\Parser.sbr" \
	"$(INTDIR)\ParserFloat.sbr" \
	"$(INTDIR)\ParserObject.sbr" \
	"$(INTDIR)\ParserVar.sbr" \
	"$(INTDIR)\ParserVerb.sbr" \
	"$(INTDIR)\Pattern.sbr" \
	"$(INTDIR)\PGrid.sbr" \
	"$(INTDIR)\Plane.sbr" \
	"$(INTDIR)\PopBar.sbr" \
	"$(INTDIR)\QLine.sbr" \
	"$(INTDIR)\QuadTree.sbr" \
	"$(INTDIR)\Quaternion.sbr" \
	"$(INTDIR)\Ray.sbr" \
	"$(INTDIR)\RecArray.sbr" \
	"$(INTDIR)\RecColor.sbr" \
	"$(INTDIR)\RecPattern.sbr" \
	"$(INTDIR)\Rectangle.sbr" \
	"$(INTDIR)\RegDialog.sbr" \
	"$(INTDIR)\Register.sbr" \
	"$(INTDIR)\Render.sbr" \
	"$(INTDIR)\RTFACTN.SBR" \
	"$(INTDIR)\Rtfreadr.sbr" \
	"$(INTDIR)\Ruler1.sbr" \
	"$(INTDIR)\SmoothD.sbr" \
	"$(INTDIR)\Snap.sbr" \
	"$(INTDIR)\Splash.sbr" \
	"$(INTDIR)\Spline.sbr" \
	"$(INTDIR)\State.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\Subject.sbr" \
	"$(INTDIR)\SubWnd.sbr" \
	"$(INTDIR)\TextCad.sbr" \
	"$(INTDIR)\textd.sbr" \
	"$(INTDIR)\TextDi.sbr" \
	"$(INTDIR)\ThickD.sbr" \
	"$(INTDIR)\TipDlg.sbr" \
	"$(INTDIR)\TransDlg.sbr" \
	"$(INTDIR)\Translate.sbr" \
	"$(INTDIR)\Triangle.sbr" \
	"$(INTDIR)\TVector.sbr" \
	"$(INTDIR)\TxtED.sbr" \
	"$(INTDIR)\Unclick.sbr" \
	"$(INTDIR)\Vector.sbr" \
	"$(INTDIR)\Vectorm.sbr" \
	"$(INTDIR)\Vectorp.sbr" \
	"$(INTDIR)\Vectorv.sbr" \
	"$(INTDIR)\Verb.sbr" \
	"$(INTDIR)\Vertex.sbr" \
	"$(INTDIR)\Zoombar.sbr" \
	"$(INTDIR)\ZoomD.sbr"

"$(OUTDIR)\cad.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=vfw32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\cad.pdb" /map:"$(INTDIR)\cad.map" /debug /machine:I386 /out:"$(OUTDIR)\cad.exe" /pdbtype:sept /libpath:"C:\Program Files\HTML Help Workshop\LIB" 
LINK32_OBJS= \
	"$(INTDIR)\AABB.obj" \
	"$(INTDIR)\AddinManager1.obj" \
	"$(INTDIR)\AddinSettingsDialog1.obj" \
	"$(INTDIR)\AndyCad.obj" \
	"$(INTDIR)\AndyCadAddin.obj" \
	"$(INTDIR)\ArrayAngle.obj" \
	"$(INTDIR)\BArrowC.obj" \
	"$(INTDIR)\BArrowP.obj" \
	"$(INTDIR)\Bezier.obj" \
	"$(INTDIR)\cad.obj" \
	"$(INTDIR)\CadAutoCamera.obj" \
	"$(INTDIR)\CadAutoCanvas.obj" \
	"$(INTDIR)\CadAutoCollection.obj" \
	"$(INTDIR)\CadAutoDrawing.obj" \
	"$(INTDIR)\CadAutoDrawingCollection.obj" \
	"$(INTDIR)\CadAutoEdit.obj" \
	"$(INTDIR)\CAdAutoShape.obj" \
	"$(INTDIR)\CadAutoSurface.obj" \
	"$(INTDIR)\CadAutoTransform.obj" \
	"$(INTDIR)\CadAutoUtils.obj" \
	"$(INTDIR)\CadAutoVector.obj" \
	"$(INTDIR)\CadAutoWnd.obj" \
	"$(INTDIR)\cadDoc.obj" \
	"$(INTDIR)\cadView.obj" \
	"$(INTDIR)\CAM.obj" \
	"$(INTDIR)\CameraDlg.obj" \
	"$(INTDIR)\Cercle.obj" \
	"$(INTDIR)\ChamfD.obj" \
	"$(INTDIR)\Chamfer.obj" \
	"$(INTDIR)\ChFi.obj" \
	"$(INTDIR)\Click.obj" \
	"$(INTDIR)\CLineSty.obj" \
	"$(INTDIR)\ColorD.obj" \
	"$(INTDIR)\Command.obj" \
	"$(INTDIR)\CPaperSize.obj" \
	"$(INTDIR)\CustomSheet.obj" \
	"$(INTDIR)\CustomWidth.obj" \
	"$(INTDIR)\CVector.obj" \
	"$(INTDIR)\Dim.obj" \
	"$(INTDIR)\DimA.obj" \
	"$(INTDIR)\DimL.obj" \
	"$(INTDIR)\DlgCap.obj" \
	"$(INTDIR)\Dot.obj" \
	"$(INTDIR)\Draw.obj" \
	"$(INTDIR)\DrawWnd.obj" \
	"$(INTDIR)\Edge.obj" \
	"$(INTDIR)\EditParse.obj" \
	"$(INTDIR)\Face.obj" \
	"$(INTDIR)\FFD.obj" \
	"$(INTDIR)\Figure.obj" \
	"$(INTDIR)\geometry.obj" \
	"$(INTDIR)\GridPag.obj" \
	"$(INTDIR)\GridPage.obj" \
	"$(INTDIR)\Image.obj" \
	"$(INTDIR)\Imagex.obj" \
	"$(INTDIR)\InfoBar.obj" \
	"$(INTDIR)\Inter.obj" \
	"$(INTDIR)\LayBar.obj" \
	"$(INTDIR)\Layerad.obj" \
	"$(INTDIR)\LayerD.obj" \
	"$(INTDIR)\LayList.obj" \
	"$(INTDIR)\LComboBox.obj" \
	"$(INTDIR)\Libdialog.obj" \
	"$(INTDIR)\LibS.obj" \
	"$(INTDIR)\LightD.obj" \
	"$(INTDIR)\Line.obj" \
	"$(INTDIR)\LineAgain.obj" \
	"$(INTDIR)\LineBar.obj" \
	"$(INTDIR)\Linestyle.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Matrix1.obj" \
	"$(INTDIR)\MClick.obj" \
	"$(INTDIR)\Memento.obj" \
	"$(INTDIR)\Mesh.obj" \
	"$(INTDIR)\Mouse.obj" \
	"$(INTDIR)\MultVar.obj" \
	"$(INTDIR)\NumCopy.obj" \
	"$(INTDIR)\OBJEdit.obj" \
	"$(INTDIR)\Observer.obj" \
	"$(INTDIR)\Operation.obj" \
	"$(INTDIR)\Optionsheet.obj" \
	"$(INTDIR)\OwnCombo.obj" \
	"$(INTDIR)\OwnList.obj" \
	"$(INTDIR)\PaperPag.obj" \
	"$(INTDIR)\PaperPage.obj" \
	"$(INTDIR)\ParseDlg.obj" \
	"$(INTDIR)\Parser.obj" \
	"$(INTDIR)\ParserFloat.obj" \
	"$(INTDIR)\ParserObject.obj" \
	"$(INTDIR)\ParserVar.obj" \
	"$(INTDIR)\ParserVerb.obj" \
	"$(INTDIR)\Pattern.obj" \
	"$(INTDIR)\PGrid.obj" \
	"$(INTDIR)\Plane.obj" \
	"$(INTDIR)\PopBar.obj" \
	"$(INTDIR)\QLine.obj" \
	"$(INTDIR)\QuadTree.obj" \
	"$(INTDIR)\Quaternion.obj" \
	"$(INTDIR)\Ray.obj" \
	"$(INTDIR)\RecArray.obj" \
	"$(INTDIR)\RecColor.obj" \
	"$(INTDIR)\RecPattern.obj" \
	"$(INTDIR)\Rectangle.obj" \
	"$(INTDIR)\RegDialog.obj" \
	"$(INTDIR)\Register.obj" \
	"$(INTDIR)\Render.obj" \
	"$(INTDIR)\RTFACTN.OBJ" \
	"$(INTDIR)\Rtfreadr.obj" \
	"$(INTDIR)\Ruler1.obj" \
	"$(INTDIR)\SmoothD.obj" \
	"$(INTDIR)\Snap.obj" \
	"$(INTDIR)\Splash.obj" \
	"$(INTDIR)\Spline.obj" \
	"$(INTDIR)\State.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Subject.obj" \
	"$(INTDIR)\SubWnd.obj" \
	"$(INTDIR)\TextCad.obj" \
	"$(INTDIR)\textd.obj" \
	"$(INTDIR)\TextDi.obj" \
	"$(INTDIR)\ThickD.obj" \
	"$(INTDIR)\TipDlg.obj" \
	"$(INTDIR)\TransDlg.obj" \
	"$(INTDIR)\Translate.obj" \
	"$(INTDIR)\Triangle.obj" \
	"$(INTDIR)\TVector.obj" \
	"$(INTDIR)\TxtED.obj" \
	"$(INTDIR)\Unclick.obj" \
	"$(INTDIR)\Vector.obj" \
	"$(INTDIR)\Vectorm.obj" \
	"$(INTDIR)\Vectorp.obj" \
	"$(INTDIR)\Vectorv.obj" \
	"$(INTDIR)\Verb.obj" \
	"$(INTDIR)\Vertex.obj" \
	"$(INTDIR)\Zoombar.obj" \
	"$(INTDIR)\ZoomD.obj" \
	"$(INTDIR)\cad.res"

"$(OUTDIR)\cad.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("cad.dep")
!INCLUDE "cad.dep"
!ELSE 
!MESSAGE Warning: cannot find "cad.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "cad - Win32 Release" || "$(CFG)" == "cad - Win32 Debug"
SOURCE=.\AABB.cpp

"$(INTDIR)\AABB.obj"	"$(INTDIR)\AABB.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\AddinManager1.cpp

"$(INTDIR)\AddinManager1.obj"	"$(INTDIR)\AddinManager1.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\AddinSettingsDialog1.cpp

"$(INTDIR)\AddinSettingsDialog1.obj"	"$(INTDIR)\AddinSettingsDialog1.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\AndyCad.cpp

"$(INTDIR)\AndyCad.obj"	"$(INTDIR)\AndyCad.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\AndyCadAddin.cpp

"$(INTDIR)\AndyCadAddin.obj"	"$(INTDIR)\AndyCadAddin.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\ArrayAngle.cpp

"$(INTDIR)\ArrayAngle.obj"	"$(INTDIR)\ArrayAngle.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\BArrowC.cpp

"$(INTDIR)\BArrowC.obj"	"$(INTDIR)\BArrowC.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\BArrowP.cpp

"$(INTDIR)\BArrowP.obj"	"$(INTDIR)\BArrowP.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Bezier.cpp

"$(INTDIR)\Bezier.obj"	"$(INTDIR)\Bezier.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\cad.cpp

"$(INTDIR)\cad.obj"	"$(INTDIR)\cad.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\hlp\cad.hpj

!IF  "$(CFG)" == "cad - Win32 Release"

OutDir=.\Release
TargetName=cad
InputPath=.\hlp\cad.hpj
InputName=cad
USERDEP__CAD_H="hlp\AfxCore.rtf"	"hlp\AfxPrint.rtf"	"hlp\$(TargetName).hm"	

"$(INTDIR)\cad.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__CAD_H)
	<<tempfile.bat 
	@echo off 
	start /wait hcw /C /E /M "hlp\$(InputName).hpj" 
	if errorlevel 1 goto :Error 
	if not exist "hlp\$(InputName).hlp" goto :Error 
	copy "hlp\$(InputName).hlp" $(OutDir) 
	goto :done 
	:Error 
	echo hlp\$(InputName).hpj(1) : error: 
	type "hlp\$(InputName).log" 
	:done 
<< 
	

!ELSEIF  "$(CFG)" == "cad - Win32 Debug"

OutDir=.\Debug
TargetName=cad
InputPath=.\hlp\cad.hpj
InputName=cad
USERDEP__CAD_H="hlp\AfxCore.rtf"	"hlp\AfxPrint.rtf"	"hlp\$(TargetName).hm"	

"$(INTDIR)\cad.hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__CAD_H)
	<<tempfile.bat 
	@echo off 
	start /wait hcw /C /E /M "hlp\$(InputName).hpj" 
	if errorlevel 1 goto :Error 
	if not exist "hlp\$(InputName).hlp" goto :Error 
	copy "hlp\$(InputName).hlp" $(OutDir) 
	goto :done 
	:Error 
	echo hlp\$(InputName).hpj(1) : error: 
	type "hlp\$(InputName).log" 
	:done 
<< 
	

!ENDIF 

SOURCE=.\cad.odl

!IF  "$(CFG)" == "cad - Win32 Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\cad.tlb" /win32 

"$(OUTDIR)\cad.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "cad - Win32 Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\cad.tlb" /win32 

"$(OUTDIR)\cad.tlb" : $(SOURCE) "$(OUTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\cad.rc

!IF  "$(CFG)" == "cad - Win32 Release"


"$(INTDIR)\cad.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\cad.res" /i "Release" /d "NDEBUG" /d "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "cad - Win32 Debug"


"$(INTDIR)\cad.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\cad.res" /i "Debug" /d "_DEBUG" /d "_AFXDLL" $(SOURCE)


!ENDIF 

SOURCE=.\CadAddIn.idl

!IF  "$(CFG)" == "cad - Win32 Release"

MTL_SWITCHES=/nologo /D "NDEBUG" /tlb "$(OUTDIR)\CadAddIn.tlb" /win32 

"$(INTDIR)\CadAddIn.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "cad - Win32 Debug"

MTL_SWITCHES=/nologo /D "_DEBUG" /tlb "$(OUTDIR)\CadAddIn.tlb" /win32 

"$(INTDIR)\CadAddIn.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\CadAutoCamera.cpp

"$(INTDIR)\CadAutoCamera.obj"	"$(INTDIR)\CadAutoCamera.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\CadAutoCanvas.cpp

"$(INTDIR)\CadAutoCanvas.obj"	"$(INTDIR)\CadAutoCanvas.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\CadAutoCollection.cpp

"$(INTDIR)\CadAutoCollection.obj"	"$(INTDIR)\CadAutoCollection.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\CadAutoDrawing.cpp

"$(INTDIR)\CadAutoDrawing.obj"	"$(INTDIR)\CadAutoDrawing.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\CadAutoDrawingCollection.cpp

"$(INTDIR)\CadAutoDrawingCollection.obj"	"$(INTDIR)\CadAutoDrawingCollection.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\CadAutoEdit.cpp

"$(INTDIR)\CadAutoEdit.obj"	"$(INTDIR)\CadAutoEdit.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\CAdAutoShape.cpp

"$(INTDIR)\CAdAutoShape.obj"	"$(INTDIR)\CAdAutoShape.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\CadAutoSurface.cpp

"$(INTDIR)\CadAutoSurface.obj"	"$(INTDIR)\CadAutoSurface.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\CadAutoTransform.cpp

"$(INTDIR)\CadAutoTransform.obj"	"$(INTDIR)\CadAutoTransform.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\CadAutoUtils.cpp

"$(INTDIR)\CadAutoUtils.obj"	"$(INTDIR)\CadAutoUtils.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\CadAutoVector.cpp

"$(INTDIR)\CadAutoVector.obj"	"$(INTDIR)\CadAutoVector.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\CadAutoWnd.cpp

"$(INTDIR)\CadAutoWnd.obj"	"$(INTDIR)\CadAutoWnd.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\cadDoc.cpp

"$(INTDIR)\cadDoc.obj"	"$(INTDIR)\cadDoc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\cadView.cpp

"$(INTDIR)\cadView.obj"	"$(INTDIR)\cadView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\CAM.cpp

"$(INTDIR)\CAM.obj"	"$(INTDIR)\CAM.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\CameraDlg.cpp

"$(INTDIR)\CameraDlg.obj"	"$(INTDIR)\CameraDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Cercle.cpp

"$(INTDIR)\Cercle.obj"	"$(INTDIR)\Cercle.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\ChamfD.cpp

"$(INTDIR)\ChamfD.obj"	"$(INTDIR)\ChamfD.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Chamfer.cpp

"$(INTDIR)\Chamfer.obj"	"$(INTDIR)\Chamfer.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\ChFi.cpp

"$(INTDIR)\ChFi.obj"	"$(INTDIR)\ChFi.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Click.cpp

"$(INTDIR)\Click.obj"	"$(INTDIR)\Click.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\CLineSty.cpp

"$(INTDIR)\CLineSty.obj"	"$(INTDIR)\CLineSty.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\ColorD.cpp

"$(INTDIR)\ColorD.obj"	"$(INTDIR)\ColorD.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Command.cpp

"$(INTDIR)\Command.obj"	"$(INTDIR)\Command.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\CPaperSize.cpp

"$(INTDIR)\CPaperSize.obj"	"$(INTDIR)\CPaperSize.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\CTreeCtrl.cpp

!IF  "$(CFG)" == "cad - Win32 Release"


"$(INTDIR)\CTreeCtrl.obj"	"$(INTDIR)\CTreeCtrl.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


!ELSEIF  "$(CFG)" == "cad - Win32 Debug"

!ENDIF 

SOURCE=.\CustomSheet.cpp

"$(INTDIR)\CustomSheet.obj"	"$(INTDIR)\CustomSheet.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\CustomWidth.cpp

"$(INTDIR)\CustomWidth.obj"	"$(INTDIR)\CustomWidth.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\CVector.cpp

"$(INTDIR)\CVector.obj"	"$(INTDIR)\CVector.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Dim.cpp

"$(INTDIR)\Dim.obj"	"$(INTDIR)\Dim.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\DimA.cpp

"$(INTDIR)\DimA.obj"	"$(INTDIR)\DimA.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\DimL.cpp

"$(INTDIR)\DimL.obj"	"$(INTDIR)\DimL.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\DlgCap.cpp

"$(INTDIR)\DlgCap.obj"	"$(INTDIR)\DlgCap.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Dot.cpp

"$(INTDIR)\Dot.obj"	"$(INTDIR)\Dot.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Draw.cpp

"$(INTDIR)\Draw.obj"	"$(INTDIR)\Draw.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\DrawWnd.cpp

"$(INTDIR)\DrawWnd.obj"	"$(INTDIR)\DrawWnd.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Edge.cpp

"$(INTDIR)\Edge.obj"	"$(INTDIR)\Edge.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\EditParse.cpp

"$(INTDIR)\EditParse.obj"	"$(INTDIR)\EditParse.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Face.cpp

"$(INTDIR)\Face.obj"	"$(INTDIR)\Face.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\FFD.cpp

"$(INTDIR)\FFD.obj"	"$(INTDIR)\FFD.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Figure.cpp

"$(INTDIR)\Figure.obj"	"$(INTDIR)\Figure.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\geometry.cpp

"$(INTDIR)\geometry.obj"	"$(INTDIR)\geometry.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\GridPag.cpp

"$(INTDIR)\GridPag.obj"	"$(INTDIR)\GridPag.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\GridPage.cpp

"$(INTDIR)\GridPage.obj"	"$(INTDIR)\GridPage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Image.cpp

"$(INTDIR)\Image.obj"	"$(INTDIR)\Image.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Imagex.cpp

"$(INTDIR)\Imagex.obj"	"$(INTDIR)\Imagex.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\InfoBar.cpp

"$(INTDIR)\InfoBar.obj"	"$(INTDIR)\InfoBar.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Inter.cpp

"$(INTDIR)\Inter.obj"	"$(INTDIR)\Inter.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\LayBar.cpp

"$(INTDIR)\LayBar.obj"	"$(INTDIR)\LayBar.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Layerad.cpp

"$(INTDIR)\Layerad.obj"	"$(INTDIR)\Layerad.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\LayerD.cpp

"$(INTDIR)\LayerD.obj"	"$(INTDIR)\LayerD.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\LayList.cpp

"$(INTDIR)\LayList.obj"	"$(INTDIR)\LayList.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\LComboBox.cpp

"$(INTDIR)\LComboBox.obj"	"$(INTDIR)\LComboBox.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Libdialog.cpp

"$(INTDIR)\Libdialog.obj"	"$(INTDIR)\Libdialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\LibS.cpp

"$(INTDIR)\LibS.obj"	"$(INTDIR)\LibS.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\LightD.cpp

"$(INTDIR)\LightD.obj"	"$(INTDIR)\LightD.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Line.cpp

"$(INTDIR)\Line.obj"	"$(INTDIR)\Line.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\LineAgain.cpp

"$(INTDIR)\LineAgain.obj"	"$(INTDIR)\LineAgain.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\LineBar.cpp

"$(INTDIR)\LineBar.obj"	"$(INTDIR)\LineBar.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Linestyle.cpp

"$(INTDIR)\Linestyle.obj"	"$(INTDIR)\Linestyle.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\MainFrm.cpp

"$(INTDIR)\MainFrm.obj"	"$(INTDIR)\MainFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Matrix1.cpp

"$(INTDIR)\Matrix1.obj"	"$(INTDIR)\Matrix1.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\MClick.cpp

"$(INTDIR)\MClick.obj"	"$(INTDIR)\MClick.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Memento.cpp

"$(INTDIR)\Memento.obj"	"$(INTDIR)\Memento.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Mesh.cpp

"$(INTDIR)\Mesh.obj"	"$(INTDIR)\Mesh.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Mouse.cpp

"$(INTDIR)\Mouse.obj"	"$(INTDIR)\Mouse.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\MultVar.cpp

"$(INTDIR)\MultVar.obj"	"$(INTDIR)\MultVar.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\NumCopy.cpp

"$(INTDIR)\NumCopy.obj"	"$(INTDIR)\NumCopy.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\OBJEdit.cpp

"$(INTDIR)\OBJEdit.obj"	"$(INTDIR)\OBJEdit.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Observer.cpp

"$(INTDIR)\Observer.obj"	"$(INTDIR)\Observer.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Operation.cpp

"$(INTDIR)\Operation.obj"	"$(INTDIR)\Operation.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Optionsheet.cpp

"$(INTDIR)\Optionsheet.obj"	"$(INTDIR)\Optionsheet.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\OwnCombo.cpp

"$(INTDIR)\OwnCombo.obj"	"$(INTDIR)\OwnCombo.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\OwnList.cpp

"$(INTDIR)\OwnList.obj"	"$(INTDIR)\OwnList.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\PaperPag.cpp

"$(INTDIR)\PaperPag.obj"	"$(INTDIR)\PaperPag.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\PaperPage.cpp

"$(INTDIR)\PaperPage.obj"	"$(INTDIR)\PaperPage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\ParseDlg.cpp

"$(INTDIR)\ParseDlg.obj"	"$(INTDIR)\ParseDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Parser.cpp

"$(INTDIR)\Parser.obj"	"$(INTDIR)\Parser.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\ParserFloat.cpp

"$(INTDIR)\ParserFloat.obj"	"$(INTDIR)\ParserFloat.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\ParserObject.cpp

"$(INTDIR)\ParserObject.obj"	"$(INTDIR)\ParserObject.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\ParserVar.cpp

"$(INTDIR)\ParserVar.obj"	"$(INTDIR)\ParserVar.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\ParserVerb.cpp

"$(INTDIR)\ParserVerb.obj"	"$(INTDIR)\ParserVerb.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Pattern.cpp

"$(INTDIR)\Pattern.obj"	"$(INTDIR)\Pattern.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\PatternA.cpp
SOURCE=.\PGrid.cpp

"$(INTDIR)\PGrid.obj"	"$(INTDIR)\PGrid.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Plane.cpp

"$(INTDIR)\Plane.obj"	"$(INTDIR)\Plane.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\PopBar.cpp

"$(INTDIR)\PopBar.obj"	"$(INTDIR)\PopBar.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\PropPage.cpp
SOURCE=.\QLine.cpp

"$(INTDIR)\QLine.obj"	"$(INTDIR)\QLine.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\QuadTree.cpp

"$(INTDIR)\QuadTree.obj"	"$(INTDIR)\QuadTree.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Quaternion.cpp

"$(INTDIR)\Quaternion.obj"	"$(INTDIR)\Quaternion.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Ray.cpp

"$(INTDIR)\Ray.obj"	"$(INTDIR)\Ray.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\RecArray.cpp

"$(INTDIR)\RecArray.obj"	"$(INTDIR)\RecArray.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\RecColor.cpp

"$(INTDIR)\RecColor.obj"	"$(INTDIR)\RecColor.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\RecPattern.cpp

"$(INTDIR)\RecPattern.obj"	"$(INTDIR)\RecPattern.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Rectangle.cpp

"$(INTDIR)\Rectangle.obj"	"$(INTDIR)\Rectangle.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\RegDialog.cpp

"$(INTDIR)\RegDialog.obj"	"$(INTDIR)\RegDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Register.cpp

"$(INTDIR)\Register.obj"	"$(INTDIR)\Register.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Render.cpp

"$(INTDIR)\Render.obj"	"$(INTDIR)\Render.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\RTFACTN.CPP

"$(INTDIR)\RTFACTN.OBJ"	"$(INTDIR)\RTFACTN.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Rtfreadr.cpp

"$(INTDIR)\Rtfreadr.obj"	"$(INTDIR)\Rtfreadr.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Ruler1.cpp

"$(INTDIR)\Ruler1.obj"	"$(INTDIR)\Ruler1.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\SmoothD.cpp

"$(INTDIR)\SmoothD.obj"	"$(INTDIR)\SmoothD.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Snap.cpp

"$(INTDIR)\Snap.obj"	"$(INTDIR)\Snap.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Splash.cpp

"$(INTDIR)\Splash.obj"	"$(INTDIR)\Splash.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Spline.cpp

"$(INTDIR)\Spline.obj"	"$(INTDIR)\Spline.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\SplineProp.cpp
SOURCE=.\State.cpp

"$(INTDIR)\State.obj"	"$(INTDIR)\State.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "cad - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /Zd /I "C:\Program Files\HTML Help Workshop\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\cad.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\cad.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "cad - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /GX /Z7 /Od /I "C:\Program Files\HTML Help Workshop\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FAcs /Fa"$(INTDIR)\\" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\cad.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\cad.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Subject.cpp

"$(INTDIR)\Subject.obj"	"$(INTDIR)\Subject.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\SubWnd.cpp

"$(INTDIR)\SubWnd.obj"	"$(INTDIR)\SubWnd.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\TextCad.cpp

"$(INTDIR)\TextCad.obj"	"$(INTDIR)\TextCad.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\textd.cpp

"$(INTDIR)\textd.obj"	"$(INTDIR)\textd.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\TextDi.cpp

"$(INTDIR)\TextDi.obj"	"$(INTDIR)\TextDi.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\ThickD.cpp

"$(INTDIR)\ThickD.obj"	"$(INTDIR)\ThickD.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\TipDlg.cpp

"$(INTDIR)\TipDlg.obj"	"$(INTDIR)\TipDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\TransDlg.cpp

"$(INTDIR)\TransDlg.obj"	"$(INTDIR)\TransDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Translate.cpp

"$(INTDIR)\Translate.obj"	"$(INTDIR)\Translate.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Triangle.cpp

"$(INTDIR)\Triangle.obj"	"$(INTDIR)\Triangle.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\TVector.cpp

"$(INTDIR)\TVector.obj"	"$(INTDIR)\TVector.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\TxtED.cpp

"$(INTDIR)\TxtED.obj"	"$(INTDIR)\TxtED.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Unclick.cpp

"$(INTDIR)\Unclick.obj"	"$(INTDIR)\Unclick.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Vector.cpp

"$(INTDIR)\Vector.obj"	"$(INTDIR)\Vector.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Vectorm.cpp

"$(INTDIR)\Vectorm.obj"	"$(INTDIR)\Vectorm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Vectorp.cpp

"$(INTDIR)\Vectorp.obj"	"$(INTDIR)\Vectorp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Vectorv.cpp

"$(INTDIR)\Vectorv.obj"	"$(INTDIR)\Vectorv.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Verb.cpp

"$(INTDIR)\Verb.obj"	"$(INTDIR)\Verb.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Vertex.cpp

"$(INTDIR)\Vertex.obj"	"$(INTDIR)\Vertex.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Zoombar.cpp

"$(INTDIR)\Zoombar.obj"	"$(INTDIR)\Zoombar.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\ZoomD.cpp

"$(INTDIR)\ZoomD.obj"	"$(INTDIR)\ZoomD.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\cad.pch"


SOURCE=.\Resource.h

!IF  "$(CFG)" == "cad - Win32 Release"

TargetName=cad
InputPath=.\Resource.h

".\hlp\cad.hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
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
<< 
	

!ELSEIF  "$(CFG)" == "cad - Win32 Debug"

TargetName=cad
InputPath=.\Resource.h

".\hlp\cad.hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
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
<< 
	

!ENDIF 

SOURCE=.\hlp\cad.cnt

!IF  "$(CFG)" == "cad - Win32 Release"

OutDir=.\Release
InputPath=.\hlp\cad.cnt
InputName=cad

"$(INTDIR)\cad.cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy "hlp\$(InputName).cnt" $(OutDir)
<< 
	

!ELSEIF  "$(CFG)" == "cad - Win32 Debug"

OutDir=.\Debug
InputPath=.\hlp\cad.cnt
InputName=cad

"$(INTDIR)\cad.cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	copy "hlp\$(InputName).cnt" $(OutDir)
<< 
	

!ENDIF 


!ENDIF 

