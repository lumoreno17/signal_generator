#Package information
hyro_init_package(signal_generator VERSION 0.0.1)

find_package ( Qt4 COMPONENTS QtCore QtGui QtOpenGl )

#Required packages
hyro_find_package(hyro_utils REQUIRED)
hyro_find_package(hyro_msgs REQUIRED)
hyro_find_package(hyro_widgets REQUIRED)

include(${QT_USE_FILE} )

include_directories(
  ${PROJECT_SOURCE_DIR}/src
)

#Declare header files
set(SIGNAL_GENERATOR_HEADERS
  include/hyro/SignalGeneratorComponent.h
  include/hyro/DigitalConverterComponent.h
  include/hyro/SignalGenerator.h
  include/hyro/msgs/Signal.h
  include/hyro/msgs/Signal.proto.h
  include/hyro/Thresholding.h
)

#Declare source files
set(SIGNAL_GENERATOR_SOURCES
  src/components/SignalGeneratorComponent.cpp
  src/components/DigitalConverterComponent.cpp
  src/internal/SignalGenerator.cpp
  src/internal/Thresholding.cpp
)

hyro_add_library(
  ${PROJECT_NAME}_components
  HEADERS ${SIGNAL_GENERATOR_HEADERS}
  SOURCES ${SIGNAL_GENERATOR_SOURCES}
  DEPENDS_ON
    hyro_utils
    hyro_msgs
    hyro_widgets
)

hyro_add_executable(
  ${PROJECT_NAME}
  SOURCES 
    src/examples/signal_generator.cpp
  DEPENDS_ON 
    ${PROJECT_NAME}_components
)

#Message declaration
hyro_compile_messages(
  ${PROJECT_NAME}_components
  SOURCES
    msgs/hyro/msgs/Signal.proto
)

hyro_install_package(${PROJECT_NAME}
  LIBS
    ${PROJECT_NAME}_components
  EXES
    ${PROJECT_NAME}
)

#Unit tests declaration
hyro_add_gtest(${PROJECT_NAME}
  SOURCES
    tests/test_signal_generator.cpp
  DEPENDS_ON
    ${PROJECT_NAME}_components
)
