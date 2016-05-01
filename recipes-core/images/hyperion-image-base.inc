# Base this image on core-image-minimal
include recipes-core/images/core-image-minimal.bb

LICENSE = "MIT"

IMAGE_FEATURES += "ssh-server-dropbear"

IMAGE_INSTALL += " \
    packagegroup-core-boot \
    kernel-modules \
    ${CORE_IMAGE_EXTRA_INSTALL} \
    hyperion \
    "

inherit extrausers

EXTRA_USERS_PARAMS += " \
    useradd -P hyperion ${MACHINE}; \
    usermod -aG sudo ${MACHINE}; \
    "
