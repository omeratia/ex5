/******************
Name: Omer Atia
ID: 206667958
Assignment:
*******************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Song {
    char* title;
    char* artist;
    int year;
    char* lyrics;
    int streams;
} Song;

typedef struct Playlist {
    char* name;
    Song** songs;
    int songsNum;
} Playlist;

char *stringToPointer();
void printPlaylistsMenu();
void addPlaylist(int *numOfPlaylists, Playlist **playlists);
void watchPlaylists(int *numOfPlaylists, Playlist **playlists);
void printPlaylistOptions();
void addSong(int playlistIndex, Playlist *playlists);
void displayPlaylist(int playlistIndex, Playlist *playlists);
void playIntirePlaylist(int chosenPlaylist, Playlist *playlists);
void sortByAlphabetically(int chosenplaylist, Playlist *playlists);
void sortByStreamsDescending(int chosenplaylist, Playlist *playlists);
void sortByStreamsAscending(int chosenplaylist, Playlist *playlists);
void sortByYear(int chosenplaylist, Playlist *playlists);
void songsSwapping(Song** first, Song** second);
void sortPlaylist(int chosenPlaylist, Playlist *playlists);
void deleteSong(int playlistIndex, Playlist *playlists);
void freeSong(int songIndex,int playlistIndex, Playlist *playlists);
void freePlaylist(int playlistIndex, Playlist *playlists);
void deletePlaylist(int *pNumOfPlaylists, Playlist **playlists);
void deleteAll(int *pNumOfPlaylists, Playlist **playlists);


int main() {
    int numOfPlaylists = 0; //keep track of the current num of playlists
    int *pNumOfPlaylists = &numOfPlaylists; //pointer so we can adjust the
    Playlist *playlists = (Playlist*)calloc(0,sizeof(Playlist)); //allocation for our playlists array

    int choice = 1; //for the menu 
    
    do
    {
        printPlaylistsMenu();

        if (scanf("%d", &choice))
        {
            switch (choice)
            {
            case 1: {
                watchPlaylists(pNumOfPlaylists,&playlists); //displays the current playlists
                break;
            }
            case 2: {
                addPlaylist(pNumOfPlaylists,&playlists); //option to add new playlist
                break;
            }
            case 3:
                deletePlaylist(pNumOfPlaylists,&playlists); //removing playlist
                break;
            case 4:
                deleteAll(pNumOfPlaylists,&playlists); //deleting all and freeing all memory before exiting
                printf("Goodbye!\n");
                return 1;
            default:
                break;
            }
        }
        else
        {
            scanf("%*s");
        }

    } while (choice != 4);


    printf("Goodbye!\n");  
}




void printPlaylistsMenu() {
    printf("Please Choose:\n"); 
    printf("\t1. Watch playlists\n\t2. Add playlist\n\t3. Remove playlist\n\t4. exit\n");   
}





void addPlaylist(int *numOfPlaylists, Playlist **playlists){
    scanf("%*[^ \n]");
    scanf("%*c");
    *numOfPlaylists +=1; //increasing the number of playlists since we adding one
    *playlists = realloc(*playlists,(*numOfPlaylists) * sizeof(Playlist)); //reallocing to a bigger memory location,
    //by a size of one playlist
    if (!(*playlists)) {
        //exiting if reallocing failed
        printf("didnt allocate memory\n");
        exit(1);}
    printf("Enter playlist's name:\n");
    (*playlists)[*numOfPlaylists-1].name = stringToPointer();
    //using this function to get a string without knowing the length of it. returns a char pointer that goes
    //into our playlist.name
    if (!(*playlists)[*numOfPlaylists-1].name){
        printf("Failed allocating memory for playlist name\n");
        exit(1);
    }
    (*playlists)[*numOfPlaylists-1].songs=NULL; //starting value as null since no songs yet
    (*playlists)[*numOfPlaylists-1].songsNum=0; //num of songs initialized at 0 
}


char *stringToPointer(){
    //this function will return a char*, hence a string, every time we need to recieve a string input
    //from our user without knowing the size of it
    char currentChar ='\0'; //starting at 0 so we will enter the loop
    char *stringPointer; //the pointer that will be returned
    int counter = 0; // counter to keep track of the memory we need

    stringPointer =(char*)malloc(sizeof(char)); //starting at a pointer for a single char
    if (!stringPointer){
        //exiting if malloc failed
        printf("Initial DMA failed\n");
        return 0;
    }
    int flag=1;
    //flag to keep the loop going
    while (flag){
        //each time getting one char from the buffer
        scanf("%c", &currentChar);
        //if its /n we need to exit because the term ended (or we never had a term at all)
        if (currentChar == '\n') break;
        //if we didnt break it means we recicved a legit char, reallocing so we can place her in our
        //char pointer
        stringPointer = (char*)realloc(stringPointer, (counter+1)* sizeof(char));
        if (!stringPointer){
        printf("DMA failed\n");
        return 0;
    }
        stringPointer[counter] = currentChar;
        counter++;
    }
    stringPointer = (char*)realloc(stringPointer, (counter + 1) * sizeof(char));
    stringPointer[counter] = '\0';
    return stringPointer;
}

void watchPlaylists(int *numOfPlaylists, Playlist **playlists){
    //function for the sub-menu of iteracting with the playlists
    int watchPlaylistsIsActive = 1;
    while (watchPlaylistsIsActive){
        printf("Choose a playlist:\n");
        if (*numOfPlaylists == 0){
            //if we dont have playlists, only option is going back to the menu
            printf("\t1. Back to main menu\n");
        }
        else {
            //printing all playlists by order then offering to go back to the menu
            for (int i=0;i<*numOfPlaylists;i++){
                printf("\t%d. %s\n",i+1,(*playlists)[i].name);
            };
            printf("\t%d. Back to main menu\n", *numOfPlaylists+1);
        }

        int chosenPlaylist;
        scanf("%d",&chosenPlaylist);
        while (chosenPlaylist<1 || chosenPlaylist > *numOfPlaylists+1){
            //term checking for invalid playlist number
            printf("Invalid option\n");
            scanf("%d",&chosenPlaylist);
        }
        if (chosenPlaylist == *numOfPlaylists+1){
            //option of going back to main menu
            return;
        }
        printf("playlist %s:\n",(*playlists)[chosenPlaylist-1].name);
        int playlistIsActive =1;
        //pointer to keep track if the user still interacts with the chosen playlist
        while (playlistIsActive){
            int playlistInteraction;
            //printing all options for the playlist
            printPlaylistOptions();
            scanf("%d",&playlistInteraction);
            while (playlistInteraction<1 || playlistInteraction > 6){
                //term checking for invalid inputs
                printf("Invalid option\n");
                scanf("%d",&playlistInteraction);
            }
            switch (playlistInteraction)
            {
            case 1:
                displayPlaylist(chosenPlaylist,*playlists); //showing all tracks
                break;
            case 2:
                addSong(chosenPlaylist,*playlists); //adding new song to the playlist
                break;
            case 3: 
                deleteSong(chosenPlaylist,*playlists); //removing song from the playlist
                break;
            case 4:
                sortPlaylist(chosenPlaylist,*playlists); //all of our sorting options
                break;
            case 5:
                playIntirePlaylist(chosenPlaylist,*playlists); //playing all songs in order
                break;
            case 6:
                playlistIsActive=0;//exiting this current playlist
                break;
            default:
                break;
            }
        }
    }
}

void printPlaylistOptions(){
    printf("\t1. Show Playlist\n");
    printf("\t2. Add Song\n");
    printf("\t3. Delete Song\n");
    printf("\t4. Sort\n");
    printf("\t5. Play\n");
    printf("\t6. exit\n");
}

void displayPlaylist(int playlistIndex, Playlist *playlists){
    //creating a pointer to the current playlist inside our playlist array for convinience of code 
    Playlist *currentPlaylist = &playlists[playlistIndex-1];
    //keep track of num of songs
    int numOfSongs = currentPlaylist->songsNum;
    //printing details for every song in the playlist in order
    for (int i=0;i<numOfSongs;i++){
        printf("%d.  Title: %s\n",i+1,currentPlaylist->songs[i]->title);
        printf("    Artist: %s\n",currentPlaylist->songs[i]->artist);
        printf("    Released: %d\n",currentPlaylist->songs[i]->year);
        printf("    Streams: %d\n",currentPlaylist->songs[i]->streams);
    }
    //indicating for user playing songs
    int activeStreaming = 1;
    while (activeStreaming){
        printf("choose a song to play, or 0 to quit:\n");
        int songToPlay;
        scanf("%d",&songToPlay);
        if (songToPlay==0){
            //pressing 0 means to exit streaming, so we exit streaming mode
            activeStreaming=0;
        }
        else if (songToPlay>=1 && songToPlay<=numOfSongs){
            //if the input is valid we are printing the song in streaming shape
            printf("Now playing %s:\n",currentPlaylist->songs[songToPlay-1]->title);
            printf("$ %s $\n",currentPlaylist->songs[songToPlay-1]->lyrics);
            currentPlaylist->songs[songToPlay-1]->streams++; //increasing the streams count for the song
        }
        else {
            printf("Invalid input\n");
        }
        
    }
}

void playIntirePlaylist(int chosenPlaylist, Playlist *playlists){
    //function to play all songs in order. again using a pointer to the specific playlist.
    Playlist *currentPlaylist = &playlists[chosenPlaylist-1];
    //keep track of num of songs in the playlist so we'll know how much to play
    int numOfSongs = currentPlaylist->songsNum;

    for (int i=0;i<numOfSongs;i++){
        //printing all the songs in order
        printf("Now playing %s:\n",currentPlaylist->songs[i]->title);
        printf("$ %s $\n",currentPlaylist->songs[i]->lyrics);
        currentPlaylist->songs[i]->streams++; //increasing the stream count for each song
        printf("\n");
    }
}

void addSong(int playlistIndex, Playlist *playlists){
    //adding single song to a chosen playlist
    scanf("%*[^ \n]");
    scanf("%*c");
    playlistIndex-=1; //adjusting to array indexing
    Playlist *currentPlaylist = &playlists[playlistIndex]; //again pointer for convinience
    
    if (currentPlaylist->songsNum == 0){
        //if we dont have songs yet, pointer is null so we shall malloc space for a single song pointer
        currentPlaylist->songs = malloc(sizeof(Song*));
    }
    else {
        //increasing using malloc the size of songs by one more pointer
        currentPlaylist->songs = realloc(currentPlaylist->songs,(currentPlaylist->songsNum+1)*sizeof(Song*));
    }
    if (!currentPlaylist->songs){
        //exiting if alloation failed
        printf("Memory allocation failed\n");
        exit(1);
    }
    //now are going to songs inside the playlist and adjusting one more song space in the songs array
    currentPlaylist->songs[currentPlaylist->songsNum] = malloc(sizeof(Song));
    //exiting if failed allocating for the songs
    if (!currentPlaylist->songs[currentPlaylist->songsNum]){
        printf("Could not find memory for the songs.\n");
        exit(1);
    }
    
    printf("Enter song's details\n");
    printf("Title:\n");
    //using our string to pointer func that return char* to get the input for the title
    currentPlaylist->songs[currentPlaylist->songsNum]->title = stringToPointer();
    printf("Artist:\n");
    //using our string to pointer func that return char* to get the input for the artist
    currentPlaylist->songs[currentPlaylist->songsNum]->artist = stringToPointer();
    printf("Year of release:\n");
    //recieving year input (as integer)
    int year;
    scanf("%d",&year);
    currentPlaylist->songs[currentPlaylist->songsNum]->year = year;
    scanf("%*[^ \n]");
    scanf("%*c");
    printf("Lyrics:\n");
    //using our string to pointer func that return char* to get the input for the lyrics
    currentPlaylist->songs[currentPlaylist->songsNum]->lyrics = stringToPointer();
    currentPlaylist->songs[currentPlaylist->songsNum]->streams = 0; //initializing streams of the songs at 0
    
    currentPlaylist->songsNum++; //increasing the songs count for the playlist
}

void sortPlaylist(int chosenPlaylist, Playlist *playlists){
    //printing all sorting options
    printf("choose:\n");
    printf("1. sort by year\n");
    printf("2. sort by streams - ascending order\n");
    printf("3. sort by streams - descending order\n");
    printf("4. sort alphabetically\n");
    int sortingChoice;
    scanf("%d",&sortingChoice);
    switch (sortingChoice)
    {
    case 1:
        sortByYear(chosenPlaylist,playlists);
        break;
    case 2:
        sortByStreamsAscending(chosenPlaylist,playlists);
        break;
    case 3:
        sortByStreamsDescending(chosenPlaylist,playlists);
        break;
    case 4:
        sortByAlphabetically(chosenPlaylist,playlists);
        break;
    default:
        sortByAlphabetically(chosenPlaylist,playlists);
        break;
    }

}

void sortByYear(int chosenplaylist, Playlist *playlists){
    //creating pointer to our playlist
    Playlist *currentPlaylist = &playlists[chosenplaylist-1];
    int numOfSongs = currentPlaylist->songsNum;
    //using bubble sort since we dont care about efficiency
    for (int i=0; i<numOfSongs-1;i++){
        for (int j=0; j< numOfSongs - 1 - i;j++){
            if (currentPlaylist->songs[j]->year > currentPlaylist->songs[j+1]->year){
                //if a song was released later than the nexy songs, we are switching them in the array
                songsSwapping(&currentPlaylist->songs[j],&currentPlaylist->songs[j+1]);
            }
        }
    }
    printf("sorted\n");
}

void sortByStreamsAscending(int chosenplaylist, Playlist *playlists){
    Playlist *currentPlaylist = &playlists[chosenplaylist-1];
    int numOfSongs = currentPlaylist->songsNum;
    //using bubble sort since we dont care about efficiency
    for (int i=0; i<numOfSongs-1;i++){
        for (int j=0; j< numOfSongs - 1 - i;j++){
            if (currentPlaylist->songs[j]->streams > currentPlaylist->songs[j+1]->streams){
                //if a current songs had been streamed more than a song after it in the playlist,
                //we are swtiching them
                songsSwapping(&currentPlaylist->songs[j],&currentPlaylist->songs[j+1]);
            }
        }
    }
    printf("sorted\n");
}

void sortByStreamsDescending(int chosenplaylist, Playlist *playlists){
    Playlist *currentPlaylist = &playlists[chosenplaylist-1];
    int numOfSongs = currentPlaylist->songsNum;
    //using bubble sort since we dont care about efficiency
    for (int i=0; i<numOfSongs-1;i++){
        for (int j=0; j< numOfSongs - 1 - i;j++){
            if (currentPlaylist->songs[j]->streams < currentPlaylist->songs[j+1]->streams){
                //if a current songs had been streamed more than a song before it in the playlist,
                //we are swtiching them
                songsSwapping(&currentPlaylist->songs[j],&currentPlaylist->songs[j+1]);
            }
        }
    }
    printf("sorted\n");
}

void sortByAlphabetically(int chosenplaylist, Playlist *playlists){
    Playlist *currentPlaylist = &playlists[chosenplaylist-1];
    int numOfSongs = currentPlaylist->songsNum;
    //using bubble sort since we dont care about efficiency
    for (int i=0; i<numOfSongs-1;i++){
        for (int j=0; j< numOfSongs - 1 - i;j++){
            //using strcmp to determine if a songs title is alphabetically 'bigger' than the next song in the 
            //array, switching them if so
            if (strcmp(currentPlaylist->songs[j]->title,currentPlaylist->songs[j+1]->title)>0){
                songsSwapping(&currentPlaylist->songs[j],&currentPlaylist->songs[j+1]);
            }
        }
    }
    printf("sorted\n");
}

void songsSwapping(Song** first, Song** second){
    //function to swap songs pointers without losing memory locations
    Song *temp = *first;
    //keeping track of the first song location
    *first = *second;
    //swapping
    *second = temp;
}

void deleteSong(int playlistIndex, Playlist *playlists){
    Playlist *currentPlaylist = &playlists[playlistIndex-1];
    int numOfSongs = currentPlaylist->songsNum;
    //displaying the user all of the songs 
    for (int i=0;i<numOfSongs;i++){
        printf("%d.  Title: %s\n",i+1,currentPlaylist->songs[i]->title);
        printf("    Artist: %s\n",currentPlaylist->songs[i]->artist);
        printf("    Released: %d\n",currentPlaylist->songs[i]->year);
        printf("    Streams: %d\n",currentPlaylist->songs[i]->streams);
    }
    printf("choose a song to delete, or 0 to quit:\n");
    int deleteChoice;
    scanf("%d",&deleteChoice);
    //inout check if the user wants to go back
    if (deleteChoice == 0){
        return;
    }
    //using the free song func that freeing all the heap memory allocated for a songs
    freeSong(deleteChoice-1,playlistIndex,playlists);
    deleteChoice--; //adjust to array indexing
    //moving all the songs ahead one spot back 
    for (int i=deleteChoice; i<currentPlaylist->songsNum-1;i++){
        currentPlaylist->songs[i] = currentPlaylist->songs[i+1];
    }
    currentPlaylist->songsNum-=1; //decreaing number of songs in the playlist

    currentPlaylist->songs = realloc(currentPlaylist->songs,(currentPlaylist->songsNum)*sizeof(Song*));
    //now to check the allocation works while there are at least one song in the playlist
    if (currentPlaylist->songs == NULL) {
        printf("DMA failed\n");
        exit(1);
    }
    printf("Song deleted successfully.\n");

}

void freeSong(int songIndex,int playlistIndex, Playlist *playlists){
    Playlist *currentPlaylist = &playlists[playlistIndex-1];
    Song *currentSong = currentPlaylist->songs[songIndex];

    free (currentSong->artist); //freeing the string
    free (currentSong->lyrics); //freeing string
    free (currentSong->title); //freeing string
    free (currentSong); //freeing the pointer to the song also from the heap
}

void deletePlaylist(int *pNumOfPlaylists, Playlist **playlists){
    
    printf("Choose a playlist:\n");
    for (int i=0;i<*pNumOfPlaylists;i++){
        //displaying all options 
        printf("\t%d. %s\n",i+1,(*playlists)[i].name);
    };
    printf("\t%d. Back to main menu\n", *pNumOfPlaylists+1);
    int chosenPlaylist;
    scanf("%d",&chosenPlaylist);
    //checking validation of input, if the user wants to go back
    if (*pNumOfPlaylists == 0 && chosenPlaylist == 1){
        return;
    }
    while (chosenPlaylist<=0 || chosenPlaylist>*pNumOfPlaylists)
    {
        //input validation
        printf("Invalid option\n");
        printf("Choose a playlist:\n");
        scanf("%d",&chosenPlaylist);
    }
    if (chosenPlaylist == *pNumOfPlaylists+1) return;
    //freeing all the content of a plsylist and the playlist itself
    freePlaylist(chosenPlaylist,*playlists);
    (*pNumOfPlaylists)--; //decreasing number of playlists
    chosenPlaylist--; //adjust to array indexing
    for (int i=chosenPlaylist;i<*pNumOfPlaylists;i++){ //shifting the playlists ahead of the deleted one
        (*playlists)[i]=(*playlists)[i+1];
    }
    *playlists = realloc(*playlists, (*pNumOfPlaylists)*sizeof(Playlist));
    //checking the reallocation worked regard the fact we have at least one playlist left yet 
    if (*playlists == NULL && *pNumOfPlaylists>0){
        printf("DMA failed\n");
        exit(1);
    }
    printf("Playlist deleted.\n");
}

void freePlaylist(int playlistIndex, Playlist *playlists){
    //making the address easy to access
    Playlist *currentPlaylist = &playlists[playlistIndex-1];
    //getting the num of songs for the iterations
    int numOfSongs = currentPlaylist->songsNum;
    //aplying free song function for every song in the playlist
    for (int i=0; i<numOfSongs; i++){
        freeSong(i,playlistIndex,playlists);
    }
    free(currentPlaylist->name); //freeing string
    free(currentPlaylist->songs); //freeing string
}

void deleteAll(int *pNumOfPlaylists, Playlist **playlists){
    //function to apply when the user exits the program
    for (int i=0;i<*pNumOfPlaylists;i++){
        freePlaylist(i,*playlists); //applying free playlist to every playlist, this will also free
        //the songs content under this playlist
    }
    free (*playlists); //freeing the pointer to the playlists array
}