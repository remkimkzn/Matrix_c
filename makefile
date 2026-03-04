CC = gcc
FLAGS = -Werror -Wall -Wextra -std=c11 
CHECK_FLAGS = -lcheck -lm -lpthread   
TARGET = test_s21_matrix

FILES = $(wildcard s21*.c)

TEST = test.c

all: s21_matrix.a

s21_matrix.a: $(FILES)
	$(CC) $(FLAGS) -c $(FILES)
	ar rcs s21_matrix.a *.o

gcov_report: s21_matrix.a
	$(CC) $(FLAGS) --coverage $(TEST) $(FILES) -o ./gcov $(CHECK_FLAGS)
	./gcov
	lcov -t "gcov" -o gcov.info -c -d .
	genhtml -o report gcov.info
	open ./report/index.html
	rm -rf *.gcno *gcda *.gcov

test: s21_matrix.a
	$(CC) $(FLAGS) $(TEST) $< -o $(TARGET) $(CHECK_FLAGS)
	./$(TARGET)

clean:
	rm -rf *gcno *gcda *gcov gcov.info ./report 
	rm -rf *.o *.a $(TARGET)