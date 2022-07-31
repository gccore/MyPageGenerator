
function(Core_ConfigureProjectThirdParties target_name)
  set(third_party_dir ${PROJECT_SOURCE_DIR}/ThirdParty)

  if(NOT EXISTS ${third_party_dir}/NodeEditor)
    message(FATAL_ERROR "Initialize submodules, i can't find NodeEditor.")
  endif()
  add_subdirectory(${third_party_dir}/NodeEditor)
  target_link_libraries(${target_name} PRIVATE NodeEditor::nodes)

  if(NOT EXISTS ${third_party_dir}/MD4C-Html)
    message(FATAL_ERROR "I can't find MD4C-Html.")
  endif()
  add_subdirectory(${third_party_dir}/MD4C-Html)
  target_link_libraries(${target_name} PRIVATE md4c-html)

  if(NOT EXISTS ${third_party_dir}/Optional)
    message(FATAL_ERROR "I can't find Optional.")
  endif()
  add_subdirectory(${third_party_dir}/Optional)
  target_link_libraries(${target_name} PRIVATE tl::optional)
endfunction()
