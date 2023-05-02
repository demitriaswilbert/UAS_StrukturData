/**
 * @file uas_no_2.cpp
 * @author Demitrias Wilbert (demitriaswilbert@gmail.com)
 * @brief Jawaban Soal UAS Struktur Data No. 2
 * 
 * Ilustrasi Simulasi nilai awal, sisip depan, sisip belakang
 * menggunakan Double Linked List untuk sembarangan tipe data       
 * 
 * @version 0.1
 * @date 2023-05-03
 * 
 */

#include <bits/stdc++.h>

/**
 * @brief kelas Node
 * 
 * @tparam T tipe data
 */
template <typename T>
class Node {
    Node *m_next, *m_prev;
    T m_data;

    public:
    /**
     * @brief Constructor
     * 
     * @param data 
     */
    Node(const T& data): m_data(data), m_next(NULL), m_prev(NULL) {}

    /**
     * @brief Constructor untuk rvalue
     * 
     * @param data 
     */
    Node(T&& data): Node(data) {}

    /**
     * @brief setter untuk next node
     * 
     * @param next 
     */
    void next(Node* next) { m_next = next; }

    /**
     * @brief getter untuk next node
     * 
     * @return Node* 
     */
    Node* next() {return m_next;}

    /**
     * @brief setter untuk previous node
     * 
     * @param prev 
     */
    void prev(Node* prev) { m_prev = prev; }

    /**
     * @brief getter untuk previous node
     * 
     * @return Node* 
     */
    Node* prev() {return m_prev;}

    /**
     * @brief getter untuk data
     * 
     * @return T& 
     */
    T& data() {return m_data;}

    /**
     * @brief Destructor
     * 
     */
    ~Node() {
        // unlink
        if (m_next != NULL) m_next->prev(m_prev);
        if (m_prev != NULL) m_prev->next(m_next);
    }
};

/**
 * @brief kelas Double Linked List
 * 
 * @tparam T tipe data
 */
template <typename T>
class DoubleLinkedList {
    Node<T> *m_front, *m_back;
    size_t m_size;

    public:
    /**
     * @brief Constructor
     * 
     * @param data data awal
     */
    DoubleLinkedList(const T& data) {
        m_front = m_back = new Node<T>(data);
        m_size = 1;
    }

    /**
     * @brief Constructor rvalue
     * 
     * @param data 
     */
    DoubleLinkedList(T&& data): DoubleLinkedList(data) {}

    /**
     * @brief getter untuk node front
     * 
     * @return Node<T>* 
     */
    Node<T>* front_node() {return m_front;}

    /**
     * @brief getter untuk node back
     * 
     * @return Node<T>* 
     */
    Node<T>* back_node() {return m_back;}

    /**
     * @brief getter data front
     * 
     * @return T& 
     */
    T& front() {return m_front->data();}

    /**
     * @brief getter data back
     * 
     * @return T& 
     */
    T& back() {return m_back->data();}

    /**
     * @brief sisip depan
     * 
     * @param data data untuk disisipkan
     */
    void push_front(const T& data) {
        Node<T> *tmp = new Node<T>(data);
        if (m_size == 0) {
            m_front = m_back = tmp;
        } else {
            m_front->prev(tmp);
            tmp->next(m_front);
            m_front = tmp;
        }
        m_size++;
    }

    /**
     * @brief sisip depan untuk rvalue
     * 
     * @param data 
     */
    void push_front(T&& data) {push_front(data);}

    /**
     * @brief sisip belakang
     * 
     * @param data 
     */
    void push_back(const T& data) {
        Node<T> *tmp = new Node<T>(data);
        if (m_size == 0) {
            m_front = m_back = tmp;
        } else {
            m_back->next(tmp);
            tmp->prev(m_back);
            m_back = tmp;
        }
        m_size++;
    }

    /**
     * @brief sisip belakang rvalue
     * 
     * @param data 
     */
    void push_back(T&& data) {push_back(data);}

    /**
     * @brief Destructor
     * 
     */
    ~DoubleLinkedList() {
        for (Node<T>* tmp = m_front; tmp != NULL;) {
            Node<T>* _next = tmp->next();
            delete tmp;
            tmp = _next;
        }
    }
};

/**
 * @brief Overload operator << pada ostream untuk print
 * 
 * @tparam T tipe data
 * @param os output stream
 * @param d double linked list yang di print
 * @return std::ostream& 
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, DoubleLinkedList<T>& d) {
    std::stringstream ss;
    for (Node<T>* t = d.front_node(); t != NULL; t = t->next()) {
        ss << (t == d.front_node()? "" : ", ") << t->data();
    }
    os << ss.str();
    return os;
}

int main() {

    /**
     * @brief Tipe Data Int
     * 
     */
    std::cout << "Tipe Data Int\n";
    DoubleLinkedList<int> list_int(5);
    std::cout << "Data Awal: \n";
    std::cout << list_int << "\n\n";

    std::cout << "Sisip Depan [4, 3, 2, 1]: \n";
    for (int i = 4; i > 0; i--) {
        list_int.push_front(i);
    }
    std::cout << list_int << "\n\n";

    std::cout << "Sisip Belakang [4, 3, 2, 1]: \n";
    for (int i = 4; i > 0; i--) {
        list_int.push_back(i);
    }
    std::cout << list_int << "\n\n";

    /**
     * @brief Tipe Data std::string
     * 
     */
    std::cout << "Tipe Data String\n";
    std::string arr[] = {"Nol", "Satu", "Dua", "Tiga", "Empat", "Lima"};
    DoubleLinkedList<std::string> list_str(arr[5]);
    std::cout << "Data Awal: \n";
    std::cout << list_str << "\n\n";

    std::cout << "Sisip Depan [\"Empat\", \"Tiga\", \"Dua\", \"Satu\"] Secara Berurutan: \n";
    for (int i = 4; i > 0; i--) {
        list_str.push_front(arr[i]);
    }
    std::cout << list_str << "\n\n";

    std::cout << "Sisip Belakang [\"Empat\", \"Tiga\", \"Dua\", \"Satu\"] Secara Berurutan: \n";
    for (int i = 4; i > 0; i--) {
        list_str.push_back(arr[i]);
    }
    std::cout << list_str << "\n\n";

}