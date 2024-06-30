FLAGS=-Wall -Wextra

bin:
	mkdir bin


bin/crypto: bin crypto.cc
	g++ ${FLAGS} crypto.cc -o ./bin/crypto 

.PHONY: criptografia/run
criptografia/run: bin/crypto
	./bin/crypto


bin/distance: bin distance.cc
	g++ $(FLAGS) distance.cc -o ./bin/distance

.PHONY: menor_distancia_arrays/run
menor_distancia_arrays/run: bin/distance
	./bin/distance

