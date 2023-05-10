#include "MusicStream.h"

#include <iostream>

void MusicStream::addProfile(const std::string &email, const std::string &username, SubscriptionPlan plan) {
    /* TODO */
    profiles.insertAtTheEnd(Profile(email,username,plan));
}

void MusicStream::deleteProfile(const std::string &email) {
    /* TODO */
    Node<Profile> *temp = profiles.getFirstNode();    
    for(int i=0; i<profiles.getSize();i++){
        if(temp->data.getEmail() == email){            
            break;
        }
        temp = temp->next;
    }    
    Node<Profile *> *followinglist = temp->data.getFollowings().getFirstNode();
    Node<Profile *> *followerslist = temp->data.getFollowers().getFirstNode();
    int n1 = temp->data.getFollowers().getSize();
    int n2 = temp->data.getFollowings().getSize();
    for(int z=0; z< n1;z++){
        followerslist->data->getFollowings().removeNode(&temp->data);
        followerslist= followerslist->next;
    }
    for(int j=0; j<n2;j++){
        followinglist->data->getFollowers().removeNode(&temp->data);
        followinglist = followinglist->next;
    }   
    temp->data.getFollowers().removeAllNodes();
    temp->data.getFollowings().removeAllNodes();
    temp->data.getPlaylists().removeAllNodes();
    profiles.removeNode(temp);
}

void MusicStream::addArtist(const std::string &artistName) {
    /* TODO */
    artists.insertAtTheEnd(Artist(artistName));
}

void MusicStream::addAlbum(const std::string &albumName, int artistId) {
    /* TODO */
    Album new_album  =Album(albumName);
    Node<Artist> *temp = artists.getFirstNode();
    albums.insertAtTheEnd(new_album);
    Album *curr = &albums.getLastNode()->data;
    for(int i=0; i<artists.getSize();i++){
        if(temp->data.getArtistId() == artistId){
            temp->data.addAlbum(curr);         
        }
        temp =temp->next;
    }    
}

void MusicStream::addSong(const std::string &songName, int songDuration, int albumId) {
    /* TODO */
    Song new_song =Song(songName,songDuration);
    Node<Album>* temp = albums.getFirstNode();
    songs.insertAtTheEnd(new_song);
    Song *curr = &songs.getLastNode()->data;
    for(int i=0;i< albums.getSize();i++){
        if(temp->data.getAlbumId() == albumId){
            temp->data.addSong(curr);
        }
        temp = temp->next;
    }
}

void MusicStream::followProfile(const std::string &email1, const std::string &email2) {
    /* TODO */
    Node<Profile> *temp = profiles.getFirstNode();
    Node<Profile> *temp1, *temp2;
    for(int i=0; i< profiles.getSize();i++){
        if(temp->data.getEmail() == email1){
            temp1 = temp;
        }
        if(temp->data.getEmail() == email2){
            temp2 = temp;
        }
        temp= temp->next;
    }
    temp1->data.followProfile(&temp2->data);
    temp2->data.getFollowers().insertAtTheEnd(&temp1->data);
}

void MusicStream::unfollowProfile(const std::string &email1, const std::string &email2) {
    /* TODO */
    Node<Profile> *temp = profiles.getFirstNode();
    Node<Profile> *temp1, *temp2;
    for(int i=0; i<profiles.getSize() ;i++){
        if(temp->data.getEmail() == email1){
            temp1 = temp;
        }
        if(temp->data.getEmail() == email2){
            temp2 = temp;
        }
        temp= temp->next;
    }
    temp1->data.unfollowProfile(&temp2->data);
    temp2->data.getFollowers().removeNode(&temp1->data);
}

void MusicStream::createPlaylist(const std::string &email, const std::string &playlistName) {
    /* TODO */
    Node<Profile> *temp = profiles.getFirstNode();
    for(int i=0; i< profiles.getSize();i++){
        if(temp->data.getEmail() == email){
            temp->data.createPlaylist(playlistName);
        }
        temp = temp->next;
    }

}

void MusicStream::deletePlaylist(const std::string &email, int playlistId) {
    /* TODO */
    Node<Profile> *temp = profiles.getFirstNode();
    for(int i=0; i< profiles.getSize();i++){
        if(temp->data.getEmail() == email){
            temp->data.deletePlaylist(playlistId);
            break;
        }
        temp = temp->next;
    }
}

void MusicStream::addSongToPlaylist(const std::string &email, int songId, int playlistId) {
    /* TODO */
    Node<Profile> *temp = profiles.getFirstNode();
    Node<Song> *curr= songs.getFirstNode();
    for(int j=0; j<songs.getSize();j++){
        if(curr->data.getSongId() == songId){
            break;
        }
        curr = curr->next;
    }
    for(int i=0; i< profiles.getSize();i++){
        if(temp->data.getEmail() == email){
            temp->data.addSongToPlaylist(&curr->data,playlistId);
        }
        temp = temp->next;
    }
}

