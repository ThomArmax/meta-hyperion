FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
PACKAGECONFIG_GL = ""
PACKAGECONFIG_append =  " gles2 widgets"

# Workarounds for getting EGL and GLES2
SRC_URI += "file://0014-eglfs-rpi-workaround.patch \
            file://0015-broadcom-97425-eglfshook.patch \
            file://0016-add-rpi-config.patch \
            file://0017-fix-rpi-cursor.patch \
            "

EXTRA_OECONF += "'-I${STAGING_DIR_TARGET}/usr/include/interface/vcos/pthreads/' \
                '-I${STAGING_DIR_TARGET}/usr/include/interface/vmcs_host/linux/' \
                "
