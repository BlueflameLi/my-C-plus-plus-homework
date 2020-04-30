
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
class CPoint
{
public:
	const int x;
	const int y;

public:
	CPoint(int x, int y) : x(x), y(y) {}
	~CPoint() {}
};
class CShape
{
protected:
	const string shape;
	const int x;
	const int y;

public:
	CShape(const string &shape, const int x, const int y)
		: shape(shape), x(x), y(y) {}
	virtual ~CShape() {}
	virtual bool HitIn(const CPoint &) const = 0;
};
class CRectangle : public CShape
{
private:
	const double length;
	const double width;

public:
	CRectangle(const string &shape, const int x, const int y, const double length, const double width)
		: CShape(shape, x, y), length(length), width(width) {}
	bool HitIn(const CPoint &) const;
};
bool CRectangle::HitIn(const CPoint &p) const
{
	if (p.x < x)
		return false;
	if (p.x > x + length)
		return false;
	if (p.y < y)
		return false;
	if (p.y > y + width)
		return false;
	return true;
}
class CCircle : public CShape
{
private:
	const double radius;

public:
	CCircle(const string &shape, const int x, const int y, const double radius)
		: CShape(shape, x, y), radius(radius) {}
	bool HitIn(const CPoint &) const;
};
bool CCircle::HitIn(const CPoint &p) const
{
	double dis = sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
	if (dis > radius)
		return false;
	return true;
}
class CUIControl
{
protected:
	const string label;
	const CShape *_pShape;

public:
	CUIControl(const string &label, const CShape *_pShape) : label(label), _pShape(_pShape) {}
	virtual void Clicked() const = 0; //定义为纯虚函数
	bool HitTest(const CPoint &) const;
	virtual ~CUIControl()
	{
		delete _pShape;
		_pShape = nullptr;
	}
};
bool CUIControl::HitTest(const CPoint &p) const
{
	if (_pShape->HitIn(p))
	{
		Clicked();
		return true;
	}
	return false;
}
class CMenu : public CUIControl
{
public:
	CMenu(const string &label, const CShape *_pShape) : CUIControl(label, _pShape) {}
	void Clicked() const
	{
		cout << "menu-" << label << " Clicked" << endl;
	}
};

class CButton : public CUIControl
{
public:
	CButton(const string &label, const CShape *_pShape) : CUIControl(label, _pShape) {}
	void Clicked() const
	{
		cout << "button-" << label << " Clicked" << endl;
	}
};
int main()
{
	int n;
	int x, y;
	vector<CUIControl *> v;
	string type, label, shape;

	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> type >> label >> shape >> x >> y;
		if (type == "menu")
		{
			if (shape == "rectangle")
			{
				int length, width;
				cin >> length >> width;
				v.push_back(new CMenu(label, new CRectangle(shape, x, y, length, width)));
			}
			else
			{
				double radius;
				cin >> radius;
				v.push_back(new CMenu(label, new CCircle(shape, x, y, radius)));
			}
		}
		else
		{
			if (shape == "rectangle")
			{
				int length, width;
				cin >> length >> width;
				v.push_back(new CButton(label, new CRectangle(shape, x, y, length, width)));
			}
			else
			{
				double radius;
				cin >> radius;
				v.push_back(new CButton(label, new CCircle(shape, x, y, radius)));
			}
		}
	}
	while (cin >> type)
	{
		cin >> x >> y;
		CPoint *p = new CPoint(x, y);
		bool flag = false;
		for (auto itr = v.end() - 1; itr >= v.begin(); itr--)
			if ((*itr)->HitTest(*p))
			{
				flag = true;
				break;
			}
		if (!flag)
			cout << "none hit" << endl;
		delete p;
		p = nullptr;
	}
	for (auto itr = v.begin(); itr != v.end(); itr++)
		if (*itr != nullptr)
		{
			delete *itr;
			*itr = nullptr;
		}
	return 0;
}