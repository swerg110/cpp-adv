//
// Created by Sergei on 12/23/24.
//
#pragma once
#include <cstdint>
#include <exception>
#include <stdexcept>
#include <iostream>

template <typename Key, typename T, typename size_type, const size_type Size,
        class Compare = std::less<Key>,
        class Allocator = std::allocator<std::pair<const Key, T> > >
class avl_array {
    struct child_type {
        size_type left;
        size_type right;
    };

    Key key_[Size];
    T val_[Size];
    std::int8_t balance_[Size];
    child_type child_[Size];
    size_type parent_[Size];
    size_type size_;
    size_type root_;

    static const size_type EMPTY = Size;

    class iterator {
        avl_array* instance_;
        size_type idx_;

        friend class reverse_iterator;
        friend avl_array;

    public:
        iterator(avl_array* instance = nullptr, size_type idx = 0)
                : instance_(instance), idx_(idx) {}

        bool operator==(const iterator& rhs) const { return idx_ == rhs.idx_; }
        bool operator!=(const iterator& rhs) const { return !(*this == rhs); }
        T& operator*() const { return instance_->val_[idx_]; }
        Key& key() const { return instance_->key_[idx_]; }

        iterator& operator++() {
            if (idx_ >= Size) return *this;

            size_type i = instance_->child_[idx_].right;
            if (i != instance_->EMPTY) {
                for (; i != instance_->EMPTY; i = instance_->child_[i].left) {
                    idx_ = i;
                }
            } else {
                i = instance_->get_parent(idx_);
                while ((i != instance_->EMPTY) && (idx_ == instance_->child_[i].right)) {
                    idx_ = i;
                    i = instance_->get_parent(idx_);
                }
                idx_ = i;
            }
            return *this;
        }

        iterator operator++(int) {
            auto temp = *this;
            ++(*this);
            return temp;
        }
    };

    class reverse_iterator : public iterator {
    public:
        reverse_iterator(avl_array* instance = nullptr, size_type idx = 0)
                : iterator(instance, idx) {}

        reverse_iterator(const iterator& iter)
                : reverse_iterator(iter.instance_, iter.idx_) {
            ++(*this);
        }

        reverse_iterator& operator++() {
            if (*this == nullptr) return *this;
            size_type i = this->instance_->child_[this->idx_].left;
            if (i != this->instance_->EMPTY) {
                for (; i != this->instance_->EMPTY; i = this->instance_->child_[i].right) {
                    this->idx_ = i;
                }
            } else {
                i = this->instance_->get_parent(this->idx_);
                while ((i != this->instance_->EMPTY) &&
                       (this->idx_ == this->instance_->child_[i].left)) {
                    this->idx_ = i;
                    i = this->instance_->get_parent(this->idx_);
                }
                this->idx_ = i;
            }
            return *this;
        }

        reverse_iterator operator++(int) {
            auto temp = *this;
            ++(*this);
            return temp;
        }
    };

public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using key_type = Key;

    avl_array() : size_(0), root_(Size) {}

    iterator begin() {
        size_type i = EMPTY;
        if (root_ != EMPTY) {
            for (i = root_; child_[i].left != EMPTY; i = child_[i].left);
        }
        return iterator(this, i);
    }

    iterator end() { return iterator(this, EMPTY); }

    reverse_iterator rbegin() {
        size_type i = EMPTY;
        if (root_ != EMPTY) {
            for (i = root_; child_[i].right != EMPTY; i = child_[i].right);
        }
        return reverse_iterator(this, i);
    }

    reverse_iterator rend() { return reverse_iterator(begin()); }

    size_type size() const { return size_; }
    bool empty() const { return size_ == static_cast<size_type>(0); }
    size_type capacity() const { return Size; }

    void clear() {
        size_ = 0;
        root_ = EMPTY;
    }

