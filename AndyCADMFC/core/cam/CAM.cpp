// CAM.cpp: implementation of the CCAM class.
//
//////////////////////////////////////////////////////////////////////

#include "../cam/CAM.h"
#include "../tvector/CTVector.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//CVector CCAM::camor,CCAM::target,CCAM::vrx,CCAM::vry,CCAM::vrz;
float CCAM::zoom_r=1;
float CCAM::zoom_pr=1;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCAM::CCAM()
{
	fov=39.598;
	float f=pi*fov/180;
	float zoomy=1/tan(f/2);
	CVector::n=-CVector::Sy*zoomy/2;
//	zoom_r=1;



}

CCAM::~CCAM()
{

}
void CCAM::Rotate(int sens,CVector prevpoint,CVector postpoint,bool b)
{
	CTVector tvec;
    CVector v;
	CVector v00(0,0,0,1);
	CVector cen=v.getcamor();
	cen=camor;
	if(!b)
		tvec.Translate(-worldor);
	else
		{
		tvec.pushTransform();
		tvec.pushUnit();
//		tvec.Translate(-camor);
		}



	double alphab=v.argu(postpoint.camxyz())-v.argu(prevpoint.camxyz());//-argu(piv);

	alphab/=1000;

	if(sens==31)
	{
	tvec.TRotatex(alphab*100);
	}else
	if(sens==32)
	{
	tvec.TRotatey(alphab*100);
	}
	else if(sens==33)
	{
	tvec.TRotate(alphab*100);
	}
	else if(sens==00)
	{
	tvec.TRotate(0.100);
	}else
	if(sens==01)
	{
	tvec.TRotate(-0.100);
	}else
	if(sens==10)
	{
	tvec.TRotatey(0.100);
	}else
	if(sens==11)
	{
	tvec.TRotatey(-0.100);
	}else
	if(sens==20)
	{
	tvec.TRotatex(0.100);
	}else
	if(sens==21)
	{
	tvec.TRotatex(-0.100);
	}

//	v.assign(cen,camor);
	if(!b)
		{
		tvec.Translate(worldor);
		tvec.endT();
		}
	else
		{
//		tvec.Translate(camor);
		tvec.endT();
		vrx.assign(vrx);
		vry.assign(vry);
		vrz.assign(vrz);
		tvec.popTransform();
		vrx=vrx/absc(vrx);
		vry=vry/absc(vry);
		vrz=vrz/absc(vrz);
		CTVector cam;
		cam.setCam(vrx,vry,vrz,camor);
		target=camor+vrz;

		}
}

void CCAM::Rotate(int sens,float angle,bool b)
{
	CTVector tvec;
    CVector v;
	CVector v00(0,0,0,1);
	CVector cen=v.getcamor();
	cen=camor;
	if(!b)
		tvec.Translate(-worldor);
	else
		{
		tvec.pushTransform();
		tvec.pushUnit();
		}

	double alphab=angle;

	if(sens==1)
	{
	tvec.TRotatex(alphab);
	}else
	if(sens==2)
	{
	tvec.TRotatey(alphab);
	}
	else if(sens==3)
	{
	tvec.TRotate(alphab);
	}

	if(!b)
		{
		tvec.Translate(worldor);
		tvec.endT();
		}
	else
		{
		tvec.endT();
		vrx.assign(vrx);
		vry.assign(vry);
		vrz.assign(vrz);
		tvec.popTransform();
		vrx=vrx/absc(vrx);
		vry=vry/absc(vry);
		vrz=vrz/absc(vrz);
		CTVector cam;
		cam.setCam(vrx,vry,vrz,camor);
		target=camor+vrz;
		}
}

void CCAM::Translate(int sens,CVector prevpoint,CVector postpoint)
{
	float b;
	CTVector tvec;

	CVector vo=camor;

//	vo=CVector(0,0,0);
	if(prevpoint!=postpoint)
	{
		CVector v1=postpoint-prevpoint,v;

		CPoint po(postpoint);
		CPoint pr(prevpoint);
		if(sens==0)
		{
			b=po.y-pr.y;
			vo.y=camor.y-b;
			b=po.x-pr.x;
			vo.x=camor.x-b;
		}
		else if(sens==1)
		{
			b=po.y-pr.y;
			vo.y=camor.y-b;
		}
		else if(sens==2)
		{
			b=po.x-pr.x;
			vo.x=camor.x-b;
//			b=po-pr;
//			vo.z=camor.z-b;
		}else
		{
			CVector vb=po-pr;
			vo=camor-vb;
		}

	}
	else
	{
		b=20;
		if(sens==00)
		{
			vo=vo-vrx*b;
		}
		else if(sens==01)
		{
			vo=vo+vrx*b;
		}
		else if(sens==10)
		{
			vo=vo-vry*b;
		}
		else if(sens==11)
		{
			vo=vo+vry*b;

		}
		else if(sens==20)
		{
			b=5;
			vo=vo+vrz*b;

		}
		else if(sens==21)
		{
			b=5;
			vo=vo-vrz*b;
		}
	}
		CTVector cam;
		cam.setCam(vrx,vry,vrz,vo);
		CVector h;
		h=h.getcamor();
		camor=vo;
		target=camor+vrz;
	
}


