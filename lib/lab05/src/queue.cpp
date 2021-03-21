#include "queue.h"
namespace lab5{
    queue::queue() {

    }

    queue::queue(std::string &data) {
        storage_structure.append(data);

    }

    queue::queue(const queue &original) {
        for(int i=0; i< original.storage_structure.listSize(); i++) { //take in infix problem
            storage_structure.append(original.storage_structure.get_value_at(i));
        }
    }

    queue::~queue() {

    }

    queue &queue::operator=(const queue &RHS) {
        //return <#initializer#>;
        storage_structure = RHS.storage_structure;
        //return *this;
    }

    bool queue::isEmpty() const {
        if(storage_structure.isEmpty()){
            return true;
        }else{
            return false;
        }
    }

    unsigned queue::queueSize() const {
        if(storage_structure.isEmpty()){
            return 0;
        }else{
            return storage_structure.listSize();
        }
    }

    std::string queue::top() const {
        //return std::__cxx11::string();
        return storage_structure.get_value_at(0); //for queue and stack
    }

    void queue::enqueue(const std::string &data) {
        storage_structure.append(data);

    }

    void queue::dequeue() {
        storage_structure.remove();
    }

    std::ostream& operator<<(std::ostream &stream, queue &RHS) {
        return stream;
    }

    std::istream& operator>>(std::istream &stream, queue &RHS) {
        return stream;
    }
}