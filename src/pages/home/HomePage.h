//
// Created by Andrew Koenig on 2023-10-13.
//

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

    void loop() override;
};

#endif  // OSSM_SOFTWARE_HOMEPAGE_H
