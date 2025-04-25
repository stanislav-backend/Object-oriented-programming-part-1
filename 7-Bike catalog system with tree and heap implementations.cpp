#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

class IndexOutOfRangeException : public exception {
protected:
	string error;
public:
	IndexOutOfRangeException(string in) : exception()
	{
		error = in;
	}
	void print() const
	{
		cout << error << '\n';
	}
};

class InvalidOperation : public exception
{
protected:
	string error;
public:
	InvalidOperation(string in) : exception()
	{
		error = in;
	}
	void print() const
	{
		cout << error << endl;
	}
};

//пункт 7.1
//ключи - марка и диаметр колеса (brand и wheel diameter)
//класс C - Bike
//минимальный набор полей - марка (brand), тип (type), тип тормозов (brake_type), количество колес (number_of_wheels), диаметр колеса (wheel_diameter), наличие амортизаторов (presence_of_shock_absorbers), возрастная характеристика (age_characteristics) - детский или взрослый (child или adult)

class Brand_and_Wheel_Diameter
{
public:
	string brand;
	int wheel_diameter; //диаметр в дюймах


	Brand_and_Wheel_Diameter(string b = "Giant", int wd = 29)
	{
		brand = b;
		wheel_diameter = wd;
	}

	Brand_and_Wheel_Diameter(const Brand_and_Wheel_Diameter& C)
	{
		brand = C.brand;
		wheel_diameter = C.wheel_diameter;

	}

	bool operator==(const Brand_and_Wheel_Diameter& C)
	{
		return (brand == C.brand && wheel_diameter == C.wheel_diameter);
	}

	bool operator>(const Brand_and_Wheel_Diameter& C)
	{
		if (brand > C.brand) return true;
		if (brand == C.brand) {
			if (wheel_diameter > C.wheel_diameter) return true;
		}
		return false;
	}

	bool operator<(const Brand_and_Wheel_Diameter& C)
	{
		if (brand < C.brand) return true;
		if (brand == C.brand) {
			if (wheel_diameter < C.wheel_diameter) return true;
		}
		return false;
	}

	~Brand_and_Wheel_Diameter() {}

	friend ostream& operator<<(ostream& s, const Brand_and_Wheel_Diameter& C);
};

ostream& operator<<(ostream& s, const Brand_and_Wheel_Diameter& C)
{
	s << "Brand: " << C.brand << "\nWheel diameter: " << C.wheel_diameter;
	return s;
}


class Bike
{
public:
	string brand;
	string type;
	string brake_type;
	int number_of_wheels;
	int wheel_diameter;
	bool presence_of_shock_absorbers;
	string age_characteristics;



	Bike(string b = "Giant", string t = "off-road", string bt = "rim", int nw = 2, int wd = 29, bool psa = true, string ac = "adult")
	{
		brand = b;
		type = t;
		brake_type = bt;
		number_of_wheels = nw;
		wheel_diameter = wd;
		presence_of_shock_absorbers = psa;
		age_characteristics = ac;
	}
	Bike(const Bike& C)
	{
		brand = C.brand;
		type = C.type;
		brake_type = C.brake_type;
		number_of_wheels = C.number_of_wheels;
		wheel_diameter = C.wheel_diameter;
		presence_of_shock_absorbers = C.presence_of_shock_absorbers;
		age_characteristics = C.age_characteristics;
	}

	bool operator==(const Bike& C)
	{
		return (brand == C.brand && type == C.type && brake_type == C.brake_type && number_of_wheels == C.number_of_wheels && wheel_diameter == C.wheel_diameter && presence_of_shock_absorbers == C.presence_of_shock_absorbers && age_characteristics == C.age_characteristics);
	}

	//пункт 7.2
	//диаметр колеса, количество колес; марка (по возрастанию)

	bool operator>(const Bike& C)
	{
		if (wheel_diameter > C.wheel_diameter)
			return true;
		if (wheel_diameter == C.wheel_diameter)
		{
			if (number_of_wheels > C.number_of_wheels)
				return true;
			if (number_of_wheels == C.number_of_wheels)
			{
				if (brand > C.brand)
					return true;
			}
		}
		return false;
	}

