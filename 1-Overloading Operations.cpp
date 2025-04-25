#include <iostream>
using namespace std;

class Matrix
{
private:
	int matrix[2][2];
public:
	Matrix() {
	 int element;
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				cout << "Введите значения элемента матрицы" << "[" << i + 1 << "]" << "[" << j + 1 << "]: ";
				cin >> element;
				matrix[i][j] = element;
			}
		}
	}

	Matrix(int a, int b, int c, int d) {
		matrix[0][0] = a;
		matrix[0][1] = b;
		matrix[1][0] = c;
		matrix[1][1] = d;
	}
	Matrix(const Matrix& M) {
		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < 2; ++j) {
				matrix[i][j] = M.matrix[i][j];
			}
		}
	}
	~Matrix() {}

	bool operator<(const Matrix& other) {
		return det() < other.det();
	}

	int det() const {
		return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	}

	void print() {
		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < 2; ++j) {
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}
	}

	friend bool operator<(int num, const Matrix& M) { return num < M.det(); }
	friend bool InverseMatrix(Matrix M) { return M.det() != 0; }
};

int main()
{
	setlocale(LC_ALL, "ru");
	int num = 5;
	Matrix A(3, 7, 6, 2);
	Matrix B;
	A.det() < B.det() ? cout << "Определитель матрицы A < чем определитель матрицы B" << endl : cout << "Определитель матрицы A > чем определитель матрицы B" << endl;
	(A.det() < num) ? cout << "Определитель матрицы A < числа num" << endl : cout << "Определитель матрицы A > числа num" << endl;
	InverseMatrix(A) ? cout << "Для матрицы A существует обратная ей матрица" << endl : cout << "Для матрицы A не существует обратной ей матрицы" << endl;
	A.print();
	return 0;
}