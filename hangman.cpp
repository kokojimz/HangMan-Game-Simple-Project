#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void BASEUP(int a,char* name,int dispScore) //tiang bagian atas
{
    if (a >= 0)
    {
        printf("  _____  %s\n",name);
        printf(" |     | Score : %d\n",dispScore);
    }
}

void BASEDOWN(int a) // tiang bagian bawah
{
    if (a >= 0)
    {
        printf("_|_\n");
    }
}

void BASEMID(int a)  //tiang dan orang tergantung
{
    if (a == 0)  
    {
        printf(" |\n"
               " |\n"
               " |\n"
               " |\n"
               " |\n");
    }

    else if (a == 1)
    {
        printf(" |     O  \n"
               " |\n"
               " |\n"
               " |\n"
               " |\n");
    }

    else if (a == 2)
    {
        printf(" |     O   \n"
               " |    /|\\ \n"
               " |\n"
               " |\n"
               " |\n");
    }

    else if (a == 3)
    {
        printf(" |     O   \n"
               " |    /|\\ \n"
               " |     |   \n"
               " |\n"
               " |\n");
    }

    else if (a == 4)
    {
        printf(" |     O   \n"
               " |    /|\\ \n"
               " |     |   \n"
               " |    / \\ \n"
               " |         \n");
    }
}

void DISPLAY(int a,char* name,int dispScore) //display gambar
{
    BASEUP(a,name,dispScore);
    BASEMID(a);
    BASEDOWN(a);
}

int update_score(char *filename, char *username, int new_score)  //lihat lalu meng-update score yang ada di file scores.txt
{
    FILE *fp = fopen(filename, "r+");
    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), fp)) 
    {
        char current_username[256];
        int current_score;
        sscanf(line, "%s %d", current_username, &current_score);
        int fin_score = current_score + new_score;
        if (strcmp(username, current_username) == 0) 
        {
            found = 1;
            fseek(fp, -strlen(line)-1, 1);
            fprintf(fp, "%s %d\n", username, fin_score);
            return fin_score;
        }
    }
    if (!found) 
    {
        fseek(fp, 0, 2);
        fprintf(fp, "%s %d\n", username, new_score);
    }
    fclose(fp);
    return 0;
}


int HANGMAN(char* word,char* name) 
{
  char wordtemp[100];
  char guess;
  int score;
  int wrong = 0;
  char file[] = "scores.txt";
  int dispScore = update_score(file, name, 0);
  for (int i = 0; i < strlen(word); i++) 
  {
    wordtemp[i] = '_';
  }
  wordtemp[strlen(word)] = '\0';
  while (wrong < 4) 
  {
    system("cls");
    DISPLAY(wrong,name,dispScore);
    printf("%s", wordtemp);
    printf("\n\nGuess a letter: ");
    scanf(" %c", &guess);
    guess = tolower(guess);
    int correct = 0;
    for (int i = 0; i < strlen(word); i++) 
    {
      if (tolower(word[i]) == guess) 
      {
        wordtemp[i] = word[i];
        correct = 1;
      }
    }
    if (correct) 
    {
        wrong += 0;
    } else 
    {
        wrong++;
    }

    if (strcmp(word, wordtemp) == 0) 
    {
        system("cls");
        int dispScore = update_score("scores.txt", name, 100);
        DISPLAY(wrong,name,dispScore);
        printf("\nYou win!\nThe word was \"%s\"", word);
        char line[256];
        int found = 0;
        FILE *fp = fopen(file, "r+");
        while (fgets(line, sizeof(line), fp)) 
        {
            char current_username[256];
            int current_score;
            sscanf(line, "%s %d", current_username, &current_score);
            int fin_score = current_score + 100;
            if (strcmp(name, current_username) == 0) 
            {
                found = 1;
                fseek(fp, -strlen(line)-1, 1);
                fprintf(fp, "%s %d\n", name, fin_score);
                break;
            }
        }
        fclose(fp);
        return score = 100;
    }
  }
  if (wrong == 4) 
  {
    system("cls");
    int dispScore = update_score(file, name, 0);
    DISPLAY(wrong,name,dispScore);
    printf("\nYou lost\nThe word was \"%s\"", word);
    return score = 0;
  }
}

char **reservoir_sample(const char *filename, int count) //https://stackoverflow.com/questions/43214157/c-get-random-words-from-text-a-file
{ // ngebuat array bernama line yang akan nampung string sebanyak variable count
    FILE *file;
    char **lines;
    char buf[1525];
    int i, n;
    file = fopen(filename, "r");
    lines = (char **)calloc(count, sizeof(char *));
    for (n = 1; fgets(buf, 1525, file); n++) 
    {
        if (n <= count) 
        {
            lines[n - 1] = strdup(buf);
        } else 
        {
            i = rand() % n;
            if (i < count) 
            {
                free(lines[i]);
                lines[i] = strdup(buf);
            }
        }
    }
    fclose(file);
    return lines;
}

