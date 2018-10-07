#pragma once
#include "CShape.h"
class CLine : public CShape
{
public:
	CLine(){}
	CLine(CPoint p1, CPoint p2) {
		m_PointStart = p1;
		m_PointEnd = p2;
	}
	CLine(const CLine &cs)
	{
		this->m_PointStart = cs.m_PointStart;
		this->m_PointEnd = cs.m_PointEnd;
		if (this->m_Style != NULL)
			delete this->m_Style;
		this->m_Style = new CStyle(*cs.m_Style);
	}
	~CLine(){
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
			MoveToEx(hdc, m_PointStart.GetX(), m_PointStart.GetY(), NULL);
			LineTo(hdc, m_PointEnd.GetX(), m_PointEnd.GetY());
		}
	}
	CShape* Clone() { return new CLine(*this); }
};

