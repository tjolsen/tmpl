macro(AddExample exampleName)
    add_executable(${exampleName} ${exampleName}.cpp)
    target_link_libraries(${exampleName} PUBLIC tmpl)
endmacro()


AddExample(concepts)
AddExample(type_list_basics)