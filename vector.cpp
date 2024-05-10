#define VECTOR_TEST 1

#include "frame.h"
#include "ztime.h"
#include <vector>

int main(int, char **)
{
    zend_execute_data ex;
    PhpFunction fn_wrap;

    constexpr size_t DEPTH = 40;
    constexpr size_t COUNT = 100'000'000;
    constexpr size_t BLOCK_SIZE = DEPTH;

    run_and_measure([&]() 
    {
        
        PhpFrame *stack = nullptr;
        std::vector<PhpFrame> slots;
        slots.reserve(2*BLOCK_SIZE);

        auto i = COUNT;
        auto d = DEPTH;
        bool f = true;
        while (i-- > 0) {
            if (f) 
            {   
                slots.emplace_back(ex, fn_wrap, stack);
                auto lastEleIt = std::prev(slots.end());
                stack = &(*lastEleIt);
            }
            else 
            {
                stack = stack !=nullptr ? stack->prev() : nullptr;
                slots.pop_back();
            }
            if (--d <= 1) {
                d = DEPTH;
                f = !f;
            }
        }

        slots.clear();
        
    }, "\n*** Using linked list with depth {} and {} iterations\n\n", DEPTH, COUNT);

    return 0;
}
