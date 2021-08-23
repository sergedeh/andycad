// Constraint.cpp: implementation of the CConstraint class.
//
//////////////////////////////////////////////////////////////////////

#include "Stdafx.h"
#include "Constraint.h"
#include "figure.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CConstraint::CConstraint(CFigure * _f1,CFigure * _f2)
{
	done=false;

	f1=_f1;
	f2=_f2;
	f1->setInterest(f2);
	if(f1!=f2)
		f2->setInterest(f1);
}

CConstraint::~CConstraint()
{

}
void CConstraint::PointToPoint(CFigure* _f1, float _i1, CFigure* _f2, float _i2)
{
	type=0;
	i1=f1->getPoint2(_i1)->un;
	i2=f2->getPoint2(_i2)->un;
	v1=f1->getPoint(i1);
	v2=f2->getPoint(i2);
	v=f1->getPoint(i1)-f2->getPoint(i2);
}
void CConstraint::EdgeToEdge(CFigure* _f1, float _i1, CFigure* _f2, float _i2)
{
	type=1;
	i1=_i1;
	i2=_i2;
	v1=f1->getEdge(i1);
	v2=f2->getEdge(i2);
	du=absc(v1)/absc(v2);
	da=argu(v2)-argu(v1);
}
void CConstraint::EdgeToPerpendicular(CFigure* _f1, float _i1, CFigure* _f2, float _i2)
{
	type=4;
	i1=_i1;
	i2=_i2;
	v1=f1->getEdge(i1);
	v2=f2->getEdge(i2);
	vedge10=f1->getEdge(i1,0);
	vedge11=f1->getEdge(i1,1);
	vedge20=f2->getEdge(i2,0);
	vedge21=f2->getEdge(i2,1);
//	du=absc(v1)/absc(v2);
	da=pi/2;
}
void CConstraint::EdgeToHorizontal(CFigure* _f1, float _i1)
{
	type=2;
	i1=_i1;
	v1=f1->getEdge(i1);
}
void CConstraint::EdgeToVertical(CFigure* _f1, float _i1)
{
	type=3;
	i1=_i1;
	v1=f1->getEdge(i1);
}
/*bool CConstraint::Update2(CFigure* _f1,float n)
{
	CVector v1;
	if((f1==_f1)&&(f1==f2))
	{
		float u1=f1->getSUVec();
		if(u1==i1)
		{
		v1=f1->getPoint(i1)-v;
		f2->TranslateTo(v1,i2);
		return true;
		}else if(u1==i2)
		{
		v1=f2->getPoint(i2)+v;
		f1->TranslateTo(v1,i1);
		return true;
		}
		return false;
	}

}*/
bool CConstraint::Update(CFigure* _f1)
{
	if(type==0)
		return UpdatePointtoPoint(_f1);
	if(type==1)
		return UpdateEdgetoEdge(_f1);
	if(type==2)
		return UpdateEdgeToHorizontal(_f1);
	if(type==3)
		return UpdateEdgeToVertical(_f1);
	if(type==4)
		return UpdateEdgeToPerpendicular(_f1);
	return false;
}
bool CConstraint::UpdateEdgeToHorizontal(CFigure* _f1)
{
	//need to take care of the case when the edge is translated=> the vector stay the same but the centroid is modified
	// and the case where the edge is rotated => the vector is changed
	// and the case where the edge is scaled => the vector is changed
	CVector v11;
	float ddu=0;
	float dda=0;
	float dda1=0;

		CVector v01=f1->getEdge(i1);
		dda=argu(v01);

		if(dda!=0)
		{
//		v11=v01-v;
		done=true;
//		v2=v01*(1/du);
		v1=polarc(absc(v01),0);
		v1=v1*cos(dda);
		f1->setEdge(v1,i1);
		return true;
		}
		return false;
}
bool CConstraint::UpdateEdgeToVertical(CFigure* _f1)
{
	//need to take care of the case when the edge is translated=> the vector stay the same but the centroid is modified
	// and the case where the edge is rotated => the vector is changed
	// and the case where the edge is scaled => the vector is changed
	CVector v11;
	float ddu=0;
	float dda=0;
	float dda1=0;

		CVector v01=f1->getEdge(i1);
		dda=argu(v01);

		if(dda!=0)
		{
//		v11=v01-v;
		done=true;
//		v2=v01*(1/du);
		v1=polarc(absc(v01),pi/2);
//		v1=v1*cos(dda);
		f1->setEdge(v1,i1);
		return true;
		}
		return false;
}
bool CConstraint::UpdateEdgeToPerpendicular(CFigure* _f1)
{
	//need to take care of the case when the edge is translated=> the vector stay the same but the centroid is modified
	// and the case where the edge is rotated => the vector is changed
	// and the case where the edge is scaled => the vector is changed
	CVector v11;
	float ddu=0;
	float dda=0;
	float dda1=0;

	if((f1==_f1)&&(f1==f2))
	{
//		float u1=f1->getSUVec();
		CVector v01=f1->getEdge(i1);
		CVector v02=f2->getEdge(i2);
		dda=argu(v02)-argu(v01);
		int i11=(i1<i2)?1:0;
		int i22=(i1<i2)?0:1;
		if(dda==pi/2) return false;
		if(v01!=v1)//u1==i1)
		{
//		v11=v01-v;
		done=true;
		CVector v001=f1->getEdge(i1,0);
		CVector v002=f1->getEdge(i1,1);
		if(v001!=vedge10)//||(v002!=vedge11))
		{
			v2=polarc(absc(v02),argu(v01)-da);
			vedge10=v001;
			i22=0;
		v1=v01;
		f2->setEdge(v2,i2,i22);
		vedge11=v002=f1->getEdge(i1,1);
		}else
			if(v002!=vedge11)
			{
			
			v2=polarc(absc(v02),argu(v01)-da);
			vedge11=v002;
			i22=1;
			v1=v01;
			f2->setEdge(v2,i2,i22);
			vedge10=v002=f1->getEdge(i1,0);
			}
/*		if(i22==0)
			v2=polarc(absc(v02),argu(v01)-da);
		else
			v2=polarc(absc(v02),argu(v01)+da);
*/
//		v1=v01;
//		f2->setEdge(v2,i2,i22);
		return true;
		}else if(v02!=v2)//u1==i2)
		{
//		v11=v02+v;
		done=true;
		try
		{
//		v1=v02*du;
		ddu=absc(v1);
//		v2=polarc(absc(v2),argu(v01)+da);
		CVector v001=f1->getEdge(i2,0);
		CVector v002=f1->getEdge(i2,1);
/*		if(v001!=vedge20)
		{
			v1=polarc(absc(v01),argu(v02)-da);
			vedge20=v001;
			i11=0;
		}else*/
			if(v002!=vedge21)//||(v001!=vedge20))
			{
			v1=polarc(absc(v01),argu(v02)-da);
			vedge21=v002;
			i11=1;
			v2=v02;
			f1->setEdge(v1,i1,i11);
			vedge20=f1->getEdge(i2,0);
			}

/*		if(i11==1)
			v1=polarc(absc(v01),argu(v02)+da);
		else
			v1=polarc(absc(v01),argu(v02)-da);
*/
		v2=v02;
		f1->setEdge(v1,i1,i11);
/*		CVector v11=f1->getEdge(i1);
		ddu=argu(v02)-argu(v11);
		if(ddu!=pi/2)
		{
			f1->setEdge(v01,i1);
		}*/
		}
		catch(...)
		{
			DWORD d=GetLastError();
		}
		return true;
		}
		return false;
	}
	CFigure * f3=(f1==_f1)?f1:(f2==_f1)?f2:NULL;
	if(!f3) return false;
	if(f3==f1)
	{
		CVector v01=f1->getPoint(i1);
		CVector v02=f2->getPoint(i2);
		if(v01!=v1)
		{
		v11=v01-v;
		done=true;
		v2=v11;
		v1=v01;
//		v1=f1->getPoint(i1)-v;
		f2->TranslateTo(v11,i2);
		return true;
		}else if(v02!=v2)//u1==i2)
		{
		v11=v02+v;
		done=true;
		v1=v11;
		v2=v02;
		f1->TranslateTo(v11,i1);
		return true;
		}
		return false;
	}
	else if(f3==f2)
	{
//		v1=f2->getPoint(i1)+v;
//		f1->TranslateTo(v1,i1);
//		return true;
		CVector v01=f1->getPoint(i1);
		CVector v02=f2->getPoint(i2);
		if(v01!=v1)
		{
		v11=v01-v;
		done=true;
		v2=v11;
		v1=v01;
//		v1=f1->getPoint(i1)-v;
		f2->TranslateTo(v11,i2);
		return true;
		}else if(v02!=v2)//u1==i2)
		{
		v11=v02+v;
		done=true;
		v1=v11;
		v2=v02;
		f1->TranslateTo(v11,i1);
		return true;
		}
		return false;
	}
	return false;
}
bool CConstraint::UpdateEdgetoEdge(CFigure* _f1)
{
	//need to take care of the case when the edge is translated=> the vector stay the same but the centroid is modified
	// and the case where the edge is rotated => the vector is changed
	// and the case where the edge is scaled => the vector is changed
	CVector v11;
	float ddu=0;
	float dda=0;
	float dda1=0;

	if((f1==_f1)&&(f1==f2))
	{
//		float u1=f1->getSUVec();
		CVector v01=f1->getEdge(i1);
		CVector v02=f2->getEdge(i2);

		if(v01!=v1)//u1==i1)
		{
//		v11=v01-v;
		done=true;
		v2=v01*(1/du);
		v2=polarc(absc(v2),argu(v01)+da);
		v1=v01;
		f2->setEdge(v2,i2);
		return true;
		}else if(v02!=v2)//u1==i2)
		{
//		v11=v02+v;
		done=true;
		try
		{
		v1=v02*du;
		ddu=absc(v1);
//		v2=polarc(absc(v2),argu(v01)+da);
		v1=polarc(absc(v1),argu(v02)-da);
		v2=v02;
		f1->setEdge(v1,i1);
		}
		catch(...)
		{
			DWORD d=GetLastError();
		}
		return true;
		}
		return false;
	}
	CFigure * f3=(f1==_f1)?f1:(f2==_f1)?f2:NULL;
	if(!f3) return false;
	if(f3==f1)
	{
		CVector v01=f1->getPoint(i1);
		CVector v02=f2->getPoint(i2);
		if(v01!=v1)
		{
		v11=v01-v;
		done=true;
		v2=v11;
		v1=v01;
//		v1=f1->getPoint(i1)-v;
		f2->TranslateTo(v11,i2);
		return true;
		}else if(v02!=v2)//u1==i2)
		{
		v11=v02+v;
		done=true;
		v1=v11;
		v2=v02;
		f1->TranslateTo(v11,i1);
		return true;
		}
		return false;
	}
	else if(f3==f2)
	{
//		v1=f2->getPoint(i1)+v;
//		f1->TranslateTo(v1,i1);
//		return true;
		CVector v01=f1->getPoint(i1);
		CVector v02=f2->getPoint(i2);
		if(v01!=v1)
		{
		v11=v01-v;
		done=true;
		v2=v11;
		v1=v01;
//		v1=f1->getPoint(i1)-v;
		f2->TranslateTo(v11,i2);
		return true;
		}else if(v02!=v2)//u1==i2)
		{
		v11=v02+v;
		done=true;
		v1=v11;
		v2=v02;
		f1->TranslateTo(v11,i1);
		return true;
		}
		return false;
	}
	return false;
}
bool CConstraint::UpdatePointtoPoint(CFigure* _f1)
{
	CVector v11;
	if((f1==_f1)&&(f1==f2))
	{
//		float u1=f1->getSUVec();
		CVector v01=f1->getPoint(i1);
		CVector v02=f2->getPoint(i2);

		if(v01!=v1)//u1==i1)
		{
		v11=v01-v;
		done=true;
		v2=v11;
		v1=v01;
		f2->TranslateTo(v11,i2);
		return true;
		}else if(v02!=v2)//u1==i2)
		{
		v11=v02+v;
		done=true;
		v1=v11;
		v2=v02;
		f1->TranslateTo(v11,i1);
		return true;
		}
		return false;
	}
	CFigure * f3=(f1==_f1)?f1:(f2==_f1)?f2:NULL;
	if(!f3) return false;
	if(f3==f1)
	{
		CVector v01=f1->getPoint(i1);
		CVector v02=f2->getPoint(i2);
		if(v01!=v1)
		{
		v11=v01-v;
		done=true;
		v2=v11;
		v1=v01;
//		v1=f1->getPoint(i1)-v;
		f2->TranslateTo(v11,i2);
		return true;
		}else if(v02!=v2)//u1==i2)
		{
		v11=v02+v;
		done=true;
		v1=v11;
		v2=v02;
		f1->TranslateTo(v11,i1);
		return true;
		}
		return false;
	}
	else if(f3==f2)
	{
//		v1=f2->getPoint(i1)+v;
//		f1->TranslateTo(v1,i1);
//		return true;
		CVector v01=f1->getPoint(i1);
		CVector v02=f2->getPoint(i2);
		if(v01!=v1)
		{
		v11=v01-v;
		done=true;
		v2=v11;
		v1=v01;
//		v1=f1->getPoint(i1)-v;
		f2->TranslateTo(v11,i2);
		return true;
		}else if(v02!=v2)//u1==i2)
		{
		v11=v02+v;
		done=true;
		v1=v11;
		v2=v02;
		f1->TranslateTo(v11,i1);
		return true;
		}
		return false;
	}
	return false;
}
