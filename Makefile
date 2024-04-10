file_util_src := src/lsc_file_util.h src/lsc_file_util.c

lsc_cat_src := src/lsc_cat.c $(file_util_src)

build/lsc_cat.c: $(lsc_cat_src)
	gcc $(lsc_cat_src) -o build/lsc_cat.exe -std='c99'