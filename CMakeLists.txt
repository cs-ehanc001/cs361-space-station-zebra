cmake_minimum_required(VERSION 3.22)

set(PROJECT space-station-zebra)
project(${PROJECT})

file(GLOB_RECURSE SOURCE src/*.cpp)
list(REMOVE_ITEM SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)


if( CMAKE_COMPILER_IS_GNUCC )
    # So many warnings
    add_compile_options(-Wall -Wextra -pedantic -Wcast-align -Wcast-qual -Wredundant-decls -Wconversion -Wnon-virtual-dtor -Wunused -Wdouble-promotion -Wformat=2 -Wnull-dereference -Wimplicit-fallthrough -Wuninitialized -Wstrict-overflow=4 -Wold-style-cast -Wfloat-equal -Wundef -Wshadow -Wfree-nonheap-object -Wsign-conversion -Wno-multichar -Woverloaded-virtual -Wctor-dtor-privacy -Wsign-promo -Wmisleading-indentation -Wzero-as-null-pointer-constant -Wsuggest-override -Weffc++ -Wno-error=effc++ -Werror)
    set(SANITIZERS -fsanitize=address -fsanitize=leak -fsanitize=undefined)
    add_compile_options(${SANITIZERS})
    add_link_options(${SANITIZERS})

    add_compile_options(-O0)
endif()
if ( MSVC )
    # I have no access to testing MSVC compilation
endif()


include_directories(inc)
add_executable(${PROJECT} "src/main.cpp" ${SOURCE})


file(GLOB_RECURSE TEST "tst/src/*.cpp")

add_executable(run_tests ${SOURCE} ${TEST})
target_include_directories(run_tests PRIVATE tst/inc)

set_property(TARGET ${PROJECT} PROPERTY CXX_STANDARD 17)
set_property(TARGET run_tests PROPERTY CXX_STANDARD 17)
