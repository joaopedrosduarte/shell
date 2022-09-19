CC = gcc

objects = main.o shellModels.o styles.o arrayCleaning.o values.o formatArgs.o

shell: $(objects)
	$(CC) -o $@ $(objects)

main.o: shellModels.h

shellModels.o: shellModels.h styles.h arrayCleaning.h values.h formatArgs.h

styles.o: styles.h values.h 

.PHONY: clean run
clean:
	rm $(objects) shell
run: 
	./shell
