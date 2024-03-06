# Makefile pour compiler binary-trees avec alloc1.c et alloc.h

# Compilateur
CC=gcc

# Options de compilation
CFLAGS=-Wall -Wextra -O2

# Nom du programme executable
TARGET=binary-trees

# Fichiers source
SOURCES=binary-trees.c alloc1.c

# Fichiers objet générés à partir des fichiers source
OBJECTS=$(SOURCES:.c=.o)

# Règle par défaut
all: $(TARGET)

# Règle pour générer l'exécutable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Règle pour générer les fichiers objet à partir des fichiers source
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers générés lors de la compilation
clean:
	rm -f $(TARGET) $(OBJECTS)

# Empêche make de confondre un fichier nommé clean avec la commande clean
.PHONY: all clean