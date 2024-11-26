/*
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "main.cpp"
#include <sstream>

TEST_CASE("Test Case 1: Based on Assignment Example") {
std::stringstream input("7 2\ngoogle.com gmail.com\nfacebook.com ufl.edu\nufl.edu maps.com\ngmail.com maps.com\nmaps.com ufl.edu\ngoogle.com gmail.com\nfacebook.com maps.com\n");
auto cin_buffer = std::cin.rdbuf(input.rdbuf());
main();
std::cin.rdbuf(cin_buffer);
}

TEST_CASE("Test Case 2: Simple Three URL Cycle") {
std::stringstream input("3 2\nsite1.com site2.com\nsite2.com site3.com\nsite3.com site1.com\n");
auto cin_buffer = std::cin.rdbuf(input.rdbuf());
main();
std::cin.rdbuf(cin_buffer);
}

TEST_CASE("Test Case 3: Star Configuration") {
std::stringstream input("4 3\ncentral.com page1.com\ncentral.com page2.com\ncentral.com page3.com\npage1.com central.com\n");
auto cin_buffer = std::cin.rdbuf(input.rdbuf());
main();
std::cin.rdbuf(cin_buffer);
}

TEST_CASE("Test Case 4: Multiple Power Iterations") {
std::stringstream input("6 5\nsite1.com site2.com\nsite2.com site3.com\nsite3.com site4.com\nsite4.com site1.com\nsite1.com site3.com\nsite2.com site4.com\n");
auto cin_buffer = std::cin.rdbuf(input.rdbuf());
main();
std::cin.rdbuf(cin_buffer);
}

TEST_CASE("Test Case 5: Complex Web Structure") {
std::stringstream input("8 4\nmain.com blog.com\nblog.com shop.com\nshop.com main.com\nmain.com news.com\nnews.com blog.com\nblog.com main.com\nshop.com news.com\nnews.com main.com\n");
auto cin_buffer = std::cin.rdbuf(input.rdbuf());
main();
std::cin.rdbuf(cin_buffer);
}*/