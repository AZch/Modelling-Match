#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;

std::string sizesParams = "sizes";
std::string homeGoalsParams = "homeGouls";
std::string homeShotsParams = "homeShots";
std::string homeRangeParams = "homeRange";
std::string awayGoalsParams = "awayGoals";
std::string awayShotsParams = "awayShots";
std::string awayRangeParams = "awayRange";
std::string maxCountParams = "maxCount";
std::string totalParams = "total";

class Game {
    private:
        int *homeGoals, *homeShots, *awayShots, *awayGoals;
        float *homeRange, *awayRange;
    public:
        Game(int *homeGoalsT, int *homeShotsT, float *homeRangeT, int *awayGoalsT, int *awayShotsT, float *awayRangeT) {
            homeGoals = homeGoalsT;
            homeShots = homeShotsT;
            homeRange = homeRangeT;
            awayShots = awayShotsT;
            awayGoals = awayGoalsT;
            awayRange = awayRangeT;
        }
    void calc(int *results) {
        int currentFirst = 0, currentSec = 0, currentRange = 0;
        for (int i = 0; i < 90; i++) {
            currentRange = currentFirst - currentSec;
            for (int j = 0; j < 5; j++) {
                currentFirst += someGoals(homeShots[j], homeGoals[j], currentRange, homeRange);
                currentSec += someGoals(awayShots[j], awayGoals[j], currentRange * (-1), awayRange);
            }
        }
        printf("(%d : %d)", currentFirst, currentSec);
        results[0] = currentFirst;
        results[1] = currentSec;
    }

    int getRandomNum() {
        int random = 1 + rand() % 10000;
        //cout << random << endl;

        return random;
    }

    int someGoals(int shots, int goals, int currentRange, float *dataRange) {
        if (getRandomNum() * rangeFoScore(currentRange, dataRange) <= shots) {
            if (getRandomNum() <= goals) {
                return 1;
            }
        }
        return 0;
    }

    float rangeFoScore(int currentRange, float *dataRange) {
        if (currentRange > 1) {
            return dataRange[0];
        } else if (currentRange == 1) {
            return dataRange[1];
        } else if (currentRange == 0) {
            return dataRange[2];
        } else if (currentRange == -1) {
            return dataRange[3];
        } else if (currentRange < -1) {
            return dataRange[4];
        }
        return 0;
    }
};

string *getData(string fileName, string *lines) {
    std::string line;
    int count = 0;
    std::ifstream in(fileName);
    if (in.is_open()) {
        while (getline(in, line)) {
            lines[count++] = line;
        }
    }
    in.close();

    return lines;
}

bool compareString(string first, string second) {
    if (first.size() != second.size()) {
        return false;
    } else {
        for (int i = 0; i < first.size(); i++) {
            if (first[i] != second[i]) {
                return false;
            }
        }
    }
    return true;
}

int* fillArrayInt(string data, int size) {
    vector<string> buf;
    boost::split(buf, data, boost::is_any_of(" "));
    int *array = new int[size];
    int count = 0;
    for (int j = 0; j < buf.size(); j++) {
        if (buf[j].size() > 0) {
                array[count++] = stoi(buf[j]);
        }
    }
    return array;
}

float* fillArrayFloat(string data, int size) {
    vector<string> buf;
    boost::split(buf, data, boost::is_any_of(" "));
    float *array = new float[size];
    int count = 0;
    for (int j = 0; j < buf.size(); j++) {
        if (buf[j].size() > 0) {
                array[count++] = stof(buf[j]);
        }
    }
    return array;
}

int getIntFromData(string data) {
    vector<string> buf;
    boost::split(buf, data, boost::is_any_of(" "));
    for (int j = 0; j < buf.size(); j++) {
        if (buf[j].size() > 0) {
            return stoi(buf[j]);
        }
    }
    return 0;
}

float getFloatFromData(string data) {
    vector<string> buf;
    boost::split(buf, data, boost::is_any_of(" "));
    for (int j = 0; j < buf.size(); j++) {
        if (buf[j].size() > 0) {
            return stof(buf[j]);
        }
    }
    return 0.0;
}

void fillResult(int first, int second, int nobody, int all, int under, int over) {
    std::ofstream out;
    out.open("result.txt");
    if (out.is_open()) {
        out << "P1: " << ((float) first / all) * 100 << endl;
        out << "X: " << ((float) nobody / all) * 100 << endl;
        out << "P2: " << ((float) second / all) * 100 << endl;
        out << "U2.5: " <<  ((float) under /all) * 100 << endl;
        out << "O2.5: " << ((float) over / all) * 100 << endl;
        out << "Count game: " << all << "\nTime read and modelling: " << clock() / 1000000.0 << endl;
    }
    out.close();
}

int main() {
    srand( time(NULL));

    string params[9];
    int arraySize = 0;
    int total = 2.5;
    int maxCount;

    int *homeGoals;
    int *homeShots;
    float *homeRange;
    int *awayGoals;
    int *awayShots;
    float *awayRange;


    // Read start data
    getData("input.txt", params);
    for (int i = 0; i < 9; i++) {
        vector<string> result;
        boost::split(result, params[i], boost::is_any_of(":"));
        vector<string> buf;
        if (compareString(sizesParams, result[0])) {
            arraySize = getIntFromData(result[1]);
        } else if (compareString(homeGoalsParams, result[0])) {
            homeGoals = fillArrayInt(result[1], arraySize);
        } else if (compareString(homeShotsParams, result[0])) {
            homeShots = fillArrayInt(result[1], arraySize);
        } else if (compareString(homeRangeParams, result[0])) {
            homeRange = fillArrayFloat(result[1], arraySize);
        } else if (compareString(awayGoalsParams, result[0])) {
            awayGoals = fillArrayInt(result[1], arraySize);
        } else if (compareString(awayShotsParams, result[0])) {
            awayShots = fillArrayInt(result[1], arraySize);
        } else if (compareString(awayRangeParams, result[0])) {
            awayRange = fillArrayFloat(result[1], arraySize);
        } else if (compareString(maxCountParams, result[0])) {
            maxCount = getIntFromData(result[1]);
        } else if (compareString(totalParams, result[0])) {
            total = getFloatFromData(result[1]);
        }
    }
    cout << "Read time: " << clock() / 1000000.0 << endl;

    unsigned int startTime = clock();
    int countFirst = 0, countSec = 0, countNobody = 0, totalU = 0, totalO = 0;
    int results[2];
    Game *game = new Game(homeGoals, homeShots, homeRange, awayGoals, awayShots, awayRange);
    for (int i = 0; i < maxCount; i++) {
        printf("%d", i);
        game->calc(results);
        if (results != NULL) {
            if (results[0] > results[1]) {
                countFirst++;
            } else if (results[0] < results[1]) {
                countSec++;
            } else {
                countNobody++;
            }
            if ((float) (results[0] + results[1]) > total) {
                totalO++;
            } else {
                totalU++;
            }
        }
        cout << (clock() - startTime) / 1000000.0 << endl;
    }
    cout << "P1: " << ((float) countFirst / maxCount) * 100 << endl;
    cout << "X: " << ((float) countNobody / maxCount) * 100 << endl;
    cout << "P2: " << ((float) countSec / maxCount) * 100 << endl;
    cout << "U2.5: " <<  ((float) totalU /maxCount) * 100 << endl;
    cout << "O2.5: " << ((float) totalO / maxCount) * 100 << endl;
    delete game;
    fillResult(countFirst, countSec, countNobody, maxCount, totalU, totalO);
    return 0;
}