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

//sorting:
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
    int numOfPlaylists = 0;
    int *pNumOfPlaylists = &numOfPlaylists;
    Playlist *playlists = (Playlist*)calloc(0,sizeof(Playlist));

    int choice = 1;
    
    do
    {
        printPlaylistsMenu();

        if (scanf("%d", &choice))
        {
            switch (choice)
            {
            case 1: {
                watchPlaylists(pNumOfPlaylists,&playlists);
                break;
            }
            case 2: {
                addPlaylist(pNumOfPlaylists,&playlists);
                break;
            }
            case 3:
                deletePlaylist(pNumOfPlaylists,&playlists);
                break;
            case 4:
                deleteAll(pNumOfPlaylists,&playlists);
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
    *numOfPlaylists +=1;
    *playlists = realloc(*playlists,(*numOfPlaylists) * sizeof(Playlist));
    if (!(*playlists)) {
        printf("didnt allocate memory\n");
        exit(1);}
    printf("Enter playlist's name:\n");
    (*playlists)[*numOfPlaylists-1].name = stringToPointer();
    if (!(*playlists)[*numOfPlaylists-1].name){
        printf("Failed allocating memory for playlist name\n");
    }
    (*playlists)[*numOfPlaylists-1].songs=NULL;
    (*playlists)[*numOfPlaylists-1].songsNum=0;
}


char *stringToPointer(){
    char currentChar ='\0';
    char *stringPointer;
    int counter = 0;

    stringPointer =(char*)malloc(sizeof(char));
    if (!stringPointer){
        printf("Initial DMA failed\n");
        return 0;
    }
    int flag=1;
    while (flag){
        scanf("%c", &currentChar);
        if (currentChar == '\n') break;
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
    int watchPlaylistsIsActive = 1;
    while (watchPlaylistsIsActive){
        printf("Choose a playlist:\n");
        if (*numOfPlaylists == 0){
            printf("\t1. Back to main menu\n");
        }
        else {
            for (int i=0;i<*numOfPlaylists;i++){
                printf("\t%d. %s\n",i+1,(*playlists)[i].name);
            };
            printf("\t%d. Back to main menu\n", *numOfPlaylists+1);
        }

        int chosenPlaylist;
        scanf("%d",&chosenPlaylist);
        while (chosenPlaylist<1 || chosenPlaylist > *numOfPlaylists+1){
            printf("Invalid option\n");
            scanf("%d",&chosenPlaylist);
        }
        if (chosenPlaylist == *numOfPlaylists+1){
            return;
        }
        printf("playlist %s:\n",(*playlists)[chosenPlaylist-1].name);//
        int playlistIsActive =1;
        while (playlistIsActive){
            int playlistInteraction;
            printPlaylistOptions();
            scanf("%d",&playlistInteraction);
            while (playlistInteraction<1 || playlistInteraction > 6){
                printf("Invalid option\n");
                scanf("%d",&playlistInteraction);
            }
            switch (playlistInteraction)
            {
            case 1:
                displayPlaylist(chosenPlaylist,*playlists);
                break;
            case 2:
                addSong(chosenPlaylist,*playlists);
                break;
            case 3: 
                deleteSong(chosenPlaylist,*playlists);
                break;
            case 4:
                sortPlaylist(chosenPlaylist,*playlists);
                break;
            case 5:
                playIntirePlaylist(chosenPlaylist,*playlists);
                break;
            case 6:
                playlistIsActive=0;
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
    Playlist *currentPlaylist = &playlists[playlistIndex-1];
    int numOfSongs = currentPlaylist->songsNum;
    for (int i=0;i<numOfSongs;i++){
        printf("%d.  Title: %s\n",i+1,currentPlaylist->songs[i]->title);
        printf("    Artist: %s\n",currentPlaylist->songs[i]->artist);
        printf("    Released: %d\n",currentPlaylist->songs[i]->year);
        printf("    Streams: %d\n",currentPlaylist->songs[i]->streams);
    }
    int activeStreaming = 1;
    while (activeStreaming){
        printf("choose a song to play, or 0 to quit:\n");
        int songToPlay;
        scanf("%d",&songToPlay);
        if (songToPlay==0){
            activeStreaming=0;
        }
        else if (songToPlay>=1 && songToPlay<=numOfSongs){
            printf("Now playing %s:\n",currentPlaylist->songs[songToPlay-1]->title);
            printf("$ %s $\n",currentPlaylist->songs[songToPlay-1]->lyrics);
            currentPlaylist->songs[songToPlay-1]->streams++;
        }
        else {
            printf("Invalid input\n");
        }
        
    }
}

void playIntirePlaylist(int chosenPlaylist, Playlist *playlists){
    Playlist *currentPlaylist = &playlists[chosenPlaylist-1];
    int numOfSongs = currentPlaylist->songsNum;

    for (int i=0;i<numOfSongs;i++){
        printf("Now playing %s:\n",currentPlaylist->songs[i]->title);
        printf("$ %s $\n",currentPlaylist->songs[i]->lyrics);
        currentPlaylist->songs[i]->streams++;
        printf("\n");
    }
}

void addSong(int playlistIndex, Playlist *playlists){
    scanf("%*[^ \n]");
    scanf("%*c");
    playlistIndex-=1;
    Playlist *currentPlaylist = &playlists[playlistIndex];
    
    if (currentPlaylist->songsNum == 0){
        currentPlaylist->songs = malloc(sizeof(Song*));
    }
    else {
        currentPlaylist->songs = realloc(currentPlaylist->songs,(currentPlaylist->songsNum+1)*sizeof(Song*));
    }
    if (!currentPlaylist->songs){
        printf("Memory allocation failed\n");
        return;
    }

    currentPlaylist->songs[currentPlaylist->songsNum] = malloc(sizeof(Song));
    if (!currentPlaylist->songs[currentPlaylist->songsNum]){
        printf("Could not find memory for the songs.\n");
        return;
    }
    
    printf("Enter song's details\n");
    printf("Title:\n");
    currentPlaylist->songs[currentPlaylist->songsNum]->title = stringToPointer();
    printf("Artist:\n");
    currentPlaylist->songs[currentPlaylist->songsNum]->artist = stringToPointer();
    printf("Year of release:\n");
    int year;
    scanf("%d",&year);
    currentPlaylist->songs[currentPlaylist->songsNum]->year = year;
    scanf("%*[^ \n]");
    scanf("%*c");
    printf("Lyrics:\n");
    currentPlaylist->songs[currentPlaylist->songsNum]->lyrics = stringToPointer();
    currentPlaylist->songs[currentPlaylist->songsNum]->streams = 0;
    
    currentPlaylist->songsNum++;
}

void sortPlaylist(int chosenPlaylist, Playlist *playlists){
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
    Playlist *currentPlaylist = &playlists[chosenplaylist-1];
    int numOfSongs = currentPlaylist->songsNum;
    //using bubble sort since we dont care about efficiency
    for (int i=0; i<numOfSongs-1;i++){
        for (int j=0; j< numOfSongs - 1 - i;j++){
            if (currentPlaylist->songs[j]->year > currentPlaylist->songs[j+1]->year){
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
            if (strcmp(currentPlaylist->songs[j]->title,currentPlaylist->songs[j+1]->title)){
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
    // int numOfSongs = playlists[playlistIndex-1].songsNum;
    Playlist *currentPlaylist = &playlists[playlistIndex-1];
    int numOfSongs = currentPlaylist->songsNum;
    for (int i=0;i<numOfSongs;i++){
        printf("%d.  Title: %s\n",i+1,currentPlaylist->songs[i]->title);
        printf("    Artist: %s\n",currentPlaylist->songs[i]->artist);
        printf("    Released: %d\n",currentPlaylist->songs[i]->year);
        printf("    Streams: %d\n",currentPlaylist->songs[i]->streams);
    }
    printf("choose a song to delete, or 0 to quit:\n");
    int deleteChoice;
    scanf("%d",&deleteChoice);
    
    if (deleteChoice == 0){
        return;
    }

    freeSong(deleteChoice-1,playlistIndex,playlists);
    deleteChoice--; //adjust to array indexing
    //moving all the songs ahead one spot back 
    for (int i=deleteChoice; i<currentPlaylist->songsNum-1;i++){
        currentPlaylist->songs[i] = currentPlaylist->songs[i+1];
    }
    currentPlaylist->songsNum-=1;

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

    free (currentSong->artist);
    free (currentSong->lyrics);
    free (currentSong->title);
    free (currentSong);
}

void deletePlaylist(int *pNumOfPlaylists, Playlist **playlists){
    
    printf("Choose a playlist:\n");
    for (int i=0;i<*pNumOfPlaylists;i++){
        printf("\t%d. %s\n",i+1,(*playlists)[i].name);
    };
    printf("\t%d. Back to main menu\n", *pNumOfPlaylists+1);
    int chosenPlaylist;
    scanf("%d",&chosenPlaylist);
    if (*pNumOfPlaylists == 0 && chosenPlaylist == 1){
        return;
    }
    while (chosenPlaylist<=0 || chosenPlaylist>*pNumOfPlaylists)
    {
        printf("Invalid option\n");
        printf("Choose a playlist:\n");
        scanf("%d",&chosenPlaylist);
    }
    if (chosenPlaylist == *pNumOfPlaylists+1) return;
    // Playlist *playlistToDelete = &(*playlists[chosenPlaylist-1]);
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
    free(currentPlaylist->name);
    free(currentPlaylist->songs);
}

void deleteAll(int *pNumOfPlaylists, Playlist **playlists){
    for (int i=0;i<*pNumOfPlaylists;i++){
        freePlaylist(i,*playlists);
    }
    free (*playlists);
}