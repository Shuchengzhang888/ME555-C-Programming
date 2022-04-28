all:step1 step2 step3 step4

step1: path-step1-main.cpp path-step1.cpp path-planning.hpp
	g++ -o step1 -std=gnu++98 -Wall -Werror -ggdb3 path-step1-main.cpp

step2: path-step2-main.cpp path-step4.cpp path-step3.cpp path-step2.cpp path-step1.cpp path-planning.hpp
	g++ -o step2 -std=gnu++98 -Wall -Werror -ggdb3 path-step2-main.cpp

step3: path-step3-main.cpp path-step4.cpp path-step3.cpp path-step2.cpp path-step1.cpp path-planning.hpp
	g++ -o step3 -std=gnu++98 -Wall -Werror -ggdb3 path-step3-main.cpp

step4: path-step4-main.cpp path-step4.cpp path-step3.cpp path-step2.cpp path-step1.cpp path-planning.hpp
	g++ -o step4 -std=gnu++98 -Wall -Werror -ggdb3 path-step4-main.cpp
