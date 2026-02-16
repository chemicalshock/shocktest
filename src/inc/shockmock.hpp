// -------------------------------------------------------------
//
//!\file shockmock.hpp
//!\brief Provides mocking support for the shocktest framework.
//!\author Colin J.D. Stewart
//
// -------------------------------------------------------------
//
//            Copyright (c) 2025-2026. OverHertz Ltd.
//                   All rights reserved
//
// -------------------------------------------------------------

#ifndef SHOCKMOCK_HPP
#define SHOCKMOCK_HPP

namespace shockmock {

    // !\brief RAII helper for temporarily overriding a function pointer.
    // When an instance is created, it saves the original value of the target function pointer and then
    // sets it to the new implementation. On scope exit, it automatically restores the original value.
    template<typename T>
    class AutoMockGuard {
    public:
        AutoMockGuard(T& target_ptr, T new_impl)
            : target(target_ptr), original(target_ptr)
        {
            target = new_impl;
        }
        ~AutoMockGuard() {
            target = original;
        }
        AutoMockGuard(const AutoMockGuard&) = delete;
        AutoMockGuard& operator=(const AutoMockGuard&) = delete;
    private:
        T& target;   //!< Reference to the function pointer to override.
        T  original; //!< The original function pointer.
    };

} // namespace shockmock

#define SHOCKMOCK_CONCAT_INNER(a, b) a##b
#define SHOCKMOCK_CONCAT(a, b) SHOCKMOCK_CONCAT_INNER(a, b)

// !\brief Declares a mockable global function pointer for a given function.
// Usage example:
//     SHOCKMOCK_DECLARE_MOCK(parse_expression, 
//                            FRACTURE::ASTNode (*)(const std::vector<FRACTURE::Token>&, size_t&), 
//                            FRACTURE::parse_expression);
#define SHOCKMOCK_DECLARE_MOCK(fn, fn_type, real_impl) \
    namespace shockmock { \
        fn_type fn##_mock_ptr = real_impl; \
    }

// !\brief Overrides a mockable function pointer for the duration of a scope.
// Usage example:
//     SHOCKMOCK_MOCK_OVERRIDE(parse_expression, my_mock_parse_expression);
#define SHOCKMOCK_MOCK_OVERRIDE(fn, new_impl) \
    shockmock::AutoMockGuard<decltype(shockmock::fn##_mock_ptr)> SHOCKMOCK_CONCAT(_autoMockGuard_##fn##_, __COUNTER__)(shockmock::fn##_mock_ptr, new_impl)

// !\brief Calls the mockable function pointer.
// Usage example:
//     auto result = SHOCKMOCK_CALL(parse_expression, tokens, index);
#define SHOCKMOCK_CALL(fn, ...) shockmock::fn##_mock_ptr(__VA_ARGS__)

#endif // SHOCKMOCK_HPP
