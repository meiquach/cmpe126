#include "fancy_calculator.h"
#include "stack.h"
#include "queue.h"

namespace lab5{
    // AUXILIARY FUNCTIONS
    bool is_number(std::string input_string);

    bool is_operator(std::string input_string);

    int get_number(std::string input_string);

    std::string get_operator(std::string input_string);

    int operator_priority(std::string operator_in);

    void calculator::parse_to_infix(std::string &input_expression) {
        lab1::expressionstream input(input_expression);
        infix_expression = lab5::queue();

        //keep looping till we reach the end
        while (input.get_current_token() != "\0") {
            infix_expression.enqueue((input.get_current_token()));
            input.get_next_token();
        }
        convert_to_postfix(infix_expression);
    }

    void calculator::convert_to_postfix(lab5::queue infix_expression) {
        stack s1;
        //std::cout<<infix_expression.queueSize()<<"\n";
        postfix_expression = lab5::queue();
        while(infix_expression.isEmpty() == false) {
            //std::string c=infix_expression.top();

            if(is_number(infix_expression.top())){
                postfix_expression.enqueue(infix_expression.top()); //push to output
            }
            else if(is_operator(infix_expression.top())){
                while(!s1.isEmpty() && operator_priority(s1.top())>= operator_priority(infix_expression.top()) && s1.top()!="("){
                    postfix_expression.enqueue(s1.top());
                    s1.pop();
                }
                s1.push(infix_expression.top());
            }
            else if(infix_expression.top() =="("){
                //postfix_expression.enqueue((s1.top()));
                s1.push(infix_expression.top());
            }
            else if(infix_expression.top() ==")"){
                while(s1.top()!="("){
                    postfix_expression.enqueue(s1.top());
                    s1.pop();
                    if(s1.isEmpty()){
                        throw -1;
                    }
                }
                s1.pop();
            }
            infix_expression.dequeue();
        }
        while(!s1.isEmpty()){ //solve the last element take-in problem
            postfix_expression.enqueue(s1.top());
            s1.pop();
        }
        //std::cout<< *this<<std::endl;
    }

    calculator::calculator() {

    }

    calculator::calculator(std::string &input_expression) {
        parse_to_infix(input_expression);
    }

    std::istream &operator>>(std::istream &stream, calculator &RHS) {
        std::string t ="";
        getline(stream, t);
        RHS.parse_to_infix(t);
        return stream;
    }

    int calculator::calculate() {
        stack s2;
        int x,y;

        //while(postfix_expression.size() > 0)
        while(postfix_expression.isEmpty() == false)
        {
            std::string v = postfix_expression.top();

            if(is_operator(postfix_expression.top()) == false)
            {
                s2.push(postfix_expression.top());
            }
            else if(postfix_expression.top() == "*")
            {
                y = get_number(s2.top());
                s2.pop();
                x = get_number(s2.top());
                s2.pop();
                x *= y;

                s2.push(std::to_string(x));
            }
            else if(postfix_expression.top() == "/")
            {
                y = get_number(s2.top());
                s2.pop();
                x = get_number(s2.top());
                s2.pop();

                x /= y;

                s2.push(std::to_string(x));
            }
            else if(postfix_expression.top() == "+")
            {
                y = get_number(s2.top());
                s2.pop();
                x = get_number(s2.top());
                s2.pop();
                x += y;

                s2.push(std::to_string(x));
            }
            else if(postfix_expression.top() == "-")
            {
                y = get_number(s2.top());
                s2.pop();
                x = get_number(s2.top());
                s2.pop();
                x -= y;

                s2.push(std::to_string(x));
            }

            postfix_expression.dequeue();
        }

        //std::cout << "answer: " << x << std::endl;

        return x;
    }

    std::ostream &operator<<(std::ostream &stream, calculator &RHS) {
        queue copy2(RHS.postfix_expression);
        queue copy1(RHS.infix_expression);
        //std::cout<<copy2.queueSize()<<"\n";

        std::cout<<"Infix: "<<copy1.top();
        copy1.dequeue();

        while(copy1.queueSize()>0){
            std::cout<<","<< copy1.top();
            copy1.dequeue();
        }

        std::cout << "\nPostfix: " << copy2.top();
        copy2.dequeue();

        //std::cout<<copy2.queueSize()<<"\n";

        /*while(copy2.isEmpty()==false){
            std::cout << "," << copy2.top();
            copy2.dequeue();
        }*/

        while(copy2.queueSize() > 0){
            std::cout << "," << copy2.top();
            copy2.dequeue();
        }

        return stream;
    }


    // AUXILIARY FUNCTIONS
    bool is_number(std::string input_string){
        for(char c:input_string){ //go to all element
            if(!(c >= '0' && c <= '9')){
                return false;
            }
        }
        return true;
    }

    bool is_operator(std::string input_string){
        if(input_string == "+" || input_string == "-" || input_string == "*" || input_string == "/" ){
            return true;
        }
        return false;
    }

    int get_number(std::string input_string){
        return stoi(input_string);
    }

    std::string get_operator(std::string input_string){
        return input_string;
    }

    int operator_priority(std::string operator_in){
        if(operator_in == "/" || operator_in == "*"){
            return 3;
        }
        else if(operator_in == "+" || operator_in == "-"){
            return 2;
        }else if(operator_in == "("|| operator_in == ")"){
            return 1;
        }else{
            return 0;
        }
    }
}


