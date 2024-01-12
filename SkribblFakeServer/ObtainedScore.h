#pragma once
#include <string>

class ObtainedScore {
public:
    // Constructors
    ObtainedScore(); // Default constructor
    ObtainedScore(int id, const std::string& playerName, int obtainedScore);

    // Destructor
    ~ObtainedScore();

    // Getter functions
    int GetId() const;
    const std::string& GetPlayerName() const;
    int GetObtainedScore() const;

    // Setter functions
    void SetId(int id);
    void SetPlayerName(const std::string& playerName);
    void SetObtainedScore(int obtainedScore);

private:
    int id;
    std::string playerName;
    int obtainedScore;
};

