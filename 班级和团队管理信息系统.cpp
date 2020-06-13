#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
using namespace std;

class Student
{
public:
    const string name;
    static int Stu_num;
    int num;

public:
    Student() {}
    explicit Student(const string &name) : name(name)
    {
        Stu_num++;
        num = Stu_num;
    }
    ~Student() {}
};
class Class
{
public:
    vector<shared_ptr<Student>> stu;
};

class Team
{
public:
    vector<shared_ptr<Student>> stu;
};

int Student::Stu_num = 9999;
map<int, shared_ptr<Student>> stu;
map<int, unique_ptr<Class>> cla;
map<string, unique_ptr<Team>> team;

void show()
{
    cout << "student list:" << endl;
    for (auto &i : stu)
        cout << i.first << ' ' << i.second->name << endl;
    for (auto &i : cla)
    {
        cout << endl;
        cout << "class " << i.first << ':' << endl;
        for (auto &j : i.second->stu)
            cout << (*j).num << ' ' << (*j).name << endl;
    }
    for (auto &i : team)
    {
        cout << endl;
        cout << i.first << " team:" << endl;
        for (auto &j : i.second->stu)
            cout << (*j).num << ' ' << (*j).name << endl;
    }
}
int main()
{
    string cmd;
    while (cin >> cmd)
    {
        if (cmd == "append")
        {
            string name;
            cin >> name;
            stu[Student::Stu_num] = make_shared<Student>(name);
        }
        else if (cmd == "create")
        {
            string type;
            cin >> type;
            if (type == "class")
            {
                int num;
                cin >> num;
                unique_ptr<Class> p(new Class());
                cla[num] = move(p);
            }
            else
            {
                string name;
                cin >> name;
                unique_ptr<Team> p(new Team());
                team[name] = move(p);
            }
        }
        else
        {
            string type;
            cin >> type;
            if (type == "class")
            {
                int num1, num2;
                cin >> num1 >> num2;
                cla[num1]->stu.push_back(stu[num2]);
            }
            else
            {
                string name;
                int num;
                cin >> name >> num;
                team[name]->stu.push_back(stu[num]);
            }
        }
    }
    show();
    return 0;
}
