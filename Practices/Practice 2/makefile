# Sabau Sabau, Elvi Mihai

INPUT = source.cpp
OUTPUT = output
OPTS = g++

all:
	${OPTS} ${INPUT} -o ${OUTPUT}


clear: 
	rm ${OUTPUT}

redo: 
	rm ${OUTPUT} && ${OPTS} ${INPUT} -o ${OUTPUT}
	
mpirun:
	mpirun -np 8 ./${OUTPUT}

run:
	./${OUTPUT}