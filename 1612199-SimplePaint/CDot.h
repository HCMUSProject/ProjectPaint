#pragma once
#include "CShape.h"
class CDot : public CShape
{
public:
	CDot() 
	{
		this->m_PointStart = this->m_PointEnd = CPoint(0, 0);
	}
	CDot(CPoint p1) {
		m_PointStart = m_PointEnd = p1;
	}
	CDot(const CDot &cs)
	{
		this->m_PointStart = this->m_PointEnd = cs.m_PointStart;
		
		if (this->m_Style != NULL)
			delete this->m_Style;
		this->m_Style = new CStyle(*cs.m_Style);
	}
	virtual ~CDot() {
		if (this->m_Style != NULL)
		{
			delete m_Style;
			m_Style = NULL;
		}
	}
	virtual void Draw(HDC hdc)
	{
		m_Style->SetHDCPen(hdc);
		SelectObject(hdc, (HBRUSH)m_Style->GetBackgroundColor());
		SetPixel(hdc, this->m_PointStart.GetX(), this->m_PointStart.GetY(), this->m_Style->GetColor());
	}
	CShape* Clone() { return new CDot(*this); }
};

