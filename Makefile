OBJ = main.o UI.o App.o str_util.o

workshop: $(OBJ)
	g++ -o mytunes $(OBJ)

main.o: main.cpp
	g++ -c main.cpp

UI.o: UI.cpp UI.h
	g++ -c -std=c++11 UI.cpp

App.o: App.cpp App.h
	g++ -c -std=c++11 App.cpp

str_util.o: str_util.cpp str_util.h
	g++ -c -std=c++11 str_util.cpp

clean:
	rm -f $(OBJ) mytunes
