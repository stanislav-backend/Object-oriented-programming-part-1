#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip> 

using namespace std;

// исключение выхода за границу списка 
class IndexOutOfRangeException : public exception {
protected:
    string error_info;
public:
    IndexOutOfRangeException(string in) : exception()
    {
        error_info = in;
    }
    void print() const {
        cout << this->error_info << endl;
    }
};

// структура программист
class Programmer
{
public:
    string second_name;
    string first_name;
    string email;
    string skype;
    string telegram;
    string programming_language;
    string workplace;
    int level;

    Programmer(string Second_Name = "A", string First_Name = "B", string Email = "C", string Skype = "D", string Telegram = "E", string Programming_Language = "F", string Workplace = "G", int Level = 0)
    {
        second_name = Second_Name;
        first_name = First_Name;
        email = Email;
        skype = Skype;
        telegram = Telegram;
        programming_language = Programming_Language;
        workplace = Workplace;
        level = Level;
    }

    Programmer(const Programmer& pr)
    {
        second_name = pr.second_name;
        first_name = pr.first_name;
        email = pr.email;
        skype = pr.skype;
        telegram = pr.telegram;
        programming_language = pr.programming_language;
        workplace = pr.workplace;
        level = pr.level;
    }

    bool operator ==(const Programmer& p)
    {
        if (second_name == p.second_name && first_name == p.first_name && email == p.email && skype == p.skype && telegram == p.telegram && programming_language == p.programming_language && workplace == p.workplace && level == p.level)
            return true;
        return false;
    }
    ~Programmer() { }
    friend ostream& operator<<(ostream& s, const Programmer& pr);
    friend istream& operator>>(istream& s, Programmer& pr);
};

ostream& operator <<(ostream& s, const Programmer& pr)
{
    if (typeid(s) == typeid(ofstream))
    {
        s << pr.second_name << "\n" << pr.first_name << "\n" << pr.email << "\n" << pr.email << "\n" << pr.skype << '\n' << pr.telegram << '\n' << pr.programming_language << '\n' << pr.workplace << '\n' << pr.level;
    }
    else
    {
        s << "Programmer: " << "\nSecond_Name: " << pr.second_name << "\nFirst_Name: " << pr.first_name << "\nEmail: " << pr.email << "\nSkype: " << pr.skype << "\nTelegram: " << pr.telegram << "\nProgramming_Language: " << pr.programming_language << "\nWorkplace: " << pr.workplace << "\nLevel: " << pr.level << endl;
    }
    return s;
}

istream& operator >>(istream& s, Programmer& pr)
{
    if (typeid(s) == typeid(ifstream))
    {
        s >> pr.second_name;
        s >> pr.first_name;
        s >> pr.email; ;
        s >> pr.skype;
        s >> pr.telegram;
        s >> pr.programming_language;
        s >> pr.workplace;
        s >> pr.level;
    }
    else
    {
        s >> pr.second_name >> pr.first_name >> pr.email >> pr.skype >> pr.telegram >> pr.programming_language >> pr.workplace >> pr.level;
    }
    return s;
}

// базовый класс элемента 
template <class T>
class Element
{
public:
    T info;
    Element* next;
    Element* prev;
    Element(T data)
    {
        next = prev = NULL;
        info = data;
    }

    Element(Element* Next, Element* Prev, T data)
    {
        next = Next;
        prev = Prev;
        info = data;
    }

    Element(const Element& el)
    {
        next = el.next;
        prev = el.prev;
        info = el.info;
    }

    template <class T1>
    friend ostream& operator <<(ostream& s, const Element<T1>& el);

    template <class T1>
    friend istream& operator >>(istream& s, Element<T1>& el);
};

template <class T1>
ostream& operator <<(ostream& s, const Element<T1>& el)
{
    s << el.info;
    return s;
}

template <class T1>
istream& operator >>(istream& s, Element<T1>& el)
{
    s >> el.info;
    return s;
}

// базовый класс односвязанного списка
template <class T>
class LinkedList
{
protected:
    Element<T>* head;
    Element<T>* tail;
    int count;
public:
    LinkedList()
    {
        head = tail = NULL;
        count = 0;
    }

    virtual ~LinkedList()
    {
        Element<T>* cur = this->head;
        while (cur != NULL)
        {
            Element<T>* to_delete = cur;
            cur = cur->next;
            delete to_delete;
        }
        this->head = NULL;
        this->count = 0;
        this->tail = NULL;
    }

