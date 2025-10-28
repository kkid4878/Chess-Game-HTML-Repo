# the sub makefile, only use of convenient， don't have to cd UCI-EECS-22L-Chess-Skeleton
# just to call the makefile in the UCI-EECS-22L-Chess-Skeleton

SUBDIR := UCI-EECS-22L-Chess-Skeleton

all:
	$(MAKE) -C $(SUBDIR)

clean:
	$(MAKE) -C $(SUBDIR) clean

run:
	$(MAKE) -C $(SUBDIR) run

.PHONY: all clean run