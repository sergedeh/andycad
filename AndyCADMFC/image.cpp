// Image.cpp: implementation of the CImage2 class.
//
//////////////////////////////////////////////////////////////////////

#include "pch.h"
//#include "cad.h"
#include "Image.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImage2::CImage2()
{
	prevu=0;
 hBitmap=NULL;
 name="CImage2";
 im=NULL;
}

CImage2::~CImage2()
{

}
CImage2::CImage2(CDC *hdc,CFile &file)
{
	name="CImage2";
	openfile(hdc,file);
}


BOOL CImage2::LoadBitmap(CDC *hdc) 
{ 
	CFileDialog fl(true);
	
	fl.m_ofn.lpstrFilter=CString("JPEG Files(*.jpg)\0*.jpg\0JPEG Files(*.jpeg)\0*.jpeg\0)PNG Files(*.png)\0*.png\0TIFF Files(*.tiff)\0*.tiff\0");
	fl.m_ofn.nFilterIndex=1;
	if(fl.DoModal()==IDOK)
	{

		try
		{

/*			if((fl.GetFileExt()=="bmp")||(fl.GetFileExt()=="BMP"))
			{
				CString sd=fl.GetPathName();
				hBitmap = (HBITMAP)LoadImage(NULL, sd, IMAGE_BITMAP, 0, 0,\
							LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE); 
				
//				DWORD d=GetLastError();
				BITMAP bm;
				hB=new CBitmap;
				hB->Attach(hBitmap);
				setTexture("",hdc);
				UpdateTexture(hdc,hB);
				closecurve(CVector(1,1),hdc);

				delete hB;
				return true;

			}else*/
			{
				CString sd=fl.GetPathName(),sext;
				texture_file=sd;
				int len = texture_file.GetLength();
				int i;
				for (i = len-1; i >= 0; i--){
					if (texture_file[i] == '.'){
						sext=texture_file.Mid(i+1);
					}
				}

//				im=new CxImage(sd,CxImage::GetTypeIdFromName(sext));
				Load(sd,CxImage::GetTypeIdFromName(sext));
				Flip();
				//				im->Flip();

				
				rec->updatevcore();
				CRect rbox=rec->vbox;
			//	rbox.NormalizeRect();
				hdc->LPtoDP(&rbox);

					if(rbox.top<rbox.bottom)
					{
						int xc=rbox.top;
						rbox.top=rbox.bottom;
						rbox.bottom=xc;
					}

			//	hdc->LPtoDP(&rbox);
			//	Copy(*im);
//					int o=hdc->SetMapMode(MM_TEXT);
//					Draw(hdc->GetSafeHdc(),rbox.left,rbox.bottom,-1,-1,&rbox,true);//,CRect(0,0,1000,1000));//,0,true);
//					hdc->SetMapMode(o);

							int o=hdc->SetMapMode(MM_TEXT);
							Draw(hdc->GetSafeHdc(),rbox.left,rbox.bottom,(rbox.right-rbox.left),(rbox.top-rbox.bottom),0,true);//,CRect(0,0,1000,1000));//,0,true);
							hdc->SetMapMode(o);

				
				
//				HBITMAP hBitmap=im.MakeBitmap(hdc->GetSafeHdc());
//				hB=new CBitmap;
//				hB->Attach(hBitmap);
//				UpdateTexture(hdc,hB);
//				im.GetXDPI();
/*				LPBYTE alpha=im.AlphaGetPointer();
				LPBYTE lpBits=im.GetBits();
				
				pheight=im.GetHeight();
				pwidth=im.GetWidth();
				int np=im.GetBpp();
				if(mytext!=NULL)
					delete mytext;
					mytext=new col[pheight*pwidth];
					int i = 0;
					int x, y,q;
					int r,g,b;
					if(np>8)
					{
						if(alpha)
						{
							for(y =pheight-1;y>-1;y--)
							{
								for(x = 0; x < pwidth; x++)
								{
									q = x + y * pwidth;
									mytext[q].b=lpBits[i++];
									mytext[q].g=lpBits[i++];
									mytext[q].r=lpBits[i++];
									mytext[q].a=alpha[q];
								}
							}
							}else
							{
							for(y =pheight-1;y>-1;y--)
							{
								for(x = 0; x < pwidth; x++)
								{
									q = x + y * pwidth;
									mytext[q].b=lpBits[i++];
									mytext[q].g=lpBits[i++];
									mytext[q].r=lpBits[i++];
									mytext[q].a=255;
									if((mytext[q].b!=0)||(mytext[q].g!=0)||(mytext[q].r!=0))
									{
										int jk=0;
									}
								}
							}

						}
					}else
					{
						if(alpha)
						{
							for(y =pheight-1;y>-1;y--)
		//					for(y =0;y<pheight;y++)
							{
								for(x = 0; x < pwidth; x++)
								{
									q = x + y * pwidth;
									mytext[q].b=lpBits[i];
									mytext[q].g=lpBits[i];
									mytext[q].r=lpBits[i++];
									mytext[q].a=alpha[q];
									if((mytext[q].b!=0)||(mytext[q].g!=0)||(mytext[q].r!=0))
									{
				//					mytext[q].a=255;
									}
								}
							}
						}else
						{
							for(y =pheight-1;y>-1;y--)
		//					for(y =0;y<pheight;y++)
							{
								for(x = 0; x < pwidth; x++)
								{
									q = x + y * pwidth;
									mytext[q].b=mytext[q].g=mytext[q].r=lpBits[i++];
									mytext[q].a=255;
									if((mytext[q].b!=0)||(mytext[q].g!=0)||(mytext[q].r!=0))
									{
										int jk=0;
									}
								}
							}
						}

					}
*/				tex_vert_mode=image_texture;
//				mode_texture=wrap;
				mode_texture=none;

				closecurve(CVector(1,1),hdc);
				draw(hdc);
				return true;

			}
		}
		catch(CFileException * fx)
		{
			 TCHAR buf[255];
			 fx->GetErrorMessage(buf, 255);
			 CString strPrompt(buf);
			 AfxMessageBox(strPrompt);
		}

	}
	return false;
}
bool CImage2::draw(bool fPrevLine, CDC *hdc,CVector point)
{
	return rec->draw(fPrevLine,hdc,point);

}
void CImage2::copy(const CFigure *fig)
{
	CLine::copy(fig);
	CString sext;
	int len = texture_file.GetLength();
	int i;
	for (i = len-1; i >= 0; i--){
		if (texture_file[i] == '.'){
			sext=texture_file.Mid(i+1);
		}
	}
				tex_vert_mode=image_texture;
//				mode_texture=wrap;
				mode_texture=none;

//	Load(texture_file,CxImage::GetTypeIdFromName(sext));
//	Flip();
	vbox=fig->vbox;

}
void CImage2::draw(CDC *hdc)
{
	try{
	CPoint p1=CPoint(mesh.Vertex(1)->v)-CPoint(mesh.Vertex(0)->v);
	CVector v22(p1.x,p1.y,0);
	float ang=-argu(v22);
	double u=-ang*180/pi;
//	CxImage::Rotate2(prevu-u,NULL,CxImage::IM_BILINEAR,CxImage::OM_BACKGROUND,0,true,true);
	prevu=u;
/*			if(mode_texture==none)
			{
				Hatch(hdc);
			}
			mode_texture=wrap;*/
	mesh.displayEdge(hdc);
	CLine::draw(hdc);
	}catch(...)
	{
		AfxMessageBox(CString("Drawing issue"));
	}
}
////////////////////////////////////////////////////////////////////////////////
/**
 * Draws the image in the specified device context, with support for alpha channel, alpha palette, transparency, opacity.
 * \param hdc : destination device context
 * \param x,y : (optional) offset
 * \param cx,cy : (optional) size.
 *                 - If cx or cy are not specified (or less than 0), the normal width or height will be used
 *                 - If cx or cy are different than width or height, the image will be stretched
 *
 * \param pClipRect : limit the drawing operations inside a given rectangle in the output device context.
 * \param bSmooth : activates a bilinear filter that will enhance the appearence for zommed pictures.
 *                   Quite slow. Needs CXIMAGE_SUPPORT_INTERPOLATION.
 * \return true if everything is ok
 */
