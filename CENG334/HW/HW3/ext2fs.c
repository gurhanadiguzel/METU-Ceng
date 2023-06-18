#include <assert.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "ext2fs_print.h"

#define __NBITS (8 * (int)sizeof(unsigned char))
#define __BMELT(d) ((d) / __NBITS)
#define __BMMASK(d) ((unsigned char)1 << ((d) % __NBITS))
#define BM_SET(d, set) ((set[__BMELT(d)] |= __BMMASK(d)))
#define BM_CLR(d, set) ((set[__BMELT(d)] &= ~__BMMASK(d)))
#define BM_ISSET(d, set) ((set[__BMELT(d)] & __BMMASK(d)) != 0)
#define ASSERT(val){}

typedef struct ext2_super_block ext2_super_block_t;
typedef struct ext2_block_group_descriptor ext2_block_group_descriptor_t;
typedef struct ext2_inode ext2_inode_t;
typedef struct ext2_dir_entry ext2_dir_entry_t;

typedef struct
{
    int fileDescriptor;
    char *buffer;
    struct stat stats;
    uint32_t blockSize;
    uint32_t indirectBlockSize;
    ext2_super_block_t *superBlock;
    ext2_block_group_descriptor_t *groupDescriptorTable;
} fs_t;

void ext2_mkdir(char *fs_image, char *path);
void ext2_rmdir(char *fs_image, char *path);
void ext2_rm(char *fs_image, char *path);
void ext2_ed(char *fs_image, char *path);
static inline int initializeFileDescriptor(char *filename);
static inline int closeFileDescriptor();
void tokenizePath(const char *path);
void getPathComponents(const char *directory);
char *getDataBlock(uint32_t dataBlockIndex);
ext2_dir_entry_t *getDirectoryEntry(uint32_t index);
ext2_inode_t *getInode(uint32_t inodeIndex);
ext2_dir_entry_t *getDirectoryEntry(uint32_t index);
void createDirectoryEntry(ext2_dir_entry_t *dirEntry, uint32_t parentInodeIndex, uint32_t inodeIndex, u_int16_t sumSize, char *newDirectoryName);
void allocateBlock(ext2_inode_t **inode, ext2_dir_entry_t **dirEntry, u_int16_t *sumSize, char *directoryName);
uint32_t allocateInode(uint32_t parentInodeIndex);
uint32_t deallocateInode_rmdir(uint32_t inodeIndex);
void deallocateInode_rm(uint32_t inodeIndex);
void removeBlock(uint32_t blockIndex);
void updateTimes(uint32_t inodeIndex);
int checkPath(ext2_inode_t **tempInode, ext2_dir_entry_t **dirEntry);
int checkDirectoryEntry_mkdir(ext2_inode_t **tempInode, ext2_dir_entry_t **dirEntry, u_int16_t *sumSize, char *directoryName);
int checkDirectoryEntry_rmdir(ext2_inode_t **tempInode, ext2_dir_entry_t **dirEntry, ext2_dir_entry_t **prevDirEntry);

fs_t fs;
time_t t;
char **pathComponents = NULL;
int componentCount = 0;
char* parentPath;
char* directoryName;
uint32_t blockIndex = 0;

int main(int argc, char *argv[]) {
    char *fs_image = argv[1];
    char *command = argv[2];
    char *path = argv[3];

    if (initializeFileDescriptor(fs_image) != 0){
        return -1;
    }

    parentPath = (char *)malloc((strlen(path) + 1) * sizeof(char));
    directoryName = (char *)malloc((strlen(path) + 1) * sizeof(char));
    tokenizePath(path);
    getPathComponents(parentPath);

    if (argc == 4) {
        if (strcmp(command, "mkdir") == 0) {
            // printf("Command is MKDIR\n");
            ext2_mkdir(fs_image, path);
        } else if (strcmp(command, "rmdir") == 0) {
            // printf("Command is RMDIR\n");
            ext2_rmdir(fs_image, path);
        } else if (strcmp(command, "rm") == 0) {
            // printf("Command is RM\n");
            ext2_rm(fs_image, path);
        } else if (strcmp(command, "ed") == 0) {
            // printf("Command is ED\n");
            ext2_ed(fs_image, path);
        } else {
            // printf("Invalid command\n");
        }
    } else {
        // printf("Wrong number of arguments.");
        return -1;
    }

    free(parentPath);
    free(directoryName);
    if (closeFileDescriptor() != 0){
        return -1;
    }

    return 0;
}

