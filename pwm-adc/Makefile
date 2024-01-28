

compile:
	make -C build all


prog: 
	`which openocd`  -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "adapter speed 5000" -c "program build/test.elf verify reset exit"	


all: compile prog
