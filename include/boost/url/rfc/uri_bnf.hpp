//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/url
//

#ifndef BOOST_URL_URI_BNF_HPP
#define BOOST_URL_URI_BNF_HPP

#include <boost/url/detail/config.hpp>
#include <boost/url/error.hpp>
#include <boost/url/optional.hpp>
#include <boost/url/bnf/range.hpp>
#include <boost/url/rfc/authority_bnf.hpp>
#include <boost/url/rfc/pct_encoded_bnf.hpp>
#include <boost/url/rfc/query_bnf.hpp>
#include <boost/url/rfc/scheme_bnf.hpp>

namespace boost {
namespace urls {

/** BNF for URI

    @par BNF
    @code
    URI           = scheme ":" hier-part [ "?" query ] [ "#" fragment ]
    @endcode

    @see
        https://datatracker.ietf.org/doc/html/rfc3986#section-3
*/
struct uri_bnf
{
    scheme_bnf scheme;
    bnf::range<pct_encoded_str> path;
    optional<authority_bnf> authority;
    optional<bnf::range<query_param>> query;
    optional<pct_encoded_str> fragment;

    BOOST_URL_DECL
    friend
    bool
    parse(
        char const*& it,
        char const* const end,
        error_code& ec,
        uri_bnf& t);
};

} // urls
} // boost

#endif