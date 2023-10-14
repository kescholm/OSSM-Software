#ifndef OSSM_SOFTWARE_HOMEPAGE_H
#define OSSM_SOFTWARE_HOMEPAGE_H

#include "HomeStatesEvents.h"
#include "machines/OSSM.h"

class HomePage : public StateMachine<HOME_NS::States, HOME_NS::Events> {
  private:
    OSSM *ossm;
    void homing();

  public:
    explicit HomePage(OSSM *ossm);

    void loopInternal() override;
};

#endif  // OSSM_SOFTWARE_HOMEPAGE_H
