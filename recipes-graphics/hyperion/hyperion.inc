SUMMARY = "Hyperion is an opensource 'AmbiLight' implementation controlled using the RaspBerry Pi"
DESCRIPTION = "Hyperion is an opensource 'AmbiLight' implementation controlled using the RaspBerry Pi running Raspbmc. \
The main features of Hyperion are: \
- Low CPU load. For a led string of 50 leds the CPU usage will typically be below 1.5% on a non-overclocked Pi. \
- Json interface which allows easy integration into scripts. \
- A command line utility allows easy testing and configuration of the color transforms \
(Transformation settings are not preserved over a restart at the moment...). \
- Priority channels are not coupled to a specific led data provider which means that a provider \
can post led data and leave without the need to maintain a connection to Hyperion. \
This is ideal for a remote application (like our Android app). \
- HyperCon. A tool which helps generate a Hyperion configuration file. \
- XBMC-checker which checks the playing status of XBMC and decides whether or not to capture the screen. \
- Black border detector. \
- A scriptable effect engine. \
- Generic software architecture to support new devices and new algorithms easily."
HOMEPAGE = "https://github.com/hyperion-project/hyperion"

SECTION = "console/tools"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"
PROVIDES = "hyperion"

inherit cmake_qt5 update-rc.d systemd

FILESEXTRAPATHS_append := "${THISDIR}/files"

SRC_URI = " \
    gitsm://github.com/hyperion-project/hyperion.git;protocol=https \
    file://init \
    "

S = "${WORKDIR}/git"

INITSCRIPT_PACKAGES = "${PN}"
INITSCRIPT_NAME_${PN} = "hyperion.sh"
INITSCRIPT_PARAMS_${PN} = "defaults 98 02"

SYSTEMD_PACKAGES = "${PN}"
SYSTEMD_SERVICE_${PN} = "hyperion.service"

PACKAGECONFIG[amlogic] = "-DENABLE_AMLOGIC=ON,-DENABLE_AMLOGIC=OFF"
PACKAGECONFIG[dispmanx] = "-DENABLE_DISPMANX=ON,-DENABLE_DISPMANX=OFF"
PACKAGECONFIG[fb] = "-DENABLE_FB=ON,-DENABLE_FB=OFF"
PACKAGECONFIG[protobuf] = "-DENABLE_PROTOBUF=ON,-DENABLE_PROTOBUF=OFF,protobuf protobuf-native,"
PACKAGECONFIG[spi] = "-DENABLE_SPIDEV=ON,-DENABLE_SPIDEV=OFF"
PACKAGECONFIG[tinkerforge] = "-DENABLE_TINKERFORGE=ON,-DENABLE_TINKERFORGE=OFF"
PACKAGECONFIG[v4l2] = "-DENABLE_V4L2=ON,-DENABLE_V4L2=OFF,protobuf protobuf-native,"
PACKAGECONFIG[x11] = "-DENABLE_X11=ON,-DENABLE_X11=OFF"
PACKAGECONFIG[ws2812b] = "-DENABLE_WS2812BPWM=ON,-DENABLE_WS2812BPWM=OFF"
PACKAGECONFIG[ws281x] = "-DENABLE_WS281XPWM=ON,-DENABLE_WS281XPWM=OFF"

PACKAGECONFIG ?= " \
    protobuf \
    spi \
    v4l2 \
    ${@bb.utils.contains("DISTRO_FEATURES", "x11", "x11", "",d)} \
    "

EXTRA_OECMAKE += " \
    -DENABLE_QT5=ON \
    -DENABLE_OSX=OFF \
    -DENABLE_TESTS=OFF \
    "

DEPENDS = " \
    libusb \
    python \
    qtbase \
    "

RDEPENDS_${PN} = " \
    qtbase \
    bash \
    procps \
    python \
    python-image \
    python-math \
    python-io \
    "

HYPERION_CONFIG_FILE ??= "${S}/config/hyperion.config.json"

FILES_${PN} += " \
    /opt/hyperion/config/hyperion.config.json \
    /opt/hyperion/effects/ \
    ${systemd_unitdir}/system/hyperion.service \
    "

do_install_append() {
    #install init scripts
    if ${@bb.utils.contains('DISTRO_FEATURES','sysvinit','true','false',d)}; then
        install -d ${D}${sysconfdir}/init.d/
        install -m 0755 ${WORKDIR}/init/sysvinit/hyperion.sh ${D}${sysconfdir}/init.d
    fi

    if ${@bb.utils.contains('DISTRO_FEATURES','systemd','true','false',d)}; then
       install -d ${D}${systemd_unitdir}/system/ ${D}${sysconfdir}/systemd/system/
       install -m 0644 ${WORKDIR}/init/systemd/hyperion.service ${D}${systemd_unitdir}/system/
    fi

    # install hyperion config file
    install -d ${D}${sysconfdir}
    install -d ${D}/opt/hyperion/config/
    install ${HYPERION_CONFIG_FILE} ${D}/opt/hyperion/config/hyperion.config.json

    install -d ${D}/opt/hyperion/effects
    install ${S}/effects/* ${D}/opt/hyperion/effects
}
