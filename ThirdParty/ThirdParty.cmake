
function(Core_ConfigureProjectThirdParties target_name)
  set(third_party_dir ${PROJECT_SOURCE_DIR}/ThirdParty)

  if(NOT EXISTS ${third_party_dir}/NodeEditor)
    message(FATAL_ERROR "Initialize submodules, i can't find NodeEditor.")
  endif()
  add_subdirectory(${third_party_dir}/NodeEditor)
  target_link_libraries(${target_name} PRIVATE NodeEditor::nodes)

  if(NOT EXISTS ${third_party_dir}/MD4C)
    message(FATAL_ERROR "Initialize submodules, i can't find MD4C.")
  endif()
  add_subdirectory(${third_party_dir}/MD4C)
  target_link_libraries(${target_name} PRIVATE md4c-html)
endfunction()