    bool insert(const key_type& key, const value_type& val) {
        if (root_ == EMPTY) {
            key_[size_] = key;
            val_[size_] = val;
            balance_[size_] = 0;
            child_[size_] = {EMPTY, EMPTY};
            set_parent(size_, EMPTY);
            root_ = size_++;
            return true;
        }

        for (size_type i = root_; i != EMPTY; i = (key < key_[i]) ? child_[i].left : child_[i].right) {
            if (key < key_[i]) {
                if (child_[i].left == EMPTY) {
                    if (size_ >= capacity()) return false;

                    key_[size_] = key;
                    val_[size_] = val;
                    balance_[size_] = 0;
                    child_[size_] = {EMPTY, EMPTY};
                    set_parent(size_, i);
                    child_[i].left = size_++;
                    insert_balance(i, 1);
                    return true;
                }
            } else if (key_[i] == key) {
                val_[i] = val;
                return true;
            } else {
                if (child_[i].right == EMPTY) {
                    if (size_ >= capacity()) return false;

                    key_[size_] = key;
                    val_[size_] = val;
                    balance_[size_] = 0;
                    child_[size_] = {EMPTY, EMPTY};
                    set_parent(size_, i);
                    child_[i].right = size_++;
                    insert_balance(i, -1);
                    return true;
                }
            }
        }
        return false;
    }

    iterator find(const key_type& key) {
        for (size_type i = root_; i != EMPTY;) {
            if (key == key_[i]) {
                return iterator(this, i);
            } else if (key < key_[i]) {
                i = child_[i].left;
            } else {
                i = child_[i].right;
            }
        }
        return end();
    }

    T& operator[](size_type key) {
        int dummy;
        if (!contains(key, dummy)) insert(key, 0);
        return *at(key);
    }

private:
    size_type get_parent(size_type node) const { return parent_[node]; }

    void set_parent(size_type node, size_type parent) {
        if (node != EMPTY) parent_[node] = parent;
    }

    void insert_balance(size_type node, std::int8_t balance) {
        while (node != EMPTY) {
            balance = (balance_[node] += balance);
            if (balance == 0) return;

            if (balance == 2) {
                if (balance_[child_[node].left] == 1) rotate_right(node);
                else rotate_left_right(node);
                return;
            } else if (balance == -2) {
                if (balance_[child_[node].right] == -1) rotate_left(node);
                else rotate_right_left(node);
                return;
            }

            size_type parent = get_parent(node);
            if (parent != EMPTY) balance = child_[parent].left == node ? 1 : -1;
            node = parent;
        }
    }

    size_type rotate_left(size_type node) {
        size_type right = child_[node].right;
        size_type right_left = child_[right].left;
        size_type parent = get_parent(node);

        set_parent(right, parent);
        set_parent(node, right);
        set_parent(right_left, node);
        child_[right].left = node;
        child_[node].right = right_left;

        if (node == root_) root_ = right;
        return right;
    }

    size_type rotate_right(size_type node) {
        size_type left = child_[node].left;
        size_type left_right = child_[left].right;
        size_type parent = get_parent(node);

        set_parent(left, parent);
        set_parent(node, left);
        set_parent(left_right, node);
        child_[left].right = node;
        child_[node].left = left_right;

        if (node == root_) root_ = left;
        return left;
    }

    size_type rotate_left_right(size_type node) {
        child_[node].left = rotate_left(child_[node].left);
        return rotate_right(node);
    }

    size_type rotate_right_left(size_type node) {
        child_[node].right = rotate_right(child_[node].right);
        return rotate_left(node);
    }

    bool contains(const key_type& key, int& index) const {
        for (size_type i = root_; i != EMPTY;) {
            if (key == key_[i]) {
                index = i;
                return true;
            } else if (key < key_[i]) {
                i = child_[i].left;
            } else {
                i = child_[i].right;
            }
        }
        index = EMPTY;
        return false;
    }

    T* at(const key_type& key) {
        for (size_type i = root_; i != EMPTY;) {
            if (key == key_[i]) {
                return &val_[i];
            } else if (key < key_[i]) {
                i = child_[i].left;
            } else {
                i = child_[i].right;
            }
        }
        return nullptr;
    }

};
