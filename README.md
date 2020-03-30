# xfrm-minstrel
Wanted to juggle with SP/SA (based on iproute2) (add and remove xfrm SP/SA, hook SA expires)

# INSTALL 
apt install libnl-3-dev libnl-xfrm-3-dev

# Makefile
make

# Run
sudo ip x monitor #allowing you to see what's happening
sudo ./src/minstrel
