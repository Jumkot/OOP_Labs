#include <iostream>

using namespace std;

class Node
{
public:
    int key;
    Node *prev;
    Node *next;

    Node()
    {
        key = 0;
        next = nullptr;
        prev = nullptr;
    }

    Node(int key) : key(key), prev(nullptr), next(nullptr) {}

    virtual ~Node()
    {
        cout << "Узел " << key << " удалён" << endl;
    }
};

class List
{
private:
    static int create;

protected:
    Node *head;
    int size;

public:
    List() : head(new Node()), size(0)
    {
        ++create;
    }

    List(int key) : head(new Node(key)), size(1)
    {
        ++create;
    }

    virtual ~List()
    {
        Node *start = head->next;
        if (start && start->key)
        {
            for (int i = 0; i < size - 1; i++)
            {
                delete_node(start->prev->key);
                start = start->next;
            }
            delete_node(start->prev->key);
            delete_node(start->key);
            cout << "Список удалён" << endl;
        }
    }

    Node *get_head() const { return head; }

    virtual void add_front(int key)
    {
        Node *node = new Node(key);

        if (head)
        {
            node->next = head;
            head->prev = node;
        }
        head = node;

        ++size;
        ++create;
    }

    virtual void add_end(int key)
    {
        Node *new_node = new Node(key);

        if (!head)
        {
            head = new_node;
        }
        Node *step = head;
        while (step->next)
        {
            step = step->next;
        }
        step->next = new_node;
        new_node->prev = step;

        ++size;
        ++create;
    }

    Node *lookup(int key)
    {
        for (Node *node = head; node != nullptr; node = node->next)
        {
            if (node->key == key)
            {
                return node;
            }
        }
        return nullptr;
    }

    virtual void delete_node(int key)
    {
        Node *node = lookup(key);
        if (node == head)
        {
            head = node->next;
        }
        else
        {
            node->prev->next = node->next;
        }
        if (node->next)
        {
            node->next->prev = node->prev;
        }

        --size;
        delete node;
    }

    virtual void create_print()
    {
        cout << "Количество созданных узлов списка: " << create << endl;
    }

    virtual void print()
    {
        Node *step = head;
        cout << "Размер: " << size << endl;
        for (int i = 0; i < size && step; i++)
        {
            cout << step << ": " << step->key << endl;
            step = step->next;
        }
        cout << endl;
    }
};

// LIFO
class Stack : public List
{
    static int create;

public:
    Stack() : List()
    {
        ++create;
    }

    Stack(int key) : List(key)
    {
        ++create;
    }

    ~Stack()
    {
        cout << "Стек удалён" << endl;
    }

    void add_front(int key)
    {
        Node *node = new Node(key);

        if (head)
        {
            node->next = head;
            head->prev = node;
        }
        head = node;

        ++size;
        ++create;
    }

    void delete_node(int key)
    {
        try
        {
            if (size == 0)
            {
                throw runtime_error("Стек пуст");
            }
            if (!head->next)
            {
                delete head;
                --size;
                return;
            }
            else
            {
                head->next->prev = nullptr;
            }

            --size;
            Node *exp = head->next;
            delete head;
            head = exp;
        }
        catch (const exception &e)
        {
            cerr << "Ошибка: " << e.what() << endl;
        }
    }

    virtual void create_print()
    {
        cout << "Количество созданных узлов стека: " << create << endl;
    }

    void print()
    {
        cout << "Стек:" << endl;
        List::print();
    }
};

// FIFO
class Queue : public List
{
    static int create;

protected:
    Node *tail;

public:
    Queue() : List(), tail(new Node())
    {
        tail->prev = head;
        head->next = tail;
        ++create;
    }

    Queue(int key) : List(key), tail(new Node())
    {
        tail->prev = head;
        head->next = tail;
        ++create;
    }

    ~Queue()
    {
        Node *start = head->next;
        if (start && start->key)
        {
            for (int i = 0; start != tail; i++)
            {
                delete_node(head->key);
                head = start;
                start = start->next;
            }
            delete_node(head->key);
            delete_node(start->key);
            cout << "Очередь удалена" << endl;
        }
        else
        {
            cout << "Очередь удалена" << endl;
        }
    }

    void add_end(int key)
    {
        if (size == 1)
        {
            tail->key = key;
            ++size;
            ++create;
            return;
        }
        Node *oldtail = tail;

        tail = new Node(key);
        if (!head)
        {
            head = tail;
        }
        else
        {
            oldtail->next = tail;
        }

        ++size;
        ++create;
    }

    void delete_node(int key)
    {

        try
        {

            if (size == 0)
            {
                throw runtime_error("Очередь пуста");
            }
            if (!head->next)
            {
                delete head;
                --size;
                return;
            }
            else
            {
                head->next->prev = nullptr;
            }

            --size;
            Node *exp = head->next;
            delete head;
            head = exp;
        }
        catch (const exception &e)
        {
            cerr << "Ошибка: " << e.what() << endl;
        }
    }

    virtual void create_print()
    {
        cout << "Количество созданных узлов очереди: " << create << endl;
    }

    void print()
    {
        cout << "Очередь:" << endl;
        List::print();
    }
};

int List::create = 0;
int Stack::create = 0;
int Queue::create = 0;

int main()
{
    // Демонстрация работы списка (двусвязный)
    List list(10);
    list.add_end(20);
    list.add_end(30);
    list.add_end(40);
    list.add_front(7);
    list.add_front(4);
    list.add_front(1);

    cout << "Голова списка: " << list.get_head()->key << endl;
    list.create_print();
    list.print();

    Node *search = list.lookup(30);
    cout << "Адрес найденного элемента: " << search->next->prev << endl;

    list.delete_node(10);

    cout << "Голова списка: " << list.get_head()->key << endl;
    list.create_print();
    list.print();

    list.delete_node(1);
    list.delete_node(30);
    list.delete_node(7);

    cout << "Голова списка: " << list.get_head()->key << endl;
    list.create_print();
    list.print();

    // Демонстрация работы стека
    Stack stack(10);
    stack.add_front(1);
    stack.add_front(5);
    stack.add_front(2);
    stack.add_front(20);

    cout << "Вершина стека: " << stack.get_head()->key << endl;
    stack.create_print();
    stack.print();

    stack.delete_node(stack.get_head()->key);
    stack.delete_node(stack.get_head()->key);
    cout << "Вершина стека: " << stack.get_head()->key << endl;
    stack.create_print();
    stack.print();

    // Демонстрация работы очереди
    Queue queue(10);
    queue.add_end(1);
    queue.add_end(5);
    queue.add_end(2);
    queue.add_end(20);

    cout << "Вершина очереди: " << queue.get_head()->key << endl;
    queue.create_print();
    queue.print();

    queue.delete_node(queue.get_head()->key);
    queue.delete_node(queue.get_head()->key);
    cout << "Вершина очереди: " << queue.get_head()->key << endl;
    queue.create_print();
    queue.print();

    Stack q;
    q.delete_node(q.get_head()->key);

    return 0;
}