long CImage2::Draw(HDC hdc, long x, long y, long cx, long cy, RECT* pClipRect, bool bSmooth)
{
	if((pDib==0)||(hdc==0)||(cx==0)||(cy==0)||(!info.bEnabled)) return 0;

	if (cx < 0) cx = head.biWidth;
	if (cy < 0) cy = head.biHeight;
	bool bTransparent = info.nBkgndIndex >= 0;
	bool bAlpha = pAlpha != 0;

	//required for MM_ANISOTROPIC, MM_HIENGLISH, and similar modes [Greg Peatfield]
	int hdc_Restore = ::SaveDC(hdc);
	if (!hdc_Restore) 
		return 0;


	//find the smallest area to paint
	RECT clipbox,paintbox;
	GetClipBox(hdc,&clipbox);

	paintbox.top =min(clipbox.bottom,max(clipbox.top,y));
	paintbox.left =min(clipbox.right,max(clipbox.left,x));
	paintbox.right =max(clipbox.left,min(clipbox.right,x+cx));
	paintbox.bottom =max(clipbox.top,min(clipbox.bottom,y+cy));

	long destw = paintbox.right - paintbox.left;
	long desth = paintbox.bottom - paintbox.top;
	pwidth=destw;
	pheight=desth;
	int q=0;
	if(mytext!=NULL)
		delete mytext;
		mytext=new col[destw*desth];

	if (!(bTransparent || bAlpha || info.bAlphaPaletteEnabled)){
//		if (cx==head.biWidth && cy==head.biHeight){ //NORMAL
//			SetDIBitsToDevice(hdc, x, y, cx, cy, 0, 0, 0, cy,
//						info.pImage,(BITMAPINFO*)pDib,DIB_RGB_COLORS);
//		} else { //STRETCH
		{
		//pixel informations
			RGBQUAD c={0,0,0,0};
			//Preparing Bitmap Info
			BITMAPINFO bmInfo;
			memset(&bmInfo.bmiHeader,0,sizeof(BITMAPINFOHEADER));
			bmInfo.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
			bmInfo.bmiHeader.biWidth=destw;
			bmInfo.bmiHeader.biHeight=desth;
			bmInfo.bmiHeader.biPlanes=1;
			bmInfo.bmiHeader.biBitCount=24;
			BYTE *pbase;	//points to the final dib
			BYTE *pdst;		//current pixel from pbase
			BYTE *ppix;		//current pixel from image
			//get the background
			HDC TmpDC=CreateCompatibleDC(hdc);
			HBITMAP TmpBmp=CreateDIBSection(hdc,&bmInfo,DIB_RGB_COLORS,(void**)&pbase,0,0);
			HGDIOBJ TmpObj=SelectObject(TmpDC,TmpBmp);

			if (pbase){
				long xx,yy;
				long sx,sy;
				float dx,dy;
				BYTE *psrc;

				long ew = ((((24 * destw) + 31) / 32) * 4);
				long ymax = paintbox.bottom;
				long xmin = paintbox.left;
				float fx=(float)head.biWidth/(float)cx;
				float fy=(float)head.biHeight/(float)cy;

				for(yy=0;yy<desth;yy++){
					dy = head.biHeight-(ymax-yy-y)*fy;
					sy = max(0L,(long)floor(dy));
					psrc = info.pImage+sy*info.dwEffWidth;
					pdst = pbase+yy*ew;
					for(xx=0;xx<destw;xx++){
						dx = (xx+xmin-x)*fx;
						sx = max(0L,(long)floor(dx));
#if CXIMAGE_SUPPORT_INTERPOLATION
						if (bSmooth){
							if (fx > 1 && fy > 1) { 
								c = GetAreaColorInterpolated(dx - 0.5f, dy - 0.5f, fx, fy, CxImage::IM_BILINEAR, CxImage::OM_REPEAT); 
							} else { 
								c = GetPixelColorInterpolated(dx - 0.5f, dy - 0.5f, CxImage::IM_BILINEAR, CxImage::OM_REPEAT); 
							} 
						} else
#endif //CXIMAGE_SUPPORT_INTERPOLATION
						{
							if (head.biClrUsed){
								c=GetPaletteColor(GetPixelIndex(sx,sy));
							} else {
								ppix = psrc + sx*3;
								c.rgbBlue = *ppix++;
								c.rgbGreen= *ppix++;
								c.rgbRed  = *ppix;
							}
						}
						*pdst++=c.rgbBlue;
						*pdst++=c.rgbGreen;
						*pdst++=c.rgbRed;
						q = xx + yy * destw;
						mytext[q].b=c.rgbBlue;
						mytext[q].g=c.rgbGreen;
						mytext[q].r=c.rgbRed;
					}
				}
			}
			//paint the image & cleanup
//			SetDIBitsToDevice(hdc,paintbox.left,paintbox.top,destw,desth,0,0,0,desth,pbase,&bmInfo,0);
			DeleteObject(SelectObject(TmpDC,TmpObj));
			DeleteDC(TmpDC);
		}
	} else {	// draw image with transparent/alpha blending
	//////////////////////////////////////////////////////////////////
		//Alpha blend - Thanks to Florian Egel

		//pixel informations
		RGBQUAD c={0,0,0,0};
		RGBQUAD ct = GetTransColor();
		long* pc = (long*)&c;
		long* pct= (long*)&ct;
		long cit = GetTransIndex();
		long ci = 0;

		//Preparing Bitmap Info
		BITMAPINFO bmInfo;
		memset(&bmInfo.bmiHeader,0,sizeof(BITMAPINFOHEADER));
		bmInfo.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
		bmInfo.bmiHeader.biWidth=destw;
		bmInfo.bmiHeader.biHeight=desth;
		bmInfo.bmiHeader.biPlanes=1;
		bmInfo.bmiHeader.biBitCount=24;

		BYTE *pbase;	//points to the final dib
		BYTE *pdst;		//current pixel from pbase
		BYTE *ppix;		//current pixel from image

		//get the background
		HDC TmpDC=CreateCompatibleDC(hdc);
		HBITMAP TmpBmp=CreateDIBSection(hdc,&bmInfo,DIB_RGB_COLORS,(void**)&pbase,0,0);
		HGDIOBJ TmpObj=SelectObject(TmpDC,TmpBmp);
		BitBlt(TmpDC,0,0,destw,desth,hdc,paintbox.left,paintbox.top,SRCCOPY);

		if (pbase){
			long xx,yy,alphaoffset,ix,iy;
			BYTE a,a1,*psrc;
			long ew = ((((24 * destw) + 31) / 32) * 4);
			long ymax = paintbox.bottom;
			long xmin = paintbox.left;

			if (cx!=head.biWidth || cy!=head.biHeight){
				//STRETCH
				float fx=(float)head.biWidth/(float)cx;
				float fy=(float)head.biHeight/(float)cy;
				float dx,dy;
				long sx,sy;
				
				for(yy=0;yy<desth;yy++){
					dy = head.biHeight-(ymax-yy-y)*fy;
					sy = max(0L,(long)floor(dy));

					alphaoffset = sy*head.biWidth;
					pdst = pbase + yy*ew;
					psrc = info.pImage + sy*info.dwEffWidth;

					for(xx=0;xx<destw;xx++){
						dx = (xx+xmin-x)*fx;
						sx = max(0L,(long)floor(dx));
						q = xx + yy * destw;

						if (bAlpha) a=pAlpha[alphaoffset+sx]; else a=255;
						a =(BYTE)((a*(1+info.nAlphaMax))>>8);

						if (head.biClrUsed){
							ci = GetPixelIndex(sx,sy);
#if CXIMAGE_SUPPORT_INTERPOLATION
							if (bSmooth){
								if (fx > 1 && fy > 1) { 
									c = GetAreaColorInterpolated(dx - 0.5f, dy - 0.5f, fx, fy, CxImage::IM_BILINEAR, CxImage::OM_REPEAT); 
								} else { 
									c = GetPixelColorInterpolated(dx - 0.5f, dy - 0.5f, CxImage::IM_BILINEAR, CxImage::OM_REPEAT); 
								} 
							} else
#endif //CXIMAGE_SUPPORT_INTERPOLATION
							{
								c = GetPaletteColor(GetPixelIndex(sx,sy));
							}
							if (info.bAlphaPaletteEnabled){
								a = (BYTE)((a*(1+c.rgbReserved))>>8);
							}
						} else {
#if CXIMAGE_SUPPORT_INTERPOLATION
							if (bSmooth){
								if (fx > 1 && fy > 1) { 
									c = GetAreaColorInterpolated(dx - 0.5f, dy - 0.5f, fx, fy, CxImage::IM_BILINEAR, CxImage::OM_REPEAT); 
								} else { 
									c = GetPixelColorInterpolated(dx - 0.5f, dy - 0.5f, CxImage::IM_BILINEAR, CxImage::OM_REPEAT); 
								} 
							} else
#endif //CXIMAGE_SUPPORT_INTERPOLATION
							{
								ppix = psrc + sx*3;
								c.rgbBlue = *ppix++;
								c.rgbGreen= *ppix++;
								c.rgbRed  = *ppix;
							}
						}
						//if (*pc!=*pct || !bTransparent){
						//if ((head.biClrUsed && ci!=cit) || ((!head.biClrUsed||bSmooth) && *pc!=*pct) || !bTransparent){
						if ((head.biClrUsed && ci!=cit) || (!head.biClrUsed && *pc!=*pct) || !bTransparent){
							// DJT, assume many pixels are fully transparent or opaque and thus avoid multiplication
							if (a == 0) {			// Transparent, retain dest 
								mytext[q].b=*pdst++;
								mytext[q].g=*pdst++;
								mytext[q].r=*pdst++; 
							} else if (a == 255) {	// opaque, ignore dest 
								mytext[q].b=*pdst++= c.rgbBlue; 
								mytext[q].g=*pdst++= c.rgbGreen; 
								mytext[q].r=*pdst++= c.rgbRed; 
							} else {				// semi transparent 
								a1=(BYTE)~a;
								mytext[q].b=*pdst++=(BYTE)((*pdst * a1 + a * c.rgbBlue)>>8); 
								mytext[q].g=*pdst++=(BYTE)((*pdst * a1 + a * c.rgbGreen)>>8); 
								mytext[q].r=*pdst++=(BYTE)((*pdst * a1 + a * c.rgbRed)>>8); 
							} 
						} else {
								mytext[q].b=*pdst++;
								mytext[q].g=*pdst++;
								mytext[q].r=*pdst++; 
						}
					}
				}
			} else {
				//NORMAL
				iy=head.biHeight-ymax+y;
				for(yy=0;yy<desth;yy++,iy++){
					alphaoffset=iy*head.biWidth;
					ix=xmin-x;
					pdst=pbase+yy*ew;
					ppix=info.pImage+iy*info.dwEffWidth+ix*3;
					for(xx=0;xx<destw;xx++,ix++){
						q = xx + yy * destw;

						if (bAlpha) a=pAlpha[alphaoffset+ix]; else a=255;
						a = (BYTE)((a*(1+info.nAlphaMax))>>8);

						if (head.biClrUsed){
							ci = GetPixelIndex(ix,iy);
							c = GetPaletteColor((BYTE)ci);
							if (info.bAlphaPaletteEnabled){
								a = (BYTE)((a*(1+c.rgbReserved))>>8);
							}
						} else {
							c.rgbBlue = *ppix++;
							c.rgbGreen= *ppix++;
							c.rgbRed  = *ppix++;
						}

						//if (*pc!=*pct || !bTransparent){
						if ((head.biClrUsed && ci!=cit) || (!head.biClrUsed && *pc!=*pct) || !bTransparent){
							// DJT, assume many pixels are fully transparent or opaque and thus avoid multiplication
							if (a == 0) {			// Transparent, retain dest 
								mytext[q].b=*pdst++;
								mytext[q].g=*pdst++;
								mytext[q].r=*pdst++; 
							} else if (a == 255) {	// opaque, ignore dest 
								mytext[q].b=*pdst++= c.rgbBlue; 
								mytext[q].g=*pdst++= c.rgbGreen; 
								mytext[q].r=*pdst++= c.rgbRed; 
							} else {				// semi transparent 
								a1=(BYTE)~a;
								mytext[q].b=*pdst++=(BYTE)((*pdst * a1 + a * c.rgbBlue)>>8); 
								mytext[q].g=*pdst++=(BYTE)((*pdst * a1 + a * c.rgbGreen)>>8); 
								mytext[q].r=*pdst++=(BYTE)((*pdst * a1 + a * c.rgbRed)>>8); 
							} 
						} else {
								mytext[q].b=*pdst++;
								mytext[q].g=*pdst++;
								mytext[q].r=*pdst++; 
						}
					}
				}
			}
		}
		//paint the image & cleanup
//		SetDIBitsToDevice(hdc,paintbox.left,paintbox.top,destw,desth,0,0,0,desth,pbase,&bmInfo,0);
		DeleteObject(SelectObject(TmpDC,TmpObj));
		DeleteDC(TmpDC);
	}


	::RestoreDC(hdc,hdc_Restore);
	return 1;
}

