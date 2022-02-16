#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

template <class ValueType>
class Heap {
public:
    Heap() {
        vector_ = new std::vector<ValueType>();
    }

    template <class Iterator>
    Heap(Iterator begin, Iterator end) {
        vector_ = new std::vector<ValueType>(begin, end);
    }

    Heap(std::initializer_list<ValueType> list) {
        vector_ = new std::vector<ValueType>();
        for (auto elem : list) {
            insert(elem);
        }
    }

    Heap(const Heap &input) {
        std::copy(input.vector_->begin(), input.vector_->end(), vector_->begin());
    }

    Heap &operator=(const Heap &input) {
        if (&input == this) {
            return *this;
        }

        std::copy(input.vector_->begin(), input.vector_->end(), vector_->begin());
        return *this;
    }

    Heap(Heap &&input) {
        vector_ = input.vector_;
    }

    Heap &operator=(Heap &&input) {
        if (&input == this) {
            return *this;
        }

        vector_ = input.vector_;
        return *this;
    }

    ~Heap() {
        delete vector_;
    }

    size_t size() const {
        return vector_->size();
    }

    bool empty() const {
        return vector_->empty();
    }

    void insert(const ValueType &input) {
        vector_->push_back(input);
        siftUp(vector_->size() - 1);
    }

    ValueType extract() {
        if (vector_->empty()) {
            return 0;
        }

        ValueType min = vector_->at(0);
        if (vector_->size() > 1) {
            vector_->operator[](0) = vector_->at(vector_->size() - 1);
            vector_->pop_back();
            siftDown(0);
        }

        return min;
    }

    std::vector<ValueType> *vector_;

private:
    void siftUp(int i) {
        while (!(vector_->at(i) < vector_->at((i - 1) / 2))) {
            std::swap(vector_->at(i), vector_->at((i - 1) / 2));
            i = (i - 1) / 2;
        }
    }

    void siftDown(int i) {
        int left, right, j;

        while (2 * i + 1 < vector_->size()) {
            left = 2 * i + 1;
            right = 2 * i + 2;
            j = left;
            if (right < vector_->size() && vector_->at(right) < vector_->at(left)) {
                j = right;
            }

            if (vector_->at(i) < vector_->at(j)) {
                break;
            }

            std::swap(vector_->at(i), vector_->at(j));
            i = j;
        }
    }
};