void RUN(char *name)
{
    srand(time(0));
    int random = (rand() % 1525);
    char** words = reservoir_sample("words.txt",random);
    int random2 = rand();
    while (random2 >= random)
    {
        random2 = rand();
    }
    char* word = words[random2];
    printf("%s",word);
    int len = strcspn(word, "\n");
    word[len] = '\0';
    int score = HANGMAN(word,name);
    char file[] = "scores.txt";
    update_score(file, name, score);
}
void loading(){
    int i,j,a;
    printf("Loading");

    for(i=0;i<=6;i++)
    {
        for(j=0;j<100000000;j++) a=j;
        printf(".");
    }
}
void logo1() //desain logo
{
    printf("===================Game===================\n");    //Sumber referensi pembuatan logo home page : patorjk.com//
    printf(" _    _                              __  __ \n"            
            "| |  | |                            |  \\/  |\n"           
            "| |__| | __ _ _ __   __ _   ______  | \\  / | __ _ _ __  \n"
            "|  __  |/ _` | '_ \\ / _` | |______| | |\\/| |/ _` | '_ \\ \n"
            "| |  | | (_| | | | | (_| |          | |  | | (_| | | | |\n"
            "|_|  |_|\\__,_|_| |_|\\__, |          |_|  |_|\\__,_|_| |_|\n"
            "                     __/ |                              \n"
            "                     |___/                              \n");
}
void home_page() //menggunakan logo di homepage
{
    system("cls");
    logo1();
    Sleep(1000);
    loading();
}

void closing() //desain logo closing
{
    printf(" _______ _    _          _   _ _  __ __     ______  _    _ \n"
           "|__   __| |  | |   /\\   | \\ | | |/ / \\ \\   / / __ \\| |  | |\n"
           "   | |  | |__| |  /  \\  |  \\| | ' /   \\ \\_/ / |  | | |  | |\n"
           "   | |  |  __  | / /\\ \\ | . ` |  <     \\   /| |  | | |  | |\n"
           "   | |  | |  | |/ ____ \\| |\\  | . \\     | | | |__| | |__| |\n"
           "   |_|  |_|  |_/_/    \\_\\_| \\_|_|\\_\\    |_|  \\____/ \\____/ \n"
           "                                                           \n");
}

void credit() //credit dengan jeda sleep(500)
{
    printf("Created BY : \n\n");
    printf("Muhammad Bagier  Asseggaf (2602134531)\n");
    Sleep(500);
    printf("Reynaldy Marchell Bagas Adji (2602141846)\n");
    Sleep(500);
    printf("Muhammad Ziddan Azzaky (2602119915)\n");
    Sleep(500);
    printf("Bryan Ferdinand Teddy Fiersdy (2602075296)\n");
    Sleep(500);
    printf("Daffa Pandora Elfarisin  (2602138151)\n");
    Sleep(500);
    printf("Rafael Sani Valentino Prahastra (2602175065)\n");
    Sleep(500);
}

int compare(const void *a, const void *b) 
{
    const int *ia = (const int *)a;
    const int *ib = (const int *)b;
    return (*ib - *ia);
}

void sort_file(const char *file_name) 
{
    char line[100];
    int values[100];
    char *strings[100];
    int count = 0;
    FILE *file = fopen(file_name, "r");
    while (fgets(line, sizeof(line), file)) 
    {
        strings[count] = strdup(strtok(line, " "));
        values[count] = atoi(strtok(NULL, " "));
        count++;
    }
    fclose(file);
    qsort(values, count, sizeof(int), compare);
    file = fopen(file_name, "w");
    for (int i = 0; i < count; i++) 
    {
        printf("#%i %s %d\n", i+1, strings[i], values[i]);
        Sleep(500);
        fprintf(file, "%s %d\n", strings[i], values[i]);
    }
    fclose(file);
}
char *states(int a, char *user)
{
    int option;
    if (a == 1)
    {
        loading();
        system("cls");
        logo1();
        loading();
        RUN(user);
        printf("\nDo you want to play again? \n'1' to play again\n'2' to change user\n'0' to go back to the main menu\n");
        scanf("%i", &option);
        loading();
        system("cls");
    if (option == 2)
    {
        loading();
        system("cls");
        printf("\nEnter your username (Cannot contain spaces!!)\n");
        scanf("%s", user);
        system("cls");
        return(user);
    }else if (option == 1){
        states(1, user);
    }else{
        return user;
    }
    }
    if (a == 2)
    {
        system("cls");
        loading();
        system("cls");
        printf("Leaderboards\n");
        sort_file("scores.txt");
        system("pause");
        system("cls");
        return user;
    }
}

int main()
{
  home_page();
  int state = 1;
  char user[100];
  logo1();
  system("cls");
  logo1();
  printf("\nEnter your username (Cannot contain spaces!!)\n");
  scanf("%s", user);
  loading();
  system("cls");
  while (state != 0)
  {
    logo1();
    printf("Enter '1' to play hangman\n");
    printf("Enter '2' to view leaderboards\n");
    printf("Enter '0' to exit\n");
    scanf("%i", &state);
    states(state,user);
  }
  loading();
  system("cls");
  closing();
  credit();
}