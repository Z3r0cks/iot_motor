#include <Arduino.h>
#include <Motor.h>

struct Question {
    uint8_t correctAnswer;
};

enum Phase { DeepSleep, QuestionChoice, AnswerQuestion, ResolveAnswer };

class Quiz {
   private:
    Motor* motor;
    uint8_t pinA;
    uint8_t pinB;
    uint8_t pinC;
    uint8_t pinD;
    uint8_t pinDataIn;
    uint8_t pinDataOut;
    bool isAtStart;
    bool isGameMaster;
    Phase phase;
    int8_t score;
    int8_t oppositeScore;
    uint8_t* questions;
    int8_t currentQuestion;
    void deepSleep();
    void chooseQuestion();

   public:
    Quiz(Motor* motor,
         uint8_t pinA,
         uint8_t pinB,
         uint8_t pinC,
         uint8_t pinD,
         uint8_t pinDataIn,
         uint8_t pinDataOut,
         bool isGameMaster);
    void wakeUp();
    void run();
};