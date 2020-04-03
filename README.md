# xfrm-minstrel
Wanted to juggle with SP/SA (based on iproute2) (add and remove xfrm SP/SA, hook SA expires)

# INSTALL 
$ apt install libnl-3-dev libnl-xfrm-3-dev

# Makefile
$ make

# Run
$ sudo ip x monitor #allowing you to see what's happening

$ sudo ./build/minstrel

Take care, by executing twice in a row the program, you will try to create the same SA/SP (and the prgm will end with an error).

# Debug 
$ sudo NLCB=debug NLDBG=2 ./build/minstrel

Table 1. Debugging Levels Level 	Description

0 Debugging disabled (default)

1 Warnings, important events and notifications

2 More or less important debugging messages

3 Repetitive events causing a flood of debugging messages

4 Even less important messages

# Reference
https://gitlab.atica.um.es/gabilm.um.es/cfgipsec2

https://spin.atomicobject.com/2016/08/26/makefile-c-projects/

http://man7.org/linux/man-pages/man7/rtnetlink.7.html

http://man7.org/linux/man-pages/man3/libnetlink.3.html

http://man7.org/linux/man-pages/man7/netlink.7.html

http://man7.org/linux/man-pages/man3/netlink.3.html

https://web.archive.org/web/20110902031641/http://1984.lsi.us.es/~pablo/docs/spae.pdf

https://netfilter.org/projects/libmnl/
