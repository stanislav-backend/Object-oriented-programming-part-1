#include <iostream>
#include <math.h>

using namespace std;

class MyArrayParent {
protected:
    //сколько памяти выделено?
    int capacity;
    //количество элементов - сколько памяти используем
    int count;
    //массив
    double* ptr;

public:
    //конструкторы и деструктор
    MyArrayParent(int Dimension = 100) {
        cout << "\nMyArray constructor";
        ptr = new double[Dimension];
        capacity = Dimension;
        count = 0;
    }
    //конструктор принимает существующий массив
    MyArrayParent(double* arr, int len)
    {
        cout << "\nMyArray constructor";
        ptr = new double[len];
        for (int i = 0; i < count; i++)
            ptr[i] = arr[i];
        capacity = len;
        count = len;
        //заполнить массив ptr, заполнить поля
    }
    //деструктор
    ~MyArrayParent() {
        cout << "\nMyArray destructor";
        if (ptr != NULL) {
            delete[] ptr;
            ptr = NULL;
        }
    }
    //обращение к полям
    int Capacity() { return capacity; }
    int Size() { return count; }

    double GetComponent(int index) {
        if (index >= 0 && index < count) return ptr[index];
        //сгенерировать исключение, если индекс неправильный
        return -1;
    }

    void SetComponent(int index, double value) {
        if (index >= 0 && index < count) ptr[index] = value;
        //сгенерировать исключение, если индекс неправильный
    }

    //добавление в конец нового значения
    void push(double value) {
        if (count < capacity) {
            ptr[count] = value;
            count++;
        }
        //что делаем, если массив заполнен?
    }

    //удаление элемента с конца
    void RemoveLastValue() {
        if (count >= 0) count--;
        //что делаем, если пуст?
    }

    double& operator[](int index) {
        if (index >= 0 && index < count)
            return ptr[index];
        throw "Индекс не может быть меньше 0 и больше count\n";
        //перегрузка оператора []
    }

    MyArrayParent& operator=(const MyArrayParent& V) {
        cout << "\noperator = ";
        if (capacity < V.capacity) {
            delete[] ptr;
            ptr = new double[V.capacity];
            capacity = V.capacity;
        }
        count = V.count;

        for (int i = 0; i < count; i++)
            ptr[i] = V.ptr[i];

        return *this;

        //оператор =
        // arr1 = arr2 = arr3; где arr_i - объекты нашего класса
    }

    MyArrayParent(const MyArrayParent& V) {
        cout << "\nCopy constructor";
        capacity = V.capacity;
        count = V.count;
        ptr = new double[capacity];

        for (int i = 0; i < count; i++)
            ptr[i] = V.ptr[i];
        //создание копии объекта - в основном, при возвращении результата из функции / передаче параметров в функцию
    }

    void print() {
        cout << "\nMyArr, size: " << count << ", values: {";
        int i = 0;
        for (i = 0; i < count; i++) {
            cout << ptr[i];
            if (i != count - 1) cout << ", ";
        }
        cout << "}";
    }

    //Отразить зеркально участки, находящиеся между отрицательными элементами
    MyArrayParent ReflectBetweenNegatives() {
        //создаем новый объект для хранения результата
        MyArrayParent result(count);

        //копируем значения из текущего объекта в результат
        for (int i = 0; i < count; i++) {
            result.ptr[i] = ptr[i];
        }

        //ищем отрицательные элементы и отражаем участки между ними
        bool isNegativeFound = false;
        int start = -1;
        for (int i = 0; i < count; i++) {
            if (ptr[i] < 0) {
                if (isNegativeFound) {
                    //отражаем участок между двумя отрицательными элементами
                    int end = i;
                    for (int j = start + 1; j < (start + end) / 2; j++) {
                        double temp = result.ptr[j];
                        result.ptr[j] = result.ptr[end - (j - start)];
                        result.ptr[end - (j - start)] = temp;
                    }
                }
                else {
                    isNegativeFound = true;
                }
                start = i;
            }
        }
        return result;
    }
};

class MyArrayChild : public MyArrayParent {
public:
    //используем конструктор родителя. Нужно ли что-то ещё?
    MyArrayChild(int Dimension = 100) : MyArrayParent(Dimension) {
        cout << "\nMyArrayChild constructor";
    }
    ~MyArrayChild() { cout << "\nMyArrayChild destructor\n"; }

