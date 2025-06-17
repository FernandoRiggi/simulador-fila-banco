# Define o compilador C a ser usado
CC = gcc

# Define as flags de compilação:
# -Wall: Habilita todos os warnings comuns
# -Wextra: Habilita warnings extras (mais warnings úteis)
# -std=c99: Compila usando o padrão C99 (boa prática, garante portabilidade)
# -g: Inclui informações de debug (útil para depuração com gdb)
CFLAGS = -Wall -Wextra -std=c99 -g

# Define os arquivos objeto (.o) que serão gerados a partir dos arquivos .c
# Assumindo que seu arquivo principal se chama bank_simulator.c
OBJS = bank_simulator.o queue.o


# Define o nome do executável final
EXEC = bank_simulator

# Regra padrão: ao digitar 'make' sem argumentos, ele tentará construir o executável
all: $(EXEC)

# Regra para criar o executável: ele depende de todos os arquivos objeto
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC) # <--- ESTA LINHA DEVE COMEÇAR COM UM CARACTERE TAB

# Regra para compilar bank_simulator.c em bank_simulator.o
# Depende do arquivo .c e do cabeçalho da fila (queue.h)
bank_simulator.o: bank_simulator.c queue.h
	$(CC) $(CFLAGS) -c bank_simulator.c # <--- ESTA LINHA DEVE COMEÇAR COM UM CARACTERE TAB

# Regra para compilar queue.c em queue.o
# Depende de queue.c e queue.h
queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c # <--- ESTA LINHA DEVE COMEÇAR COM UM CARACTERE TAB

# Regra para limpar os arquivos gerados pela compilação
# Remove todos os arquivos .o e o executável
clean:
	rm -f $(OBJS) $(EXEC) # <--- ESTA LINHA DEVE COMEÇAR COM UM CARACTERE TAB