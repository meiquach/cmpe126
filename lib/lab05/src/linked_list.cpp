#include <linked_list.h>
namespace lab5 {
    linked_list::linked_list() {
        head = nullptr;
        tail = nullptr;

    }

    linked_list::linked_list(std::string &data) : linked_list(){
        append(data);

    }

    linked_list::linked_list(const linked_list &original) {
        head = nullptr;
        node *temp;
        if (original.head == NULL) {
            head = NULL;
            tail = NULL;
        } else {
            temp = original.head;

            for (int i = 0; i < original.listSize(); i++) {
                append(temp->data);
                temp = temp->next;
            }
        }
    }

    linked_list::~linked_list() {
        while(head != nullptr){
            remove(0);
        }

    }

    linked_list &lab5::linked_list::operator=(const linked_list &RHS) {
        //return <#initializer#>;
        while(head != nullptr){
            remove(0);
        }
        head = nullptr;
        tail = nullptr;

        node *tmp;
        tmp = RHS.head;
        for (int i = 0; i < RHS.listSize(); i++) {
            append(tmp->data);
            tmp = tmp->next;
        }
        return *this;
    }


    bool linked_list::isEmpty() const {
        return head == nullptr;

    }

    unsigned linked_list::listSize() const {
        node *tmp;
        int x = 1;

        tmp = head;

        if (isEmpty() == true) {
            return 0;
        } else {
            while (tmp->next != NULL) {
                x++;
                tmp = tmp->next;
            }
        }

        return x;
    }

    void linked_list::insert(const std::string input, unsigned int location) {
        node *tmp = new node(input);

        //std::cout << "location: " << location << "\n";
        //std::cout << "Insert: " << input << "\n";

        if (head == NULL || location == 0) {
            if (head == NULL) {
                head = tmp;
                tail = tmp;
            } else {
                tail = head;
                tmp->next = head;
                head = tmp;
            }

        } else {
            int m = 1;
            node *tmp = head;

            while (tmp->next != NULL && m != location) {
                tmp = tmp->next;
                ++m;
            }

            if (m != location) {
                append(input);
            } else {
                node *t2 = new node(input);

                t2->next = tmp->next;
                tmp->next = t2;
            }
        }
    }

    void linked_list::append(const std::string input) {
        node *temp = new node(input), *t1;

        if (head == NULL) {
            head = temp;
        } else {
            t1 = head;

            while (t1->next != NULL) {
                t1 = t1->next;
            }
            t1->next = temp;
        }
        tail = temp;
    }

    void linked_list::remove(unsigned location) {

        //std::cout << "location: " << location << "\n";

        if (location == 0) {
            node *tmp; //tmp pointer
            tmp = head; //tmp is a first node

            //std::cout << "remove: " << head->data << "\n";
            head = head->next;
            delete tmp;

            if(head == nullptr){ //if one-node list
                tail = nullptr;
            }

        } else {
            int n = 1;
            node *tmp = head;

            while (tmp->next != NULL && n < location) {
                tmp = tmp->next;
                ++n;
            }
            node *tmp1 = tmp->next;
            tmp->next = tmp->next->next;
            delete tmp1;

            if(tmp->next == nullptr){ //when the tail was removed
                tail = tmp;
            }
        }

    }

    std::ostream &operator<<(std::ostream &stream, linked_list &RHS) {
        node *tmp;

        tmp = RHS.head;

        std::cout << tmp->data;
        tmp = tmp->next;

        while (tmp->next != NULL) {
            std::cout << " -> " << tmp->data;
            tmp = tmp->next;
        }

        std::cout << " -> " << tmp->data;
        tmp = tmp->next;

        if (tmp == NULL) {
            std::cout << " -> " << "NULL";
        }


        return stream;
    }

    std::istream &operator>>(std::istream &stream, linked_list &RHS) {
        std::string word;

        stream >> word;

        RHS.append(word);

        return stream;
    }

    void linked_list::sort() {
        node *sorted = NULL;
        node *current = head;

        while (current != NULL)
        {
            node *next = current->next;

            node *current_sorted;

            if (sorted == NULL || sorted->data >= current->data)
            {
                current->next = sorted;
                sorted = current;
            }
            else
            {
                current_sorted = sorted;

                while (current_sorted->next != NULL && current_sorted->next->data < current->data)
                {
                    current_sorted = current_sorted->next;
                }

                current->next = current_sorted->next;
                current_sorted->next = current;
            }

            current = next;
        }

        head = sorted;

    }

    std::string linked_list::get_value_at(unsigned location) const {
        node *tmp;
        tmp = head;
        int count = 0;

        //std::cout << "location: " << location << "\n";

        while (count != location && tmp->next != NULL) {
            ++count;
            tmp = tmp->next;
        }

        //std::cout << "data: " << tmp->data << "\n";

        return tmp->data;

    }
}