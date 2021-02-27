#include "lifo.h"

namespace lab3{
    lifo::lifo() {
    //Reserve 100 spaces in lifo_storage
        lifo_storage.reserve(100);
        index = 0;
    }

    lifo::lifo(std::string input_string) : lifo(){ //does the same thing as the constructor
        /*lifo_storage.reserve(100);
        index = 0;*/
        /*lifo_storage.append(input_string);
        index++;*/
        push(input_string);

    }

    lifo::lifo(const lifo &original) {
        index = original.index;
        lifo_storage = original.lifo_storage;
    }

    lifo::~lifo() {

    }

    lifo &lifo::operator=(const lifo &right) {
        //return <#initializer#>;
        lifo_storage = right.lifo_storage;
        index = right.index;
        return *this;
    }

    bool lifo::is_empty(){
        //return false;
        return size()==0;
    }

    int lifo::size(){
        //return 0;
        return index;
    }

    std::string lifo::top(){
        //return std::__cxx11::string();
        return lifo_storage[index-1];
    }

    void lifo::push(std::string input) {
        if(size()==100){
            throw -1;
        }
        /*if(index == lifo_storage.capacity()){
            lifo_storage.reserve(lifo_storage.capacity());
        }*/
        lifo_storage.append(input);
        index++;
    }

    void lifo::pop() {
        if(size()==0){
            throw -1;
        }
        //if(index >= 0)
        index--;
    }
}