#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

class Element
{
	int Data;
	Element* pNext;
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "Econstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "Edestructor:\t" << this << endl;
	}
	friend class ForwardList;

};
int Element::count = 0;

class ForwardList
{
	Element* Head;
	unsigned int size;
public:
	ForwardList()
	{
		Head = nullptr; //���� ������ ����, �� ��� ������ ��������� �� 0
		cout << "LConstructor:\t" << this << endl;
	}

	ForwardList(const std::initializer_list<int>& il) : ForwardList()
	{
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		
		}
	}

	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	// Adding elements:

	void push_front(int Data)
	{
		/*Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;*/
		Head = new Element(Data, Head);
		size++;
	}

	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		//Element* New = new Element(Data);
		Element* Temp = Head;
		while (Temp->pNext != nullptr)
			Temp = Temp->pNext;
		Temp->pNext = new Element(Data);
		size++;
		
	}

	// Erasing element:

	void pop_front()
	{
		Element* Erased = Head;
		Head = Head->pNext;
		delete Erased;
		size--;
	}

	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext)
			Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}

	void insert(int Data, int Index)
	{
		//Element* New = new Element(Data);
		Element* Temp = Head;
		if (Index ==0)
		{
			push_front(Data);
		}
		else if (Temp->pNext == nullptr)
		{
			push_back(Data);
		}
		else
		{
			for (int i = 0; i <= Index - 1; i++)Temp = Temp->pNext;
			/*New->pNext = Temp->pNext;
			Temp->pNext = New;*/
			Temp->pNext = new Element(Data, Temp->pNext);
			size++;
		}
	}
	void erase(int Index)
	{
		Element *Temp = Head, *Helping = Head;
		for (int i = 0; i < Index; i++) 
		{
			Helping = Temp;
			Temp = Temp->pNext;
		}
		if (Temp == Head)
		{
			Head = Temp->pNext;
		}
		else
		{
			Helping->pNext = Temp->pNext;
		}
		//free(Temp); // Deallocate memory block (void free (void* ptr);). ������: https://cplusplus.com/reference/cstdlib/free/
		delete(Temp); //Deallocate storage space. ������: https://cplusplus.com/reference/new/operator%20delete/
		size--;
	}

	void print()const
	{
		//Element* Temp = Head; //Temp ��� ��������
		//while (Temp)			// �������� - ��� ���������, ��� ������ �������� ����� �������� ������ � ��������� ������
		//{
		//	cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
		//	Temp = Temp->pNext; //������� �� ��������� �������.
		//}
		for(Element* Temp = Head; Temp; Temp=Temp->pNext)
			cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
		cout << "���������� ��������� ������� " << Element::count << endl;
		cout << "������ ������ " << size << endl;
	}
};
//#define BASE_CHECK
//#define RANGE_BASE_FOR_ARRAY
void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "������� ������ ������: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	//list.push_back(123);
	list.print();
	list.pop_front();
	list.print();
	list.pop_back();
	list.print();
	int index;
	int value;
	cout << "������� ������ ������������ ��������: "; cin >> index;
	cout << "������� �������� ������������ ��������: "; cin >> value;
	list.insert(value, index);
	list.print();
#endif // BASE_CHECK

	/*ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);

	list1.print();
	list2.print();*/

#ifdef RANGE_BASE_FOR_ARRAY
	int arr[] = { 3,5,8,13,21 };
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
	{
		cout << arr[i] << "\t";
	}
	cout << endl;
	for (int i : arr)
	{
		cout << i << "\t";
	}
	cout << endl;
#endif // RANGE_BASE_FOR_ARRAY
	ForwardList list = { 3,5,8,13,21 };
	list.print();
	//list.insert(0, 0);
	//list.print();
	list.erase(0);
	list.print();
}