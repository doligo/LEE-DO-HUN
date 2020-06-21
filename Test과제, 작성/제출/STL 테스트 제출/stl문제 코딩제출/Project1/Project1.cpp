#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <iterator>

using namespace std;

class p
{
private:
    int a, b, c;
public:
    p(int _a, int _b, int _c)
    {
        a = _a;
        b = _b;
        c = _c;
    }

    void print()
    {
        cout << "a : " << a << ", b : " << b << ", c : " << c << endl;
    }

};

template <typename T>
void Copy(T t, T s , int n)
{
    for (int i = 0; i < n; i++)
    {
        t[i] = s[i];
    }
}

struct MyType
{
    char ch;
};

ostream &operator<<(ostream& o, MyType& m) 
{
    o << m.ch << " ";
    return o;
}

template <typename T>
class Stack
{
private:
    T* array;
    int top;
    int size;
public:
    Stack(int s = 10) : size(s), top(-1)
    {
        array = new int[size];
    }
    void Push(T data)
    {
        array[++top] = data;
    }
    bool Empty()
    {
        return top == -1;
    }
    int Pop()
    {
        return array[top--];
    }
};
template <typename T>
class Queue
{
private:
    T* array;
    int rear, front;
    int size;
public:
    Queue(int s = 10) : size(s)
    {
        front = 0;
        rear = 0;
        array = new T[size];
    }
    void Push(T data)
    {
        array[rear] = data;
        rear++;
    }
    bool Empty()
    {
        return front == rear;
    }
    T Pop()
    {
        return array[front++];
    }
};

