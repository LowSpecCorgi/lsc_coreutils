src := src/lsc_cat.c

build/lsc_cat.c: $(src)
	gcc $(src) -o build/lsc_cat.exe -std='c99'