#include "../inc/doubly_linked_list.h"

namespace lab6{
    doubly_linked_list::doubly_linked_list() {
        head = nullptr;
        tail = nullptr;
    }

    doubly_linked_list::doubly_linked_list(int input):doubly_linked_list() {
        append(input);
    }

    doubly_linked_list::doubly_linked_list(std::vector<int> vector_input) : doubly_linked_list() {
        //convert a vector into a linked list
        for (int num : vector_input)
            append(num);
    }

    doubly_linked_list::doubly_linked_list(const doubly_linked_list &original) {
        node *temp = original.head;
        node *copy = new node(temp->get_data());
        this->head = copy;
        while (temp->next != nullptr){
            temp = temp->next;
            node *copy1 = new node(temp->get_data());
            copy->next = copy1;
            copy1->prev = copy;
            copy = copy1;
        }
    }

    doubly_linked_list::~doubly_linked_list() { //delete every single nodes
        while(head != nullptr){
            remove(0);
        }
    }

    int doubly_linked_list::get_data(unsigned position) {
        if (is_empty())
            throw -1;
        node *temp = head;
        int result;
        if (position >= size()){
            throw -1;
        }
        for (int i = 0; i< position;i++){
            temp = temp->next;
        }
        return result = temp->get_data();

    }

    std::vector<int> doubly_linked_list::get_set(unsigned position_from, unsigned position_to) {
        node *current = head;
        std::vector<int>result;
        int count; //location in the result vector
        if (position_from >= size() || position_to >= size() || position_from > position_to || position_from < 0 || position_to < 0){
            throw -1;
        }
        for (int i = 0; i<position_from; i++){
            current = current->next;
        }
        for (int i = position_from; i <= position_to; i++){
            count = current-> get_data();
            current = current->next;
            result.push_back(count);
        }
        return result;

    }

    unsigned doubly_linked_list::size() {
        node *temp = head;
        unsigned count = 0;
        while(temp != nullptr){
            temp = temp-> next;
            count++;
        }
        return count;
    }

    bool doubly_linked_list::is_empty() {
        return head == nullptr;
    }

    void doubly_linked_list::append(int input) {
        node *temp = new node(input);
        node *current = head;
        if (!is_empty()){
            while(current->next != nullptr){
                current = current->next;
            }
            current->next = temp;
            temp->next = nullptr;
            temp->prev = current;
            tail = temp;
        }
        else {
            head = temp;
            tail = temp;
        }
    }

    void doubly_linked_list::insert(int input, unsigned int location) {
        if (head == nullptr) {
            if (location == 0)
                append(input);
            else throw -1;

        } else if (location == 0) {
            // Put a new node before the head and update the head
            head->prev = new node(input);
            head->prev->next = head;
            head = head->prev;
        } else {
            // To be inserted node is the node before the index pos
            node *in_front = head;
            for (unsigned i = 0; i < location - 1; i++) {
                in_front = in_front->next;
                if (!in_front)
                    throw -1;
            }
            // make a connection, the inserted node point backwards to in_front node and forwards to the node after
            node *inserted = new node(input);
            inserted->next = in_front->next;
            inserted->prev = in_front;
            inserted->prev->next = inserted;  // Make the node before point forwards to the node after

            // Make the node after point backwards to the node in_front
            // reach the end no more node, then update tail
            if (inserted->next) {
                inserted->next->prev = inserted;
            }else
                tail = inserted;
        }

    }

    void doubly_linked_list::remove(unsigned location) {
        if(is_empty())
            throw -1;
        node *prev = nullptr;
        node *current = head;
        if (location > size()){
            throw -1;
        }
        for(int i = 0; i< location; i++){
            prev = current;
            current = current->next;
            if(!current)
                throw -1;
        }
        if (prev) { // edge case for a previous node
            if(!current->next){
                prev->next = nullptr;
                tail = prev;
                delete(current);
                return;
            }
            prev->next = current->next;
            current->next->prev = current->prev;
        }
        else{
            head = current->next;
        }
        delete(current);

    }

