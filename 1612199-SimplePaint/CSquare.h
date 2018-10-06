#pragma once
#include "CShape.h"
#include "CRectangle.h"
class CSquare : public CRectangle
{
public:
	CSquare() {}
	CSquare(CPoint p1, CPoint p2) {
		m_PointStart.SetX(p1.GetX());
		m_PointStart.SetY(p1.GetY());
		// hinh vuong thi x=y
		m_PointEnd.SetX(p2.GetY());
		m_PointEnd.SetY(p2.GetY());
	}
	~CSquare() {}
	
	CShape* Clone() { return new CSquare(*this); }
};

