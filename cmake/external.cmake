include(FetchContent)

# fetch and build "embedded_utils" code repo
FetchContent_Populate(
  embedded_utils
  GIT_REPOSITORY https://github.com/cracked-machine/embedded_utils.git
  GIT_TAG main
  SOURCE_DIR embedded_utils
)

# fetch and build "stm32_interrupt_managers" code repo
FetchContent_Populate(
  stm32_interrupt_managers
  GIT_REPOSITORY https://github.com/cracked-machine/stm32_interrupt_managers.git
  GIT_TAG main
  SOURCE_DIR stm32_interrupt_managers
)

target_sources(${BUILD_NAME} PRIVATE
    ${CMAKE_BINARY_DIR}/embedded_utils/src/i2c_utils_ref.cpp
    ${CMAKE_BINARY_DIR}/embedded_utils/src/restricted_base.cpp
    ${CMAKE_BINARY_DIR}/embedded_utils/src/spi_utils_ref.cpp
    ${CMAKE_BINARY_DIR}/embedded_utils/src/timer_manager.cpp
    ${CMAKE_BINARY_DIR}/embedded_utils/src/usart_utils.cpp
    ${CMAKE_BINARY_DIR}/stm32_interrupt_managers/src/isr_manager_stm32g0.cpp
)

target_include_directories(${BUILD_NAME} PRIVATE 
    ${CMAKE_BINARY_DIR}/stm32_interrupt_managers/include
    ${CMAKE_BINARY_DIR}/embedded_utils/include
)
