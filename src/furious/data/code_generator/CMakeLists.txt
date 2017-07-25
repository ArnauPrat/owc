
find_package(LLVM REQUIRED)
include_directories(${LLVM_INCLUDE_DIRS})

add_definitions(
  -D__STDC_LIMIT_MACROS
  -D__STDC_CONSTANT_MACROS
  )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -std=c++11")


add_executable(loop-convert LoopConvert.cpp)

link_directories(${LLVM_LIBRARY_DIR})

#target_link_libraries(loop-convert
#  ${LIBCLANG_LIBRARY}
#  clangTooling
#  clangBasic
#  clangASTMatchers
# )
target_link_libraries(loop-convert
  clangFrontend
  clangSerialization
  clangDriver
  clangParse
  clangSema
  clangAnalysis
  clangAST
  clangBasic
  clangEdit
  clangLex
  clangTooling
  )

target_link_libraries(loop-convert
  LLVMX86AsmParser # MC, MCParser, Support, X86Desc, X86Info
  LLVMX86Desc # MC, Support, X86AsmPrinter, X86Info
  LLVMX86AsmPrinter # MC, Support, X86Utils
  LLVMX86Info # MC, Support, Target
  LLVMX86Utils # Core, Support
  LLVMipo
  LLVMScalarOpts
  LLVMInstCombine
  LLVMTransformUtils
  #LLVMipa
  LLVMAnalysis
  LLVMTarget
  LLVMOption # Support
  LLVMMCParser # MC, Support
  LLVMMC # Object, Support
  LLVMObject # BitReader,  Core, Support
  LLVMBitReader # Core,  #Support
  LLVMCore # Support
  LLVMSupport
  )