static inline int initializeFileDescriptor(char *filename) {
    fs.fileDescriptor = open(filename, O_RDWR);
    off_t length = lseek(fs.fileDescriptor, 0, SEEK_END);
    fs.buffer = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED, fs.fileDescriptor, 0);

    if (fs.fileDescriptor < 0) {
        // printf("File cannot found.\n");
        return -1;
    }
    if (fstat(fs.fileDescriptor, &fs.stats) < 0) {
        // printf("File cannot found.\n");
        return -1;
    }
    if (fs.buffer == MAP_FAILED) {
        // printf("Mmap failed.\n");
        return -1;
    }

    fs.superBlock = (ext2_super_block_t *)&fs.buffer[EXT2_SUPER_BLOCK_POSITION];
    fs.blockSize = EXT2_UNLOG(fs.superBlock->log_block_size);
    fs.indirectBlockSize = fs.blockSize / sizeof(uint32_t);
    fs.groupDescriptorTable = (ext2_block_group_descriptor_t *)getDataBlock(fs.superBlock->first_data_block + 1);

    // print_stat(&fs.stats);
    // print_super_block(fs.superBlock);
    // print_group_descriptor(fs.groupDescriptorTable);

    return 0;
}

static inline int closeFileDescriptor() {
    if (munmap(fs.buffer, fs.stats.st_size) != 0) {
        // printf("munmap failed.\n");
        return -1;
    }

    return 0;
}

void ext2_mkdir(char *fs_image, char *path) {
    uint32_t inodeIndex = EXT2_ROOT_INODE;
    ext2_inode_t *tempInode = getInode(inodeIndex);
    // print_inode(tempInode, inodeIndex);
    ext2_dir_entry_t *dirEntry = getDirectoryEntry(tempInode->direct_blocks[0]);
    // print_dir_entry(dirEntry, "ROOT");
    void *tempEntry = dirEntry;

    int isPathFound = checkPath(&tempInode, &dirEntry);
    // print_inode(tempInode, dirEntry->inode);
    if (!isPathFound && componentCount > 0) {
        // printf("Path cannot be found\n");
        return;
    }

    uint32_t parentInodeIndex = dirEntry->inode;
    u_int16_t sumSize = 0;
    int isDirectoryFound = checkDirectoryEntry_mkdir(&tempInode, &dirEntry, &sumSize, directoryName);
    if (isDirectoryFound) {
        // printf("There is a same file in this directory.\n");
        return;
    }

    uint32_t newInode = allocateInode(parentInodeIndex);
    printf("EXT2_ALLOC_INODE %d\n", newInode);
    createDirectoryEntry(dirEntry, parentInodeIndex, newInode, sumSize, directoryName);
    updateTimes(parentInodeIndex);
}

