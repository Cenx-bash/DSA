/*
LINKED LIST vs ARRAY:

Array:
+ Random access O(1)
+ Cache friendly (contiguous memory)
- Fixed size (or expensive resizing)
- Insertion/Deletion O(n)

Linked List:
+ Dynamic size
+ Insertion/Deletion O(1) (at known position)
- No random access O(n)
- Extra memory for pointers
- Not cache friendly

MEMORY LAYOUT:
Array: [1][2][3][4][5] (contiguous)
Linked List: [1|→] [2|→] [3|→] [4|→] [5|null] (scattered)
*/

#include <iostream>
using namespace std;

// ============================================
// BASIC NODE STRUCTURE
// ============================================

struct ListNode {
    int val;
    ListNode* next;
    
    // Constructors
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// ============================================
// COMPLETE LINKED LIST CLASS
// ============================================

class SinglyLinkedList {
private:
    ListNode* head;
    ListNode* tail;
    int size;
    
public:
    // Constructor
    SinglyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    
    // Destructor
    ~SinglyLinkedList() {
        ListNode* current = head;
        while(current) {
            ListNode* next = current->next;
            delete current;
            current = next;
        }
    }
    
    // ============ INSERTION OPERATIONS ============
    
    // Insert at beginning - O(1)
    void insertAtHead(int val) {
        ListNode* newNode = new ListNode(val);
        newNode->next = head;
        head = newNode;
        
        if(!tail) tail = head;  // First node
        size++;
    }
    