	~Bike() {}

	friend ostream& operator<<(ostream& s, const Bike& C);
};

ostream& operator<<(ostream& s, const Bike& C)
{
	s << "Brand: " << C.brand << "\nType: " << C.type << "\nBrake type: " << C.brake_type << "\nNumber of wheels: " << C.number_of_wheels << "\nWheel diameter: " << C.wheel_diameter << "\nPresence of shock absorbers: " << C.presence_of_shock_absorbers << "\nAge characteristics: " << C.age_characteristics;
	return s;
}

template<class T1, class T2>
class Node
{
protected:
	//ключ
	T1 key;

	//значение
	T2 data;

	//не можем хранить Node, но имеем право хранить указатель
	Node* left;
	Node* right;
	Node* parent;

	//переменная, необходимая для поддержания баланса дерева
	int height;

	virtual Node<T1, T2>* Min(Node<T1, T2>* current)
	{
		while (current->getLeft() != NULL)
			current = current->getLeft();
		return current;
	}

	virtual Node<T1, T2>* Max(Node<T1, T2>* current)
	{
		while (current->getRight() != NULL)
			current = current->getRight();
		return current;
	}

public:
	//доступные извне переменные и функции
	virtual void setKey(T1 k) { key = k; }
	virtual void setData(T2 d) { data = d; }

	virtual T1 getKey() { return key; }
	virtual T2 getData() { return data; }
	int getHeight() { return height; }

	virtual Node* getLeft() { return left; }
	virtual Node* getRight() { return right; }
	virtual Node* getParent() { return parent; }

	virtual void setLeft(Node* N) { left = N; }
	virtual void setRight(Node* N) { right = N; }
	virtual void setParent(Node* N) { parent = N; }


	Node<T1, T2>(T1 k, T2 d)
	{
		key = k;
		data = d;
		left = right = parent = NULL;
		height = 0;
	}

	Node<T1, T2>()
	{
		left = NULL;
		right = NULL;
		parent = NULL;
		key = T1();
		data = T2();
		height = 0;
	}

	virtual void print()
	{
		cout << "\n(" << key << ", " << data << ")";
	}

	virtual void setHeight(int h)
	{
		height = h;
	}

	template<class T1, class T2> friend ostream& operator<< (ostream& stream, Node<T1, T2>& N);
};

template<class T1, class T2>
ostream& operator<< (ostream& stream, Node<T1, T2>& N)
{
	stream << "\nNode Key: " << N.key << ", Node Data: " << N.data << ", height: " << N.height;
	return stream;
}
template<class T1, class T2>
void print(Node<T1, T2>* N) { cout << "\n(" << N->getKey() << ", " << N->getData() << ")"; }


template<class T1, class T2>
class Tree
{
protected:
	//корень - его достаточно для хранения всего дерева
	Node<T1, T2>* root;

	//функция добавления узла в дерево
	virtual Node<T1, T2>* push_R(Node<T1, T2>* N)
	{
		return push_R(N, root);
	}

	virtual Node<T1, T2>* push_R(Node<T1, T2>* N, Node<T1, T2>* Current)
	{
		//не передан добавляемый узел
		if (N == NULL) return NULL;

		if (Current == NULL) Current = root;

		//пустое дерево - добавляем в корень
		if (root == NULL)
		{
			root = N;

			return root;
		}

		if (Current->getKey() > N->getKey())
		{
			//идем влево
			if (Current->getLeft() != NULL) return push_R(N, Current->getLeft());
			else {
				Current->setLeft(N);
				N->setParent(Current);
			}
		}
		if (Current->getKey() < N->getKey())
		{
			//идем вправо
			if (Current->getRight() != NULL) return push_R(N, Current->getRight());
			else {
				Current->setRight(N);
				N->setParent(Current);
			}
		}
		//будем считать, что у нас все значения уникальны, потому совпадений не будет
		//if (Current->getKey() == N->getKey()) 
		return N;
	}

