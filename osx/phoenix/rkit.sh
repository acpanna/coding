#!/bin/sh

PHOENIX_DIR=$(pwd -P)

cd ${PHOENIX_DIR} && xcodebuild clean && xcodebuild

sudo -u root sh -c "cd ${PHOENIX_DIR}/build/Release/ && chown -R root:wheel phoenix.kext/ && kextload phoenix.kext && (kextstat | grep 'phoenix') && kextunload phoenix.kext && rm -rf phoenix.kext* && (dmesg | tail -n10)"
