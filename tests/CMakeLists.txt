set(SOURCE_FILES
        concepts.cpp
        list_creation.cpp
        list_find.cpp
        type_list_functions.cpp
        value_list_functions.cpp
        value_list_math.cpp

        catch_main.cpp
        catch.hpp
        )


add_executable(unittests ${SOURCE_FILES})
target_link_libraries(unittests PUBLIC tmpl)