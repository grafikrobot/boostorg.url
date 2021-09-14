//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/url
//

// Test that header file is self-contained.
#include <boost/url/rfc/hier_part_bnf.hpp>

#include <boost/url/detail/test/test_suite.hpp>
#include "test_bnf.hpp"

namespace boost {
namespace urls {

class hier_part_bnf_test
{
public:
    void
    run()
    {
        using T = hier_part_bnf;

        good<T>("");
        good<T>("/");
        good<T>("//");
        good<T>("//user:pass@");
        good<T>("//boost.org");
        good<T>("//1.2.3.4:8080");
        good<T>("//1.2.3.4:8080/");
        good<T>("//1.2.3.4:8080/x");
        good<T>("//1.2.3.4:8080/x/");
        good<T>("//1.2.3.4:8080////");
        good<T>("/x");
        good<T>("/x/");
        good<T>("/x/y");
        good<T>("/x/y//");
        good<T>("x");
        good<T>("x/");
        good<T>("x//");
        good<T>("x/y/z");
        good<T>("x//y///z///");
        good<T>(":/"); // colon ok in hier-part

        error_code ec;
        hier_part_bnf t;
        bnf::parse_string(
            "/1/2/3/4/5", ec, t);
        BOOST_TEST(t.path.path == "/1/2/3/4/5");
        BOOST_TEST(t.path.count == 5);
    }
};

TEST_SUITE(
    hier_part_bnf_test,
    "boost.url.hier_part_bnf");

} // urls
} // boost