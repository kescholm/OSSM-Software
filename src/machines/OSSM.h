#ifndef OSSM_SOFTWARE_OSSM_H
#define OSSM_SOFTWARE_OSSM_H

#include "OSSMStatesEvents.h"
#include "abstract/StateMachine.h"

class OSSM : public StateMachine<OSSM_NS::States, OSSM_NS::Events> {
  public:
    OSSM();

    void setup() override;
    void loop() override;
    void handleEvent() override;
    void updateDisplay() override;
};

#endif  // OSSM_SOFTWARE_OSSM_H
