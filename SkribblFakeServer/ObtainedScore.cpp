#include "ObtainedScore.h"

// Default constructor
ObtainedScore::ObtainedScore() : id(0), playerName(""), obtainedScore(0) {}

// Parameterized constructor
ObtainedScore::ObtainedScore(int id, const std::string& playerName, int obtainedScore)
    : id(id), playerName(playerName), obtainedScore(obtainedScore) {}

// Destructor
ObtainedScore::~ObtainedScore() {
    // Destructor implementation (if needed)
}

// Getter functions
int ObtainedScore::GetId() const {
    return id;
}

const std::string& ObtainedScore::GetPlayerName() const {
    return playerName;
}

int ObtainedScore::GetObtainedScore() const {
    return obtainedScore;
}

// Setter functions
void ObtainedScore::SetId(int id) {
    this->id = id;
}

void ObtainedScore::SetPlayerName(const std::string& playerName) {
    this->playerName = playerName;
}

void ObtainedScore::SetObtainedScore(int scorObtinut) {
    this->obtainedScore = scorObtinut;
}

std::ostream& operator<<(std::ostream& os, const ObtainedScore& score)
{
    os << "ID: " << score.GetId() << ", Player Name: " << score.GetPlayerName()
        << ", Obtained Score: " << score.GetObtainedScore();
    return os;
}