    virtual Element<T>* pop() = 0;
    virtual Element<T>* push(T value) = 0;

    Element<T>& operator[] (int index)
    {
        if (index < 0 || index >= count) {
            throw IndexOutOfRangeException(string("index = " + to_string(index) + ", count of elements = " + to_string(count)));
        }
        Element<T>* current = head;
        for (int i = 0; current != NULL && i < index; current = current->next, i++);
        return *current;
    }

    virtual bool isEmpty()
    {
        return (this->count == 0);
    }

    template <class T1>
    friend ostream& operator <<(ostream& s, const LinkedList<T1>& el);
    template <class T1>
    friend istream& operator >>(istream& s, const LinkedList<T1>& el);
};

template <class T1>
ostream& operator <<(ostream& s, const LinkedList<T1>& el)
{
    Element<T1>* current;
    for (current = el.head; current != NULL; current = current->next)
        s << *current << " ";
    return s;
}

template <class T1>
istream& operator >>(istream& s, const LinkedList<T1>& el)
{
    for (Element<T1>* current = el.head; current != NULL; current = current->next)
        s >> *current;
    return s;
}

// односвязанный стэк. Добавление в конец, удаление с конца.
template < typename T1 >
class Stack : virtual public LinkedList<T1>
{
public:
    Stack() : LinkedList<T1>() { }

    virtual ~Stack()

    {
        Element<T1>* cur = this->head;
        while (cur != NULL)
        {
            Element<T1>* to_delete = cur;
            cur = cur->next;
            delete to_delete;
        }
        this->head = NULL;
        this->count = 0;
        this->head = NULL;
    }

    virtual Element<T1>* pop()
    {
        if (this->isEmpty())
            return NULL;

        Element<T1>* res = this->tail;
        (this->count)--;
        if (this->head == this->tail)
        {
            this->head = this->tail = NULL;
            return res;
        }

        Element<T1>* current = this->head;
        for (; current->next != this->tail; current = current->next);
        current->next = NULL;
        this->tail = current;
        return res;
    }

    virtual Element<T1>* push(T1 value)
    {
        Element<T1>* newElem = new Element<T1>(value);

        if (this->isEmpty())
            this->head = this->tail = newElem;
        else
            this->tail->next = newElem;
        this->tail = newElem;
        (this->count++);
        return this->tail;
    }
};

// односвязанная очередь. Добавление в конец, удаление с начала.
template < typename T1 >
class Queue : virtual public LinkedList<T1>
{
public:
    Queue() : LinkedList<T1>() { }

    virtual ~Queue()

    {
        Element<T1>* cur = this->head;
        while (cur != NULL)
        {
            Element<T1>* to_delete = cur;
            cur = cur->next;
            delete to_delete;
        }
        this->head = NULL;
        this->count = 0;
        this->head = NULL;
    }

    virtual Element<T1>* pop()
    {
        if (this->isEmpty())
            return NULL;

        Element<T1>* res = this->head;
        (this->count)--;
        if (this->head == this->tail)
        {
            this->head = this->tail = NULL;
            return res;
        }
        this->head = this->head->next;
        return res;
    }

    virtual Element<T1>* push(T1 value)
    {
        Element<T1>* newElem = new Element<T1>(value);

        if (this->isEmpty())
            this->head = this->tail = newElem;
        else
            this->tail->next = newElem;
        this->tail = newElem;
        (this->count++);
        return this->tail;
    }
};

// Класс с методами, как для стэка, так и для очереди
template < typename T1 >
class StackQueue : protected Queue<T1>, protected Stack<T1>
{
public:
    StackQueue() : Queue<T1>(), Stack<T1>() { }

    Element<T1>* pop() { Queue < T1 >::pop(); Stack < T1 >::pop(); return this->tail; }
    Element<T1>* push(T1 value) { Queue < T1 >::push(value); Stack < T1 >::push(value); return this->tail; }


    Element<T1>* push_back(T1 value)
    {
        return Stack < T1 >::push(value);
    }

    Element<T1>* push_front(T1 value)
    {
        Element<T1>* newElem = new Element<T1>(value);

        if (this->isEmpty())
            this->head = this->tail = newElem;
        newElem->next = this->head;
        this->head = newElem;
        return this->head;
    }

    Element<T1>* pop_back()
    {
        return Stack < T1 >::pop();
    }

    Element<T1>* pop_front()
    {
        return Queue < T1 >::pop();
    }