    //удаление элемента 
    void RemoveAt(int index = -1) {
        if (index == -1) { RemoveLastValue(); return; }
        if (index < 0 || index >= count || count == 0) return;

        for (int i = index; i < count; i++)
            ptr[i] = ptr[i + 1];
        count--;

    }
    //поиск элемента
    int IndexOf(double value, bool bFindFromStart = true) {
        if (bFindFromStart)
        {
            for (int i = 0; i < count; i++)
                if (abs(value - ptr[i]) < 0.0001)
                    return i;
            return -1;
        }
        for (int i = count; i > 0; i++)
            if (abs(value - ptr[i]) < 0.0001)
                return i;
        return -1;
    }
    //вставка элемента
    void InsertAt(double value, int index = -1) {
        if (index == -1) { push(value); return; }
        if (index < 0 || index >= count || count >= capacity) return;

        for (int i = count - 1; i >= index; i--)
            ptr[i + 1] = ptr[i];
        ptr[index] = value;
        count++;
    }
    //выделение подпоследовательности
    MyArrayChild SubSequence(int StartIndex = 0, int Length = -1) {
        MyArrayChild res;
        for (int i = 0; i < Length; i++)
            res.push(ptr[i + StartIndex]);
        return res;

    }
    //добавление элемента в конец
    void operator +(double value) {
        push(value);
    }
};

class MySortedArray : public MyArrayChild {
protected:
    int BinSearchIterative(double value, int left, int right)
    {
        while (left <= right)
        {
            int middle = (left + right) / 2;
            if (abs(ptr[middle] - value) < 0.00001) return middle;
            if (ptr[middle] > value) right = middle - 1;
            else if (ptr[middle] < value) left = middle + 1;
        }
        return -1;
    }
    int BinSearchRecursion(double value, int left, int right)
    {
        if (left > right) return (abs(ptr[right] - value) < 0.00001) ? right : -1;
        int middle = (left + right) / 2;
        if (abs(ptr[middle] - value) < 0.00001) return middle;
        if (ptr[middle] > value) return BinSearchRecursion(value, left, middle - 1);
        else return BinSearchRecursion(value, middle + 1, right);
    }
    //функция видоизменена для реализации push: возвращает индекс ближайшего по значению элемента вместо точного совпадения
    int BinSearchRecursionForPush(double value, int left, int right)
    {
        if (left > right) return right;
        int middle = (left + right) / 2;
        if (abs(ptr[middle] - value) < 0.00001) return middle;
        if (ptr[middle] > value) return BinSearchRecursionForPush(value, left, middle - 1);
        else return BinSearchRecursionForPush(value, middle + 1, right);
    }

public:
    MySortedArray(int Dimension = 100) : MyArrayChild(Dimension) {
        cout << "\nMySortedArray constructor";
    }
    ~MySortedArray() { cout << "\nMySortedArray destructor\n"; }


    //переопределение метода ReflectBetweenNegatives
    MyArrayParent ReflectBetweenNegatives() {
        //т.к. массив уже отсортирован, отражение между отрицательными элементами не меняет порядок
        return *this;
    }

    //переопределение метода push для добавления элементов в отсортированный порядок
    void push(double value)
    {
        if (count >= capacity) return;
        if (count == 0) { MyArrayParent::push(value); return; }
        if (count == 1)
        {
            if (ptr[0] > value) InsertAt(value, 0);
            else MyArrayParent::push(value);
            return;
        }
        int index = BinSearchRecursionForPush(value, 0, count - 1);
        InsertAt(value, index + 1);
    }

    //переопределение метода IndexOf для поиска элемента в отсортированном массиве
    int IndexOf(double value, bool bFindFromStart = true) { return BinSearchIterative(value, 0, count - 1); }
};


int main()
{
    setlocale(LC_ALL, "RUS");
    // создание объекта MyArrayChild
    MyArrayChild arr;

    // добавление элементов в MyArrayChild
    for (int i = -10; i < 25; i++)
        arr.push(i);

    // печать массива MyArrayChild
    cout << "\nМассив MyArrayChild:";
    arr.print();

    // добавление элемента в MyArrayChild
    arr + 30;

    // печать массива MyArrayChild после добавления элемента
    cout << "\nПосле добавления 30 в MyArrayChild:";
    arr.print();

    // получение подпоследовательности из MyArrayChild и её печать
    cout << "\nПодпоследовательность из MyArrayChild:";
    arr.SubSequence(3, 5).print();

    // поиск элементов в MyArrayChild и печать индексов
    cout << "\nИндекс 13 в MyArrayChild: " << arr.IndexOf(13, true);
    cout << "\nИндекс 11 в MyArrayChild: " << arr.IndexOf(11);


    // создание объекта MySortedArray
    MySortedArray sort_arr;

    // добавление элементов в MySortedArray
    for (int i = 23; i > 0; i--)
        sort_arr.push(i);

    // печать отсортированного массива MySortedArray
    cout << "\nОтсортированный массив MySortedArray:";
    sort_arr.print();

    // поиск элементов в MySortedArray и печать индексов
    cout << "\nИндекс 13 в MySortedArray: " << sort_arr.IndexOf(13, true);
    cout << "\nИндекс 11 в MySortedArray: " << sort_arr.IndexOf(11);

    // удаление последнего элемента из MySortedArray
    sort_arr.RemoveAt();

    // печать MySortedArray после удаления последнего элемента
    cout << "\nПосле удаления последнего элемента из MySortedArray:";
    sort_arr.print();

    // печать емкости MySortedArray
    cout << "\nЕмкость MySortedArray: " << sort_arr.Capacity();

    return 0;
}

