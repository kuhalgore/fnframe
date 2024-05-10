#define VECTOR_TEST 1

#include "frame.h"
#include "ztime.h"
#include <stack>
#include <vector>

template<typename T, size_t N>
class Container
{

public:
    using value_type = T;
    using reference = T & ;
    using const_reference = T const &;
    using size_type = size_t;

    Container() : nSize(0)
    {
        ptrArr.reserve(100);
        ptrArr.emplace_back(static_cast<T*>(::operator new (sizeof(T[N]))));

    }

    ~Container()
    {
        for(auto&ptr: ptrArr)
        ::operator delete (ptr, sizeof(T[N]));
    }

    bool empty() const
    {
        return (nSize == 0);
    }

    size_t size() const
    {
        return nSize;
    }

    template <typename ...Args>
    void emplace_back(Args&&...args)
    {
        const auto& arrSize = ptrArr.size();
        if (nSize / N == arrSize) // time to add new bucket
        {
            std::cout << "adding bucket no " << arrSize + 1 << std::endl;

            ptrArr.emplace_back(static_cast<T*>(::operator new (sizeof(T[N]))));
        }

        new (ptrArr[nSize/N] + nSize%N ) T(std::forward<Args>(args)...);
        ++nSize;
    }

    void pop_back()
    {
        back().~T();
        --nSize;
    }

    reference back()
    {
        return ptrArr.back()[nSize%N];
    }
private:
    size_t nSize;
    std::vector<T*> ptrArr; //vector of buckets 
};

int main(int, char **)
{
    zend_execute_data ex;
    PhpFunction fn_wrap;

    constexpr size_t DEPTH = 400;
    constexpr size_t COUNT = 100'000'000;

    run_and_measure([&]()
    {

        PhpFrame *stack = nullptr;
        std::stack<PhpFrame, Container<PhpFrame, 40>> slots;

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