    template <class T1>
    friend ostream& operator <<(ostream& s, const StackQueue<T1>& el);
};

template <class T1>
ostream& operator <<(ostream& s, const StackQueue<T1>& el)
{
    Element<T1>* current;
    for (current = el.head; current != NULL; current = current->next)
        s << *current << " ";
    return s;
}

// Двусвязанный стэк
template < typename T1 >
class DoubleLinkedStack : public Stack<T1>
{
public:
    DoubleLinkedStack() : Stack<T1>() { }

    virtual ~DoubleLinkedStack()

    {
        Element<T1>* cur = this->head;
        while (cur != NULL)
        {
            Element<T1>* to_delete = cur;
            cur = cur->next;
            delete to_delete;
        }
        this->head = NULL;
        this->count = 0;
        this->head = NULL;
    }

    Element<T1>* push(T1 value)
    {
        if (this->isEmpty())
        {
            this->head = new Element<T1>(value);
            this->tail = this->head;
            this->head->next = NULL;
            this->head->prev = NULL;
        }
        else
        {
            Element<T1>* old_tail = this->tail;
            Stack < T1 >::push(value);
            this->tail->prev = old_tail;
        }
        (this->count)++;
        return this->tail;
    }

    Element<T1>* pop()
    {
        if (this->tail == NULL || this->tail == this->head) return Stack < T1 >::pop();

        Element<T1>* res = this->tail;
        this->tail = this->tail->prev;
        this->tail->next->prev = NULL;
        this->tail->next = NULL;
        (this->count)--;
        return res;
    }

    Element<T1>* insert(T1 value, int index)
    {
        if (index < 0)
        {
            throw IndexOutOfRangeException("Index < 0");
        }
        else if (index <= this->count)
        {
            Element<T1>* cur = this->head;
            int cur_num = 0;

            while (cur_num < index)
            {
                cur = cur->next;
                cur_num++;
            }

            // Вставка в начало
            if (cur == this->head)
            {
                Element<T1>* old = this->head;
                this->head = new Element<T1>(value);
                this->head->next = old;
                old->prev = this->head;
                (this->count)++;
                return this->head;
            }
            // Вставка между началом и концом
            else if (cur != NULL)
            {
                Element<T1>* old_prev = cur->prev;

                cur->prev = new Element<T1>(value);
                cur->prev->next = cur;
                cur->prev->prev = old_prev;
                old_prev->next = cur->prev;
                (this->count)++;
                return cur->prev;
            }
            // Вставка после хвоста
            else
            {
                Element<T1>* old_tail = this->tail;
                Stack < T1 >::push(value);
                this->tail->prev = old_tail;
                return this->tail;
            }
        }
        else
        {
            throw IndexOutOfRangeException("Index > len(Stack)");
        }
    }

    Element<T1> remove(int index)
    {

        if (index < 0)
        {
            throw IndexOutOfRangeException("Index < 0");
        }
        else if (index < this->count)
        {
            Element<T1>* cur = this->head;
            int cur_num = 0;

            while (cur_num != index)
            {
                cur = cur->next;
                cur_num++;
            }

            Element<T1>* c_prev = cur->prev;
            Element<T1>* c_next = cur->next;

            if (cur == this->head)
            {
                this->head = this->head->next;
            }
            if (cur == this->tail)
            {
                this->tail = this->tail->prev;
            }

            Element<T1> ans(*cur);
            ans.next = NULL;
            ans.prev = NULL;

            delete cur;
            cur = NULL;

            if (c_prev != NULL)
                c_prev->next = c_next;
            if (c_next != NULL)
                c_next->prev = c_prev;

            (this->count)--;
            return ans;

        }

        else
        {
            throw IndexOutOfRangeException("Index > tail index");
        }
    }

    Element<T1>* find(T1 value)
    {
        Element<T1>* current = this->head;
        for (; current != NULL; current = current->next)
        {
            if (current->info == value)
            {
                return current;
            }
        }
        return 0;
    }
};


template < typename T1 >
class MyDoubleLinkedList : public DoubleLinkedStack<T1>
{
public:
    MyDoubleLinkedList() : DoubleLinkedStack<T1>() { }

    // Конструктор копий. Необходим для работы фильтра.
    MyDoubleLinkedList(const MyDoubleLinkedList& M)
    {
        if (M.count == 0)
        {
            this->head = M.head;
            this->tail = M.tail;
            this->count = M.count;
        }

        else
        {
            this->head = M.head;
            Element<T1>* cur = this->head->next;
            while (cur != M.tail)
            {
                this->push(cur->info);
                cur = this->tail;
            }
            this->count = M.count;
        }
    }