void ext2_rmdir(char *fs_image, char *path) {
    uint32_t inodeIndex = EXT2_ROOT_INODE;
    ext2_inode_t *rootInode = getInode(inodeIndex);
    // print_inode(rootInode, inodeIndex);

    ext2_dir_entry_t *dirEntry = getDirectoryEntry(rootInode->direct_blocks[0]);
    // print_dir_entry(dirEntry, "Root");

    void *tempEntry = dirEntry;
    ext2_inode_t *tempInode = rootInode;

    int isPathFound = checkPath(&tempInode, &dirEntry);
    if (!isPathFound && componentCount > 0) {
        // printf("Path cannot be found\n");
        return;
    }

    uint32_t parentInodeIndex = dirEntry->inode;
    ext2_inode_t *parentInode = getInode(parentInodeIndex);
    ext2_dir_entry_t *prevDirEntry = getDirectoryEntry(parentInode->direct_blocks[0]);
    u_int16_t sumSize = 0;

    int isDirectoryFound = checkDirectoryEntry_rmdir(&tempInode, &dirEntry, &prevDirEntry);
    if (!isDirectoryFound) {
        // printf("Directory cannot be found.\n");
        return;
    }

    inodeIndex = dirEntry->inode;

    uint32_t index = deallocateInode_rmdir(inodeIndex);
    if (index == -1) {
        return;
    }
    prevDirEntry->length += dirEntry->length;
    parentInode->link_count--;
    fs.groupDescriptorTable->used_dirs_count--;
    printf("EXT2_FREE_DIR_ENTRY %s %d\n", directoryName, blockIndex);
    printf("EXT2_FREE_INODE %d\n", inodeIndex);
    removeBlock(blockIndex);
    updateTimes(parentInodeIndex);
}

void ext2_rm(char *fs_image, char *path) {
    uint32_t inodeIndex = EXT2_ROOT_INODE;
    ext2_inode_t *rootInode = getInode(inodeIndex);
    // print_inode(rootInode, inodeIndex);

    ext2_dir_entry_t *dirEntry = getDirectoryEntry(rootInode->direct_blocks[0]);
    // print_dir_entry(dirEntry, "Root");

    void *tempEntry = dirEntry;
    ext2_inode_t *tempInode = rootInode;

    int isPathFound = checkPath(&tempInode, &dirEntry);
    if (!isPathFound && componentCount > 0) {
        // printf("Path cannot be found\n");
        return;
    }

    uint32_t parentInodeIndex = dirEntry->inode;
    ext2_inode_t *parentInode = getInode(parentInodeIndex);
    ext2_dir_entry_t *prevDirEntry = getDirectoryEntry(parentInode->direct_blocks[0]);
    u_int16_t sumSize = 0;

    // print_inode(parentInode, parentInodeIndex);
    int isFileFound = checkDirectoryEntry_rmdir(&tempInode, &dirEntry, &prevDirEntry);
    // print_dir_entry(dirEntry, "IN RM");
    if (!isFileFound || dirEntry->file_type != 1) {
        // printf("File cannot be found.\n");
        return;
    }

    inodeIndex = dirEntry->inode;

    dirEntry->inode = 0;

    printf("EXT2_FREE_DIR_ENTRY %s %d\n", directoryName, blockIndex);
    printf("EXT2_FREE_INODE %d\n", inodeIndex);
    deallocateInode_rm(inodeIndex);
    prevDirEntry->length += dirEntry->length;
    parentInode->link_count--;
    updateTimes(parentInodeIndex);
}

void ext2_ed(char *fs_image, char *path) {
    // Update function
}

char *getDataBlock(uint32_t dataBlockIndex) {
    return &fs.buffer[fs.blockSize * dataBlockIndex];
}

ext2_dir_entry_t *getDirectoryEntry(uint32_t index) {
    return (ext2_dir_entry_t *)(fs.buffer + (index * fs.blockSize));
}

ext2_inode_t *getInode(uint32_t inodeIndex) {
    uint32_t blockGroupIndex = (size_t)((inodeIndex - 1) / fs.superBlock->inodes_per_group);
    uint32_t inodeOffset = (inodeIndex - 1) - (blockGroupIndex * fs.superBlock->inodes_per_group);

    ASSERT(blockGroupIndex >= 0);
    ASSERT(inodeOffset >= 0);

    ext2_block_group_descriptor_t *groupDescriptor = &fs.groupDescriptorTable[blockGroupIndex];
    char *inodeTable = getDataBlock(groupDescriptor->inode_table);
    return (ext2_inode_t *)(inodeTable + fs.superBlock->inode_size * inodeOffset);
}

