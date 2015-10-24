ALL: boost

.PHONY = clean

clean:
	@echo "Borrando ./boost"
	\rm -f boost

boost: boostGraph.cpp
	g++ -std=c++11 -I /usr/BoostGraph/boost_1_59_0/ boostGraph.cpp -o boost