	//поиск узла в дереве. Второй параметр - в каком поддереве искать, первый - что искать
	virtual Node<T1, T2>* Find1_R(T2 Data, Node<T1, T2>* Current)
	{
		//база рекурсии
		if (Current == NULL || Current->getData() == Data) return Current;

		//рекурсивный вызов
		if (Current->getData() > Data) return Find1_R(Data, Current->getLeft());
		return Find1_R(Data, Current->getRight());
	}

	virtual Node<T1, T2>* Find2_R(T1 Key, Node<T1, T2>* Current)
	{
		//база рекурсии
		if (Current == NULL || Current->getKey() == Key) return Current;

		//рекурсивный вызов
		if (Current->getKey() > Key) return Find2_R(Key, Current->getLeft());
		return Find2_R(Key, Current->getRight());
	}

public:
	//доступ к корневому элементу
	virtual Node<T1, T2>* getRoot() { return root; }

	//конструктор дерева: в момент создания дерева ни одного узла нет, корень смотрит в никуда
	Tree<T1, T2>() { root = NULL; }

	//рекуррентная функция добавления узла. Интерфейс аналогичен (добавляется корень поддерева, 
	//куда нужно добавлять узел), но вызывает сама себя - добавление в левое или правое поддерево

	//функция для добавления числа. Делаем новый узел с этими данными и вызываем нужную функцию добавления в дерево
	virtual Node<T1, T2>* push(T1 k, T2 value) {
		Node<T1, T2>* N = new Node<T1, T2>(k, value);
		return push_R(N);
	}

	//удаление узла
	virtual void Remove(Node<T1, T2>* N, Node<T1, T2>* back = NULL) {
		if (N == NULL) return;

		Node<T1, T2>* tmp = NULL;
		if (N->getLeft() != NULL) {
			//замена на элемент в левом поддереве относительно N
			tmp = Max(N->getLeft());
		}
		else if (N->getRight() != NULL) {
			//замена на элемент в правом поддереве относительно N
			tmp = Min(N->getRight());
		}
		else if (N->getParent() == NULL) {
			//если родителя нет, то это корень
			root = new Node<T1, T2>();
			return;
		}

		if (tmp->getParent()->getKey() > tmp->getKey()) {
			//tmp - слева относительно его parent
			if (tmp->getRight() == NULL && tmp->getLeft() != NULL) {
				tmp->getParent()->setLeft(tmp->getLeft());
				tmp->getLeft()->setParent(tmp->getParent());
			}
			else {
				tmp->getParent()->setLeft(tmp->getRight());
				if (tmp->getRight() != NULL)
					tmp->getRight()->setParent(tmp->getParent());
			}
		}
		else {
			//tmp - справа относитильно его parent
			if (tmp->getLeft() == NULL && tmp->getRight() != NULL) {
				tmp->getParent()->setRight(tmp->getRight());
				tmp->getRight()->setParent(tmp->getParent());
			}
			else {
				tmp->getParent()->setRight(tmp->getLeft());
				if (tmp->getLeft() != NULL)
					tmp->getLeft()->setParent(tmp->getParent());
			}
		}
		N->setKey(tmp->getKey());
		N->setData(tmp->getData());

		//обновление высот
		height_update(tmp->getParent());
		back = tmp;
		delete tmp;
	}

	virtual void height_update(Node<T1, T2>* N)
	{
		if (N != NULL) {
			if (N->getParent() != NULL)
				N->setHeight(N->getParent()->getHeight() + 1);
			height_update(N->getLeft());
			height_update(N->getRight());
		}
	}

	//поиск минимума и максимума в дереве
	virtual Node<T1, T2>* Min(Node<T1, T2>* Current = NULL)
	{
		if (root == NULL) return NULL;
		if (Current == NULL) Current = getRoot();
		Node<T1, T2>* current = Current;
		while (current->getLeft() != NULL)
			current = current->getLeft();

		return current;
	}

	virtual Node<T1, T2>* Max(Node<T1, T2>* Current = NULL)
	{
		if (root == NULL) return NULL;
		if (Current == NULL) Current = getRoot();
		Node<T1, T2>* current = Current;
		while (current->getRight() != NULL)
			current = current->getRight();

		return current;
	}

