/**
 * @file uas_no_4.cpp
 * @author Demitrias Wilbert (demitriaswilbert@gmail.com)
 * @brief Jawaban Soal UAS Struktur Data No. 4
 * 
 * Ilustrasi Simulasi antrian dengan memanfaatkan single linked list
 * untuk operasi sisip dan hapus    
 * 
 * @version 0.1
 * @date 2023-05-03
 * 
 */

#include <bits/stdc++.h>

/**
 * @brief kelas node
 * 
 * @tparam T 
 */
template <typename T>
class Node {
    T m_data;
    Node *m_next;

    public:
    /**
     * @brief Constructor
     * 
     * @param _data 
     */
    Node(const T& _data) : m_data(_data), m_next(NULL) {}

    /**
     * @brief Constructor untuk rvalue
     * 
     * @param _data 
     */
    Node(T&& _data) : m_data(_data), m_next(NULL) {}
    
    /**
     * @brief getter next node
     * 
     * @return Node* 
     */
    Node* next() { return m_next; }

    /**
     * @brief setter next node
     * 
     * @param _next 
     */
    void next(Node* _next) { m_next = _next; }

    /**
     * @brief getter data
     * 
     * @return T& 
     */
    T& data() { return m_data; }

    /**
     * @brief setter data
     * 
     * @param _data 
     */
    void data(const T& _data) { m_data = _data; }
    
    /**
     * @brief setter data dengan rvalue
     * 
     * @param _data 
     */
    void data(T&& _data) { m_data = _data; }
};

/**
 * @brief kelas queue
 * 
 * @tparam T tipe data
 */
template <typename T>
class Queue {
    Node<T> *m_front, *m_back;
    size_t m_size;

    public: 
    /**
     * @brief Constructor
     * 
     */
    Queue<T>() : m_front(NULL), m_back(NULL), m_size(0) {}

    /**
     * @brief getter node front
     * 
     * @return Node<T>* 
     */
    Node<T>* front_node() {return m_front;}
    
    /**
     * @brief getter node back
     * 
     * @return Node<T>* 
     */
    Node<T>* back_node() {return m_back;}

    /**
     * @brief pop dari queue (pop front)
     * 
     */
    void pop() {
        // empty Queue
        if (!m_front)
            return;

        // 1 left
        if (m_front == m_back)
            m_back = NULL;

        Node<T>* tmp = m_front->next();
        delete m_front;
        m_front = tmp;

        // decrement size
        m_size--;
    }

    /**
     * @brief sisip element
     * 
     * Element akan disisipkan kedalam queue sesuai index
     * 
     * @param pos posisi sisip
     * @param element 
     */
    void insert(size_t pos, T element) {

        Node<T>* new_elem = new Node<T>(element);

        if (size() == 0 || pos >= size()) 
            return push(element);

        if (pos == 0) {
            new_elem->next(m_front);
            m_front = new_elem;
        } else {
            Node<T>* tmp = m_front;
            while (pos-- > 1 && tmp != NULL) {
                tmp = tmp->next();
            }
            Node<T>* nextNode = tmp->next();
            tmp->next(new_elem);
            new_elem->next(nextNode);
        }
        m_size++;
    }

    /**
     * @brief hapus element
     * 
     * menghapus element dalam queue pada posisi (pos)
     * 
     * @param pos 
     */
    void remove(size_t pos) {
        if (size() < 2 || pos == 0) 
            return pop();

        Node<T>* tmp = m_front, *tmpNext = tmp->next();
        while (pos-- > 1 && tmpNext->next() != NULL) {
            tmp = tmpNext;
            tmpNext = tmpNext->next();
        }
        if (tmpNext == m_back) {
            m_back = tmp;
        } 
        tmp->next(tmpNext->next());
        delete tmpNext;
        m_size--;
    }

    /**
     * @brief push back
     * 
     * @param element 
     */
    void push(T element) {
        // new element
        Node<T>* elem = new Node<T>(element);

        // empty queue
        if (m_back == NULL) {
            m_back = m_front = elem;
            m_size++;
            return;
        }

        m_back->next(elem);
        m_back = elem;
        m_size++;
    }

