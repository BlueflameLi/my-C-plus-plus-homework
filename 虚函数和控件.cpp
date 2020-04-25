
#include <iostream>
#include <vector>
using namespace std;

class CUIControl
{
protected:
	const string label;

public:
	CUIControl(string label) : label(label) {}
	virtual void Clicked() const = 0; //定义为纯虚函数
	virtual ~CUIControl() {}
};

class CMenu : public CUIControl
{
public:
	CMenu(string label) : CUIControl(label) {}
	void Clicked() const
	{
		cout << "menu-" << label << " Clicked" << endl;
	}
};

class CButton : public CUIControl
{
public:
	CButton(string label) : CUIControl(label) {}
	void Clicked() const
	{
		cout << "button-" << label << " Clicked" << endl;
	}
};
int main()
{
	int n;
	string type, label;
	vector<CUIControl *> v;

	cin >> n;
	while (n--)
	{
		cin >> type >> label;
		if (type == "menu")
			v.push_back(new CMenu(label));
		else
			v.push_back(new CButton(label));
	}

	int p;
	while (cin >> type >> p)
		v[p - 1]->Clicked();
	for (auto itr = v.begin(); itr != v.end(); itr++)
		if (*itr != nullptr)
		{
			delete *itr;
			*itr = nullptr;
		}
	return 0;
}