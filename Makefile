all: create_data_store.c utils.c db_io.c  lru_cache.c hash_functions.c core.c install_db.c

create_data_store.c:
	cc -c -ggdb -I ./inc -o ./lib/create_data_store.o ./src/create_data_store.c

utils.c:
	cc -c -ggdb -I ./inc -o ./lib/utils.o ./src/utils.c

db_io.c:
	cc -c -ggdb -I ./inc -o ./lib/db_io.o ./src/db_io.c

hash_functions.c:
	cc -c -ggdb -I ./inc -o ./lib/hash_functions.o ./src/hash_functions.c

core.c:
	cc -c -ggdb -I ./inc -o ./lib/core.o ./src/core.c

install_db.c: create_data_store.c
	cc -ggdb -I ./inc -o ./lib/install_db ./lib/create_data_store.o ./src/install_db.c

lru_cache.c:
	cc -c -ggdb -I ./inc -o ./lib/lru_cache.o ./src/lru_cache.c

driver.c: all
	cc -ggdb -I ./inc -o ./lib/uptown ./lib/create_data_store.o ./lib/utils.o ./lib/db_io.o ./lib/hash_functions.o ./lib/core.o ./lib/lru_cache.o ./src/driver.c