	//поиск узла в дереве
	virtual Node<T1, T2>* Find(T2 Data)
	{
		if (root == NULL) return NULL;
		return Find1_R(Data, root);
	}

	//три обхода дерева
	virtual void PreOrder(Node<T1, T2>* N, void (*f)(Node<T1, T2>*))
	{
		if (N != NULL) f(N);
		if (N != NULL && N->getLeft() != NULL) PreOrder(N->getLeft(), f);
		if (N != NULL && N->getRight() != NULL)	PreOrder(N->getRight(), f);
	}

	//InOrder-обход даст отсортированную последовательность
	virtual void InOrder(Node<T1, T2>* N, void (*f)(Node<T1, T2>*))
	{
		if (N != NULL && N->getLeft() != NULL) InOrder(N->getLeft(), f);
		if (N != NULL) f(N);
		if (N != NULL && N->getRight() != NULL)	InOrder(N->getRight(), f);
	}

	virtual void PostOrder(Node<T1, T2>* N, void (*f)(Node<T1, T2>*))
	{
		if (N != NULL && N->getLeft() != NULL) PostOrder(N->getLeft(), f);
		if (N != NULL && N->getRight() != NULL)	PostOrder(N->getRight(), f);
		if (N != NULL) f(N);
	}

	//обход через поиск в глубину
	void dfs(Node<T1, T2>* Current)
	{
		if (Current != NULL)
		{
			cout << (Current->getKey()) << '\t';
			if (Current->getLeft() != NULL) cout << Current->getLeft()->getKey();
			cout << '\t';
			if (Current->getRight() != NULL) cout << Current->getRight()->getKey();
			cout << '\n';
			dfs(Current->getLeft());
			dfs(Current->getRight());
		}
	}

	//интерфейс для функции поиска в виде перегрузки операции[]
	T2 operator[](T1 k)
	{
		return Find2_R(k, getRoot())->getData();
	}
};

template<class T1, class T2 >
class AVL_Tree : public Tree<T1, T2>
{
protected:
	//определение разности высот двух поддеревьев
	int bfactor(Node<T1, T2>* p) {
		int hl = 0;
		int hr = 0;
		if (p->getLeft() != NULL)
			hl = p->getLeft()->getHeight();
		if (p->getRight() != NULL)
			hr = p->getRight()->getHeight();
		return (hr - hl);
	}

	//при добавлении узлов в них нет информации о балансе, т.к. не ясно, куда в дереве они попадут
	//после добавления узла рассчитываем его высоту (расстояние до корня) и редактируем высоты в узлах, где это
	//значение могло поменяться
	void fixHeight(Node<T1, T2>* p)
	{
		int hl = 0;
		int hr = 0;
		if (p->getLeft() != NULL)
			hl = p->getLeft()->getHeight();
		if (p->getRight() != NULL)
			hr = p->getRight()->getHeight();
		p->setHeight((hl > hr ? hl : hr) + 1);
	}

	//краеугольные камни АВЛ-деревьев - процедуры поворотов
	Node<T1, T2>* RotateRight(Node<T1, T2>* p) //правый поворот вокруг p
	{
		Node<T1, T2>* q = p->getLeft();

		p->setLeft(q->getRight());
		q->setRight(p);

		if (p == Tree<T1, T2>::root)
			Tree<T1, T2>::root = q;
		else {
			if (p->getParent()->getLeft() == p)
				p->getParent()->setLeft(q);
			else
				p->getParent()->setRight(q);
		}

		q->setParent(p->getParent());
		p->setParent(q);
		if (p->getLeft() != NULL) p->getLeft()->setParent(p);

		fixHeight(p);
		fixHeight(q);
		return q;
	}

	Node<T1, T2>* RotateLeft(Node<T1, T2>* q) //левый поворот вокруг q
	{
		Node<T1, T2>* p = q->getRight();

		q->setRight(p->getLeft());
		p->setLeft(q);

		if (q == Tree<T1, T2>::root)
			Tree<T1, T2>::root = p;
		else {
			if (q->getParent()->getLeft() == q)
				q->getParent()->setLeft(p);
			else
				q->getParent()->setRight(p);
		}

		p->setParent(q->getParent());
		q->setParent(p);
		if (q->getRight() != NULL) q->getRight()->setParent(q);

		fixHeight(q);
		fixHeight(p);
		return p;
	}

