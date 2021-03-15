#include <linked_list.h>
namespace lab5 {
    linked_list::linked_list() {
        head->data = "\0";
        tail = head;

    }

    linked_list::linked_list(std::string &data) {
        head->data = data;
        tail = head;

    }

    linked_list::linked_list(const linked_list &original) {
        node* h, *t;
        h = original.head;
        t = original.tail;

    }

    linked_list::~linked_list() {

    }

    linked_list &lab5::linked_list::operator=(const linked_list &RHS) {
        //return <#initializer#>;
        head = RHS.head;
        tail = RHS.tail;
    }


    bool linked_list::isEmpty() const {
        if(head == nullptr){
            return true;
        }
        else{
            return false;
        }
    }

    unsigned linked_list::listSize() const {
        node* tmp;
        int x = 0;
        tmp = head;
        if(isEmpty()== true){
            return 0;
        }
        else{
             while(tmp->next!=nullptr){
                 x++;
                 tmp = tmp->next;
             }
        }
        return x;
    }

    void linked_list::insert(const std::string input, unsigned int location) {
        if(isEmpty() == true){
            head->data= input;
        }
        if(location == 0){ //at the head
            node* tmp;
            tmp->data = input;
            tmp->next = head;

            head = tmp;
        }

        else if(location !=0 && location == listSize()) {//in the end
            node *tmp = new node(input); //create new node
            /*new_node->data = new_data; //put in data
            new_node->next = prev_node -> next;
            prev_node->next = new_node;*/

        }

    }

    void linked_list::append(const std::string input) {
        node *tmp;
        tmp->data = input;
        //tmp->next =

    }

    void linked_list::remove(unsigned location) {
        node *tmp;
        node *extract;

        tmp=head;
        extract = head;

        if(location == 0){
            head = head->next;
        }

    }

    std::ostream& operator<<(std::ostream &stream, linked_list &RHS) {
        return stream;
    }

    std::istream& operator>>(std::istream &stream, linked_list &RHS) {
        return stream;
    }

    void linked_list::sort() {

    }

    std::string linked_list::get_value_at(unsigned location) {

    }
}