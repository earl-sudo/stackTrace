# CMAKE 
# CMake may not be the worst language ever made but it wasn't for lack of effort!! I wish I didn't have
# to deal with this, but I do.

# cmake_minimum_required(VERSION <min>[...<policy_max>] [FATAL_ERROR])

cmake_minimum_required(VERSION 3.16)

# <help> defining "project"
# project(<PROJECT-NAME>
#        [VERSION <major>[.<minor>[.<patch>[.<tweak>]]]]
#        [DESCRIPTION <project-description-string>]
#        [HOMEPAGE_URL <url-string>]
#        [LANGUAGES <language-name>...])

project(stackTrace)

# <help> Setting langauge properties for "project"

set(CMAKE_CXX_STANDARD 20)

# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS ON)

# Add library to "project"
# add_library(<name> [STATIC | SHARED | MODULE]
#        [EXCLUDE_FROM_ALL]
#        [<source>...])
# EXAMPLE: add_library(BuiltElsewhere STATIC IMPORTED)
# <help> 
# target_compile_definitions(<target>
#        <INTERFACE|PUBLIC|PRIVATE> [items1...]
#        [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])
# EXAMPLE: target_compile_definitions(foo PUBLIC FOO)
# EXAMPLE: target_compile_definitions(foo PUBLIC -DFOO)  # -D removed
# EXAMPLE: target_compile_definitions(foo PUBLIC "" FOO) # "" ignored
# EXAMPLE: target_compile_definitions(foo PUBLIC -D FOO) # -D becomes "", then  ignored

# <help> set_target_properties(target1 target2 ...
#        PROPERTIES prop1 value1
#        prop2 value2 ...)
# EXAMPLE: set_target_properties(Foo PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED ON C_EXTENSIONS OFF)
# EXAMPLE: set_target_properties(BuiltElsewhere PROPERTIES IMPORTED_LOCATION /path/to/libSomething.a)


# $<CONFIG>
# CMAKE_<LANG>_FLAGS_<CONFIG>
# CMAKE_<TARGETTYPE>_LINKER_FLAGS_<CONFIG>
# EXAMPLE: set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall")
# EXAMPLE: set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# SETTING "target PROPERTIES 
# ================================================================

# add_executable(<name> [WIN32] [MACOSX_BUNDLE]
#               [EXCLUDE_FROM_ALL]
#               [source1] [source2 ...])
# add_executable(<name> IMPORTED [GLOBAL])
# add_executable(<name> ALIAS <target>)

add_executable(stackTrace main.cpp)

# <help> Add include path to "target"
# target_include_directories(<target> [SYSTEM] [AFTER|BEFORE]
#        <INTERFACE|PUBLIC|PRIVATE> [items1...]
#        [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])
# EXAMPLE: target_include_directories(myawesomelib PUBLIC include)

# <help> Add library to "target"
# target_include_directories(<target> [SYSTEM] [AFTER|BEFORE]
#        <INTERFACE|PUBLIC|PRIVATE> [items1...]
#        [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])
# EXAMPLE: target_link_libraries(myawesomecli PRIVATE myawesomelib)
# EXAMPLE: link_directories(/Users/User/Projects/libraries/libs)

# <help> apply option to all target files
# target_compile_options(<target> [BEFORE]
#        <INTERFACE|PUBLIC|PRIVATE> [items1...]
#        [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])
# EXAMPLE: target_compile_options(propertyTree PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>)
# EXAMPLE: target_compile_options(Foo PRIVATE -fno-exceptions)

# <help> target_compile_definitions(<target>
#        <INTERFACE|PUBLIC|PRIVATE> [items1...]
#        [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])
# EXAMPLE: target_compile_definitions(foo PUBLIC FOO)
# EXAMPLE: target_compile_definitions(foo PUBLIC -DFOO)  # -D removed
# EXAMPLE: target_compile_definitions(foo PUBLIC "" FOO) # "" ignored
# EXAMPLE: target_compile_definitions(foo PUBLIC -D FOO) # -D becomes "", then ignored

# <help> set_target_properties(target1 target2 ...
#        PROPERTIES prop1 value1
#        prop2 value2 ...)
# EXAMPLE: set_target_properties(Foo PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED ON C_EXTENSIONS OFF)
# EXAMPLE: set_target_properties(BuiltElsewhere PROPERTIES IMPORTED_LOCATION /path/to/libSomething.a)

# apply compile option to a file.
# EXAMPLE: set_property(SOURCE main.cpp APPEND PROPERTY COMPILE_OPTIONS -fno-exceptions)