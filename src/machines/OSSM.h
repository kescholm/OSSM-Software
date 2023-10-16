#ifndef OSSM_SOFTWARE_OSSM_H
#define OSSM_SOFTWARE_OSSM_H

#include "ESP_FlexyStepper.h"
#include "OSSMStatesEvents.h"
#include "abstract/StateMachine.h"

class OSSM : public StateMachine<OSSM_NS::States, OSSM_NS::Events> {
    const char *errorMessage;
    void handleEvent() override;
    void loopInternal() override;

  public:
    OSSM();

    void setError(const char *message);
    ESP_FlexyStepper stepper;
};

#endif  // OSSM_SOFTWARE_OSSM_H