void CCAM::Translate(CVector v)
{
	CTVector tvec;

	CVector vo=camor+v;

//	vo=vo+vrx*v.x+vry*v.y+vrz*v.z;

	CTVector cam;
	cam.setCam(vrx,vry,vrz,vo);
	camor=vo;
	target=camor+vrz;
}


void CCAM::draw(CDC *hdc)
{

}
void CCAM::copy(const CShape *fig)
{
	CCAM* cam=(CCAM*) fig;
	camor=cam->camor;
	fov=cam->fov;
	target=cam->target;
	vrx=cam->vrx;
	vry=cam->vry;
	vrz=cam->vrz;
	worldor=cam->worldor;
	xvec=cam->xvec;
	yvec=cam->yvec;
//	zoom_r=cam->zoom_r;
	zvec=cam->zvec;
	CShape::copy(fig);

}
CShape* CCAM::generateCopy()
{
	CCAM* l=new CCAM;
	l->copy(this);
	return l;

}

void CCAM::setPerspective(CAABB& box)
{
	CVector v;
	if(!v.getPerspective())
	{
	CTVector tvec;
	tvec.TRotatex(-pi/4);
	tvec.VendT();
	}
	else
	{
	CTVector tvec;
	tvec.VinitVect();
	initCam();
	}
	CVector vo;
	vo.setperspective();

}

void CCAM::setCamview(CString s,CAABB& box)
{
	CTVector tvec;
	tvec.InitCamView(s,box);
	if(s=="perpective")
	{
		CVector v;
		v.setperspective();
	}

}

void CCAM::setcamorigin(CAABB* b)
{
	if(b!=NULL)
	{
		Translate(b->center()-camor);//worldor=b->center();//camor.viewi();
  	}
	else
	{
		CVector v0(0,0,0);
		camor=v0;
		Translate(v0-camor);//worldor=b->center();//camor.viewi();
//		worldor.setcamor(v0);
//		worldor.getcamor();//getcooro();
	}

}
void CCAM::setcamtopleft(CAABB* b)
{
	if(b!=NULL)
	{
		CVector vc=b->center();
		CVector topleft=CPoint(0,0);
		Translate(b->center()-topleft);//worldor=b->center();//camor.viewi();
  	}
	else
	{
		CVector v0(0,0,0);
		camor=v0;
		Translate(v0-camor);//worldor=b->center();//camor.viewi();
//		worldor.setcamor(v0);
//		worldor.getcamor();//getcooro();
	}

}

void CCAM::setcam(CVector vo, CVector vt)
{
		CTVector cam;
		camor=vo;
		target=vt;
		CVector vz1=vt-vo,vx,vy,vz,vor;
		if(vt==vo) return;
		vz1=vz1/absc(vz1);
		vx=vx.getcamx();
		vy=vy.getcamy();
		vz=vz.getcamz();
		vx=vx.getcamx();
		vy=vy.getcamy();
		vrz=vz1;
		vry=vrx*vrz;
		vry=vry/absc(vry);
		vrx=vrz*vry;
		vrx=vrx/absc(vrx);

		vrz.w=0;
		vrz.w=0;
		vry.w=0;
		vrx.w=0;
		cam.setCam(vrx,vry,vrz,vo);
		vo.viewi();
}

void CCAM::setcamvector(CVector v,CVector t,CVector vright,CVector vup)
{
	camor=v;
	target=t;
	vrz=t;
	vrx=vright;
	vry=vup;
}

