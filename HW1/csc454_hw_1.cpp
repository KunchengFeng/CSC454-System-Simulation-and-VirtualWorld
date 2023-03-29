#include <iostream>
#include <string>
#include <stdlib.h>

class Creature;
class Room;
void createRooms(int n, Room* rooms);
void createCreatures(int m, Creature* creatures, Room* rooms);
void loopForCommand(Creature* creatures, int n, Room* rooms, int m);
void look(Creature* creatures, Room* rooms, int creature);
void clean(Creature* creatures, Room* rooms, int creature, int player);
void dirty(Creature* creatures, Room* rooms, int creature, int player);
void move(Creature* creatures, Room* rooms, int creature, int player, std::string direction);
void react(Creature* creatures, Room* rooms, int targetRoom, int except, int player, std::string action);
std::string whichWay(Room* rooms, int thisRoom);
void helpInfo();

// coding in progress... coding in progress... coding in progress...
void checkStatus(Creature* creatures, Room* rooms, int room, int player);
void leave(Creature* creatures, int creature, Room* rooms, int room, int player);


// Rooms are numbered from 0.
class Room {
private:
    int state;
    int doorNorth, doorSouth, doorEast, doorWest;
    Creature* cPointers[10];

public:
    Room() {}
    Room(int s, int dn, int ds, int de, int dw) {
        this->state = s;
        this->doorNorth = dn;
        this->doorSouth = ds;
        this->doorEast = de;
        this->doorWest = dw;
        for (int i = 0; i < 10; i++) {
            cPointers[i] = NULL;
        }
    }

    int getOccupancy() {
        int result = 0;
        for (int i = 0; i < 10; i++) {
            if (cPointers[i] != NULL) {
                result++;
            }
        }
        return result;
    }

    int getState() { return this->state; }
    int getDoorNorth() { return this->doorNorth; }
    int getDoorSouth() { return this->doorSouth; }
    int getDoorEast() { return this->doorEast; }
    int getDoorWest() { return this->doorWest; }

    Creature* getCPointers(int i) {
        if (cPointers[i] != NULL) {
            return cPointers[i];
        }
        else {
            return NULL;
        }
    }

    void populate(Creature* cPointer) {
        for (int i = 0; i < 10; i++) {
            if (this->cPointers[i] == NULL) {
                this->cPointers[i] = cPointer;
                break;
            }
            else {
                continue;
            }
        }
    }

    void remove(Creature* cPointer) {
        for (int i = 0; i < 10; i++) {
            if (this->cPointers[i] == cPointer) {
                this->cPointers[i] = NULL;
                break;
            }
            else {
                continue;
            }
        }
    }

    void getCleaned() {
        if (this->state > 0) {
            this->state = state - 1;
        }
    }

    void getDirtied() {
        if (this->state < 2) {
            this->state = state + 1;
        }
    }
};


// Creatures are also numbered from 0, and location represent the room it's currently in, -1 means it's out of the simulation.
class Creature {
private:
    int type;
    int name;
    int location;
    int respect;

public:
    Creature() {}
    Creature(int i, int t, int l) {
        this->name = i;
        this->type = t;
        this->location = l;
        if (t == 0) {
            this->respect = 40;
        }
        else {
            this->respect = 0;
        }
    }

    int getType() { return this->type; }
    int getName() { return this->name; }
    int getLocation() { return this->location; }
    int getRespect() { return this->respect; }

    void moreRespect() { this->respect = respect++; }
    void lessRespect() { this->respect = respect--; }
    void setLocation(int room) { this->location = room; }
};


int main() {
    int n, m;

    // Creating rooms.
    std::cout << "Please enter the number of rooms" << std::endl;
    std::cin >> n;
    Room* rooms = new Room[n];
    createRooms(n, rooms);

    // Creating creatures.
    std::cout << "\nPlease enter the number of creatures" << std::endl;
    std::cin >> m;
    Creature* creatures = new Creature[m];
    createCreatures(m, creatures, rooms);

    loopForCommand(creatures, n, rooms, m);
    return 0;
};

