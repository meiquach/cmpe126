#include "stack.h"
namespace lab5{
    stack::stack() {

    }

    stack::stack(std::string &data) {
        storage_structure.insert(data);
    }

    stack::stack(const stack &original) {
        for (int i = 0; i < storage_structure.listSize(); i++) {
            storage_structure.insert(original.storage_structure.get_value_at(i));
        }
    }

    stack::~stack() {

    }

    stack &stack::operator=(const stack &RHS) {
        //return <#initializer#>;
        storage_structure = RHS.storage_structure;
    }

    bool stack::isEmpty() const {
        if(storage_structure.isEmpty()){
            return true;
        }else{
            return false;
        }
    }

    unsigned stack::stackSize() const {
        if(storage_structure.listSize() == 0){
            return 0;
        }else{
            return storage_structure.listSize();
        }
    }

    std::string stack::top() const {
        //return std::__cxx11::string();
        return storage_structure.get_value_at(0);
    }

    void stack::push(const std::string &data) {
        storage_structure.insert(data);

    }

    void stack::pop() {
        storage_structure.remove();

    }

    std::ostream& operator<<(std::ostream &stream, stack &RHS) {
        return stream;
    }

    std::istream& operator>>(std::istream &stream, stack &RHS) {
        return stream;
    }
}