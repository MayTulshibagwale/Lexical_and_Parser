all: cooke_parser

cooke_parser: front.o parser.o 
	$(CC) -g -Wall front.o parser.o -o cooke_parser

.c.o:
	$(CC) -g -Wall -c $<


test: cooke_parser front.in
	./cooke_parser example1.dc

clean:
	$(RM) front.o parser.o cooke_parser
