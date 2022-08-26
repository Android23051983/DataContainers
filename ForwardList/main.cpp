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
	int get_Data()const
	{
		return Data;
	}
	Element* get_pNext()const
	{
		return pNext;
	}

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
	Element* get_Head()const
	{
		return Head;
	}
	ForwardList()
	{
		Head = nullptr; //Если список пуст, то его Голова указывает на 0
		size = 0;
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
		Element* Temp = Head;
		if (Index == 0)
		{
			pop_front();
		}
		else
		{
			for (int i = 0; i < Index - 1; i++)
			{

				Temp = Temp->pNext;

			}
				Element *Erased = Temp->pNext;
				Temp->pNext = Temp->pNext->pNext;
				delete Erased;
				size--;
		}
	
	
	}

	

	void print()const
	{
		//Element* Temp = Head; //Temp это итератор
		//while (Temp)			// Итератор - это указатель, при помощи которого можно получить доступ к элементам данных
		//{
		//	cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
		//	Temp = Temp->pNext; //Переход на следующий элемент.
		//}
		for(Element* Temp = Head; Temp; Temp=Temp->pNext)
			cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
		cout << "Общее количество элементов в списках: " << Element::count << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList result = left;	
	for (Element* Temp = right.get_Head(); Temp; Temp = Temp->get_pNext())
	{
		result.push_back(Temp->get_Data());
	}
	return result;
}
//#define BASE_CHECK
//#define RANGE_BASE_FOR_ARRAY
#define ENDL_TEST_WORK
void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
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
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
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
#ifdef ENDL_TEST_WORK
	cout << "Создание списков" << endl;
	ForwardList list1 = { 3,5,8,13,21 };
	ForwardList list2 = { 34,55,89 };
	cout << endl;
	cout << "list1" << endl;
	list1.print();
	cout << endl;
	cout << "list2" << endl;
	list2.print();
	cout << endl;
	cout << "Вставка элемета списка" << endl;
	list1.insert(0, 4);
	cout << "list1" << endl;
	list1.print();
	cout << endl;
	cout << "Удаление элемета списка" << endl;
	list1.erase(4);
	cout << "list1" << endl;
	list1.print();
	//ForwardList list3 = list1 + list2;
	//list3.print();

#endif // ENDL_TEST_WORK

}	