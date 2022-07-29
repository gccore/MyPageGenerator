
function(Core_ConfigureProjectThirdParties target_name)
  set(third_party_dir ${PROJECT_SOURCE_DIR}/ThirdParty)

  if(NOT EXISTS ${third_party_dir}/NodeEditor)
    message(FATAL_ERROR "Initialize submodules i can't find NodeEditor.")
  endif()
  add_subdirectory(${third_party_dir}/NodeEditor)
  target_link_libraries(${target_name} PRIVATE NodeEditor::nodes)
endfunction()
