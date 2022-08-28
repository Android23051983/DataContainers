#include<iostream>

using namespace std;
using std::cin;
using std::cout;
using std::endl;
#define tab "\t"

class List
{
	class Element
	{
		int Data;
		Element* pNext; // ук на следующий элемент
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EC:\t" << this << endl;
		}
		~Element()
		{
			cout << "ED:\t" << this << endl;
		}
		friend class List;
	
	}*Head, * Tail;
	size_t size;
public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LC:\t" << this << endl;
	}

	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LD:\t" << this << endl;
	}
	// Adding elements:
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		
		}
		Element* New = new Element(Data);
		New->pNext = Head;
		Head->pPrev = New;
		Head = New;
		size++;
	}

	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)return push_front(Data);
		Element* New = new Element(Data);
		New->pPrev = Tail;
		Tail->pNext = New;
		Tail = New;
		size++;

	}

	// Removing elements:

	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			size--;
			return;
		}
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
		size--;
	}

	void pop_back()
	{
		if (Head == Tail)return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}

	void erase(int index)
	{
		if (index >=size)return;
		if (index == size-1)return pop_back();
		if (index ==0)return pop_front();
		Element* Temp;
		if (index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < index; i++)Temp = Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size-index-1; i++)Temp = Temp = Temp->pPrev;

		}
		Temp->pPrev->pNext = Temp -> pNext;
		Temp->pNext->pPrev = Temp -> pPrev;
		delete Temp;
		size--;
	}

	void insert(int Data, int Index)
	{
		if (Index >= size)
		{
			cout << "Error: Выход за пределы списка!" << endl;
			return;
		}

		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
		}
		Element* New = new Element(Data);
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;
		size++;
	}
	//Methods:
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Кол-во" << size<< endl;
	}
	void reverse_print()const
	{
	for(Element* Temp=  Tail; Temp; Temp=Temp->pPrev)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "ВВедите размер списка"; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);

	}
	list.print();
	list.reverse_print();
	int index;
	int value;
	cout << "Введите индекс "; cin >> index;
	cout << "Введите значение "; cin >> value;
	list.insert(value, index);
	list.print();
	list.reverse_print();
	cout << "Введите индекс "; cin >> index;
	list.erase(index);
	list.print();
	list.reverse_print();




}