void MusicStream::deleteSongFromPlaylist(const std::string &email, int songId, int playlistId) {
    /* TODO */
    Node<Profile> *temp = profiles.getFirstNode();    
    for(int i=0; i< profiles.getSize();i++){
        if(temp->data.getEmail() == email){            
            break;            
        }
        temp = temp->next;
    }

    LinkedList<Song *> currpl = temp->data.getPlaylist(playlistId)->getSongs(); 
    Node<Song*> *currs = currpl.getFirstNode();
    for(int j=0; j<currpl.getSize();j++){
        if(currs->data->getSongId() ==  songId){            
            break;
        }
        currs = currs->next;
    }
    temp->data.deleteSongFromPlaylist(currs->data,playlistId);    
}

LinkedList<Song *> MusicStream::playPlaylist(const std::string &email, Playlist *playlist) {
    /* TODO */
    LinkedList<Song *> songlist;
    Node<Profile> *temp = profiles.getFirstNode();
    for(int i=0; i< profiles.getSize();i++){
        if(temp->data.getEmail() == email){
            if(temp->data.getPlan() == premium){
                return playlist->getSongs();
            }
            else if(temp->data.getPlan() == free_of_charge){
                Node<Song *> *adsongs =  playlist->getSongs().getFirstNode();
                for(int j=0; j< playlist->getSongs().getSize();j++){
                    songlist.insertAtTheEnd(adsongs->data);
                    songlist.insertAtTheEnd(&Song::ADVERTISEMENT_SONG);
                    adsongs = adsongs->next;
                }
                return songlist;                
            }
        }
        temp =temp->next;
    }
}

Playlist *MusicStream::getPlaylist(const std::string &email, int playlistId) {
    /* TODO */
    Node<Profile> *temp = profiles.getFirstNode();
    for(int i =0; i<profiles.getSize(); i++){
        if(temp->data.getEmail() == email){
            return temp->data.getPlaylist(playlistId);
        }
        temp = temp->next;
    }
}

LinkedList<Playlist *> MusicStream::getSharedPlaylists(const std::string &email) {
    /* TODO */
    Node<Profile> *temp = profiles.getFirstNode();
    for(int i=0;i<profiles.getSize();i++){
        if(temp->data.getEmail() == email){
            return temp->data.getSharedPlaylists();
        }
        temp = temp->next;
    }
}

void MusicStream::shufflePlaylist(const std::string &email, int playlistId, int seed) {
    /* TODO */
    Node<Profile>* temp = profiles.getFirstNode();   
    for(int i=0;i<profiles.getSize();i++){
        if(temp->data.getEmail() == email){
            temp->data.shufflePlaylist(playlistId,seed);
            return ;
        }
        temp = temp->next;
    }
}

void MusicStream::sharePlaylist(const std::string &email, int playlistId) {
    /* TODO */
    Node<Profile>* temp = profiles.getFirstNode();   
    for(int i=0;i<profiles.getSize();i++){
        if(temp->data.getEmail() == email){
            temp->data.sharePlaylist(playlistId);
            return ;
        }
        temp = temp->next;
    }
}

void MusicStream::unsharePlaylist(const std::string &email, int playlistId) {
    /* TODO */
    Node<Profile>* temp = profiles.getFirstNode();    
    for(int i=0;i<profiles.getSize();i++){
        if(temp->data.getEmail() == email){
            temp->data.unsharePlaylist(playlistId);
            return ;
        }
        temp = temp->next;
    }
}

void MusicStream::subscribePremium(const std::string &email) {
    /* TODO */
    Node<Profile> *temp = profiles.getFirstNode();
    for(int i=0; i<profiles.getSize();i++){
        if(temp->data.getEmail() == email){
            temp->data.setPlan(premium);
            return;
        }
        temp = temp->next;
    }
}

void MusicStream::unsubscribePremium(const std::string &email) {
    /* TODO */
    Node<Profile> *temp = profiles.getFirstNode();
    for(int i=0; i<profiles.getSize();i++){
        if(temp->data.getEmail() == email){
            temp->data.setPlan(free_of_charge);
            return;
        }
        temp = temp->next;
    }
}

void MusicStream::print() const {
    std::cout << "# Printing the music stream ..." << std::endl;

    std::cout << "# Number of profiles is " << profiles.getSize() << ":" << std::endl;
    profiles.print();

    std::cout << "# Number of artists is " << artists.getSize() << ":" << std::endl;
    artists.print();

    std::cout << "# Number of albums is " << albums.getSize() << ":" << std::endl;
    albums.print();

    std::cout << "# Number of songs is " << songs.getSize() << ":" << std::endl;
    songs.print();

    std::cout << "# Printing is done." << std::endl;
}
