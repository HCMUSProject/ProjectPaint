#pragma once
#include "CShape.h"
class CEllipse : public CShape
{
public:
	CEllipse() {}
	CEllipse(CPoint p1, CPoint p2) {
		m_PointStart = p1;
		m_PointEnd = p2;
	}
	CEllipse(const CEllipse &cs)
	{
		this->m_PointStart = cs.m_PointStart;
		this->m_PointEnd = cs.m_PointEnd;
		if (this->m_Style != NULL)
			delete this->m_Style;
		this->m_Style = new CStyle(*cs.m_Style);
	}
	~CEllipse() {
		if (this->m_Style != NULL)
		{
			delete m_Style;
			m_Style = NULL;
		}
	}
	virtual void Draw(HDC hdc)
	{
		m_Style->SetHDCPen(hdc);
		if (!(m_PointStart.GetX() == m_PointEnd.GetX() && m_PointStart.GetY() == m_PointEnd.GetY()))
		{
			SelectObject(hdc, (HBRUSH)m_Style->GetBackgroundColor());

			Ellipse(hdc, m_PointStart.GetX(), m_PointStart.GetY(), m_PointEnd.GetX(), m_PointEnd.GetY());
		}
	}
	virtual CShape* Clone() { return new CEllipse(*this); }
};