    doubly_linked_list doubly_linked_list::split(unsigned position) {
        if (is_empty())
            throw -1;
        doubly_linked_list split(get_set(position, size() - 1));
        for(int i = size() - 1; i >= position && i >=0; i--){
            remove(i);
        }
        return split;

    }

    doubly_linked_list doubly_linked_list::split_set(unsigned position_1, unsigned position_2) {
        doubly_linked_list split_set;
        node* temp = head;
        int counter = 0;
        while(counter != position_1){
            temp = temp->next;
            counter++;
        }

        node* temp2 = temp;
        for (int i = position_1; i < position_2; i++){
            split_set.append(temp2->get_data());
            temp2 = temp2->next;
        }
        split_set.append(temp2->get_data());
        for(int i = position_2; i >= int(position_1); i--){
            remove(i);
        }
        return split_set;

    }

    void doubly_linked_list::swap(unsigned position_1, unsigned position_2) {
        // Swap wrongly ordered indices and check for same indices
        if (position_1 > position_2)
            std::swap(position_1, position_2);
        else if (position_1 == position_2) {
            if (position_1 >= size())
                throw -1;
            return;
        }
        int listOne = get_data(position_1);
        int listTwo = get_data(position_2);
        remove(position_1);
        remove(position_2 - 1);
        insert(listOne, position_2 - 1);
        insert(listTwo, position_1);

    }

    void doubly_linked_list::swap_set(unsigned location_1_start, unsigned location_1_end, unsigned location_2_start,
                                      unsigned location_2_end) {
        node* tempA = head;
        if(location_1_start > location_2_start && location_1_start > location_2_end){
            int start = location_1_start;
            int end = location_1_end;
            location_1_start = location_2_start;            //makes sure that the start1 is before start2
            location_2_start = start;                       //makes sure that start1 comes before end2
            location_1_end = location_2_end;
            location_2_end = end;
        }
        if(location_1_start > location_1_end){
            int temp = location_1_start;            //performs a simple temp swap if the start and end locations are flipped for location1
            location_1_start = location_1_end;
            location_1_end = temp;
        }
        if(location_2_start > location_2_end){
            int temp = location_2_start;
            location_2_start = location_2_end;
            location_2_end = temp;
        }
        if(location_1_end >= location_2_start){
            throw "error: invalid location bounds.";
        }
        int count = 0;
        while(count != location_1_start){
            tempA = tempA->next;
            count++;
        }
        node* tempB = tempA;
        while(count != location_1_end){
            tempB = tempB->next;
            count++;
        }
        node* tempC = tempB;
        while(count != location_2_start){
            tempC = tempC->next;
            count++;
        }
        node* tempD = tempC;
        while(count != location_2_end){
            tempD = tempD->next;
            count++;
        }
        node* tempAprev = tempA->prev;
        node* tempAnext = tempB->next;
        node* tempBprev = tempC->prev;
        node* tempCnext = tempD->next;

        if (tempAprev != nullptr && tempCnext != nullptr && tempBprev == tempB){
            tempAprev->next = tempC;
            tempC->prev = tempAprev;
            tempD->next = tempA;
            tempA->prev = tempD;
            tempB->next = tempCnext;
            tempCnext->prev = tempB;
        }
        else if(tempAprev == nullptr && tempCnext != nullptr){
            //edge case for swapping set with head and another set that does not have a tail
            if(tempAnext == tempD || tempBprev == tempD){
                tempC->prev = nullptr;
                tempD->next = tempA;
                tempA->prev = tempD;
                tempB->next = tempCnext;
                tempCnext->prev = tempD;
                head = tempC;
            }
            else{
                tempC->prev = nullptr;
                tempD->next = tempAnext;
                tempAnext->prev = tempD;
                tempBprev->next = tempA;
                tempA->prev = tempBprev;
                tempB->next = tempCnext;
                tempCnext->prev = tempB;
                head = tempC;
            }
        }
        else if(tempAprev != nullptr && tempCnext == nullptr){                       //edge case for swapping a set with tail and a set that does not have a head
            if(tempBprev == tempB){
                tempAprev->next = tempC;
                tempC->prev = tempAprev;
                tempD->next = tempA;
                tempB->prev = tempD;
                tempB->next = nullptr;
                tail = tempB;
            }
            else{
                tempAprev->next = tempC;
                tempC->prev = tempAprev;
                tempD->next = tempAnext;
                tempAnext->prev = tempD;
                tempBprev->next = tempA;
                tempA->prev = tempBprev;
                tempB->next = nullptr;
                tail = tempB;
            }
        }
        else if(tempAprev == nullptr && tempCnext == nullptr){
            if(tempBprev == tempB){
                tempC->prev = nullptr;
                tempD->next = tempA;
                tempA->prev = tempD;
                tempB->next = nullptr;
                head = tempC;
                tail = tempB;
            }
            else{
                tempC->prev = nullptr;
                tempD->next = tempAnext;
                tempAnext->prev = tempD;
                tempBprev->next = tempA;
                tempA->prev = tempBprev;
                tempB->next = nullptr;
                head = tempC;
                tail = tempB;
            }
        }
        else{
            tempAprev->next = tempC;
            tempC->prev = tempAprev;
            tempD->next = tempAnext;
            tempAnext->prev = tempD;
            tempBprev->next = tempA;
            tempA->prev = tempBprev;
            tempB->next = tempCnext;
            tempCnext->prev = tempB;
        }
    }

