//Author:绫雪 时间:2021/12/08 邮箱:2239301685@qq.com/yaolin6666@gmail.com 
//操作系统实验作业:存储分区管理算法
//实现最佳适应法和首次适应法
#include <iostream>
#include<cstring>
#include<algorithm>
#include<windows.h>
#include<list>
using namespace std;
class space
{
public:
      int address;          //开始地址
      int end;              //结束地址
      int size;             //分区大小
      space();
      space(int a, int b);
      bool operator<(const space& b)
      {
          return this->size < b.size;
      }
      bool operator==(const space& b)
      {
          if (this->address == b.address && this->end == b.end)
              return true;
          else
              return false;
      }
      friend ostream& operator<<(ostream& os, const space& c);
};
space::space()
{
    address = 0;
    end = 0;
    size = 0;
}
space::space(int a, int b)
{
    address = a;
    size = b;
    end = b + a - 1;
}
ostream& operator<<(ostream& os, const space& c)
{
    os << c.address << "\t" << c.end << "\t" << c.size;
    return os;
}
template <class T>
void Print(T first, T last)
{
    int i = 1;
    for (; first != last; first++)
    {
        cout <<i<<"\t" << *first << endl;
        i++;
    }
    cout << endl;
}
template<class T>
int find(T first, T last, space Find)
{
    space temp1,temp2;
    T tem,lastT,firstT;
    lastT = last;
    lastT--;
    int n=-1;
    for (; first != last; first++)
    {
        temp1 = *first;
        tem = first;
        firstT = first;
        firstT++;
        if (lastT != first)
        {
            tem++;
        }
        temp2 = *tem;
        if (((temp1.end+1) == Find.address))
        {   
            if (firstT == last)
            {
                n = 1;
            }
            else if ((((temp2.address - 1) - temp1.end) >= Find.size))
            {
                n = 1;
                break;
            }
        }
        else
        {
            n = 2;
        }
    }
    return n;
}
template<class T>
void storChange(T first, T last, space Find)
{
    space temp;
    for (; first != last; first++)
    {
        temp = *first;
        if (temp.end + 1 == Find.address)
        {
            temp.end += Find.size;
            temp.size += Find.size;
            *first = temp;
            break;
        }
    }
}
template<class T>
void storAccept(T first, T last, int Req)
{
    space Temp;
    int Add;
    bool flag = true;
    for (; first != last; first++)
    {
        Temp = *first;
        if (Temp.size >= Req)
        {
            Temp.size -= Req;
            Temp.end -= Req;
            Add = Temp.end + 1;
            cout << "SUCCESS!!! ADDRESS=" << Add<<endl;
            *first = Temp;
            flag = false;
            break;
        }
    }
    if(flag)
        cout << "Too much Application" << endl;
}
int main()
{
    int cursor=0,n=0;
    int acasflag = -1;                                      //acas标志    
    int chooseflag = -1;                                    //最佳适应首次适应标志
    int asflag = -1;                                        //空间分派标志
    char a[10], b[10],c[10] = "best",d[10]="first",e[10]="ac",f[10]="as";
    int adrI = 0, sizeI = 0;
    list<space> RelaxSpace;
    space Ini(0, 32767);
    cout << "Index *\tadr *\tend *\tsize" << endl;
    RelaxSpace.push_back(Ini);
    Print(RelaxSpace.begin(), RelaxSpace.end());
    cout << "input the way(best of first):";
    while (true)
    {
        cin >> a;
        if (strcmp(a, c) == 0)
        {
            chooseflag = 1;
            break;
        }
        else if (strcmp(a, d) == 0)
        {
            chooseflag = 2;
            break;
        }
        else
        {
            cout << "输入错误" << endl;
        }
    }   
    while (true) 
    {
        cout << "Assign or accept:";
        while (true)
        {
            cin >> b;
            if (strcmp(b, e) == 0)
            {
                acasflag = 1;
                break;
            }
            else if (strcmp(b, f) == 0)
            {
                acasflag = 2;
                break;
            }
            else
            {
                cout << "输入错误" << endl;
            }
        }
        adrI = 0,sizeI=0;
        if (acasflag == 1)
        {
            cout << "Input adr and size:";
            cin >> adrI >> sizeI;
            space assign(adrI, sizeI);
            asflag = find(RelaxSpace.begin(), RelaxSpace.end(), assign);
            if(asflag==1)
            {
                storChange(RelaxSpace.begin(), RelaxSpace.end(), assign);
            }
            else if (asflag == 2)
            {
                RelaxSpace.push_back(assign);
            }
            if (chooseflag == 1)
            {
                RelaxSpace.sort();
            }
            cout << asflag << endl;
            cout << "Index *\tadr *\tend *\tsize" << endl;
            Print(RelaxSpace.begin(), RelaxSpace.end());
            cout << endl << endl;
        }
        if (acasflag == 2)
        {
            cout << "Input APPLACATION:";
            cin >> sizeI;
            storAccept(RelaxSpace.begin(), RelaxSpace.end(), sizeI);
            cout << "Index *\tadr *\tend *\tsize" << endl;
            if (chooseflag == 1)
            {
                RelaxSpace.sort();
            }
            Print(RelaxSpace.begin(), RelaxSpace.end());
            cout << endl<<endl;
        }
    }
}
