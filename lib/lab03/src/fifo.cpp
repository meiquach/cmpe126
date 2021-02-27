#include "fifo.h"
#include<iostream>
using namespace std;
namespace lab3{
    fifo::fifo() {
    //Reserve 100 spaces in fifo_storage
        fifo_storage.reserve(100);
        front_index = 0;
        back_index = 0;
    }

    fifo::fifo(std::string input_string) : fifo() {
        //fifo_storage.reserve(100);
        fifo_storage.append(input_string); //Add a single item
        //front_index = 0;
        //back_index= 0;
    }

    fifo::fifo(const fifo &original) {
        front_index = original.front_index;
        back_index = original.back_index;
        fifo_storage = original.fifo_storage;
        /*for(int i=0; i<fifo_storage.getlength();i++){
            cout<<fifo_storage[i]<<endl;
        }*/

        //fifo_storage.reserve( original.fifo_storage.capacity());
    }

    fifo::~fifo() {

    }

    fifo &fifo::operator=(const fifo &right) {
        //return <#initializer#>;
        fifo_storage = right.fifo_storage;
        back_index = right.back_index;
        return *this;
    }

    bool fifo::is_empty(){
        return size()==0;
        //return fifo_storage.empty();
        //return false;
    }

    int fifo::size(){
        return back_index - front_index;
        //return 0;
    }

    std::string fifo::top(){
        //cout<<"return front index"<<front_index<<endl;

        //return fifo_storage[front_index];
        return fifo_storage.operator[](front_index);
        //return std::__cxx11::string();
    }

    void fifo::enqueue(std::string input) {
        if (size() == 100){
            throw -1;
        }
        fifo_storage.append(input);
        back_index++;

    }

    void fifo::dequeue() {
        if(is_empty()){
            throw 1;
        }
        front_index++;
        //check stringVector empty
        /*if(!this->size()){
            std::cout<< "Cannot dequeue";
        }*/

        //lab2::stringVector copy_arr;

    }
}