	//балансировка поддерева узла p - вызов нужных поворотов в зависимости от показателя баланса
	Node<T1, T2>* Balance(Node<T1, T2>* p) //балансировка узла p
	{
		fixHeight(p);
		if (bfactor(p) == 2)
		{
			if (bfactor(p->getRight()) < 0) RotateRight(p->getRight());
			return RotateLeft(p);
		}
		if (bfactor(p) == -2)
		{
			if (bfactor(p->getLeft()) > 0) RotateLeft(p->getLeft());
			return RotateRight(p);
		}

		return p; //балансировка не нужна
	}

public:
	//конструктор AVL_Tree вызывает конструктор базового класса Tree
	AVL_Tree<T1, T2>() : Tree<T1, T2>() {}

	virtual Node<T1, T2>* push_R(Node<T1, T2>* N)
	{
		return push_R(N, Tree<T1, T2>::root);
	}

	//рекуррентная функция добавления узла
	//устроена аналогично, но вызывает сама себя - добавление в левое или правое поддерево
	virtual Node<T1, T2>* push_R(Node<T1, T2>* N, Node<T1, T2>* Current)
	{
		//вызываем функцию push_R из базового класса
		Node<T1, T2>* pushedNode = Tree<T1, T2>::push_R(N, Current);
		//применяем к добавленному узлу балансировку
		if (Current != NULL)
			return Balance(Current);
		return pushedNode;
	}

	//функция для добавления числа
	//делаем новый узел с этими данными и вызываем нужную функцию добавления в дерево
	virtual Node<T1, T2>* push(T1 k, T2 n)
	{
		Node<T1, T2>* N = new Node<T1, T2>;
		N->setData(n);
		N->setKey(k);
		return push_R(N);
	}

	//добавил back - значение, которое необходимо балансировать // (изменения)
	//удаление узла
	virtual void Remove(Node<T1, T2>* N, Node<T1, T2>* tmp = NULL)
	{
		Node<T1, T2>* back = new Node<T1, T2>;
		Tree<T1, T2>::Remove(N, back);
		Balance(back);
	}
};


template <class T1, class T2>
class Heap
{
private:
	//массив
	T1* arr_key;
	T2* arr_data;
	//сколько элементов добавлено
	int len;
	//сколько памяти выделено
	int size;
public:
	//доступ к вспомогательным полям кучи и оператор индекса
	int getCapacity() { return size; }
	int getCount() { return len; }

	//конструктор
	Heap<T1, T2>(int MemorySize = 1024)
	{
		arr_key = new T1[MemorySize];
		arr_data = new T2[MemorySize];
		len = 0;
		size = MemorySize;
	}

	void push(T1 key, T2 data)
	{
		if (len >= size)
			throw IndexOutOfRangeException(string("IndexOutOfRange Exception in push"));

		arr_key[len] = key;
		arr_data[len] = data;

		len++;
		SiftUp();
	}

	void Remove(T1 key)
	{
		for (int i = 0; i < len; i++)
		{
			if (arr_key[i] == key)
			{
				T1 temp_key;
				T2 temp_data;
				if (i == len - 1) {
					arr_key[i] = temp_key;
					arr_data[i] = temp_data;
				}
				else {
					Swap(i, len - 1);
					arr_key[len - 1] = temp_key;
					arr_data[len - 1] = temp_data;

					if (arr_key[i] > temp_key)
						SiftUp(i);
					else
						Heapify(i);
				}
				len--;
			}
		}
	}

	void Delete(T1 key)
	{
		for (int i = 0; i < len; i++) {
			if (arr_key[i] == key)
				Swap(i, len - 1);
		}
		throw IndexOutOfRangeException(string("NotFindKey Exception in Delete"));
		len--;
	}

