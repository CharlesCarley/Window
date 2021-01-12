include(FindDoxygen)

if (DOXYGEN_FOUND)


	set(TargetName   DoxygenDocs)
	set(Input_CFG	 ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
	set(Output_CFG	 ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
	set(Output_MAIN	 ${CMAKE_CURRENT_BINARY_DIR}/html/index.html)

	set_source_files_properties(${Output_MAIN} PROPERTIES GENERATED TRUE)

	set(Target_SRC
		header.html
		footer.html
		dox.css
		style.css
		Layout.xml
		${Input_CFG}
		${Output_CFG}
		${Output_MAIN}
	)


	set(Input_SRC
		Source/MainPage.inl
	)

	source_group("Source"    FILES ${Input_SRC})
	source_group("Resource"  FILES ${Target_SRC})

	configure_file(${Input_CFG} ${Output_CFG})

	add_custom_target(${TargetName}
		COMMAND ${DOXYGEN_EXECUTABLE} ${Output_CFG}
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} 
		COMMENT "Building Documentation" 
		SOURCES ${Target_SRC} ${Input_SRC}
		)

	set_target_properties(${TargetName} PROPERTIES FOLDER "CMakePredefinedTargets")
else()
	message("")
	message("Doxygen was not found. To build the documentation install Doxygen")
	message("https://www.doxygen.nl/index.html and reconfigure")
	message("")
endif()
