/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * libbitcoin is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <boost/test/unit_test.hpp>

#include <bitcoin/bitcoin.hpp>

using namespace bc;

BOOST_AUTO_TEST_SUITE(pid_lock_tests)

BOOST_AUTO_TEST_CASE(pid_lock__duplicate_locks)
{
    pid_lock main("application-name");
    BOOST_REQUIRE(!main.is_locked());
    BOOST_REQUIRE(main.lock());
    BOOST_REQUIRE(main.is_locked());
    std::thread thread(
        []()
        {
            pid_lock duplicate("application-name");
            BOOST_REQUIRE(duplicate.is_locked());
            BOOST_REQUIRE(!duplicate.lock());
        });
    thread.join();
    BOOST_REQUIRE(main.unlock());
}

BOOST_AUTO_TEST_SUITE_END()

