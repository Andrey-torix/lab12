template <typename T>
class Stack
{
private:
    struct Node
    {
        Node* next;
        T obj;
    };
public:   
    Node* nodeHead;
    size_t length;
    Stack() {
        nodeHead = NULL;
        length = 0;
    };
    void push(T&& value) {
        Node* nd = new Node;
        nd->obj = std::move(value);
        nd->next = nodeHead;
        length++;
        nodeHead = nd;
    }
    void push(const T& value) {
        Node* nd = new Node;
        nd->obj = std::move(value);
        nd->next = nodeHead;
        length++;
        nodeHead = nd;
    }

    size_t Length() {
        return length;
    }
    void pop() {
        if (length > 0){
        T tmp = std::move(nodeHead->obj);
        nodeHead = std::move(nodeHead->next);
        length--;
        }
    }
    const T& head() const {
        T& ref = nodeHead->obj;
        return ref;
    }
};