void tokenizePath(const char *path) {
    size_t length = strlen(path);
    

    char *pathCopy = (char *)malloc((length + 1) * sizeof(char));
    strcpy(pathCopy, path);

    char *token = strtok(pathCopy, "/");
    char *lastToken = NULL;

    while (token != NULL) {
        if (lastToken != NULL) {
            strcat(parentPath, lastToken);
            strcat(parentPath, "/");
        }
        lastToken = token;
        token = strtok(NULL, "/");
    }

    strcpy(directoryName, lastToken);
    free(pathCopy);
}

void getPathComponents(const char *directory) {
    size_t length = strlen(directory);
    char *tempPath = (char *)malloc((length + 1) * sizeof(char));
    strcpy(tempPath, directory);

    const char delimiter[] = "/";
    char *token = strtok(tempPath, delimiter);
    while (token != NULL) {
        pathComponents = realloc(pathComponents, (componentCount + 1) * sizeof(char *));
        pathComponents[componentCount] = strdup(token);
        componentCount++;
        token = strtok(NULL, delimiter);
    }

    for (int i = 0; i < componentCount; i++) {
        // printf("%s\n", pathComponents[i]);
    }
    free(tempPath);
}

int checkPathHelper(ext2_inode_t **tempInode, ext2_dir_entry_t **dirEntry, int index) {
    int isFound = 0;

    void *tempEntry = *dirEntry;
    u_int16_t blockSize = fs.blockSize;
    while (blockSize > 0) {
        if (((*dirEntry)->name_length == strlen(pathComponents[index])) && (!strncmp((*dirEntry)->name, pathComponents[index], (*dirEntry)->name_length))) {
            // printf("Path have been found. %s\n", (*dirEntry)->name);
            (*tempInode) = getInode((*dirEntry)->inode);
            isFound = 1;
            break;
        }
        blockSize -= (*dirEntry)->length;
        tempEntry = (*dirEntry);
        tempEntry += (*dirEntry)->length;
        (*dirEntry) = (ext2_dir_entry_t *)tempEntry;
    }
    return isFound;
}

