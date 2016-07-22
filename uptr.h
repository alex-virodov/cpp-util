/*
* Copyright (C) 2015 Alexandr Virodov
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef __PTR_H__
#define __PTR_H__

#include <memory>

// ====================================================================
template <class T> 
using uptr = std::unique_ptr<T>;

// ====================================================================
template <class T>
uptr<T> make_uptr(T*&& raw) { return uptr<T>(raw); }

// ====================================================================
template <class T>
struct EmptyDeleteForUref
{
public:
    void operator()(T* ptr) {};
};

// ====================================================================
template <class T>
class uref : public std::unique_ptr<T, EmptyDeleteForUref<T>>
{
    template <class U> 
    friend class uref;

public:
    uref(nullptr_t) : unique_ptr(nullptr) {};

    uref(const uref&    other) : unique_ptr(other.get()) {};
    uref(const uptr<T>& other) : unique_ptr(other.get()) {};
    
    // forbid uref from creating from pointers directly - immediate leak
    uref(T* raw) = delete;

    // forbid uref from uptr rvalue - you probably want uptr instead of uref
    // otherwise immediate pointer-to-deleted-object
    uref(const uptr<T>&& other) = delete;

	template<class U, class = typename enable_if<is_convertible<U*, T*>::value, void>::type>
    uref(const uref<U>& other) : unique_ptr(other.get())
    {
    }

	template<class U, class = typename enable_if<is_convertible<U*, T*>::value, void>::type>
    uref& operator=(const uref<U>& other)
    {
        _Myptr = other.get();
    }
};

// ====================================================================
template <class T>
uref<T> make_uref_to_variable(T& raw) { auto ref = uref<T>(nullptr); ref.reset(&raw); return ref; }

#endif