#!/bin/sh

cd ~haaner/Apps/phoenix && xcodebuild clean && xcodebuild

sudo -u root sh -c 'cd /Users/haaner/Apps/phoenix/build/Release/ && chown -R root:wheel phoenix.kext/ && kextload phoenix.kext && (kextstat | grep "phoenix") && kextunload phoenix.kext && rm -rf phoenix.kext* && (dmesg | tail -n10)'
