#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>

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

    return 0;
}