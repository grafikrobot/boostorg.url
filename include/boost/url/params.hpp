//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/url
//

#ifndef BOOST_URL_PARAMS_HPP
#define BOOST_URL_PARAMS_HPP

#include <boost/url/detail/config.hpp>
#include <boost/url/string.hpp>
#include <boost/url/detail/parts_base.hpp>
#include <initializer_list>
#include <iterator>
#include <type_traits>

namespace boost {
namespace urls {

#ifndef BOOST_URL_DOCS
class url;
#endif

class params
    : private detail::parts_base
{
    friend class url;

    url* u_ = nullptr;
    string_value::allocator a_;

    template<class Allocator>
    params(
        url& u,
        Allocator const& a) noexcept
        : u_(&u)
        , a_(a)
    {
    }

public:
    class iterator;

    class reference
    {
        friend class params;
        friend class iterator;

        BOOST_URL_DECL
        reference(
            char const* s,
            std::size_t nk,
            std::size_t nv,
            string_value::allocator a);

    public:
        string_value key;
        string_value value;
        bool has_value;
    };

    using const_reference =
        reference;

    struct value_type
    {
        string_view key;
        string_view value;
        bool has_value;

    #ifdef BOOST_NO_CXX14_AGGREGATE_NSDMI
        constexpr
        value_type(
            string_view key_ = {},
            string_view value_ = {},
            bool has_value_ = false ) noexcept
            : key(key_)
            , value(value_)
            , has_value(has_value_)
        {
        }
    #endif
    };

    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    //--------------------------------------------
    //
    // Members
    //
    //--------------------------------------------

    params&
    operator=(std::initializer_list<
        value_type> init)
    {
        assign(init);
        return *this;
    }

    void
    assign(std::initializer_list<
        value_type> init)
    {
        assign(init.begin(), init.end());
    }

    template<class FwdIt>
    void
    assign(FwdIt first, FwdIt last)
    {
        assign(first, last,
            typename std::iterator_traits<
                FwdIt>::iterator_category{});
    }

private:
    template<class FwdIt>
    void
    assign(FwdIt first, FwdIt last,
        std::forward_iterator_tag);

    template<class FwdIt>
    void
    assign(FwdIt first, FwdIt last,
        std::input_iterator_tag) = delete;
public:

    //--------------------------------------------
    //
    // Element Access
    //
    //--------------------------------------------

    inline
    reference
    at(std::size_t pos) const;

    BOOST_URL_DECL
    reference
    operator[](
        std::size_t pos) const;

    inline
    reference
    front() const;

    inline
    reference
    back() const;

    //--------------------------------------------
    //
    // Iterators
    //
    //--------------------------------------------

    inline
    iterator
    begin() const noexcept;

    inline
    iterator
    end() const noexcept;

    //--------------------------------------------
    //
    // Capacity
    //
    //--------------------------------------------

    bool
    empty() const noexcept
    {
        return size() == 0;
    }

    inline
    std::size_t
    size() const noexcept;

    //--------------------------------------------
    //
    // Modifiers
    //
    //--------------------------------------------

    inline
    void
    clear() noexcept;

    //--------------------------------------------

    inline
    iterator
    insert(
        iterator before,
        value_type const& v);

    inline
    iterator
    insert(
        iterator before,
        std::initializer_list<
            value_type> init);

    template<class FwdIt>
    iterator
    insert(
        iterator before,
        FwdIt first,
        FwdIt last);

private:
    template<class FwdIt>
    iterator
    insert(
        iterator before,
        FwdIt first,
        FwdIt last,
        std::forward_iterator_tag);

    template<class FwdIt>
    iterator
    insert(
        iterator before,
        FwdIt first,
        FwdIt last,
        std::input_iterator_tag) = delete;
public:

    //--------------------------------------------

    inline
    iterator
    replace(
        iterator pos,
        value_type const& value);

    template<class FwdIt>
    iterator
    replace(
        iterator from,
        iterator to,
        FwdIt first,
        FwdIt last);

    inline
    iterator
    replace(
        iterator from,
        iterator to,
        std::initializer_list<
            value_type> init);

    inline
    iterator
    remove_value(
        iterator pos);

    inline
    iterator
    replace_value(
        iterator pos,
        string_view value);

    template<class Value>
#ifdef BOOST_URL_DOCS
    iterator
#else
    typename std::enable_if<
        is_stringlike<Value>::value,
        iterator>::type
#endif
    replace_value(
        iterator pos,
        Value const& value);

    //--------------------------------------------

    inline
    iterator
    emplace_at(
        iterator pos,
        string_view key,
        string_view value);

    template<
        class Key,
        class Value>
#ifdef BOOST_URL_DOCS
    iterator
#else
    typename std::enable_if<
        is_stringlike<Key>::value &&
        is_stringlike<Value>::value,
        iterator>::type
#endif
    emplace_at(
        iterator pos,
        Key const& key,
        Value const& value);

    inline
    iterator
    emplace_at(
        iterator pos,
        string_view key);

    template<
        class Key>
#ifdef BOOST_URL_DOCS
    iterator
#else
    typename std::enable_if<
        is_stringlike<Key>::value,
        iterator>::type
#endif
    emplace_at(
        iterator pos,
        Key const& key);

    inline
    iterator
    emplace_before(
        iterator before,
        string_view key,
        string_view value);

    template<
        class Key,
        class Value>
#ifdef BOOST_URL_DOCS
    iterator
#else
    typename std::enable_if<
        is_stringlike<Key>::value &&
        is_stringlike<Value>::value,
        iterator>::type
#endif
    emplace_before(
        iterator before,
        Key const& key,
        Value const& value);

    inline
    iterator
    emplace_before(
        iterator before,
        string_view key);

    template<class Key>
#ifdef BOOST_URL_DOCS
    iterator
#else
    typename std::enable_if<
        is_stringlike<Key>::value,
        iterator>::type
#endif
    emplace_before(
        iterator before,
        Key const& key);

    //--------------------------------------------

    inline
    iterator
    erase(iterator pos);

    inline
    iterator
    erase(
        iterator first,
        iterator last);

    BOOST_URL_DECL
    std::size_t
    erase(string_view key) noexcept;

    template<class Key>
#ifdef BOOST_URL_DOCS
    std::size_t
#else
    typename std::enable_if<
        is_stringlike<Key>::value,
        std::size_t>::type
#endif
    erase(Key const& key) noexcept
    {
        return erase(to_string_view(key));
    }

    //--------------------------------------------

    inline
    iterator
    emplace_back(
        string_view key,
        string_view value);

    template<
        class Key,
        class Value>
#ifdef BOOST_URL_DOCS
    iterator
#else
    typename std::enable_if<
        is_stringlike<Key>::value &&
        is_stringlike<Value>::value,
        iterator>::type
#endif
    emplace_back(
        Key const& key,
        Value const& value);

    template<class Key>
#ifdef BOOST_URL_DOCS
    iterator
#else
    typename std::enable_if<
        is_stringlike<Key>::value,
        iterator>::type
#endif
    emplace_back(
        Key const& key);

    inline
    void
    push_back(
        value_type const& value);

    inline
    void
    pop_back() noexcept;

    //--------------------------------------------
    //
    // Lookup
    //
    //--------------------------------------------

    BOOST_URL_DECL
    std::size_t
    count(string_view key) const noexcept;

    template<class Key>
#ifdef BOOST_URL_DOCS
    std::size_t
#else
    typename std::enable_if<
        is_stringlike<Key>::value,
        std::size_t>::type
#endif
    count(Key const& key) const noexcept
    {
        return count(to_string_view(key));
    }

    inline
    iterator
    find(string_view key) const noexcept;

    template<class Key>
#ifdef BOOST_URL_DOCS
    iterator
#else
    typename std::enable_if<
        is_stringlike<Key>::value,
        iterator>::type
#endif
    find(Key const& key) const noexcept;

    /** Search [from, end), from==end is valid
    */
    BOOST_URL_DECL
    iterator
    find(
        iterator from,
        string_view key) const noexcept;

    template<class Key>
#ifdef BOOST_URL_DOCS
    iterator
#else
    typename std::enable_if<
        is_stringlike<Key>::value,
        iterator>::type
#endif
    find(
        iterator from,
        Key const& key) const noexcept;

    inline
    bool
    contains(string_view key) const noexcept;

    template<class Key>
#ifdef BOOST_URL_DOCS
    bool
#else
    typename std::enable_if<
        is_stringlike<Key>::value,
        bool>::type
#endif
    contains(Key const& key) const noexcept
    {
        return count(to_string_view(key));
    }
};

} // urls
} // boost

// VFALCO This include is at the bottom of
// url.hpp because of a circular dependency
//#include <boost/url/impl/params.hpp>

#endif