#pragma once
class CStyle
{
	HPEN _hPen;
	int _iStyle;
	int _iWidth;
	COLORREF _color;
	COLORREF _bgColor;
public:
	CStyle()
	{
		_iStyle = PS_SOLID;
		_iWidth = 1;
		_color = RGB(0, 0, 0);
		_hPen = CreatePen(_iStyle, _iWidth, _color);
		_bgColor = COLOR_WINDOW + 1;
	}
	CStyle(int iStyle, int iWidth, COLORREF color, COLORREF bgcolor)
	{
		_iStyle = iStyle;
		_iWidth = iWidth;
		_color = color;
		_bgColor = bgcolor;
		_hPen = CreatePen(_iStyle, _iWidth, _color);
	}
	CStyle(const CStyle &st)
	{
		if (&st != NULL)
		{
			_iStyle = st._iStyle;
			_iWidth = st._iWidth;
			_color = st._color;
			_bgColor = st._bgColor;
			_hPen = CreatePen(_iStyle, _iWidth, _color);
		}
	}
	~CStyle(){}
	void SetStyle(int iStyle)
	{ 
		_iStyle = iStyle; 
		DeleteObject(_hPen);
		_hPen = CreatePen(_iStyle, _iWidth, _color);
	}
	void SetWidth(int iWidth) {
		_iWidth = iWidth; 
		DeleteObject(_hPen);
		_hPen = CreatePen(_iStyle, _iWidth, _color);
	}
	void SetColor(COLORREF color) {
		_color = color; 
		DeleteObject(_hPen);
		_hPen = CreatePen(_iStyle, _iWidth, _color);
	}
	void SetBackgroundColor(COLORREF bgcolor) {
		_bgColor = bgcolor;
	}

	void SetHDCPen(HDC hdc)
	{
		SelectObject(hdc, _hPen);
	}

	int GetStyle() { return _iStyle; }
	int GetWidth() { return _iWidth; }
	COLORREF GetColor() { return _color; }
	COLORREF GetBackgroundColor() { return _bgColor; }
};

