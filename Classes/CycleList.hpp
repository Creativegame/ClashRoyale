//
//  CycleList.hpp
//  ClashRoyale
//
//  Created by 贾佳菊 on 16/4/21.
//
//

#ifndef CycleList_hpp
#define CycleList_hpp

#include <stdio.h>
#include <iostream>

template <typename CycleListNode>
class CycleList {
public:
    
    CycleList(){
        _size = 0;
        _head = nullptr;
        _current = nullptr;
        _pushPoint = nullptr;
    }
    ~CycleList(){
        Element *deletePointer = _head->postElement;
        while (deletePointer && deletePointer != _head) {
            delete deletePointer;
            deletePointer = deletePointer->postElement;
        }
        if (_head){
            delete _head;
        }
    }
    
    bool empty(){
        return (_size <= 0);
    }
    
    void push(CycleListNode node){
        if (_size <= 0){
            _head = new (std::nothrow) Element(node);
            _head->preElement = _head;
            _head->postElement = _head;
            _current = _head;
            _pushPoint = _head;
        }else {
            Element *newElement = new (std::nothrow) Element(node);
            newElement->postElement = _head;
            newElement->preElement = _pushPoint;
            _pushPoint->postElement = newElement;
            _pushPoint = newElement;
            _head->preElement = newElement;
        }
        ++_size;
    }
    
    CycleListNode getNext(){
        Element *currentPointer = _current;
        _current = _current->postElement;
        return currentPointer->nodeValue;
    }
    
    void print(int times){
        while (times > 0){
            printOnce();
            --times;
        }
    }
    
    void printOnce(){
        Element *printPointer = _head;
        do {
            std::cout << &printPointer->nodeValue << " ";
            printPointer = printPointer->postElement;
        }while (printPointer != _head);
        std::cout << std::endl;
    }
    
private:
    
    class Element{
    public:
        Element(CycleListNode node):
        nodeValue(node) {}
        
        CycleListNode nodeValue;
        Element *preElement = nullptr;
        Element *postElement = nullptr;
    };
    
    int _size = 0;
    Element *_head = nullptr;
    Element *_pushPoint = nullptr;
    Element *_current = nullptr;
    
};

#endif /* CycleList_hpp */
