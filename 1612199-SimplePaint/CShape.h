#pragma once
#include "CPoint.h"
#include "CStyle.h"
class CShape
{
protected:
	CPoint m_PointStart;
	CPoint m_PointEnd;
	CStyle* m_Style;
	
public:
	CShape(){}
	CShape(const CShape &cs)
	{
		// BUG BUG BUG BUG BUG BUG BUG BUG BUG BUG BUG BUGBUG BUG BUG BUG BUG BUG
		this->m_PointStart = cs.m_PointStart;
		this->m_PointEnd = cs.m_PointEnd;
		if (this->m_Style!=NULL)
			delete this->m_Style;
		this->m_Style = new CStyle(*cs.m_Style);

	}
	virtual ~CShape()
	{ 
		if (this->m_Style != NULL)
		{
			delete m_Style;
			m_Style = NULL;
		}
	}

	virtual void SetPointStart(CPoint P)
	{
		m_PointStart = P;
	}
	virtual void SetPointEnd(CPoint P)
	{
		m_PointEnd = P;
	}
	virtual void SetStyle(CStyle st)
	{
		m_Style = new CStyle(st);
	}
	virtual void Draw(HDC hdc) = 0;
	virtual CShape* Clone() = 0;
};

