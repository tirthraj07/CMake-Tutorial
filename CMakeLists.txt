cmake_minimum_required(VERSION 3.15)

project(HttpWebClient VERSION 1.0
                      DESCRIPTION "Simple HTTP Project"
                      LANGUAGES CXX)


find_package(cpprestsdk REQUIRED)
find_package(OpenSSL REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE cpprestsdk::cpprest OpenSSL::SSL OpenSSL::Crypto)
