#ifndef OSSM_SOFTWARE_OSSM_H
#define OSSM_SOFTWARE_OSSM_H

#include "ESP_FlexyStepper.h"
#include "OSSMStatesEvents.h"
#include "abstract/StateMachine.h"

class OSSM : public StateMachine<OSSM_NS::States, OSSM_NS::Events> {
  public:
    explicit OSSM(ESP_FlexyStepper *stepper);
    void loop() override;
    void draw() override;
    void handleEvent() override;

    ESP_FlexyStepper *stepper;
};

#endif  // OSSM_SOFTWARE_OSSM_H
