#ifndef TIMER_H
#define TIMER_H

#include <string>
#include <stack>
#include <chrono>


using namespace std::chrono;

class Timer{
    public:
        std::stack<high_resolution_clock::time_point> tictoc_stack;

        void tic(){
            high_resolution_clock::time_point t1 = high_resolution_clock::now();
            tictoc_stack.push(t1);
        }

        double toc(){   
            duration<double, std::micro> diff = high_resolution_clock::now() - tictoc_stack.top();
            tictoc_stack.pop();
            return diff.count();
        }
        void reset(){
            tictoc_stack = std::stack<high_resolution_clock::time_point>();
        }
};

#endif