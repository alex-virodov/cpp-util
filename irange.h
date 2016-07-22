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

#ifndef __IRANGE_H__
#define __IRANGE_H__

#include <vector>

class irange
{
    int m_start;
    int m_end;
public:
    class iter
    {
        int i;
    public:
        iter(int i) : i(i) {}
        int operator*() { return i; }
        void operator++() { i++; }
        bool operator!=(const iter& other) { return this->i != other.i; }

    };

    irange(int zero_to) : m_start(0), m_end(zero_to) {}
    irange(int from, int to) : m_start(from), m_end(to) {}

    irange(unsigned int zero_to) : m_start(0), m_end(zero_to) {}

    template<class T>
    irange(const std::vector<T>& vec) : m_start(0), m_end(vec.size()) {}

    template <class T>
    irange(const T& iterable) : m_start(0), m_end(iterable.cend() - iterable.cbegin()) {};

    template <class T>
    irange(T& iterable) : m_start(0), m_end(iterable.end() - iterable.begin()) {};

    iter begin() { return m_start; }
    iter end()   { return m_end; }
};

#endif