void clean(Creature* creatures, Room* rooms, int creature, int player) {
    int targetRoom = creatures[creature].getLocation();
    int pcRoom = creatures[player].getLocation();
   
    // Cleaning a clean room
    if (rooms[targetRoom].getState() == 0) { return; }

    if (player == creature) {
        rooms[targetRoom].getCleaned();
        react(creatures, rooms, targetRoom, -1, player, "clean");
    }
    else if (targetRoom == -1) {
        std::cout << "This creature already left the simulation." << std::endl;
        return;
    }
    else if (targetRoom != pcRoom) {
        std::cout << "This creature is not in the same room as the player." << std::endl;
    }
    else {
        // Player is making some other creature do it.
        rooms[targetRoom].getCleaned();
        if (creatures[creature].getType() == 1) {
            // Creature is an anime.
            creatures[player].moreRespect();
            creatures[player].moreRespect();
            creatures[player].moreRespect();
            std::cout << creature << " licks your face a lot. Respect is now " << creatures[player].getRespect() << std::endl;
        }
        else {
            // Creature is an human.
            creatures[player].lessRespect();
            creatures[player].lessRespect();
            creatures[player].lessRespect();
            std::cout << creature << " grumbles a lot. Respect is now " << creatures[player].getRespect() << std::endl;
        }
        react(creatures, rooms, targetRoom, creature, player, "clean");
    }
}

void cleanBySelf(Creature* creatures, Room* rooms, int creature) {
    int room = creatures[creature].getLocation();
    rooms[room].getCleaned();
    std::cout << creature << " cleaned room #" << room << " because it was dirty." << std::endl;
}

void createCreatures(int m, Creature* creatures, Room* rooms) {
    int t, l;
    for (int i = 0; i < m; i++) {
        std::cout << "Please enter creature #" << i << "'s type and location" << std::endl;
        std::cin >> t;
        std::cin >> l;
        creatures[i] = Creature(i, t, l);
        rooms[l].populate(&creatures[i]);
    }
};

void createRooms(int n, Room* rooms) {
    int s, dn, ds, de, dw;
    for (int i = 0; i < n; i++) {
        std::cout << "Please enter the state of room #" << i << " and the numbers of its respective neighbors neighbors" << std::endl;
        std::cin >> s;
        std::cin >> dn;
        std::cin >> ds;
        std::cin >> de;
        std::cin >> dw;
        rooms[i] = Room(s, dn, ds, de, dw);
    }
};

void dirty(Creature* creatures, Room* rooms, int creature, int player) {
    int targetRoom = creatures[creature].getLocation();
    int pcRoom = creatures[player].getLocation();

    // Dirtying a dirty room.
    if (rooms[targetRoom].getState() == 2) { return; }

    if (player == creature) {
        rooms[targetRoom].getDirtied();
        react(creatures, rooms, targetRoom, -1, player, "dirty");
    }
    else if (targetRoom == -1) {
        std::cout << "This creature already left the simulation." << std::endl;
        return;
    }
    else if (targetRoom != pcRoom) {
        std::cout << "This creature is not in the same room as the player." << std::endl;
    }
    else {
        // Player is making some other creature do it.
        rooms[targetRoom].getDirtied();
        if (creatures[creature].getType() == 1) {
            // Creature is an anime.
            creatures[player].lessRespect();
            creatures[player].lessRespect();
            creatures[player].lessRespect();
            std::cout << creature << " growls a lot. Respect is now " << creatures[player].getRespect() << std::endl;
        }
        else {
            // Creature is an human.
            creatures[player].moreRespect();
            creatures[player].moreRespect();
            creatures[player].moreRespect();
            std::cout << creature << " smiles a lot. Respect is now " << creatures[player].getRespect() << std::endl;
        }
        react(creatures, rooms, targetRoom, creature, player, "dirty");
    }
}

void dirtyBySelf(Creature* creatures, Room* rooms, int creature) {
    int room = creatures[creature].getLocation();
    rooms[room].getDirtied();
    std::cout << creature << " dirtied room #" << room << " because it was clean." << std::endl;
}

void loopForCommand(Creature* creatures, int n, Room* rooms, int m) {
    std::string input, command;
    std::getline(std::cin, input);      // For some reason it always accepts an empty command right after the input of creatures.
    int creature = 0;
    int player = 0;
    int separator = -1;
    int respect;

    for (int i = 0; i < n; i++) {
        if (creatures[i].getType() == 0) {
            player = i;
            break;
        }
    }

    while (1) {
        // Check end game condition.
        respect = creatures[player].getRespect();
        if (respect <= 0) {
            std::cout << "\nYou were not liked by the others, game over." << std::endl;
            break;

        }
        else if (respect >= 80) {
            std::cout << "\nGreat Job! You are loved by all, game over." << std::endl;
        }

        std::cout << "\nPlease enter a command." << std::endl;
        std::getline(std::cin, input);

        if (input == "exit") {
            std::cout << "Goodbye!" << std::endl;
            break;
        }
        else {
            separator = input.find(":", 0);
            if (separator != -1) {
                creature = std::stoi(input.substr(0, separator));
                command = input.substr(separator + 1);
            }
            else {
                creature = player;
                command = input;
            }

            // Small out of bound check.
            if (creature < 0 || creature >= m) {
                std::cout << "Error, no such creature." << std::endl;
                continue;
            }

            // Execute commands.
            if (command == "look") {
                look(creatures, rooms, creature);
            }
            else if (command == "clean") {
                clean(creatures, rooms, creature, player);
            }
            else if (command == "dirty") {
                dirty(creatures, rooms, creature, player);
            }
            else if (command == "north") {
                move(creatures, rooms, creature, player, "north");
            }
            else if (command == "south") {
                move(creatures, rooms, creature, player, "south");
            }
            else if (command == "east") {
                move(creatures, rooms, creature, player, "east");
            }
            else if (command == "west") {
                move(creatures, rooms, creature, player, "west");
            }
            else if (command == "help") {
                helpInfo();
            }
            else {
                std::cout << "Error, unknown command." << std::endl;
            }
        }
        separator = -1;
        creature = 0;
        command = "";
    }
}

