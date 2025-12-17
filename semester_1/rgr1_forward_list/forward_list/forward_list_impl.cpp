#include "forward_list_impl.h"

ForwardList::ForwardList() {}

ForwardList::ForwardList(const ForwardList& rhs) {
    Node* current_el = rhs.head_;
    Node* tail = nullptr;

    while (current_el != nullptr) {
        Node* new_node = new Node(current_el->value_);

        if (head_ == nullptr) {
            head_ = new_node;
        } else {
            tail->next_ = new_node;
        }

        tail = new_node;

        current_el = current_el->next_;

        ++size_;
    }
}

ForwardList::ForwardList(size_t count, int32_t value) {
    for (size_t i = 0; i < count; i++) {
        PushFront(value);
    }
}

ForwardList::ForwardList(std::initializer_list<int32_t> init) {
    std::initializer_list<int32_t>::iterator iter = init.end();
    while (iter != init.begin()) {
        --iter;
        PushFront(*iter);
    }
}

ForwardList& ForwardList::operator=(const ForwardList& rhs) {
    if (this == &rhs) {
        return *this;
    }
    Clear();

    Node* current_el = rhs.head_;
    Node* tail = nullptr;

    while (current_el != nullptr) {
        Node* new_node = new Node(current_el->value_);

        if (head_ == nullptr) {
            head_ = new_node;
        } else {
            tail->next_ = new_node;
        }

        tail = new_node;

        current_el = current_el->next_;

        ++size_;
    }

    return *this;
}

ForwardList::~ForwardList() {
    Clear();
}

void ForwardList::PushFront(int32_t value) {
    Node* new_node = new Node(value);
    new_node->next_ = head_;
    head_ = new_node;
    ++size_;
}

void ForwardList::PopFront() {
    if (head_ == nullptr) {
        return;
    }
    Node* temp = head_;
    head_ = head_->next_;
    delete temp;
    --size_;
}

void ForwardList::Remove(int32_t value) {
    while (head_ != nullptr && head_->value_ == value) {
        PopFront();
    }

    Node* current_el = head_;
    while (current_el != nullptr && current_el->next_ != nullptr) {
        if (current_el->next_->value_ == value) {
            Node* temp = current_el->next_;
            current_el->next_ = temp->next_;
            delete temp;
            --size_;
        } else {
            current_el = current_el->next_;
        }
    }
}

void ForwardList::Clear() {
    while (head_ != nullptr) {
        PopFront();
    }
}

bool ForwardList::FindByValue(int32_t value) {
    Node* current_el = head_;

    while (current_el != nullptr) {
        if (current_el->value_ == value) {
            return true;
        }
        current_el = current_el->next_;
    }

    return false;
}

void ForwardList::Print(std::ostream& out) {
    Node* current_el = head_;

    if (current_el == nullptr) {
        return;
    }

    out << current_el->value_;
    current_el = current_el->next_;

    while (current_el != nullptr) {
        out << " " << current_el->value_;
        current_el = current_el->next_;
    }
}

int32_t ForwardList::Front() const {
    if (head_ != nullptr) {
        return head_->value_;
    } else {
        throw std::runtime_error("List is empty");
    }
}

size_t ForwardList::Size() const {
    return size_;
}