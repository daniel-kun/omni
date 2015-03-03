cmake_minimum_required (VERSION 2.8.11)

project (omni)

set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "") # To suppress -rdynamic, which causes problems on linux with OpenGL-drivers that use llvm-3.4

add_compile_options(-std=c++1y)
set(CMAKE_CXX_FLAGS "-std=c++1y")

include_directories ("${PROJECT_SOURCE_DIR}/interface/")

add_library (omni-core SHARED
    source/omni/core/already_exists_error.cpp
    source/omni/core/context.cpp
    source/omni/core/domain.cpp
    source/omni/core/id.cpp
    source/omni/core/logic_error.cpp
    source/omni/core/module_emit_options.cpp
    source/omni/core/no_context_error.cpp
    source/omni/core/not_implemented_error.cpp
    source/omni/core/runtime.cpp
    source/omni/core/statement_emit_result.cpp
    source/omni/core/verification_failed_eror.cpp
    source/omni/core/invalid_argument_error.cpp
    source/omni/core/parser.cpp
    source/omni/core/model/binary_operator_expression.cpp
    source/omni/core/model/bitcast_expression.cpp
    source/omni/core/model/block.cpp
    source/omni/core/model/builtin_literal_expression.cpp
    source/omni/core/model/cast_expression.cpp
    source/omni/core/model/do_while_statement.cpp
    source/omni/core/model/entity.cpp
    source/omni/core/model/expression.cpp
    source/omni/core/model/external_function.cpp
    source/omni/core/model/function.cpp
    source/omni/core/model/function_call_expression.cpp
    source/omni/core/model/function_prototype.cpp
    source/omni/core/model/if_statement.cpp
    source/omni/core/model/literal_expression.cpp
    source/omni/core/model/meta_info.cpp
    source/omni/core/model/meta_info_extension.cpp
    source/omni/core/model/modifying_expression.cpp
    source/omni/core/model/module.cpp
    source/omni/core/model/native_type_to_type_class.cpp
    source/omni/core/model/parameter.cpp
    source/omni/core/model/pure_expression.cpp
    source/omni/core/model/return_statement.cpp
    source/omni/core/model/scope.cpp
    source/omni/core/model/statement.cpp
    source/omni/core/model/type.cpp
    source/omni/core/model/type_class.cpp
    source/omni/core/model/type_mismatch_error.cpp
    source/omni/core/model/use_before_declaration_error.cpp
    source/omni/core/model/variable_assignment_expression.cpp
    source/omni/core/model/variable_declaration_expression.cpp
    source/omni/core/model/variable_expression.cpp
    source/omni/core/model/while_statement.cpp
    source/omni/core/tools/string.cpp
    source/omni/core/input/abstract_syntax_element.cpp
    source/omni/core/input/concrete_syntax_element.cpp
    source/omni/core/input/fixed_template_element.cpp
    source/omni/core/input/input_state.cpp
    source/omni/core/input/regex_template_element.cpp
    source/omni/core/input/repeater_template_element.cpp
    source/omni/core/input/syntax_element.cpp
    source/omni/core/input/syntax_suggestion.cpp
    source/omni/core/input/syntax_template_element.cpp
    source/omni/core/input/syntax_tree_parser_xml.cpp
    source/omni/core/input/template_element.cpp
    source/omni/core/input/template_visitor.cpp
    source/omni/core/input/variable_template_element.cpp)

find_package (Boost 1.48 COMPONENTS system filesystem unit_test_framework REQUIRED)
include_directories (${Boost_INCLUDE_DIR})

execute_process(COMMAND "llvm-config-3.6" --includedir OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE LLVM_INCLUDE_DIRS)
execute_process(COMMAND "llvm-config-3.6" --cxxflags OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE LLVM_CXXFLAGS)
execute_process(COMMAND "llvm-config-3.6" --ldflags OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE LLVM_LDFLAGS)
execute_process(COMMAND "llvm-config-3.6" --libs OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE LLVM_LIBS)

include_directories (${LLVM_INCLUDE_DIRS})
target_link_libraries(omni-core 
${Boost_LIBRARIES}
${LLVM_LDFLAGS}
${LLVM_LIBS}
-lz
-lpthread
-lncurses
-ldl
-lstdc++
)

set(CMAKE_CXX_FLAGS "-std=c++1y ${LLVM_CXXFLAGS} -fexceptions")

add_library (omni-runtime SHARED
    source/omni/runtime/memory.cpp)

target_link_libraries (omni-runtime ${Boost_LIBRARIES} -lstdc++)

set(CMAKE_CXX_FLAGS "-std=c++1y")

