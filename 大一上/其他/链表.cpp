#include <bits/stdc++.h>

using namespace std;
//创建链表节点的结构体
struct Node {
    int data; //根据需求更改data的类型
    Node* next;
    //构造Node函数
    Node(int value) : data(value), next(nullptr) {} //:表示初始化data和next
};
//创建链表类
class linkedList {
private:
    Node* head;
    int size;

    // 私有辅助函数声明
    Node* getMiddle(Node* start) const;
    Node* merge(Node* left, Node* right, bool ascending) const;
    Node* mergeSort(Node* start, bool ascending);

public:
    // 构造函数和析构函数声明
    linkedList();
    ~linkedList();

    // 基本操作函数声明
    void append(int value);
    void prepend(int value);
    void insert(int value, int position);
    void insertAscending(int value);
    void insertDescending(int value);
    bool remove(int value);
    void removeAt(int position);
    bool contains(int value) const;
    void clear();

    // 排序相关函数声明
    void sort(bool ascending = true);
    void bubbleSort(bool ascending = true);
    void selectionSort(bool ascending = true);
    void insertionSort(bool ascending = true);

    // 查询函数声明（const成员函数）
    bool isEmpty() const;
    int getSize() const;
    int getHead() const;
    int getTail() const;
    int getNth(int n) const;
    int findPosition(int value) const;
    bool isAscending() const;
    bool isDescending() const;

    void reverse();

private:
    Node* mergeSort(Node* start, bool ascending) {
        if (start == nullptr || start->next == nullptr) {
            return start;
        }

        // 找到中间节点
        Node* middle = getMiddle(start);
        Node* nextOfMiddle = middle->next;

        // 断开链表
        middle->next = nullptr;

        // 递归排序左右两部分
        Node* left = mergeSort(start, ascending);
        Node* right = mergeSort(nextOfMiddle, ascending);

        // 合并已排序的两部分
        return merge(left, right, ascending);
    }

    // 获取链表的中间节点(当fast到达末尾时slow刚好到mid,时间复杂度低)
    Node* getMiddle(Node* head) {
        if (head == nullptr) return head;

        Node* slow = head;
        Node* fast = head->next;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

    // 合并两个已排序的链表
    Node* merge(Node* left, Node* right, bool ascending) {
        if (left == nullptr) return right;
        if (right == nullptr) return left;

        Node* result = nullptr;

        if (ascending) {
            // 升序合并
            if (left->data <= right->data) {
                result = left;
                result->next = merge(left->next, right, ascending);
            }
            else {
                result = right;
                result->next = merge(left, right->next, ascending);
            }
        }
        else {
            // 降序合并
            if (left->data >= right->data) {
                result = left;
                result->next = merge(left->next, right, ascending);
            }
            else {
                result = right;
                result->next = merge(left, right->next, ascending);
            }
        }

        return result;
    }
public:
    //构造函数
    linkedList() : head(nullptr), size(0) {}
    //当linkedList离开其作用域时析构函数~自启动释放所有Node
    ~linkedList() {
        clear();
    }

    // 在尾部添加节点
    void append(int value) {
        Node* newNode = new Node(value);

        if (head == nullptr) {
            // 空链表，新节点成为头节点
            head = newNode;
        }
        else {
            // 找到最后一个节点
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            // 连接新节点
            current->next = newNode;
        }
        size++;
    }

    // 在头部添加节点
    void prepend(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;  // 新节点指向原头节点
        head = newNode;        // 更新头指针
        size++;
    }
    // 在指定位置插入节点
    bool insert(int value, int position) {
        if (position < 0 || position > size) {
            cout << "Invalid position!" << endl;
            return false;
        }

        if (position == 0) {
            prepend(value);
            return true;
        }

        Node* newNode = new Node(value);
        Node* current = head;

        // 移动到要插入位置的前一个节点
        for (int i = 0; i < position - 1; i++) {
            current = current->next;
        }

        // 插入新节点
        newNode->next = current->next;
        current->next = newNode;
        size++;
        return true;
    }
    
    //升序插入
    void insertAscending(int value) {
        Node* newNode = new Node(value);

        // 情况1：空链表或新节点应该成为头节点
        if (head == nullptr || value <= head->data) {
            newNode->next = head;
            head = newNode;
            size++;
            return;
        }

        // 情况2：找到合适的插入位置
        Node* current = head;
        // 遍历直到找到第一个大于等于value的节点
        while (current->next != nullptr && current->next->data < value) {
            current = current->next;
        }

        // 插入新节点到current之后
        newNode->next = current->next;
        current->next = newNode;
        size++;
    }

    //降序插入
    void insertDescending(int value) {
        Node* newNode = new Node(value);

        // 情况1：空链表或新节点应该成为头节点
        if (head == nullptr || value >= head->data) {
            newNode->next = head;
            head = newNode;
            size++;
            return;
        }

        // 情况2：找到合适的插入位置
        Node* current = head;
        // 遍历直到找到第一个小于等于value的节点
        while (current->next != nullptr && current->next->data > value) {
            current = current->next;
        }

        // 插入新节点到current之后
        newNode->next = current->next;
        current->next = newNode;
        size++;
    }

    // 删除指定值的节点
    bool remove(int value) {
        if (head == nullptr) {
            return false;
        }

        // 如果要删除的是头节点
        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            size--;
            return true;
        }

        // 查找要删除节点的前一个节点
        Node* current = head;
        while (current->next != nullptr && current->next->data != value) {
            current = current->next;
        }

        // 如果找到要删除的节点
        if (current->next != nullptr) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
            size--;
            return true;
        }

