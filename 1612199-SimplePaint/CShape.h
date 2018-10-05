#pragma once
#include "CPoint.h"
#include "CStyle.h"
class CShape
{
protected:
	CPoint m_PointStart;
	CPoint m_PointEnd;
	CStyle* m_Style;

	
public:
	CShape(){}
	~CShape() { delete m_Style; }

	virtual void SetPointStart(CPoint P)
	{
		m_PointStart.SetX(P.GetX());
		m_PointStart.SetY(P.GetY());
	}
	virtual void SetPointEnd(CPoint P)
	{
		m_PointEnd.SetX(P.GetX());
		m_PointEnd.SetY(P.GetY());
	}
	virtual void SetStyle(CStyle st)
	{
		m_Style = new CStyle(st);
	}
	virtual void Draw(HDC hdc) = 0;
	virtual CShape* Clone() = 0;
};

