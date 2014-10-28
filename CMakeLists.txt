cmake_minimum_required (VERSION 2.6)

project (omni)

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
target_link_libraries (omni-core ${Boost_LIBRARIES})

execute_process(COMMAND "llvm-config-3.6" --includedir OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE LLVM_INCLUDE_DIRS)
execute_process(COMMAND "llvm-config-3.6" --cxxflags OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE LLVM_CXXFLAGS)

include_directories (${LLVM_INCLUDE_DIRS})
target_link_libraries(omni-core 
/usr/lib/llvm-3.6/lib/libLLVMLTO.a
/usr/lib/llvm-3.6/lib/libLLVMObjCARCOpts.a
/usr/lib/llvm-3.6/lib/libLLVMLinker.a
/usr/lib/llvm-3.6/lib/libLLVMipo.a
/usr/lib/llvm-3.6/lib/libLLVMVectorize.a
/usr/lib/llvm-3.6/lib/libLLVMBitWriter.a
/usr/lib/llvm-3.6/lib/libLLVMIRReader.a
/usr/lib/llvm-3.6/lib/libLLVMBitReader.a
/usr/lib/llvm-3.6/lib/libLLVMAsmParser.a
/usr/lib/llvm-3.6/lib/libLLVMR600CodeGen.a
/usr/lib/llvm-3.6/lib/libLLVMR600Desc.a
/usr/lib/llvm-3.6/lib/libLLVMR600Info.a
/usr/lib/llvm-3.6/lib/libLLVMR600AsmPrinter.a
/usr/lib/llvm-3.6/lib/libLLVMSystemZDisassembler.a
/usr/lib/llvm-3.6/lib/libLLVMSystemZCodeGen.a
/usr/lib/llvm-3.6/lib/libLLVMSystemZAsmParser.a
/usr/lib/llvm-3.6/lib/libLLVMSystemZDesc.a
/usr/lib/llvm-3.6/lib/libLLVMSystemZInfo.a
/usr/lib/llvm-3.6/lib/libLLVMSystemZAsmPrinter.a
/usr/lib/llvm-3.6/lib/libLLVMNVPTXCodeGen.a
/usr/lib/llvm-3.6/lib/libLLVMNVPTXDesc.a
/usr/lib/llvm-3.6/lib/libLLVMNVPTXInfo.a
/usr/lib/llvm-3.6/lib/libLLVMNVPTXAsmPrinter.a
/usr/lib/llvm-3.6/lib/libLLVMCppBackendCodeGen.a
/usr/lib/llvm-3.6/lib/libLLVMCppBackendInfo.a
/usr/lib/llvm-3.6/lib/libLLVMMSP430CodeGen.a
/usr/lib/llvm-3.6/lib/libLLVMMSP430Desc.a
/usr/lib/llvm-3.6/lib/libLLVMMSP430Info.a
/usr/lib/llvm-3.6/lib/libLLVMMSP430AsmPrinter.a
/usr/lib/llvm-3.6/lib/libLLVMXCoreDisassembler.a
/usr/lib/llvm-3.6/lib/libLLVMXCoreCodeGen.a
/usr/lib/llvm-3.6/lib/libLLVMXCoreDesc.a
/usr/lib/llvm-3.6/lib/libLLVMXCoreInfo.a
/usr/lib/llvm-3.6/lib/libLLVMXCoreAsmPrinter.a
/usr/lib/llvm-3.6/lib/libLLVMMipsDisassembler.a
/usr/lib/llvm-3.6/lib/libLLVMMipsCodeGen.a
/usr/lib/llvm-3.6/lib/libLLVMMipsAsmParser.a
/usr/lib/llvm-3.6/lib/libLLVMMipsDesc.a
/usr/lib/llvm-3.6/lib/libLLVMMipsInfo.a
/usr/lib/llvm-3.6/lib/libLLVMMipsAsmPrinter.a
/usr/lib/llvm-3.6/lib/libLLVMARMDisassembler.a
/usr/lib/llvm-3.6/lib/libLLVMARMCodeGen.a
/usr/lib/llvm-3.6/lib/libLLVMARMAsmParser.a
/usr/lib/llvm-3.6/lib/libLLVMARMDesc.a
/usr/lib/llvm-3.6/lib/libLLVMARMInfo.a
/usr/lib/llvm-3.6/lib/libLLVMARMAsmPrinter.a
/usr/lib/llvm-3.6/lib/libLLVMAArch64Disassembler.a
/usr/lib/llvm-3.6/lib/libLLVMAArch64CodeGen.a
/usr/lib/llvm-3.6/lib/libLLVMAArch64AsmParser.a
/usr/lib/llvm-3.6/lib/libLLVMAArch64Desc.a
/usr/lib/llvm-3.6/lib/libLLVMAArch64Info.a
/usr/lib/llvm-3.6/lib/libLLVMAArch64AsmPrinter.a
/usr/lib/llvm-3.6/lib/libLLVMAArch64Utils.a
/usr/lib/llvm-3.6/lib/libLLVMPowerPCDisassembler.a
/usr/lib/llvm-3.6/lib/libLLVMPowerPCCodeGen.a
/usr/lib/llvm-3.6/lib/libLLVMPowerPCAsmParser.a
/usr/lib/llvm-3.6/lib/libLLVMPowerPCDesc.a
/usr/lib/llvm-3.6/lib/libLLVMPowerPCInfo.a
/usr/lib/llvm-3.6/lib/libLLVMPowerPCAsmPrinter.a
/usr/lib/llvm-3.6/lib/libLLVMSparcDisassembler.a
/usr/lib/llvm-3.6/lib/libLLVMSparcCodeGen.a
/usr/lib/llvm-3.6/lib/libLLVMSparcAsmParser.a
/usr/lib/llvm-3.6/lib/libLLVMSparcDesc.a
/usr/lib/llvm-3.6/lib/libLLVMSparcInfo.a
/usr/lib/llvm-3.6/lib/libLLVMSparcAsmPrinter.a
/usr/lib/llvm-3.6/lib/libLLVMTableGen.a
/usr/lib/llvm-3.6/lib/libLLVMDebugInfo.a
/usr/lib/llvm-3.6/lib/libLLVMOption.a
/usr/lib/llvm-3.6/lib/libLLVMX86Disassembler.a
/usr/lib/llvm-3.6/lib/libLLVMX86AsmParser.a
/usr/lib/llvm-3.6/lib/libLLVMX86CodeGen.a
/usr/lib/llvm-3.6/lib/libLLVMSelectionDAG.a
/usr/lib/llvm-3.6/lib/libLLVMAsmPrinter.a
/usr/lib/llvm-3.6/lib/libLLVMMCParser.a
/usr/lib/llvm-3.6/lib/libLLVMX86Desc.a
/usr/lib/llvm-3.6/lib/libLLVMX86Info.a
/usr/lib/llvm-3.6/lib/libLLVMX86AsmPrinter.a
/usr/lib/llvm-3.6/lib/libLLVMX86Utils.a
/usr/lib/llvm-3.6/lib/libLLVMLineEditor.a
/usr/lib/llvm-3.6/lib/libLLVMMCDisassembler.a
/usr/lib/llvm-3.6/lib/libLLVMInstrumentation.a
/usr/lib/llvm-3.6/lib/libLLVMInterpreter.a
/usr/lib/llvm-3.6/lib/libLLVMCodeGen.a
/usr/lib/llvm-3.6/lib/libLLVMScalarOpts.a
/usr/lib/llvm-3.6/lib/libLLVMInstCombine.a
/usr/lib/llvm-3.6/lib/libLLVMTransformUtils.a
/usr/lib/llvm-3.6/lib/libLLVMipa.a
/usr/lib/llvm-3.6/lib/libLLVMAnalysis.a
/usr/lib/llvm-3.6/lib/libLLVMTarget.a
/usr/lib/llvm-3.6/lib/libLLVMRuntimeDyld.a
/usr/lib/llvm-3.6/lib/libLLVMExecutionEngine.a
/usr/lib/llvm-3.6/lib/libLLVMMC.a
/usr/lib/llvm-3.6/lib/libLLVMObject.a
/usr/lib/llvm-3.6/lib/libLLVMCore.a
/usr/lib/llvm-3.6/lib/libLLVMSupport.a
/usr/lib/llvm-3.6/lib/libllvm_Hexagon.a
/usr/lib/llvm-3.6/lib/libLLVMHexagonCodeGen.a
/usr/lib/llvm-3.6/lib/libLLVMHexagonDesc.a
/usr/lib/llvm-3.6/lib/libLLVMHexagonDisassembler.a
/usr/lib/llvm-3.6/lib/libLLVMHexagonInfo.a
-lz
-lpthread
-lncurses
-ldl
-lboost_filesystem
-lboost_system
)

set(CMAKE_CXX_FLAGS "-std=c++11 ${LLVM_CXXFLAGS} -fexceptions")

add_library (omni-runtime SHARED
    source/omni/runtime/memory.cpp)

target_link_libraries (omni-runtime ${Boost_LIBRARIES})

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

target_link_libraries (omni-tests omni-core omni-runtime ${Boost_LIBRARIES})

