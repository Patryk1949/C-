#include <bits/stdc++.h>
#include "SPL/Containers.hpp"

using namespace std;

class DoublyLinkedListNode {
    public:
        int data;
        DoublyLinkedListNode *next;
        DoublyLinkedListNode *prev;

        DoublyLinkedListNode(int node_data) {
            this->data = node_data;
            this->next = nullptr;
            this->prev = nullptr;
        }
};

class DoublyLinkedList {
    public:
        DoublyLinkedListNode *head;
        DoublyLinkedListNode *tail;

        DoublyLinkedList() {
            this->head = nullptr;
            this->tail = nullptr;
        }

        void insert_node(int node_data) {
            DoublyLinkedListNode* node = new DoublyLinkedListNode(node_data);

            if (!this->head) {
                this->head = node;
            } else {
                this->tail->next = node;
                node->prev = this->tail;
            }

            this->tail = node;
        }
};

void print_doubly_linked_list(DoublyLinkedListNode* node, string sep, ostream &fout) {
    while (node) {
        fout << node->data;

        node = node->next;

        if (node) {
            fout << sep;
        }
    }
}

void free_doubly_linked_list(DoublyLinkedListNode* node) {
    while (node) {
        DoublyLinkedListNode* temp = node;
        node = node->next;

        free(temp);
    }
}

/*
 * Complete the 'sortedInsert' function below.
 *
 * The function is expected to return an INTEGER_DOUBLY_LINKED_LIST.
 * The function accepts following parameters:
 *  1. INTEGER_DOUBLY_LINKED_LIST llist
 *  2. INTEGER data
 */

/*
 * For your reference:
 *
 * DoublyLinkedListNode {
 *     int data;
 *     DoublyLinkedListNode* next;
 *     DoublyLinkedListNode* prev;
 * };
 *
 */

DoublyLinkedListNode* sortedInsert(DoublyLinkedListNode* llist, int data) {
    DoublyLinkedListNode *const newNode = new DoublyLinkedListNode(data);
    
    if (llist == nullptr){
        newNode->prev = newNode->next = nullptr;
        return newNode;
    }
    
    if (llist->data > data){
        newNode->next = llist;
        newNode->prev = nullptr;
        llist->prev = newNode;
        return newNode;
    }
    
    DoublyLinkedListNode *I=llist;
    for (; I->next!=nullptr; I=I->next)
        if (I->data<=data && I->next->data>data){
            newNode->next = I->next;
            newNode->prev = I;
            
         	I->next->prev = newNode;
            I->next = newNode;
            return llist;
        }
        
    newNode->next = nullptr;
    newNode->prev = I;
    I->next = newNode;
    return llist;
}

template<class T>
void addNum(std::vector<T> &dest, const T x){
	for (auto &I : dest)
		I += x;
}

int main()
{
   //  ofstream fout(getenv("OUTPUT_PATH"));

   //  int t;
   //  cin >> t;
   //  cin.ignore(numeric_limits<streamsize>::max(), '\n');

   //  for (int t_itr = 0; t_itr < t; t_itr++) {
   //      DoublyLinkedList* llist = new DoublyLinkedList();

   //      int llist_count;
   //      cin >> llist_count;
   //      cin.ignore(numeric_limits<streamsize>::max(), '\n');

   //      for (int i = 0; i < llist_count; i++) {
   //          int llist_item;
   //          cin >> llist_item;
   //          cin.ignore(numeric_limits<streamsize>::max(), '\n');

   //          llist->insert_node(llist_item);
   //      }

   //      int data;
   //      cin >> data;
   //      cin.ignore(numeric_limits<streamsize>::max(), '\n');

   //      DoublyLinkedListNode* llist1 = sortedInsert(llist->head, data);

   //      print_doubly_linked_list(llist1, " ", std::cout);
   //      cout << "\n";

   //      free_doubly_linked_list(llist1);
   //  }

	sp::DArray<double> arr;
	arr.resize(10000000);

	for (size_t i=9999999; i!=(size_t)-1; --i)
		arr[i] = 2.0;

   return 0;
}
