require hyperion-image-base.inc

DESCRIPTION = "Standard full-featured Linux system with hyperion"

IMAGE_INSTALL += " \
    packagegroup-basic \
    packagegroup-base \
    packagegroup-core-full-cmdline \
    "
