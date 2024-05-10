#include "frame.h"
#include "ztime.h"

#include <assert.h>
#include <stdio.h>
#include <memory>
#include <array>



int main(int, char **)
{
    zend_execute_data ex;
    PhpFunction fn_wrap;

    constexpr size_t DEPTH = 40;
    constexpr size_t COUNT = 100'000'000;


    run_and_measure([&]() 
    {

        PhpFrame *stack = nullptr;

        auto i = COUNT;
        auto d = DEPTH;
        bool f = true;
        while (i-- > 0) {
            if (f) 
            {   
                stack = new PhpFrame{ex, fn_wrap, stack};
            }
            else 
            {
                auto t = stack;
                stack = stack !=nullptr ? stack->prev() : nullptr;
                if (t) delete t;
            }
            if (--d <= 1) 
            {
                d = DEPTH;
                f = !f;
            }
        }

        while (stack) 
        {
            auto *t = stack;
            stack = stack->prev();
            delete t;
        }
    }, "\n*** Using linked list with depth {} and {} iterations\n\n", DEPTH, COUNT);

    return 0;
}