void CImage2::setMove(bool mv,CVector pos)
{
	rec->setMove(mv,pos);

}
void CImage2::create(CVector pos)
{
	rec->create(pos);

}
bool CImage2::Hatch(CDC* hdc)
{
	CString sext;
	int len = texture_file.GetLength();
	int i;
	for (i = len-1; i >= 0; i--){
		if (texture_file[i] == '.'){
			sext=texture_file.Mid(i+1);
		}
	}

//				im=new CxImage(sd,CxImage::GetTypeIdFromName(sext));
	Load(texture_file,CxImage::GetTypeIdFromName(sext));
	Flip();
	//				im->Flip();

	
	updatevcore();
	CRect rbox=vbox;
//	rbox.NormalizeRect();
	hdc->LPtoDP(&rbox);

		if(rbox.top<rbox.bottom)
		{
			int xc=rbox.top;
			rbox.top=rbox.bottom;
			rbox.bottom=xc;
		}
//	hdc->LPtoDP(&rbox);
//	Copy(*im);
					int w = rbox.right - rbox.left;
					int h = rbox.top - rbox.bottom;
					int x,y,z;
					int bx=head.biWidth;
					int by=head.biHeight;
					double d=w*h;
					i=0;
					int _h=0;
					int u=0,v=0;
					int po=0;
					col* bigtext;
					bigtext=new col[w*h];
					try{
					for (y = 0 ; y < h ; y += by){
						if ((y+by)>h) by=h-y;
						z=bx;
						u=0;
						for (x = 0 ; x < w ; x += z){
							if ((x+z)>w) z=w-x;
							RECT r = {rbox.left + x,rbox.bottom + y,rbox.left + x + z,rbox.bottom + y + by};
							int o=hdc->SetMapMode(MM_TEXT);
							Draw(hdc->GetSafeHdc(),rbox.left+x,rbox.bottom+y,-1,-1,&r,true);//,CRect(0,0,1000,1000));//,0,true);
							for(i=0;i<pheight;i++){
								for(int j=0;j<pwidth;j++)
								{
									int q=j+i*pwidth;
									int hj=u*pwidth+v*w*pheight+j+i*w;
									if(hj>=d)
									{
										TRACE("Excess item");
										CString stg;
										stg.Format(_T("u is %d"),u);
										TRACE(stg);
										stg.Format(_T("v is %d"),v);
										TRACE(stg);
										stg.Format(_T("i is %d"),i);
										TRACE(stg);
										stg.Format(_T("j is %d"),j);
										TRACE(stg);
										stg.Format(_T("Total is %d"),hj);
										TRACE(stg);
										continue;

									}
									bigtext[u*pwidth+v*w*pheight+j+i*w]=mytext[q];
								}
							}
							hdc->SetMapMode(o);
							u++;
						//	Draw(hdc,rc->left + x, rc->top + y,-1,-1,&r);
						}
						v++;
					}
					}catch(...)
					{
					}
//					int ppwidth=pwidth,q,qq;
//					int ppheight=pheight;
					pwidth=w;
					pheight=h;
					d=w*h;
					if(mytext!=NULL)
						delete []mytext;
					mytext=new col[d];
//					u=0,v=0;
/*					for(int j=0;j<v;j++)
					{
						for(i=0;i<u;i++)
						{
							for(int yy=0;yy<ppheight;yy++)
							{
							for(int xx=0;xx<ppwidth;xx++)
							{
								qq=j*(ppwidth*ppheight)*u+i*(ppwidth*ppheight)+xx+yy*(ppwidth-1);
							q=i*(ppwidth-1)+xx+(yy+j*ppheight)*pwidth;
						//	i=u*(ppwidth*ppheight)+ppwidth*v+xx;
							mytext[q]=bigtext[qq];
							}
							}

						}
					}*/
					for(y=0;y<d;y++)
					{
							mytext[y]=bigtext[y];
					}
					try{
					delete []bigtext;
					}catch(...)
					{
					}
					
	return true;
}
bool CImage2::getCharge()
{
	if(rec->getCharge())
	{
	bool b=rec->getCharge();
//	mesh.copy(rec.getMesh());
	mesh.empty();
	CVector uv=rec->box.getParam(rec->ptbegin[0]);
	mesh.addVertex(new CVertex(rec->ptbegin[0],uv.x,uv.y));
	uv=rec->box.getParam(rec->ptbegin[1]);
	mesh.addVertex(new CVertex(rec->ptbegin[1],uv.x,uv.y));
	new CEdge(mesh.Vertex(mesh.Vcount()-2),mesh.Vertex(mesh.Vcount()-1),mesh.Ecount());

	uv=rec->box.getParam(rec->ptbegin[2]);
	mesh.addVertex(new CVertex(rec->ptbegin[2],uv.x,uv.y));
	new CEdge(mesh.Vertex(mesh.Vcount()-2),mesh.Vertex(mesh.Vcount()-1),mesh.Ecount());
	uv=rec->box.getParam(rec->ptbegin[3]);
	mesh.addVertex(new CVertex(rec->ptbegin[3],uv.x,uv.y));
	new CEdge(mesh.Vertex(mesh.Vcount()-2),mesh.Vertex(mesh.Vcount()-1),mesh.Ecount());
	new CEdge(mesh.Vertex(mesh.Vcount()-1),mesh.Vertex(mesh.Vcount()-4),mesh.Ecount());

	ptbegin=rec->ptbegin;
	ptend=rec->ptend;
	updatecore();
	mesh.updateBoxUV(rec->box);
	cl=true;
		return true;
	}
	else return false;
}

