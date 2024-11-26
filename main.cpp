#include <iostream>
#include <cassert>
#include <stdexcept>

using namespace std;

class Vector {
private:
    int* arr;
    int capacity;
    int current;

public:
    Vector() : arr(new int[1]), capacity(1), current(0) {}

    ~Vector() {
        delete[] arr;
    }

    explicit Vector(size_t n) : arr(new int[n]), capacity(n), current(n) {
        for (size_t i = 0; i < n; ++i) {
            arr[i] = 0;
        }
    }


    Vector(const Vector& other) : arr(new int[other.capacity]), capacity(other.capacity), current(other.current) {
        for (int i = 0; i < current; ++i) {
            arr[i] = other.arr[i];
        }
    }


    Vector& operator=(const Vector& other) {
        if (this == &other) {
            return *this;
        }

        delete[] arr;

        capacity = other.capacity;
        current = other.current;
        arr = new int[capacity];

        for (int i = 0; i < current; ++i) {
            arr[i] = other.arr[i];
        }

        return *this;
    }


    Vector(Vector&& other) noexcept : arr(other.arr), capacity(other.capacity), current(other.current) {
        other.arr = nullptr;
        other.capacity = 0;
        other.current = 0;
    }


    Vector& operator=(Vector&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        delete[] arr;

        arr = other.arr;
        capacity = other.capacity;
        current = other.current;

        other.arr = nullptr;
        other.capacity = 0;
        other.current = 0;

        return *this;
    }

    void push(int data) {
        if (current == capacity) {
            int* temp = new int[2 * capacity];
            for (int i = 0; i < capacity; ++i) {
                temp[i] = arr[i];
            }
            delete[] arr;
            arr = temp;
            capacity *= 2;
        }
        arr[current++] = data;
    }

    int get(int index) const {
        if (index < current) {
            return arr[index];
        }
        return -1;
    }

    void clear() {
        delete[] arr;
        arr = nullptr;
        current = 0;
        capacity = 0;
    }

    int size() const { return current; }
    int getCapacity() const { return capacity; }

    void resize(int n) {
        if (n == size()) return;

        Vector temp;
        if(n > capacity) {
            capacity = n *2;
            for (int i = 0; i < current; ++i) {
                temp.push(arr[i]);
            }
            for (int i = current; i < n; ++i) {
                temp.push(0);
            }
        }else {
            for (int i = 0; i < n; ++i) {
                temp.push(arr[i]);
            }
        }
        *this = temp;
    }

    void assign(size_t n, int value) {
        clear();
        for (size_t i = 0; i < n; ++i) {
            push(value);  //
        }
    }

    int at(int index) const {
        if (index < 0) {
            index += current;
        }

        if (index < 0) {
            return arr[0];
        }

        if (index >= current) {
            return arr[current - 1];
        }

        return arr[index];
    }
};


class Stack {
private:
    Vector* vec;
public:
    ~Stack() { delete vec; }
    Stack() : vec(new Vector()) {}
    explicit Stack(const size_t n) { vec = new Vector(n); }
    Stack(const int a[], const size_t n) {
        vec = new Vector();
        for (int i = 0; i < n; i++)
            vec->push(a[i]);
    }
    Stack(const Stack& a) : vec(new Vector(*a.vec)) {}

    void clear() {
        vec->clear();
        vec = new Vector();
    }

    int at(int i) const {
        return vec->at(i);
    }

    void resize(size_t n) {
        vec->resize(n);
    }
    void assign(size_t n, int value) {
        vec->assign(n, value);
    }

    size_t length() const { return vec->size(); }
    bool empty() const { return vec->size() == 0; }

    void swap(Stack& a) noexcept { std::swap(vec, a.vec); }
};

void print(Stack& a) {
    for (int i = 0; i < a.length(); ++i) {
        cout << a.at(i) << endl;
    }
}
int main()
{
     int array[] = {1, 4, 7, 9};
		 Stack a(array, 4);
    assert(4 == a.length());
     assert(1 == a.at(0));
     assert(9 == a.at(10));
     print(a);

     Stack b(a);
     b.clear();
    assert(b.empty());

    Stack c;
    assert(c.empty());
    c.assign(3, 7);
   assert(3 == c.length());

    Stack d(5);
    assert(5 == d.length());
    d.resize(10);
    b.swap(d);
    assert(10 == b.length());
    assert(d.empty());
}