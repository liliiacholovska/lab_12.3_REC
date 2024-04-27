#include <iostream>

using namespace std;

struct Node {
    int data;   // ���� �����
    Node* prev; // �������� �� ��������� ������� � ������
    Node* next; // �������� �� ��������� ������� � ������
};

// ���������� ������� ��� ��������� ��������������� ������ � ������ �������
Node* createListRec(int values[], int size, int index = 0, Node* tail = nullptr) {
    if (index == size) {
        return (tail ? tail->next : nullptr); // ���������� ������ ������
    }

    Node* newNode = new Node(); // ��������� ������ ����� ��������� Node
    newNode->data = values[index]; // ����� �������� � ������ values � ���� data ������ �����
    newNode->prev = tail; // ������������ ��������� prev ������ ����� �� �������� ������� ����� (tail)

    if (tail != nullptr) { // ��������, �� ���� ������� �����
        tail->next = newNode; // ���� tail ����, ���������� ���� �������� next �� ����� �����
    }

    Node* head = createListRec(values, size, index + 1, newNode); // ����������� ������ ������� ��� ��������� ���������� �����, �������� ������ ����� �� ��������� ���� (tail)

    return (index == 0) ? newNode : head; // ��������� ������ ������
}

// ���������� ������� ��� ��������� ��� �������� ������
void printListRec(Node* node) {
    if (node == nullptr) {
        cout << endl;
        return;
    }
    cout << node->data << " ";
    printListRec(node->next);
}

// ���������� ������� ��� ����� ������ ����� � ������
void swapAdjacentNodesRec(Node*& head, Node* current) {
    if (current == nullptr || current->next == nullptr) {
        return; // ������� �������: ���� ����� ������� ��� ��������� ����� �������
    }

    Node* next = current->next;   // �����, ���� ������� �������
    current->next = next->next;   // ����������� ��������� ����� �� ����� ���� ����������
    next->next = current;         // ����������� ���������� ����� ����� �� ��������
    next->prev = current->prev;   // ����������� ��������� �� ��������� ����� ��� ����������
    current->prev = next;         // ����������� ��������� �� ��������� ����� ��� ���������

    if (current->next) {
        current->next->prev = current;  // ����������� ��������� �� ��������� ����� ��� ����� ���� ����������
    }
    if (next->prev) {
        next->prev->next = next;        // ����������� ��������� �� ��������� ����� ��� ����� ����� ��������
    }
    else {
        head = next;                    // ��������� ������ ������, ���� �������� ��� �������
    }

    swapAdjacentNodesRec(head, current->next);  // ����������� ������ ��� ����� �������� ����
}

// ���������� ������� ��� ��������� ������ �� ��������� ���'��
void deleteListRec(Node* head) {
    if (!head) return; // ������� �������: ���� ������ null
    deleteListRec(head->next);  // ���������� ��������� ���������� �����
    delete head;                // ��������� ��������� �����
}

int main() {
    int values[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int size = sizeof(values) / sizeof(values[0]);  // ���������� ������� �������� � �����

    Node* head = createListRec(values, size);  // ��������� ������

    cout << "Original list:" << endl;
    printListRec(head);  // ���� ������������ ������

    swapAdjacentNodesRec(head, head);  // ��������� ����� ������ �����

    cout << "List after swapping adjacent nodes:" << endl;
    printListRec(head);  // ���� ������ ���� �����

    deleteListRec(head);  // ��������� ������ �� ��������� ���'��
    return 0;
}