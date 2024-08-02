#include <iostream>
#include <fstream>
#include <ctime> 
using namespace std;

const string introduction = "Набери команду для поиска сокровищ.(максимум 10 человек)\n"
"Меньше людей — больше денег, но на вас могут\n"
"напасть бандиты. Цель: выжить и получить максимум золота.\n"
"(После каждого продолжения нажимайте «Enter»)\n"
"                                                    ";

class Gold {
public:
    Gold() {
        gold = rand() % 901 + 100;
    }

    int getGold() const {
        return gold;
    }
private:
    int gold;
};

class Survivors {
public:
    Survivors(int playersOnTeam, int numberOfBandits) {
        survivors = playersOnTeam - numberOfBandits;
    }

    int getSurvivors() const {
        return survivors;
    }
private:
    int survivors;
};

class Game {
public:
    void start() {
        cout << introduction << endl;
        getPlayersOnTeam();
        if (teamSize()) {
            play();
        }
        else {
            cout << "Некорректное количество членов команды. Программа завершена." << endl;
        }
    }
    
private:
    int playersOnTeam;
    int numberOfBandits;
    ofstream resultFile;

    void openResultFile() {
        resultFile.open("game_results.txt", ios::app);
        if (!resultFile) {
            cerr << "Не удалось открыть файл для записи результатов." << endl;
            exit(1);
        }
    }

    void closeResultFile() {
        resultFile.close();
    }

    void waitForEnter() {
        cin.get();
    }

    void getPlayersOnTeam() {
        cout << "Сколько людей ты возьмёшь в команду?: ";
        cin >> playersOnTeam;
        cin.ignore();
        waitForEnter();
    }

    bool teamSize() {
        return !cin.fail() && playersOnTeam >= 1 && playersOnTeam <= 10;
    }

    void play() {
        openResultFile();
        numberOfBandits = rand() % 11;
        cout << "На вас напало " << numberOfBandits << " бандитов" << endl;
        waitForEnter();

        if (numberOfBandits == 0) {
            noBandits();
        }
        else {
            banditsAttack();
        }
        resultFile << "--------------------------------\n";
        closeResultFile();
    }

    void noBandits() {
        cout << "На вас никто не напал, вам повезло! " << endl;
        resultFile << "На вас никто не напал, вам повезло! " << endl;
        waitForEnter();
        Gold treasure;
        int totalGold = treasure.getGold();
        cout << "Вы нашли сокровище с " << totalGold << " золотыми монетами" << endl;
        resultFile << "Вы нашли сокровище с " << totalGold << " золотыми монетами" << endl;
        waitForEnter();
        cout << "Ты получил: " << totalGold / playersOnTeam << " золотых монет" << endl;
        resultFile << "Ты получил: " << totalGold / playersOnTeam << " золотых монет" << endl;
        waitForEnter();
    }

    void banditsAttack() {
        Survivors survivors(playersOnTeam, numberOfBandits);
        int numSurvivors = survivors.getSurvivors();
        int randomNum = rand() % 10 + 1;

        if (randomNum == 1) {
            cout << "Один из членов команды сбежал!" << endl;
            resultFile << "Один из членов команды сбежал!" << endl;
            waitForEnter();
            numSurvivors--;
        }

        if (numSurvivors > 0) {
            cout << "Победа с потерями" << endl;
            resultFile << "Победа с потерями" << endl;
            waitForEnter();
            cout << "Вас осталось " << numSurvivors << " членов команды " << endl;
            resultFile << "Вас осталось " << numSurvivors << " членов команды " << endl;
            waitForEnter();
            Gold treasure;
            int totalGold = treasure.getGold();
            cout << "Вы нашли сокровище с " << totalGold << " золотыми монетами" << endl;
            resultFile << "Вы нашли сокровище с " << totalGold << " золотыми монетами" << endl;
            waitForEnter();

            int Yourgold = totalGold / numSurvivors;
            cout << "Ты получил: " << Yourgold << " золотых монет" << endl;
            resultFile << "Ты получил: " << Yourgold << " золотых монет" << endl;
            waitForEnter();
        }
        else {
            cout << "Ваша команда погибла" << endl;
            resultFile << "Ваша команда погибла" << endl;
            waitForEnter();
        }
    }
};

int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));
    Game game;
    game.start();
    return 0;
}