    void doubly_linked_list::sort() {
        unsigned listSize = size();
        if (listSize == 0) return;
        for (unsigned current = 0; current < listSize - 1; current++) {
            unsigned smallest = current;
            for (unsigned candidate = current + 1; candidate < listSize; candidate++)
                if (get_data(candidate) < get_data(smallest))
                    smallest = candidate;
            swap(current, smallest);
        }
    }

    doubly_linked_list doubly_linked_list::operator+(const doubly_linked_list &rhs) const {
        doubly_linked_list list(*this);
        list += rhs;
        return list;
    }

    doubly_linked_list& doubly_linked_list::operator=(const doubly_linked_list &rhs) {
        if (this == &rhs) {
            return *this;
        }
        // not empty then delete
        while (!is_empty())
            remove(0);
        // Copy the values from the rhs list to this list
        *this += rhs;
        return *this;

        /*while(!this->is_empty()){
            this->remove(0);
        }
        node* copy = rhs.head;
        while(copy != nullptr){
            this->append(copy->get_data());
            copy = copy->next;
        }
        return *this;*/

    }

    doubly_linked_list& doubly_linked_list::operator+=(const doubly_linked_list &rhs) {;
        node *rhs_temp = rhs.head;
        while(rhs_temp != nullptr){
            this->append(rhs_temp->get_data());
            rhs_temp = rhs_temp->next;
        }
        return *this;

    }

    bool doubly_linked_list::operator==(const doubly_linked_list &rhs) {
        bool done = false;
        node* lh = head;
        node* rh = rhs.head;
        while (!done) {
            if ((lh == nullptr) != (rh == nullptr)) return false;
            if ((lh->get_data()) != (rh->get_data())) return false;

            lh = lh->next;
            rh = rh->next;

            if (lh == nullptr && rh == nullptr) done = true;
        }
        return true;
    }

    std::ostream &operator<<(std::ostream &stream, doubly_linked_list &RHS) {
        node* current = RHS.head;
        stream << std::string("NULL <- ");
        while(current->next){
            stream << current->get_data();
            stream << " <-> ";
            current = current->next;
        }
        stream << current->get_data();
        stream << " -> NULL";
        return stream;

    }

    std::istream &operator>>(std::istream &stream, doubly_linked_list &RHS) {
        int input;
        stream >> input;
        RHS.append(input);
        return stream;
    }

}

