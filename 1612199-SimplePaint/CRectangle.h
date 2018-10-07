#pragma once
#include "CShape.h"
class CRectangle : public CShape
{
public:
	CRectangle() {}
	CRectangle(CPoint p1, CPoint p2) {
		m_PointStart = p1;
		m_PointEnd = p2;
	}
	CRectangle(const CRectangle &cs)
	{
		this->m_PointStart = cs.m_PointStart;
		this->m_PointEnd = cs.m_PointEnd;
		if (this->m_Style != NULL)
			delete this->m_Style;
		this->m_Style = new CStyle(*cs.m_Style);
	}
	~CRectangle() {
		if (this->m_Style != NULL)
		{
			delete m_Style;
			m_Style = NULL;
		}
	}
	void Draw(HDC hdc)
	{
		m_Style->SetHDCPen(hdc);
		if (!(m_PointStart.GetX() == m_PointEnd.GetX() && m_PointStart.GetY() == m_PointEnd.GetY()))
		{
			SelectObject(hdc, (HBRUSH)m_Style->GetBackgroundColor());
			
			Rectangle(hdc, m_PointStart.GetX(), m_PointStart.GetY(), m_PointEnd.GetX(), m_PointEnd.GetY());
		}
	}
	CShape* Clone() { return new CRectangle(*this); }
};

