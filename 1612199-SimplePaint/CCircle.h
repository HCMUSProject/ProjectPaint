#pragma once
#include "CEllipse.h"
class CCircle : public CEllipse
{
public:
	CCircle() {}
	CCircle(CPoint p1, CPoint p2) {
		/*m_PointStart = p1;
		m_PointEnd = p2;*/
		m_PointStart.SetX(p1.GetX());
		m_PointStart.SetY(p1.GetY());
		// hinh tron thi x=y
		m_PointEnd.SetX(p2.GetY());
		m_PointEnd.SetY(p2.GetY());
	}
	~CCircle() {}
	void Draw(HDC hdc)
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
	CShape* Clone() { return new CCircle(*this); }
};

