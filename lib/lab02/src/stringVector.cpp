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
        data = str;

        if(length > new_size){
            length = new_size;
    }
        delete[] str;
    }


    bool stringVector::empty() const
    { //check if empty
        if(length == 0)
            return true;
        else
            return false;

    }
    void stringVector::append(std::string new_data) {
        std::string *str = new std::string[allocated_length];
        //string *str = nullptr;

        if(length == allocated_length) {

            if (allocated_length == 0) {
                delete[] data;
                data = new std::string[1];
                allocated_length = allocated_length + 1;
            } else if (allocated_length > 0) {
                str = new std::string[2 * allocated_length];
                for (int i = 0; i < length; i++) {
                    str[i] = data[i];
                }
            }

            allocated_length = allocated_length * 2;

            delete[] data;
            data = new std::string[allocated_length];

            for (int i = 0; i < length; i++) {
                data[i] = str[i];
            }
        }

        data[length] = new_data;
        length++;

        delete [] str;
        /*if(length == allocated_length){
            if(allocated_length == 0){
                allocated_length = 1;
                data = new std::string[allocated_length];
                data[0] = new_data;
            }
            else if(allocated_length > length){
                data[length] = new_data;
            }
            else{
                reserve(allocated_length * 2);
                data[length] = new_data;
            }
            }
        length++;*/
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
            std::cout << rhs.data[i] << std::endl;
            this->data[i] = rhs.data[i];
            std::cout << data[i] << std::endl;
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






