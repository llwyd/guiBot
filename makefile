guiBot: bot.o desktop.o
	gcc -g bot.o desktop.o -lX11 -o guiBot
bot.o: guiBot.c
	gcc -c guiBot.c -o bot.o -lX11
desktop.o: desktop.c
	gcc -c desktop.c -o desktop.o -lX11
clean:
	rm guiBot bot.o desktop.o
