SIGNALS="abrt segv"
LIBSEGV=/lib/x86_64-linux-gnu/libSegFault.so
SENTRY_VER=sentry-native-0.4.15
SENTRY_BUILD=$(abspath ${SENTRY_VER}-build)
SENTRY_FILE=${SENTRY_VER}.tar.gz
SENTRY_INCLUDE=${SENTRY_VER}/include

SENTRY_DSN=`cat sentry_dsn.txt` # put your sentry_dsn here

all: ./test
	./test

./test: test.c
	cc -g test.c -o test

segv: ./test
	env SEGFAULT_SIGNALS=${SIGNALS} LD_PRELOAD=${LIBSEGV} ./test

sentry: ${SENTRY_BUILD}/libsentry.so
	cc -g -DSENTRY -I${SENTRY_INCLUDE} test.c -L${SENTRY_BUILD} -lsentry -o test_sentry
	env SENTRY_DSN=${SENTRY_DSN} LD_LIBRARY_PATH=${SENTRY_BUILD} ./test_sentry

${SENTRY_BUILD}/libsentry.so: ${SENTRY_VER}
	(cd ${SENTRY_BUILD}; cmake ../${SENTRY_VER}; make -j8)

${SENTRY_VER}:
	tar xvfz ${SENTRY_FILE}
	(cd ${SENTRY_VER}/external; git clone https://github.com/getsentry/breakpad.git)
	(cd ${SENTRY_VER}/external/third_party; git clone https://chromium.googlesource.com/linux-syscall-support lss)
	mkdir ${SENTRY_BUILD}
