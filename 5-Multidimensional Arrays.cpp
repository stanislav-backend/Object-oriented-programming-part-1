#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

class Exception : public exception {
protected:
    //сообщение об ошибке
    char* str;

public:
    Exception(const char* s) {
        str = new char[strlen(s) + 1];
        strcpy(str, s);
    }
    Exception(char* s) {
        str = new char[strlen(s) + 1];
        strcpy(str, s);
    }
    Exception(const Exception& e) {
        str = new char[strlen(e.str) + 1];
        strcpy(str, e.str);
    }
    ~Exception() { delete[] str; }

    virtual void print() { cout << "Exception: " << str << "; " << what(); }
};

class IndexOutOfBoundsExeption : public Exception {
protected:
    int Row;
    int Col;

public:
    IndexOutOfBoundsExeption(char* s, int row, int col) : Exception(s) {
        Row = row;
        Col = col;
    }
    IndexOutOfBoundsExeption(const char* s, int row, int col) : Exception(s) {
        Row = row;
        Col = col;
    }
    virtual void print() {
        cout << "IndexOutOfBoundsExeption: " << str << " , row: " << Row
            << ", col :" << Col;
    }
};

class InvalidOperationException : public Exception {
protected:
    int Row1;
    int Col1;
    int Row2;
    int Col2;

public:
    InvalidOperationException(char* s, int row1, int col1, int row2 = -1,
        int col2 = -1)
        : Exception(s) {
        Row1 = row1;
        Col1 = col1;
        Row2 = row2;
        Col2 = col2;
    }
    InvalidOperationException(const char* s, int row1, int col1, int row2 = -1,
        int col2 = -1)
        : Exception(s) {
        Row1 = row1;
        Col1 = col1;
        Row2 = row2;
        Col2 = col2;
    }
    virtual void print() {
        cout << "InvalidOperationException: " << str << " row1: " << Row1
            << " col1: " << Col1 << " row2: " << Row2 << " col2: " << Col2;
    }
};

class WrongSizeException : public Exception {
protected:
    int Row1;
    int Col1;
    int Row2;
    int Col2;

public:
    WrongSizeException(char* s, int row1, int col1, int row2 = -1, int col2 = -1)
        : Exception(s) {
        Row1 = row1;
        Col1 = col1;
        Row2 = row2;
        Col2 = col2;
    }
    WrongSizeException(const char* s, int row1, int col1, int row2 = -1,
        int col2 = -1)
        : Exception(s) {
        Row1 = row1;
        Col1 = col1;
        Row2 = row2;
        Col2 = col2;
    }
    virtual void print() {
        cout << "WrongSizeException: " << str << " row1: " << Row1
            << " col1: " << Col1 << " row2: " << Row2 << " col2: " << Col2;
    }
};

class NonPositiveSizeException : public WrongSizeException {
public:
    NonPositiveSizeException(char* s, int Row, int Col)
        : WrongSizeException(s, Row, Col) {}
    NonPositiveSizeException(const char* s, int Row, int Col)
        : WrongSizeException(s, Row, Col) {}
    virtual void print() {
        cout << "NonPositiveSizeException: " << str << " row1: " << Row1
            << " col1: " << Col1;
    }
};

class TooLargeSizeException : public WrongSizeException {
public:
    TooLargeSizeException(char* s, int Row, int Col)
        : WrongSizeException(s, Row, Col) {}
    TooLargeSizeException(const char* s, int Row, int Col)
        : WrongSizeException(s, Row, Col) {}
    virtual void print() {
        cout << "TooLargeSizeException: " << str << " row1: " << Row1
            << " col1: " << Col1;
    }
};

class InvalidArgumentException : public Exception {
public:
    InvalidArgumentException(char* s) : Exception(s) {}
    InvalidArgumentException(const char* s) : Exception(s) {}
    virtual void print() { cout << "InvalidArgumentException: " << str; }
};

