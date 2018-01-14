set(SOURCE_FILES
        concepts.cpp
        list_creation.cpp


        catch_main.cpp
        catch.hpp
        )


add_executable(unittests ${SOURCE_FILES})
target_link_libraries(unittests PUBLIC tmpl)