        return false;
    }

    // 查找是否存在节点
    bool contains(int value) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
    // 反转链表
    void reverse() {
        if (head == nullptr || head->next == nullptr) {
            return;
        }

        Node* prev = nullptr;
        Node* current = head;
        Node* next = nullptr;

        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }

        head = prev;
        cout << "链表已反转" << endl;
    }

    //排序, 使用归并
    void sort(bool ascending = true) {
        if (head == nullptr || head->next == nullptr) {
            return;  // 空链表或只有一个节点，已经有序
        }

        head = mergeSort(head, ascending);
        cout << "链表已按" << (ascending ? "升序" : "降序") << "排序" << endl;
    }

    // 检查链表是否按升序排列
    bool isAscending() const {
        if (head == nullptr || head->next == nullptr) {
            return true;
        }

        Node* current = head;
        while (current->next != nullptr) {
            if (current->data > current->next->data) {
                return false;
            }
            current = current->next;
        }
        return true;
    }

    // 检查链表是否按降序排列
    bool isDescending() const {
        if (head == nullptr || head->next == nullptr) {
            return true;
        }

        Node* current = head;
        while (current->next != nullptr) {
            if (current->data < current->next->data) {
                return false;
            }
            current = current->next;
        }
        return true;
    }

    //冒泡排序
    void bubbleSort(bool ascending = true) {
        if (head == nullptr || head->next == nullptr) {
            return;
        }

        bool swapped;
        do {
            swapped = false;
            Node* current = head;
            Node* prev = nullptr;

            while (current->next != nullptr) {
                bool shouldSwap = ascending ?
                    (current->data > current->next->data) :
                    (current->data < current->next->data);

                if (shouldSwap) {
                    // 交换节点数据
                    int temp = current->data;
                    current->data = current->next->data;
                    current->next->data = temp;
                    swapped = true;
                }
                prev = current;
                current = current->next;
            }
        } while (swapped);

    }

    // 获取链表大小
    int getSize() const {
        return size;
    }

    // 判断链表是否为空
    bool isEmpty() const {
        return head == nullptr;
    }

    // 清空链表
    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        size = 0;
    }
};
int main() {
    
    return 0;
}