    ~MyDoubleLinkedList() override
    {
        cout << "MyDoubleLinkedList Destructor called" << endl;
    }

    Element<T1>* push(T1 value)
    {
        return DoubleLinkedStack < T1 >::push(value);
    }

    Element<T1>* pop()
    {
        if (this->isEmpty())
            return NULL;

        Element<T1>* res = this->head;
        (this->count)--;
        if (this->head == this->tail)
        {
            this->head = this->tail = NULL;
            return res;
        }
        this->head = this->head->next;
        return res;
    }

    Element<T1>* insert(T1 value, int index)
    {
        return DoubleLinkedStack < T1 >::insert(value, index);
    }

    Element<T1> remove(int index)
    {
        return DoubleLinkedStack < T1 >::remove(index);
    }

    Element<T1>* find(T1 value)
    {
        return DoubleLinkedStack < T1 >::find(value);
    }

    // фильтр, принимающий функцию 
    template < typename T2 >
    MyDoubleLinkedList filter(bool(*criterion)(T1& value_to_comparison, T2 param), T2 param_for_search_in_value)

    {
        MyDoubleLinkedList<T1> ans;
        Element<T1>* cur = this->head;
        while (cur != nullptr)
        {
            if (criterion(cur->info, param_for_search_in_value))
            {
                ans.push(cur->info);
            }
            cur = cur->next;
        }
        return ans;
    }

    // рекурсивный фильтр, принимающий функцию
    template < typename T2 >
    MyDoubleLinkedList < T1 >* filter_recursive(bool(*criterion)(T1& value_to_comparison, T2 param), T2 param_for_search_in_value, Element < T1 >* cur = NULL, MyDoubleLinkedList < T1 >* ans = NULL)

    {
        if (ans == NULL && cur == NULL)
        {
            cur = this->head;
            ans = new MyDoubleLinkedList<T1>;
        }

        // База рекурсии
        if (cur == NULL)
        {
            return ans;
        }

        // Добавление элемента
        if (criterion(cur->info, param_for_search_in_value))
        {
            ans->push(cur->info);
        }

        return filter_recursive(criterion, param_for_search_in_value, cur->next, ans);
    }

    void save(ofstream& s)
    {
        s << this->count << endl;
        Element<T1>* cur = this->head;
        for (int i = 0; i < this->count; ++i)
        {
            s << (*cur) << endl;
            cur = cur->next;
        }
    }

    void load(ifstream& s)
    {
        int count_of_elements;
        string line;
        getline(s, line);
        std::istringstream iss(line);
        iss >> count_of_elements;
        for (int i = 0; i < count_of_elements; ++i)
        {
            T1 cur;
            s >> cur;
            this->push(cur);
        }

    }

    template <class T1>
    friend ostream& operator <<(ostream& s, const MyDoubleLinkedList<T1>& el);
    template <class T1>
    friend istream& operator >>(istream& s, const MyDoubleLinkedList<T1>& el);
};

template <class T1>
ostream& operator <<(ostream& s, const MyDoubleLinkedList<T1>& el)
{
    Element<T1>* current;
    for (current = el.head; current != NULL; current = current->next)
        s << *current << " ";
    return s;
}

template <class T1>
istream& operator >>(istream& s, const MyDoubleLinkedList<T1>& el)
{
    for (Element<T1>* current = el.head; current != NULL; current = current->next)
        s >> *current;
    return s;
}