    /**
     * @brief getter data front
     * 
     * @return T& 
     */
    T& front() { return m_front->data(); }
    
    /*/
     * @brief getter data front
     * 
     * @return T& 
     */
    T& back() { return m_back->data(); }
    
    /**
     * @brief jumlah data dalam queue
     * 
     * @return size_t 
     */
    size_t size() const { return m_size; }

    /**
     * @brief Destructor
     * 
     */
    ~Queue() {
        while (size())
            pop();
    }
};

/**
 * @brief Overload operator << pada ostream untuk print
 * 
 * @tparam T tipe data
 * @param os output stream
 * @param d q yang di print
 * @return std::ostream& 
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, Queue<T>& d) {
    std::stringstream ss;
    for (Node<T>* t = d.front_node(); t != NULL; t = t->next()) {
        ss << (t == d.front_node()? "" : ", ") << t->data();
    }
    os << ss.str();
    return os;
}

int main() {
    std::cout << "Tipe Data Int\n";
    Queue<int> q_int;
    q_int.push(5);
    std::cout << "Data Awal: \n";
    std::cout << q_int << "\n\n";

    std::cout << "Sisip Depan 4: \n";
    q_int.insert(0, 4);
    std::cout << q_int << "\n\n";

    std::cout << "Sisip belakang 3: \n";
    q_int.insert(q_int.size(), 3);
    std::cout << q_int << "\n\n";

    std::cout << "Sisip tengah (index 1) 7: \n";
    q_int.insert(1, 7);
    std::cout << q_int << "\n\n";

    std::cout << "Sisip tengah (index 2) 9: \n";
    q_int.insert(2, 9);
    std::cout << q_int << "\n\n";

    std::cout << "push 8: \n";
    q_int.push(8);
    std::cout << q_int << "\n\n";

    std::cout << "pop: \n";
    q_int.pop();
    std::cout << q_int << "\n\n";

    std::cout << "Hapus Depan: \n";
    q_int.remove(0);
    std::cout << q_int << "\n\n";

    std::cout << "Hapus Belakang: \n";
    q_int.remove(q_int.size() - 1);
    std::cout << q_int << "\n\n";

    std::cout << "Hapus Tengah (index 1): \n";
    q_int.remove(1);
    std::cout << q_int << "\n\n";


    /**
     * @brief Tipe Data std::string
     * 
     */
    std::string arr[] = {
        "nol", "satu",
        "dua", "tiga",
        "empat", "lima",
        "enam", "tujuh",
        "delapan", "sembilan",
        "sepuluh",
    };

    std::cout << "Tipe Data String\n";
    Queue<std::string> q_str;
    q_str.push(arr[5]);
    std::cout << "Data Awal: \n";
    std::cout << q_str << "\n\n";

    std::cout << "Sisip Depan \"empat\": \n";
    q_str.insert(0, arr[4]);
    std::cout << q_str << "\n\n";

    std::cout << "Sisip belakang \"tiga\": \n";
    q_str.insert(q_str.size(), arr[3]);
    std::cout << q_str << "\n\n";

    std::cout << "Sisip tengah (index 1) \"tujuh\": \n";
    q_str.insert(1, arr[7]);
    std::cout << q_str << "\n\n";

    std::cout << "Sisip tengah (index 2) \"sembilan\": \n";
    q_str.insert(2, arr[9]);
    std::cout << q_str << "\n\n";

    std::cout << "push \"delapan\": \n";
    q_str.push(arr[8]);
    std::cout << q_str << "\n\n";

    std::cout << "pop: \n";
    q_str.pop();
    std::cout << q_str << "\n\n";

    std::cout << "Hapus Depan: \n";
    q_str.remove(0);
    std::cout << q_str << "\n\n";

    std::cout << "Hapus Belakang: \n";
    q_str.remove(q_str.size() - 1);
    std::cout << q_str << "\n\n";

    std::cout << "Hapus Tengah (index 1): \n";
    q_str.remove(1);
    std::cout << q_str << "\n\n";

}