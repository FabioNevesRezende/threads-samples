install(
    TARGETS barrier.exe
    RUNTIME COMPONENT threads-samples_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
