require hyperion.inc

inherit cmake

SRC_URI += " \
	file://0003-use-yocto-cmake-qt4.patch \
	"

EXTRA_OECMAKE += "-DENABLE_QT5=OFF"