int checkPath(ext2_inode_t **tempInode, ext2_dir_entry_t **dirEntry) {
    int isFound = 0;
    uint32_t index;
    for (int i = 0; i < componentCount; i++) {
        isFound = 0;
        // printf("%s\n", pathComponents[i]);

        for (int j = 0; j < EXT2_NUM_DIRECT_BLOCKS; j++) {
            index = (*tempInode)->direct_blocks[j];
            if (index != 0) {
                (*dirEntry) = getDirectoryEntry(index);
                isFound = checkPathHelper(tempInode, dirEntry, i);
                if (isFound) {
                    return isFound;
                }
            }
        }

        if ((*tempInode)->single_indirect != 0) {
            uint32_t *singleDataBlock = (u_int32_t *)getDataBlock((*tempInode)->single_indirect);

            for (int j = 0; j < fs.indirectBlockSize; j++) {
                index = singleDataBlock[j];
                if (index != 0) {
                    (*dirEntry) = getDirectoryEntry(index);
                    isFound = checkPathHelper(tempInode, dirEntry, i);
                    if (isFound) {
                        return isFound;
                    }
                }
            }
        }

        if ((*tempInode)->double_indirect != 0) {
            uint32_t *doubleDataBlock = (uint32_t *)getDataBlock((*tempInode)->double_indirect);

            for (int k = 0; k < fs.indirectBlockSize; k++) {
                if (doubleDataBlock[k] != 0) {
                    uint32_t *singleDataBlock = (u_int32_t *)getDataBlock(doubleDataBlock[k]);

                    for (int j = 0; j < fs.indirectBlockSize; j++) {
                        index = singleDataBlock[j];
                        if (index != 0) {
                            (*dirEntry) = getDirectoryEntry(index);
                            isFound = checkPathHelper(tempInode, dirEntry, i);
                            if (isFound) {
                                return isFound;
                            }
                        }
                    }
                }
            }
        }

        if ((*tempInode)->triple_indirect != 0) {
            uint32_t *tripleDataBlock = (uint32_t *)getDataBlock((*tempInode)->triple_indirect);

            for (int l = 0; l < fs.indirectBlockSize; l++) {
                if (tripleDataBlock[l] != 0) {
                    uint32_t *doubleDataBlock = (uint32_t *)getDataBlock(tripleDataBlock[l]);

                    for (int k = 0; k < fs.indirectBlockSize; k++) {
                        if (doubleDataBlock[k] != 0) {
                            uint32_t *singleDataBlock = (u_int32_t *)getDataBlock(doubleDataBlock[k]);

                            for (int j = 0; j < fs.indirectBlockSize; j++) {
                                index = singleDataBlock[j];
                                if (index != 0) {
                                    (*dirEntry) = getDirectoryEntry(index);
                                    isFound = checkPathHelper(tempInode, dirEntry, i);
                                    if (isFound) {
                                        return isFound;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return isFound;
}

int checkDirectoryEntry_mkdir(ext2_inode_t **tempInode, ext2_dir_entry_t **dirEntry, u_int16_t *sumSize, char *directoryName) {
    int isFound = 0;
    u_int16_t blockSize;
    void *tempEntry = (*dirEntry);

    for (int i = 0; i < EXT2_NUM_DIRECT_BLOCKS; i++) {
        if (isFound) {
            return isFound;
        }

        blockIndex = (*tempInode)->direct_blocks[i];

        if (blockIndex == 0) {
            continue;
        }

        (*dirEntry) = getDirectoryEntry(blockIndex);
        blockSize = fs.blockSize;
        while (blockSize > 0) {
            blockSize -= (*dirEntry)->length;
            if (((*dirEntry)->name_length == strlen(directoryName)) && (!strncmp((*dirEntry)->name, directoryName, (*dirEntry)->name_length))) {
                isFound = 1;
                break;
            }

            if (blockSize == 0) {
                if ((fs.blockSize - (*sumSize)) < EXT2_DIR_LENGTH(strlen(directoryName))) {
                    allocateBlock(tempInode, dirEntry, sumSize, directoryName);
                    (*sumSize) = 0;

                } else {
                    printf("EXT2_ALLOC_DIR_ENTRY %s %d\n", directoryName, blockIndex);
                    (*dirEntry)->length = EXT2_DIR_LENGTH(strlen((*dirEntry)->name));
                    *sumSize += (*dirEntry)->length;
                    tempEntry = (*dirEntry);
                    tempEntry += (*dirEntry)->length;
                    (*dirEntry) = (ext2_dir_entry_t *)tempEntry;
                }

                break;
            }

            if ((*dirEntry)->length != EXT2_DIR_LENGTH(strlen((*dirEntry)->name))) {
                if ((*dirEntry)->length > EXT2_DIR_LENGTH(strlen(directoryName))) {
                    (*dirEntry)->length = EXT2_DIR_LENGTH(strlen((*dirEntry)->name));
                    *sumSize = fs.blockSize - ((*dirEntry)->length - EXT2_DIR_LENGTH(strlen((*dirEntry)->name)));
                    // be careful block size
                    break;
                }
            }

            *sumSize += (*dirEntry)->length;
            tempEntry = (*dirEntry);
            tempEntry += (*dirEntry)->length;
            (*dirEntry) = (ext2_dir_entry_t *)tempEntry;
        }
    }

    return isFound;
}

int checkDirectoryEntry_rmdir(ext2_inode_t **tempInode, ext2_dir_entry_t **dirEntry, ext2_dir_entry_t **prevDirEntry) {
    int isFound = 0;
    u_int16_t blockSize;
    void *tempEntry = (*dirEntry);

    for (int i = 0; i < EXT2_NUM_DIRECT_BLOCKS; i++) {
        blockIndex = (*tempInode)->direct_blocks[i];
        if (isFound || blockIndex == 0)
            break;
        (*dirEntry) = getDirectoryEntry(blockIndex);
        blockSize = fs.blockSize;
        while (blockSize > 0) {
            // print_dir_entry((*dirEntry), "path");
            if (((*dirEntry)->name_length == strlen(directoryName)) && (!strncmp((*dirEntry)->name, directoryName, (*dirEntry)->name_length))) {
                isFound = 1;

                break;
            }
            blockSize -= (*dirEntry)->length;
            if (blockSize > 0) {
                (*prevDirEntry) = (*dirEntry);
            }
            tempEntry = (*dirEntry);
            tempEntry += (*dirEntry)->length;
            (*dirEntry) = (ext2_dir_entry_t *)tempEntry;
        }
    }

    return isFound;
}

void allocateBlock(ext2_inode_t **inode, ext2_dir_entry_t **dirEntry, u_int16_t *sumSize, char *directoryName) {
    unsigned char *blockBitmap = getDataBlock( fs.groupDescriptorTable->block_bitmap);

    for (int i = 0; i < fs.superBlock->block_count; i++) {
        if (!BM_ISSET(i, blockBitmap)) {
            printf("EXT2_ALLOC_DIR_ENTRY %s %d\n", directoryName, i);
            BM_SET(i, blockBitmap);

            (*dirEntry) = getDirectoryEntry(i);
            for (int j = 0; j < EXT2_NUM_DIRECT_BLOCKS; j++) {
                if ((*inode)->direct_blocks[j] == 0) {
                    (*inode)->direct_blocks[j] = i;
                }
            }

            fs.superBlock->free_block_count--;
            fs.groupDescriptorTable->free_block_count--;
            fs.groupDescriptorTable->used_dirs_count++;
            (*inode)->size += fs.blockSize;
            (*inode)->block_count_512 += fs.blockSize / 512;
            break;
        }
    }
}

void createDirectoryEntry(ext2_dir_entry_t *dirEntry, uint32_t parentInodeIndex, uint32_t inodeIndex, u_int16_t sumSize, char *newDirectoryName) {
    unsigned char *blockBitmap = getDataBlock(fs.groupDescriptorTable->block_bitmap);
    ext2_inode_t *parentInode = getInode(parentInodeIndex);
    ext2_inode_t *inode = getInode(inodeIndex);

    // printf("PARENT INODE IS %d \n", parentInodeIndex);
    // print_inode(parentInode, parentInodeIndex);
    // print_inode(inode, inodeIndex);

    ext2_dir_entry_t *newDirectoryEntry;
    for (int i = 0; i < fs.superBlock->block_count; i++) {
        if (!BM_ISSET(i, blockBitmap)) {
            newDirectoryEntry = getDirectoryEntry(i);
            printf("EXT2_ALLOC_BLOCK %d\n", i);

            newDirectoryEntry->inode = inodeIndex;
            newDirectoryEntry->length = EXT2_DIR_LENGTH(strlen("."));
            newDirectoryEntry->name_length = strlen(".");
            newDirectoryEntry->file_type = 2;
            strcpy(newDirectoryEntry->name, ".");
            // print_dir_entry(newDirectoryEntry, "nokta");
            printf("EXT2_ALLOC_DIR_ENTRY %s %d\n", ".", i);

            void *temp = newDirectoryEntry;
            temp += newDirectoryEntry->length;
            newDirectoryEntry = (ext2_dir_entry_t *)temp;

            newDirectoryEntry->inode = parentInodeIndex;
            newDirectoryEntry->length = fs.blockSize - 12;
            newDirectoryEntry->name_length = strlen("..");
            newDirectoryEntry->file_type = 2;
            strcpy(newDirectoryEntry->name, "..");
            // print_dir_entry(newDirectoryEntry, "iki nokta");
            printf("EXT2_ALLOC_DIR_ENTRY %s %d\n", "..", i);

            inode->direct_blocks[0] = i;
            BM_SET(i, blockBitmap);

            fs.superBlock->free_block_count--;
            fs.groupDescriptorTable->free_block_count--;
            fs.groupDescriptorTable->used_dirs_count++;

            break;
        }
    }

    dirEntry->inode = inodeIndex;
    dirEntry->length = fs.blockSize - sumSize;
    strcpy(dirEntry->name, newDirectoryName);
    dirEntry->name_length = strlen(newDirectoryName);
    dirEntry->file_type = 2;
    // print_inode(getInode(dirEntry->inode), inodeIndex);
    // print_dir_entry(dirEntry, "New Dir Entry");
}

uint32_t allocateInode(uint32_t parentInodeIndex) {
    uint32_t index = 0;
    ext2_inode_t *parentInode = getInode(parentInodeIndex);
    ext2_inode_t *newInode;
    unsigned char *inodeBitmap = getDataBlock(fs.groupDescriptorTable->inode_bitmap) ;

    for (; index < fs.superBlock->inode_count; index++) {
        if (!BM_ISSET(index, inodeBitmap)) {
            // printf("INODE index is %d\n", index + 1);
            newInode = getInode(index + 1);
            newInode->mode = EXT2_I_DTYPE;
            newInode->uid = EXT2_I_UID;
            newInode->size = fs.blockSize;
            newInode->access_time = UPDATE_TIME(t);
            newInode->creation_time = UPDATE_TIME(t);
            newInode->modification_time = UPDATE_TIME(t);
            newInode->deletion_time = 0;
            newInode->gid = EXT2_I_GID;
            newInode->link_count = 2;
            newInode->block_count_512 = fs.blockSize / 512;

            parentInode->link_count++;
            // parentInode->block_count_512 += fs.blockSize / 512;

            BM_SET(index, inodeBitmap);
            fs.superBlock->free_inode_count--;
            fs.groupDescriptorTable->free_inode_count--;

            break;
        }
    }
    // printf("NEW INODE HAS BEEN CREATED\n");
    // print_inode(newInode, index + 1);

    return index + 1;
}

uint32_t deallocateInode_rmdir(uint32_t inodeIndex) {
    ext2_inode_t *inode = getInode(inodeIndex);
    blockIndex = inode->direct_blocks[0];

    ext2_dir_entry_t *dirEntry = getDirectoryEntry(blockIndex);
    uint32_t length = dirEntry->length;
    void *tempEntry = dirEntry;
    tempEntry += dirEntry->length;
    dirEntry = (ext2_dir_entry_t *)tempEntry;

    if (dirEntry->length == fs.blockSize - length) {
        unsigned char *inodeBitmap = getDataBlock(fs.groupDescriptorTable->inode_bitmap);
        BM_CLR(inodeIndex - 1, inodeBitmap);
        fs.superBlock->free_inode_count++;
        fs.groupDescriptorTable->free_inode_count++;
        inode->link_count -= 2;
        inode->deletion_time = UPDATE_TIME(t);
        return blockIndex;
    }

    // printf("Directory is not empty \n");
    return -1;
}

void deallocateInode_rm(uint32_t inodeIndex) {
    ext2_inode_t *inode = getInode(inodeIndex);
    // printf("Link Count %d", inode->link_count);
    // print_inode(inode, inodeIndex);

    if (inode->link_count == 1) {
        for (int i = 0; i < EXT2_NUM_DIRECT_BLOCKS; i++) {
            if (inode->direct_blocks[i] != 0) {
                removeBlock(inode->direct_blocks[i]);
                inode->direct_blocks[i] = 0;
            }
        }

        if (inode->single_indirect != 0) {
            uint32_t *singleDataBlock = (u_int32_t *)getDataBlock(inode->single_indirect);
            for (int i = 0; i < fs.indirectBlockSize; i++) {
                if (singleDataBlock[i] != 0) {
                    removeBlock(singleDataBlock[i]);
                    singleDataBlock[i] = 0;
                }
            }
            removeBlock(inode->single_indirect);
        }

        if (inode->double_indirect != 0) {
            uint32_t *doubleDataBlock = (uint32_t *)getDataBlock(inode->double_indirect);
            for (int j = 0; j < fs.indirectBlockSize; j++) {
                if (doubleDataBlock[j] != 0) {
                    uint32_t *singleDataBlock = (u_int32_t *)getDataBlock(doubleDataBlock[j]);
                    for (int i = 0; i < fs.indirectBlockSize; i++) {
                        if (singleDataBlock[i] != 0) {
                            removeBlock(singleDataBlock[i]);
                            singleDataBlock[i] = 0;
                        }
                    }
                    removeBlock(doubleDataBlock[j]);
                }
            }
            removeBlock(inode->double_indirect);
        }

        if (inode->triple_indirect != 0) {
            uint32_t *tripleDataBlock = (uint32_t *)getDataBlock(inode->triple_indirect);
            for (int k = 0; k < fs.indirectBlockSize; k++) {
                if (tripleDataBlock[k] != 0) {
                    uint32_t *doubleDataBlock = (uint32_t *)getDataBlock(tripleDataBlock[k]);
                    for (int j = 0; j < fs.indirectBlockSize; j++) {
                        if (doubleDataBlock[j] != 0) {
                            uint32_t *singleDataBlock = (u_int32_t *)getDataBlock(doubleDataBlock[j]);
                            for (int i = 0; i < fs.indirectBlockSize; i++) {
                                if (singleDataBlock[i] != 0) {
                                    removeBlock(singleDataBlock[i]);
                                    singleDataBlock[i] = 0;
                                }
                            }
                            removeBlock(doubleDataBlock[j]);
                        }
                    }
                    removeBlock(tripleDataBlock[k]);
                }
            }
            removeBlock(inode->triple_indirect);
        }

        unsigned char *inodeBitmap = getDataBlock(fs.groupDescriptorTable->inode_bitmap);
        BM_CLR(inodeIndex - 1, inodeBitmap);
        fs.superBlock->free_inode_count++;
        fs.groupDescriptorTable->free_inode_count++;
        inode->link_count--;
        inode->size = 0;
        inode->block_count_512 = 0;
        inode->deletion_time = UPDATE_TIME(t);
    }
}

void removeBlock(uint32_t index) {
    printf("EXT2_FREE_BLOCK %d\n", index);
    unsigned char *blockBitmap = getDataBlock( fs.groupDescriptorTable->block_bitmap);
    BM_CLR(index, blockBitmap);
    fs.superBlock->free_block_count++;
    fs.groupDescriptorTable->free_block_count++;
}

void updateTimes(uint32_t inodeIndex) {
    ext2_inode_t *inode = getInode(inodeIndex);
    ext2_dir_entry_t *directoryEntry = getDirectoryEntry(inode->direct_blocks[0]);
    void *temp;

    while (inodeIndex != EXT2_ROOT_INODE) {
        // printf("PARENT INDEX IS %d\n", inodeIndex);
        inode = getInode(inodeIndex);
        inode->access_time = UPDATE_TIME(t);
        inode->modification_time = UPDATE_TIME(t);

        directoryEntry = getDirectoryEntry(inode->direct_blocks[0]);
        temp = directoryEntry;
        temp += directoryEntry->length;
        directoryEntry = temp;
        inodeIndex = directoryEntry->inode;
    }
    inode->access_time = UPDATE_TIME(t);
    inode->modification_time = UPDATE_TIME(t);
}
