#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

class Node {
public:
    int key;
    Node* left;
    Node* right;

    Node(int key) {
        this->key = key;
        left = right = nullptr;
    }
};

class BST {
private:
    Node* root;

public:
    BST() {
        root = nullptr;
    }

    void Add(int key) {
        root = Add(root, key);
    }

    void BSTSort(vector<int>& A) {
        for (int a : A)
            Add(a);
    }

    // Добавление элемента
    Node* Add(Node* node, int key) {
        if (node == nullptr)
            return new Node(key);
        if (key < node->key)
            node->left = Add(node->left, key);
        else if (key > node->key)
            node->right = Add(node->right, key);
        return node;
    }

    // Поиск элемента
    bool Search(int key) {
        return Search(root, key);
    }

    // Удаление элемента
    void Remove(int key) {
        root = Remove(root, key);
    }

private:
    // Поиск элемента
    bool Search(Node* node, int key) {
        if (node == nullptr)
            return false;
        if (node->key == key)
            return true;
        if (key < node->key)
            return Search(node->left, key);
        return Search(node->right, key);
    }

    // Удаление элемента
    Node* Remove(Node* node, int key) {
        if (node == nullptr)
            return node;

        if (key < node->key)
            node->left = Remove(node->left, key);
        else if (key > node->key)
            node->right = Remove(node->right, key);
        else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = MinValueNode(node->right);
            node->key = temp->key;
            node->right = Remove(node->right, temp->key);
        }
        return node;
    }

    // Поиск минимального значения для метода Remove
    Node* MinValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }
};

int main() {

    int max_tree_size = 1000;

    vector<int> A_random, A_sorted;
    srand(time(nullptr));

    for (int N = 10; N <= max_tree_size; N *= 10) {
        A_random.clear();
        A_sorted.clear();

        // A_random - массив случайных данных
        // A_sorted - массив данных, упорядоченных по возрастанию
        for (int i = 0; i < N; i++) {
            A_random.push_back(rand() % N);
            A_sorted.push_back(i);
        }

        // Создание двух деревьев
        BST bst_random, bst_sorted;

        double time_sort_random = 0, time_sort_sorted = 0, time_search = 0, time_remove = 0;

        // Время сортировки случайных данных
        auto start = chrono::high_resolution_clock::now();

        bst_random.BSTSort(A_random);

        auto end = chrono::high_resolution_clock::now();
        time_sort_random = chrono::duration_cast<chrono::microseconds>(end - start).count();

        // Время сортировки упорядоченных данных
        start = chrono::high_resolution_clock::now();

        bst_sorted.BSTSort(A_sorted);

        end = chrono::high_resolution_clock::now();
        time_sort_sorted = chrono::duration_cast<chrono::microseconds>(end - start).count();

        int num_elements_to_search_remove = N / 10;
        vector<int> elements_to_search_remove;

        // Генерация случайных элементов для Search и Remove
        for (int i = 0; i < num_elements_to_search_remove; i++) {
            elements_to_search_remove.push_back(rand() % N);
        }

        // Время поиска элементов
        start = chrono::high_resolution_clock::now();

        for (int key : elements_to_search_remove) {
            bst_random.Search(key);
        }

        end = chrono::high_resolution_clock::now();
        time_search = chrono::duration_cast<chrono::microseconds>(end - start).count();


        // Время удаления элементов
        start = chrono::high_resolution_clock::now();

        for (int key : elements_to_search_remove) {
            bst_random.Remove(key);
        }

        end = chrono::high_resolution_clock::now();
        time_remove = chrono::duration_cast<chrono::microseconds>(end - start).count();

        cout << "N = " << N << ", Random Sort Time: " << time_sort_random << " mcs, Sorted Sort Time: " << time_sort_sorted << " mcs, Search Time: " << time_search << " mcs, Remove Time: " << time_remove << " mcs" << endl;
    }

    return 0;
}
