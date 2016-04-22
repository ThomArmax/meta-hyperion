LICENSE = "MIT"

IMAGE_FEATURES += "ssh-server-dropbear"

IMAGE_INSTALL += "packagegroup-core-boot \
                  kernel-modules \
                  ${CORE_IMAGE_EXTRA_INSTALL} \
                  hyperion \
                  "

inherit core-image  
inherit extrausers

EXTRA_USERS_PARAMS = " \
    useradd -P hyperion ${MACHINE}; \
    usermod -aG sudo ${MACHINE}; \
    "