void look(Creature* creatures, Room* rooms, int creature) {
    int room = creatures[creature].getLocation();
    if (room == -1) {
        std::cout << "This creature has already exited the simulation :(" << std::endl;
        return;
    }
    else {
        // Find out room state.
        std::string state;
        int temp = rooms[room].getState();
        if (temp == 0) {
            state = "clean";
        }
        else if (temp == 1) {
            state = "half-dirty";
        }
        else {
            state = "dirty";
        }

        // Find out about the neighbors.
        std::string neighbors = "neighbors";
        temp = rooms[room].getDoorNorth();
        if (temp != -1) {
            neighbors = neighbors + " " + std::to_string(temp) + " to the north";
        }
        temp = rooms[room].getDoorSouth();
        if (temp != -1) {
            neighbors = neighbors + " " + std::to_string(temp) + " to the south";
        }
        temp = rooms[room].getDoorEast();
        if (temp != -1) {
            neighbors = neighbors + " " + std::to_string(temp) + " to the east";
        }
        temp = rooms[room].getDoorWest();
        if (temp != -1) {
            neighbors = neighbors + " " + std::to_string(temp) + " to the west";
        }

        // Find out about the residence in the room
        std::string contains = "contains:";
        int type, name;
        Creature* cPointer = NULL;
        for (int i = 0; i < 10; i++) {
            cPointer = rooms[room].getCPointers(i);
            if (cPointer != NULL) {
                type = cPointer->getType();
                name = cPointer->getName();
                if (type == 0) {
                    contains = contains + "\nPC";
                }
                else if (type == 1) {
                    contains = contains + "\nanimal " + std::to_string(name);
                }
                else {
                    contains = contains + "\nhuman " + std::to_string(name);
                }
            }
        }

        // Display the state and the neighbors.
        std::cout << "Room " << room << ", " << state << ", " << neighbors << ", " << contains <<std::endl;
    }
}

void react(Creature* creatures, Room* rooms, int targetRoom, int except, int player, std::string action) {
    int type, name, respect;
 
    for (int i = 0; i < 10; i++) {
        Creature* creature = rooms[targetRoom].getCPointers(i);
        if (creature != NULL) {
            type = creature->getType();
            name = creature->getName();
            
            if (action == "clean") {
                if (name != except) {
                    if (type == 1) {
                        creatures[player].moreRespect();
                        respect = creatures[player].getRespect();
                        std::cout << name << " licks your face. Respect is now " << respect << std::endl;
                    }
                    else if (type == 2) {
                        creatures[player].lessRespect();
                        respect = creatures[player].getRespect();
                        std::cout << name << " grumbles. Respect is now " << respect << std::endl;
                    }
                }
            }
            else {
                if (name != except) {
                    if (type == 1) {
                        creatures[player].lessRespect();
                        respect = creatures[player].getRespect();
                        std::cout << name <<  " growls. Respect is now " << respect << std::endl;
                    }
                    else if (type == 2) {
                        creatures[player].moreRespect();
                        respect = creatures[player].getRespect();
                        std::cout << name << " smiles. Respect is now " << respect << std::endl;
                    }
                }
            }
        }
        else {
            continue;
        }
    }

    checkStatus(creatures, rooms, targetRoom, player);
}