int main()
{
    p p1 = { 10, 20 ,30 };

    p1.print(); ////////// 1번

    
    string s("Hello!");
    const char* sz = s.c_str();
    
    const char* sz2 = "Hello!";
    string s2("Hi~!");
    s2 = sz2; ///////////// 2번

    int arr1[5] = { 10, 20, 30, 40, 50 };
    int arr2[5];

   //Copy(t, s, n) t:목적지 주소, s:소스 주소, n: 원소갯수 
    Copy(arr2, arr1, 5);

    for (int i = 0; i < 5; i++)
        cout << arr2[i] << " ";
    cout << endl;

    MyType myArr1[5] = { 'a', 'b', 'c', 'd', 'e' };
    MyType myArr2[5];

    Copy(myArr2, myArr1, 5);
    for (int i = 0; i < 5; i++)
        cout << myArr1[i] << " ";
    cout << endl;
    ///////////////// 3번

    Stack<int> st;

    st.Push(10);
    st.Push(20);
    st.Push(30);

    if (!st.Empty())
        cout << st.Pop() << endl;

    if (!st.Empty())
        cout << st.Pop() << endl;

    if (!st.Empty())
        cout << st.Pop() << endl;
    /////////////////// 4번 스택은 last in last out 이다
    cout << endl;

    Queue<int> q;

    q.Push(10);
    q.Push(20);
    q.Push(30);

    if (!q.Empty())
        cout << q.Pop() << endl;

    if (!q.Empty())
        cout << q.Pop() << endl;

    if (!q.Empty())
        cout << q.Pop() << endl;

    ///////////// 5번 큐는 First in First out 이다


	vector<int> vv;
	vv.push_back(10);
	vv.push_back(20);
	vv.push_back(30);
	vv.push_back(40);
	vv.push_back(50);

	vector<int>::iterator iterr;
	vector<int>::iterator iterr2;

	iterr = vv.begin();
	iterr++;
	iterr++;
	iterr2 = vv.erase(iterr);

	for (vector<int>::size_type i = 0; i < vv.size(); i++)
		cout << vv[i] << " ";
	cout << endl;
	///////////////////// 17번 문제

	vector<int> mun1;
	mun1.push_back(10);
	mun1.push_back(20);
	mun1.push_back(30);
	mun1.push_back(40);
	mun1.push_back(50);
	mun1.push_back(60);
	mun1.push_back(70);
	mun1.push_back(80);
	mun1.push_back(90);
	mun1.push_back(100);

	reverse(mun1.begin(), mun1.begin() + 5);
	for (vector<int>::size_type i = 0; i < mun1.size(); i++)
		cout << mun1[i] << " ";
	cout << endl;
	///////////////// 18번

	vector<int> mun2;

	mun2.push_back(70);
	mun2.push_back(20);
	mun2.push_back(32);
	mun2.push_back(40);
	mun2.push_back(33);
	mun2.push_back(60);
	mun2.push_back(32);
	mun2.push_back(33);
	mun2.push_back(90);
	mun2.push_back(50);

	sort(mun2.begin(), mun2.end());
	vector<int>::iterator mun2_iter;
	mun2_iter = unique(mun2.begin(), mun2.end());

	for (vector<int>::iterator iter = mun2.begin(); iter != mun2_iter; iter++)
		cout << *iter << " ";
	cout << endl << endl;
	//////////////// 19번
	cout << "<합치기 전>" << endl;
	vector<int> mun3;

	mun3.push_back(10);
	mun3.push_back(20);
	mun3.push_back(30);
	mun3.push_back(40);
	mun3.push_back(50);
	mun3.push_back(60);
	mun3.push_back(70);
	mun3.push_back(80);
	mun3.push_back(90);
	mun3.push_back(100);

	vector<int> mun3_2;
	mun3_2.assign(10, 0);

	vector<int>::iterator mun3_iter;
	mun3_iter = copy(mun3.begin(), mun3.end(), mun3_2.begin());
	for (vector<int>::size_type i = 0; i < mun3_2.size(); i++)
		cout << mun3_2[i] << " ";
	cout << endl;
	cout << "<합친후>" << endl;

	vector<int> mun3_3;
	mun3_3.assign(10, 0);
	vector<int>::iterator mun3_iter2;
	mun3_iter2 = transform(mun3.begin(), mun3.end(), mun3_2.begin(), mun3_3.begin(), plus<int>());

	for (mun3_iter = mun3_3.begin(); mun3_iter != mun3_iter2; mun3_iter++)
		cout << *mun3_iter << " ";
	cout << endl << endl;
	/////////// 20번

	vector<int> vvv1;
	vector<int> vvv2;
	vector<int> vvv3;
	vvv3.assign(8, 0);

	vvv1.push_back(50);
	vvv1.push_back(10);
	vvv1.push_back(30);
	vvv1.push_back(80);
	vvv1.push_back(60);

	vvv2.push_back(20);
	vvv2.push_back(70);
	vvv2.push_back(40);

	sort(vvv1.begin(), vvv1.end());
	sort(vvv2.begin(), vvv2.end());

	vector<int>::iterator vvv_iter;
	vvv_iter = merge(vvv1.begin(), vvv1.end(), vvv2.begin(), vvv2.end(), vvv3.begin());

	for (vector<int>::size_type i = 0; i < vvv3.size(); i++)
		cout << vvv3[i] << " ";
	cout << endl;
	//////////////// 21번

	vector<int> aa;

	aa.push_back(10);
	aa.push_back(20);
	aa.push_back(30);
	aa.push_back(40);
	aa.push_back(50);
	aa.push_back(60);
	aa.push_back(70);
	aa.push_back(80);
	aa.push_back(90);
	aa.push_back(100);

	vector<int>::iterator aaiter;
	aaiter = aa.begin() + 6;
	
	rotate(aa.begin(), aaiter, aa.end());
	for (vector<int>::size_type i = 0; i < aa.size(); i++)
		cout << aa[i] << " ";
	cout << endl;
	//////////// 22번

	vector<int> bb1, bb2, bb3;
	vector<int>::iterator bbiter;

	bb3.assign(8, 0);

	bb1.push_back(50);
	bb1.push_back(10);
	bb1.push_back(30);
	bb1.push_back(80);
	bb1.push_back(60);

	sort(bb1.begin(), bb1.end());

	bb2.push_back(20);
	bb2.push_back(70);
	bb2.push_back(40);

	sort(bb2.begin(), bb2.end());

	bbiter = set_union(bb1.begin(), bb1.end(), bb2.begin(), bb2.end(), bb3.begin());

	for (vector<int>::size_type i = 0; i < bb3.size(); i++)
		cout << bb3[i] << " ";
	cout << endl << endl;
	///// 23번

	vector<int> v1;
	v1.push_back(10);
	v1.push_back(40);
	v1.push_back(50);

	vector<int> v2;
	v2.push_back(20);
	v2.push_back(30);
	v2.push_back(60);

	vector<int> v3(6);

	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());

	merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());

	for (vector<int>::size_type i = 0; i < v3.size(); ++i)
	{
		cout << v3[i] << endl;
	}
	///// 27번

	vector<int> v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);

	copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));

	//// 28번

    return 0;
}