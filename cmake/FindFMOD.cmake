set(CMAKE_FIND_PACKAGE_NAME "FMOD")

set(FMOD_API_HOME "")

if (WIN32)
	if (MSVC)
		set(FMOD_API_HOME ${CMAKE_SOURCE_DIR}/lib/fmodstudio/win)
		if (NOT EXISTS ${FMOD_API_HOME})
			message(FATAL "FMOD Studio API directory could not be found at: ${FMOD_API_HOME}")
		endif()

		if (CMAKE_BUILD_TYPE MATCHES "Debug")
			set(FMOD_Logging "L")
		else()
			set(FMOD_Logging "")
		endif()

		set(FMOD_Libraries
			${FMOD_API_HOME}/lib/fmodstudio${FMOD_Logging}_vc.lib
			${FMOD_API_HOME}/lib/fmod${FMOD_Logging}_vc.lib)

		# Copy dlls to the output directory
		if(NOT EXISTS "${CMAKE_BINARY_DIR}/fmodstudio.dll")
			file(COPY "${FMOD_API_HOME}/lib/fmodstudio${FMOD_Logging}.dll"
				DESTINATION "${CMAKE_BINARY_DIR}")
		endif()
		if(NOT EXISTS "${CMAKE_BINARY_DIR}/fmod${FMOD_Logging}.dll")
			file(COPY "${FMOD_API_HOME}/lib/fmod${FMOD_Logging}.dll"
				DESTINATION "${CMAKE_BINARY_DIR}")
		endif()
	else()
		message(FATAL "FMOD Studio Windows non-msvc builds are not supported")
	endif()
endif()

if (EMSCRIPTEN)
	set(FMOD_API_HOME ${CMAKE_SOURCE_DIR}/lib/fmodstudio/web)

	if (CMAKE_BUILD_TYPE MATCHES "Debug")
		set(FMOD_Logging "L")
	else()
		set(FMOD_Logging "")
	endif()

	set(FMOD_Libraries
		${FMOD_API_HOME}/lib/fmodstudio${FMOD_Logging}_bindings.a
		${FMOD_API_HOME}/lib/fmodstudio${FMOD_Logging}_js.a
		${FMOD_API_HOME}/lib/fmodstudio${FMOD_Logging}_wasm.a)

	set(FMOD_Emscripten_Flags "-s EXPORTED_RUNTIME_METHODS=['cwrap','setValue','getValue']")
endif()

if ("${FMOD_API_HOME}" STREQUAL "")
	message(FATAL "FMOD Studio package could not be found")
endif()

set(FMOD_Includes ${FMOD_API_HOME}/inc)

set(FMOD_FOUND 1)