void CImage2::initL()
{
	if(mytext!=NULL)
	{
		delete mytext;
		mytext=NULL;
	}
	rec->initL();
}

void CImage2::setPtsBegin(CVector point)
{
	rec->setPtsBegin(point);
		
}


void CImage2::savefile(CDC *hdc,CFile &file)
{
	rec->savefile(file);
	CFigure::savefile(file);
}

void CImage2::openfile(CDC *hdc,CFile &file)
{
	rec=new CRectangle(file);
	CFigure::openfile(file);
	updatecore();
	name="CImage2";
//	draw(hdc);

}

HGLOBAL CImage2::ConvertDDBtoDIB(CBitmap *pBmp,CDC *hdc)
{

	BITMAP bm;
	BITMAPINFOHEADER bi;
	LPBITMAPINFO lpBi;
	DWORD dwSizeCT;
	DWORD dwDibLen;
	
	POSITION pos;
	CPalette *pPalOld;
	HGLOBAL hDib;
	
	pBmp->GetBitmap(&bm);
	bi.biSize=sizeof(BITMAPINFOHEADER);
	bi.biWidth=bm.bmWidth;
	bi.biHeight=bm.bmHeight;
	bi.biPlanes=bm.bmPlanes;
	bi.biBitCount=bm.bmPlanes*bm.bmBitsPixel;
	bi.biCompression=BI_RGB;
	bi.biSizeImage=0;
	bi.biXPelsPerMeter=0;
	bi.biYPelsPerMeter=0;
	bi.biClrUsed=0;
	bi.biClrImportant=0;
	
	dwSizeCT=GetColorTableSize(bi.biBitCount);
	dwDibLen=bi.biSize+dwSizeCT*sizeof(RGBQUAD);
	
	hDib=::GlobalAlloc(GHND, dwDibLen);
	lpBi=(LPBITMAPINFO)::GlobalLock(hDib);
	lpBi->bmiHeader=bi;

	
	VERIFY
	(
	::GetDIBits
	(
	hdc->GetSafeHdc(),
	(HBITMAP)pBmp->GetSafeHandle(),
	0,
	(WORD)bi.biHeight,
	NULL,
	lpBi,
	DIB_RGB_COLORS
	)
	);
	bi=lpBi->bmiHeader;
	::GlobalUnlock(hDib);
	if(bi.biSizeImage == 0)
	{
	bi.biSizeImage=WIDTHBYTES(bi.biBitCount*bi.biWidth)*bi.biHeight;
	}
	
	dwDibLen+=bi.biSizeImage;
	hDib=::GlobalReAlloc(hDib, dwDibLen, GHND);
	ASSERT(hDib);
	lpBi=(LPBITMAPINFO)::GlobalLock(hDib);
	ASSERT(hDib);

	VERIFY
	(
	::GetDIBits
	(
	hdc->GetSafeHdc(),
	(HBITMAP)pBmp->GetSafeHandle(),
	0,
	(WORD)bi.biHeight,
	(LPSTR)lpBi+sizeof(BITMAPINFOHEADER)+dwSizeCT*sizeof(RGBQUAD),
	lpBi,
	DIB_RGB_COLORS
	)
	);
	::GlobalUnlock(hDib);
	return hDib;
}

