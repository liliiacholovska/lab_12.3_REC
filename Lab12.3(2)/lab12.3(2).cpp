#include <iostream>

using namespace std;

struct Node {
    int data;   // Поле даних
    Node* prev; // Вказівник на попередній елемент у списку
    Node* next; // Вказівник на наступний елемент у списку
};

// Рекурсивна функція для створення двонаправленого списку з масиву значень
Node* createListRec(int values[], int size, int index = 0, Node* tail = nullptr) {
    if (index == size) {
        return (tail ? tail->next : nullptr); // Повернення голови списку
    }

    Node* newNode = new Node(); // Створення нового вузла структури Node
    newNode->data = values[index]; // Запис значення з масиву values у поле data нового вузла
    newNode->prev = tail; // Встановлення вказівника prev нового вузла на поточний кінцевий вузол (tail)

    if (tail != nullptr) { // Перевірка, чи існує кінцевий вузол
        tail->next = newNode; // Якщо tail існує, встановити його вказівник next на новий вузол
    }

    Node* head = createListRec(values, size, index + 1, newNode); // Рекурсивний виклик функції для створення наступного вузла, передача нового вузла як поточного кінця (tail)

    return (index == 0) ? newNode : head; // Повертати голову списку
}

// Рекурсивна функція для виведення всіх елементів списку
void printListRec(Node* node) {
    if (node == nullptr) {
        cout << endl;
        return;
    }
    cout << node->data << " ";
    printListRec(node->next);
}

// Рекурсивна функція для обміну сусідніх вузлів у списку
void swapAdjacentNodesRec(Node*& head, Node* current) {
    if (current == nullptr || current->next == nullptr) {
        return; // Базовий випадок: якщо вузол відсутній або наступний вузол відсутній
    }

    Node* next = current->next;   // Вузол, який потрібно обміняти
    current->next = next->next;   // Направлення поточного вузла на вузол після наступного
    next->next = current;         // Направлення наступного вузла назад на поточний
    next->prev = current->prev;   // Виправлення вказівника на попередній вузол для наступного
    current->prev = next;         // Виправлення вказівника на попередній вузол для поточного

    if (current->next) {
        current->next->prev = current;  // Виправлення вказівника на попередній вузол для вузла після наступного
    }
    if (next->prev) {
        next->prev->next = next;        // Виправлення вказівника на наступний вузол для вузла перед поточним
    }
    else {
        head = next;                    // Оновлення голови списку, якщо поточний був головою
    }

    swapAdjacentNodesRec(head, current->next);  // Рекурсивний виклик для обміну наступної пари
}

// Рекурсивна функція для видалення списку та звільнення пам'яті
void deleteListRec(Node* head) {
    if (!head) return; // Базовий випадок: якщо голова null
    deleteListRec(head->next);  // Рекурсивне видалення наступного вузла
    delete head;                // Звільнення поточного вузла
}

int main() {
    int values[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int size = sizeof(values) / sizeof(values[0]);  // Обчислення кількості елементів у масиві

    Node* head = createListRec(values, size);  // Створення списку

    cout << "Original list:" << endl;
    printListRec(head);  // Вивід оригінального списку

    swapAdjacentNodesRec(head, head);  // Виконання обміну сусідніх вузлів

    cout << "List after swapping adjacent nodes:" << endl;
    printListRec(head);  // Вивід списку після обміну

    deleteListRec(head);  // Видалення списку та звільнення пам'яті
    return 0;
}