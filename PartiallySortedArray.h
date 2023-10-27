#ifndef PARTIALLY_SORTED_ARRAY_H
#define PARTIALLY_SORTED_ARRAY_H

#include <vector>
#include <algorithm>

template<typename T = int>
class PartiallySortedArray {
public:
    using value_type = T;
    using reference = T &;
    using pointer = T *;
    using size_type = std::size_t;

    class Iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer_type = T *;
        using reference_type = T &;

        Iterator() : m_ptr(nullptr) {};

        explicit Iterator(pointer_type ptr) : m_ptr(ptr) {}

        reference_type operator*() const {
            return *m_ptr;
        }

        pointer_type operator->() {
            return m_ptr;
        }

        Iterator &operator++() {
            m_ptr++;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        Iterator &operator--() {
            m_ptr--;
            return *this;
        }

        Iterator operator--(int) {
            Iterator tmp = *this;
            --(*this);
            return tmp;
        }

        difference_type operator-(const Iterator &right) const {
            return m_ptr - right.m_ptr;
        }

        bool operator==(const Iterator &b) {
            return this->m_ptr == b.m_ptr;
        };

        bool operator!=(const Iterator &b) {
            return this->m_ptr != b.m_ptr;
        };

    private:
        pointer_type m_ptr;
    };

    explicit PartiallySortedArray() : size(0), capacity(0), arr(new T(0)) {
        this->firstPositive = Iterator(arr);
        this->firstZero = Iterator(arr);
        this->last = Iterator(arr);
        this->base = Iterator(arr);
    }

    Iterator begin() {
        return base;
    }

    Iterator end() {
        return Iterator(arr + size);
    }

    size_type getSize() const {
        return this->size;
    }

    size_type getCapacity() const {
        return this->capacity;
    };

    T &get_item(size_type index) const {
        return arr[index];
    }

    Iterator find(const T &elem) {
        if (elem < 0) {
            return std::find(base, firstZero, elem);
        } else if (elem == 0) {
            return std::find(firstZero, firstPositive, elem);
        } else {
            return std::find(firstPositive, last, elem);
        }
    }

    void insert(const T &elem) {
        if (isFull()) {
            expand(2 * capacity + 1);
        }
        arr[size] = elem;
        size++;
        if (elem == 0) {
            swap(firstPositive, last);
            firstPositive++;
        }
        if (elem < 0) {
            swap(firstPositive, last);
            swap(firstZero, firstPositive);
            firstPositive++;
            firstZero++;
        }
        last++;
    }

    void erase(Iterator it) {
        last--;
        if (*it > 0) {
            swap(it, last);
        } else if (*it == 0) {
            firstPositive--;
            swap(it, firstPositive);
            swap(firstPositive, last);
        } else if (*it < 0) {
            firstZero--;
            firstPositive--;
            swap(it, firstZero);
            swap(firstZero, firstPositive);
            swap(firstPositive, last);
        }
        size--;
    }


    bool isEmpty() const {
        return size == 0;
    }

    bool isFull() const {
        return size == capacity;
    }

    void swap(Iterator &a, Iterator &b) {
        std::iter_swap(a, b);
    }

private:
    void expand(size_type new_capacity) {
        if (new_capacity <= this->capacity)
            return;

        auto new_items_container = new T[new_capacity];
        for (size_type i{}; i < this->size; ++i) {
            new_items_container[i] = arr[i];
        }

        delete[] arr;
        arr = new_items_container;
        this->capacity = new_capacity;
        this->firstZero = Iterator(arr + (firstZero - base));
        this->firstPositive = Iterator(arr + (firstPositive - base));
        this->last = Iterator(arr + (last - base));
        this->base = Iterator(arr);
    }

private :
    Iterator base;
    Iterator firstZero;
    Iterator firstPositive;
    Iterator last;
    T *arr;
    size_t capacity;
    size_t size;
};

template<class InputIterator, class OutputIterator>
void
merge(InputIterator first1, InputIterator last1,
      InputIterator first2, InputIterator last2,
      OutputIterator result) {
    InputIterator it1 = first1;
    InputIterator it2 = first2;
    OutputIterator res = result;
    while (it1 != last1 && it2 != last2)
        *res++ = (*it1 <= *it2) ? *it1++ : *it2++;
    while (it1 != last1)
        *res++ = *it1++;
    while (it2 != last2)
        *res++ = *it2++;
}

#endif //PARTIALLY_SORTED_ARRAY_H
