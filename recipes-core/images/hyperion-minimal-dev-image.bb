require hyperion-image-base.inc

DESCRIPTION = "A minimal console-only image with hyperion and debug tweaks"

IMAGE_FEATURES += " \
    package-management \
    "

EXTRA_IMAGE_FEATURES = " \
    debug-tweaks \
    "

IMAGE_INSTALL += " \
    hyperion-dbg \
    "