float CCAM::getzoom(){
	return CCAM::zoom_r;
}

 void CCAM::zoom(float zr)
{
	zoom_r=zr;
	CTVector t;
	t.Translate(-camor);
	t.Scale(1/zoom_pr,1/zoom_pr);
	t.Translate(camor);
	t.VendT();
	t.Translate(-camor);
	t.Scale(zr,zr);
	t.Translate(camor);
	t.VendT();
	zoom_pr=zoom_r;
	vrx=vrx.getcamx();
	vry=vry.getcamy();
	vrz=vrz.getcamz();
	CVector v;
	v=v.getcamor();
	t.setCam(vrx,vry,vrz,v);//worldor);
	camor=v;
	
/*  vrx=vrx/absc(vrx);
	vry=vry/absc(vry);
	vrz=vrz/absc(vrz);
	CTVector cam;*/
//	cam.setCam(vrx,vry,vrz,camor);
//	target=camor+vrz;
	
}

CVector CCAM::getcamor()
{
 return camor;
}

CVector CCAM::gettarget()
{
	return target;
}

void CCAM::setfov(float f)
{
	if(fov!=f)
	{
	fov=f;
	f=pi*f/180;
	float zoomy=1/tan(f/2);
	CVector::n=-CVector::Sy*zoomy/2;
	}
	else
	{
		float zoomy=-2*CVector::n/CVector::Sy;
		f=2*atan(1/zoomy);
		f=f*180/pi;
		fov=f;
	}
}

float CCAM::getfov()
{
	return fov;
}

void CCAM::setfarplane(float f)
{
	CVector::f=f;
}

void CCAM::setnearplane(float n)
{
	CVector::n=n;

}

float CCAM::getfarplane()
{
	return CVector::f;
}

float CCAM::getnearplane()
{
	return CVector::n;
}

void CCAM::initCam()
{
	CVector vx(1,0,0),vy(0,-1,0),vz(0,0,-1),vo(0,0,0);//CVector::f);
	setcamvector(vo,vz,vx,vy);
	camor=vo;
	zoom_r=1;
	zoom_pr=1;
	fov=39.598;

	CTVector cam;
	cam.setCam(vrx,vry,vrz,camor);

	float f=pi*fov/180;
	float zoomy=1/tan(f/2);
	CVector::n=-CVector::Sy*zoomy/2;

}

void CCAM::init(CShape *f)
{
	CVector vr=f->box.corner(3);//rop.BottomRight();
	vr.v2D();
	CVector vl=f->box.corner(0);//rop.TopLeft();
	vl.v2D();

	//This vector is to shift the screen to start at the bottom left of the bounding box
	//The x represent the bottom of the screen while the y is the left side
	//(check the CVEctor content
	CVector vv2(vr.getscrb().x,vr.getscrtop().y);

	//We move from the left top of the bounding box to the origin of the world
	//Coordinate then from the origin of the screen coordinate to the new screen
	//starting at the top left of the bounding box
	CTVector vt;
	vt.VpushTransform();
	vt.VpushUnit();
	vt.VinitVect();
	vt.VendT();


	vt.pushTransform();
	vt.pushUnit();
	vt.Translate(vl);//box.corner(0));
	vt.Translate(vv2);
	vt.endT();

}

void CCAM::undo()
{
	CTVector vt;
	vt.popTransform();
	vt.VpopTransform();

}

CVector CCAM::getScreen()
{
	CVector vr;
	CVector vv2(vr.getscrb().x,vr.getscrtop().y);
	return vv2;
}

void CCAM::initZoom()
{
	float f=1/zoom_r;
	zoom(f);
}

void CCAM::Update()
{
	CTVector t;
	t.setCam(vrx,vry,vrz,camor);//worldor);
}

void CCAM::openfile(CFile &file)
{
	camor.openfile(file);
	target.openfile(file);
	vrx.openfile(file);
	vry.openfile(file);
	vrz.openfile(file);
	worldor.openfile(file);
	file.Read(&fov,sizeof(float));
	file.Read(&zoom_r,sizeof(float));

}
void CCAM::savefile(CFile &file)
{
	camor.savefile(file);
	target.savefile(file);
	vrx.savefile(file);
	vry.savefile(file);
	vrz.savefile(file);
	worldor.savefile(file);
	file.Write(&fov,sizeof(float));
	file.Write(&zoom_r,sizeof(float));
	CTVector cam;
	cam.setCam(vrx,vry,vrz,camor);

	float f=pi*fov/180;
	float zoomy=1/tan(f/2);
	CVector::n=-CVector::Sy*zoomy/2;

}
LONG CCAM::Readfile(CFile &file)
{
	camor.Readfile(file);
	target.Readfile(file);
	vrx.Readfile(file);
	vry.Readfile(file);
	vrz.Readfile(file);
	worldor.Readfile(file);
	file.Seek(sizeof(float),CFile::current);
	return file.Seek(sizeof(float),CFile::current);
}