	T2& operator[](T1 key)
	{
		for (int i = 0; i < len; i++) {
			if (arr_key[i] == key)
				return arr_data[i];
		}
		throw IndexOutOfRangeException(string("NotFindKey Exception in []"));
	}

	void Swap(int id1, int id2)
	{
		if (id1 < 0 || id1 >= len || id2 < 0 || id2 >= len)
			throw IndexOutOfRangeException(string("IndexOutOfRange Exception in Swap"));

		T1 temp_key;
		T2 temp_data;
		temp_key = arr_key[id1];
		arr_key[id1] = arr_key[id2];
		arr_key[id2] = temp_key;

		temp_data = arr_data[id1];
		arr_data[id1] = arr_data[id2];
		arr_data[id2] = temp_data;
	}

	int GetLeftChildIndex(int id)
	{
		if (id < 0 || id << 1 >= len)
			throw IndexOutOfRangeException(string("IndexOutOfRange Exception in GetLeftChildIndex"));

		return id << 1 + 1;
	}

	int GetRightChildIndex(int id)
	{
		if (id < 0 || id << 1 >= len)
			throw IndexOutOfRangeException(string("IndexOutOfRange Exception in GetRightChildIndex"));

		return id << 1 + 2;
	}

	int GetParentIndex(int id)
	{
		if (id < 0 || id >= len)
			throw IndexOutOfRangeException(string("IndexOutOfRange Exception in GetParentIndex"));

		if (id % 2)
			return id >> 1;
		return id >> 1 - 1;
	}

	//восстановление свойств кучи после удаления или добавления элемента
	void Heapify(int id = 0)
	{
		if (id < 0 || id >= len)
			throw IndexOutOfRangeException(string("IndexOutOfRange Exception in Heapify"));

		int leftChild = 2 * id + 1;
		int rightChild = 2 * id + 2;
		int largestChild;

		//нужно сравнить элементы и при необходимости произвести просеивание вниз
		if (leftChild < len && rightChild >= len)
		{
			//ребенок один
			if (arr_key[leftChild] > arr_key[id])
			{
				Swap(leftChild, id);
				Heapify(leftChild);
			}
		}
		if (rightChild < len)
		{
			//ребенка два
			largestChild = arr_key[leftChild] > arr_key[rightChild] ? leftChild : rightChild;
			if (arr_key[largestChild] > arr_key[id])
			{
				Swap(largestChild, id);
				Heapify(largestChild);
			}
		}
	}

	void SiftUp(int id = -1)
	{
		if (id == -1) id = len - 1;
		if (id < 0 || id >= len)
			throw IndexOutOfRangeException(string("IndexOutOfRange Exception in SiftUp"));

		if (id != 0)
		{
			int parent_id = GetParentIndex(id);
			if (arr_key[id] > arr_key[parent_id])
			{
				Swap(id, parent_id);
				SiftUp(parent_id);
			}
		}
	}

	T2 ExtractMax()
	{
		if (len == 0)
			throw InvalidOperation(string("InvalidOperation in ExatractMax"));
		T1 res_key = arr_key[0];
		T2 res_data = arr_data[0];
		Swap(0, len - 1);
		len--;
		Heapify();
		return res_data;
	}

	void print()
	{
		for (int i = 0; i < len; i++) {
			cout << "Key:\n" << arr_key[i] << "\nData:\n" << arr_data[i];
		}
	}

	~Heap()
	{
		cout << "Heap destructor\n";
		if (arr_key != NULL && arr_data != NULL) {
			delete[] arr_key;
			delete[] arr_data;
		}
	}
};