void move(Creature* creatures, Room* rooms, int creature, int player, std::string direction) {
    int thisRoom = creatures[creature].getLocation();
    if (thisRoom == -1) {
        std::cout << "This creature already left the simulation." << std::endl;
        return;
    }
    int nextRoom;


    if (direction == "north") {
        nextRoom = rooms[thisRoom].getDoorNorth();
    }
    else if (direction == "south") {
        nextRoom = rooms[thisRoom].getDoorSouth();
    }
    else if (direction == "east") {
        nextRoom = rooms[thisRoom].getDoorEast();
    }
    else {
        nextRoom = rooms[thisRoom].getDoorWest();
    }

    if (nextRoom != -1) {
        if (rooms[nextRoom].getOccupancy() < 10) {
            rooms[thisRoom].remove(&creatures[creature]);
            rooms[nextRoom].populate(&creatures[creature]);
            creatures[creature].setLocation(nextRoom);
            if (creature == player) {
                std::cout << "You leave towards the " << direction << ".\n";
                return;
            }
            else {
                std::cout << creature << " leaves towards the " << direction << ".\n";
                int newState = rooms[nextRoom].getState();
                int type = creatures[creature].getType();
                if (type == 1 && newState == 2) {
                    cleanBySelf(creatures, rooms, creature);
                }
                else if (type == 2 && newState == 0) {
                    dirtyBySelf(creatures, rooms, creature);
                }
            }
        }
        else {
            std::cout << creature << " can't enter room #" << nextRoom << " because it's full." << std::endl;
            return;
        }
    }
    else {
        std::cout << "Error, room #" << thisRoom << " does not have a door facing " << direction << std::endl;
        return;
    }
}

// Creature have already reacted, now we check if anybody needs to leave the room
void checkStatus(Creature* creatures, Room* rooms, int room, int player) {
    int state = rooms[room].getState();
    int type, name;
    std::string direction = "";
    Creature* cPointer;

    for (int i = 0; i < 10; i++) {
        cPointer = rooms[room].getCPointers(i);

        if (cPointer != NULL) {
            type = cPointer->getType();
            name = cPointer->getName();

            if (type == 1 && state == 2) {
                direction = whichWay(rooms, room);
            }
            else if (type == 2 && state == 0) {
                direction = whichWay(rooms, room);
            }

            // Empty string means that creature don't have to leave, none means that a creature have no where to go.
            if (direction == "none") {
                leave(creatures, name, rooms, room, player);
            }
            else if (direction == "north" || direction == "south" || direction == "east" || direction == "west") {
                move(creatures, rooms, name, player, direction);
            }

            direction = "";
        }
        else {
            continue;
        }
    }
}

std::string whichWay(Room* rooms, int thisRoom) {
    int pick = rand() % 4;
    int nextRoom = -1;
    std::string direction = "none";

    for (int i = 0; i < 4; i++) {
        if (pick == 0) {
            nextRoom = rooms[thisRoom].getDoorNorth();
            direction = "north";
        }
        else if (pick == 1) {
            nextRoom = rooms[thisRoom].getDoorSouth();
            direction = "south";
        }
        else if (pick == 2) {
            nextRoom = rooms[thisRoom].getDoorEast();
            direction = "east";
        }
        else if (pick == 3) {
            nextRoom = rooms[thisRoom].getDoorWest();
            direction = "west";
            pick = -1;
        }

        if (nextRoom != -1) {
            if (rooms[nextRoom].getOccupancy() < 10) { return direction; }
        }

        direction = "none";
        pick++;
    }
    return direction;
}

void leave(Creature* creatures, int creature, Room* rooms, int room, int player) {
    int type;
    creatures[creature].setLocation(-1);
    rooms[room].remove(&creatures[creature]);

    std::cout << creature << " drill a hole in the ceiling and crawl out of the house." << std::endl;
    Creature* temp;
    for (int i = 0; i < 10; i++) {
        temp = rooms[room].getCPointers(i);

        if (temp != NULL) {
            creature = temp->getName();
            type = temp->getType();

            if (type == 1) {
                creatures[player].lessRespect();
                std::cout << creature << " growls. Respect is now " << creatures[player].getRespect() << std::endl;
            }
            else if (type == 2) {
                creatures[player].lessRespect();
                std::cout << creature << " grumbles. Respect is now " << creatures[player].getRespect() << std::endl;
            }
        }
    }
}

void helpInfo() {
    std::cout << "Available string commands:" << std::endl;
    std::cout << "look\ncreatureNumber:look" << std::endl;
    std::cout << "clean\ncreatureNumber:clean" << std::endl;
    std::cout << "dirty\ncreatureNumber:dirty" << std::endl;
    std::cout << "north\ncreatureNumber:north" << std::endl;
    std::cout << "south\ncreatureNumber:south" << std::endl;
    std::cout << "east\ncreatureNumber:east" << std::endl;
    std::cout << "west\ncreatureNumber:west" << std::endl;
    std::cout << "exit" << std::endl;
}
