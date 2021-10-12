#include <iostream>

namespace examples
{

    template <class T>
    class Matrix
    {
    private:
        int _size;
        T **_m;
        Matrix(T x)
        {
            _m = new T *[_size];
            for (int i = 0; i < _size; i++)
            {
                _m[i] = new T[_size];
                for (int j = 0; j < _size; j++)
                {
                    this->_m[i][j] = x;
                }
            }
        }

    public:
        Matrix(int size)
        {
            _size = size;
            _m = new T *[_size];
            for (int i = 0; i < _size; i++)
            {
                _m[i] = new T[_size];
                for (int j = 0; j < _size; j++)
                {
                    _m[i][j] = 1 + rand() % 9;
                }
            }
        }
        friend Matrix &operator*(Matrix &a, Matrix &b)
        {
            Matrix *r = new Matrix(a._size);
            for (int i = 0; i < a._size; i++)
            {
                for (int j = 0; j < a._size; j++)
                {
                    for (int k = 0; k < a._size; k++)
                    {
                        r->_m[i][j] += a._m[i][k] * b._m[k][j];
                    }
                }
            }
            return *r;
        }
        friend Matrix &operator+(Matrix &a, Matrix &b)
        {
            Matrix *r = new Matrix(a._size);
            for (int i = 0; i < a._size; i++)
            {
                for (int j = 0; j < a._size; j++)
                {
                    r->_m[i][j] += a._m[i][j] + b._m[i][j];
                }
            }
            return *r;
        }
        bool operator==(Matrix &b)
        {
            if (this->_m == nullptr)
                return false;
            for (int i = 0; i < _size; i++)
            {
                for (int j = 0; j < _size; j++)
                {
                    if (this->_m[i][j] != b._m[i][j])
                        return false;
                }
            }
            return true;
        }
        void ShowMatrix()
        {
            if (_m == nullptr)
                return;
            for (int i = 0; i < _size; i++)
            {
                for (int j = 0; j < _size; j++)
                {
                    std::cout << _m[i][j] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
    };
}