CPP = g++
CPPFLAG = -Wall -Wextra -Wpedantic -O3

ARG = ../LittleWomen.txt

.PHONY: all
all: norep2_VCT_.x norep2_MAP_.x norep2_U_MAP_.x

norep2_VCT_.x: norep2.cpp
	$(CPP) $(CPPFLAG) -o $@ $< -D_VCT_

norep2_MAP_.x: norep2.cpp
	$(CPP) $(CPPFLAG) -o $@ $< -D_MAP_

norep2_U_MAP_.x: norep2.cpp
	$(CPP) $(CPPFLAG) -o $@ $< -D_U_MAP_

.PHONY: celan
clean:
	rm -f norep2_VCT_.x norep2_MAP_.x norep2_U_MAP_.x

.PHONY: run
run:
	./norep2_VCT_.x $(ARG)
	./norep2_MAP_.x $(ARG)
	./norep2_U_MAP_.x $(ARG)