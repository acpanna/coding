#!/bin/sh

dd if=/dev/zero of=/tmp/fsfile bs=1k count=4096

losetup /dev/loop0 /tmp/fsfile

mke2fs /dev/loop0 4096
tune2fs /dev/loop0 -c 0
mount -t ext2 /dev/loop0 /mnt

cp -dpR /tmp/fssub/* /mnt

ldconfig -r /mnt

umount /mnt

losetup -d /dev/loop0

dd if=/tmp/fsfile | gzip -v9 > /tmp/rootfs.gz
dd if=/tmp/rootfs.gz of=/dev/fd0 bs=1k
