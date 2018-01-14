macro(AddExample exampleName)
    add_executable(${exampleName} ${exampleName}.cpp)
    target_link_libraries(${exampleName} PUBLIC tmpl)
    target_compile_options(${exampleName} PUBLIC "-Wall")
endmacro()


AddExample(concepts)
AddExample(type_list_basics)
AddExample(value_list_basics)