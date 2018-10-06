#pragma once
#include "CEllipse.h"
class CCircle : public CEllipse
{
public:
	CCircle() {}
	CCircle(CPoint p1, CPoint p2) {
		m_PointStart.SetX(p1.GetX());
		m_PointStart.SetY(p1.GetY());
		// hinh tron thi x=y
		m_PointEnd.SetX(p2.GetY());
		m_PointEnd.SetY(p2.GetY());
	}
	~CCircle() {}
	virtual CShape* Clone() { return new CCircle(*this); }
};

