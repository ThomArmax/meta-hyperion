require hyperion.inc

inherit cmake_qt5

DEPENDS += "\
	qtbase \
	"

RDPENDS_${PN} = "\
	qtbase \
	"

EXTRA_OECMAKE += "-DENABLE_QT5=ON"
