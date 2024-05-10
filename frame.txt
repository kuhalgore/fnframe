#pragma once

#ifndef FRAME_H
#  define FRAME_H

#include <cstdint>
#include <memory>

constexpr std::size_t MAX_RESOURCES = 4;

struct zend_execute_data {
};
struct zval {
};

class PhpFunction {
public:
};

class PhpFrame {
public:

    PhpFrame() = delete;

    PhpFrame(zend_execute_data &ex, PhpFunction &fn_wrap, PhpFrame *prev)
        : _prev(prev)
        , _fn_wrap(fn_wrap)
        , _ex(&ex)
    {}

    /// Dtor
    ~PhpFrame() = default;

    /// Disabled copy operations
    PhpFrame(PhpFrame const &) = delete;
    PhpFrame & operator=(PhpFrame const &) = delete;

    /// Move operations
#if defined(VECTOR_TEST)
    PhpFrame(PhpFrame &&rhs) noexcept = default;
#else
    PhpFrame(PhpFrame &&rhs) = delete;
#endif
    PhpFrame & operator=(PhpFrame &&) = delete;

    auto *prev() const noexcept { return _prev; }

protected:

    PhpFrame *_prev = nullptr;

    struct {
        bool valid : 1;
        bool disable_optimization : 1;
        bool user_code : 1;
        bool zend_call_code : 1;
        bool zend_call_top : 1;
    } _flags{};

    PhpFunction &_fn_wrap;
    zend_execute_data *_ex = nullptr;
    uint32_t _lineno = 0;
    zval *_This_obj = nullptr;
    zval *_rval = nullptr;
    std::weak_ptr<void> _resources[MAX_RESOURCES];
    std::shared_ptr<void> _temp[MAX_RESOURCES];
};


#endif
