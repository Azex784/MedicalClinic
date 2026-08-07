#define BOOST_AUTO_TEST_MAIN //root of all tests suites and cases
#define BOOST_TEST_DYN_LINK //use shared boost library
#include <boost/test/unit_test.hpp>

using namespace boost::unit_test;

struct TestConfig {

    TestConfig() {
        expected_failures(0);
        timeout(1);
        tolerance(0.0001);
    }

    ~TestConfig() {
    }
};

BOOST_GLOBAL_FIXTURE(TestConfig);