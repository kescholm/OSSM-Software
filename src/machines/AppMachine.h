#ifndef OSSM_SOFTWARE_APPMACHINE_H
#define OSSM_SOFTWARE_APPMACHINE_H

#include "AppStatesEvents.h"
#include "abstract/Machine.h"

class AppMachine : public Machine<App::States, App::Events> {
  public:
    AppMachine();

    void setup() override;
    void loop() override;
    void handleEvent() override;
    void updateDisplay() override;
};

#endif  // OSSM_SOFTWARE_APPMACHINE_H