PBITMAPINFO CImage2::CreateBMPInfo(HBITMAP hBMP, bool set=true) 
 { 

	BITMAP bm;
	BITMAPINFOHEADER bi;
	LPBITMAPINFO lpBi;
	DWORD dwSizeCT;
	DWORD dwDibLen;
	
	PBITMAPINFO pbmi;
	WORD    cClrBits; 

	POSITION pos;
	CPalette *pPalOld;
	HGLOBAL hDib;

    // Retrieve the bitmap's color format, width, and height. 
    GetObject(hBMP, sizeof(BITMAP), (LPSTR)&bm); 


    // Convert the color format to a count of bits. 
    cClrBits =set?32:(WORD)(bm.bmPlanes * bm.bmBitsPixel); 
    if (cClrBits == 1) 
        cClrBits = 1; 
    else if (cClrBits <= 4) 
        cClrBits = 4; 
    else if (cClrBits <= 8) 
        cClrBits = 8; 
    else if (cClrBits <= 16) 
        cClrBits = 16; 
    else if (cClrBits <= 24) 
        cClrBits = 24; 
    else cClrBits = 32; 

    // Allocate memory for the BITMAPINFO structure. (This structure 
    // contains a BITMAPINFOHEADER structure and an array of RGBQUAD 
    // data structures.) 

     if ((cClrBits != 24)&&(cClrBits != 32)&&(cClrBits != 16)) 
         pbmi = (PBITMAPINFO) LocalAlloc(LPTR, 
                    sizeof(BITMAPINFOHEADER) + 
                    sizeof(RGBQUAD) * (1<< cClrBits)); 

     // There is no RGBQUAD array for the 24-bit-per-pixel format. 

     else 
         pbmi = (PBITMAPINFO) LocalAlloc(LPTR, 
                    sizeof(BITMAPINFOHEADER)); 


	pbmi->bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
	pbmi->bmiHeader.biWidth=bm.bmWidth;
	pbmi->bmiHeader.biHeight=bm.bmHeight;
	pbmi->bmiHeader.biPlanes=bm.bmPlanes;
	pbmi->bmiHeader.biBitCount=set?32:bm.bmPlanes*bm.bmBitsPixel;
	pbmi->bmiHeader.biCompression=BI_RGB;
	pbmi->bmiHeader.biSizeImage=WIDTHBYTES(pbmi->bmiHeader.biBitCount*pbmi->bmiHeader.biWidth)*pbmi->bmiHeader.biHeight;
	pbmi->bmiHeader.biXPelsPerMeter=0;
	pbmi->bmiHeader.biYPelsPerMeter=0;
	pbmi->bmiHeader.biClrUsed=0;
	pbmi->bmiHeader.biClrImportant=0;

	return pbmi;

}
void CImage2::CreateBMPFile(LPTSTR pszFile,HBITMAP hBMP, HDC hDC) 
 { 

    HANDLE hf;                 // file handle 
    BITMAPFILEHEADER hdr;       // bitmap file-header 
    PBITMAPINFOHEADER pbih;     // bitmap info-header 
    LPBYTE lpBits;              // memory pointer 
    DWORD dwTotal;              // total count of bytes 
    DWORD cb;                   // incremental count of bytes 
    BYTE *hp;                   // byte pointer 
    DWORD dwTmp; 

     
	PBITMAPINFO pbmi=CreateBMPInfo(hBMP);
    lpBits = (LPBYTE) GlobalAlloc(GMEM_FIXED, pbmi->bmiHeader.biSizeImage);


    // Retrieve the color table (RGBQUAD array) and the bits 
    // (array of palette indices) from the DIB. 
    GetDIBits(hDC, hBMP, 0, (WORD) pbmi->bmiHeader.biHeight, lpBits, pbmi,DIB_RGB_COLORS);

    // Create the .BMP file. 
    hf = CreateFile(pszFile, 
                   GENERIC_READ | GENERIC_WRITE, 
                   (DWORD) 0, 
                    NULL, 
                   CREATE_ALWAYS, 
                   FILE_ATTRIBUTE_NORMAL, 
                   (HANDLE) NULL); 

    hdr.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M" 
    // Compute the size of the entire file. 
    hdr.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) + 
                 pbmi->bmiHeader.biSize + pbmi->bmiHeader.biClrUsed 
                 * sizeof(RGBQUAD) + pbmi->bmiHeader.biSizeImage); 
    hdr.bfReserved1 = 0; 
    hdr.bfReserved2 = 0; 

    // Compute the offset to the array of color indices. 
    hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) + 
                    pbmi->bmiHeader.biSize + pbmi->bmiHeader.biClrUsed 
                    * sizeof (RGBQUAD); 

    // Copy the BITMAPFILEHEADER into the .BMP file. 
    WriteFile(hf, (LPVOID) &hdr, sizeof(BITMAPFILEHEADER), 
        (LPDWORD) &dwTmp,  NULL);

    // Copy the BITMAPINFOHEADER and RGBQUAD array into the file. 
    WriteFile(hf, (LPVOID)&pbmi->bmiHeader, sizeof(BITMAPINFOHEADER) 
                  + pbmi->bmiHeader.biClrUsed * sizeof (RGBQUAD), 
                  (LPDWORD) &dwTmp, ( NULL));

    // Copy the array of color indices into the .BMP file. 
    dwTotal = cb = pbmi->bmiHeader.biSizeImage; 
    hp = lpBits; 
    WriteFile(hf, (LPSTR) hp, (int) cb, (LPDWORD) &dwTmp,NULL) ; 

    // Close the .BMP file. 
     CloseHandle(hf); 

    // Free memory. 
    GlobalFree((HGLOBAL)lpBits);
}





DWORD CImage2::GetColorTableSize(WORD wBitCount)
{
	DWORD dwSizeCT;
	switch(wBitCount)
	{
		case 1:
		{
		dwSizeCT=2;
		break;
		}
		case 4:
		{
		dwSizeCT=16;
		break;
		}
		case 8:
		{
		dwSizeCT=256;
		break;
		}
		case 24:
		{
		dwSizeCT=0;
		}
		default: dwSizeCT=0;
	}
	return dwSizeCT;
}

void CImage2::drawTrans(CDC *hdc)
{
	CFigure::drawTrans(hdc);
}

 

