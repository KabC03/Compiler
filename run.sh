
clear
python3 ./src/generate_tokeniser_enum.py
clang++ ./src/*.c++ -fsanitize=address -Wall -Werror -std=c++11 -o ./output/out
echo "Compiled"
./a.out

