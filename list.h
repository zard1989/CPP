#ifndef LIST
#define LIST

#include <iostream>
using namespace std;

template <class T>
class ListNode {
private:
    T _content;
    ListNode* _next_node;
public:
    ListNode(T content) {
        _content   = content;
        _next_node = NULL;
    }
    
    ~ListNode() {
    }

    T& get_content() {
        return _content;
    }

    T set_content(T new_content) {
        T old_content = _content;
        _content    = new_content;
    
        return old_content;
    }

    ListNode* get_next_node() {
        return _next_node;
    }

    ListNode* set_next_node(T next_node_content) {
        _next_node = new ListNode(next_node_content);
        return _next_node;
    }
    
    ListNode* set_next_node(ListNode* next_node) {
        _next_node = next_node;
        return _next_node;
    }

    bool is_tail() {
        if (_next_node == NULL)
            return true;
        else
            return false;
    }
};


template <class T>
class List {
private:
    ListNode<T>* _first_node;
    int _size;
    ListNode<T>* walk_to(int pos) {
        if (_size == 0 || pos < 0 || pos >= _size) {
            cout <<"Wrong index!!" <<endl;
            return NULL;
        }
        
        ListNode<T>* target = _first_node;
        
        for (int i=0;i<pos;i++) {
            target = target->get_next_node();
        }
        
        return target;
    }
public:
    List() {
        _size        = 0;
        _first_node = NULL;
    }
    
    List& push(T content) {
        if (_size == 0) {
            _first_node = new ListNode<T>(content);
            _size++;
            return *this;
        }
        
        ListNode<T>* tail_node = walk_to(_size-1);
        tail_node->set_next_node(content);
        _size++;
        
        return *this;
    }
    
    T pop() {
        if (_size == 0)
            return NULL;
        
        if (_size == 1) {
            T content = walk_to(0)->get_content();
            delete walk_to(0);
            _size--;
            return content;
        }
        
        ListNode<T>* new_tail_node = walk_to(_size-2);
        
        T content = new_tail_node->get_next_node()->get_content();
        delete new_tail_node->get_next_node();
        new_tail_node->set_next_node(NULL);
        
        _size--;
        
        return content;
    }
    
    T& get(int pos) {
        ListNode<T>* the_node = walk_to(pos);
        return the_node->get_content();
    }
    
    List& unshift(T content) {
        T old_content = _first_node->get_content();
        ListNode<T>* old_next = _first_node->get_next_node();
        
        _first_node->set_content(content);
        _first_node->set_next_node(old_content);
        _first_node->get_next_node()->set_next_node(old_next);
        
        _size++;
        
        return *this;
    }
    
    T shift() {
        if (_size == 0)
            return T();
        
        if (_size == 1) {
            T content = walk_to(0)->get_content();
            delete walk_to(0);
            _size--;
            return content;
        }
        
        T old_content = _first_node->get_content();
        
        ListNode<T>* next_node = _first_node->get_next_node();
        
        _first_node->set_content(next_node->get_content());
        _first_node->set_next_node(next_node->get_next_node());
        
        delete next_node;
        
        _size--;
        return old_content;
    }
    
    List& insert(int pos, T content) {
        if (pos == 0)
            return unshift(content);
        else if (pos == _size)
            return push(content);
        else if (pos > _size || pos < 0) {
            cout <<"Index must be in 0 to size. Do nothing." <<endl;
            return *this;
        }
        
        ListNode<T>* before  = walk_to(pos-1);
        ListNode<T>* after   = walk_to(pos);
        ListNode<T>* the_one = new ListNode<T>(content);
        before->set_next_node(the_one);
        the_one->set_next_node(after);
        
        _size++;
        return *this;
    }
    
    T remove(int pos) {
        if (pos == 0)
            return shift();
        else if (pos == _size-1)
            return pop();
        else if (pos >= _size || pos < 0 ) {
            cout <<"Index must be in 0 to size-1. Do nothing" <<endl;
            return NULL;
        }
        
        ListNode<T>* before  = walk_to(pos-1);
        ListNode<T>* the_one = before->get_next_node();
        ListNode<T>* after   = the_one->get_next_node();
        
        T content = the_one->get_content();
        
        delete the_one;
        
        before->set_next_node(after);
        
        _size--;
        
        return content; 
    }
    
    int size() {
        return _size;
    }
    
    List& sort(int (*compare)(T a, T b)) {
        for (int i=_size-1;i>=1;i--) {
            ListNode<T>* max = walk_to(0);
            for (int j=1;j<=i;j++) {
                if (compare(max->get_content(), walk_to(j)->get_content()) == -1) {
                    max = walk_to(j);
                }
            }
            ListNode<T>* li = walk_to(i);
            T temp = li->get_content();
            li->set_content(max->get_content());
            max->set_content(temp);
        }
        
        return *this;
    }
};

#endif
