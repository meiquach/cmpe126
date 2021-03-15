#include <string>
#include "calculator.h"
#include<iostream>

namespace lab4 {
    // AUXILIARY FUNCTIONS
    bool is_number(std::string input_string);

    bool is_operator(std::string input_string);

    int get_number(std::string input_string);

    std::string get_operator(std::string input_string);

    int operator_priority(std::string operator_in);

    void calculator::parse_to_infix(std::string &input_expression) {
        lab1::expressionstream input(input_expression);
        //keep looping till we reach the end
        while (input.get_current_token() != "\0") {
            infix_expression.enqueue((input.get_current_token()));
            input.get_next_token();
        }
        /*unsigned size = infix_expression.size();
        for(int i =0; i<size;i++){
            std::cout<<infix_expression.top()<<std::endl;
            infix_expression.dequeue();
        }*/
        convert_to_postfix(infix_expression);
    }

    void calculator::convert_to_postfix(lab3::fifo infix_expression) {
        lab3::lifo Stack; //Create a stack

        while(infix_expression.is_empty() == false) {
            //std::string c=infix_expression.top();

            if(is_number(infix_expression.top())){
                postfix_expression.enqueue(infix_expression.top()); //push to output
            }
            else if(is_operator(infix_expression.top())){
                while(!Stack.is_empty() && operator_priority(Stack.top())>= operator_priority(infix_expression.top()) && Stack.top()!="("){
                    postfix_expression.enqueue(Stack.top());
                    Stack.pop();
                }
                Stack.push(infix_expression.top());
            }
            else if(infix_expression.top() =="("){
                //postfix_expression.enqueue((Stack.top()));
                Stack.push(infix_expression.top());
            }
            else if(infix_expression.top() ==")"){
                while(Stack.top()!="("){
                    postfix_expression.enqueue(Stack.top());
                    Stack.pop();
                    if(Stack.is_empty()){
                        throw -1;
                    }
                }
                Stack.pop();
            }
            infix_expression.dequeue();
        }
        while(!Stack.is_empty()){
            postfix_expression.enqueue(Stack.top());
            Stack.pop();
        }
        //std::cout<< *this<<std::endl;
    }


    calculator::calculator() {

    }

    calculator::calculator(std::string &input_expression) {
        parse_to_infix(input_expression);
        //convert_to_postfix(infix_expression);

    }

    std::istream &operator>>(std::istream &stream, calculator &RHS) {
        //do sth
        return stream;
    }

    int lab4::calculator::calculate() {
        lab3::lifo stack;
        int x,y;

        //while(postfix_expression.size() > 0)
        while(postfix_expression.is_empty() == false)
        {
            //std::string v = postfix_expression.top();

            if(is_operator(postfix_expression.top()) == false)
            {
                stack.push(postfix_expression.top());
            }
            else if(postfix_expression.top() == "*")
            {
                y = get_number(stack.top());
                stack.pop();
                x = get_number(stack.top());
                stack.pop();
                x *= y;

                stack.push(std::to_string(x));
            }
            else if(postfix_expression.top() == "/")
            {
                y = get_number(stack.top());
                stack.pop();
                x = get_number(stack.top());
                stack.pop();

                x /= y;

                stack.push(std::to_string(x));
            }
            else if(postfix_expression.top() == "+")
            {
                y = get_number(stack.top());
                stack.pop();
                x = get_number(stack.top());
                stack.pop();
                x += y;

                stack.push(std::to_string(x));
            }
            else if(postfix_expression.top() == "-")
            {
                y = get_number(stack.top());
                stack.pop();
                x = get_number(stack.top());
                stack.pop();
                x -= y;

                stack.push(std::to_string(x));
            }

            postfix_expression.dequeue();
        }

        //std::cout << "answer: " << x << std::endl;

        return x;
    }

    std::ostream &operator<<(std::ostream &stream, calculator &RHS) {
        lab3::fifo copy2(RHS.postfix_expression);
        lab3::fifo copy1(RHS.infix_expression);

        std::cout<<"Infix: "<<copy1.top();
        copy1.dequeue();

        while(copy1.size()>0){
            std::cout<<","<< copy1.top();
            copy1.dequeue();
        }

        std::cout << "\nPostfix: " << copy2.top();
        copy2.dequeue();

        while(copy2.size() > 0){
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