add_executable (omni-tests
    source/omni/tests/test_file_manager.cpp
    source/omni/tests/test_llvm.cpp
    source/omni/tests/test_utils.cpp
    source/omni/tests/core/input/test_input_manager.cpp
    source/omni/tests/core/input/test_input_state.cpp
    source/omni/tests/core/input/test_syntax_tree_parser_xml.cpp
    source/omni/tests/core/input/test_utils_input.cpp
    source/omni/tests/core/model/test_binary_operator_expression.cpp
    source/omni/tests/core/model/test_block.cpp
    source/omni/tests/core/model/test_domain.cpp
    source/omni/tests/core/model/test_entity.cpp
    source/omni/tests/core/model/test_external_function.cpp
    source/omni/tests/core/model/test_function.cpp
    source/omni/tests/core/model/test_if_statement.cpp
    source/omni/tests/core/model/test_native_type_to_type_class.cpp
    source/omni/tests/core/model/test_variable.cpp
    source/omni/tests/core/model/test_while_statement.cpp
    source/omni/tests/core/test_context.cpp
    source/omni/tests/core/test_id.cpp
    source/omni/tests/core/test_runtime_memory.cpp
    source/omni/tests/runtime/test_memory.cpp
    source/omni/tests/core/tools/test_string.cpp
    source/omni/tests/core/model/test_bitcast_expression.cpp
    source/omni/tests/core/model/test_builtin_literal_expression.cpp
    source/omni/tests/core/model/test_cast_expression.cpp
    source/omni/tests/core/model/test_expression.cpp
    source/omni/tests/core/model/test_function_prototype.cpp
    source/omni/tests/core/model/test_literal_expression.cpp
    source/omni/tests/core/model/test_modifying_expression.cpp
    source/omni/tests/core/model/test_module.cpp
    source/omni/tests/core/model/test_parameter.cpp
    source/omni/tests/core/model/test_pure_expression.cpp
    source/omni/tests/core/model/test_return_statement.cpp
    source/omni/tests/core/model/test_scope.cpp
    source/omni/tests/core/model/test_statement.cpp
    source/omni/tests/core/model/test_type.cpp
    source/omni/tests/core/model/test_variable_declaration_expression.cpp
    source/omni/tests/core/model/test_variable_expression.cpp)

add_definitions (-DBOOST_TEST_DYN_LINK)

target_link_libraries (omni-tests omni-core omni-runtime ${Boost_LIBRARIES} -lstdc++)

set(CMAKE_AUTOMOC on)

find_package(Qt5Widgets REQUIRED)

include_directories(${Qt5Widgets_INCLUDE_DIRS})
add_definitions(${Qt5Widgets_DEFINITIONS})
set(CMAKE_CXX_FLAGS "-std=c++1y ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

add_library (omni-ui SHARED 
    interface/omni/ui/ui_meta_extension.hpp
    interface/omni/ui/blueprint.hpp
    interface/omni/ui/entity_placeholder_widget.hpp
    interface/omni/ui/syntax_input.hpp
    interface/omni/ui/ui.hpp
    interface/omni/ui/generic_entity_editor.hpp
    interface/omni/ui/suggestion_text_edit.hpp
    interface/omni/ui/entity_toggle_widget.hpp
    interface/omni/ui/entity_widget_provider_base.hpp
    interface/omni/ui/entity_widget_provider.hpp
    interface/omni/ui/flowlayout.hpp
    interface/omni/ui/entity_base_widget.hpp
    interface/omni/ui/init.hpp
    interface/omni/ui/literal_expression_view.hpp
    interface/omni/ui/suggestion_list_model.hpp
    interface/omni/ui/tree_sort_filter_proxy_model.hpp
    interface/omni/ui/variable_declaration_expression_view.hpp
    source/omni/ui/entity_widget_provider.cpp
    source/omni/ui/flowlayout.cpp
    source/omni/ui/syntax_input.cpp
    source/omni/ui/generic_entity_editor.cpp
    source/omni/ui/ui_meta_extension.cpp
    source/omni/ui/blueprint.cpp
    source/omni/ui/init.cpp
    source/omni/ui/variable_declaration_expression_view.cpp
    source/omni/ui/suggestion_list_model.cpp
    source/omni/ui/tree_sort_filter_proxy_model.cpp
    source/omni/ui/entity_placeholder_widget.cpp
    source/omni/ui/ui.cpp
    source/omni/ui/suggestion_text_edit.cpp
    source/omni/ui/entity_toggle_widget.cpp
    source/omni/ui/entity_base_widget.cpp
    source/omni/ui/literal_expression_view.cpp
)


target_link_libraries (omni-ui Qt5::Widgets -lstdc++)

set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "") # To suppress -rdynamic, which causes problems on linux with OpenGL-drivers that use llvm-3.4

add_executable (omni-forge
    source/omni/forge/sandbox_selector_model.hpp
    source/omni/forge/sandbox_widget.hpp
    source/omni/forge/main_window.hpp
    source/omni/forge/sandbox_selector.cpp
    source/omni/forge/sandbox_selector_model.cpp
    source/omni/forge/main_window.cpp
    source/omni/forge/main.cpp
    source/omni/forge/sandbox_selector.hpp
    source/omni/forge/sandbox_widget.cpp
)

target_link_libraries (omni-forge Qt5::Widgets omni-core omni-ui -lstdc++)

