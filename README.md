# OS

This operating system kernel for x86_32 processor. As bootloader used GRUB. To emulation use QEMU.


### How to start

Create raw-image:
```Bash
$ qemu-img create -f raw hard_disk.img 1G
```

Prepare the block device driver:
```Bash
# modprobe -r loop
# modprobe loop max_part=15
# losetup -f hard_disk.img
```

Check the name assigned to the image:
```Bash
# losetup
NAME       SIZELIMIT OFFSET AUTOCLEAR RO BACK-FILE
/dev/loop0 0      0         0         0  /home/andrey/OS/hard_disk.img
```

Create a partition table:
```Bash
# parted /dev/loop0
...
(parted) mklabel msdos
...
(parted) quit
...
# fdisk /dev/loop0
...
n (new partition)
...
p (primary partition 1)
...
4096
...
(default)
...
w
```

Install `GRUB`:
```Bash
# mkfs.ext2 /dev/loop0p1
# mount /dev/loop0p1 /mnt
# mkdir /mnt/boot
# grub-install --root-directory=/mnt  /dev/loop0
```


### Building the kernel

```Bash
$ make
```


### Run QEMU

```Bash
# cp hard_disk.img /mnt/boot
# cp boot/grub.cfg /mnt/boot/grub
# qemu-system-x86_64 /home/andrey/OS/hard_disk.img
```