Step 1:
Install GMP Library:

	https://gmplib.org/
	
Compile:

	tar --lzip -xvf gmp-6.1.0.tar.lz
	cd gmp-6.1.0
	./configure
	make
	make check
	make install
	
Step 2:
Compile IamLupo Core Library:

	cd core
	./compile

Step 3:
At this point you can compile all Problems and Examples with:
	
	./compile
