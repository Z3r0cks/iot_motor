#include <Quiz.h>

#define Threshold 150

// TODO: set correct time to rotate
#define TimeToRotate 100

Quiz::Quiz(Motor* motor,
           uint8_t pinA,  // up
           uint8_t pinB,  // back
           uint8_t pinC,  // ok
           uint8_t pinD,  // down
           uint8_t pinDataIn,
           uint8_t pinDataOut,
           bool isGameMaster) {
    this->motor = motor;
    this->pinA = pinA;
    this->pinB = pinB;
    this->pinC = pinC;
    this->pinD = pinD;
    this->pinDataIn = pinDataIn;
    this->pinDataOut = pinDataOut;
    this->isGameMaster = isGameMaster;
    this->isAtStart = true;
    this->phase = Phase::DeepSleep;
    this->score = 0;
    this->oppositeScore = 0;
    // TODO: set correct numbers for answers
    this->questions = new uint8_t[13]{0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0};
    this->currentQuestion = -1;

    pinMode(pinA, INPUT);
    pinMode(pinB, INPUT);
    pinMode(pinC, INPUT);
    pinMode(pinD, INPUT);
    pinMode(pinDataIn, INPUT);
    pinMode(pinDataOut, OUTPUT);
};

void Quiz::deepSleep() {
    if (digitalRead(pinDataIn) == 1) {
        this->phase = Phase::QuestionChoice;
    };
}

void Quiz::wakeUp() {
    digitalWrite(pinDataOut, 1);
    this->phase = Phase::QuestionChoice;
}

void Quiz::chooseQuestion() {
    if (this->isGameMaster) {
        if (touchRead(this->pinA) > Threshold) {
            if (this->currentQuestion > -1) {
                this->motor->rotateLeft(TimeToRotate);
                currentQuestion--;
            }
        } else if (touchRead(this->pinB) > Threshold) {
        } else if (touchRead(this->pinC) > Threshold) {
            digitalWrite(this->pinDataOut, currentQuestion);
        } else if (touchRead(this->pinD) > Threshold) {
            if (this->currentQuestion < 12) {
                this->motor->rotateRight(TimeToRotate);
                currentQuestion++;
            }
        }
    } else {
    }
}

void Quiz::run() {
    switch (this->phase) {
        case (Phase::DeepSleep):
            this->deepSleep();
            break;
        case (Phase::QuestionChoice):
            this->chooseQuestion();
            break;
        case (Phase::AnswerQuestion):
            break;
        case (Phase::ResolveAnswer):
            break;
    }
}
