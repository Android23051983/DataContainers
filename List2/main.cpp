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
	class ConstBaseIrerator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIrerator(Element* Temp) : Temp(Temp)
		{
			cout << this << endl;
		}
		~ConstBaseIrerator() 
		{
			cout << this << endl;
		}
		bool operator==(const ConstBaseIrerator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ConstBaseIrerator& other)const
		{
			return this->Temp != other.Temp;
		}
		const int& operator*()const
		{
			return Temp->Data;
		}
	};

public:
	class ConstIterator:public ConstBaseIrerator
	{
	public:
		ConstIterator(Element* Temp) :ConstBaseIrerator(Temp)
		{
			cout << "IConstructor:\t" << this << endl;
		}
		~ConstIterator()
		{
			cout << "IDestructor:\t" << this << endl;
		}
		ConstIterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstIterator operator++(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		ConstIterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}


		
	};
	class ConstReverseIterator:public ConstBaseIrerator
	{
		
	public:
		ConstReverseIterator(Element* Temp) :ConstBaseIrerator(Temp)
		{
			cout << "RevIterConstructor:\t" << this << endl;
		}
		~ConstReverseIterator()
		{
			cout << "RevIterDestructor:\t" << this << endl;
		}

		ConstReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstReverseIterator operator++(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ConstReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstReverseIterator operator--(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}

	};

	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp) :ConstIterator(Temp) {}
		~Iterator() {}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	class ReversIterator :public ConstReverseIterator
	{
	public:
		ReversIterator(Element* Temp) : ConstReverseIterator(Temp) {}
		~ReversIterator() {}
		int& operator*()
		{
			return Temp->Data;
		}


	};

	ConstIterator cbegin()const
	{
		return Head;
	}
	ConstIterator cend()const
	{
		return nullptr;
	}

	ConstReverseIterator crbegin()const
	{
		return Tail;
	}
	ConstReverseIterator crend()const
	{
		return nullptr;
	}
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}

	ReversIterator rbegin()
	{
		return Tail;
	}
	ReversIterator rend()
	{
		return nullptr;
	}

public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LC:\t" << this << endl;
	}

	List(const std::initializer_list<int>& il) :List()
	{
		cout << typeid(il.begin()).name() << endl;;
		/*for (int const* it = il.begin(); it != il.end(); ++it)
		{
			push_back(*it);
		}*/
		for (int i : il)push_back(i);
	}

	List(const List& other) :List()
	{
		*this = other;	
		cout << "LCopyConstructor:\t" << this << endl;
	}

	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LD:\t" << this << endl;
	}

	//operators
	
	List& operator=(const List& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)this->push_back(Temp->Data);
		cout << "LCopyAssignment:\t" << this << endl;
		return *this;
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
		/*Element* New = new Element(Data);
		New->pNext = Head;
		Head->pPrev = New;
		Head = New;*/
		Head = Head->pPrev = new Element(Data, Head);
		size++;
	}

	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)return push_front(Data);
		/*Element* New = new Element(Data);
		New->pPrev = Tail;
		Tail->pNext = New;
		Tail = New;*/
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
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
		cout << "Кол-во " << size<< endl;
	}
	void reverse_print()const
	{
	for(Element* Temp=  Tail; Temp; Temp=Temp->pPrev)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}
};
List operator+(const List& left, const List& right)
{
	List cat = left;
	for (List::ConstIterator it = right.cbegin(); it != right.cend(); ++it)
	{
		cat.push_back(*it);
		//*it *= 10;
	}
	return cat;
}
//#define BASE_CHECK
//#define ITERATORS_CHECK
void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
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
#endif // BASE_CHECK
#ifdef ITERATORS_CHECK
	List list = { 3,5,8,13,21 };
	list.print();
	List list1;
	list1 = list;
	for (int i : list1)cout << i << tab; cout << endl;

	for (List::ReverseIterator reviter = list.rbegin(); reviter != list.rend(); ++reviter)
	{
		cout << *reviter << tab;
		cout << endl;
	}
	cout << endl;
#endif // ITERATORS_CHECK
	List list1 = { 3,5,8,12,21 };
	List list2 = { 34,55,89 };
	List list3 = list1 + list2;
	/*list3.print();
	list2.print();
	list1.print();*/
	for (int i : list1)cout << i << tab; cout << endl;
	for (List::ReversIterator it = list2.rbegin(); it != list2.rend(); ++it)
	{
		cout << *it << tab;
	
	}

	cout << endl;
	for (List::Iterator it = list3.begin(); it != list2.end(); ++it)
	{
		cout << *it << tab;
	
	}

	cout << endl;



}