template <class T> class BaseMatrix {
protected:
    T** ptr;
    int height;
    int width;

public:
    BaseMatrix(int Height = 2, int Width = 2) {
        if (Height < 1 || Width < 1)
            throw NonPositiveSizeException(
                "Non Positive Size Exceptionn in BaseMatrix constructor", Height,
                Width);
        if (Height > 16000 || Width > 16000)
            throw TooLargeSizeException(
                "Too Large Size Exception in BaseMatrix constructor", Height, Width);
        height = Height;
        width = Width;
        ptr = new T * [height];
        for (int i = 0; i < height; i++)
            ptr[i] = new T[width];
    }

    BaseMatrix(const BaseMatrix& M) {
        height = M.height;
        width = M.width;
        ptr = new T * [height];
        for (int i = 0; i < height; i++) {
            ptr[i] = new T[width];
            for (int j = 0; j < width; j++)
                ptr[i][j] = M.ptr[i][j];
        }
    }

    ~BaseMatrix() {

        //деструктор
        if (ptr != NULL) {
            for (int i = 0; i < height; i++)
                delete[] ptr[i];
            delete[] ptr;
            ptr = NULL;
        }
    }

    BaseMatrix operator=(const BaseMatrix& M) {
        if (height != M.height || width != M.width) {
            if (ptr != NULL) {
                for (int i = 0; i < height; i++)
                    delete[] ptr[i];
                delete[] ptr;
                ptr = NULL;
            }
            height = M.height;
            width = M.width;
            ptr = new T * [height];
            for (int i = 0; i < height; i++) {
                ptr[i] = new T[width];
            }
        }
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++)
                ptr[i][j] = M.ptr[i][j];
        }

        return *this;
    }

    T Trace() {
        if (width != height)
            throw InvalidOperationException("InvalidOperationException Trace, Cannot "
                "calculate trace for non-square matrix",
                height, width);
        T ans = 0;
        for (int i = 0; i < width; i++)
            ans += ptr[i][i];
        return ans;
    }

    BaseMatrix<T> operator+(BaseMatrix<T>& M) {
        if (width != M.width || height != M.height)
            throw InvalidOperationException("InvalidOperationException + undefined "
                "values for matrix of different sizes",
                height, width, M.height, M.width);
        BaseMatrix<T> A;
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                A(i, j) = ptr[i][j] + M(i, j);
        return A;
    }

    void print() {
        //вывод
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++)
                cout << ptr[i][j] << " ";
            cout << "\n";
        }
    }

    T& operator()(int i, int j) {
        if (i < 0 || i >= height || j < 0 || j > width)
            throw IndexOutOfBoundsExeption("IndexOutOfBoundsExeption", i, j);
        return ptr[i][j];
    }

    template <class T1> friend ostream& operator<<(ostream& s, BaseMatrix<T1>& M);
    template <class T1> friend istream& operator>>(istream& s, BaseMatrix<T1>& M);
    template <class T1>
    friend ifstream& operator>>(ifstream& s, BaseMatrix<T1>& M);
};

template <class T1> ostream& operator<<(ostream& s, BaseMatrix<T1>& M) {

    if (typeid(s) == typeid(ofstream)) {
        s << M.height << " " << M.width;
        for (int i = 0; i < M.height; i++)
            for (int j = 0; j < M.width; j++)
                s << " " << M.ptr[i][j];
        return s;
    }
    for (int i = 0; i < M.height; i++) {
        for (int j = 0; j < M.width; j++)
            cout << M.ptr[i][j] << " ";
        cout << "\n";
    }
    return s;
}

template <class T1> istream& operator>>(istream& s, BaseMatrix<T1>& M) {
    for (int i = 0; i < M.height; i++)
        for (int j = 0; j < M.width; j++)
            s >> M.ptr[i][j];
    return s;
}

template <class T1> ifstream& operator>>(ifstream& s, BaseMatrix<T1>& M) {

    int w, h;
    s >> h >> w;

    if (h != M.height || w != M.width) {
        if (M.ptr != NULL) {
            for (int i = 0; i < M.height; i++)
                delete[] M.ptr[i];
            delete[] M.ptr;
            M.ptr = NULL;
        }
        M.ptr = new T1 * [h];
        M.height = h;
        M.width = w;

        for (int i = 0; i < M.height; i++) {
            M.ptr[i] = new T1[M.width];
        }
    }

    for (int i = 0; i < M.height; i++)
        for (int j = 0; j < M.width; j++)
            s >> M.ptr[i][j];
    return s;
}

template <class T2> class Matrix : public BaseMatrix<T2> {
public:
    Matrix(int Height = 2, int Width = 2) : BaseMatrix<T2>(Height, Width) {}
    Matrix(const BaseMatrix<T2>& M) : BaseMatrix<T2>(&M) {}
    ~Matrix() {
        //деструктор
        if (this->ptr != NULL) {
            for (int i = 0; i < this->height; i++)
                delete[] this->ptr[i];
            delete[] this->ptr;
            this->ptr = NULL;
        }
    }

    // В строках матрицы, в которых есть отрицательные элементы,
    // произвести циклический сдвиг вправо на число этих элементов (для
    // каждой строки оно своё).

    Matrix<T2> ShiftRowsWithNegatives() {
        Matrix<T2> shiftedMatrix(this->height, this->width);

        for (int i = 0; i < this->height; ++i) {
            bool hasNegative = false;
            int negativeCount = 0;

            for (int j = 0; j < this->width; ++j) {
                if (this->ptr[i][j] < 0) {
                    hasNegative = true;
                    ++negativeCount;
                }
            }

            if (hasNegative) {
                for (int j = 0; j < this->width; ++j) {
                    int newIndex = (j + negativeCount) % this->width;
                    shiftedMatrix.ptr[i][newIndex] = this->ptr[i][j];
                }
            }
            else {
                for (int j = 0; j < this->width; ++j) {
                    shiftedMatrix.ptr[i][j] = this->ptr[i][j];
                }
            }
        }
        return shiftedMatrix;
    }

    template <class T1> friend istream& operator>>(istream& s, Matrix<T1>& M);
    template <class T1> friend ostream& operator<<(ostream& s, Matrix<T1>& M);
};

