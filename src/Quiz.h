#include <Arduino.h>

struct Question {
    uint8_t catogery;
    uint8_t correctAnswer;
};

enum Phase {
    DeepSleep,
    CategoryChoice,
    QuestionChoice,
    AnswerQuestion,
    ResolveAnswer
};

class Quiz {
   private:
    bool isGameMaster;
    Phase phase;
    int8_t score;
    int8_t oppositeScore;
    uint8_t category[3];
    Question questions[12];
    uint8_t currentCategory;
    uint8_t currentQuestion;
    void chooseCategory();
    void chooseQuestion();
    
   public:
    Quiz(uint8_t pinA,
         uint8_t pinB,
         uint8_t pinC,
         uint8_t pinD,
         uint8_t pinData);
    void wakeUp();
    void run();
};