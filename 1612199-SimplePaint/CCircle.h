#pragma once
#include "CEllipse.h"
class CCircle : public CEllipse
{
public:
	CCircle() {}
	CCircle(CPoint p1, CPoint p2) {
		m_PointStart = p1;
		// hinh tron thi x=y
		m_PointEnd.SetX(p2.GetY() - p1.GetY() + p1.GetX());
		m_PointEnd.SetY(p2.GetY());
	}
	CCircle(const CCircle &cs)
	{
		this->m_PointStart = cs.m_PointStart;
		this->m_PointEnd = cs.m_PointEnd;
		if (this->m_Style != NULL)
			delete this->m_Style;
		this->m_Style = new CStyle(*cs.m_Style);
	}
	~CCircle() {
		if (this->m_Style != NULL)
		{
			delete m_Style;
			m_Style = NULL;
		}
	}
	virtual CShape* Clone() { return new CCircle(*this); }
};

