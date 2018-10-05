#pragma once
class CPoint
{
	int m_x;
	int m_y;
public:
	CPoint() { m_x = 0; m_y = 0; }
	CPoint(int x, int y) { m_x = x; m_y = y; }
	~CPoint(){}

	void SetX(int x) { m_x = x; }
	void SetY(int y) { m_y = y; }
	int GetX() { return m_x; }
	int GetY(){ return m_y; }
};

