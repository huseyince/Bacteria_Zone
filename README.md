# Bacteria_Zone
You are going to write a program that will simulate a bacteria habitat. The parameters of your habitat will
be given in a text file (data.txt). Your program must read this file in text mode from your application folder. data.txt file includes information about your habitat and the bacteria capability to eat other bacteria.

Here is a short sample:

"""""data.txt dosyayı gelecek"""""

First section (bacteria: ) of the file gives the name of the bacteria separated by space. Second section
(rules: ) shows the eating rules. “A -> B” means A can eat B if it is in the growing area. Third section (size:
) gives the size of our habitat in matrix format. And the last section (start:) shows the starting position of
bacteria. We are going to simulate the life cycle of the habitat after n turn. Your program reads this file,
shows this information on the screen and reads the life turns (n) form user. After that the program
calculates the resulting habitat pattern on the screen.

Here is the four turns of our sample habitat.

"""""TABLOLAR""""""

In each turn the bacteria are multiply itself to neighbor cells. If the cell is occupied by other bacteria
according to the rules one bacteria eats the other one. The life cycle must be executed in the same order
that the bacteria written on the file. For example in our sample scenario first bacteria A multiply itself,
after B and at last C makes the multiplication.
