#pragma once

/*Dynamic Array template class that acts as a custom std::vector class
 *Should be a templated class DynamicArray<T>
 *Stores elements on the heap
 *Supports: push_back, pop_back, operator[], size(), capcity(), clear()
 * when full, size * 2
 * should not leak memory
 **** Constraints ****
 * Use new/delete[] for now (no maloc)
 * Dont wrap std::vector
 * */

#include <iostream>
#include <new>
#include <stdexcept>
#include <memory>
#include <utility>

namespace Dwarf {

    template <typename T>
    class DynamicArray {
      public:
        // constuctor / desctructor
        DynamicArray() : m_Size(0), m_Capacity(4) {
            m_Elements = std::make_unique<T[]>(m_Capacity);
        }
        DynamicArray(int reservedCapacity) : m_Size(0), m_Capacity(reservedCapacity) {
            if (reservedCapacity <= 0)
                throw std::invalid_argument("Capacity must be >0\n");
            m_Elements = std::make_unique<T[]>(m_Capacity);
        }

        // copy constructor
        DynamicArray(const DynamicArray& other)
            : m_Size(other.m_Size), m_Capacity(other.m_Capacity) {
            this->m_Elements = std::make_unique<T[]>(m_Capacity);
            for (int i = 0; i < other.m_Size; i++) {
                this->m_Elements[i] = other.m_Elements[i];
            }
        }

        // copy constructor
        DynamicArray(DynamicArray&& other) : m_Size(other.m_Size), m_Capacity(other.m_Capacity) {
            m_Elements       = std::move(other.m_Elements);
            other.m_Size     = 0;
            other.m_Capacity = 0;
        }

        ~DynamicArray() = default;

        // pushes index at the end of the array
        void push_back(T value) {
            if (m_Size == m_Capacity) {
                resize();
            }
            m_Elements[m_Size] = value;
            m_Size++;
        }

        // takes last element in the array
        T pop_back() {
            if (m_Size < 1) {
                throw std::out_of_range("Array is empty!");
            }
            T val = m_Elements[m_Size - 1];
            m_Size--;
            return val;
        }

        // getters
        int size() const { return m_Size; }
        int capacity() const { return m_Capacity; }

        // empties array - keeps size allocated at this moment
        void clear() { m_Size = 0; }

        // ----- Operator overloads ------
        // operator[] overload allows picking element at a specific index
        T& operator[](int i) {
            if (i >= m_Size || i < 0)
                throw std::out_of_range("Index is out of range");
            return m_Elements[i];
        }

        // copy operator overload allows arrayB = arrayA
        DynamicArray& operator=(const DynamicArray& other) {
            if (this == &other) { // if b is equal to the memory location of a - more specifically a
                                  // self copy guard -- probably does not work with unique_ptrs
                return *this;
            }
            // delete old mem, allocate new, copy new
            this->m_Capacity = other.m_Capacity;
            this->m_Size     = other.m_Size;
            this->m_Elements = std::make_unique<T[]>(this->m_Capacity);
            for (int i = 0; i < other.m_Size; i++) {
                this->m_Elements[i] = other.m_Elements[i];
            }
            return *this;
        }

        // move opperator
        DynamicArray& operator=(DynamicArray&& other) {
            if (this == &other) {
                return *this;
            }
            m_Size           = other.m_Size;
            m_Capacity       = other.m_Capacity;
            m_Elements       = std::move(other.m_Elements);
            other.m_Size     = 0;
            other.m_Capacity = 0;
            return *this;
        }

        // iterator stuff
        T* begin() { return &m_Elements[0]; }

        T* end() { return &m_Elements[m_Size]; }
        const T* begin() const { return &m_Elements[0]; }
        const T* end() const { return &m_Elements[m_Size]; }

      private:
        std::unique_ptr<T[]> m_Elements;
        int m_Size;
        int m_Capacity;

      private:
        void resize() {
            int newCapacity                 = m_Capacity * 2;
            std::unique_ptr<T[]> tmpElement = std::make_unique<T[]>(newCapacity);
            for (int i = 0; i < m_Size; i++) {
                tmpElement[i] = std::move(m_Elements[i]);
            }
            m_Elements = std::move(tmpElement);
            m_Capacity = newCapacity;
        }
    };

} // namespace Dwarf
