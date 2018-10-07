#pragma once
#include "CShape.h"
#include "CRectangle.h"
class CSquare : public CRectangle
{
public:
	CSquare() {}
	CSquare(CPoint p1, CPoint p2) {
		m_PointStart = p1;
		// hinh vuong thi x=y
		m_PointEnd.SetX(p2.GetY()- p1.GetY() + p1.GetX());
		m_PointEnd.SetY(p2.GetY());
	}
	CSquare(const CSquare &cs)
	{
		this->m_PointStart = cs.m_PointStart;
		this->m_PointEnd = cs.m_PointEnd;
		if (this->m_Style != NULL)
			delete this->m_Style;
		this->m_Style = new CStyle(*cs.m_Style);
	}
	~CSquare() {
		if (this->m_Style != NULL)
		{
			delete m_Style;
			m_Style = NULL;
		}
	}
	
	CShape* Clone() { return new CSquare(*this); }
};

