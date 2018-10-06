#pragma once
#include "CShape.h"
class CEllipse : public CShape
{
public:
	CEllipse() {}
	CEllipse(CPoint p1, CPoint p2) {
		m_PointStart.SetX(p1.GetX());
		m_PointStart.SetY(p1.GetY());
		m_PointEnd.SetX(p2.GetX());
		m_PointEnd.SetY(p2.GetY());
	}
	~CEllipse() {}
	virtual void Draw(HDC hdc)
	{
		m_Style->SetHDCPen(hdc);
		if (!(m_PointStart.GetX() == m_PointEnd.GetX() && m_PointStart.GetY() == m_PointEnd.GetY()))
		{
			//SetBkMode(hdc, TRANSPARENT);
			//SetBkColor(hdc, RGB(0, 0, 0));
			SelectObject(hdc, (HBRUSH)m_Style->GetBackgroundColor());

			Ellipse(hdc, m_PointStart.GetX(), m_PointStart.GetY(), m_PointEnd.GetX(), m_PointEnd.GetY());
		}
	}
	virtual CShape* Clone() { return new CEllipse(*this); }
};
