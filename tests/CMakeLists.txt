set(SOURCE_FILES
        concepts.cpp
        list_creation.cpp
        value_list_functions.cpp
        value_list_math.cpp

        catch_main.cpp
        catch.hpp
        )


add_executable(unittests ${SOURCE_FILES})
target_link_libraries(unittests PUBLIC tmpl)