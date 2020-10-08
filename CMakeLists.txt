cmake_minimum_required(VERSION 3.8.0)
project( Yams )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Core REQUIRED Widgets REQUIRED)

find_package( OpenCV REQUIRED )

include_directories(src)

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
    src/QAboutWidget.qrc
)

add_executable( ${PROJECT_NAME}
    ${HEADERS} ${SRCS}
    ${CLASS_HEADERS} ${CLASS_SRCS}
    ${QT_CLASS_HEADERS} ${QT_CLASS_SRCS} ${QT_VIEW} ${QT_RESSOURCES}
    
    src/main.cpp
    src/yams.rc
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
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")
else()
	message(SEND_ERROR "Vous êtes sur une plate-forme non suportée ! (Non Win32, Mac OS X ou Unix)")
endif(WIN32)

target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )
target_link_libraries( ${PROJECT_NAME} Qt5::Core )
target_link_libraries( ${PROJECT_NAME} Qt5::Widgets )

