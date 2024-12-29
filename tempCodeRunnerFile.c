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
        int playlistIsActive =1;
        while (playlistIsActive){
            int playlistInteraction;
            printf("playlist %s:\n",(*playlists)[chosenPlaylist-1].name);
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