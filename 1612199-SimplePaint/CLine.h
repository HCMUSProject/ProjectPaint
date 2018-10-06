#pragma once
#include "CShape.h"
class CLine : public CShape
{
public:
	CLine(){}
	CLine(CPoint p1, CPoint p2) {
		m_PointStart.SetX(p1.GetX());
		m_PointStart.SetY(p1.GetY());
		m_PointEnd.SetX(p2.GetX());
		m_PointEnd.SetY(p2.GetY());
	}
	~CLine(){}
	void Draw(HDC hdc)
	{
		m_Style->SetHDCPen(hdc);
		if (!(m_PointStart.GetX() == m_PointEnd.GetX() && m_PointStart.GetY() == m_PointEnd.GetY()))
		{
			MoveToEx(hdc, m_PointStart.GetX(), m_PointStart.GetY(), NULL);
			LineTo(hdc, m_PointEnd.GetX(), m_PointEnd.GetY());
		}
	}
	CShape* Clone() { return new CLine(*this); }
};