// Заполение по столбцам
template <class T1> istream& operator>>(istream& s, Matrix<T1>& M) {
    for (int i = 0; i < M.height; i++)
        for (int j = 0; j < M.width; j++)
            s >> M.ptr[j][i];
    return s;
}

template <class T1> ostream& operator<<(ostream& s, Matrix<T1>& M) {

    for (int i = 0; i < M.height; i++) {
        for (int j = 0; j < M.width; j++)
            cout << M.ptr[i][j] << " ";
        cout << "\n";
    }
    return s;
}

template <class T1> T1 function(T1 x) { return x * x; }

template <class T1> T1 function2(T1 x) { return -1; }

int main() {
    try {
        Matrix<double> M;
        M(0, 0) = 1;
        M(0, 1) = 2;
        M(1, 0) = 3;
        M(1, 1) = 4;
        cout << "M maxtrix" << endl;
        M.print();
        cout << endl;

        // BaseMatrix<double> M2;
        // cin >> M2;
        // cout << M2;

        Matrix<double> M1(3, 3);
        cin >> M1;
        cout << M1;

        Matrix<double> test_func;
        test_func(0, 0) = -1;
        test_func(0, 1) = 2;
        test_func(1, 0) = -3;
        test_func(1, 1) = -4;
        test_func = test_func.ShiftRowsWithNegatives();
        cout << "ShiftRowsWithNegatives" << endl;
        test_func.print();
        cout << endl;

        BaseMatrix<double> test2;

        // test2 = M1.Func(nullptr);
        // cout << "Func(Matrix)"<<endl; test2.print(); cout << endl;

        // BaseMatrix<double> M3(2,2);
        // BaseMatrix<double> M4(3,2);
        //(M3+M4).print();
        // cout << M4.Trace();

        // BaseMatrix<double> M5(16300,16300);
        // cout << M5;

        BaseMatrix<double> M6[10];
        for (int i = 0; i < 10; i++)
            M6[i](0, 0) = M6[i](0, 1) = M6[i](1, 0) = M6[i](1, 1) = 2 << i;
        ofstream fout("1.txt");
        if (fout) {
            fout << "13\n";
            for (int i = 0; i < 10; i++)
                fout << M6[i] << "\n";
            BaseMatrix<double> M_test1(1, 3);
            BaseMatrix<double> M_test2(3, 1);
            BaseMatrix<double> M_test3(3, 3);
            M_test1(0, 0) = 1;
            M_test1(0, 1) = 2;
            M_test1(0, 2) = 3;
            M_test2(0, 0) = 1;
            M_test2(1, 0) = 2;
            M_test2(2, 0) = 3;
            M_test3(0, 0) = 1;
            M_test3(0, 1) = 2;
            M_test3(0, 2) = 3;
            M_test3(1, 0) = 1;
            M_test3(1, 1) = 2;
            M_test3(1, 2) = 3;
            M_test3(2, 0) = 1;
            M_test3(2, 1) = 2;
            M_test3(2, 2) = 3;
            fout << M_test3 << "\n";
            fout << M_test1 << "\n";
            fout << M_test2 << "\n";

            fout.close();
        }

        ifstream fin("1.txt");
        if (fin) {
            int n;
            fin >> n;
            BaseMatrix<double>* p = new BaseMatrix<double>[n];
            for (int i = 0; i < n; i++) {
                fin >> p[i];
                cout << p[i];
                cout << "Trace : " << p[i].Trace() << endl << endl;
            }
            delete[] p;
            fin.close();
        }

    }
    catch (TooLargeSizeException ex) {
        cout << "Too Large Size has been caught ";
        ex.print();
    }
    catch (NonPositiveSizeException ex) {
        cout << "Non Positive Size has been caught ";
        ex.print();
    }
    catch (InvalidArgumentException ex) {
        cout << "Invalid Argument  has been caught ";
        ex.print();
    }
    catch (IndexOutOfBoundsExeption ex) {
        cout << "Index out of bounds has been caught ";
        ex.print();
    }
    catch (Exception ex) {
        cout << "exception has been caught ";
        ex.print();
    }
    catch (exception ex) {
        cout << "exception has been caught ";
        ex.what();
    }
    catch (...) {
        cout << "Something has been caught ";
    }

    return 0;
}