int main()
{
	try
	{
		//class Bike && class Brand_and_Wheel_Diameter
		Bike C0("Merida", "road", "disk", 2, 25, true, "adult");
		Brand_and_Wheel_Diameter K0(C0.brand, C0.wheel_diameter);
		Bike C1("Gary Turner", "urban", "pedal", 2, 27, true, "adult");
		Brand_and_Wheel_Diameter K1(C1.brand, C1.wheel_diameter);
		Bike C2("Merida", "urban", "tape", 3, 15, false, "child");
		Brand_and_Wheel_Diameter K2(C2.brand, C2.wheel_diameter);
		Bike C3("Ghost", "off-road", "roller", 2, 26, true, "adult");
		Brand_and_Wheel_Diameter K3(C3.brand, C3.wheel_diameter);
		Bike C4("Scott", "road", "stirrups", 3, 17, true, "child");
		Brand_and_Wheel_Diameter K4(C4.brand, C4.wheel_diameter);
		Bike C5("Shwinn", "off-road", "rim", 2, 23, false, "adult");
		Brand_and_Wheel_Diameter K5(C5.brand, C5.wheel_diameter);
		Bike C6("Cube", "urban", "disk", 2, 25, false, "adult");
		Brand_and_Wheel_Diameter K6(C6.brand, C6.wheel_diameter);
		Bike C7("Kellys", "special", "roller", 2, 28, false, "adult");
		Brand_and_Wheel_Diameter K7(C7.brand, C7.wheel_diameter);
		Bike C8;
		Brand_and_Wheel_Diameter K8(C8.brand, C8.wheel_diameter);
		Bike C9("Trek", "road", "pedal", 3, 18, true, "child");
		Brand_and_Wheel_Diameter K9(C9.brand, C9.wheel_diameter);


		//Tree
		Tree<Brand_and_Wheel_Diameter, Bike> T;
		T.push(K0, C0);
		T.push(K1, C1);
		T.push(K2, C2);
		T.push(K3, C3);
		T.push(K4, C4);
		T.push(K5, C5);
		T.push(K6, C6);
		T.push(K7, C7);
		T.push(K8, C8);
		T.push(K9, C9);

		//operator []
		cout << "\n-----\noperator []:\n";
		cout << T[K8] << "\n\n";
		cout << T[Brand_and_Wheel_Diameter("Giant", 29)] << "\n\n";
		cout << T[K8] << "\n\n";


		//Min
		Node<Brand_and_Wheel_Diameter, Bike>* Mi = T.Min();
		cout << "Min = " << Mi->getData();
		cout << "\n\n";


		//Max
		Node<Brand_and_Wheel_Diameter, Bike>* Ma = T.Max();
		cout << "Max = " << Ma->getData();
		cout << "\n\n";


		//Find Value
		cout << "Find: " << C0 << "\t-> " << T.Find(C0) << "\n\n";
		cout << "Find: " << C5 << "\t-> " << T.Find(C5) << "\n\n";
		cout << "Find: " << C3 << "\t-> " << T.Find(C3) << "\n\n";
		cout << "Find: " << C7 << "\t-> " << T.Find(C7) << "\n\n";
		cout << "Find: " << C2 << "\t-> " << T.Find(C2) << "\n\n";


		//PreOrder && InOrder
		void (*f_ptr)(Node<Brand_and_Wheel_Diameter, Bike>*); f_ptr = print;
		/*
		cout << "\n-----\nPreorder:";
		T.PreOrder(T.getRoot(), f_ptr);
		cout << "\n-----\nInorder:";
		T.InOrder(T.getRoot(), f_ptr);*/


		//Remove
		//Print Tree with dfs
		T.dfs(T.getRoot());
		Node<Brand_and_Wheel_Diameter, Bike>* N1 = T.getRoot()->getRight();
		Node<Brand_and_Wheel_Diameter, Bike>* N2 = T.getRoot()->getLeft();

		cout << "\n-----\nRemove:\n";
		T.Remove(N1); T.dfs(T.getRoot());

		cout << "\n-----\nRemove:\n";
		T.Remove(N2); T.dfs(T.getRoot());

		for (int i = 0; i < 10; i++)
		{
			cout << "\n-----\nRemove:\n";
			T.Remove(T.getRoot()); T.dfs(T.getRoot());
		}



		//AVL_Tree	
		cout << "\n-----AVL_Tree-----\n";
		AVL_Tree<Brand_and_Wheel_Diameter, Bike> AVLT;
		AVLT.push(K0, C0);
		AVLT.push(K1, C1);
		AVLT.push(K2, C2);
		AVLT.push(K3, C3);
		AVLT.push(K4, C4);
		AVLT.push(K5, C5);
		AVLT.push(K6, C6);
		AVLT.push(K7, C7);
		AVLT.push(K8, C8);
		AVLT.push(K9, C9);


		//Min
		Node<Brand_and_Wheel_Diameter, Bike>* TMi = AVLT.Min();
		cout << "Min = " << TMi->getData();
		cout << "\n\n";


		//Max
		Node<Brand_and_Wheel_Diameter, Bike>* TMa = AVLT.Max();
		cout << "Max = " << TMa->getData();
		cout << "\n\n";


		//Find Value
		cout << "Find: " << C1 << "\t-> " << AVLT.Find(C1) << "\n\n";
		cout << "Find: " << C9 << "\t-> " << AVLT.Find(C9) << "\n\n";
		cout << "Find: " << C4 << "\t-> " << AVLT.Find(C4) << "\n\n";
		cout << "Find: " << C8 << "\t-> " << AVLT.Find(C8) << "\n\n";
		cout << "Find: " << C6 << "\t-> " << AVLT.Find(C6) << "\n\n";


		//PreOrder && InOrder
		/*
		cout << "\n-----\nPreorder:";
		T.PreOrder(T.getRoot(), f_ptr);
		cout << "\n-----\nInorder:";
		T.InOrder(T.getRoot(), f_ptr);*/


		//Remove
		//Print AVL_Tree with dfs
		AVLT.dfs(AVLT.getRoot());
		Node<Brand_and_Wheel_Diameter, Bike>* N3 = AVLT.getRoot()->getRight();
		Node<Brand_and_Wheel_Diameter, Bike>* N4 = AVLT.getRoot()->getLeft();

		cout << "\n-----\nRemove:\n";
		AVLT.Remove(N3); AVLT.dfs(AVLT.getRoot());

		cout << "\n-----\nRemove:\n";
		AVLT.Remove(N4); AVLT.dfs(AVLT.getRoot());

		for (int i = 0; i < 10; i++) {
			cout << "\n-----\nRemove:\n";
			AVLT.Remove(AVLT.getRoot()); AVLT.dfs(AVLT.getRoot());
		}


		//Heap
		cout << "\n-----Heap-----\n";
		Heap<Brand_and_Wheel_Diameter, Bike> TreeHeap;
		TreeHeap.push(K0, C0);
		TreeHeap.push(K1, C1);
		TreeHeap.push(K2, C2);

		cout << "\n-----\nExtractMax:\n";
		cout << TreeHeap.ExtractMax() << "\n\n";


		cout << "\n-----\nRemove and Push:\n";
		TreeHeap.print(); cout << "\n";

		TreeHeap.Remove(K1);
		TreeHeap.print(); cout << "\n";

		TreeHeap.push(K3, C3);
		TreeHeap.push(K4, C4);
		TreeHeap.print(); cout << "\n";

		TreeHeap.Remove(K0);
		TreeHeap.print(); cout << "\n";

		TreeHeap.push(K5, C5);
		TreeHeap.push(K6, C6);
		TreeHeap.push(K7, C7);
		TreeHeap.print(); cout << "\n";

		TreeHeap.Remove(K2);
		TreeHeap.Remove(K3);
		TreeHeap.print(); cout << "\n";

		TreeHeap.push(K8, C8);
		TreeHeap.push(K9, C9);
		TreeHeap.print(); cout << "\n";

		TreeHeap.Remove(K9);
		TreeHeap.print(); cout << "\n";

		TreeHeap.Remove(K7);
		TreeHeap.print(); cout << "\n";

		TreeHeap.Remove(K8);
		TreeHeap.print(); cout << "\n";

		TreeHeap.Remove(K6);
		TreeHeap.print(); cout << "\n";

		TreeHeap.Remove(K5);
		TreeHeap.print(); cout << "\n";

		TreeHeap.Remove(K4);
		TreeHeap.print(); cout << "\n";

	}
	catch (IndexOutOfRangeException ex)
	{
		ex.print();
	}
	catch (InvalidOperation ex)
	{
		ex.print();
	}
	//catch (...) { cout << "Exception Not Found"; }
	char c;
	cin >> c;


	return 0;
}

