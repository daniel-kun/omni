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

execute_process(COMMAND "llvm-config-3.5" --includedir OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE LLVM_INCLUDE_DIRS)
execute_process(COMMAND "llvm-config-3.5" --cxxflags OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE LLVM_CXXFLAGS)

include_directories (${LLVM_INCLUDE_DIRS})
target_link_libraries(omni-core 
/usr/lib/llvm-3.5/lib/libLLVMLTO.a
/usr/lib/llvm-3.5/lib/libLLVMObjCARCOpts.a
/usr/lib/llvm-3.5/lib/libLLVMLinker.a
/usr/lib/llvm-3.5/lib/libLLVMipo.a
/usr/lib/llvm-3.5/lib/libLLVMVectorize.a
/usr/lib/llvm-3.5/lib/libLLVMBitWriter.a
/usr/lib/llvm-3.5/lib/libLLVMIRReader.a
/usr/lib/llvm-3.5/lib/libLLVMBitReader.a
/usr/lib/llvm-3.5/lib/libLLVMAsmParser.a
/usr/lib/llvm-3.5/lib/libLLVMR600CodeGen.a
/usr/lib/llvm-3.5/lib/libLLVMR600Desc.a
/usr/lib/llvm-3.5/lib/libLLVMR600Info.a
/usr/lib/llvm-3.5/lib/libLLVMR600AsmPrinter.a
/usr/lib/llvm-3.5/lib/libLLVMSystemZDisassembler.a
/usr/lib/llvm-3.5/lib/libLLVMSystemZCodeGen.a
/usr/lib/llvm-3.5/lib/libLLVMSystemZAsmParser.a
/usr/lib/llvm-3.5/lib/libLLVMSystemZDesc.a
/usr/lib/llvm-3.5/lib/libLLVMSystemZInfo.a
/usr/lib/llvm-3.5/lib/libLLVMSystemZAsmPrinter.a
/usr/lib/llvm-3.5/lib/libLLVMHexagonCodeGen.a
/usr/lib/llvm-3.5/lib/libLLVMHexagonAsmPrinter.a
/usr/lib/llvm-3.5/lib/libLLVMHexagonDesc.a
/usr/lib/llvm-3.5/lib/libLLVMHexagonInfo.a
/usr/lib/llvm-3.5/lib/libLLVMNVPTXCodeGen.a
/usr/lib/llvm-3.5/lib/libLLVMNVPTXDesc.a
/usr/lib/llvm-3.5/lib/libLLVMNVPTXInfo.a
/usr/lib/llvm-3.5/lib/libLLVMNVPTXAsmPrinter.a
/usr/lib/llvm-3.5/lib/libLLVMCppBackendCodeGen.a
/usr/lib/llvm-3.5/lib/libLLVMCppBackendInfo.a
/usr/lib/llvm-3.5/lib/libLLVMMSP430CodeGen.a
/usr/lib/llvm-3.5/lib/libLLVMMSP430Desc.a
/usr/lib/llvm-3.5/lib/libLLVMMSP430Info.a
/usr/lib/llvm-3.5/lib/libLLVMMSP430AsmPrinter.a
/usr/lib/llvm-3.5/lib/libLLVMXCoreDisassembler.a
/usr/lib/llvm-3.5/lib/libLLVMXCoreCodeGen.a
/usr/lib/llvm-3.5/lib/libLLVMXCoreDesc.a
/usr/lib/llvm-3.5/lib/libLLVMXCoreInfo.a
/usr/lib/llvm-3.5/lib/libLLVMXCoreAsmPrinter.a
/usr/lib/llvm-3.5/lib/libLLVMMipsDisassembler.a
/usr/lib/llvm-3.5/lib/libLLVMMipsCodeGen.a
/usr/lib/llvm-3.5/lib/libLLVMMipsAsmParser.a
/usr/lib/llvm-3.5/lib/libLLVMMipsDesc.a
/usr/lib/llvm-3.5/lib/libLLVMMipsInfo.a
/usr/lib/llvm-3.5/lib/libLLVMMipsAsmPrinter.a
/usr/lib/llvm-3.5/lib/libLLVMARMDisassembler.a
/usr/lib/llvm-3.5/lib/libLLVMARMCodeGen.a
/usr/lib/llvm-3.5/lib/libLLVMARMAsmParser.a
/usr/lib/llvm-3.5/lib/libLLVMARMDesc.a
/usr/lib/llvm-3.5/lib/libLLVMARMInfo.a
/usr/lib/llvm-3.5/lib/libLLVMARMAsmPrinter.a
/usr/lib/llvm-3.5/lib/libLLVMAArch64Disassembler.a
/usr/lib/llvm-3.5/lib/libLLVMAArch64CodeGen.a
/usr/lib/llvm-3.5/lib/libLLVMAArch64AsmParser.a
/usr/lib/llvm-3.5/lib/libLLVMAArch64Desc.a
/usr/lib/llvm-3.5/lib/libLLVMAArch64Info.a
/usr/lib/llvm-3.5/lib/libLLVMAArch64AsmPrinter.a
/usr/lib/llvm-3.5/lib/libLLVMAArch64Utils.a
/usr/lib/llvm-3.5/lib/libLLVMPowerPCDisassembler.a
/usr/lib/llvm-3.5/lib/libLLVMPowerPCCodeGen.a
/usr/lib/llvm-3.5/lib/libLLVMPowerPCAsmParser.a
/usr/lib/llvm-3.5/lib/libLLVMPowerPCDesc.a
/usr/lib/llvm-3.5/lib/libLLVMPowerPCInfo.a
/usr/lib/llvm-3.5/lib/libLLVMPowerPCAsmPrinter.a
/usr/lib/llvm-3.5/lib/libLLVMSparcDisassembler.a
/usr/lib/llvm-3.5/lib/libLLVMSparcCodeGen.a
/usr/lib/llvm-3.5/lib/libLLVMSparcAsmParser.a
/usr/lib/llvm-3.5/lib/libLLVMSparcDesc.a
/usr/lib/llvm-3.5/lib/libLLVMSparcInfo.a
/usr/lib/llvm-3.5/lib/libLLVMSparcAsmPrinter.a
/usr/lib/llvm-3.5/lib/libLLVMTableGen.a
/usr/lib/llvm-3.5/lib/libLLVMDebugInfo.a
/usr/lib/llvm-3.5/lib/libLLVMOption.a
/usr/lib/llvm-3.5/lib/libLLVMX86Disassembler.a
/usr/lib/llvm-3.5/lib/libLLVMX86AsmParser.a
/usr/lib/llvm-3.5/lib/libLLVMX86CodeGen.a
/usr/lib/llvm-3.5/lib/libLLVMSelectionDAG.a
/usr/lib/llvm-3.5/lib/libLLVMAsmPrinter.a
/usr/lib/llvm-3.5/lib/libLLVMMCParser.a
/usr/lib/llvm-3.5/lib/libLLVMX86Desc.a
/usr/lib/llvm-3.5/lib/libLLVMX86Info.a
/usr/lib/llvm-3.5/lib/libLLVMX86AsmPrinter.a
/usr/lib/llvm-3.5/lib/libLLVMX86Utils.a
/usr/lib/llvm-3.5/lib/libLLVMJIT.a
/usr/lib/llvm-3.5/lib/libLLVMLineEditor.a
/usr/lib/llvm-3.5/lib/libLLVMMCDisassembler.a
/usr/lib/llvm-3.5/lib/libLLVMInstrumentation.a
/usr/lib/llvm-3.5/lib/libLLVMInterpreter.a
/usr/lib/llvm-3.5/lib/libLLVMCodeGen.a
/usr/lib/llvm-3.5/lib/libLLVMScalarOpts.a
/usr/lib/llvm-3.5/lib/libLLVMInstCombine.a
/usr/lib/llvm-3.5/lib/libLLVMTransformUtils.a
/usr/lib/llvm-3.5/lib/libLLVMipa.a
/usr/lib/llvm-3.5/lib/libLLVMAnalysis.a
/usr/lib/llvm-3.5/lib/libLLVMMCJIT.a
/usr/lib/llvm-3.5/lib/libLLVMTarget.a
/usr/lib/llvm-3.5/lib/libLLVMRuntimeDyld.a
/usr/lib/llvm-3.5/lib/libLLVMExecutionEngine.a
/usr/lib/llvm-3.5/lib/libLLVMMC.a
/usr/lib/llvm-3.5/lib/libLLVMObject.a
/usr/lib/llvm-3.5/lib/libLLVMCore.a
/usr/lib/llvm-3.5/lib/libLLVMSupport.a
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
    source/omni/tests/runtime/test_memory.cpp)

add_definitions (-DBOOST_TEST_DYN_LINK)

target_link_libraries (omni-tests omni-core omni-runtime ${Boost_LIBRARIES})

