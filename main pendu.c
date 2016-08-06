/*
 * El Alalmi Aymane
 * The Game of pendu
 * Made with LOVE <3
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>

# define size 20

void play (void);
void add_word (void);
void print_files(void);
void show_words (void);
void fill_array (void);

char words[20][size], arr[size], username[20];
int line, coun_words, count, wrong_move, moves;
FILE *input, *output;

int main (void){
	int choiceMenu;
	char try_again;

	system("COLOR F2");
	printf("\n***** Pendu *****\n");

	do{
		fill_array();
		printf("Press 1. Play\nPress 2. add word\nPress 3.Exit\n >> "); // print the menu
		scanf("%d", &choiceMenu);

		switch (choiceMenu){
			case 1:
				do{
					play();

					printf("Try again !! (y/n) >> ");
					scanf("%c", &try_again); // ask to play again
				}while(try_again == 'y');
				break;
			case 2:
				add_word(); // add new words
				break;
		}
	}while(choiceMenu != 3);

	printf("***** thank you for your visit !! *****\n");
	return 0;
}

void play (void){
	int i, flag = 0;
	char c; 

	wrong_move = 0;
	moves = 0;

	
	getchar();
	printf("Please nenter your username >> "); gets(username);
	do{
		printf("Please enter a number >> ");
	}while(scanf("%d", &line) != 1);// choose a word from the database
	getchar();
	printf("%s\n", words[line]);

	for(i=0; i < strlen(words[line]); i++){ // fill the arr with the '-'
		arr[i] = '-';
	}

	do{
		printf("Enter a letter >> "); scanf("%c", &c); 
		getchar();
		moves++;

		for(i = 0; i < strlen(words[line]); i++){
			if(c == words[line][i]){ // check if the letter is right in the chosen word
				arr[i] = c; // write the right lette in the arr
				flag++;
			}
		}
		if(flag != 0)
			wrong_move++; // count the wrong letters given by the player
		printf("%s\n", arr); // print the arr to know how many letter left and display the letters that are known so far
	}while(strcmp(arr, words[line]) != 0);  // check if the word is complet

	if(strcmp(arr, words[line]) == 0)
		printf("Done !! \nYou did %d wrong moves in %d moves!!\n", wrong_move, moves);
	print_files();
}

void add_word (void){
	char other, new_word[size];
	int i, j, flag;
	input = fopen("input.txt", "a");
	do{		
		printf("New word N° %d>> ", count+1);
		scanf("%s", &new_word); // ask for the new word
		getchar();

		for (j = 0; j < coun_words; ++j){   // check if the word doesn't already exist or exit the function
			if(strcmp(new_word, words[j]) == 0){
				flag = 1;
				break;
			}
		}	
		
		if(flag == 1)
			printf("This word already exisxts !!");
		
		else if(flag == 0){
			coun_words++;
			strcpy(words[coun_words], new_word);	
		}

		fprintf(input, "%s\n", new_word);

		printf("An other word (y/n) >> ");
		scanf("%c", &other);
		getchar();
	}while(other == 'y');
	
	fclose(input);
}

void fill_array (void){
	int i;
	count = 0;
	input = fopen("input.txt", "r");
	
	for (i = 0; !feof(input); ++i){
		fscanf(input, "%s", &words[i]);
		count++;
	}

	printf("words --> \n");
	for(i=0; i<count-1; i++)
		printf("%d %s\n", i, words[i]);
	coun_words = count;
	
	fclose(input);
}

void print_files (void){
	int i;
	output = fopen("output.txt", "a");
	fprintf(output, "%s %d %d \n", username, moves, wrong_move);
	fclose(output);
}
