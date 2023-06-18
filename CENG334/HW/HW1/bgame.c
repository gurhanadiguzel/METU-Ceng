#include <stdio.h>
#include <stdlib.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

#include "logging.h"
#include "message.h"

#define PIPE(fd) socketpair(AF_UNIX, SOCK_STREAM, PF_UNIX, fd)

typedef struct bomber_data {
    coordinate position;
    int totalArgCnt;
    char **argList;
    int pid;
    int fileno;
    int isAlive;
} bomber_data;

typedef struct bomb {
    coordinate position;
    int pid;
    int fileno;
    int interval;
    int radius;
    int isExploded;
} bomb;

int mapWidth, mapHeight, obstacleCount, bomberCount;
int bombCount, activeBombCount, activeBomberCount;

bomber_data *bomberList;
bomb *bombList;
obsd *obstacleList;
struct pollfd *fdList;
struct pollfd *fdBombList;

void dfe(int *pid, int *fileno, char *args[], int index, ot objectType) {
    int fd[2];

    PIPE(fd);

    *fileno = fd[0];

    *pid = fork();

    if (*pid == -1) {
        exit(1);
    } else if (*pid == 0) {
        // close(STDIN_FILENO);
        // close(STDOUT_FILENO);
        close(fd[0]);

        dup2(fd[1], STDIN_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

        execvp(args[0], args);
    } else {
        if (objectType == BOMBER) {
            fdList[index].fd = *fileno;
            fdList[index].events = POLLIN;
        }
        if (objectType == BOMB) {
            fdBombList[index].fd = *fileno;
            fdBombList[index].events = POLLIN;
        }
        close(fd[1]);
    }
}

void readInputs() {
    int map_width, map_height, obstacle_count, bomber_count;

    scanf("%d", &map_width);
    scanf("%d", &map_height);
    scanf("%d", &obstacle_count);
    scanf("%d", &bomber_count);

    mapWidth = map_width;
    mapHeight = map_height;
    obstacleCount = obstacle_count;
    bomberCount = bomber_count;
    activeBomberCount = bomber_count;

    obstacleList = (obsd *)malloc(obstacle_count * sizeof(obsd));
    int pos_x, pos_y, durability;
    for (int i = 0; i < obstacleCount; i++) {
        scanf("%d", &pos_x);
        scanf("%d", &pos_y);
        scanf("%d", &durability);
        obstacleList[i].position.x = pos_x;
        obstacleList[i].position.y = pos_y;
        obstacleList[i].remaining_durability = durability;
    }

    bomberList = (bomber_data *)malloc(bomberCount * sizeof(bomber_data));
    fdList = (struct pollfd *)malloc(bomberCount * sizeof(struct pollfd));
    fdBombList = (struct pollfd *)malloc(sizeof(struct pollfd) * 0);
    int count;
    for (int j = 0; j < bomber_count; j++) {
        scanf("%d", &pos_x);
        scanf("%d", &pos_y);
        scanf("%d", &count);

        bomberList[j].position.x = pos_x;
        bomberList[j].position.y = pos_y;
        bomberList[j].totalArgCnt = count;
        bomberList[j].isAlive = 1;
        bomberList[j].argList = (char **)malloc((count) * sizeof(char *));

        for (int k = 0; k < (count); k++) {
            char *argument = (char *)malloc(128 * sizeof(char));
            bomberList[j].argList[k] = (char *)malloc(128 * sizeof(char));
            scanf("%s", argument);
            bomberList[j].argList[k] = argument;
        }
        dfe(&bomberList[j].pid, &bomberList[j].fileno, bomberList[j].argList, j, BOMBER);
    }
}

int objectCounter(coordinate pos, od *outgoingMessageData) {
    int result = 0;
    int obstacleX1 = 0;
    int obstacleX2 = 0;
    int obstacleY1 = 0;
    int obstacleY2 = 0;
    // printf("POSITON %d %d\n", pos.x, pos.y);
    for (int k = 0; k < bombCount; k++) {
        if ((pos.x == bombList[k].position.x) && (bombList[k].position.y == pos.y)) {
            result++;
            od newBomb = {.type = BOMB, .position = bombList[k].position};
            outgoingMessageData = (od *)realloc(outgoingMessageData, sizeof(od) * result);
            outgoingMessageData[result - 1] = newBomb;
            break;
        }
    }
    for (int i = 1; i <= 3; i++) {
        for (int j = 0; j < obstacleCount; j++) {
            if (obstacleList[j].remaining_durability != 0) {
                if ((pos.x + i) == obstacleList[j].position.x && pos.y == obstacleList[j].position.y && !obstacleX1) {
                    result++;
                    od newObstacle = {.type = OBSTACLE, .position = obstacleList[j].position};
                    outgoingMessageData = (od *)realloc(outgoingMessageData, sizeof(od) * result);
                    outgoingMessageData[result - 1] = newObstacle;
                    obstacleX1 = 1;
                    continue;
                } else if ((pos.x - i) == obstacleList[j].position.x && pos.y == obstacleList[j].position.y && !obstacleX2) {
                    result++;
                    od newObstacle = {.type = OBSTACLE, .position = obstacleList[j].position};
                    outgoingMessageData = (od *)realloc(outgoingMessageData, sizeof(od) * result);
                    outgoingMessageData[result - 1] = newObstacle;
                    obstacleX2 = 1;
                    continue;
                } else if ((pos.x) == obstacleList[j].position.x && (pos.y + i) == obstacleList[j].position.y && !obstacleY1) {
                    result++;
                    od newObstacle = {.type = OBSTACLE, .position = obstacleList[j].position};
                    outgoingMessageData = (od *)realloc(outgoingMessageData, sizeof(od) * result);
                    outgoingMessageData[result - 1] = newObstacle;
                    obstacleY1 = 1;
                    continue;
                } else if ((pos.x) == obstacleList[j].position.x && (pos.y - i) == obstacleList[j].position.y && !obstacleY2) {
                    result++;
                    od newObstacle = {.type = OBSTACLE, .position = obstacleList[j].position};
                    outgoingMessageData = (od *)realloc(outgoingMessageData, sizeof(od) * result);
                    outgoingMessageData[result - 1] = newObstacle;
                    obstacleY2 = 1;
                    continue;
                }
            }
        }

        if (!obstacleX1) {
            for (int k = 0; k < bomberCount; k++) {
                if ((pos.x + i) == bomberList[k].position.x && bomberList[k].position.y == (pos.y) && bomberList[k].isAlive) {
                    result++;
                    od newBomber = {.type = BOMBER, .position = bomberList[k].position};
                    outgoingMessageData = (od *)realloc(outgoingMessageData, sizeof(od) * result);
                    outgoingMessageData[result - 1] = newBomber;
                    break;
                }
            }

            for (int k = 0; k < bombCount; k++) {
                if ((pos.x + i) == bombList[k].position.x && bombList[k].position.y == (pos.y) && !bombList[k].isExploded) {
                    result++;
                    od newBomb = {.type = BOMB, .position = bombList[k].position};
                    outgoingMessageData = (od *)realloc(outgoingMessageData, sizeof(od) * result);
                    outgoingMessageData[result - 1] = newBomb;
                    break;
                }
            }
        }

        if (!obstacleX2) {
            for (int k = 0; k < bomberCount; k++) {
                if ((pos.x - i) == bomberList[k].position.x && bomberList[k].position.y == (pos.y) && bomberList[k].isAlive) {
                    result++;
                    od newBomber = {.type = BOMBER, .position = bomberList[k].position};
                    outgoingMessageData = (od *)realloc(outgoingMessageData, sizeof(od) * result);
                    outgoingMessageData[result - 1] = newBomber;
                    break;
                }
            }
            for (int k = 0; k < bombCount; k++) {
                if ((pos.x - i) == bombList[k].position.x && bombList[k].position.y == (pos.y) && !bombList[k].isExploded) {
                    result++;
                    od newBomb = {.type = BOMB, .position = bombList[k].position};
                    outgoingMessageData = (od *)realloc(outgoingMessageData, sizeof(od) * result);
                    outgoingMessageData[result - 1] = newBomb;
                    break;
                }
            }
        }

        if (!obstacleY1) {
            for (int k = 0; k < bomberCount; k++) {
                if ((pos.x) == bomberList[k].position.x && bomberList[k].position.y == (pos.y + i) && bomberList[k].isAlive) {
                    result++;
                    od newBomber = {.type = BOMBER, .position = bomberList[k].position};
                    outgoingMessageData = (od *)realloc(outgoingMessageData, sizeof(od) * result);
                    outgoingMessageData[result - 1] = newBomber;
                    break;
                }
            }
            for (int k = 0; k < bombCount; k++) {
                if ((pos.x) == bombList[k].position.x && bombList[k].position.y == (pos.y + i) && !bombList[k].isExploded) {
                    result++;
                    od newBomb = {.type = BOMB, .position = bombList[k].position};
                    outgoingMessageData = (od *)realloc(outgoingMessageData, sizeof(od) * result);
                    outgoingMessageData[result - 1] = newBomb;
                    break;
                }
            }
        }

        if (!obstacleY2) {
            for (int k = 0; k < bomberCount; k++) {
                if ((pos.x) == bomberList[k].position.x && bomberList[k].position.y == (pos.y - i) && bomberList[k].isAlive) {
                    result++;
                    od newBomber = {.type = BOMBER, .position = bomberList[k].position};
                    outgoingMessageData = (od *)realloc(outgoingMessageData, sizeof(od) * result);
                    outgoingMessageData[result - 1] = newBomber;
                    break;
                }
            }
            for (int k = 0; k < bombCount; k++) {
                if ((pos.x) == bombList[k].position.x && bombList[k].position.y == (pos.y - i) && !bombList[k].isExploded) {
                    result++;
                    od newBomb = {.type = BOMB, .position = bombList[k].position};
                    outgoingMessageData = (od *)realloc(outgoingMessageData, sizeof(od) * result);
                    outgoingMessageData[result - 1] = newBomb;
                    break;
                }
            }
        }
    }
    // printf(RESULT IS : %d\n", result);
    return result;
}

coordinate bomberMove(coordinate currentPos, coordinate targetPos) {
    // printf("CURRENT  pos : %d %d \n", currentPos.x, currentPos.y);
    // printf("TARGET  pos : %d %d \n", targetPos.x, targetPos.y);
    for (int i = 0; i < obstacleCount; i++) {
        if (obstacleList[i].position.x == targetPos.x && obstacleList[i].position.y == targetPos.y && obstacleList[i].remaining_durability != 0) {
            return currentPos;
        }
    }
    for (int i = 0; i < bomberCount; i++) {
        if (bomberList[i].position.x == targetPos.x && bomberList[i].position.y == targetPos.y && bomberList[i].isAlive) {
            return currentPos;
        }
    }
    if (targetPos.x >= mapWidth || targetPos.y >= mapHeight || targetPos.x < 0 || targetPos.y < 0) {
        return currentPos;
    }
    if ((abs(targetPos.x - currentPos.x) <= 1) && (targetPos.y == currentPos.y)) {
        return targetPos;
    }
    if ((abs(targetPos.y - currentPos.y) <= 1) && (targetPos.x == currentPos.x)) {
        return targetPos;
    }
    return currentPos;
}

int bomberPlant(coordinate pos, long interval, int radius, int bomberIndex) {
    // Check if there is a bomb here
    for (int i = 0; i < bombCount; i++) {
        if (bombList[i].position.x == pos.x && bombList[i].position.y == pos.y && !bombList[i].isExploded) {
            return 0;
        }
    }

    bombCount++;
    activeBombCount++;

    // Adding new bomb in bombList
    bombList = (bomb *)realloc(bombList, sizeof(bomb) * bombCount);
    bomb newBomb = {.position = pos, .radius = radius, .interval = interval, .isExploded = 0};
    bombList[bombCount - 1] = newBomb;

    // Adding new bomb in fdBombList and goes dfe()
    char argument[128];
    sprintf(argument, "%ld", interval);
    char **argList = (char **)malloc(sizeof(char *) * 2);
    argList[0] = "./bomb";
    argList[1] = argument;
    // printf("ARGUMENTS : %s %s\n", argList[0], argList[1]);

    fdBombList = (struct pollfd *)realloc(fdBombList, sizeof(struct pollfd) * bombCount);
    dfe(&bombList[bombCount - 1].pid, &bombList[bombCount - 1].fileno, argList, (bombCount - 1), BOMB);
    return 1;
}

int activeBomberCounter() {
    int count = 0;
    for (int i = 0; i < bomberCount; i++) {
        if (bomberList[i].isAlive)
            count++;
    }
    return count;
}

int activeBombFinder() {
    //    int count = 0;
    for (int i = 0; i < bombCount; i++) {
        if (!bombList[i].isExploded) {
            // count++;
            return i;
        }
    }
    return -1;
}

void bombExplode(bomb actBomb, int radius) {
    int obstacleX1 = 0;
    int obstacleX2 = 0;
    int obstacleY1 = 0;
    int obstacleY2 = 0;
    int activeBomberCountTemp = activeBomberCounter();
    // printf("ACTIVE BOMBER COUNT IN EXPLODE : %d\n", activeBomberCountTemp);
    // printf("ACTIVE BOMBER COUNT IN EXPLODE2 : %d\n", activeBomberCount);

    for (int i = 1; i <= radius; i++) {
        for (int j = 0; j < obstacleCount; j++) {
            if (obstacleList[j].remaining_durability != 0) {
                if ((actBomb.position.x + i) == obstacleList[j].position.x &&
                    actBomb.position.y == obstacleList[j].position.y &&
                    !obstacleX1) {
                    obstacleX1 = 1;
                    if (obstacleList[j].remaining_durability != -1) {
                        obstacleList[j].remaining_durability--;
                    }
                    continue;
                }
                if ((actBomb.position.x - i) == obstacleList[j].position.x &&
                    actBomb.position.y == obstacleList[j].position.y &&
                    !obstacleX2) {
                    obstacleX2 = 1;
                    if (obstacleList[j].remaining_durability != -1) {
                        obstacleList[j].remaining_durability--;
                    }
                    continue;
                }
                if ((actBomb.position.x) == obstacleList[j].position.x &&
                    (actBomb.position.y + i) == obstacleList[j].position.y &&
                    !obstacleY1) {
                    obstacleY1 = 1;
                    if (obstacleList[j].remaining_durability != -1) {
                        obstacleList[j].remaining_durability--;
                    }
                    continue;
                }
                if ((actBomb.position.x) == obstacleList[j].position.x &&
                    (actBomb.position.y - i) == obstacleList[j].position.y &&
                    !obstacleY2) {
                    obstacleY2 = 1;
                    if (obstacleList[j].remaining_durability != -1) {
                        obstacleList[j].remaining_durability--;
                    }
                    continue;
                }
            }
        }
        // printf("ACTIVE BOMBER COUNTER IN EXPLODE: %d %d\n", activeBomberCount, actBomb.pid);
        // printf("ACTIVE BOMB COUNT: %d \n", activeBombCount);

        for (int j = 0; j < bomberCount; j++) {
            if (bomberList[j].isAlive && activeBomberCountTemp > 1) {
                if ((actBomb.position.x == bomberList[j].position.x) &&
                    (actBomb.position.y == bomberList[j].position.y)) {
                    bomberList[j].isAlive = 0;
                    activeBomberCountTemp--;
                    if (activeBomberCountTemp == 1) {
                        break;
                    }
                    continue;
                }
                if ((actBomb.position.x + i == bomberList[j].position.x) &&
                    (actBomb.position.y == bomberList[j].position.y) &&
                    !obstacleX1) {
                    bomberList[j].isAlive = 0;
                    activeBomberCountTemp--;
                    if (activeBomberCountTemp == 1) {
                        break;
                    }
                    continue;
                }
                if ((actBomb.position.x - i == bomberList[j].position.x) &&
                    (actBomb.position.y == bomberList[j].position.y) &&
                    !obstacleX2) {
                    bomberList[j].isAlive = 0;
                    activeBomberCountTemp--;
                    if (activeBomberCountTemp == 1) {
                        break;
                    }

                    continue;
                }
                if ((actBomb.position.x == bomberList[j].position.x) &&
                    ((actBomb.position.y + i) == bomberList[j].position.y) &&
                    !obstacleY1) {
                    bomberList[j].isAlive = 0;
                    activeBomberCountTemp--;
                    if (activeBomberCountTemp == 1) {
                        break;
                    }
                    continue;
                }
                if ((actBomb.position.x == bomberList[j].position.x) &&
                    ((actBomb.position.y - i) == bomberList[j].position.y) &&
                    !obstacleY2) {
                    bomberList[j].isAlive = 0;
                    activeBomberCountTemp--;
                    if (activeBomberCountTemp == 1) {
                        break;
                    }
                    continue;
                }
            }
        }
        // printf("ACTIVE BOMBER COUNTER IN EXPLODE2: %d \n", activeBomberCount);
        // printf("ACTIVE BOMB COUNT2: %d \n", activeBombCount);
    }
}

void printMap() {
    for (int j = 0; j < mapHeight; j++) {
        for (int i = 0; i < mapWidth; i++) {
            int bomber_controller = 0;
            int bomb_controller = 0;
            int obstacle_controller = 0;
            for (int k = 0; k < bomberCount; k++) {
                if (bomberList[k].position.x == i && bomberList[k].position.y == j && bomberList[k].isAlive) {
                    printf("B ");
                    bomber_controller = 1;
                    break;
                }
            }

            for (int k = 0; k < bombCount; k++) {
                if (bombList[k].position.x == i && bombList[k].position.y == j && !bombList[k].isExploded) {
                    printf("X ");
                    bomb_controller = 1;
                    break;
                }
            }
            if (bomb_controller)
                continue;
            for (int k = 0; k < obstacleCount; k++) {
                if (obstacleList[k].position.x == i && obstacleList[k].position.y == j && obstacleList[k].remaining_durability != 0) {
                    printf("%d ", obstacleList[k].remaining_durability);
                    obstacle_controller = 1;
                    break;
                }
            }
            if (obstacle_controller)
                continue;
            if (!bomber_controller)
                printf("_ ");
        }
        printf("\n");
    }
}

void processGame() {
    while ((activeBomberCount > 0) || (activeBombCount > 0)) {
        if (activeBomberCount == 0 && activeBombCount >= 1) {
            while (1) {
                int index = activeBombFinder();
                if (index != -1) {
                    activeBombCount--;
                    bombList[index].isExploded = 1;
                    im incomingMessage;
                    read_data(fdBombList[index].fd, &incomingMessage);
                    incomingMessage.type = BOMB_EXPLODE;
                    imp incomingPrint = {.m = &incomingMessage, .pid = bombList[index].pid};
                    print_output(&incomingPrint, NULL, NULL, NULL);

                    int status;
                    waitpid(bombList[index].pid, &status, WUNTRACED);
                    close(bombList[index].fileno);
                }
                break;
            }
        }
        if (activeBombCount > 0) {
            poll(fdBombList, bombCount, 1);
            for (int i = 0; i < bombCount; i++) {
                if ((fdBombList[i].revents & POLLIN) && !bombList[i].isExploded) {
                    // printf("ACTIVE BOMB COUNT Is EXPLODE : %d  %d %d \n", activeBombCount, bombList[i].isExploded, i, bombList[i].position.x, bombList[i].position.y);
                    im incomingMessage;
                    read_data(fdBombList[i].fd, &incomingMessage);
                    if (incomingMessage.type == BOMB_EXPLODE) {
                        imp incomingPrint = {.m = &incomingMessage, .pid = bombList[i].pid};
                        print_output(&incomingPrint, NULL, NULL, NULL);

                        bombExplode(bombList[i], bombList[i].radius);
                        bombList[i].isExploded = 1;
                        activeBombCount--;

                        int status;
                        waitpid(bombList[i].pid, &status, WUNTRACED);
                        close(bombList[i].fileno);

                        // for (int j = i; j < bombCount - 1; j++) {
                        //     bombList[j] = bombList[j + 1];
                        //     fdBombList[j] = fdBombList[j + 1];
                        // }
                        // bombCount--;
                        // bombList = (bomb *)realloc(bombList, sizeof(bomb) * (bombCount + 5));
                        // fdBombList = (struct pollfd *)realloc(fdBombList, sizeof(struct pollfd) * (bombCount + 5));
                        // i--;
                    }
                }
            }
        }

        if (activeBomberCount > 0) {
            poll(fdList, bomberCount, 1);
            for (int i = 0; i < bomberCount; i++) {
                if (fdList[i].revents & POLLIN) {
                    im incomingMessage;
                    read_data(fdList[i].fd, &incomingMessage);
                    imp incomingPrint = {.m = &incomingMessage, .pid = bomberList[i].pid};
                    print_output(&incomingPrint, NULL, NULL, NULL);
                    // printf("ACTIVE BOMBER COUNT in BOMBER : %d %d\n", activeBomberCount);

                    if (bomberList[i].isAlive) {
                        if (activeBomberCount == 1) {
                            om outgoingMessage = {.type = BOMBER_WIN};
                            send_message(fdList[i].fd, &outgoingMessage);
                            omp outgoingPrint = {.pid = bomberList[i].pid, .m = &outgoingMessage};
                            print_output(NULL, &outgoingPrint, NULL, NULL);
                            activeBomberCount--;
                            bomberList[i].isAlive = 0;

                            int status;
                            waitpid(bomberList[i].pid, &status, WUNTRACED);
                            close(bomberList[i].fileno);
                            continue;
                        }
                        if (incomingMessage.type == BOMBER_START) {
                            om outgoingMessage = {.type = BOMBER_LOCATION, .data.new_position = bomberList[i].position};
                            send_message(fdList[i].fd, &outgoingMessage);
                            omp outgoingPrint = {.pid = bomberList[i].pid, .m = &outgoingMessage};
                            print_output(NULL, &outgoingPrint, NULL, NULL);
                        }
                        if (incomingMessage.type == BOMBER_SEE) {
                            od *outgoingMessageData = (od *)malloc(sizeof(od));
                            int objectCount = objectCounter(bomberList[i].position, outgoingMessageData);

                            om outgoingMessage = {.type = BOMBER_VISION, .data.object_count = objectCount};
                            send_message(fdList[i].fd, &outgoingMessage);
                            omp outgoingPrint = {.pid = bomberList[i].pid, .m = &outgoingMessage};
                            send_object_data(fdList[i].fd, objectCount, outgoingMessageData);
                            print_output(NULL, &outgoingPrint, NULL, outgoingMessageData);
                        }
                        if (incomingMessage.type == BOMBER_MOVE) {
                            coordinate newPos = bomberMove(bomberList[i].position, incomingMessage.data.target_position);
                            bomberList[i].position = newPos;

                            om outgoingMessage = {.type = BOMBER_LOCATION, .data.new_position = newPos};
                            send_message(fdList[i].fd, &outgoingMessage);
                            omp outgoingPrint = {.pid = bomberList[i].pid, .m = &outgoingMessage};
                            print_output(NULL, &outgoingPrint, NULL, NULL);
                        }
                        if (incomingMessage.type == BOMBER_PLANT) {
                            long interval = incomingMessage.data.bomb_info.interval;
                            int radius = incomingMessage.data.bomb_info.radius;
                            int isPlanted = bomberPlant(bomberList[i].position, interval, radius, i);

                            om outgoingMessage = {.type = BOMBER_PLANT_RESULT, .data.planted = isPlanted};
                            send_message(fdList[i].fd, &outgoingMessage);
                            omp outgoingPrint = {.pid = bomberList[i].pid, .m = &outgoingMessage};
                            print_output(NULL, &outgoingPrint, NULL, NULL);
                        }

                    } else {
                        om outgoingMessage = {.type = BOMBER_DIE};
                        send_message(fdList[i].fd, &outgoingMessage);
                        omp outgoingPrint = {.pid = bomberList[i].pid, .m = &outgoingMessage};
                        print_output(NULL, &outgoingPrint, NULL, NULL);
                        activeBomberCount--;

                        int status;
                        waitpid(bomberList[i].pid, &status, WUNTRACED);
                        close(bomberList[i].fileno);

                        // for (int j = i; j < bomberCount - 1; j++) {
                        //     bomberList[j] = bomberList[j + 1];
                        //     fdList[j] = fdList[j + 1];
                        // }
                        // bomberCount--;
                        // bomberList = (bomber_data *)realloc(bomberList, sizeof(bomber_data) * (bomberCount + 5));
                        // fdList = (struct pollfd *)realloc(fdList, sizeof(struct pollfd) * (bomberCount + 5));
                        // i--;
                    }
                }
            }
        }
        // printf(" ACTIVES  %d %d:\n", activeBomberCount, activeBombCount);
        // printMap();
        // printf("\n\n");
        usleep(1000);
    }
}

int main() {
    readInputs();
    processGame();
    return 0;
}
