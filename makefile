guiBot: bot.o desktop.o
	gcc -g bot.o desktop.o -lX11 -lXtst -o guiBot
bot.o: guiBot.c
	gcc -g -c guiBot.c -o bot.o -lX11 -lXtst
desktop.o: desktop.c
	gcc -g -c desktop.c -o desktop.o -lX11
clean:
	rm guiBot bot.o desktop.o
