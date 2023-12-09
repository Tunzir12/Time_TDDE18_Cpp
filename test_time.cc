#include "catch.hpp"
#include "Time.h"


TEST_CASE("Constructor") {
    Time t1{10, 30, 15};
    CHECK(t1.hours == 10);
    CHECK(t1.minutes == 30);
    CHECK(t1.seconds == 15);
}

TEST_CASE("isValid function") {
    Time t1{10, 30, 15};
    CHECK(isValid(t1) == true);

    Time t2{24, 0, 0};
    REQUIRE(isValid(t2) == false);

    Time t3{8,80,58};
    CHECK(isValid(t3)==false);

    Time t4{13,15,90};
    CHECK(isValid(t4)==false);
}

TEST_CASE("toString function") {
    Time t1{10, 30, 15};
    CHECK(toString(t1) == "10:30:15");
    REQUIRE(toString(t1, false) == "10:30:15 AM");

    Time t2{18, 45, 0};
    CHECK(toString(t2) == "18:45:00");
    REQUIRE(toString(t2, false) == "06:45:00 PM");
}

TEST_CASE("isAM function") {
    Time t1{12, 00, 00};
    CHECK(isAM(t1) == false);

    Time t2{8, 15, 00};
    CHECK(isAM(t2) == true);

}
TEST_CASE("Arithmetic operators") {
    Time t1{12, 30, 45};
    Time t2 = t1 + 60;
    Time t3 = t1 - 30;
    CHECK(t2 == Time{12, 31, 45});
    CHECK(t3 == Time{12, 30, 15});

    Time t4 = t1 + 100;
    CHECK(t4==Time{12,32,25});

     Time t5 = t1 + (86400 * 3);

    CHECK(t5==Time{12,30,45});

    Time t6 = t1 - (86400*3);

    CHECK(t6==Time{12,30,45});
}

TEST_CASE("Increment and Decrement operators") {
    
    Time t1{10, 30, 15};

    ++t1;
    REQUIRE(t1.hours == 10);
    REQUIRE(t1.minutes == 30);
    REQUIRE(t1.seconds == 16);

    Time t2 = t1++;
    REQUIRE(t2.hours == 10);
    REQUIRE(t2.minutes == 30);
    REQUIRE(t2.seconds == 16);
    REQUIRE(t1.hours == 10);
    REQUIRE(t1.minutes == 30);
    REQUIRE(t1.seconds == 17);

    --t1;
    REQUIRE(t1.hours == 10);
    REQUIRE(t1.minutes == 30);
    REQUIRE(t1.seconds == 16);

    Time t3 = t1--;
    REQUIRE(t3.hours == 10);
    REQUIRE(t3.minutes == 30);
    REQUIRE(t3.seconds == 16);
    REQUIRE(t1.hours == 10);
    REQUIRE(t1.minutes == 30);
    REQUIRE(t1.seconds == 15);
}

TEST_CASE("Comparison operators") {
    Time t1{10, 30, 15};
    Time t2{9, 45, 0};

    REQUIRE(t1 == t1);
    REQUIRE(t1 != t2);
    CHECK_FALSE(t1 < t2);
    REQUIRE(t1 > t2);
    REQUIRE(t1 <= t1);
    CHECK_FALSE(t1 <= t2);
    REQUIRE(t1 >= t1);
    REQUIRE(t1 >= t2);
    CHECK_FALSE(t2 >= t1);
}

TEST_CASE("Stream operators") {
    Time t1{10, 30, 15};
    std::ostringstream oss;
    oss << t1;
    REQUIRE(oss.str() == "10:30:15");

    Time t2;
    std::istringstream iss("08:45:30");
    iss >> t2;
    REQUIRE(t2.hours == 8);
    REQUIRE(t2.minutes == 45);
    REQUIRE(t2.seconds == 30);

    Time t3;
    std::istringstream iss_invalid("99:99:99");
    iss_invalid>>t3;

    REQUIRE(iss_invalid.fail());
    CHECK(t3.hours == 0);
    CHECK(t3.minutes == 0);
    CHECK(t3.seconds == 0);

    Time t4;
    std::istringstream iss_no_colon("123456"); // Missing colons
    iss_no_colon >> t3;
    REQUIRE(iss_no_colon.fail());


}
