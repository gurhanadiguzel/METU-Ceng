#include "Profile.h"

Profile::Profile(const std::string &email, const std::string &username, SubscriptionPlan plan) {
    this->email = email;
    this->username = username;
    this->plan = plan;
}

const std::string &Profile::getUsername() const {
    return this->username;
}

const std::string &Profile::getEmail() const {
    return this->email;
}

SubscriptionPlan Profile::getPlan() const {
    return this->plan;
}

LinkedList<Playlist> &Profile::getPlaylists() {
    return this->playlists;
}

LinkedList<Profile *> &Profile::getFollowings() {
    return this->following;
}

LinkedList<Profile *> &Profile::getFollowers() {
    return this->followers;
}

void Profile::setPlan(SubscriptionPlan plan) {
    this->plan = plan;
}

void Profile::followProfile(Profile *profile) {
    /* TODO */
    this->following.insertAtTheEnd(profile);
}

void Profile::unfollowProfile(Profile *profile) {
    /* TODO */
    this->following.removeNode(profile);
}

void Profile::createPlaylist(const std::string &playlistName) {
    /* TODO */
    this->playlists.insertAtTheEnd(Playlist(playlistName));
}

void Profile::deletePlaylist(int playlistId) {
    /* TODO */
    Node<Playlist> *temp = playlists.getFirstNode();
    for(int i=0; i<playlists.getSize();i++){
        if(temp->data.getPlaylistId() == playlistId){
            playlists.removeNode(temp); 
            break;
        }
        temp = temp->next;
    }    
}

void Profile::addSongToPlaylist(Song *song, int playlistId) {
    /* TODO */
    Node<Playlist> *temp = playlists.getFirstNode();
    for(int i=0; i<playlists.getSize();i++){
        if(temp->data.getPlaylistId() == playlistId){
            temp->data.addSong(song);
        }
        temp = temp->next;
    }
}

void Profile::deleteSongFromPlaylist(Song *song, int playlistId) {
    /* TODO */
    Node<Playlist> *temp = playlists.getFirstNode();
    for(int i=0; i<playlists.getSize();i++){
        if(temp->data.getPlaylistId() == playlistId){
            temp->data.dropSong(song);
            break;
        }
        temp = temp->next;
    }
}

Playlist *Profile::getPlaylist(int playlistId) {
    /* TODO */
    Node<Playlist> *temp = playlists.getFirstNode();
    for(int i=0; i<playlists.getSize();i++){
        if(temp->data.getPlaylistId() == playlistId){
            return &temp->data;
        }
        temp = temp->next;
    }
}

LinkedList<Playlist *> Profile::getSharedPlaylists() {
    /* TODO */
    Node<Profile*> *following = this->getFollowings().getFirstNode();
    LinkedList<Playlist *> shared;
    Node<Playlist> *curr;
    for(int j=0; j<this->getFollowings().getSize();j++){
        curr = following->data->getPlaylists().getFirstNode();
        for(int i=0; i<following->data->getPlaylists().getSize();i++){
            if(curr->data.isShared()){
                shared.insertAtTheEnd(&curr->data);
            }
            curr = curr->next;
        }
        following = following->next;
    }    
    return shared;
}


void Profile::shufflePlaylist(int playlistId, int seed) {
    /* TODO */
    Node<Playlist> *temp = playlists.getFirstNode();
    for(int i=0; i<playlists.getSize();i++){
        if(temp->data.getPlaylistId() == playlistId){
            temp->data.shuffle(seed);
        }
        temp = temp->next;
    }
}

void Profile::sharePlaylist(int playlistId) {
    /* TODO */
    Node<Playlist> *temp = playlists.getFirstNode();
    for(int i=0; i<playlists.getSize();i++){
        if(temp->data.getPlaylistId() == playlistId){
            temp->data.setShared(true);
        }
        temp = temp->next;
    }
}

void Profile::unsharePlaylist(int playlistId) {
    /* TODO */
    Node<Playlist> *temp = playlists.getFirstNode();
    for(int i=0; i<playlists.getSize();i++){
        if(temp->data.getPlaylistId() == playlistId){
            temp->data.setShared(false);
        }
        temp = temp->next;
    }
}

bool Profile::operator==(const Profile &rhs) const {
    return this->email == rhs.email && this->username == rhs.username && this->plan == rhs.plan;
}

bool Profile::operator!=(const Profile &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Profile &profile) {
    os << "email: " << profile.email << " |";
    os << " username: " << profile.username << " |";
    if (profile.plan == free_of_charge) {
        os << " plan: " << "free_of_charge" << " |";
    } else if (profile.plan == premium) {
        os << " plan: " << "premium" << " |";
    } else {
        os << " plan: " << "undefined" << " |";
    }

    os << " playlists: [";
    Node<Playlist> *firstPlaylistNode = profile.playlists.getFirstNode();
    Node<Playlist> *playlistNode = firstPlaylistNode;
    if (playlistNode) {
        do {
            os << playlistNode->data;
            if (playlistNode->next != firstPlaylistNode) os << ", ";
            playlistNode = playlistNode->next;
        } while (playlistNode != firstPlaylistNode);
    }
    os << "] |";
    os << " following: [";
    Node<Profile *> *firstProfileNode = profile.following.getFirstNode();
    Node<Profile *> *profileNode = firstProfileNode;
    if (profileNode) {
        do {
            os << profileNode->data->getEmail();
            if (profileNode->next != firstProfileNode) os << ", ";
            profileNode = profileNode->next;
        } while (profileNode != firstProfileNode);
    }
    os << "] |";
    os << " followers: [";
    firstProfileNode = profile.followers.getFirstNode();
    profileNode = firstProfileNode;
    if (profileNode) {
        do {
            os << profileNode->data->getEmail();
            if (profileNode->next != firstProfileNode) os << ", ";
            profileNode = profileNode->next;
        } while (profileNode != firstProfileNode);
    }
    os << "]";

    return os;
}
