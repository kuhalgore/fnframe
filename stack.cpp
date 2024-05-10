#define VECTOR_TEST 1

#include "frame.h"
#include "ztime.h"
#include <stack>

int main(int, char **)
{
    zend_execute_data ex;
    PhpFunction fn_wrap;

    constexpr size_t DEPTH = 40;
    constexpr size_t COUNT = 100'000'000;

    run_and_measure([&]()
    {

        PhpFrame *stack = nullptr;
        std::stack<PhpFrame> slots;

        auto i = COUNT;
        auto d = DEPTH;
        bool f = true;
        while (i-- > 0) {
            if (f)
            {
                slots.emplace(ex, fn_wrap, stack);
                stack = &slots.top();
            }
            else
            {
                stack = stack != nullptr ? stack->prev() : nullptr;
                slots.pop();
            }
            if (--d <= 1) {
                d = DEPTH;
                f = !f;
            }
        }

        while (!slots.empty())
        {
            slots.pop();
        }

    }, "\n*** Using linked list with depth {} and {} iterations\n\n", DEPTH, COUNT);

    return 0;
}
