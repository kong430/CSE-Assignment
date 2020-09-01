TARGET = reader_Aprocess writer_Bprocess

all : $(TARGET)

program1 : reader_Aprocess.c
	gcc -o reader_Aprocess reader_Aprocess.c

program2 : writer_Aprocess.c
	gcc -o writer_Bprocess writer_Bprocess.c

clean:
	rm $(TARGET)
