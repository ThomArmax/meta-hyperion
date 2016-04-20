require hyperion.inc

SRC_URI = " \
	gitsm://github.com/hyperion-project/hyperion.git;protocol=https \
	file://0001-use-yocto-protobuf.patch \
	file://0002-fix-qa-issue-set-valid-install-path.patch \
	"

SRCREV = "f64b6eb8dbaeef0f4aae8954da3b87524be106bd"

S = "${WORKDIR}/git"

PR = "1"
PV = "1.1"

