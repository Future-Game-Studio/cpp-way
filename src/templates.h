namespace examples
{
    template <class T>
    void bubbleSort(T a[], int n)
    {
        for (int i = 0; i < n - 1; i++)
            for (int j = n - 1; i < j; j--)
                if (a[j] < a[j - 1])
                    std::swap(a[j], a[j - 1]);
    }

    template <class T>
    void printArray(T a[], int n)
    {
        for (int i = 0; i < n; i++)
            std::cout << a[i] << " ";
        std::cout << std::endl;
    }

    template <class T, typename Func>
    void f(T a[], int n, Func lamFunc)
    {
        for (int i = 0; i < n; i++)
            a[i] = lamFunc(a[i]);
    }

    template <class T>
    T multByTwo(T x)
    {
        return x * 2;
    }

    template <class T>
    T divByTwo(T x)
    {
        return x / 2;
    }

    template <class T>
    void transform(T a[], int n, const std::function<T(T)> &lambda)
    {
        for (int i = 0; i < n; i++)
            a[i] = lambda(a[i]);
    }
}