// функция для фильтра по дате рождения
template <class T>
bool FilterType(Programmer value, T s, T type)
{
    if (type == "second_name")
    {
        if (value.second_name != s)
            return true;
    }
    if (type == "first_name")
    {
        if (value.first_name != s)
            return true;
    }
    if (type == "email")
    {
        if (value.email != s)
            return true;
    }
    if (type == "skype")
    {
        if (value.skype != s)
            return true;
    }
    if (type == "telegram")
    {
        if (value.telegram != s)
            return true;
    }
    if (type == "programming_language")
    {
        if (value.programming_language != s)
            return true;
    }
    if (type == "workplace")
    {
        if (value.workplace != s)
            return true;
    }
    if (type == "level")
    {
        if (value.level != s)
            return true;
    }
    return false;
}
ostream& set_manip(ostream& f)
{
    f << left << oct;
    return f;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    // Тестирование 6.2 пункт 2.
    // Выделяем память для списка динамически (используя указатель на базовый класс).
    DoubleLinkedStack<int>* BaseDoubleLinkedList = new MyDoubleLinkedList<int>();

    BaseDoubleLinkedList->push(10);
    BaseDoubleLinkedList->push(20);
    BaseDoubleLinkedList->push(30);

    cout << *BaseDoubleLinkedList << endl;

    // // Преобразование указателя базового класса в указатель производного класса с помощью dynamic_cast
    MyDoubleLinkedList<int>* DerivedDoubleLinkedList = dynamic_cast<MyDoubleLinkedList<int>*>(BaseDoubleLinkedList);

    if (DerivedDoubleLinkedList != nullptr)
    {
        cout << "Dynamic cast успешен!" << endl;

        // Добавляем элемент через производный класс
        DerivedDoubleLinkedList->push(40);
        cout << "Список после добавления элемента через производный класс: " << *DerivedDoubleLinkedList << endl;
    }
    else
    {
        cout << "Dynamic cast не удался!" << endl;
    }

    delete BaseDoubleLinkedList;
    // Вывод: 
    // 10 20 30
    // Dynamic cast успешен!
    // Список после добавления элемента через производный класс : 10 20 30 40
    // MyDoubleLinkedList Destructor called

    // тестирование 6.1
    cout << "Тестирование задание 6.1 пункт 1" << endl;
    cout << "Для Stack: " << endl;
    Stack<int> MyStack;
    Queue<int> MyQuare;
    StackQueue<int> MyStackQuare;

    for (int i = 0; i < 10; i++)
        MyStack.push(i);
    cout << MyStack << endl;

    Element<int>* res = MyStack.pop();
    cout << "Удалённый элемент: " << res->info << endl;
    cout << "Обновлённый список: " << MyStack << endl;

    cout << "Для Quare: " << endl;
    for (int i = 0; i < 10; i++)
        MyQuare.push(i);
    cout << MyQuare << endl;

    Element<int>* res2 = MyQuare.pop();
    cout << "Удалённый элемент: " << res2->info << endl;
    cout << "Обновлённый список: " << MyQuare << endl;

    cout << "Для StackQuare: " << endl;
    for (int i = 0; i < 10; i++)
        MyStackQuare.push_back(i);
    cout << MyStackQuare << endl;

    Element<int>* res3 = MyStackQuare.pop_front();
    cout << "Удалённый элемент: " << res3->info << endl;
    cout << "Обновлённый список: " << MyStackQuare << endl;

    MyStackQuare.push_front(1232);
    cout << "Добавленный элемент: " << 1232 << endl;
    cout << "Обновлённый список: " << MyStackQuare << endl;

    Element<int>* res4 = MyStackQuare.pop_back();
    cout << "Удалённый элемент: " << res4->info << endl;
    cout << "Обновлённый список: " << MyStackQuare << endl;

    cout << "Тестирование задание 6.1 пункт 2:";

    DoubleLinkedStack<int> MyDoubleStack;

    for (int i = 0; i < 10; i++)
        MyDoubleStack.push(i);
    cout << MyDoubleStack << endl;


    Programmer a("Pogba", "Paul", "puaulpog@gmail.com", "PogbaPaul", "PogbaPaul", "Python", "Ebay!", 7);
    Programmer b("Spertsyan", "Eduard", "edosperts@gmail.com", "SpertsyanE", "edospertsyan", "C++", "Dell", 10);
    Programmer c("Arshavin", "Andrey", "arshavin@gmail.com", "ArshavinA", "AndrArsh", "Java", "Ebay", 6);
    DoubleLinkedStack<Programmer> S;
    DoubleLinkedStack<Programmer> D;
    S.push(a);
    S.push(b);
    S.push(c);

    Programmer aa("Pogba", "Paul", "puaulpog@gmail.com", "PogbaPaul", "PogbaPaul", "Python", "Ebay!", 7);
    Programmer bb("Spertsyan", "Eduard", "edosperts@gmail.com", "SpertsyanE", "edospertsyan", "C++", "Dell", 10);
    Programmer cc("Arshavin", "Andrey", "arshavin@gmail.com", "ArshavinA", "AndrArsh", "Java", "Ebay", 6);

    MyDoubleLinkedList<Programmer> D2;
    D2.push(aa);
    //cout << D2.filter(FilterType, string("28.11.2005"));


}