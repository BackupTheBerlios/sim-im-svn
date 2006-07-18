# a small macro to create mo files out of po's

MACRO(FIND_MSGFMT)
    IF(NOT MSGFMT_EXECUTABLE)
        IF(NOT WIN32)
            SET(MSGFMT_NAME "msgfmt")
        ELSE(NOT WIN32)
            SET(MSGFMT_NAME "msg2qm")
        ENDIF(NOT WIN32)
        FIND_PROGRAM(MSGFMT_EXECUTABLE ${MSGFMT_NAME})
        IF (NOT MSGFMT_EXECUTABLE)
          MESSAGE(FATAL_ERROR "${MSGFMT_NAME} not found - aborting")
        ENDIF (NOT MSGFMT_EXECUTABLE)
    ENDIF(NOT MSGFMT_EXECUTABLE)
ENDMACRO(FIND_MSGFMT)

MACRO(COMPILE_PO_FILES po_subdir)
    FIND_MSGFMT()

    FILE(GLOB po_files ${po_subdir}/*.po)

    ADD_CUSTOM_TARGET(po-files ALL)

    FILE(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/po)

    FOREACH(po_input ${po_files})
        GET_FILENAME_COMPONENT(_basename ${po_input} NAME_WE)
        GET_FILENAME_COMPONENT(po_file   ${po_input} NAME)
        
        SET(mo_output po/${_basename}.mo)

        ADD_CUSTOM_TARGET( ${mo_output} 
			    COMMAND ${CMAKE_COMMAND} 
			    -E echo 
			    "Generating" ${mo_output} "from" ${po_input} 
                            COMMAND ${MSGFMT_EXECUTABLE}
                            ${po_input}
			    -o ${mo_output}
                            DEPENDS ${po_input}
        )
        SET(mo_files ${mo_files} ${mo_output})
	# FIXME installation path for Windows
	INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/${mo_output} DESTINATION ${SIM_I18N_DIR}/${_basename}/LC_MESSAGES RENAME sim.mo)
    ENDFOREACH(po_input ${po_files})
ADD_DEPENDENCIES(po-files ${mo_files})
    #   INSTALL(FILES ${mo_files} DESTINATION ${SIM_I18N_DIR})
ENDMACRO(COMPILE_PO_FILES po_subdir)
