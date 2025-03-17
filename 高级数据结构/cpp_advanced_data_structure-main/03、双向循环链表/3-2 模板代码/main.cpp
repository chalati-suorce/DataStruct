#include <iostream>
using namespace std;

// ˫��ѭ������

template<typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;
    Node(const T& value) : data(value), prev(NULL), next(NULL) {

    }
};

template<class T>
class DoublyLinkedList {
public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void push_front(const T& value);
    void push_back(const T& value);
    void insert_after(Node<T>* node, const T& value);
    void delete_node(Node<T>* node);
    void modify(Node<T>* node, const T& value);
    Node<T>* find(const T& value) const;

    void print() const;
    int size() const;
    bool empty() const;

private:
    Node<T>* m_dummyHead;
    int m_size;
};

template<class T>
DoublyLinkedList<T>::DoublyLinkedList() : m_size(0) {
    m_dummyHead = new Node<T>(T());
    m_dummyHead->prev = m_dummyHead;
    m_dummyHead->next = m_dummyHead;
}

template<class T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    while (m_size > 0) {
        delete_node(m_dummyHead->next);
    }
    delete m_dummyHead;
    m_dummyHead = NULL;
}

// ����ǰ��m_dummyHead <=> m_dummyHead->next
// �����m_dummyHead <=> newNode <=> m_dummyHead->next
template<class T>
void DoublyLinkedList<T>::push_front(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    // �޸� newNode �� prev �� next ָ��
    newNode->prev = m_dummyHead;
    newNode->next = m_dummyHead->next;
    // �޸� m_dummyHead->next �� prev ָ��
    m_dummyHead->next->prev = newNode;
    // �޸� m_dummyHead �� next ָ��
    m_dummyHead->next = newNode;
    ++m_size;
}

// ����ǰ��m_dummyHead->prev <=> m_dummyHead
// �����m_dummyHead->prev <=> newNode <=> m_dummyHead
template<class T>
void DoublyLinkedList<T>::push_back(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    // �޸� newNode �� prev �� next ָ��
    newNode->prev = m_dummyHead->prev;
    newNode->next = m_dummyHead;
    // �޸� m_dummyHead->prev �� next ָ��
    m_dummyHead->prev->next = newNode;
    // �޸� m_dummyHead �� prev ָ��
    m_dummyHead->prev = newNode;
    ++m_size;
}

// ����ǰ��node <=> node->next
// �����node <=> newNode <=> node->next
template<class T>
void DoublyLinkedList<T>::insert_after(Node<T>* node, const T& value) {
    if (node == NULL || node == m_dummyHead) {
        return;
    }
    Node<T>* newNode = new Node<T>(value);
    // �޸� newNode �� prev �� next ָ��
    newNode->prev = node;
    newNode->next = node->next;
    // �޸� node->next �� prev ָ��
    node->next->prev = newNode;
    // �޸� node �� next  ָ��
    node->next = newNode;
    ++m_size;
}

// ɾ��ǰ��node->prev  <=> node <=>  node->next
// ɾ����node->prev <=> node->next
template<class T>
void DoublyLinkedList<T>::delete_node(Node<T>* node) {
    if (node == NULL || node == m_dummyHead) {
        return;
    }
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
    --m_size;
}

template<class T>
void DoublyLinkedList<T>::modify(Node<T>* node, const T& value) {
    if (node == NULL || node == m_dummyHead) {
        return;
    }
    node->data = value;
}

template<class T>
Node<T>* DoublyLinkedList<T>::find(const T& value) const {
    Node<T>* curr = m_dummyHead->next;
    while (curr != m_dummyHead) {
        if (curr->data == value) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

template<class T>
void DoublyLinkedList<T>::print() const {
    Node<T>* curr = m_dummyHead->next;
    while (curr != m_dummyHead) {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
}

template<class T>
int DoublyLinkedList<T>::size() const {
    return m_size;
}

template<class T>
bool DoublyLinkedList<T>::empty() const {
    return m_size == 0;
}

int main() {
    DoublyLinkedList<char> dll;
    dll.push_back('i');  dll.print();
    dll.push_back('c');  dll.print();
    dll.push_back('p');  dll.print();
    dll.push_back('c');  dll.print();

    dll.push_front('m'); dll.print();
    dll.push_front('a'); dll.print();

    Node<char>* nd = dll.find('a');
    dll.insert_after(nd, 'c');  dll.print();
    nd = dll.find('m');
    dll.insert_after(nd, '/');  dll.print();

    nd = dll.find('i');
    dll.modify(nd, 'c');  dll.print();

    nd = dll.find('m');
    dll.delete_node(nd);   dll.print();

    cout << dll.empty() << endl;
    cout << dll.size() << endl;

    return 0;
}