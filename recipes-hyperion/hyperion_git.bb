require hyperion.inc

SRC_URI += " \
    file://0001-use-yocto-protobuf.patch \
    file://0002-fix-qa-issue-set-valid-install-path.patch \
    "

SRCREV = "f64b6eb8dbaeef0f4aae8954da3b87524be106bd"

PR = "0"
PV = "1.1.1"
