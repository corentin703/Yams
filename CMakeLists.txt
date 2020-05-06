cmake_minimum_required(VERSION 3.1.0)
project( Yams )

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Core REQUIRED Widgets REQUIRED)

find_package( OpenCV REQUIRED )



set(HEADERS
    
)

set(SRCS
    
)

set(CLASS_HEADERS
    src/models/CDice.hpp
    src/models/CDiceSet.hpp
)

set(CLASS_SRCS
    src/models/CDice.cpp
)

set(QT_CLASS_HEADERS
    src/models/QPlayerGrid.hpp

    src/QYams.hpp
    src/image_recognition/QCameraWidget.hpp
    src/QPlayerGridsWidget.hpp

    src/QYamsStartFormWidget.hpp

    src/QAboutWidget.hpp
    src/QEndGameWidget.hpp
)

set(QT_CLASS_SRCS
    src/models/QPlayerGrid.cpp

    src/QYams.cpp
    src/image_recognition/QCameraWidget.cpp
    src/QPlayerGridsWidget.cpp

    src/QYamsStartFormWidget.cpp

    src/QAboutWidget.cpp
    src/QEndGameWidget.cpp
)

set(QT_VIEW
    src/QYams.ui
    src/image_recognition/QCameraWidget.ui
    src/QPlayerGridsWidget.ui

    src/QYamsStartFormWidget.ui

    src/QAboutWidget.ui
    src/QEndGameWidget.ui
)

set(QT_RESSOURCES
    src/QYams.qrc
)

add_executable( ${PROJECT_NAME} 
    ${HEADERS} ${SRCS} 
    ${CLASS_HEADERS} ${CLASS_SRCS} 
    ${QT_CLASS_HEADERS} ${QT_CLASS_SRCS} ${QT_VIEW} ${QT_RESSOURCES}  
    
    src/main.cpp 
)

if(WIN32) # Regarde si on est sous Windows
	if(MSVC) # Regarde si on utilise le compilateur de Visual Studio
		set_target_properties(${PROJECT_NAME} PROPERTIES
			WIN32_EXECUTABLE YES
			LINK_FLAGS "/ENTRY:mainCRTStartup"
		)
	elseif(CMAKE_COMPILER_IS_GNUCXX)
			# SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows") # Pas testé
	else()
		message(SEND_ERROR "Vous utilisez un compilateur non supporté ! (Pas MSVC ou GCC)")
	endif(MSVC)
elseif(APPLE)
	set_target_properties(${PROJECT_NAME} PROPERTIES
			MACOSX_BUNDLE YES
	)
elseif(UNIX)
	# Rien de requis
else()
	message(SEND_ERROR "Vous êtes sur une plate-forme non suportée ! (Not Win32, Mac OS X or Unix)")
endif(WIN32)

target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )
# target_link_libraries( ${PROJECT_NAME} ${QT_LIBRARIES} )
target_link_libraries( ${PROJECT_NAME} Qt5::Core )
target_link_libraries( ${PROJECT_NAME} Qt5::Widgets )

