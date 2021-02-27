#include "../inc/stringVector.h"
#include <iostream>

namespace lab2 {
    stringVector::stringVector() {
        //construct an empty object
        length = 0;
        allocated_length = 0;
        data = nullptr;
        //data = new std::string[allocated_length]; //generate the pt to memory


    }
    stringVector::~stringVector(){
        //if (data != nullptr){ //deallocate memory
            delete[] data;
    }

    unsigned stringVector::size() const {
        return length;
        //return ;
    }
    unsigned stringVector::capacity() const{
        return allocated_length;
        //return ;
    }

    void stringVector::reserve(unsigned new_size) {
        //check if allocated length = length
        std::string *str = new std::string[new_size];
        for(int i=0;i<new_size;i++){
            if(i<length){
                str[i] = data[i];
            }
            else
                break;

        }
        allocated_length = new_size;
        delete[] data;
        data = str;

        if(length > new_size){
            length = new_size;
        }
    }


    bool stringVector::empty() const
    { //check if empty
        if(length == 0)
            return true;
        else
            return false;

    }
    void stringVector::append(std::string new_data) {
        if (allocated_length == 0) {
            reserve(1);
        } else if (allocated_length == length) {
            reserve(allocated_length * 2);
        }
        data[length] = new_data; //adding new data
        length++;


    }
        //case1: if capacity is 0 set to 1
        //case2: over capacity = double array


    void stringVector::swap(unsigned pos1, unsigned pos2) {
        std::string tempt = data[pos1];
        data[pos1] = data[pos2];
        data[pos2] = tempt;

    }

    stringVector &stringVector::operator=(stringVector const &rhs) {
        if(this == &rhs)
        {
            return *this;
        }

        length = rhs.length;
        allocated_length = rhs.allocated_length;

        delete [] data;
        this->data = new std::string[allocated_length];

        for (int i = 0; i < allocated_length; i++)
        {
            this->data[i] = rhs.data[i];
        }
        //stringVector *lhs = new stringVector(); //create a new array
        //reserve(rhs.allocated_length);

        //return ;
    }

    std::string &stringVector::operator[](unsigned position) {
        if(position >= length){
             throw std::exception();

        }else{
            return data[position];
        }
        //return ;
    }

    void stringVector::sort() {
        std::string str;
        for (int i=0; i<length; i++){ //bubble sort
            for(int j =0;j<length-i-1;j++){
                if(data[j]>this->data[j+1]){
                    str = data[j];
                    data[j] = data[j+1];
                    data[j+1] = str;
                }
            }
        }
    }
}