    // Insert at end - O(1) with tail pointer, O(n) without
    void insertAtTail(int val) {
        ListNode* newNode = new ListNode(val);
        
        if(!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }
    
    // Insert at specific position - O(n)
    void insertAtPosition(int val, int pos) {
        if(pos < 0 || pos > size) {
            cout << "Invalid position!" << endl;
            return;
        }
        
        if(pos == 0) {
            insertAtHead(val);
            return;
        }
        if(pos == size) {
            insertAtTail(val);
            return;
        }
        
        ListNode* newNode = new ListNode(val);
        ListNode* current = head;
        
        // Move to position before insertion
        for(int i = 0; i < pos - 1; i++) {
            current = current->next;
        }
        
        newNode->next = current->next;
        current->next = newNode;
        size++;
    }
    
    // Insert in sorted order - O(n)
    void insertSorted(int val) {
        ListNode* newNode = new ListNode(val);
        
        // Case 1: Empty list or insert at head
        if(!head || head->val >= val) {
            newNode->next = head;
            head = newNode;
            if(!tail) tail = head;
            size++;
            return;
        }
        
        // Case 2: Insert in middle or end
        ListNode* current = head;
        while(current->next && current->next->val < val) {
            current = current->next;
        }
        
        newNode->next = current->next;
        current->next = newNode;
        
        if(!newNode->next) tail = newNode;  // Inserted at end
        size++;
    }
    
    // ============ DELETION OPERATIONS ============
    
    // Delete from head - O(1)
    void deleteAtHead() {
        if(!head) return;
        
        ListNode* temp = head;
        head = head->next;
        delete temp;
        size--;
        
        if(!head) tail = nullptr;
    }
    
    // Delete from tail - O(n)
    void deleteAtTail() {
        if(!head) return;
        
        if(head == tail) {
            delete head;
            head = tail = nullptr;
            size = 0;
            return;
        }
        
        ListNode* current = head;
        while(current->next != tail) {
            current = current->next;
        }
        
        delete tail;
        tail = current;
        tail->next = nullptr;
        size--;
    }
    
    // Delete first occurrence of value - O(n)
    void deleteByValue(int val) {
        if(!head) return;
        
        // If head needs to be deleted
        if(head->val == val) {
            deleteAtHead();
            return;
        }
        
        ListNode* current = head;
        while(current->next && current->next->val != val) {
            current = current->next;
        }
        
        if(current->next) {
            ListNode* temp = current->next;
            current->next = current->next->next;
            if(temp == tail) tail = current;
            delete temp;
            size--;
        }
    }
    
    // Delete at position - O(n)
    void deleteAtPosition(int pos) {
        if(pos < 0 || pos >= size) {
            cout << "Invalid position!" << endl;
            return;
        }
        
        if(pos == 0) {
            deleteAtHead();
            return;
        }
        
        ListNode* current = head;
        for(int i = 0; i < pos - 1; i++) {
            current = current->next;
        }
        
        ListNode* temp = current->next;
        current->next = current->next->next;
        if(temp == tail) tail = current;
        delete temp;
        size--;
    }
    
    // ============ SEARCHING ============
    
    // Search value - O(n)
    bool search(int val) {
        ListNode* current = head;
        while(current) {
            if(current->val == val) return true;
            current = current->next;
        }
        return false;
    }
    
    // Search value with position - O(n)
    int searchWithPosition(int val) {
        ListNode* current = head;
        int pos = 0;
        while(current) {
            if(current->val == val) return pos;
            current = current->next;
            pos++;
        }
        return -1;
    }
    
    // ============ REVERSAL OPERATIONS ============
    
    // Iterative reversal - O(n)
    void reverseIterative() {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        ListNode* next = nullptr;
        tail = head;  // Old head becomes new tail
        
        while(curr) {
            next = curr->next;  // Store next
            curr->next = prev;  // Reverse link
            prev = curr;        // Move prev
            curr = next;        // Move curr
        }
        
        head = prev;  // prev is new head
    }
    
    /*
    VISUALIZATION OF REVERSAL:
    Original: 1 → 2 → 3 → 4 → NULL
    
    Step 0: prev=NULL, curr=1, next=?
    Step 1: next=2, 1→NULL, prev=1, curr=2
    NULL ← 1    2 → 3 → 4 → NULL
    
    Step 2: next=3, 2→1, prev=2, curr=3
    NULL ← 1 ← 2    3 → 4 → NULL
    
    Step 3: next=4, 3→2, prev=3, curr=4
    NULL ← 1 ← 2 ← 3    4 → NULL
    
    Step 4: next=NULL, 4→3, prev=4, curr=NULL
    NULL ← 1 ← 2 ← 3 ← 4
    
    Result: 4 → 3 → 2 → 1 → NULL
    */
    
    // Recursive reversal
    ListNode* reverseRecursiveHelper(ListNode* node) {
        if(!node || !node->next) return node;
        
        ListNode* newHead = reverseRecursiveHelper(node->next);
        node->next->next = node;
        node->next = nullptr;
        
        return newHead;
    }
    
    void reverseRecursive() {
        tail = head;
        head = reverseRecursiveHelper(head);
    }
    
    // Reverse in groups of K
    ListNode* reverseKGroupHelper(ListNode* start, int k) {
        // Check if there are k nodes
        ListNode* check = start;
        for(int i = 0; i < k; i++) {
            if(!check) return start;  // Not enough nodes
            check = check->next;
        }
        
        // Reverse k nodes
        ListNode* prev = nullptr;
        ListNode* curr = start;
        ListNode* next = nullptr;
        
        for(int i = 0; i < k; i++) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        
        // start is now tail, connect to next reversed group
        start->next = reverseKGroupHelper(curr, k);
        return prev;  // prev is new head
    }
    
    void reverseKGroup(int k) {
        if(k <= 1) return;
        head = reverseKGroupHelper(head, k);
        
        // Update tail
        ListNode* current = head;
        while(current && current->next) {
            current = current->next;
        }
        tail = current;
    }
    
    // ============ CYCLE DETECTION & REMOVAL ============
    
    // Detect cycle using Floyd's Algorithm (Two Pointers)
    bool hasCycle() {
        if(!head) return false;
        
        ListNode* slow = head;
        ListNode* fast = head;
        
        while(fast && fast->next) {
            slow = slow->next;        // Move 1 step
            fast = fast->next->next;  // Move 2 steps
            
            if(slow == fast) return true;
        }
        return false;
    }
    
    /*
    CYCLE DETECTION VISUALIZATION:
    
    List: 1 → 2 → 3 → 4 → 5
                   ↑       ↓
                   7 ← 6 ←┘
    
    Step 1: slow=1, fast=1
    Step 2: slow=2, fast=3
    Step 3: slow=3, fast=5
    Step 4: slow=4, fast=7
    Step 5: slow=5, fast=5 ← Meeting point!
    
    Why it works: If cycle exists, fast will catch up to slow
    (like two runners on a circular track, faster one laps slower)
    */
    
    // Find starting point of cycle
    ListNode* detectCycleStart() {
        if(!head || !head->next) return nullptr;
        
        ListNode* slow = head;
        ListNode* fast = head;
        bool hasCycle = false;
        
        // Phase 1: Detect cycle
        while(fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast) {
                hasCycle = true;
                break;
            }
        }
        
        if(!hasCycle) return nullptr;
        
        // Phase 2: Find cycle start
        slow = head;
        while(slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        
        return slow;  // This is the start of cycle
    }
    
    /*
    FINDING CYCLE START - MATHEMATICAL PROOF:
    
    Let:
    L1 = distance from head to cycle start
    L2 = distance from cycle start to meeting point
    C = cycle length
    
    Slow pointer traveled: L1 + L2
    Fast pointer traveled: L1 + L2 + n*C (where n is number of cycles)
    
    Fast is 2x slow: 2(L1 + L2) = L1 + L2 + n*C
    Therefore: L1 + L2 = n*C
    Therefore: L1 = n*C - L2
    
    This means distance from head to cycle start (L1) equals
    distance from meeting point to cycle start (n*C - L2)
    
    Hence, resetting slow to head and moving both pointers at same speed
    will make them meet at cycle start!
    */
    
    // Remove cycle
    void removeCycle() {
        ListNode* cycleStart = detectCycleStart();
        if(!cycleStart) return;
        
        ListNode* current = cycleStart;
        while(current->next != cycleStart) {
            current = current->next;
        }
        current->next = nullptr;  // Break the cycle
    }
    
    // ============ MERGING LISTS ============
    
    // Merge two sorted lists
    static ListNode* mergeTwoSortedLists(ListNode* l1, ListNode* l2) {
        // Create dummy node to simplify logic
        ListNode dummy(0);
        ListNode* current = &dummy;
        
        while(l1 && l2) {
            if(l1->val <= l2->val) {
                current->next = l1;
                l1 = l1->next;
            } else {
                current->next = l2;
                l2 = l2->next;
            }
            current = current->next;
        }
        
        // Attach remaining nodes
        current->next = l1 ? l1 : l2;
        
        return dummy.next;
    }
    
    // ============ MIDDLE ELEMENT ============
    
    // Find middle using Two Pointers (Tortoise and Hare)
    ListNode* findMiddle() {
        if(!head) return nullptr;
        
        ListNode* slow = head;
        ListNode* fast = head;
        
        while(fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        return slow;
    }
    
    // ============ OTHER OPERATIONS ============
    
    // Get length
    int getSize() {
        return size;  // O(1) with size tracking
    }
    
    // Alternative: Calculate length - O(n)
    int length() {
        int count = 0;
        ListNode* current = head;
        while(current) {
            count++;
            current = current->next;
        }
        return count;
    }
    
    // Get Nth node from end
    ListNode* getNthFromEnd(int n) {
        if(n <= 0 || n > size) return nullptr;
        
        ListNode* first = head;
        ListNode* second = head;
        
        // Move first n steps ahead
        for(int i = 0; i < n; i++) {
            first = first->next;
        }
        
        // Move both until first reaches end
        while(first) {
            first = first->next;
            second = second->next;
        }
        
        return second;
    }
    
    // Remove Nth node from end
    void removeNthFromEnd(int n) {
        if(n <= 0 || n > size) return;
        
        ListNode dummy(0);
        dummy.next = head;
        ListNode* first = &dummy;
        ListNode* second = &dummy;
        
        // Move first n+1 steps ahead
        for(int i = 0; i <= n; i++) {
            first = first->next;
        }
        
        // Move both until first reaches end
        while(first) {
            first = first->next;
            second = second->next;
        }
        
        // Delete node
        ListNode* temp = second->next;
        second->next = second->next->next;
        if(temp == tail) tail = second;
        delete temp;
        size--;
        
        head = dummy.next;
    }
    
    // Check if palindrome
    bool isPalindrome() {
        if(!head || !head->next) return true;
        
        // Find middle
        ListNode* slow = head;
        ListNode* fast = head;
        while(fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        // Reverse second half
        ListNode* prev = nullptr;
        ListNode* curr = slow;
        while(curr) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        
        // Compare first and second half
        ListNode* first = head;
        ListNode* second = prev;
        while(second) {
            if(first->val != second->val) return false;
            first = first->next;
            second = second->next;
        }
        
        return true;
    }
    
    // Remove duplicates from sorted list
    void removeDuplicatesSorted() {
        if(!head) return;
        
        ListNode* current = head;
        while(current && current->next) {
            if(current->val == current->next->val) {
                ListNode* temp = current->next;
                current->next = current->next->next;
                if(temp == tail) tail = current;
                delete temp;
                size--;
            } else {
                current = current->next;
            }
        }
    }
    
    // Display list
    void display() {
        ListNode* current = head;
        while(current) {
            cout << current->val;
            if(current->next) cout << " → ";
            current = current->next;
        }
        cout << " → NULL" << endl;
    }
    
    // Display with size info
    void displayDetailed() {
        cout << "List (size=" << size << "): ";
        display();
        if(head) cout << "Head: " << head->val << endl;
        if(tail) cout << "Tail: " << tail->val << endl;
    }
};
